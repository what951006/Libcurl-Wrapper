#pragma once

enum QAQNetworkReplyError
{
	REPLY_INIT,
	REPLY_NO_ERROR,

};


class QAQNetworkReply
{
public:
	QAQNetworkReply();

	void FreeReply();

	virtual void* GetData()
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

	virtual void SetData(void *data) {
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
	virtual ~QAQNetworkReply() {}

	QAQNetworkReplyError error_;
	void *data_;
	int len_;
};
//
//QAQNETWORK_LIB  QAQNetworkReply* CreateReply();