
// VirtualSystemBaseLSystemView.h : CVirtualSystemBaseLSystemView 类的接口
//

#pragma once
#include "VirtualSystemBaseLSystemDoc.h"

#include "Controller.h"

class CVirtualSystemBaseLSystemView : public CView
{
protected: // 仅从序列化创建
	CVirtualSystemBaseLSystemView();
	DECLARE_DYNCREATE(CVirtualSystemBaseLSystemView)

// 特性
public:
	CVirtualSystemBaseLSystemDoc* GetDocument() const;

// 操作
public:
	//NEW
	HGLRC m_hRC;    //Rendering Context着色描述表
    CDC* m_pDC;        //Device Context设备描述表
    BOOL InitializeOpenGL();    //Initialize OpenGL
    BOOL SetupPixelFormat();    //Set up the Pixel Format

	GLint mouseX,mouseY;				//记录鼠标位置
	GLint rotateX,rotateY,rotateAngle;	//记录旋转方向和角度，用于鼠标控制
	double tFovy;						// 在gluPerspective中使用(在OnMouseWheel中使用)

	Controller controller;
	Tree tree;
	void RenderScene();            //Render the Scene
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CVirtualSystemBaseLSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // VirtualSystemBaseLSystemView.cpp 中的调试版本
inline CVirtualSystemBaseLSystemDoc* CVirtualSystemBaseLSystemView::GetDocument() const
   { return reinterpret_cast<CVirtualSystemBaseLSystemDoc*>(m_pDocument); }
#endif

