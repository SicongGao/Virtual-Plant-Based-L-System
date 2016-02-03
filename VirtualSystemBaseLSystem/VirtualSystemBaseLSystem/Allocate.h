#pragma once
#include "Expression.h"

class Allocate
{
public:
	Allocate(Parameter parameter);
	~Allocate(void);

	//double totalEnergy;		
	double reminderEnergy;	//ʣ��������
	double requireEnergy;	//����������Ԫ����������
	double availableEnergy;	//����������
	//����֦�ɣ�Ҷ�ӵ�������������
	double requireEnergyRoot;
	double requireEnergySegment;
	double requireEnergyLeaf;

	vector<double> basicUnitSegmentGetEnergy;		//������ʵ�ʻ��������,������������Ԫ����ҶƬ��õ�������
	vector<double> basicUnitLeafGetEnergy;			//ÿ��ҶƬʵ�ʻ��������
	vector<double> basicUnitSegmentRequireEnergy;	//����������������,������������Ԫ����ҶƬ�����������
	vector<double> basicUnitLeafRequireEnergy;		//ÿ��ҶƬʵ������������
	list<BasicUnit> basicUnitList;					//������Ԫ����
	string simpleStringF;							//�򻯱��ʽ

	//֦����Ҷ��Beta�ֲ�����
	vector<double> segmentBetaDistribution;
	vector<double> leafBetaDistribution;
	//vector<double> segmentAbsordAblityBetaDistribution;	//֦����ǿ�����ֲ�
	//vector<double> leafAbsordAblityBetaDistribution;	//Ҷ�ӻ�ǿ�����ֲ�

	//�洢������Ϣ
	Parameter parameter;
	
	/*=====================================FUNCTION========================================*/
	void setInput(double energy,list<BasicUnit> buList,string s,Parameter p);
	vector<double> betaDistribution(int a,int b,int T);			//Beta�ֲ�����,������Ӧ�ģ�֦����Ҷ�ӣ�vector����
	double expansionRate(int beginDay,int endDay,string type);	//������չ��
	void allocateEnergy();		//����������
	void computeRequireEnergy(int iteratorTime);			//����ÿ��������Ԫ����������
	list<BasicUnit> feedbackToOrgan();		//���������������ٱ仯

	int computeDays(int itratorTime);	//������ʼʱ��
	//void readParameter();		//��ȡ����
};

