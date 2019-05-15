#include "stdafx.h"
#include "QAQNetworkImpl.h"

#include <iostream>
#include <string>
using namespace std;

#include <curl/curl.h>

void SetShareHandle(CURL *curl_handle)
{
	static CURLSH *shared_handle = nullptr;

	if (!shared_handle)
	{
		shared_handle = curl_share_init();
		curl_share_setopt(shared_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
	}

	curl_easy_setopt(curl_handle, CURLOPT_SHARE, shared_handle);
	curl_easy_setopt(curl_handle, CURLOPT_DNS_CACHE_TIMEOUT, 60 * 5);
}

QAQNetworkImpl::QAQNetworkImpl()
{
	reset();
}


QAQNetworkImpl::~QAQNetworkImpl()
{
	stopAsync();
}

void QAQNetworkImpl::syncGet()
{
	asyncGetThread();
}

void QAQNetworkImpl::syncPost()
{
	asyncPostThread();
}

void QAQNetworkImpl::asyncGet()
{
	async_thread_ = std::move(std::thread(&QAQNetworkImpl::asyncGetThread, this));
}

void QAQNetworkImpl::asyncPost()
{
	async_thread_ = std::move(std::thread(&QAQNetworkImpl::asyncPostThread, this));

}

void QAQNetworkImpl::stopAsync()
{
	is_cancel_ = true; //set quit flag
	if (std::this_thread::get_id() != async_thread_.get_id())
	{
		if (async_thread_.joinable())
		{
			async_thread_.join();//wait for thread to quit
		}
	}
	reset();
}


void QAQNetworkImpl::setUserData(void *opaque)
{
	opaque_ = opaque;
}

void* QAQNetworkImpl::getUserData()
{
	return opaque_;
}

void QAQNetworkImpl::setDelegate(QAQNetwork::Delegate*dele)
{
	delegate_ = dele;
}

void QAQNetworkImpl::reset()
{
	is_cancel_ = false;
	req_.reset();
	reply_.reset();
}


QAQNetworkReq* QAQNetworkImpl::getRequest()
{
	return &req_;
}

QAQNetworkReply* QAQNetworkImpl::getReply()
{
	return &reply_;
}

void QAQNetworkImpl::asyncGetThread()
{
	CURL *curl = curl_easy_init();
	SetShareHandle(curl);
	struct curl_slist *headers = nullptr;
	for (int i = 0; i < req_.getHeaderCount(); ++i)
	{
		headers = curl_slist_append(headers, req_.getHeader(i));
	}
	//set headers
	if (req_.getHeaderCount() > 0)
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	curl_easy_setopt(curl, CURLOPT_URL, req_.getUrl());

	/* example.com is redirected, so we tell libcurl to follow redirection */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	//begin write function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QAQNetworkImpl::WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)this);
	//end write function

	//begin progress
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, QAQNetworkImpl::ProgressCallback);
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	//end progress

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
	/////* 设置连接超时,单位:毫秒 */
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 5000L);

	////设置速度超时
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);//1byte
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);//5seconds

													   /* Perform the request, res will get the return code */
	CURLcode res = curl_easy_perform(curl);

	/*manual stop*/
	if (res != CURLE_ABORTED_BY_CALLBACK && res != CURLE_WRITE_ERROR)//CURLE_ABORTED_BY_CALLBACK
	{
		/* Check for errors */
		if (CURLE_OK == res)
		{
			reply_.setError(REPLY_NO_ERROR);
		}
		else if (CURLE_OPERATION_TIMEDOUT == res)
		{
			reply_.setError(REPLY_TIME_OUT);
		}

		if (delegate_)
		{
			delegate_->onReply(this, &reply_);
		}
	}

	if (headers)
		curl_slist_free_all(headers); /* free the header list */

	if (curl)
		curl_easy_cleanup(curl);
}

void QAQNetworkImpl::asyncPostThread()
{
	CURL *curl = curl_easy_init();
	SetShareHandle(curl);
	struct curl_slist *headers = nullptr;
	for (int i = 0; i < req_.getHeaderCount(); ++i)
	{
		headers = curl_slist_append(headers, req_.getHeader(i));
	}
	//set headers
	if (req_.getHeaderCount() > 0)
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	///*post data here*/
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req_.post_data_.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, req_.post_data_.size());

	curl_easy_setopt(curl, CURLOPT_URL, req_.getUrl());

	/* example.com is redirected, so we tell libcurl to follow redirection */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	//begin write function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, QAQNetworkImpl::WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)this);
	//end write function

	//begin progress
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, QAQNetworkImpl::ProgressCallback);
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	//end progress

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
	/////* 设置连接超时,单位:毫秒 */
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 5000L);

	////设置速度超时
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);//1byte
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);//5seconds

	/* Perform the request, res will get the return code */
	CURLcode res = curl_easy_perform(curl);

	/*manual stop*/
	if (res != CURLE_ABORTED_BY_CALLBACK && res != CURLE_WRITE_ERROR)//CURLE_ABORTED_BY_CALLBACK
	{
		/* Check for errors */
		if (CURLE_OK == res)
		{
			reply_.setError(REPLY_NO_ERROR);
		}
		else if (CURLE_OPERATION_TIMEDOUT == res)
		{
			reply_.setError(REPLY_TIME_OUT);
		}

		if (delegate_)
		{
			delegate_->onReply(this, &reply_);
		}
	}

	if (headers)
		curl_slist_free_all(headers); /* free the header list */

	if (curl)
		curl_easy_cleanup(curl);
}

int QAQNetworkImpl::onProgress(double t, double d)
{
	if (delegate_)
	{
		 delegate_->onDataProgress(this, t, d);
	}
	return 0;
}



size_t QAQNetworkImpl::WriteMemoryCallback(void *buffer, size_t size, size_t count, void * stream)
{
	QAQNetworkImpl* pStream = static_cast<QAQNetworkImpl *>(stream);

	if (pStream)
	{
		return pStream->onWrite(buffer,size, count);
	}
	return 0;
};


int QAQNetworkImpl::ProgressCallback(char *user,
	double t, /* dltotal */
	double d, /* dlnow */
	double ultotal,
	double ulnow)
{
	QAQNetworkImpl* imp = (QAQNetworkImpl*)user;
	if (imp)
	{
		return imp->onProgress(t, d);
	}
	return 0;
}

size_t QAQNetworkImpl::onWrite(void* buffer, size_t size, size_t count)
{
	if (is_cancel_)
	{//the flag to unblock curl_easy_perform
		return 0;
	}
	int write_size = size * count;

	if (delegate_)
	{
		if (!delegate_->onTrunk(this, (char *)buffer, write_size))
		{
			reply_.result_.append((char *)buffer, write_size);
		}
	}
	else
	{
		reply_.result_.append((char *)buffer, write_size);
	}

	return write_size;
}
