#include "stdafx.h"
#include "LSystemIterator.h"
#include <fstream>

////��������
// int LSystemIterator::iteratorTimes=1;

LSystemIterator::LSystemIterator()
{
	string s;

	expressionList.clear();
	basicUnitList.clear();
	//iteratorTimes=1;

	//read file
	ifstream readFile("data/L_sequence.txt");
	if(readFile.is_open())
	{
		int i=0;

		readFile>>s;

		Expression expression=Expression(s);
			
		expression.analysis();
		expressionList.push_back(expression);


		while (!readFile.eof())
		{
			readFile>>s;
			Expression expression=Expression(s);
			
			expressionList.push_back(expression);
		}
	}

	readFile.close();

	//��ʼ��ԭʼ����
	basicUnitList=expressionList[0].getBasicUnit();
	simpleString=expressionList[0].getSimpleString();

	//���±�Ǻ�,���ӱ��
	doSign(simpleString);
	findChildren(simpleString);
}


LSystemIterator::~LSystemIterator(void)
{
}



void LSystemIterator::initSimpleString(string s)
{
	FNum=0;
	simpleStringF=s;
	addressF.clear();

	//ɾ����ͷ��β��[]
	if (simpleStringF[0]=='[')
		simpleStringF.erase(0,1);
	if (simpleStringF[simpleStringF.length()-1]==']')
		simpleStringF.erase(simpleStringF.length()-1,1);

	//ɾ����F�������ĸ
	for(int i=0;i<simpleStringF.length();i++)
	{
		if ((simpleStringF[i]!='F')&&(simpleStringF[i]!='[')&&(simpleStringF[i]!=']'))
		{
				simpleStringF.erase(i,1);
				i--;
		}
	}

	//ɾ����
	for(int i=0;i<simpleStringF.length()-1;i++)
	{
		if ((simpleStringF[i]=='[')&&(simpleStringF[i+1]==']'))
		{
			simpleStringF.erase(i,2);
			i--;
		}
	}

	//F��������,��¼F�ĵ�ַ
	for(int i=0;i<simpleStringF.length();i++)
		if (simpleStringF[i]=='F') 
		{
			addressF.push_back(i);
			FNum++;
		}
}

//�����
void LSystemIterator::doSign(string &s)
{
	int stack;//ջ���
	sign.clear();

	initSimpleString(s);

	//��ʼ����һ��F�ı�ʶ��Ϊ1
	sign.push_back(1);
	for(int i=1;i<FNum;i++)
	{
		int formerF=i;

		//��Fǰһ���ַ�Ϊ']',��ͨ������ƥ��Ѱ������ǰ��F������ǰF�ı��ֵΪǰһ�����ֵ+1
		if (simpleStringF[addressF[i]-1]==']')
		{
			stack=-1;
			int tempF=i;
			
			for(int j=addressF[i]-2;j>=0;j--)
			{
				//��ѭ��ǰ������ջstack=-1����Ϊջ����']',��ѭ��������'['stack+1,����']'stack-1����stackΪ0ʱ˵���ҵ�һ������������
				if (simpleStringF[j]==']') stack--;
				else if (simpleStringF[j]=='[') stack++;
				else if (simpleStringF[j]=='F') formerF--;	//��¼·����F

				//if (stack>0) break;

				if ((stack==0) && (simpleStringF[j]=='F'))
					break;
				
			}
		}
		//��Fǰһ���ַ�Ϊ'['����ͨ������ƥ���ҵ�����ĸ���F
		else if (simpleStringF[addressF[i]-1]=='[')
		{
			stack=0;
			for(int j=addressF[i]-2;j>=0;j--)
			{
				if (simpleStringF[j]=='F') formerF--;
				else if (simpleStringF[j]=='[') stack++;
				else stack--;

				if ((stack==0)&&(simpleStringF[j]=='F'))
					break;
			}
		}
		else formerF=i-1;
		sign.push_back(sign[formerF]+1);
	}

	//save
	int i=0;
	list<BasicUnit>::iterator basicUnit;
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
			if(!basicUnit->isRule)
				basicUnit->signNumber=sign[i++];
	}

	//Output
	cout<<"Do Sign��"<<endl;
	cout<<"F number is "<<FNum<<endl;
	cout<<"The sequence sign is��"<<endl<<simpleStringF<<endl;

	for(int i=0;i<FNum;i++)
		cout<<sign[i]<<" ";
	cout<<endl;
}

//Ѱ��F�ĺ���
void LSystemIterator::findChildren(string &s)
{
	simpleStringF="["+s+"]";
	initSimpleString(simpleStringF);
	list<BasicUnit>::iterator basicUnit=basicUnitList.begin();

	cout<<endl;
	cout<<"Find F's children:"<<endl;

	//ö��ÿ��F��Ѱ�����ǵĺ���
	for(int i=0;i<FNum;i++)
	{
		while(basicUnit->isRule)
			basicUnit++;

		cout<<"The "<<i+1<<" has children:";

		int stack=1;
		int passF=i;	//·����F
		int count=0;	//ͳ�ƺ��Ӹ���

		//���������F�����һ��F1����F1ΪF��Ψһ����
		if (simpleStringF[addressF[i]+1]=='F') 
			{
				cout<<i+2;
				basicUnit->children.push_back(i+2);
				count++;
			}
		else
			for(int j=addressF[i]+1;j<simpleStringF.length();j++)
			{
				if (stack==0) break;	//stackΪ0��ζ��F�������������
				else if (simpleStringF[j]==']') stack--;
				else if (simpleStringF[j]=='[') stack++;
				else if (simpleStringF[j]=='F') 
					{
						passF++;

						//���׵ı��ֵ+1=���ӵı��ֵ
						if ((sign[i]+1)==sign[passF])
						{
							cout<<passF+1<<"  ";
							basicUnit->children.push_back(passF+1);
							count++;
						}
					}
			}

		if (count==0) cout<<"NULL";
		cout<<endl;

		basicUnit++;
	}
}

