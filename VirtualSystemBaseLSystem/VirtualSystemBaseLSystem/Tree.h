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

	//基本单元序列
	list<BasicUnit> basicUnitList;
	string simpleStringF;
	list<BasicUnit>::iterator addressF;

	GLdouble leafPoints[50][3];			//叶子绘制点数组
	GLint leafPonitsCount;				//叶子绘制点数目

	GLuint texture[1];					//创建纹理

	void drawTree();
	void drawSegment(double radius,double length);
	void drawLeaf(GLdouble scale,GLdouble position);
	void setInformation();
	void loadTextures(char *fileName);	//load Texture
	void loadLeafPoints(string fileName);
};

