#include "TestC.h"
#include <windows.h>



TestC::TestC()
{
}


TestC::~TestC()
{
}

void TestC::DoStart()
{
	if (start_)
		delete start_;

	start_ = new HttpStartup;
	start_->func_ = std::bind(&TestC::OnStart, this, std::placeholders::_1, std::placeholders::_2);

	start_->ASyncPost("www.baidu.com","");
}

void TestC::OnStart(bool, StartupStruct*)
{
	static int i = 0;
	if (++i < 5)
		DoStart();
	else
		MessageBoxW(NULL, L"Hello", L"", NULL);
}
