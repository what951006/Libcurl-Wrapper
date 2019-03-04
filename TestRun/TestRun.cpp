// TestRun.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "../QAQNetwork.h"
#pragma comment(lib,"../Debug/TestCurl")

int main()
{
	QAQNetwork *network = CreateNetwork();

	QAQNetworkReq *request = CreateRequest();

	request->SetUrl("https://www.baidu.com");

	QAQNetworkReply*reply = network->SyncGet(request);


	if (reply->GetError() == REPLY_NO_ERROR)
	{
		printf(reply->GetData());
	}

	DeleteRequest(request);
	DeleteNetwork(network);
    return 0;
}

