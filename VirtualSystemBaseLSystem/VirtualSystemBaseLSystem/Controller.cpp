#include "stdafx.h"
#include "Controller.h"


Controller::Controller(void)
{
	readParameter();

	iteratorTimes=0;
	generateEnergy=0;
	requireEnergy=0;
	//能量池设定能量为
	remindEnergy=10;
	//avaliableEnergy=0;

	lSystemIterator=LSystemIterator();
}


Controller::~Controller(void)
{
}

void Controller::reset()
{
	iteratorTimes=0;
	generateEnergy=0;
	requireEnergy=0;
	remindEnergy=0;
}

void Controller::setItratorTime(int it)
{
	//iteratorTimes=it;

	/*ofstream writeFile("Data/IteratorTimes.txt");

	writeFile<<it<<"\n";
	
	writeFile.close();*/
	iteratorTimes=it;
}

int Controller::getItratorTime()
{
	/*int k;

	ifstream readFile("Data/IteratorTimes.txt");
	readFile>>k;
	readFile.close();*/

	return iteratorTimes;
}

//读取参数信息
void Controller::readParameter()
{
	parameter.iteratorDay.clear();
	ifstream readFile("Data/parameter.txt");

	/*readFile>>leafPonitsCount;

	if(readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile>>leafPoints[i][0]>>leafPoints[i][1]>>leafPoints[i][2];
			i++;
		}
	}
	readFile.close();*/

	/*
	parameter.txt文件结构

	最大年龄
	leafMaxAge segmentMaxAge;

	Beta分布参数
	leafA leafB 
	segmentA segmentB

	汇强参数
	leafAbsordAblity;
	segmentAbsordAblity;

	根与叶子的生物量需求量比例
	propotionOfLeafAndRoot;

	每个迭代周期的时间，第一个数字是个数，往后以此是各个周期的时间长度（天为单位）
	vector<int> iteratorDay;

	产生生物量生长潜力
	E

	叶面积每平方厘米蒸腾作用抵抗力
	resistanceToTranspiration

	光衰减系数
	lightExtinctionCoefficient

	植物的占地面积与植物叶片面积的比
	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal

	叶子的密度
	leafDensity

	叶子的厚度
	leafThickness

	形态参数，高度和半径的比
	propotionOfHeightAndRadius

	节间的密度
	segmentDensity
	*/

	if(readFile.is_open())
	{
		readFile>>parameter.leafMaxAge>>parameter.segmentMaxAge;
		//readFile>>parameter.leafAbsordAblity>>parameter.segmentAbsordAblity;
		readFile>>parameter.leafA>>parameter.leafB;
		readFile>>parameter.segmentA>>parameter.segmentB;
		readFile>>parameter.leafAbsordAblity;
		readFile>>parameter.segmentAbsordAblity;
		readFile>>parameter.propotionOfLeafAndRoot;
		
		int n,k;
		readFile>>n;
		for(int i=0;i<n;i++)
		{
			readFile>>k;
			parameter.iteratorDay.push_back(k);
		}

		readFile>>parameter.E;
		readFile>>parameter.resistanceToTranspiration;
		readFile>>parameter.lightExtinctionCoefficient;
		readFile>>parameter.propertyOfLeafAreaProjectionTotalAndLeafAreaTotal;
		readFile>>parameter.leafDensity;
		readFile>>parameter.leafThickness;
		readFile>>parameter.propotionOfHeightAndRadius;
		readFile>>parameter.segmentDensity;
	}
	readFile.close();
}

//输出基本信息到文本
void Controller::computeSegmentAndLeafAmount()
{
	list<BasicUnit>::iterator basicUnit;

	

	//统计枝条叶子数
	segmentAmount=0;
	leafAmount=0;
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
		{
			segmentAmount++;
			
			if (basicUnit->leafAmount>0)
				leafAmount+=basicUnit->leafAmount;
		}
	}

	//ofstream writeFile("Data/BasicUnitInfomation.txt");

	///*
	//BasicUnitInfomatin.txt文件结构

	//Iterator Times

	//Generate Energy
	//
	//Require Energy
	//
	//Remind Energy
	//
	//Segments Amount

	//Leaves Amount
	//*/
	//writeFile<<iteratorTimes<<"\n";
	//writeFile<<generateEnergy<<"\n";
	//writeFile<<requireEnergy<<"\n";
	//writeFile<<remindEnergy<<"\n";
	//writeFile<<segmentAmount<<"\n";
	//writeFile<<leafAmount<<"\n";
	//
	//writeFile.close();
}

