#include "stdafx.h"
#include "QAQNetworkImpl.h"



void CreateNetwork(QAQNetwork**net, QAQNetwork::Delegate *gate)
{
	*net = new QAQNetworkImpl;
	(*net)->setDelegate(gate);
}

void DeleteNetwork(QAQNetwork** net)
{
	delete *net;
	net = nullptr;
}
