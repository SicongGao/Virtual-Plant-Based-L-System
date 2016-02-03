#pragma once
#include <string>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

struct BasicUnit //������Ԫ�ṹ�壬������ȡ�����еĻ�����Ԫ
{	
	double redius;
	double length;
	double angleX;
	double angleY;
	double angleZ;
	
	//�洢ʽ�еĹ���
	string rule;
	//�Ƿ���ڹ���
	bool isRule;
	//bool hasLeaf;

	int id;	//���

	int signNumber;	//��Ǻ�
	
	int age;
	int birthIteratorTime;	//���ĸ��������ڳ���

	vector<int> children;	//�������
	int parent;	//�������

	int leafAmount;				//ҶƬ��Ŀ
	vector<double> leafArea;	//ҶƬ���
};

struct Parameter //���ֲ���
{	
	//�������
	int leafMaxAge;
	int segmentMaxAge;

	//��ǿ
	double leafAbsordAblity;
	double segmentAbsordAblity;

	//Beta�ֲ�����
	double leafA,leafB;
	double segmentA,segmentB;
	//����Ҷ�ӵ�����������������
	double propotionOfLeafAndRoot;
	
	//�����������ڵ�����
	vector<int> iteratorDay;

	/****************Generate Energy Part**************/
	double E;	//��������������Ǳ��
	double resistanceToTranspiration;	//Ҷ���ÿƽ�������������õֿ���
	double lightExtinctionCoefficient;	//��˥��ϵ��
	double propertyOfLeafAreaProjectionTotalAndLeafAreaTotal; //ֲ���ռ�������ֲ��ҶƬ����ı�
	/****************Organ Change*********************/
	double leafDensity;		//Ҷ�ӵ��ܶ�
	double leafThickness;	//Ҷ�ӵĺ��
	double propotionOfHeightAndRadius;	//��̬�������߶ȺͰ뾶�ı�

	double segmentDensity;	//�ڼ���ܶ�
};

class Expression
{
//����ʽ��
public:
	Expression(string s);
	~Expression(void);
	
	//���ʽ���ƺ�����
	char expressionName;
	string expression;

	//�򻯱��ʽ
	string simpleString;
	
	//�洢ȫ����������Ԫ��Ϣ
	list<BasicUnit> basicUnitList;
	
	//��¼���ʽ����������ֵ
	vector<string> parameterName;
	vector<double> parameterValue;
	
	/*=====================================FUNCTION========================================*/

	//��������ַ�name������ֵ
	double getParameterValue(string name);

	void setParameterValue(string s);
	
	//�������ʽ,�洢ȫ����������Ԫ��Ϣ
	void analysis();
	
	//ȡ������������Ԫ
	list<BasicUnit> getBasicUnit();

	//�ָ��ַ���.���ؽ��Ϊ�����ַ�
	vector<string> splitString(char s[],const char *split);
	
	//���������ڵ��ַ��������з�������������ʽ���
	double analysisBracket(string s);

	//����Ҫƥ������ţ���(������[����,���ַ���������ʼλ�ã�������һ�����ŵ���Ծ���
	int fineNextBracket(char bracket,string s);

	//�򻯽���ʽ
	string getSimpleString();
	void setSimpleString(string s);
};

