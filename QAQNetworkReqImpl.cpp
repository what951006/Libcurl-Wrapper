#include "stdafx.h"
#include "QAQNetworkReqImpl.h"



QAQNetworkReqImpl::QAQNetworkReqImpl()
{
	
}


QAQNetworkReqImpl::~QAQNetworkReqImpl()
{
	
}

void QAQNetworkReqImpl::SetHeader(const char * header )
{
	headers_.emplace_back(header);
}

void QAQNetworkReqImpl::SetUrl(const char * url)
{
	url_ = url;
}

const char * QAQNetworkReqImpl::GetHeader(int index)
{
	if (index >= headers_.size())
	{
		return nullptr;
	}
	return headers_.at(index).c_str();
}

int QAQNetworkReqImpl::GetHeaderCount()
{
	return headers_.size();
}

char * QAQNetworkReqImpl::GetUrl() const
{
	return (char*)url_.c_str();
}