#pragma once
#include "LSystemIterator.h"
#include "Tree.h"
#include "Allocate.h"
#include "GenerateEnergy.h"

//交换信息类，总控制
class Controller
{
public:
	Controller(void);
	~Controller(void);

	//基本单元序列
	list<BasicUnit> basicUnitList;

	//记录表达式
	vector<Expression> expressionList;

	//简化解析式
	string simpleString;
	string simpleStringF;

	int iteratorTimes;
	double remindEnergy;
	double requireEnergy;
	double generateEnergy;
	double avaliableEnergy;

	int segmentAmount;
	int leafAmount;

	Parameter parameter;
	LSystemIterator lSystemIterator;

	Tree tree;
	
	//=================================FUNCTION==========================================
	
	void run();
	void setItratorTime(int it);
	int getItratorTime();
	void reset();
	
	void readParameter();
	void computeSegmentAndLeafAmount();	//计算基本信息
	void writeBasicUnitListDetail();
	void writeBasicUnitListWithTreeDraw();
	void writeEnergyDetail();
	void writeEnergySatatistic();
};