void LSystemIterator::writeLSystemIteratorDetail(int times)
{
	list<BasicUnit>::iterator basicUnit;
	//int iteratorTimes=times;

	ofstream writeFile("Data/L-System Iterator detail.txt",ofstream::app);
	
	writeFile<<"Iterator Time:"<<times<<"\n";

	basicUnit=basicUnitList.begin();
	for(int i=0;i<simpleString.length();i++)
	{
		if ((simpleString[i]>='A') && (simpleString[i]<='Z'))
		{
			if (basicUnit->isRule)
			{
				if (basicUnit->angleX!=0)
				{
					if (basicUnit->angleX>0)
						writeFile<<"+("<<basicUnit->angleX<<")";
					else writeFile<<"-("<<basicUnit->angleX<<")";
				}
				if (basicUnit->angleY!=0)
				{
					if (basicUnit->angleY>0)
						writeFile<<"&("<<basicUnit->angleY<<")";
					else writeFile<<"^("<<basicUnit->angleY<<")";
				}
				if (basicUnit->angleZ!=0)
				{
					if (basicUnit->angleZ>0)
						writeFile<<"/("<<basicUnit->angleZ<<")";
					else writeFile<<"\("<<basicUnit->angleZ<<")";
				}

				writeFile<<basicUnit->rule;
			}
			else
			{
				writeFile<<'F';
			}


			basicUnit++;
		}
		else
			writeFile<<simpleString[i];

		
	}

	writeFile<<endl;

	writeFile.close();

	}

void LSystemIterator::iteratorProcess(int times)
{
	list<BasicUnit>::iterator basicUnit,j;
	Expression tempExpression=expressionList[0];

	iteratorTimes=times;

	int stringIndex=0;
			
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (basicUnit->isRule)
		{
			char name=basicUnit->rule[0];
			int index;	//��Ҫ�滻�ı��ʽ���
			string paremater;
			list<BasicUnit> tempList;

			//Ѱ����Ҫ�滻�ı��ʽ���
			for (index=1;index<expressionList.size();index++)
				if (expressionList[index].expressionName==name)
					break;

			paremater=basicUnit->rule.substr(2,tempExpression.fineNextBracket('(',&basicUnit->rule[2]));

			//�������ʽ
			expressionList[index].setParameterValue(paremater);
			expressionList[index].analysis();

			//��������(ֻ������basicUnitList����)
			tempList=expressionList[index].getBasicUnit();
			//����Ƕ���Ϣ���µ������У�ֻ�����ڿ�ͷ
			tempList.begin()->angleX=basicUnit->angleX;
			tempList.begin()->angleY=basicUnit->angleY;
			tempList.begin()->angleZ=basicUnit->angleZ;
			//������������
			for(j=tempList.begin();j!=tempList.end();j++)
				j->birthIteratorTime=iteratorTimes;
			//�滻
			basicUnitList.splice(basicUnit,tempList);
			
			
			//ɾ���滻��Ԫ��
			basicUnitList.erase(basicUnit--);

			//============================���¼򻯽���ʽ=========================
			//�ҵ���һ����Ҫ�滻��λ��
			while((simpleString[stringIndex]=='F')||((simpleString[stringIndex]=='[')||(simpleString[stringIndex]==']')))
				stringIndex++;
			//�滻
			simpleString.replace(stringIndex,1,expressionList[index].simpleString);
			//stringIndex�ƶ�
			stringIndex+=expressionList[index].simpleString.length();					
		}
	}
	
	//output the L-system
	writeLSystemIteratorDetail(times);


	cout<<"=========================================================="<<endl;
	cout<<"IteratorTimes:"<<iteratorTimes++<<endl;
	cout<<"BasicUnit Counts:"<<basicUnitList.size()<<endl;
	cout<<"SimpleString:"<<simpleString<<endl;
		
	//���±�Ǻ�,���ӱ��
	doSign(simpleString);
	findChildren(simpleString);

	//����IDֵ
	int i=1;
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
			basicUnit->id=i++;
	}

	//���¸���ID
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
		{
			j=basicUnit;
			for(int i=0;i<basicUnit->children.size();i++)
			{
				int k=basicUnit->children[i];
				for(j=basicUnitList.begin();j!=basicUnitList.end();j++)
				{
					if (!j->isRule)	k--;
					if (k==0)	
					{
						j->parent=basicUnit->id;
						break;
					}
						
				}
			}
		}
	}
		/*for (list<BasicUnit>::iterator bs=basicUnitList.begin();bs!=basicUnitList.end();bs++)
			{
				if (bs->isRule)
					cout<<bs->rule<<": ";
				else cout<<"F:";

				cout<<" Redius:"<<bs->redius<<" Length:"<<bs->length<<" X:"<<bs->angleX
					<<" Y:"<<bs->angleY<<" Z:"<<bs->angleZ<<endl;
			}*/
	
}

void LSystemIterator::setIteratorTimes(int i)
{
	iteratorTimes=i;
}

void LSystemIterator::setBasicUnitList(list<BasicUnit> buList)
{
	basicUnitList=buList;
}