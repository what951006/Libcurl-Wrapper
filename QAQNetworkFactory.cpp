#include "stdafx.h"
#include "QAQNetworkFactory.h"


#include "QAQNetworkImpl.h"
#include "QAQNetworkReqImpl.h"
QAQNetworkFactory::QAQNetworkFactory()
{
	quit_ = false;
	thread_ = std::move(std::thread(&QAQNetworkFactory::FactoryThread,this));
}


QAQNetworkFactory::~QAQNetworkFactory()
{
	quit_ = true;
	if (thread_.joinable())
	{
		thread_.join();
	}
}

void QAQNetworkFactory::CreateNetwork(QAQNetworkReq** req, QAQNetwork** net)
{
	*net = new QAQNetworkImpl;
	*req = new QAQNetworkReqImpl;
}

void QAQNetworkFactory::DeleteNetwork(QAQNetworkReq* req, QAQNetwork* net)
{
	if (req)
	{
		delete req;
		req = nullptr;
	}

	if (net)
	{
		net->CleanInterface();
		que_.push(net);
	}
}

void QAQNetworkFactory::FactoryThread()
{
	while (!quit_)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(20));
		QAQNetwork* net;
		if (que_.TryPop(net))
			delete net;
	}
}
