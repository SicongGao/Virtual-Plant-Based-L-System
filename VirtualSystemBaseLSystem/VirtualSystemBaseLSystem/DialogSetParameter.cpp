// DialogSetParameter.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtualSystemBaseLSystem.h"
#include "DialogSetParameter.h"
#include "afxdialogex.h"


// DialogSetParameter 对话框

IMPLEMENT_DYNAMIC(DialogSetParameter, CDialogEx)

DialogSetParameter::DialogSetParameter(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogSetParameter::IDD, pParent)
{
	CString temp;

	readParameter();

	growthCycleList="";
	for(int i=0;i<parameter.iteratorDay.size();i++)
	{
		temp.Format(_T("%d"),parameter.iteratorDay[i]);
		growthCycleList=growthCycleList+temp+_T(" ");
	}
}

DialogSetParameter::~DialogSetParameter()
{
}

void DialogSetParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX,IDC_EDIT1,parameter.leafMaxAge);
	DDX_Text(pDX,IDC_EDIT2,parameter.leafDensity);
	DDX_Text(pDX,IDC_EDIT3,parameter.leafThickness);
	DDX_Text(pDX,IDC_EDIT4,parameter.propotionOfHeightAndRadius);
	DDX_Text(pDX,IDC_EDIT5,parameter.segmentMaxAge);
	DDX_Text(pDX,IDC_EDIT6,parameter.segmentDensity);
	DDX_Text(pDX,IDC_EDIT7,parameter.leafA);
	DDX_Text(pDX,IDC_EDIT8,parameter.leafB);
	DDX_Text(pDX,IDC_EDIT9,parameter.segmentA);
	DDX_Text(pDX,IDC_EDIT10,parameter.segmentB);
	DDX_Text(pDX,IDC_EDIT11,parameter.leafAbsordAblity);
	DDX_Text(pDX,IDC_EDIT13,parameter.segmentAbsordAblity);
	DDX_Text(pDX,IDC_EDIT15,parameter.E);
	DDX_Text(pDX,IDC_EDIT16,parameter.resistanceToTranspiration);
	DDX_Text(pDX,IDC_EDIT17,parameter.lightExtinctionCoefficient);
	DDX_Text(pDX,IDC_EDIT18,parameter.propertyOfLeafAreaProjectionTotalAndLeafAreaTotal);
	DDX_Text(pDX,IDC_EDIT19,parameter.propotionOfLeafAndRoot);
	DDX_Text(pDX,IDC_EDIT20,growthCycleList); 
}


BEGIN_MESSAGE_MAP(DialogSetParameter, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogSetParameter::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DialogSetParameter::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SetBetaDistribution, &DialogSetParameter::OnBnClickedButtonSetbetadistribution)
	ON_BN_CLICKED(IDC_BUTTON_SetGrowthCycle, &DialogSetParameter::OnBnClickedButtonSetgrowthcycle)
END_MESSAGE_MAP()


//读取参数信息
void DialogSetParameter::readParameter()
{
	ifstream readFile("Data/parameter.txt");

	/*
	parameter.txt文件结构

	最大年龄
	leafMaxAge segmentMaxAge;

	Beta分布参数
	leafA leafB 
	segmentA segmentB

	汇强的参数
	leafAbsordAblity;
	segmentAbsordAblity;

	根与叶子的生物量需求量比例
	propotionOfLeafAndRoot;

	每个迭代周期的时间，第一个数字是个数，往后以此是各个周期的时间长度（天为单位）
	vector<int> iteratorDay;

	产生生物量生长潜力
	E

	叶面积每平方厘米蒸腾作用抵抗力
	resistanceToTranspiration

	光衰减系数
	lightExtinctionCoefficient

	植物的占地面积与植物叶片面积的比
	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal

	叶子的密度
	leafDensity

	叶子的厚度
	leafThickness

	形态参数，高度和半径的比
	propotionOfHeightAndRadius

	节间的密度
	segmentDensity
	*/

	if(readFile.is_open())
	{
		readFile>>parameter.leafMaxAge>>parameter.segmentMaxAge;
		//readFile>>parameter.leafAbsordAblity>>parameter.segmentAbsordAblity;
		readFile>>parameter.leafA>>parameter.leafB;
		readFile>>parameter.segmentA>>parameter.segmentB;
		readFile>>parameter.leafAbsordAblity;
		readFile>>parameter.segmentAbsordAblity;
		readFile>>parameter.propotionOfLeafAndRoot;
		
		int n,k;
		readFile>>n;
		for(int i=0;i<n;i++)
		{
			readFile>>k;
			parameter.iteratorDay.push_back(k);
		}

		readFile>>parameter.E;
		readFile>>parameter.resistanceToTranspiration;
		readFile>>parameter.lightExtinctionCoefficient;
		readFile>>parameter.propertyOfLeafAreaProjectionTotalAndLeafAreaTotal;
		readFile>>parameter.leafDensity;
		readFile>>parameter.leafThickness;
		readFile>>parameter.propotionOfHeightAndRadius;
		readFile>>parameter.segmentDensity;
	}
	readFile.close();
}

