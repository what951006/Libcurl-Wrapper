#include "stdafx.h"
#include "QAQNetwork.h"
#include "QAQNetworkImpl.h"

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

