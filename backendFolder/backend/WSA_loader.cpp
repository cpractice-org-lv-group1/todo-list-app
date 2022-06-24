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
		printf("Failed. Error Code: %d", WSAGetLastError());
	}
}

void WSA_loader::Clean()
{
	WSACleanup();
}
