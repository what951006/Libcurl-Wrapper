#pragma once
#include "QAQNetwork.h"

#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <curl/curl.h>



class QAQNetworkImpl :
	public QAQNetwork
{
public:
	QAQNetworkImpl();
	~QAQNetworkImpl();

	virtual QAQNetworkReply* SyncGet(QAQNetworkReq * req, void *user = nullptr, DataCallBack data_cb = nullptr, DataProgress pro_cb= nullptr) override;

	virtual QAQNetworkReply* SyncPost(QAQNetworkReq * req, const char*post_data, void *user = nullptr, DataCallBack data_cb = nullptr, DataProgress pro_cb = nullptr) override;

	virtual void ASyncGet(QAQNetworkReq *, void *user, DataCallBack, DataProgress=nullptr) override;

	virtual void ASyncPost(QAQNetworkReq *, const char*post_data,void *user, DataCallBack, DataProgress = nullptr) override;

	virtual void ASyncGet2(QAQNetworkReq *, QAQNetworkInterface *) override;

	virtual void ASyncPost2(QAQNetworkReq *, const char*post_data, QAQNetworkInterface *) override;

	virtual const char * GetMemPtr() override;

	virtual int GetMemLen() override;
protected:
	virtual void Stop() override;

	virtual void CleanInterface() override;

	void DeleteReply();

	void QAQNetworkImpl::SetShareHandle(CURL *curl_handle);

	void ASyncGetThread();

	void ASyncPostThread();

	int OnProgress(double t,double d);

	int OnWrite(const char *data ,int len);

	static int ProgressCallback(char *user,
		double t, /* dltotal */
		double d, /* dlnow */
		double ultotal,
		double ulnow);

	static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);


	std::mutex mutex_;
	std::atomic_bool is_cancel_;
	std::atomic_bool is_running_;
	std::thread async_thread_;

	//interface
	QAQNetworkInterface * inter_face_;
	void * user_;
	DataCallBack data_cb_;
	DataProgress pro_cb_;
	//////////////////////////////////////////////////////////////////////////

	
	CURL *curl_;
	struct curl_slist *headers;
	std::string post_data_;
	QAQNetworkReply *reply_;
	QAQNetworkReq * req_;
	std::string result_;



};

