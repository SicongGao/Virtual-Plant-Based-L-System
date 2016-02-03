#pragma once
#include "Expression.h"

class Segment
{
public:
	Segment(BasicUnit basicUnit);
	~Segment(void);

	GLdouble baseRadius;	//֦�ɵ��µװ뾶
	GLdouble topRadius;		//֦�ɵ��϶��뾶
	GLdouble length;		//֦�ɵĳ���

	GLdouble angleX;		//֦�������ɽǶ�
	GLdouble angleY;
	GLdouble angleZ;

	GLUquadricObj *cylinder;

	//���ó��Ⱥ����µװ뾶
	void setLength(GLdouble l);
	void setBaseRadius(GLdouble r);
	void setTopRadius(GLdouble r);

	void draw();
};

