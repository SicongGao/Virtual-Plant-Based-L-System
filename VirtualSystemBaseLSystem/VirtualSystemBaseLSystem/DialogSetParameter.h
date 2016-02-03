#pragma once
#include "Expression.h"

// DialogSetParameter 对话框

class DialogSetParameter : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSetParameter)

public:
	DialogSetParameter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogSetParameter();

	void readParameter();
	void saveParameter();

	Parameter parameter;
	CString growthCycleList;		//存储生长周期序列
	// 对话框数据
	enum { IDD = IDD_DIALOG_SetParameter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSetbetadistribution();
	afx_msg void OnBnClickedButtonSetgrowthcycle();
};
