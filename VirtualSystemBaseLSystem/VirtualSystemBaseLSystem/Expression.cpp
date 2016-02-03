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
	
	//��¼���ʽ����
	expressionName=s[0];

	//�򻯽���ʽ
	setSimpleString(expression);

	index=fineNextBracket('(',&s[2]);	//index�ǻ�þ����¸����ŵĳ���
	string ss=s.substr(2,index);


	//��ȡ�������еĲ���
	parameterName=splitString(&ss[0],",");

/*  Expression����
	setParameterValue("3,2");
	analysis();*/
}


Expression::~Expression(void)
{
}

//��������ַ�name������ֵ
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

//�ָ��ַ���.���ؽ��Ϊ�ַ���
vector<string> Expression::splitString(char *s,const char *split)
{
	vector<string> result;
	char *p;
	p=strtok(s,split);   //�ָ��
	
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

//����Ҫƥ������ţ���(������[����,���ַ���������ʼλ�ã�������һ�����ŵ���Ծ���
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



//�������ʽ,����һ��BasicUnit���͵�vector���洢ȫ����������Ԫ��Ϣ
void Expression::analysis()
{
	string s=expression;
	
	//�������
	basicUnitList.clear();
	
	for(int i=0;i<s.length();i++)
		if((s[i]>='A')&&(s[i]<='Z')&&(s[i]!='L'))	//�ҵ�һ��������Ԫ
		{
			BasicUnit tempBasicUnit={1,1,0,0,0,"",false,0,0,0,1};
			
			//��ǰѰ����������
			for(int j=i-1;j>=0;j--)
			{
				if( (s[j]=='F')	|| (s[j]==']') )	//�ҵ���һ��������Ԫ������
					break;
				else if ( (s[j]=='/')||(s[j]=='\\')||(s[j]=='+')||( (s[j]=='-')&&(s[j+1]=='(') )
						||(s[j]=='&')||(s[j]=='^') ||(s[j]=='L') )
				{
					//��������ڵ�ֵ
					int k=fineNextBracket('(',&s[j+2]);
					double value=analysisBracket(s.substr(j+2,k));

					if (s[j]=='L') tempBasicUnit.leafAmount=value;
					else if (s[j]=='+') tempBasicUnit.angleX=-abs(value);
					else if (s[j]=='-') tempBasicUnit.angleX=abs(value);
					else if (s[j]=='&') tempBasicUnit.angleY=-abs(value);
					else if (s[j]=='^') tempBasicUnit.angleY=abs(value);
					else if (s[j]=='/') tempBasicUnit.angleZ=abs(value);
					else if (s[j]=='\\') tempBasicUnit.angleZ=-abs(value);
					
					//��ʼÿ��ҶƬ�����Ϊ0.5
					for(int v=0;v<tempBasicUnit.leafAmount;v++)
						tempBasicUnit.leafArea.push_back(0.5);	
				}
			}

			//if (s[i]=='F')
			//{
			//	 //���Ѱ����������
			//	int k=fineNextBracket('(',&s[i+2]);
			//	tempBasicUnit.length=analysisBracket(s.substr(i+2,k));
			//}
			if (s[i]!='F') //�ѱ��ʽ�洢����
			{
				/*int k=fineNextBracket('(',&s[i]);

				//string tempString=s.substr(i+2,k-2);	//����ַ���
				//vector<string> temp=splitString(&tempString[0],",");	//�����洢��temp

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
	
//ȡ������������Ԫ
list<BasicUnit> Expression::getBasicUnit()
{
	return basicUnitList;
}	

//���������ڵ��ַ��������з�������������ʽ���
double Expression::analysisBracket(string s)
{
	int p=0;
	double result=0;
	string tempS(s);
	vector<string> numberString=splitString(&tempS[0],"*/");
	double number[10];

	//���ʽ�л�����������ַ�������������֣��ֲ���ȡ����
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

	//���ݱ��ʽ�е���������м��㣬��ʱ֧�֡���/
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