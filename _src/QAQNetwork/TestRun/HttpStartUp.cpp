#include "stdafx.h"
#include "HttpStartup.h"


HttpStartup::HttpStartup()
{
	CreateNetwork(&network_,this);
}

HttpStartup::~HttpStartup()
{
	DeleteNetwork(&network_);
}

void HttpStartup::ASyncPost(const std::string & url, const std::string &post_data)
{
	// for the first time ,u neet to stop
	network_->stopAsync();
	network_->getRequest()->setUrl(u8"http://obs.qaqgame.com/ÄãºÃ--ÈÕ±¾.mp4");
	network_->syncGet();
}



void HttpStartup::onReply(QAQNetwork *, QAQNetworkReply*reply)
{
	if(reply->getError() == QAQNetworkReplyError::REPLY_NO_ERROR)
		printf(reply->getData());
	else 
		printf("Reply Error\n");
}

void HttpStartup::onDataProgress(QAQNetwork *, double total, double now)
{
	
}

bool HttpStartup::onTrunk(QAQNetwork *, char *data, int len)
{
	printf("onTrunk\n");
	return true;
}
