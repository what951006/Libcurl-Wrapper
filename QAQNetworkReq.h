#pragma once


#ifdef QAQNETWORK_EXPORT
#define QAQNETWORK_LIB _declspec(dllexport)
#else
#define QAQNETWORK_LIB _declspec(dllimport)
#endif

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

QAQNETWORK_LIB QAQNetworkReq* CreateRequest();

QAQNETWORK_LIB void DeleteRequest(QAQNetworkReq*);