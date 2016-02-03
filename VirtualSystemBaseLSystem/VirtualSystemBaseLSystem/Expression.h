#pragma once
#include <string>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

struct BasicUnit //基本单元结构体，用于提取规则中的基本单元
{	
	double redius;
	double length;
	double angleX;
	double angleY;
	double angleZ;
	
	//存储式中的规则
	string rule;
	//是否存在规则
	bool isRule;
	//bool hasLeaf;

	int id;	//编号

	int signNumber;	//标记号
	
	int age;
	int birthIteratorTime;	//在哪个生长周期出现

	vector<int> children;	//孩子序号
	int parent;	//父类序号

	int leafAmount;				//叶片数目
	vector<double> leafArea;	//叶片面积
};

struct Parameter //各种参数
{	
	//最大年龄
	int leafMaxAge;
	int segmentMaxAge;

	//汇强
	double leafAbsordAblity;
	double segmentAbsordAblity;

	//Beta分布参数
	double leafA,leafB;
	double segmentA,segmentB;
	//根与叶子的生物量需求量比例
	double propotionOfLeafAndRoot;
	
	//各个迭代周期的天数
	vector<int> iteratorDay;

	/****************Generate Energy Part**************/
	double E;	//产生生物量生长潜力
	double resistanceToTranspiration;	//叶面积每平方厘米蒸腾作用抵抗力
	double lightExtinctionCoefficient;	//光衰减系数
	double propertyOfLeafAreaProjectionTotalAndLeafAreaTotal; //植物的占地面积与植物叶片面积的比
	/****************Organ Change*********************/
	double leafDensity;		//叶子的密度
	double leafThickness;	//叶子的厚度
	double propotionOfHeightAndRadius;	//形态参数，高度和半径的比

	double segmentDensity;	//节间的密度
};

class Expression
{
//解析式类
public:
	Expression(string s);
	~Expression(void);
	
	//表达式名称和内容
	char expressionName;
	string expression;

	//简化表达式
	string simpleString;
	
	//存储全部的生长单元信息
	list<BasicUnit> basicUnitList;
	
	//记录表达式参数名称与值
	vector<string> parameterName;
	vector<double> parameterValue;
	
	/*=====================================FUNCTION========================================*/

	//传入参数字符name，返回值
	double getParameterValue(string name);

	void setParameterValue(string s);
	
	//解析表达式,存储全部的生长单元信息
	void analysis();
	
	//取得所有生长单元
	list<BasicUnit> getBasicUnit();

	//分割字符串.返回结果为单个字符
	vector<string> splitString(char s[],const char *split);
	
	//传入括号内的字符串，进行分析，返回算术式结果
	double analysisBracket(string s);

	//传入要匹配的括号（‘(’，‘[’）,和字符串括号起始位置，返回下一个括号的相对距离
	int fineNextBracket(char bracket,string s);

	//简化解析式
	string getSimpleString();
	void setSimpleString(string s);
};

