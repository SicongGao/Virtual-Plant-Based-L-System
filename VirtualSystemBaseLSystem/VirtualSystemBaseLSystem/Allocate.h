#pragma once
#include "Expression.h"

class Allocate
{
public:
	Allocate(Parameter parameter);
	~Allocate(void);

	//double totalEnergy;		
	double reminderEnergy;	//剩余生物量
	double requireEnergy;	//所有生长单元需求生物量
	double availableEnergy;	//可用生物量
	//根，枝干，叶子的生物量需求量
	double requireEnergyRoot;
	double requireEnergySegment;
	double requireEnergyLeaf;

	vector<double> basicUnitSegmentGetEnergy;		//生物量实际获得生物量,不包括生长单元自身叶片获得的生物量
	vector<double> basicUnitLeafGetEnergy;			//每个叶片实际获得生物量
	vector<double> basicUnitSegmentRequireEnergy;	//生物量需求生物量,不包括生长单元自身叶片需求的生物量
	vector<double> basicUnitLeafRequireEnergy;		//每个叶片实际需求生物量
	list<BasicUnit> basicUnitList;					//生长单元序列
	string simpleStringF;							//简化表达式

	//枝条，叶子Beta分布数组
	vector<double> segmentBetaDistribution;
	vector<double> leafBetaDistribution;
	//vector<double> segmentAbsordAblityBetaDistribution;	//枝条汇强贝塔分布
	//vector<double> leafAbsordAblityBetaDistribution;	//叶子汇强贝塔分布

	//存储参数信息
	Parameter parameter;
	
	/*=====================================FUNCTION========================================*/
	void setInput(double energy,list<BasicUnit> buList,string s,Parameter p);
	vector<double> betaDistribution(int a,int b,int T);			//Beta分布计算,返回相应的（枝条，叶子）vector数组
	double expansionRate(int beginDay,int endDay,string type);	//计算扩展率
	void allocateEnergy();		//分配生物量
	void computeRequireEnergy(int iteratorTime);			//计算每个生长单元需求生物量
	list<BasicUnit> feedbackToOrgan();		//反馈生物量到器官变化

	int computeDays(int itratorTime);	//计算起始时间
	//void readParameter();		//读取参数
};

