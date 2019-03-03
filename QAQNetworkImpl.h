#pragma once
#include "QAQNetwork.h"
#include <string>


#include <curl/curl.h>

struct MemoryStruct
{
	char *memory;
	size_t size;
	MemoryStruct()
	{
		memory = (char *)malloc(1);
		size = 0;
	}
	~MemoryStruct()
	{
		free(memory);
		memory = NULL;
		size = 0;
	}
};

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
	MemoryStruct respond_;
	QAQNetworkReply *reply_;

	virtual void DeleteReply() override;

};

