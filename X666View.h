// X666View.h : CX666View ��Ľӿ�
//


#pragma once
#include "onfig.h"
#include "Ai_stone.h"
class CX666View : public CView
{
protected: // �������л�����
	CX666View();
	DECLARE_DYNCREATE(CX666View)

// ����
public:
	CX666Doc* GetDocument() const;

	Config m_config;//����
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CX666View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HBRUSH m_brush;
	POINT map_point;
	Ai_stone Ai;

	

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// ��ʾ�������ӣ��ж��ֲ�ͬͼƬ������
	int m_color;
	// �ܹ��б�ʾ����ͼƬ����Ŀ
	int num_color;
	int color_witch;
	// ���µ��ǵڼ�����
	int num_order;
	// �ڷ����ǰ׷�
	int color;
public:
	afx_msg void OnCon();

public:
	// ������1
	bool computer1;
public:
	// ������2
	bool computer2;
	// ��ʾ��û���������ӵı�־
	bool flat_six;
	
public:
	bool flat_draw;
public:
	afx_msg void OnNew();
public:
	afx_msg void OnBack();
public:
	afx_msg void OnFront();
public:
	afx_msg void OnSave();
public:
	afx_msg void OnSaveAs();
public:
	afx_msg void OnOpen();
public:
	afx_msg void OnFrontall();
public:
	afx_msg void OnBackall();
public:
	afx_msg void OnIn();
public:
	afx_msg void OnInputchunk();
public:
	// ���ļ��е�λ��
	long m_fine;
public:
	// ��û�б�Ҫ���ҿ��ֿ�
	bool flat_fine;
public:
	// Ҫ�ڿռ��в��ҵĳ���
	long fine_legth;
public:
	// ���ҿ��ֿ�
	void fine_math(int &x1,int &y1,int &x2,int &y2);
public:
	void fine_mathblack(int &x1,int &y1,int &x2,int &y2);
public:
	afx_msg void OnBlack();
};

#ifndef _DEBUG  // X666View.cpp �еĵ��԰汾
inline CX666Doc* CX666View::GetDocument() const
   { return reinterpret_cast<CX666Doc*>(m_pDocument); }
#endif

