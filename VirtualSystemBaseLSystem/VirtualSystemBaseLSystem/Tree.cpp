#include "stdafx.h"
#include "Tree.h"

int color[2][3]={142,73,35,
				242,145,37};
double  staticScle=0.035;

//Tree::Tree(string s,list<BasicUnit> list)
//{
//	simpleStringF=s;
//	basicUnitList=list;
//
//	//ɾ��ǰ������
//	if (simpleStringF[0]=='[')
//	{
//		simpleStringF.erase(0,1);
//		simpleStringF.erase(simpleStringF.length()-1,1);
//	}
//
//	//ɾ����ʽ
//	for( addressF=basicUnitList.begin();addressF!=basicUnitList.end();addressF++)
//	{
//		if (addressF->isRule)
//			basicUnitList.erase(addressF--);
//	}
//
//	
//
//}
//Tree::Tree(string s)
//{
//	simpleStringF=s;
//	//ɾ��ǰ������
//	if (simpleStringF[0]=='[')
//	{
//		simpleStringF.erase(0,1);
//		simpleStringF.erase(simpleStringF.length()-1,1);
//	}
//}
Tree::Tree()
{
	loadTextures("Data/Draw/skin2.bmp");
	loadLeafPoints("leafPoints");
}
Tree::~Tree(void)
{
}

void Tree::loadTextures(char *fileName)
{
	FILE *file=NULL;
	AUX_RGBImageRec *textureImage[1];	//��������ռ�

	memset(textureImage,0,sizeof(void *)*1);

	//��ȡ�����ļ�
	file=fopen(fileName,"r");
	if (file)
	{
		textureImage[0]=auxDIBImageLoadA(fileName);
		fclose(file);
	}
	else printf("Read texture failed!");

	glGenTextures(1,&texture[0]);				//��������
	glBindTexture(GL_TEXTURE_2D, texture[0]);	//ѡ��ʹ������
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//��������ɫ����

	glBindTexture(GL_TEXTURE_2D,texture[0]);//ѡ��ʹ������
	glEnable(GL_TEXTURE_2D);	//open

	//�ͷ�����
	if (textureImage[0])
	{
		if (textureImage[0]->data)
			free(textureImage[0]->data);
		free(textureImage[0]);
	}
}

void Tree::loadLeafPoints(string fileName)
{
	int i=0;
	ifstream readFile("data/draw/"+fileName+".txt");

	readFile>>leafPonitsCount;

	if(readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile>>leafPoints[i][0]>>leafPoints[i][1]>>leafPoints[i][2];
			i++;
		}
	}
	readFile.close();
}

void Tree::setInformation()
{
	int n;

	simpleStringF="";
	basicUnitList.clear();

	BasicUnit basicUnit;

	//��ȡ������Ϣ
	ifstream readFile("Data/writeBasicUnitListWithTreeDraw.txt");

	readFile>>simpleStringF;

	readFile>>n;
	
	for(int i=0;i<n;i++)
	{		
		readFile>>basicUnit.angleX;
		readFile>>basicUnit.angleY;
		readFile>>basicUnit.angleZ;
		readFile>>basicUnit.length;
		readFile>>basicUnit.redius;
		readFile>>basicUnit.leafAmount;

		for(int j=0;j<basicUnit.leafAmount;j++)
		{
			double temp;
			readFile>>temp;
			basicUnit.leafArea.push_back(temp);
		}

		basicUnitList.push_back(basicUnit);
	}
	

	readFile.close();
	

	//ɾ��ǰ������
	if (simpleStringF[0]=='[')
	{
		simpleStringF.erase(0,1);
		simpleStringF.erase(simpleStringF.length()-1,1);
	}

	{
		double size=0.035;
		list<BasicUnit>::iterator itor=basicUnitList.begin();
		while(itor!=basicUnitList.end())
		{
			if (itor->leafAmount>0)
			{
				itor->leafArea[0]=size;
				itor->leafArea[1]=size;
				size-=0.001;
			}
			itor++;
		}
	}

	////ɾ����ʽ
	//for( addressF=basicUnitList.begin();addressF!=basicUnitList.end();addressF++)
	//{
	//	if (addressF->isRule)
	//		basicUnitList.erase(addressF--);
	//}

	if(basicUnitList.size()<161)
		return;
	//Change the Basic Information
	list<BasicUnit>::iterator itor=basicUnitList.begin();

	//trunk
	for(int i=0;i<9;i++)
	{
		itor->redius=1.3;
		itor++;
	}
	//segment
	for(int i=0;i<56;i++)
	{
		itor->redius=0.5;
		//itor->leafAmount=2;
		itor++;
	}
	//trunk
	for(int i=0;i<3;i++)
	{
		itor->redius=1.0;
		itor++;
	}
	//segment
	for(int i=0;i<42;i++)
	{
		itor->redius=0.5;
		//itor->leafAmount=2;
		itor++;
	}
	//trunk
	for(int i=0;i<3;i++)
	{
		itor->redius=0.81;
		itor++;
	}
	//segment
	for(int i=0;i<28;i++)
	{
		itor->redius=0.5;
		//itor->leafAmount=2;
		itor++;
	}
	//trunk
	for(int i=0;i<3;i++)
	{
		itor->redius=0.51;
		itor++;
	}
	//segment
	for(int i=0;i<14;i++)
	{
		itor->redius=0.5;
		//itor->leafAmount=2;
		itor++;
	}
	//trunk
	for(int i=0;i<3;i++)
	{
		itor->redius=0.441;
		itor++;
	}
}

