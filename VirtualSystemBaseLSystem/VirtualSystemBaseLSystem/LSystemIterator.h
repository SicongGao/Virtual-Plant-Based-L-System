#pragma once
#include "Expression.h"
#include <list>

class LSystemIterator
{
public:
	LSystemIterator();
	~LSystemIterator(void);

	//基本单元序列
	list<BasicUnit> basicUnitList;

	//记录表达式
	vector<Expression> expressionList;

	//简化解析式
	string simpleString;
	string simpleStringF;

	//迭代次数
	int iteratorTimes;

	//基本单元数量
	long basicUnitCount;
	
	long FNum;	//F的总数目

	//addressF为F在S中的所在位置，rusult为标记结果
	vector<int> addressF,sign;	

	/*=====================================FUNCTION========================================*/

	//迭代过程
	void iteratorProcess(int times);

	//初始化字符串
	void initSimpleString(string s);

	//做标记
	void doSign(string &s);

	//寻找F的孩子
	void findChildren(string &s);

	void setIteratorTimes(int i);
	void setBasicUnitList(list<BasicUnit> buList);

	void writeLSystemIteratorDetail(int times);
};

