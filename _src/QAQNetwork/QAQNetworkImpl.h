#pragma once
#include "QAQNetwork.h"

#include <string>
#include <thread>
#include <atomic>
#include <mutex>

#include "QAQNetworkReqImpl.h"
#include "QAQNetworkReplyImpl.h"



class QAQNetworkImpl :public QAQNetwork
{
public:
	QAQNetworkImpl();
	~QAQNetworkImpl();

	virtual QAQNetworkReq* getRequest() override;

	virtual QAQNetworkReply* getReply() override;

	virtual void syncGet() override;

	virtual void syncPost() override;

	virtual void asyncGet() override;

	virtual void asyncPost() override;

	virtual void stopAsync() override;

	virtual void setUserData(void *opaque) override;

	virtual void* getUserData() override;

	virtual void setDelegate(QAQNetwork::Delegate*dele) override;

protected:

	void reset();

	void asyncGetThread();

	void asyncPostThread();

	int onProgress(double t,double d);

	size_t onWrite(void* buffer, size_t size, size_t nmemb);

	static int ProgressCallback(char *user,
		double t, /* dltotal */
		double d, /* dlnow */
		double ultotal,
		double ulnow);

	static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);


	std::atomic_bool is_cancel_=false;
	std::thread async_thread_;

	//////////////////////////////////////////////////////////////////////////
	QAQNetworkReplyImpl reply_;
	QAQNetworkReqImpl req_;
	


	QAQNetwork::Delegate* delegate_ = nullptr;
	void * opaque_ = nullptr;
};

