#pragma once
#include "Expression.h"
#include <math.h>

class GenerateEnergy
{
public:
	GenerateEnergy();
	~GenerateEnergy(void);

	list<BasicUnit> basicUnitList;

	double generateEnergyTotal;		//产生生物量总量
	double leafAreaTotal;			//叶片总面积
	double leafAreaProjectionTotal;	//占地面积（叶片投影面积）

	double E;	//产生生物量生长潜力
	double resistanceToTranspiration;	//叶面积每平方厘米蒸腾作用抵抗力
	double lightExtinctionCoefficient;	//光衰减系数
	double propertyOfLeafAreaProjectionTotalAndLeafAreaTotal;	//植物的占地面积与植物叶片面积的比
	double propertyOfRootAndLeaf;
	/************************************FUNCTION*********************************/
	void setInput(list<BasicUnit> buList,Parameter p);
	double countAllLeafArea();			//计算所有叶片的面积
	double computeGenerateEnergy();	//计算产生生物量
};

