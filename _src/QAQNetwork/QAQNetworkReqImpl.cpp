#include "stdafx.h"
#include "QAQNetworkReqImpl.h"




void QAQNetworkReqImpl::setHeader(const char * header )
{
	headers_.emplace_back(header);
}

void QAQNetworkReqImpl::setUrl(const char * url)
{
	url_ = url;
}

void QAQNetworkReqImpl::reset()
{
	headers_.swap(std::vector<std::string>());
	url_ = "";
	post_data_ = "";
}

void QAQNetworkReqImpl::setPostData(const char * post_data)
{
	post_data_ = post_data;
}

const char * QAQNetworkReqImpl::getHeader(int index)
{
	if (index >= headers_.size())
	{
		return nullptr;
	}
	return headers_.at(index).c_str();
}

int QAQNetworkReqImpl::getHeaderCount()
{
	return headers_.size();
}

const char * QAQNetworkReqImpl::getUrl() const
{
	return url_.c_str();
}