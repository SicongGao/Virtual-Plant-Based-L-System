#pragma once
#include "Expression.h"

class Segment
{
public:
	Segment(BasicUnit basicUnit);
	~Segment(void);

	GLdouble baseRadius;	//枝干的下底半径
	GLdouble topRadius;		//枝干的上顶半径
	GLdouble length;		//枝干的长度

	GLdouble angleX;		//枝条与主干角度
	GLdouble angleY;
	GLdouble angleZ;

	GLUquadricObj *cylinder;

	//设置长度和上下底半径
	void setLength(GLdouble l);
	void setBaseRadius(GLdouble r);
	void setTopRadius(GLdouble r);

	void draw();
};

