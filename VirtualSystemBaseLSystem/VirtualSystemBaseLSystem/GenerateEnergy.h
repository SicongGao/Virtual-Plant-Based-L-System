#pragma once
#include "Expression.h"
#include <math.h>

class GenerateEnergy
{
public:
	GenerateEnergy();
	~GenerateEnergy(void);

	list<BasicUnit> basicUnitList;

	double generateEnergyTotal;		//��������������
	double leafAreaTotal;			//ҶƬ�����
	double leafAreaProjectionTotal;	//ռ�������ҶƬͶӰ�����

	double E;	//��������������Ǳ��
	double resistanceToTranspiration;	//Ҷ���ÿƽ�������������õֿ���
	double lightExtinctionCoefficient;	//��˥��ϵ��
	double propertyOfLeafAreaProjectionTotalAndLeafAreaTotal;	//ֲ���ռ�������ֲ��ҶƬ����ı�
	double propertyOfRootAndLeaf;
	/************************************FUNCTION*********************************/
	void setInput(list<BasicUnit> buList,Parameter p);
	double countAllLeafArea();			//��������ҶƬ�����
	double computeGenerateEnergy();	//�������������
};

