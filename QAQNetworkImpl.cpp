#include "stdafx.h"
#include "QAQNetworkImpl.h"

#include <iostream>
#include <string>
using namespace std;




QAQNetworkImpl::QAQNetworkImpl()
	:user_(nullptr)
	, data_cb_(nullptr)
	, headers(nullptr)
	, is_running_(false)
	, pro_cb_(nullptr)
	, inter_face_(nullptr)
	, is_cancel_(false)
	, reply_(nullptr)
{
	
}


QAQNetworkImpl::~QAQNetworkImpl()
{
	Stop();
}

QAQNetworkReply* QAQNetworkImpl::SyncGet(QAQNetworkReq * req, void *user , DataCallBack data_cb, DataProgress pro_cb)
{
	is_running_ = true;
	req_ = req;

	user_ = user;
	data_cb_ = data_cb;
	pro_cb_ = pro_cb;
	

	ASyncGetThread();
	return reply_;
}

void QAQNetworkImpl::ASyncGet(QAQNetworkReq *req, void *user, DataCallBack data_cb, DataProgress pro_cb)
{
	is_running_ = true;
	req_ = req;

	user_ = user;
	data_cb_ = data_cb;
	pro_cb_ = pro_cb;
	
	async_thread_ = std::move(std::thread(&QAQNetworkImpl::ASyncGetThread, this));

}

void QAQNetworkImpl::DeleteReply()
{
	if (reply_)
	{
		delete reply_;
		reply_ = nullptr;
	}
}


void QAQNetworkImpl::Stop()
{
	is_cancel_ = true; //set quit flag
	if (std::this_thread::get_id() != async_thread_.get_id())
	{
		if (async_thread_.joinable())
		{
			async_thread_.join();//wait for thread to quit
		}
	}

	DeleteReply();

	if (headers)
		curl_slist_free_all(headers); /* free the header list */
	headers = nullptr;
	if (curl_)
		curl_easy_cleanup(curl_);
	curl_ = nullptr;
}


void QAQNetworkImpl::ASyncGet2(QAQNetworkReq *req, QAQNetworkInterface *face)
{
	is_running_ = true;
	inter_face_ = face;
	req_ = req;
	async_thread_ = std::move(std::thread(&QAQNetworkImpl::ASyncGetThread, this));
}

void QAQNetworkImpl::ASyncPost2(QAQNetworkReq *req, const char*post_data, QAQNetworkInterface *face)
{
	is_running_ = true;
	inter_face_ = face;
	post_data_ = post_data;
	req_ = req;
	//throw std::logic_error("The method or operation is not implemented.");
	async_thread_ = std::move(std::thread(&QAQNetworkImpl::ASyncPostThread, this));

}

QAQNetworkReply* QAQNetworkImpl::SyncPost(QAQNetworkReq * req, const char*post_data, void *user, DataCallBack data_cb, DataProgress pro_cb)
{
	post_data_ = post_data;
	req_ = req;
	
	user_ = user;
	data_cb_ = data_cb;
	pro_cb_ = pro_cb;

	ASyncPostThread();
	return reply_;
}

void QAQNetworkImpl::ASyncPost(QAQNetworkReq *req, const char*post_data, void *user, DataCallBack data_cb, DataProgress pro_cb)
{
	is_running_ = true;
	post_data_ = post_data;
	req_ = req;

	user_ = user;
	data_cb_ = data_cb;
	pro_cb_ = pro_cb;

	//throw std::logic_error("The method or operation is not implemented.");
	async_thread_ = std::move(std::thread(&QAQNetworkImpl::ASyncPostThread, this));

}

