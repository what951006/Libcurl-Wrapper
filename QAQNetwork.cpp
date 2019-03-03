#include "stdafx.h"
#include "QAQNetwork.h"
#include "QAQNetworkImpl.h"

QAQNetwork* CreateQAQNetwork()
{
	return new QAQNetworkImpl();
}
