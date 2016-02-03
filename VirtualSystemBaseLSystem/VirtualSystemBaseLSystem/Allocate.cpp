#include "stdafx.h"
#include "Allocate.h"


Allocate::Allocate(Parameter parameter)
{
	//����֦����Ҷ�ӵ�Beta�ֲ�����
	segmentBetaDistribution=betaDistribution(parameter.segmentA,parameter.segmentB,parameter.segmentMaxAge);
	leafBetaDistribution=betaDistribution(parameter.leafA,parameter.leafB,parameter.segmentMaxAge);

	//����֦����Ҷ�ӻ�ǿ��Beta�ֲ�����
	/*segmentAbsordAblityBetaDistribution=betaDistribution(parameter.segmentAbsordAblityA,parameter.segmentAbsordAblityB,
															parameter.segmentMaxAge);
	leafAbsordAblityBetaDistribution=betaDistribution(parameter.leafAbsordAblityA,parameter.leafAbsordAblityB,
															parameter.leafMaxAge);*/
}

Allocate::~Allocate(void)
{
}

//������ʼʱ��
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

//Beta�ֲ�����,������Ӧ�ģ�֦����Ҷ�ӣ�vector����
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
	//���ܺͷŵ��������һ��λ��
	distribution.push_back(total);

	return distribution;
}

//������չ��
double Allocate::expansionRate(int beginDay,int endDay,string type)	
{
	vector<double> distribution;
	double pt=0;

	//ȡ����Ӧ��Beta�ֲ�����
	if (type=="Leaf") distribution=leafBetaDistribution;
	else if (type=="Segment") distribution=segmentBetaDistribution;
	/*else if (type=="LeafAbsord") distribution=leafAbsordAblityBetaDistribution;
	else if (type=="SegmentAbsord") distribution=segmentAbsordAblityBetaDistribution;*/

	if (beginDay==0) beginDay=1;

	double check=distribution.back();

	for(int i=beginDay;i<=endDay;i++)
		pt+=distribution.at(i);
		
	pt/=distribution.back(); //vector.back()�������һ��Ԫ�أ�������Ԫ��֮��

	return pt;
}

