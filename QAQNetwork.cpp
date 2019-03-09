#include "stdafx.h"
#include "QAQNetwork.h"
#include "QAQNetworkImpl.h"
#include "QAQNetworkReqImpl.h"



void CreateNetwork(QAQNetworkReq** req, QAQNetwork**net)
{
	*req = new QAQNetworkReqImpl;
	*net = new QAQNetworkImpl;
}

void DeleteNetwork(QAQNetworkReq** req, QAQNetwork** net)
{
	delete *req;
	delete *net;
	req = nullptr;
	net = nullptr;
}
