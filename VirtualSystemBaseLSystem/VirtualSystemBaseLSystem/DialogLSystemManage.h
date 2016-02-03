#pragma once

#include "VirtualSystemBaseLSystem.h"
#include "Controller.h"

using namespace std;

// DialogLSystemManage ������ͼ

class DialogLSystemManage : public CFormView
{
	DECLARE_DYNCREATE(DialogLSystemManage)

protected:
	DialogLSystemManage();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~DialogLSystemManage();
	void readBasicUnitInformation();

public:
	enum { IDD = IDD_DIALOG_Interactions };
	CString lSystemContent;		//����Lϵͳ����
	
	int iteratorTimes;
	double remindEnergy;
	double requireEnergy;
	double generateEnergy;
	double avaliableEnergy;

	int segmentAmount;
	int leafAmount;

	int iteratorNow;

	Controller controller;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedGrowing();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedButton1();
};


