#include "stdafx.h"
#include "Allocate.h"


Allocate::Allocate(Parameter parameter)
{
	//计算枝条和叶子的Beta分布数组
	segmentBetaDistribution=betaDistribution(parameter.segmentA,parameter.segmentB,parameter.segmentMaxAge);
	leafBetaDistribution=betaDistribution(parameter.leafA,parameter.leafB,parameter.segmentMaxAge);

	//计算枝条和叶子汇强的Beta分布数组
	/*segmentAbsordAblityBetaDistribution=betaDistribution(parameter.segmentAbsordAblityA,parameter.segmentAbsordAblityB,
															parameter.segmentMaxAge);
	leafAbsordAblityBetaDistribution=betaDistribution(parameter.leafAbsordAblityA,parameter.leafAbsordAblityB,
															parameter.leafMaxAge);*/
}

Allocate::~Allocate(void)
{
}

//计算起始时间
int Allocate::computeDays(int itratorTime)
{
	int days=0;

	for(int i=0;i<itratorTime;i++)
		days+=parameter.iteratorDay[i];

	return days;
}

void Allocate::setInput(double energy,list<BasicUnit> buList,string s,Parameter parameter)
{
	this->parameter=parameter;
	
	this->availableEnergy=energy;
	basicUnitList=buList;
	simpleStringF=s;
}

//Beta分布计算,返回相应的（枝条，叶子）vector数组
vector<double> Allocate::betaDistribution(int a,int b,int T)			
{
	vector<double> distribution;
	double total=0;

	for(int i=1;i<=T;i++)
	{
		double x1=(i-0.5)/T;
		double x2=1-x1;
		double temp=pow(x1,a-1)*pow(x2,b-1)/T;

		distribution.push_back(temp);
		total+=temp;
	}
	//把总和放到数组最后一个位置
	distribution.push_back(total);

	return distribution;
}

//计算扩展率
double Allocate::expansionRate(int beginDay,int endDay,string type)	
{
	vector<double> distribution;
	double pt=0;

	//取出相应的Beta分布数组
	if (type=="Leaf") distribution=leafBetaDistribution;
	else if (type=="Segment") distribution=segmentBetaDistribution;
	/*else if (type=="LeafAbsord") distribution=leafAbsordAblityBetaDistribution;
	else if (type=="SegmentAbsord") distribution=segmentAbsordAblityBetaDistribution;*/

	if (beginDay==0) beginDay=1;

	double check=distribution.back();

	for(int i=beginDay;i<=endDay;i++)
		pt+=distribution.at(i);
		
	pt/=distribution.back(); //vector.back()存着最后一个元素，即所有元素之和

	return pt;
}

//计算每个生长单元需求生物量
void Allocate::computeRequireEnergy(int iteratorTime)
{
	list<BasicUnit>::iterator basicUnit=basicUnitList.begin();
	int beginDay,endDay,today=0;
	double tempSegment,tempLeaf;

	//计算当前时间
	today=computeDays(iteratorTime);

	requireEnergyLeaf=0;
	requireEnergySegment=0;
	basicUnitSegmentRequireEnergy.clear();
	basicUnitLeafRequireEnergy.clear();

	////同步basicUnit与simpleF
	//while(basicUnit->isRule)
	//	basicUnit++;

	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{ 
		if (!basicUnit->isRule)
		{
			tempLeaf=0;

			//设定beginDay
			/*if (basicUnit->birthIteratorTime==iteratorTime) 
				beginDay=1;
			else  beginDay=computeDays(basicUnit->birthIteratorTime);*/
			//else  beginDay=today-computeDays(basicUnit->birthIteratorTime);
			beginDay=basicUnit->age;
			if (beginDay==0) beginDay=1;


			//设定endDay 
			//endDay=beginDay+parameter.iteratorDay[iteratorTime-1];
			endDay=basicUnit->age+parameter.iteratorDay[iteratorTime-1];
			if (endDay>parameter.segmentMaxAge)
				endDay=parameter.segmentMaxAge;
			if (beginDay>parameter.segmentMaxAge)
				beginDay=parameter.segmentMaxAge;

			tempSegment=expansionRate(1,endDay,"Segment");
			

			//Segment:汇强×扩展率
			double push=tempSegment*parameter.segmentAbsordAblity;
			requireEnergySegment+=push;
			basicUnitSegmentRequireEnergy.push_back(push);
			
			//若有叶子计算叶子
			if (basicUnit->leafAmount>0)
			{
				//设定endDay，beginDay在上面已经计算过
				if (endDay>parameter.leafMaxAge)
					endDay=parameter.leafMaxAge;

				tempLeaf=expansionRate(1,endDay,"Leaf");
				//parameter.leafAbsordAblity=expansionRate(beginDay,endDay,"LeafAbsord");	//计算汇强

				//Leaf:汇强×扩展率
				requireEnergyLeaf+=parameter.leafAbsordAblity*tempLeaf*basicUnit->leafAmount;
				for(int v=0;v<basicUnit->leafAmount;v++)
					basicUnitLeafRequireEnergy.push_back(tempLeaf*parameter.leafAbsordAblity);
			}

			//Add Age
			basicUnit->age+=parameter.iteratorDay[iteratorTime-1];
		}
	}

	//汇强×扩展率
	//requireEnergyLeaf*=parameter.leafAbsordAblity;
	//requireEnergySegment*=parameter.segmentAbsordAblity;

	requireEnergyLeaf*=1000;
	requireEnergySegment*=1000;
	requireEnergyRoot=parameter.propotionOfLeafAndRoot*requireEnergyLeaf;

	requireEnergy=requireEnergyLeaf+requireEnergyRoot+requireEnergySegment;

	requireEnergy*=0.1;

	//output Leaf segment and root's ENERGY 
	{
		ofstream writeFile("Data/writeSegmentLeafRootEnergy.txt",ofstream::app);
		writeFile<<requireEnergySegment*0.1<<" "<<requireEnergyLeaf*0.1<<" "<<requireEnergyRoot*0.1<<endl;
		writeFile.close();

	}
}

