
// VirtualSystemBaseLSystem.h : VirtualSystemBaseLSystem Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CVirtualSystemBaseLSystemApp:
// �йش����ʵ�֣������ VirtualSystemBaseLSystem.cpp
//

class CVirtualSystemBaseLSystemApp : public CWinAppEx
{
public:
	CVirtualSystemBaseLSystemApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVirtualSystemBaseLSystemApp theApp;