//����ÿ��������Ԫ����������
void Allocate::computeRequireEnergy(int iteratorTime)
{
	list<BasicUnit>::iterator basicUnit=basicUnitList.begin();
	int beginDay,endDay,today=0;
	double tempSegment,tempLeaf;

	//���㵱ǰʱ��
	today=computeDays(iteratorTime);

	requireEnergyLeaf=0;
	requireEnergySegment=0;
	basicUnitSegmentRequireEnergy.clear();
	basicUnitLeafRequireEnergy.clear();

	////ͬ��basicUnit��simpleF
	//while(basicUnit->isRule)
	//	basicUnit++;

	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{ 
		if (!basicUnit->isRule)
		{
			tempLeaf=0;

			//�趨beginDay
			/*if (basicUnit->birthIteratorTime==iteratorTime) 
				beginDay=1;
			else  beginDay=computeDays(basicUnit->birthIteratorTime);*/
			//else  beginDay=today-computeDays(basicUnit->birthIteratorTime);
			beginDay=basicUnit->age;
			if (beginDay==0) beginDay=1;


			//�趨endDay 
			//endDay=beginDay+parameter.iteratorDay[iteratorTime-1];
			endDay=basicUnit->age+parameter.iteratorDay[iteratorTime-1];
			if (endDay>parameter.segmentMaxAge)
				endDay=parameter.segmentMaxAge;
			if (beginDay>parameter.segmentMaxAge)
				beginDay=parameter.segmentMaxAge;

			tempSegment=expansionRate(1,endDay,"Segment");
			

			//Segment:��ǿ����չ��
			double push=tempSegment*parameter.segmentAbsordAblity;
			requireEnergySegment+=push;
			basicUnitSegmentRequireEnergy.push_back(push);
			
			//����Ҷ�Ӽ���Ҷ��
			if (basicUnit->leafAmount>0)
			{
				//�趨endDay��beginDay�������Ѿ������
				if (endDay>parameter.leafMaxAge)
					endDay=parameter.leafMaxAge;

				tempLeaf=expansionRate(1,endDay,"Leaf");
				//parameter.leafAbsordAblity=expansionRate(beginDay,endDay,"LeafAbsord");	//�����ǿ

				//Leaf:��ǿ����չ��
				requireEnergyLeaf+=parameter.leafAbsordAblity*tempLeaf*basicUnit->leafAmount;
				for(int v=0;v<basicUnit->leafAmount;v++)
					basicUnitLeafRequireEnergy.push_back(tempLeaf*parameter.leafAbsordAblity);
			}

			//Add Age
			basicUnit->age+=parameter.iteratorDay[iteratorTime-1];
		}
	}

	//��ǿ����չ��
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

//����������
void Allocate::allocateEnergy()	
{
	//��ǰ�����������������ɵ�������
	availableEnergy+=1000;
	if (availableEnergy>=requireEnergy)
	{
		reminderEnergy=availableEnergy-requireEnergy;

		//����������
		basicUnitLeafGetEnergy=basicUnitLeafRequireEnergy;
		basicUnitSegmentGetEnergy=basicUnitSegmentRequireEnergy;

	}
	else //�����������
	{
		list<BasicUnit>::iterator basicUnit;
		int signCount=0;
		double temp;

		//ͳ������������ԪsignNumber֮��
		for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
			if (!basicUnit->isRule)
				signCount+=basicUnit->signNumber;

		basicUnitSegmentGetEnergy.clear();

		int indexOfSegment=0;
		int indexOfLeaf=0;
		//���ݱ�Ǻŷ��䣬�ȷ��䵽ÿ��ҶԪ��segment�����ٷ��䵽Ҷ��
		for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
		{
			if (!basicUnit->isRule)
			{
				temp=(double)basicUnit->signNumber/signCount*availableEnergy;
				//basicUnitSegmentGetEnergy.push_back(temp);
				double total=basicUnitSegmentRequireEnergy[indexOfSegment];

				//ͳ�Ƶ�ǰ����������ԪҶ�������������ܺ�
				for(int i=0;i<basicUnit->leafAmount;i++)
					total+=basicUnitLeafRequireEnergy[indexOfLeaf+i];

				//���ݹ�ʽ����ڼ䣬[segmentRequire/(segmentRequire+leafRequire)]*basicUnitGetEnergy
				//���ڼ���������������������ռ����
				basicUnitSegmentGetEnergy.push_back(temp*basicUnitSegmentRequireEnergy[indexOfSegment]/total);


				//���䵽Ҷ��,�����Ҷ��
				if (basicUnit->leafAmount>0)
				{
					//����Ҷ��
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

//���������������ٱ仯
list<BasicUnit> Allocate::feedbackToOrgan()
{
	list<BasicUnit>::iterator basicUnit;
	int indexSegment=0;		//�ڼ��α�
	int indexLeaf=0;		//Ҷ���α�
	double tLeaf=parameter.leafDensity*parameter.leafThickness;  //Ҷ�ӵ��ܶȡ����
	double tSegment=3.1415926*parameter.segmentDensity*parameter.propotionOfHeightAndRadius;  //֦���ܶȡ���̬������3.14

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
			//Ҷ�Ӽ��α仯
			if(basicUnit->leafAmount!=0)
			{
				for(int i=0;i<basicUnit->leafAmount;i++)
					basicUnit->leafArea[i]+=basicUnitLeafGetEnergy[indexLeaf++]/(tLeaf*basicUnit->leafArea[i]);
			}

			//�ڼ伸�α仯
			testSegment.push_back(pow(pow(basicUnit->redius,3)+basicUnitSegmentGetEnergy[indexSegment++]/tSegment,1/3.0)-basicUnit->redius);
			indexSegment--;
			basicUnit->redius=pow(pow(basicUnit->redius,3)+basicUnitSegmentGetEnergy[indexSegment++]/tSegment,1/3.0);
			basicUnit->length=parameter.propotionOfHeightAndRadius*basicUnit->redius;
		}
	}

	return basicUnitList;
}