#include "stdafx.h"
#include "QAQNetwork.h"
#include "QAQNetworkImpl.h"
#include "QAQNetworkReqImpl.h"

QAQNetwork* CreateNetwork()
{
	return new QAQNetworkImpl();
}

QAQNETWORK_LIB void DeleteNetwork(QAQNetwork* network)
{
	if (network)
	{
		network->DeleteReply();
		delete network;
	}
}

QAQNetworkReq* CreateRequest()
{
	return new QAQNetworkReqImpl;
}

void DeleteRequest(QAQNetworkReq*req)
{
	delete req;
}
