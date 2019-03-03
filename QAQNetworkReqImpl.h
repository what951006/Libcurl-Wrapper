#pragma once

#include <string>

#include "QAQNetworkReq.h"
class QAQNetworkReqImpl :
	public QAQNetworkReq
{
	friend class QAQNetwork;
public:
	QAQNetworkReqImpl();
	virtual ~QAQNetworkReqImpl();


	virtual void SetHeader(HttpHeader header) override;


	virtual void SetUrl(const char * url) override;



protected:
	virtual HttpHeader* GetHeader() override;


	virtual int GetHeaderCount() override;


	virtual char * GetUrl() const override;
private:


	HttpHeader *header_;
	int count_;
	std::string url_;
};

