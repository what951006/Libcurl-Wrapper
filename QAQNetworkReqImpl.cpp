#include "stdafx.h"
#include "QAQNetworkReqImpl.h"

#define MAX_HEADER 16

QAQNetworkReqImpl::QAQNetworkReqImpl()
	:header_(nullptr)
	,count_(0)
{
	header_ = new HttpHeader[MAX_HEADER];
}


QAQNetworkReqImpl::~QAQNetworkReqImpl()
{
	delete[] header_;
}

void QAQNetworkReqImpl::SetHeader(HttpHeader header)
{
	header_[count_++] = header;

}

void QAQNetworkReqImpl::SetUrl(const char * url)
{
	url_ = url;
}

HttpHeader* QAQNetworkReqImpl::GetHeader()
{
	return header_;
}

int QAQNetworkReqImpl::GetHeaderCount()
{
	return count_;
}

char * QAQNetworkReqImpl::GetUrl() const
{
	return (char*)url_.c_str();
}