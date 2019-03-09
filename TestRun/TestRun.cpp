// TestRun.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <thread>
#include "../QAQNetwork.h"
#include "HttpStartUp.h"
//
//void DataProgressCB(double now, double total, void*user)
//{
//	printf("%f,%f percent:%f\n",now,total,now/total);
//}
//
//void  DataCB(QAQNetworkReply* reply, void*user)
//{
//	if (reply->GetError() == REPLY_NO_ERROR)
//	{
//		printf(reply->GetData());
//	}
//
//}

int main()
{
//	for (int i = 0; i < 1; ++i)
//	{
//		QAQNetwork *network = CreateNetwork();
//
//		QAQNetworkReq *request = CreateRequest();
//
//		request->SetUrl("http://obs.qaqgame.com/speed/download/QAQGAME_INSTALL_V3.1.2.79_official.exe");
//
//		//http://iso.mirrors.ustc.edu.cn/qtproject/archive/qt/5.12/5.12.1/qt-opensource-mac-x64-5.12.1.dmg
////			QAQNetworkReply*reply = network->SyncGet(request);
//
//
//		network->ASyncGet(request, nullptr, DataCB, DataProgressCB);
//
//
//		DeleteLater(network, request);
//
//		//Sleep(100);
//	}

	//HttpStartUp startup[2009];
	//for (int i = 0; i < 2009; ++i)
	//{
	//	startup[i].Request();
	//}

	//HttpStartUp *startup = new HttpStartUp[2];
	///*for (int i = 0; i < 1; ++i)
	//{*/
	//startup[0].Request();
	//
	//startup[1].Request();
	////}

	////for (int i = 0; i < 1; ++i)
	//
	//delete startup;

	//for (int i = 0; i < 100; ++i)
	//{
	//	HttpStartUp startup;
	//	startup.Request();

	//	
	//	Sleep(1000);
	//}
	//
	HttpStartUp startup;
	startup.Request();

	//HttpStartUp startup2;
	//startup2.Request();

	//std::vector<int*> thread_vec_{ new int(0),new int(1),new int(2),new int(3), new int(4) };
	//for (int i = 0; i < thread_vec_.size(); ++i)
	//{
	//	if (i == 1)
	//	{
	//		delete thread_vec_[i];
	//		thread_vec_[i] = thread_vec_.back();
	//		thread_vec_.pop_back();
	//	}
	//}

	//for (int i = 0; i < thread_vec_.size(); ++i)
	//{
	//	printf("%d\n", *thread_vec_[i]);
	//}

	//Sleep(10000000);

	system("pause");
	//DeleteRequest(request);
	//DeleteNetwork(network);
    return 0;
}

