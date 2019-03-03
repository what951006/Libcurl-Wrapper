
## HOW TO USE IT
1、synchronize way

```C++
	QAQNetwork *network =  CreateNetwork();

	QAQNetworkReq *request =  CreateRequest();

	request->SetUrl("https://www.baidu.com");

	QAQNetworkReply*reply = network->SyncGet(request);


	printf(reply->GetData());



	DeleteRequest(request);
	DeleteNetwork(network);
```

