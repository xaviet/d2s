
// d2s.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cd2sApp: 
// �йش����ʵ�֣������ d2s.cpp
//

class Cd2sApp : public CWinApp
{
public:
	Cd2sApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cd2sApp theApp;
