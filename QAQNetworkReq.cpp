#include "stdafx.h"
#include "QAQNetworkReq.h"
#include "QAQNetworkReqImpl.h"



QAQNetworkReq* CreateRequest()
{
	return new QAQNetworkReqImpl;
}

void DeleteNetworkReq(QAQNetworkReq*req)
{
	delete req;
}
