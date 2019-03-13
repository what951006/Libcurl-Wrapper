#pragma once
#include <thread>
#include <atomic>

#include "QAQNetwork.h"
#include "ThreadSafe_Queue.h"

class QAQNetworkFactory
{
public:
	QAQNetworkFactory();
	~QAQNetworkFactory();

	void CreateNetwork(QAQNetworkReq**, QAQNetwork**);
	
	void DeleteNetwork(QAQNetworkReq*, QAQNetwork*);

	void FactoryThread();


	ThreadSafe_Queue<QAQNetwork*> que_;
	std::thread thread_;
	atomic_bool quit_;
};

