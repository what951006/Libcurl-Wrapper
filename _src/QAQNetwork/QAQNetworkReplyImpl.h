#pragma once
#include "QAQNetwork.h"

#include <string>
class QAQNetworkReplyImpl :public QAQNetworkReply
{
	friend class QAQNetworkImpl;
public:
	void reset();

	virtual const char* getData() override;

	virtual unsigned int getLength() override;

	virtual QAQNetworkReplyError getError() override;

protected:

	void setError(QAQNetworkReplyError error);

	std::string result_;
	QAQNetworkReplyError error_= REPLY_INIT;
};