void Tree::drawLeaf(GLdouble scale,GLdouble position)
{
	glDisable(GL_TEXTURE_2D);	//����Ҷ��ʱ��ʱ�ر�������ͼ
	glColor3ub(14,82,34);
	
	scale=0.015;	//size in
	//scale=1.015;	//size in
	//scale-=0.5;
	position-=0.6;
	glPushMatrix();


	//������ϵ�ƶ���֦������
	glTranslatef(0.0,0.0,position);	
		
	//��תҶƬ���򣬸�����ʵ
	glRotatef(50,0.0,0.0,1);

	//��СҶ��
	glScalef(scale,scale,scale);

	//�����Ҷ��ǰ��������ת
	glRotatef(60,1.0,0,0);
	
	////////////////////////////////΢��-Left/////////////////////////////////
	glPushMatrix();
	//��΢�ƶ�Ҷ�ӵĳ�ʼ����
	//glTranslatef(0.4,0,0);

	glPolygonMode(GL_FRONT,GL_FILL);//�����ɫ

	//��Ҷ��
	glBegin(GL_POLYGON);
		for (int i=0;i<leafPonitsCount;i++)
			glVertex3f(leafPoints[i][0],leafPoints[i][1],leafPoints[i][2]);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////////////////////////

	//���ұ�Ҷ��ǰ��������ת
	glRotatef(120,-1.0,0,0);
	////////////////////////////////΢��-Right/////////////////////////////////
	glPushMatrix();
	//��΢�ƶ�Ҷ�ӵĳ�ʼ����
	//glTranslatef(0.4,0,0);

	glPolygonMode(GL_FRONT,GL_FILL);//�����ɫ

	//��Ҷ��
	glBegin(GL_POLYGON);
		for (int i=0;i<leafPonitsCount;i++)
			glVertex3f(leafPoints[i][0],leafPoints[i][1],leafPoints[i][2]);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////////////////////////


	glPopMatrix();

	glEnable(GL_TEXTURE_2D);	//��������ͼ
}

void Tree::drawSegment(double radius,double length)
{
	GLUquadricObj *cylinder=gluNewQuadric();
	
	//��ʼ��Բ����
	gluQuadricDrawStyle(cylinder,GLU_FILL);
	gluQuadricNormals(cylinder,GL_SMOOTH);
	gluQuadricOrientation(cylinder,GLU_INSIDE);
	gluQuadricTexture(cylinder,GL_TRUE);			//ʹ������

	radius*=0.15;

	double temp=0.5;

	//gluCylinder(cylinder,radius,radius,length,4,3.0);
	gluCylinder(cylinder,0.15,0.15,temp,4,3.0);

	gluDeleteQuadric(cylinder);

	//glTranslatef(0.0,0.0,length);	
	glTranslatef(0.0,0.0,temp);	
}

void Tree::drawTree()
{
	int ii=0,countF=0;
	addressF=basicUnitList.begin();
	
	//FF[F[F]F]FFF
	glRotatef(90.0,-1.0,0.0,0.0);

	for(int i=0;i<simpleStringF.length();i++)
	{
		if (simpleStringF[i]=='[')
		{
			glPushMatrix();						
		}
		else if (simpleStringF[i]==']')
		{
			glPopMatrix();
		}
		else //simpleStringF[i]=='F'
		{
			countF++;
			//���������ɫ
			glColor3ub(color[countF%2][0],color[countF%2][1],color[countF%2][2]);
					
			if (addressF->angleZ!=0)
				glRotatef(addressF->angleZ,0.0,0.0,addressF->angleZ);
			if (addressF->angleY!=0)
				glRotatef(addressF->angleY,0.0,addressF->angleY,0.0);
			if (addressF->angleX!=0)
				glRotatef(addressF->angleX,addressF->angleX,0.0,0.0);

			drawSegment(addressF->redius,addressF->length);
			
			if (addressF->leafAmount)
			{
					drawLeaf(addressF->leafArea[0],addressF->length);
					drawLeaf(addressF->leafArea[0],addressF->length-0.35);
			}

			addressF++;
		}
	}

	//drawLeaf(1,1);
}