//分配生物量
void Allocate::allocateEnergy()	
{
	//当前需求生物量满足生成的生物量
	availableEnergy+=1000;
	if (availableEnergy>=requireEnergy)
	{
		reminderEnergy=availableEnergy-requireEnergy;

		//分配生物量
		basicUnitLeafGetEnergy=basicUnitLeafRequireEnergy;
		basicUnitSegmentGetEnergy=basicUnitSegmentRequireEnergy;

	}
	else //需求大于生成
	{
		list<BasicUnit>::iterator basicUnit;
		int signCount=0;
		double temp;

		//统计所有生长单元signNumber之和
		for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
			if (!basicUnit->isRule)
				signCount+=basicUnit->signNumber;

		basicUnitSegmentGetEnergy.clear();

		int indexOfSegment=0;
		int indexOfLeaf=0;
		//根据标记号分配，先分配到每个叶元（segment），再分配到叶子
		for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
		{
			if (!basicUnit->isRule)
			{
				temp=(double)basicUnit->signNumber/signCount*availableEnergy;
				//basicUnitSegmentGetEnergy.push_back(temp);
				double total=basicUnitSegmentRequireEnergy[indexOfSegment];

				//统计当前基本生长单元叶子需求生物量总和
				for(int i=0;i<basicUnit->leafAmount;i++)
					total+=basicUnitLeafRequireEnergy[indexOfLeaf+i];

				//根据公式分配节间，[segmentRequire/(segmentRequire+leafRequire)]*basicUnitGetEnergy
				//即节间需求量在总需求量中所占比例
				basicUnitSegmentGetEnergy.push_back(temp*basicUnitSegmentRequireEnergy[indexOfSegment]/total);


				//分配到叶子,如果有叶子
				if (basicUnit->leafAmount>0)
				{
					//分配叶子
					for(int i=0;i<basicUnit->leafAmount;i++)
					{
						basicUnitLeafGetEnergy.push_back(temp*basicUnitLeafRequireEnergy[indexOfLeaf++]/total);
					}
				}
				indexOfSegment++;
			}
		}
		reminderEnergy=0;
	}
}

//反馈生物量到器官变化
list<BasicUnit> Allocate::feedbackToOrgan()
{
	list<BasicUnit>::iterator basicUnit;
	int indexSegment=0;		//节间游标
	int indexLeaf=0;		//叶子游标
	double tLeaf=parameter.leafDensity*parameter.leafThickness;  //叶子的密度×厚度
	double tSegment=3.1415926*parameter.segmentDensity*parameter.propotionOfHeightAndRadius;  //枝干密度×形态参数×3.14

	//=======================================================================================
	int leafNum=0;
	int segmentNum=0;

	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
		{
			segmentNum++;
			leafNum+=basicUnit->leafAmount;
		}
	}

	//=======================================================================================
	vector<double> testSegment;

	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule) 
		{
			//叶子几何变化
			if(basicUnit->leafAmount!=0)
			{
				for(int i=0;i<basicUnit->leafAmount;i++)
					basicUnit->leafArea[i]+=basicUnitLeafGetEnergy[indexLeaf++]/(tLeaf*basicUnit->leafArea[i]);
			}

			//节间几何变化
			testSegment.push_back(pow(pow(basicUnit->redius,3)+basicUnitSegmentGetEnergy[indexSegment++]/tSegment,1/3.0)-basicUnit->redius);
			indexSegment--;
			basicUnit->redius=pow(pow(basicUnit->redius,3)+basicUnitSegmentGetEnergy[indexSegment++]/tSegment,1/3.0);
			basicUnit->length=parameter.propotionOfHeightAndRadius*basicUnit->redius;
		}
	}

	return basicUnitList;
}