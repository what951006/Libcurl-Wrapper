#pragma once

#include <vector>
#include <string>
#include "QAQNetwork.h"


#define  MAX_HEADER 16
class QAQNetworkReqImpl :
	public QAQNetworkReq
{
	friend class QAQNetwork;
public:
	QAQNetworkReqImpl();
	virtual ~QAQNetworkReqImpl();


	virtual void SetHeader(const char * header) override;


	virtual void SetUrl(const char * url) override;



protected:
	virtual const char * GetHeader(int ) override;


	virtual int GetHeaderCount() override;


	virtual char * GetUrl() const override;
private:
	std::vector<std::string >	headers_;

	std::string url_;
};

