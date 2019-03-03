#include "stdafx.h"
#include "QAQNetworkImpl.h"
#include "QAQNetworkReq.h"
#include "QAQNetworkReply.h"


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
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void*)&respond_);
	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl_);

	/* Check for errors */
	if (res != CURLE_OK)
	{
		QAQNetworkReply *reply = new QAQNetworkReply;
		return reply;
	}
	else
	{
		QAQNetworkReply *reply = new QAQNetworkReply;
		reply->SetData((void*)respond_.c_str());
		reply->SetLength(respond_.size());
		reply->SetError(REPLY_NO_ERROR);
		return reply;
	}
}

void QAQNetworkImpl::ASyncGet(QAQNetworkReq *, void *user, DataCallBack)
{
	//throw std::logic_error("The method or operation is not implemented.");
}
