#include "stdafx.h"
#include "GenerateEnergy.h"


GenerateEnergy::GenerateEnergy()
{
	//init
	leafAreaTotal=0;
	leafAreaProjectionTotal=0;

	
}


GenerateEnergy::~GenerateEnergy(void)
{
}

void GenerateEnergy::setInput(list<BasicUnit> buList,Parameter parameter)
{
	basicUnitList=buList;

	propertyOfLeafAreaProjectionTotalAndLeafAreaTotal=parameter.propertyOfLeafAreaProjectionTotalAndLeafAreaTotal;
	resistanceToTranspiration=parameter.resistanceToTranspiration;
	lightExtinctionCoefficient=parameter.lightExtinctionCoefficient;
	E=parameter.E;
	propertyOfRootAndLeaf=parameter.propotionOfLeafAndRoot;
	//统计所有叶子面积
	leafAreaTotal=countAllLeafArea();
}

//计算所有叶片的面积
double GenerateEnergy::countAllLeafArea()
{
	list<BasicUnit>::iterator basicUnit;
	int leafAreaTotal=0;

	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
		{
			double temp=0;
			for(int i=0;i<basicUnit->leafAmount;i++)
				temp+=basicUnit->leafArea[i];

			leafAreaTotal+=temp;
		}
	}
	return leafAreaTotal;
}

//计算产生生物量
double GenerateEnergy::computeGenerateEnergy()
{
	if (leafAreaTotal==0) return 0;
	else
	{
		leafAreaProjectionTotal=propertyOfLeafAreaProjectionTotalAndLeafAreaTotal*leafAreaTotal*0.001;

		generateEnergyTotal=E*leafAreaProjectionTotal/(resistanceToTranspiration*lightExtinctionCoefficient)
						*(1-exp(-lightExtinctionCoefficient*leafAreaTotal/leafAreaProjectionTotal));
		double temp=1-exp(-lightExtinctionCoefficient*leafAreaTotal/leafAreaProjectionTotal);
		return (generateEnergyTotal+generateEnergyTotal*propertyOfRootAndLeaf)*1000;
	}
}