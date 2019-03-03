#pragma once
#include "QAQNetwork.h"
#include <string>


#include <curl/curl.h>
class QAQNetworkImpl :
	public QAQNetwork
{
public:
	QAQNetworkImpl();
	~QAQNetworkImpl();

	virtual QAQNetworkReply* SyncGet(QAQNetworkReq * req) override;


	virtual void ASyncGet(QAQNetworkReq *, void *user, DataCallBack) override;


	CURL *curl_;
	CURLcode res;
	std::string respond_;
};

