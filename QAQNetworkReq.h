#pragma once

struct HttpHeader
{
	char *header_key;
	char *header_value;
};

class QAQNetworkReq
{
public:
	QAQNetworkReq() {};

	virtual ~QAQNetworkReq() {};

	virtual void SetHeader(HttpHeader header) = 0;

	virtual void SetUrl(const char * url)=0;

	virtual HttpHeader* GetHeader() = 0;
	
	virtual int GetHeaderCount() = 0;

	virtual char * GetUrl() const = 0;

};