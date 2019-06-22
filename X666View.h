// X666View.h : CX666View 类的接口
//


#pragma once
#include "onfig.h"
#include "Ai_stone.h"
class CX666View : public CView
{
protected: // 仅从序列化创建
	CX666View();
	DECLARE_DYNCREATE(CX666View)

// 属性
public:
	CX666Doc* GetDocument() const;

	Config m_config;//配置
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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

	

// 生成的消息映射函数
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
	// 表示那种棋子，有多种不同图片的棋子
	int m_color;
	// 总共有表示棋子图片的数目
	int num_color;
	int color_witch;
	// 所下的是第几个子
	int num_order;
	// 黑方还是白方
	int color;
public:
	afx_msg void OnCon();

public:
	// 电脑人1
	bool computer1;
public:
	// 电脑人2
	bool computer2;
	// 表示有没有连成六子的标志
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
	// 在文件中的位置
	long m_fine;
public:
	// 有没有必要查找开局库
	bool flat_fine;
public:
	// 要在空间中查找的长度
	long fine_legth;
public:
	// 查找开局库
	void fine_math(int &x1,int &y1,int &x2,int &y2);
public:
	void fine_mathblack(int &x1,int &y1,int &x2,int &y2);
public:
	afx_msg void OnBlack();
};

#ifndef _DEBUG  // X666View.cpp 中的调试版本
inline CX666Doc* CX666View::GetDocument() const
   { return reinterpret_cast<CX666Doc*>(m_pDocument); }
#endif

