#pragma once
#include "HttpStartUp.h"
class TestC
{
public:
	TestC();
	~TestC();

	void DoStart();

	void OnStart(bool, StartupStruct*);

	HttpStartup *start_= nullptr;
};

