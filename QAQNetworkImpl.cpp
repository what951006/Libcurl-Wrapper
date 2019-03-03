#include "stdafx.h"
#include "QAQNetworkImpl.h"
#include "QAQNetworkReq.h"
#include "QAQNetworkReply.h"



size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory)
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}


QAQNetworkImpl::QAQNetworkImpl()
{
	curl_ = curl_easy_init();
}


QAQNetworkImpl::~QAQNetworkImpl()
{
	curl_easy_cleanup(curl_);
}

QAQNetworkReply* QAQNetworkImpl::SyncGet(QAQNetworkReq * req)
{
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, true);
	curl_easy_setopt(curl_, CURLOPT_URL, req->GetUrl());

	/* example.com is redirected, so we tell libcurl to follow redirection */
	curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void*)&respond_);

	curl_easy_setopt(curl_, CURLOPT_VERBOSE, 0L);
	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl_);

	/* Check for errors */
	if (res != CURLE_OK)
	{
		reply_ = new QAQNetworkReply;
		return reply_;
	}
	else
	{
		reply_ = new QAQNetworkReply;
		reply_->SetData(respond_.memory);
		reply_->SetLength(respond_.size);
		reply_->SetError(REPLY_NO_ERROR);
		return reply_;
	}
}

void QAQNetworkImpl::ASyncGet(QAQNetworkReq *, void *user, DataCallBack)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void QAQNetworkImpl::DeleteReply()
{
	if (reply_)
	{
		delete reply_;
		reply_ = nullptr;
	}
}
