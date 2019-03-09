#pragma once

#include "../QAQNetwork.h"

class HttpStartUp:public QAQNetworkInterface
{
public:
	HttpStartUp();
	~HttpStartUp();

	void Request();

	virtual void OnDataReply(QAQNetworkReply*) override;


	virtual void OnDataProgress(double total, double now) override;

	QAQNetwork *network;
	QAQNetworkReq *request;
};