void DialogSetParameter::saveParameter()
{
	ofstream writeFile("Data/parameter.txt");

	/*
	parameter.txt文件结构

	最大年龄
	leafMaxAge segmentMaxAge;

	Beta分布参数
	leafA leafB 
	segmentA segmentB

	汇强的参数
	leafAbsordAblity;
	segmentAbsordAblity;

	根与叶子的生物量需求量比例
	propotionOfLeafAndRoot;

	每个迭代周期的时间，第一个数字是个数，往后以此是各个周期的时间长度（天为单位）
	vector<int> iteratorDay;

	产生生物量生长潜力
	E

	叶面积每平方厘米蒸腾作用抵抗力
	resistanceToTranspiration

	光衰减系数
	lightExtinctionCoefficient

	植物的占地面积与植物叶片面积的比
	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal

	叶子的密度
	leafDensity

	叶子的厚度
	leafThickness

	形态参数，高度和半径的比
	propotionOfHeightAndRadius

	节间的密度
	segmentDensity
	*/
	writeFile<<parameter.leafMaxAge<<" "<<parameter.segmentMaxAge<<"\n";
	writeFile<<parameter.leafA<<" "<<parameter.leafB<<"\n";
	writeFile<<parameter.segmentA<<" "<<parameter.segmentB<<"\n";
	writeFile<<parameter.leafAbsordAblity<<"\n";
	writeFile<<parameter.segmentAbsordAblity<<"\n";
	writeFile<<parameter.propotionOfLeafAndRoot<<"\n";

	writeFile<<parameter.iteratorDay.size()<<" ";

	for(int i=0;i<parameter.iteratorDay.size();i++)
		writeFile<<parameter.iteratorDay[i]<<" ";

	writeFile<<"\n";
	
	writeFile<<parameter.E<<"\n";
	writeFile<<parameter.resistanceToTranspiration<<"\n";
	writeFile<<parameter.lightExtinctionCoefficient<<"\n";
	writeFile<<parameter.propertyOfLeafAreaProjectionTotalAndLeafAreaTotal<<"\n";
	writeFile<<parameter.leafDensity<<"\n";
	writeFile<<parameter.leafThickness<<"\n";
	writeFile<<parameter.propotionOfHeightAndRadius<<"\n";
	writeFile<<parameter.segmentDensity<<"\n";


	writeFile.close();
}

// DialogSetParameter 消息处理程序
void DialogSetParameter::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	
	UpdateData(true);

	//把 growthCycleList的数据转换到parameter.iteratorDay
	vector<string> days;
	int pos;
	CString temp;

	parameter.iteratorDay.clear();

	pos=growthCycleList.Find(' ');
	while(pos>=0)
	{
		temp=growthCycleList.Left(pos);
		parameter.iteratorDay.push_back(_ttoi(temp));

		growthCycleList=growthCycleList.Mid(pos+1);

		pos=growthCycleList.Find(' ');
	}
	if (growthCycleList.GetLength()!=0)
		parameter.iteratorDay.push_back(_ttoi(growthCycleList));


	saveParameter();
}


void DialogSetParameter::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void DialogSetParameter::OnBnClickedButtonSetbetadistribution()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog dlg( IDD_DIALOG_BetaDistribution) ;
    dlg.DoModal(); 
	
}


void DialogSetParameter::OnBnClickedButtonSetgrowthcycle()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog dlg( IDD_DIALOG_SetGrowthCycle) ;
	CDialog dlg( IDD_DIALOG_LSystemDetail) ;
	
    dlg.DoModal(); 
}
