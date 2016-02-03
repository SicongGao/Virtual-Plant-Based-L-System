#pragma once
#include "LSystemIterator.h"
#include "stdafx.h"

class Tree
{
public:
	Tree(string s,list<BasicUnit> list);
	Tree(string s);
	Tree();
	~Tree(void);

	//������Ԫ����
	list<BasicUnit> basicUnitList;
	string simpleStringF;
	list<BasicUnit>::iterator addressF;

	GLdouble leafPoints[50][3];			//Ҷ�ӻ��Ƶ�����
	GLint leafPonitsCount;				//Ҷ�ӻ��Ƶ���Ŀ

	GLuint texture[1];					//��������

	void drawTree();
	void drawSegment(double radius,double length);
	void drawLeaf(GLdouble scale,GLdouble position);
	void setInformation();
	void loadTextures(char *fileName);	//load Texture
	void loadLeafPoints(string fileName);
};

