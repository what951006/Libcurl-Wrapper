#include "stdafx.h"
#include "QAQNetworkReply.h"

QAQNetworkReply::QAQNetworkReply()
	:len_(-1)
	, error_(REPLY_INIT)
	, data_(nullptr)
{
}


void QAQNetworkReply::FreeReply()
{
	delete this;
}
