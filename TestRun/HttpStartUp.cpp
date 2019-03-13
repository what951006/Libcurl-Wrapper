#include "HttpStartUp.h"
#include <stdio.h>



HttpStartUp::HttpStartUp()
{
	CreateNetwork(&request, &network);
}


HttpStartUp::~HttpStartUp()
{
	DeleteNetwork(&request, &network);
}

void HttpStartUp::Request()
{


	request->SetUrl("http://iso.mirrors.ustc.edu.cn/qtproject/archive/qt/5.12/5.12.1/qt-opensource-mac-x64-5.12.1.dmg");

	////http://obs.qaqgame.com/speed/download/QAQGAME_INSTALL_V3.1.2.79_official.exe
	////http://iso.mirrors.ustc.edu.cn/qtproject/archive/qt/5.12/5.12.1/qt-opensource-mac-x64-5.12.1.dmg
	////			QAQNetworkReply*reply = network->SyncGet(request);
	////

	//network->ASyncPost2(request,"channel_code=&mac=00CFE045F37A&vc=7840daf4672d52c602678df9d82a4d26" ,this);
	

	//request->SetUrl("http://obs.qaqgame.com/speed/download/QAQGAME_INSTALL_V3.1.2.79_official.exe");

	network->ASyncGet2(request, this);
	
}

void HttpStartUp::OnDataReply(QAQNetworkReply*reply)
{
	// throw std::logic_error("The method or operation is not implemented.");
	printf("OnDataReply:success \n error code:%d ,Data: %s\n", reply->GetError() , reply->GetData());

	delete this;
}
//
void HttpStartUp::OnDataProgress(double total, double now)
{
	printf("%f,%f percent:%f\n", now, total, now / total);
	//throw std::logic_error("The method or operation is not implemented.");
}
