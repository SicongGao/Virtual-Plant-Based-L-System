#pragma once
#include "Expression.h"
#include <list>

class LSystemIterator
{
public:
	LSystemIterator();
	~LSystemIterator(void);

	//������Ԫ����
	list<BasicUnit> basicUnitList;

	//��¼���ʽ
	vector<Expression> expressionList;

	//�򻯽���ʽ
	string simpleString;
	string simpleStringF;

	//��������
	int iteratorTimes;

	//������Ԫ����
	long basicUnitCount;
	
	long FNum;	//F������Ŀ

	//addressFΪF��S�е�����λ�ã�rusultΪ��ǽ��
	vector<int> addressF,sign;	

	/*=====================================FUNCTION========================================*/

	//��������
	void iteratorProcess(int times);

	//��ʼ���ַ���
	void initSimpleString(string s);

	//�����
	void doSign(string &s);

	//Ѱ��F�ĺ���
	void findChildren(string &s);

	void setIteratorTimes(int i);
	void setBasicUnitList(list<BasicUnit> buList);

	void writeLSystemIteratorDetail(int times);
};

