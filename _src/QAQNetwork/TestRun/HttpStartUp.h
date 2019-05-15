#pragma once
#include <string>


#include "..\QAQNetwork.h"


class HttpStartup:public QAQNetwork::Delegate
{
public:
	HttpStartup();
	~HttpStartup();

	void ASyncPost(const std::string & url ,const std::string &post_data);

	virtual void onReply(QAQNetwork *, QAQNetworkReply*) override;

	virtual void onDataProgress(QAQNetwork *, double total, double now) override;

	QAQNetwork * network_;

	virtual bool onTrunk(QAQNetwork *, char *data, int len) override;

};

