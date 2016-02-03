
// VirtualSystemBaseLSystemView.h : CVirtualSystemBaseLSystemView ��Ľӿ�
//

#pragma once
#include "VirtualSystemBaseLSystemDoc.h"

#include "Controller.h"

class CVirtualSystemBaseLSystemView : public CView
{
protected: // �������л�����
	CVirtualSystemBaseLSystemView();
	DECLARE_DYNCREATE(CVirtualSystemBaseLSystemView)

// ����
public:
	CVirtualSystemBaseLSystemDoc* GetDocument() const;

// ����
public:
	//NEW
	HGLRC m_hRC;    //Rendering Context��ɫ������
    CDC* m_pDC;        //Device Context�豸������
    BOOL InitializeOpenGL();    //Initialize OpenGL
    BOOL SetupPixelFormat();    //Set up the Pixel Format

	GLint mouseX,mouseY;				//��¼���λ��
	GLint rotateX,rotateY,rotateAngle;	//��¼��ת����ͽǶȣ�����������
	double tFovy;						// ��gluPerspective��ʹ��(��OnMouseWheel��ʹ��)

	Controller controller;
	Tree tree;
	void RenderScene();            //Render the Scene
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CVirtualSystemBaseLSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // VirtualSystemBaseLSystemView.cpp �еĵ��԰汾
inline CVirtualSystemBaseLSystemDoc* CVirtualSystemBaseLSystemView::GetDocument() const
   { return reinterpret_cast<CVirtualSystemBaseLSystemDoc*>(m_pDocument); }
#endif

