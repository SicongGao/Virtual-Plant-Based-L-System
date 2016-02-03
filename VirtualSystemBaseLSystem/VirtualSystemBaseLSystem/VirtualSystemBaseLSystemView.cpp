
// VirtualSystemBaseLSystemView.cpp : CVirtualSystemBaseLSystemView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "VirtualSystemBaseLSystem.h"
#endif

#include "VirtualSystemBaseLSystemDoc.h"
#include "VirtualSystemBaseLSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
// CVirtualSystemBaseLSystemView

IMPLEMENT_DYNCREATE(CVirtualSystemBaseLSystemView, CView)

BEGIN_MESSAGE_MAP(CVirtualSystemBaseLSystemView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CVirtualSystemBaseLSystemView 构造/析构

CVirtualSystemBaseLSystemView::CVirtualSystemBaseLSystemView()
{
	// TODO: 在此处添加构造代码

	rotateX=0;
	rotateY=0;
	rotateAngle=0;//记录旋转方向和角度，用于鼠标控制

    tFovy = 45.0;

	//初始化树
	tree=Tree();

	//clear
	ofstream out("Data/writeEnergyDetail.txt");
	ofstream out1("Data/writeEnergySatatistic.txt");	
	ofstream out2("Data/writeBasicUnitListWithTreeDraw.txt");
	ofstream out3("Data/writeSegmentLeafRootEnergy.txt");
}

CVirtualSystemBaseLSystemView::~CVirtualSystemBaseLSystemView()
{
	/*ofstream writeFile("Data/IteratorTimes.txt");

	writeFile<<0<<"\n";
	
	writeFile.close();*/

	ofstream writeFile1("Data/BasicUnitInfomation.txt");

	if(writeFile1.is_open())
	{
		for(int i=0;i<6;i++)
			writeFile1<<0<<"\n";
	}
	
	writeFile1.close();
}

BOOL CVirtualSystemBaseLSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CVirtualSystemBaseLSystemView 绘制



void CVirtualSystemBaseLSystemView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVirtualSystemBaseLSystemView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVirtualSystemBaseLSystemView 诊断

#ifdef _DEBUG
void CVirtualSystemBaseLSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CVirtualSystemBaseLSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVirtualSystemBaseLSystemDoc* CVirtualSystemBaseLSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVirtualSystemBaseLSystemDoc)));
	return (CVirtualSystemBaseLSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CVirtualSystemBaseLSystemView 消息处理程序


int CVirtualSystemBaseLSystemView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	InitializeOpenGL();

	return 0;
}


void CVirtualSystemBaseLSystemView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	 //Make the RC non-current
    if(::wglMakeCurrent (0,0) == FALSE)
    {
        MessageBox(_T("Could not make RC non-current"));
    }
 
    //Delete the rendering context
    if(::wglDeleteContext (m_hRC)==FALSE)
    {
        MessageBox(_T("Could not delete RC"));
    }
    //Delete the DC
    if(m_pDC)
    {
        delete m_pDC;
    }
    //Set it to NULL
    m_pDC = NULL;
}


BOOL CVirtualSystemBaseLSystemView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


void CVirtualSystemBaseLSystemView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if ( 0 >= cx || 0 >= cy )
	 {
		  return;
	 }

	glViewport(0,0,(GLsizei)cx,(GLsizei)cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(GLfloat)cx/(GLfloat)cy,1.0,50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
}


void CVirtualSystemBaseLSystemView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RenderScene();
}

void CVirtualSystemBaseLSystemView::OnDraw(CDC* /*pDC*/)
{
	CVirtualSystemBaseLSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	RenderScene();
}

BOOL CVirtualSystemBaseLSystemView::SetupPixelFormat()
{
 static PIXELFORMATDESCRIPTOR pfd =
 {
      sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
      1,                              // version number
      PFD_DRAW_TO_WINDOW |            // support window
      PFD_SUPPORT_OPENGL |            // support OpenGL
      PFD_DOUBLEBUFFER,                // double buffered
      PFD_TYPE_RGBA,                  // RGBA type
      24,                             // 24-bit color depth
      0, 0, 0, 0, 0, 0,               // color bits ignored
      0,                              // no alpha buffer
      0,                              // shift bit ignored
      0,                              // no accumulation buffer
      0, 0, 0, 0,                     // accum bits ignored
      16,                             // 16-bit z-buffer
      0,                              // no stencil buffer
      0,                              // no auxiliary buffer
      PFD_MAIN_PLANE,                 // main layer
      0,                              // reserved
      0, 0, 0                         // layer masks ignored
 };
 int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
 if ( m_nPixelFormat == 0 )
 {
      return FALSE;
 }
 if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
 {
      return FALSE;
 }
 return TRUE;
}

