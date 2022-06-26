#include "WSA_loader.h"
#include "config.h"

WSA_loader::WSA_loader()
{
}

WSA_loader::~WSA_loader()
{
}

void WSA_loader::Load()
{
	WSADATA m_wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0) {
		Logger("{WSA_loader.cpp//WSA_loader::Load} Failed. Error Code: " + WSAGetLastError());
	}
}

void WSA_loader::Clean()
{
	WSACleanup();
	Logger("{WSA_loader.cpp//WSA_loader::Clean} Call clean function WSACleanup ");
}
