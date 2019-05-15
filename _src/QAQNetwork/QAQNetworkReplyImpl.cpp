#include "stdafx.h"
#include "QAQNetworkReplyImpl.h"


void QAQNetworkReplyImpl::reset()
{
	error_ = REPLY_INIT;
	result_ = "";
}

const char* QAQNetworkReplyImpl::getData()
{
	return result_.c_str();
}

unsigned int QAQNetworkReplyImpl::getLength()
{
	return result_.size();
}

QAQNetworkReplyError QAQNetworkReplyImpl::getError()
{
	return error_;
}

void QAQNetworkReplyImpl::setError(QAQNetworkReplyError error)
{
	error_ = error;
}
