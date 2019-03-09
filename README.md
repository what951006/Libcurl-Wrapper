## BRIEF
this is a wrappered project which based on libcurl,supported http,https,user can invoke the API by synchronized way or asynchronous way which depends on your needing.

## BUILD
the curl libs were builded by VS2015 and so openssl was
just run TestCurl.sln ，U can see the all source code
## HOW TO USE IT
### 1、used by synchronized way
example:
```C++
	QAQNetwork *network;
	QAQNetworkReq *request;
	CreateNetwork(&request, &network);
	request->SetUrl("https://www.baidu.com");
	QAQNetworkReply*reply = network->SyncGet(request);
	if(reply->GetError()==REPLY_NO_ERROR)
	{
		printf(reply->GetData());
	}
	DeleteNetwork(&request, &network);
```

### 2、used by asynchronous way
#### example
```C++
#include <QAQNetwork.h>
class HttpStartUp:public QAQNetworkInterface
{
public:
	HttpStartUp()
	{
		CreateNetwork(&request, &network);
	}
	~HttpStartUp()
	{
		DeleteNetwork(&request, &network);
	}

	void Request()
	{
		request->SetUrl("https://www.baidu.com");
		network->ASyncGet2(request, this);
	}

	virtual void OnDataReply(QAQNetworkReply* reply)
	{
		if(reply->GetError()==REPLY_NO_ERROR)
		{
			printf(reply->GetData());
		}
	}


	virtual void OnDataProgress(double total, double now) override;

	QAQNetwork *network;
	QAQNetworkReq *request;
};

int main
{
	HttpStartUp hp;
	hp.Request();
	system("pause");
	return 0;
}

```