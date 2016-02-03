#include "stdafx.h"
#include "Segment.h"

Segment::Segment(BasicUnit basicUnit)
{
	length=basicUnit.length;
	angleX=basicUnit.angleX;
	angleY=basicUnit.angleY;
	angleZ=basicUnit.angleZ;
	baseRadius=0.3;
	topRadius=0.3;

	cylinder=gluNewQuadric();

	//生成随机颜色
	glColor3ub(rand()%255,rand()%255,rand()%255);
	//初始化圆柱体
	gluQuadricDrawStyle(cylinder,GLU_FILL);
	gluQuadricNormals(cylinder,GL_SMOOTH);
	gluQuadricOrientation(cylinder,GLU_INSIDE);
	//gluQuadricTexture(cylinder,GL_TRUE);			//使用纹理
}


Segment::~Segment(void)
{
}

void Segment::setLength(GLdouble l)
{
	length=l;
}

void Segment::setBaseRadius(GLdouble r)
{
	baseRadius=r;
}

void Segment::setTopRadius(GLdouble r)
{
	topRadius=r;
}


//绘制
void Segment::draw(void)
{
	glColor3ub(64,58,34);
	gluCylinder(cylinder,baseRadius,topRadius,length,60,32.0);
}