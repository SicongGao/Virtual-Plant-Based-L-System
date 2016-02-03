// DialogSetParameter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtualSystemBaseLSystem.h"
#include "DialogSetParameter.h"
#include "afxdialogex.h"


// DialogSetParameter �Ի���

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


//��ȡ������Ϣ
void DialogSetParameter::readParameter()
{
	ifstream readFile("Data/parameter.txt");

	/*
	parameter.txt�ļ��ṹ

	�������
	leafMaxAge segmentMaxAge;

	Beta�ֲ�����
	leafA leafB 
	segmentA segmentB

	��ǿ�Ĳ���
	leafAbsordAblity;
	segmentAbsordAblity;

	����Ҷ�ӵ�����������������
	propotionOfLeafAndRoot;

	ÿ���������ڵ�ʱ�䣬��һ�������Ǹ����������Դ��Ǹ������ڵ�ʱ�䳤�ȣ���Ϊ��λ��
	vector<int> iteratorDay;

	��������������Ǳ��
	E

	Ҷ���ÿƽ�������������õֿ���
	resistanceToTranspiration

	��˥��ϵ��
	lightExtinctionCoefficient

	ֲ���ռ�������ֲ��ҶƬ����ı�
	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal

	Ҷ�ӵ��ܶ�
	leafDensity

	Ҷ�ӵĺ��
	leafThickness

	��̬�������߶ȺͰ뾶�ı�
	propotionOfHeightAndRadius

	�ڼ���ܶ�
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
	parameter.txt�ļ��ṹ

	�������
	leafMaxAge segmentMaxAge;

	Beta�ֲ�����
	leafA leafB 
	segmentA segmentB

	��ǿ�Ĳ���
	leafAbsordAblity;
	segmentAbsordAblity;

	����Ҷ�ӵ�����������������
	propotionOfLeafAndRoot;

	ÿ���������ڵ�ʱ�䣬��һ�������Ǹ����������Դ��Ǹ������ڵ�ʱ�䳤�ȣ���Ϊ��λ��
	vector<int> iteratorDay;

	��������������Ǳ��
	E

	Ҷ���ÿƽ�������������õֿ���
	resistanceToTranspiration

	��˥��ϵ��
	lightExtinctionCoefficient

	ֲ���ռ�������ֲ��ҶƬ����ı�
	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal

	Ҷ�ӵ��ܶ�
	leafDensity

	Ҷ�ӵĺ��
	leafThickness

	��̬�������߶ȺͰ뾶�ı�
	propotionOfHeightAndRadius

	�ڼ���ܶ�
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

// DialogSetParameter ��Ϣ�������
void DialogSetParameter::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	
	UpdateData(true);

	//�� growthCycleList������ת����parameter.iteratorDay
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void DialogSetParameter::OnBnClickedButtonSetbetadistribution()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog dlg( IDD_DIALOG_BetaDistribution) ;
    dlg.DoModal(); 
	
}


void DialogSetParameter::OnBnClickedButtonSetgrowthcycle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialog dlg( IDD_DIALOG_SetGrowthCycle) ;
	CDialog dlg( IDD_DIALOG_LSystemDetail) ;
	
    dlg.DoModal(); 
}
