#include "stdafx.h"
#include "Expression.h"
#include <sstream>

Expression::Expression(string s)
{
	string temp;
	int index;
	
	for(index=1;index<s.length();index++)
		if ((s[index-1]=='>')||(s[index-1]=='@')) break;
	expression=s.substr(index,s.length());
	
	//记录表达式名称
	expressionName=s[0];

	//简化解析式
	setSimpleString(expression);

	index=fineNextBracket('(',&s[2]);	//index是获得距离下个括号的长度
	string ss=s.substr(2,index);


	//提取规则名中的参数
	parameterName=splitString(&ss[0],",");

/*  Expression步骤
	setParameterValue("3,2");
	analysis();*/
}


Expression::~Expression(void)
{
}

//传入参数字符name，返回值
double Expression::getParameterValue(string name)
{
	int count=0;

	while (parameterName.at(count)!=name)
		count++;

	return parameterValue.at(count);
}

void Expression::setParameterValue(string s)
{
	vector<string> value=splitString(&s[0],",");
	string p;
	for(int i=0;i<value.size();i++)
	{
		p=value.at(i);
		parameterValue.push_back(atof(&p[0]));
	}
}

//分割字符串.返回结果为字符串
vector<string> Expression::splitString(char *s,const char *split)
{
	vector<string> result;
	char *p;
	p=strtok(s,split);   //分割方法
	
	int count=0;
	while(p)
	{
		result.push_back(p);  
		p=strtok(NULL,split);
	}

	//for(int i=0;i<result.size();i++)
	//	cout<<result.at(i)<<endl;

	return result;
}

//传入要匹配的括号（‘(’，‘[’）,和字符串括号起始位置，返回下一个括号的相对距离
int Expression::fineNextBracket(char bracket,string s)
{
	char nextBracket;
	int index=1;

	if (bracket=='(')
		nextBracket=')';
	else nextBracket=']';

	for(index=1;index<s.length();index++)
	{
		if (s[index]==nextBracket)
			break;
	}

	return index;
}



//解析表达式,返回一个BasicUnit类型的vector，存储全部的生长单元信息
void Expression::analysis()
{
	string s=expression;
	
	//清空容器
	basicUnitList.clear();
	
	for(int i=0;i<s.length();i++)
		if((s[i]>='A')&&(s[i]<='Z')&&(s[i]!='L'))	//找到一个生长单元
		{
			BasicUnit tempBasicUnit={1,1,0,0,0,"",false,0,0,0,1};
			
			//向前寻找自身属性
			for(int j=i-1;j>=0;j--)
			{
				if( (s[j]=='F')	|| (s[j]==']') )	//找到上一个基本单元，跳出
					break;
				else if ( (s[j]=='/')||(s[j]=='\\')||(s[j]=='+')||( (s[j]=='-')&&(s[j+1]=='(') )
						||(s[j]=='&')||(s[j]=='^') ||(s[j]=='L') )
				{
					//获得括号内的值
					int k=fineNextBracket('(',&s[j+2]);
					double value=analysisBracket(s.substr(j+2,k));

					if (s[j]=='L') tempBasicUnit.leafAmount=value;
					else if (s[j]=='+') tempBasicUnit.angleX=-abs(value);
					else if (s[j]=='-') tempBasicUnit.angleX=abs(value);
					else if (s[j]=='&') tempBasicUnit.angleY=-abs(value);
					else if (s[j]=='^') tempBasicUnit.angleY=abs(value);
					else if (s[j]=='/') tempBasicUnit.angleZ=abs(value);
					else if (s[j]=='\\') tempBasicUnit.angleZ=-abs(value);
					
					//初始每个叶片的面积为0.5
					for(int v=0;v<tempBasicUnit.leafAmount;v++)
						tempBasicUnit.leafArea.push_back(0.5);	
				}
			}

			//if (s[i]=='F')
			//{
			//	 //向后寻找自身属性
			//	int k=fineNextBracket('(',&s[i+2]);
			//	tempBasicUnit.length=analysisBracket(s.substr(i+2,k));
			//}
			if (s[i]!='F') //把表达式存储起来
			{
				/*int k=fineNextBracket('(',&s[i]);

				//string tempString=s.substr(i+2,k-2);	//组合字符串
				//vector<string> temp=splitString(&tempString[0],",");	//参数存储到temp

				//tempString=s[i];
				//tempString.append("(");
				//for(int k=0;k<temp.size();k++)
				//{
				//	ostringstream os;

				//	os<<analysisBracket(temp[k]);

				//	tempString.append(os.str());
				//	tempString.append(",");
				//}

				//tempString[tempString.length()-1]=')';*/
				string tempString;

				tempString=s.substr(i,fineNextBracket(')',&s[i]));
				
				tempBasicUnit.rule=tempString;
				tempBasicUnit.isRule=true;
			}
			
			basicUnitList.push_back(tempBasicUnit);
		}
}
	
//取得所有生长单元
list<BasicUnit> Expression::getBasicUnit()
{
	return basicUnitList;
}	

//传入括号内的字符串，进行分析，返回算术式结果
double Expression::analysisBracket(string s)
{
	int p=0;
	double result=0;
	string tempS(s);
	vector<string> numberString=splitString(&tempS[0],"*/");
	double number[10];

	//表达式中或许包含参数字符，或许包含数字，分布提取出来
	for(int i=0;i<numberString.size();i++)
	{
		string temp=numberString[i];
		
		if (((temp[0]>='0')&&(temp[0]<='9'))||(temp[0]=='-'))
			number[i]=atof(&temp[0]);
		else 
		{
			int count=0;
			while (parameterName[count]!=temp)
				count++;
			number[i]=parameterValue[count];
		}
	}

	//根据表达式中的运算符进行计算，暂时支持×，/
	for(int i=0;i<s.length();i++)
	{
		if ((s[i]=='*'))
		{
			result=number[p]*number[p+1];
			number[p+1]=result;
			p++;
		}
		if ((s[i]=='/'))
		{
			result=number[p]/number[p+1];
			number[p+1]=result;
			p++;
		}
	}

	result=number[p];
	return result;
}

void Expression::setSimpleString(string s)
{
	string temp;
	
	for(int i=0;i<s.length();i++)
		if ((s[i]=='[')||(s[i]==']')||((s[i]>='A')&&(s[i]<='Z')&&(s[i]!='L')))
		{
			temp.append(s.substr(i,1));
		}

		simpleString=temp;
}

string Expression::getSimpleString()
{
	return simpleString;
}