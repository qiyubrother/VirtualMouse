
// VirtualMouse.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVirtualMouseApp: 
// �йش����ʵ�֣������ VirtualMouse.cpp
//

class CVirtualMouseApp : public CWinApp
{
public:
	CVirtualMouseApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVirtualMouseApp theApp;