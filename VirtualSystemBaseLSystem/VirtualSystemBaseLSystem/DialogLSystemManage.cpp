// DialogLSystemManage.cpp : 实现文件
//
#include "stdafx.h"
#include "DialogLSystemManage.h"
#include "Controller.h"
#include <fstream>
#include <Windows.h>

// DialogLSystemManage

IMPLEMENT_DYNCREATE(DialogLSystemManage, CFormView)

DialogLSystemManage::DialogLSystemManage()
	: CFormView(DialogLSystemManage::IDD)
{
	string s;
	string temp="\r";
	int pos;

	ifstream in("data/L_sequence.txt", ios::in);  
	istreambuf_iterator<char> beg(in), end;  
	s=s.assign(beg, end);//或者string st;st.assign(beg,end); 
	
	//加入temp，实现换行
	if (s.find("\r")==s.npos)
	{
		pos=s.find("\n");
		while (pos!=s.npos)
		{
			s.insert(pos,temp);
			pos+=2;
			pos=s.find("\n",pos);
		}
	}

	lSystemContent=s.c_str();

	in.close(); 

	iteratorTimes=0;
	remindEnergy=0;
	requireEnergy=0;
	generateEnergy=0;
	avaliableEnergy=0;
	segmentAmount=0;
	leafAmount=0;

	iteratorNow=0;
}

DialogLSystemManage::~DialogLSystemManage()
{
}

void DialogLSystemManage::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT1,lSystemContent);
	DDX_Text(pDX,IDC_STATIC8,iteratorTimes);
	DDX_Text(pDX,IDC_STATIC11,generateEnergy);
	DDX_Text(pDX,IDC_STATIC12,requireEnergy);
	DDX_Text(pDX,IDC_STATIC14,remindEnergy);
	DDX_Text(pDX,IDC_STATIC9,segmentAmount);
	DDX_Text(pDX,IDC_STATIC10,leafAmount);
	DDX_Text(pDX,IDC_STATIC15,avaliableEnergy);
}

BEGIN_MESSAGE_MAP(DialogLSystemManage, CFormView)
	ON_BN_CLICKED(IDOK, &DialogLSystemManage::OnBnClickedOk)
	ON_BN_CLICKED(IDGrowing, &DialogLSystemManage::OnBnClickedGrowing)
	ON_BN_CLICKED(IDReset, &DialogLSystemManage::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogLSystemManage::OnBnClickedButton1)
END_MESSAGE_MAP()


// DialogLSystemManage 诊断

#ifdef _DEBUG
void DialogLSystemManage::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogLSystemManage::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


//void DialogLSystemManage::readBasicUnitInformation()
//{
//
//	/*
//	BasicUnitInfomatin.txt文件结构
//
//	Iterator Times
//
//	Generate Energy
//	
//	Require Energy
//	
//	Remind Energy
//	
//	Segments Amount
//
//	Leaves Amount
//	*/
//
//	ifstream readFile("Data/BasicUnitInfomation.txt");
//
//	if(readFile.is_open())
//	{
//		readFile>>generateEnergy;
//		readFile>>generateEnergy;
//		readFile>>requireEnergy;
//		readFile>>remindEnergy;
//		readFile>>segmentAmount;
//		readFile>>leafAmount;
//		
//	}
//	readFile.close();
//}

// DialogLSystemManage 消息处理程序


void DialogLSystemManage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	lSystemContent.GetString();

	CStdioFile file;	
	file.Open(_T("Data/L_sequence.txt"),CFile::modeWrite|CFile::typeText);
	file.SetLength(0);
	file.WriteString(lSystemContent);
	file.Close();

	//readBasicUnitInformation();

	UpdateData(FALSE);
}

void DialogLSystemManage::OnBnClickedGrowing()
{
	// TODO: 在此添加控件通知处理程序代码
	iteratorTimes++;
	if (iteratorTimes!=0)
		GetDlgItem(IDGrowing)->SetWindowText(_T("Next Iterator Times"));

	/*ofstream writeFile("Data/IteratorTimes.txt");

	writeFile<<iteratorTimes<<"\n";
	
	writeFile.close();*/

	controller.setItratorTime(iteratorTimes);
	controller.run();

	generateEnergy=controller.generateEnergy;
	requireEnergy=controller.requireEnergy;
	remindEnergy=controller.remindEnergy;
	segmentAmount=controller.segmentAmount;
	leafAmount=controller.leafAmount;
	avaliableEnergy=controller.avaliableEnergy;
	//Sleep(3000);

	//readBasicUnitInformation();
	UpdateData(false);
}

//清空
void DialogLSystemManage::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	ofstream writeFile("Data/IteratorTimes.txt");

	writeFile<<0<<"\n";
	
	writeFile.close();

	ofstream writeFile1("Data/BasicUnitInfomation.txt");

	if(writeFile1.is_open())
	{
		for(int i=0;i<6;i++)
			writeFile1<<0<<"\n";
	}
	
	writeFile1.close();

	//清空文件
	ofstream out("Data/writeBasicUnitListWithTreeDraw.txt");
	out.close();
	ofstream out1("Data/writeEnergyDetail.txt");
	out1.close();
	ofstream out2("Data/writeEnergySatatistic.txt");
	out1.close();
	
	GetDlgItem(IDGrowing)->SetWindowText(_T("Growing"));

	iteratorTimes=0;
	generateEnergy=0;
	requireEnergy=0;
	remindEnergy=0;
	segmentAmount=0;
	leafAmount=0;
	avaliableEnergy=0;

	controller.reset();

	controller.readParameter();

	UpdateData(false);
}

//Check L-System
void DialogLSystemManage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog dlg( IDD_DIALOG_LSystemCheck) ;
    dlg.DoModal(); 
}
