#include "stdafx.h"
#include "QAQNetwork.h"
#include "QAQNetworkFactory.h"

QAQNetworkFactory factory_;


void CreateNetwork(QAQNetworkReq** req, QAQNetwork**net)
{
	factory_.CreateNetwork(req, net);
}

void DeleteNetwork(QAQNetworkReq** req, QAQNetwork** net)
{
	factory_.DeleteNetwork(*req, *net);
}
