#pragma once
#include "LSystemIterator.h"
#include "Tree.h"
#include "Allocate.h"
#include "GenerateEnergy.h"

//������Ϣ�࣬�ܿ���
class Controller
{
public:
	Controller(void);
	~Controller(void);

	//������Ԫ����
	list<BasicUnit> basicUnitList;

	//��¼���ʽ
	vector<Expression> expressionList;

	//�򻯽���ʽ
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
	void computeSegmentAndLeafAmount();	//���������Ϣ
	void writeBasicUnitListDetail();
	void writeBasicUnitListWithTreeDraw();
	void writeEnergyDetail();
	void writeEnergySatatistic();
};