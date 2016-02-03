#include "stdafx.h"
#include "LSystemIterator.h"
#include <fstream>

////迭代次数
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

	//初始化原始序列
	basicUnitList=expressionList[0].getBasicUnit();
	simpleString=expressionList[0].getSimpleString();

	//更新标记号,孩子标号
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

	//删除开头结尾的[]
	if (simpleStringF[0]=='[')
		simpleStringF.erase(0,1);
	if (simpleStringF[simpleStringF.length()-1]==']')
		simpleStringF.erase(simpleStringF.length()-1,1);

	//删除除F以外的字母
	for(int i=0;i<simpleStringF.length();i++)
	{
		if ((simpleStringF[i]!='F')&&(simpleStringF[i]!='[')&&(simpleStringF[i]!=']'))
		{
				simpleStringF.erase(i,1);
				i--;
		}
	}

	//删括号
	for(int i=0;i<simpleStringF.length()-1;i++)
	{
		if ((simpleStringF[i]=='[')&&(simpleStringF[i+1]==']'))
		{
			simpleStringF.erase(i,2);
			i--;
		}
	}

	//F的总数量,记录F的地址
	for(int i=0;i<simpleStringF.length();i++)
		if (simpleStringF[i]=='F') 
		{
			addressF.push_back(i);
			FNum++;
		}
}

//做标记
void LSystemIterator::doSign(string &s)
{
	int stack;//栈标记
	sign.clear();

	initSimpleString(s);

	//初始化第一个F的标识符为1
	sign.push_back(1);
	for(int i=1;i<FNum;i++)
	{
		int formerF=i;

		//若F前一个字符为']',则通过括号匹配寻找区块前的F，否则当前F的标记值为前一个标记值+1
		if (simpleStringF[addressF[i]-1]==']')
		{
			stack=-1;
			int tempF=i;
			
			for(int j=addressF[i]-2;j>=0;j--)
			{
				//在循环前，虚拟栈stack=-1，因为栈中有']',在循环中碰到'['stack+1,碰到']'stack-1，若stack为0时说明找到一个完整的区块
				if (simpleStringF[j]==']') stack--;
				else if (simpleStringF[j]=='[') stack++;
				else if (simpleStringF[j]=='F') formerF--;	//记录路过的F

				//if (stack>0) break;

				if ((stack==0) && (simpleStringF[j]=='F'))
					break;
				
			}
		}
		//若F前一个字符为'['，则通过括号匹配找到最近的父类F
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
	cout<<"Do Sign："<<endl;
	cout<<"F number is "<<FNum<<endl;
	cout<<"The sequence sign is："<<endl<<simpleStringF<<endl;

	for(int i=0;i<FNum;i++)
		cout<<sign[i]<<" ";
	cout<<endl;
}

//寻找F的孩子
void LSystemIterator::findChildren(string &s)
{
	simpleStringF="["+s+"]";
	initSimpleString(simpleStringF);
	list<BasicUnit>::iterator basicUnit=basicUnitList.begin();

	cout<<endl;
	cout<<"Find F's children:"<<endl;

	//枚举每个F，寻找他们的孩子
	for(int i=0;i<FNum;i++)
	{
		while(basicUnit->isRule)
			basicUnit++;

		cout<<"The "<<i+1<<" has children:";

		int stack=1;
		int passF=i;	//路过的F
		int count=0;	//统计孩子个数

		//特殊情况，F后紧跟一个F1，则F1为F的唯一孩子
		if (simpleStringF[addressF[i]+1]=='F') 
			{
				cout<<i+2;
				basicUnit->children.push_back(i+2);
				count++;
			}
		else
			for(int j=addressF[i]+1;j<simpleStringF.length();j++)
			{
				if (stack==0) break;	//stack为0意味着F的区间搜索完毕
				else if (simpleStringF[j]==']') stack--;
				else if (simpleStringF[j]=='[') stack++;
				else if (simpleStringF[j]=='F') 
					{
						passF++;

						//父亲的标记值+1=孩子的标记值
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
			int index;	//需要替换的表达式编号
			string paremater;
			list<BasicUnit> tempList;

			//寻找需要替换的表达式编号
			for (index=1;index<expressionList.size();index++)
				if (expressionList[index].expressionName==name)
					break;

			paremater=basicUnit->rule.substr(2,tempExpression.fineNextBracket('(',&basicUnit->rule[2]));

			//解析表达式
			expressionList[index].setParameterValue(paremater);
			expressionList[index].analysis();

			//更新序列(只更新了basicUnitList序列)
			tempList=expressionList[index].getBasicUnit();
			//延伸角度信息到新的序列中，只保存在开头
			tempList.begin()->angleX=basicUnit->angleX;
			tempList.begin()->angleY=basicUnit->angleY;
			tempList.begin()->angleZ=basicUnit->angleZ;
			//更新序列年龄
			for(j=tempList.begin();j!=tempList.end();j++)
				j->birthIteratorTime=iteratorTimes;
			//替换
			basicUnitList.splice(basicUnit,tempList);
			
			
			//删除替换的元素
			basicUnitList.erase(basicUnit--);

			//============================更新简化解析式=========================
			//找到下一个需要替换的位置
			while((simpleString[stringIndex]=='F')||((simpleString[stringIndex]=='[')||(simpleString[stringIndex]==']')))
				stringIndex++;
			//替换
			simpleString.replace(stringIndex,1,expressionList[index].simpleString);
			//stringIndex移动
			stringIndex+=expressionList[index].simpleString.length();					
		}
	}
	
	//output the L-system
	writeLSystemIteratorDetail(times);


	cout<<"=========================================================="<<endl;
	cout<<"IteratorTimes:"<<iteratorTimes++<<endl;
	cout<<"BasicUnit Counts:"<<basicUnitList.size()<<endl;
	cout<<"SimpleString:"<<simpleString<<endl;
		
	//更新标记号,孩子标号
	doSign(simpleString);
	findChildren(simpleString);

	//更新ID值
	int i=1;
	for(basicUnit=basicUnitList.begin();basicUnit!=basicUnitList.end();basicUnit++)
	{
		if (!basicUnit->isRule)
			basicUnit->id=i++;
	}

	//更新父类ID
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