void Controller::writeBasicUnitListDetail()
{
	list<BasicUnit>::iterator basicUnit;
	int n=0;

	ofstream writeFile("Data/BasicUnitListDetail.txt");
	
	writeFile<<"Iterator Time:"<<iteratorTimes<<"\n";

	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		n++;
		writeFile<<"No."<<n<<"   ";
		if (basicUnit->isRule)
			writeFile<<"Rule:"<<basicUnit->rule<<"\n";
		else
		{
			writeFile<<"Length:"<<basicUnit->length<<"   ";
			writeFile<<"Redius:"<<basicUnit->redius<<"   ";
			writeFile<<"LeafAmount:"<<basicUnit->leafAmount<<"   ";
			writeFile<<"\n";
		}
	}
	
	writeFile<<"Segments:"<<segmentAmount<<"   ";
	writeFile<<"Leaves:"<<leafAmount<<"\n";
	writeFile.close();
}

void Controller::writeBasicUnitListWithTreeDraw()
{
	list<BasicUnit>::iterator basicUnit;

	ofstream writeFile("Data/writeBasicUnitListWithTreeDraw.txt");

	writeFile<<simpleStringF<<endl;

	writeFile<<segmentAmount<<endl;
	
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
		{
			writeFile<<basicUnit->angleX<<" ";
			writeFile<<basicUnit->angleY<<" ";
			writeFile<<basicUnit->angleZ<<" ";
			writeFile<<basicUnit->length<<" ";
			writeFile<<basicUnit->redius<<" ";
			writeFile<<basicUnit->leafAmount<<endl;
			for(int i=0;i<basicUnit->leafAmount;i++)
				writeFile<<basicUnit->leafArea[i]<<" ";

			writeFile<<endl;
		}
	}
	

	writeFile.close();
}

//写入当前生长周期产生的生物量
void Controller::writeEnergyDetail()
{
	ofstream writeFile("Data/writeEnergyDetail.txt",ofstream::app);

	writeFile<<"Iterator:"<<iteratorTimes<<endl;
	writeFile<<"Require Energy:"<<requireEnergy<<endl;
	writeFile<<"Generate Energy:"<<generateEnergy<<endl;
	writeFile<<"Avaliable Energy:"<<avaliableEnergy<<endl;
	writeFile<<"Remind Energy:"<<remindEnergy<<endl;

	writeFile<<endl;

	writeFile.close();
}

//方便统计
void Controller::writeEnergySatatistic()
{
	ofstream writeFile("Data/writeEnergySatatistic.txt",ofstream::app);

	writeFile<<requireEnergy<<" "<<generateEnergy<<" "<<avaliableEnergy<<" "<<remindEnergy<<endl;

	writeFile.close();
}

void Controller::run()
{
	GenerateEnergy generate;
	Allocate allocate=Allocate(parameter);
	 
	//int iteratorTimes=3;

	//iteratorTimes=getItratorTime();
	//iteratorTimes=9;

	if (iteratorTimes==1)
		lSystemIterator=LSystemIterator();

	//迭代L系统
	if(iteratorTimes>1)
		lSystemIterator.iteratorProcess(iteratorTimes);
	

	//提取计算值
	basicUnitList=lSystemIterator.basicUnitList;
	simpleString=lSystemIterator.simpleString;
	simpleStringF=lSystemIterator.simpleStringF;

	readParameter();

	//生成生物量
	generate.setInput(basicUnitList,parameter);
 	generateEnergy=generate.computeGenerateEnergy();
	
	avaliableEnergy=generateEnergy+remindEnergy;	//加上能量池中剩余的生物量

	//分配生物量,以及反馈到器官
	allocate.setInput(avaliableEnergy,basicUnitList,simpleStringF,parameter);
	allocate.computeRequireEnergy(iteratorTimes);
	allocate.allocateEnergy();
	allocate.feedbackToOrgan();

	basicUnitList=allocate.basicUnitList;

	requireEnergy=allocate.requireEnergy;

	//统计剩余生物量
	remindEnergy=avaliableEnergy-requireEnergy;
	if (remindEnergy<0)
		remindEnergy=0;

	computeSegmentAndLeafAmount();
	writeBasicUnitListDetail();
	writeBasicUnitListWithTreeDraw();	//传信息给画树函数
	writeEnergyDetail();
	writeEnergySatatistic();
	

	lSystemIterator.setBasicUnitList(basicUnitList);
}