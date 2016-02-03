#include "stdafx.h"
#include "Controller.h"


Controller::Controller(void)
{
	readParameter();

	iteratorTimes=0;
	generateEnergy=0;
	requireEnergy=0;
	//�������趨����Ϊ
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

//��ȡ������Ϣ
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
	parameter.txt�ļ��ṹ

	�������
	leafMaxAge segmentMaxAge;

	Beta�ֲ�����
	leafA leafB 
	segmentA segmentB

	��ǿ����
	leafAbsordAblity;
	segmentAbsordAblity;

	����Ҷ�ӵ�����������������
	propotionOfLeafAndRoot;

	ÿ���������ڵ�ʱ�䣬��һ�������Ǹ����������Դ��Ǹ������ڵ�ʱ�䳤�ȣ���Ϊ��λ��
	vector<int> iteratorDay;

	��������������Ǳ��
	E

	Ҷ���ÿƽ�������������õֿ���
	resistanceToTranspiration

	��˥��ϵ��
	lightExtinctionCoefficient

	ֲ���ռ�������ֲ��ҶƬ����ı�
	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal

	Ҷ�ӵ��ܶ�
	leafDensity

	Ҷ�ӵĺ��
	leafThickness

	��̬�������߶ȺͰ뾶�ı�
	propotionOfHeightAndRadius

	�ڼ���ܶ�
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

//���������Ϣ���ı�
void Controller::computeSegmentAndLeafAmount()
{
	list<BasicUnit>::iterator basicUnit;

	

	//ͳ��֦��Ҷ����
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
	//BasicUnitInfomatin.txt�ļ��ṹ

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

//д�뵱ǰ�������ڲ�����������
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

//����ͳ��
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

	//����Lϵͳ
	if(iteratorTimes>1)
		lSystemIterator.iteratorProcess(iteratorTimes);
	

	//��ȡ����ֵ
	basicUnitList=lSystemIterator.basicUnitList;
	simpleString=lSystemIterator.simpleString;
	simpleStringF=lSystemIterator.simpleStringF;

	readParameter();

	//����������
	generate.setInput(basicUnitList,parameter);
 	generateEnergy=generate.computeGenerateEnergy();
	
	avaliableEnergy=generateEnergy+remindEnergy;	//������������ʣ���������

	//����������,�Լ�����������
	allocate.setInput(avaliableEnergy,basicUnitList,simpleStringF,parameter);
	allocate.computeRequireEnergy(iteratorTimes);
	allocate.allocateEnergy();
	allocate.feedbackToOrgan();

	basicUnitList=allocate.basicUnitList;

	requireEnergy=allocate.requireEnergy;

	//ͳ��ʣ��������
	remindEnergy=avaliableEnergy-requireEnergy;
	if (remindEnergy<0)
		remindEnergy=0;

	computeSegmentAndLeafAmount();
	writeBasicUnitListDetail();
	writeBasicUnitListWithTreeDraw();	//����Ϣ����������
	writeEnergyDetail();
	writeEnergySatatistic();
	

	lSystemIterator.setBasicUnitList(basicUnitList);
}