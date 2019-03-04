#pragma once

#ifndef QAQNETWORK_STATIC
	#ifdef QAQNETWORK_EXPORT
	#define QAQNETWORK_LIB _declspec(dllexport)
	#else
	#define QAQNETWORK_LIB _declspec(dllimport)
	#endif
#else
	#define QAQNETWORK_LIB
#endif



class QAQNetworkReq;
class QAQNetworkReply;
using DataCallBack = void(*)(QAQNetworkReply*, void*user);
class QAQNetwork
{
public:
	QAQNetwork() {};
	virtual ~QAQNetwork() {};


	virtual QAQNetworkReply* SyncGet(QAQNetworkReq * req) = 0;

	virtual void ASyncGet(QAQNetworkReq *,void *user, DataCallBack) = 0;

//	virtual ASyncPost(QAQNetworkReq *, void *user,);

	virtual void DeleteReply()=0;
protected:
	QAQNetworkReply* reply_;
	QAQNetworkReq* req_;
};

QAQNETWORK_LIB QAQNetwork* CreateNetwork();

QAQNETWORK_LIB void DeleteNetwork(QAQNetwork*);

QAQNETWORK_LIB QAQNetworkReq* CreateRequest();

QAQNETWORK_LIB void DeleteRequest(QAQNetworkReq*);