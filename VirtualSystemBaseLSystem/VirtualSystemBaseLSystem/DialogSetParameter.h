#pragma once
#include "Expression.h"

// DialogSetParameter �Ի���

class DialogSetParameter : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSetParameter)

public:
	DialogSetParameter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogSetParameter();

	void readParameter();
	void saveParameter();

	Parameter parameter;
	CString growthCycleList;		//�洢������������
	// �Ի�������
	enum { IDD = IDD_DIALOG_SetParameter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSetbetadistribution();
	afx_msg void OnBnClickedButtonSetgrowthcycle();
};