//初始化opengl绘制
BOOL CVirtualSystemBaseLSystemView::InitializeOpenGL()
{
    //Get a DC for the Client Area
    m_pDC = new CClientDC(this);
    //Failure to Get DC
    if(m_pDC == NULL)
		return FALSE;
 
    //Failure to set the pixel format
    if(!SetupPixelFormat())
		return FALSE;

	//Create Rendering Context
	m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());
	//Failure to Create Rendering Context
	if(m_hRC == 0)
		return FALSE;
	 //Make the RC Current
	 if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
		 return FALSE;
	    
	//OpenGL初始化设置
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_SMOOTH);					// 启用阴影平滑
	glClearDepth(1.0f);							// 设置深度缓存
	glEnable(GL_DEPTH_TEST);					// 启用深度测试
	glDepthFunc(GL_LEQUAL);						// 所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 告诉系统对透视进行修正
	glEnable(GL_AUTO_NORMAL); 
	glEnable(GL_NORMALIZE); 

    gluOrtho2D(0.0,200.0,0.0,150.0);

	//定时刷新窗口
	SetTimer(1,1,NULL);

	return TRUE;
}

void testPaper()
{
	//GLUquadricObj *cylinder=gluNewQuadric();
	//
	////初始化圆柱体
	//gluQuadricDrawStyle(cylinder,GLU_FILL);
	//gluQuadricNormals(cylinder,GL_SMOOTH);
	//gluQuadricOrientation(cylinder,GLU_INSIDE);
	//gluQuadricTexture(cylinder,GL_TRUE);			//使用纹理


	//glColor3ub(142,82,34);
	//glRotatef(90.0,-1.0,0.0,0.0);


	////gluCylinder(cylinder,radius,radius,length,4,3.0);
	//gluCylinder(cylinder,0.35,0.35,4.6,40,30.0);
	//

	//gluDeleteQuadric(cylinder);

	////glTranslatef(0.0,0.0,length);	
	////glTranslatef(0.0,0.0,temp);	

	GLdouble leafPoints[50][3];			//叶子绘制点数组
	GLint leafPonitsCount;				//叶子绘制点数目

	int i=0;
	ifstream readFile("data/draw/leafPoints.txt");

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

	glColor3ub(14,82,34);
	//scale=0.035;	//size in
	//scale-=0.5;

	glPushMatrix();


	//把坐标系移动到枝条顶端
	//glTranslatef(0.0,0.0,-0.15);	
		
	//旋转叶片方向，更加真实
	glRotatef(50,0.0,0.0,1);

	//缩小叶子
	//glScalef(scale,scale,scale);

	//画左边叶子前，进行旋转
	glRotatef(60,1.0,0,0);
	
	////////////////////////////////微调-Left/////////////////////////////////
	glPushMatrix();
	//稍微移动叶子的初始距离
	//glTranslatef(0.4,0,0);

	glPolygonMode(GL_FRONT,GL_FILL);//填充颜色

	//画叶子
	glBegin(GL_POLYGON);
		for (int i=0;i<leafPonitsCount;i++)
			glVertex3f(leafPoints[i][0],leafPoints[i][1],leafPoints[i][2]);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////////////////////////



}

void CVirtualSystemBaseLSystemView::RenderScene()
{
	// Clear out the color & depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除屏幕和深度缓存
	glLoadIdentity();									// 重置当前的模型观察矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0,-5.0,-25.0);

	glRotatef(rotateAngle,rotateX,rotateY,0);	//用于鼠标控制旋转

	tree.setInformation();
	tree.drawTree();
	//testPaper();

	SwapBuffers( m_pDC->GetSafeHdc() );
}

BOOL CVirtualSystemBaseLSystemView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int tWheelCount = zDelta / 120;
    if(tWheelCount > 0) 
        tFovy += 1.0;
    else if(tWheelCount < 0) 
        tFovy -= 1.0;
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                                            // 此处尤其不可少glLoadIdentity()
    gluPerspective(tFovy, 1, 0.1, 1000.0);                        // 注意zNear,zFar的取值
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return TRUE;
}


void CVirtualSystemBaseLSystemView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnMouseMove(nFlags, point);

	if(nFlags & (MK_LBUTTON == TRUE))
	{
		if ((point.x-mouseX)>0)	//鼠标向右移动，即逆时针旋转
			rotateY=-1;
		else if ((point.x-mouseX)<0) //否则顺时针旋转
			rotateY=1;		

		rotateAngle+=2.5;		//增加旋转角度
	}
	
	mouseX=point.x;
	mouseY=point.y;
}
