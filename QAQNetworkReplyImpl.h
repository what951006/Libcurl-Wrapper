#pragma once
#include "QAQNetworkReply.h"
class QAQNetworkReplyImpl:public QAQNetworkReply
{
public:
	QAQNetworkReplyImpl();
	virtual ~QAQNetworkReplyImpl();

	virtual void* GetData() override;


	virtual int GetLength() override;


	virtual QAQNetworkReplyError GetError() override;

};

