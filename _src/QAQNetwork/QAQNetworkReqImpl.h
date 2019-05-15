#pragma once

#include <vector>
#include <string>
#include "QAQNetwork.h"


class QAQNetworkReqImpl :public QAQNetworkReq
{
	friend class QAQNetworkImpl;
public:
	void reset();

	virtual void setHeader(const char * header) override;

	virtual void setUrl(const char * url) override;

	virtual void setPostData(const char *post_data) override;

protected:
	virtual const char * getHeader(int ) override;

	virtual int getHeaderCount() override;

	virtual const char * getUrl() const override;
private:
	std::vector<std::string>	headers_;

	std::string url_;
	std::string post_data_;
};