void QAQNetworkImpl::ASyncGetThread()
{
	is_cancel_ = false;
	is_running_ = true;
	curl_ = curl_easy_init();
	SetShareHandle(curl_);
	for (int i = 0; i < req_->GetHeaderCount(); ++i)
	{
		headers = curl_slist_append(headers, req_->GetHeader(i));
	}
	//set headers
	if (req_->GetHeaderCount() > 0)
		curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, false);

	curl_easy_setopt(curl_, CURLOPT_URL, req_->GetUrl());

	/* example.com is redirected, so we tell libcurl to follow redirection */
	curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);

	//begin write function
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, QAQNetworkImpl::WriteMemoryCallback);
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void*)this);
	//end write function

	//begin progress
	curl_easy_setopt(curl_, CURLOPT_NOPROGRESS, FALSE);
	curl_easy_setopt(curl_, CURLOPT_PROGRESSFUNCTION, QAQNetworkImpl::ProgressCallback);
	curl_easy_setopt(curl_, CURLOPT_PROGRESSDATA, this);
	//end progress

	curl_easy_setopt(curl_, CURLOPT_VERBOSE, 0L);
	/////* 设置连接超时,单位:毫秒 */
	curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT_MS, 5000L);

	/* Perform the request, res will get the return code */
	CURLcode res = curl_easy_perform(curl_);

	/*manual stop*/
	if (res != CURLE_ABORTED_BY_CALLBACK && res != CURLE_WRITE_ERROR)//CURLE_ABORTED_BY_CALLBACK
	{
		/* Check for errors */
		if (res != CURLE_OK)
		{
			reply_ = new QAQNetworkReply;
		}
		else
		{
			reply_ = new QAQNetworkReply;
			reply_->SetData((char*)result_.c_str());
			reply_->SetLength(result_.size());
			reply_->SetError(REPLY_NO_ERROR);
		}

		if (data_cb_)
		{
			data_cb_(reply_, user_);
		}
		else if (inter_face_)
		{
			inter_face_->OnDataReply(reply_);
		}
	}
	is_running_ = false;
}

void QAQNetworkImpl::ASyncPostThread()
{
	is_cancel_ = false;
	is_running_ = true;

	curl_ = curl_easy_init();
	SetShareHandle(curl_);
	for (int i = 0; i < req_->GetHeaderCount(); ++i)
	{
		headers = curl_slist_append(headers, req_->GetHeader(i));
	}
	//set headers
	if (req_->GetHeaderCount() > 0)
		curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

	/*post data here*/
	curl_easy_setopt(curl_, CURLOPT_POST, 1L);
	curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, post_data_.c_str());
	curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, post_data_.size());


	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, false);

	curl_easy_setopt(curl_, CURLOPT_URL, req_->GetUrl());

	/* example.com is redirected, so we tell libcurl to follow redirection */
	curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);

	//begin write function
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, QAQNetworkImpl::WriteMemoryCallback);
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void*)this);
	//end write function

	//begin progress
	curl_easy_setopt(curl_, CURLOPT_NOPROGRESS, FALSE);
	curl_easy_setopt(curl_, CURLOPT_PROGRESSFUNCTION, QAQNetworkImpl::ProgressCallback);
	curl_easy_setopt(curl_, CURLOPT_PROGRESSDATA, this);
	//end progress

	curl_easy_setopt(curl_, CURLOPT_VERBOSE, 0L);
	/////* 设置连接超时,单位:毫秒 */
	curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT_MS, 5000L);

	/* Perform the request, res will get the return code */
	CURLcode res = curl_easy_perform(curl_);

	/*manual stop*/
	if (res != CURLE_ABORTED_BY_CALLBACK && res != CURLE_WRITE_ERROR)//CURLE_ABORTED_BY_CALLBACK
	{
		/* Check for errors */
		if (res != CURLE_OK)
		{
			reply_ = new QAQNetworkReply;
		}
		else
		{
			reply_ = new QAQNetworkReply;
			reply_->SetData((char*)result_.c_str());
			reply_->SetLength(result_.size());
			reply_->SetError(REPLY_NO_ERROR);
		}

		if (data_cb_)
		{
			data_cb_(reply_, user_);
		}
		else if (inter_face_)
		{
			inter_face_->OnDataReply(reply_);
		}
	}
	is_running_ = false;
}

int QAQNetworkImpl::OnProgress(double t, double d)
{
	if (pro_cb_)
		pro_cb_(d, t, user_);

	else if (inter_face_)
	{
		inter_face_->OnDataProgress(t, d);
	}

	return 0;
}

void QAQNetworkImpl::SetShareHandle(CURL *curl_handle)
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

size_t QAQNetworkImpl::WriteMemoryCallback(void *buffer, size_t size, size_t count, void * stream)
{
	QAQNetworkImpl* pStream = static_cast<QAQNetworkImpl *>(stream);

	if (pStream)
	{
		if (pStream->is_cancel_)
		{
			return 0;
		}
		pStream->result_.append((char *)buffer, size * count);
		return size * count;
	}
	return 0;
};


void QAQNetworkImpl::CleanInterface()
{
	inter_face_ = nullptr;
}

int QAQNetworkImpl::ProgressCallback(char *user,
	double t, /* dltotal */
	double d, /* dlnow */
	double ultotal,
	double ulnow)
{
	QAQNetworkImpl* imp = (QAQNetworkImpl*)user;
	if (imp)
	{
		return imp->OnProgress(t, d);
	}
	return 0;
}