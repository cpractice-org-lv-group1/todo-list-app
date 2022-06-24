#pragma once
#ifndef _WSA_LOADER_H__INCLUDED
#define _WSA_LOADER_H__INCLUDED

static class WSA_loader
{
public:
	WSA_loader();
	~WSA_loader();
	static void Load();
	static void Clean();
	};
#endif

