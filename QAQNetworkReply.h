#pragma once

enum QAQNetworkReplyError
{
	REPLY_INIT,
	REPLY_NO_ERROR,

};


class QAQNetworkReply
{
public:
	QAQNetworkReply()
	: len_(-1)
	, error_(REPLY_INIT)
	, data_(nullptr)
	{}

	virtual ~QAQNetworkReply() {}


	virtual char* GetData()
	{
		return data_;
	}

	virtual int GetLength()
	{
		return len_;
	}
	virtual QAQNetworkReplyError GetError()
	{
		return error_;
	}

	virtual void SetData(char *data) {
		data_ = data;
	}

	virtual void SetLength(int len)
	{
		len_ = len;
	}

	virtual void SetError(QAQNetworkReplyError error)
	{
		error_ = error;
	}

private:
	

	QAQNetworkReplyError error_;
	char *data_;
	int len_;
};
//
//QAQNETWORK_LIB  QAQNetworkReply* CreateReply();