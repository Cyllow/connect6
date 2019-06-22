// X666View.cpp : CX666View 类的实现
//

#include "stdafx.h"
#include "afxdlgs.h"
#include "X666.h"
#include "mutual.h"
#include "X666Doc.h"
#include "X666View.h"
#include "onfig.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CX666View
struct Chunk
{
	int x;
	int y;
	int length;
};
IMPLEMENT_DYNCREATE(CX666View, CView)

BEGIN_MESSAGE_MAP(CX666View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_CON, &CX666View::OnCon)
	ON_COMMAND(ID_NEW, &CX666View::OnNew)
	ON_COMMAND(ID_BACK, &CX666View::OnBack)
	ON_COMMAND(ID_FRONT, &CX666View::OnFront)
	ON_COMMAND(ID_SAVE, &CX666View::OnSave)
	ON_COMMAND(ID_SAVE_AS, &CX666View::OnSaveAs)
	ON_COMMAND(ID_OPEN, &CX666View::OnOpen) 
	ON_COMMAND(ID_FRONTALL, &CX666View::OnFrontall)
	ON_COMMAND(ID_BACKALL, &CX666View::OnBackall)
	ON_COMMAND(ID_IN, &CX666View::OnIn)
	ON_COMMAND(ID_INPUTCHUNK, &CX666View::OnInputchunk)
	ON_COMMAND(ID_BLACK, &CX666View::OnBlack)
END_MESSAGE_MAP()

// CX666View 构造/析构

CX666View::CX666View()
: m_color(0)
, num_order(0)
, color(0)
, computer1(false)
, computer2(false)
, flat_six(false)
, flat_draw(true)
, flat_fine(true)
, fine_legth(0)
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	bmps[0].LoadBitmap(IDB_BITMAP2);
	bmps[1].LoadBitmap(IDB_BITMAP3);
	bmps[2].LoadBitmap(IDB_BITMAP4);
	bmps[3].LoadBitmap(IDB_BITMAP5);
	bmps[4].LoadBitmap(IDB_BITMAP6);
	bmps[5].LoadBitmap(IDB_BITMAP7);

	//m_fine=sizeof(struct Chunk);
	//map_point.x=bmp.
	m_fine=0;
	Stone_infor[0].color=0;
	Stone_back[0].x=0;
	Stone_white[0].x=0;
	num_color=6;
	color_witch=0;
	m_brush=CreatePatternBrush((HBITMAP)bmp);
	bmp.DeleteObject();


}

CX666View::~CX666View()
{
}

BOOL CX666View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CX666View 绘制
void CX666View::OnDraw(CDC* pDC)
{
	CX666Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	POINT points;
	CDC dcmem;BITMAP bm;

	dcmem.CreateCompatibleDC(pDC);

	for(int i=1;i<Stone_infor[0].color-1;i++)
	{

		points.x=38+(28*(Stone_infor[i].x-1));
		points.y=38+(28*(Stone_infor[i].y-1));




		if(Stone_infor[i].color==1)
		{
			dcmem.SelectObject(&bmps[3]);//"1raw"
			GetObjectA(bmps[3],sizeof(BITMAP),(LPVOID)&bm);	
		}
		if(Stone_infor[i].color==2)
		{
			dcmem.SelectObject(&bmps[5]);//"1raw"
			GetObjectA(bmps[5],sizeof(BITMAP),(LPVOID)&bm);	
		}
		pDC->BitBlt(points.x,points.y,bm.bmWidth,bm.bmHeight,&dcmem,0,0,SRCCOPY);
	}
	if(Stone_infor[Stone_infor[0].color-1].color==1&&Stone_infor[0].color>=2)
	{

		points.x=38+(28*(Stone_infor[Stone_infor[0].color-1].x-1));
		points.y=38+(28*(Stone_infor[Stone_infor[0].color-1].y-1));
		dcmem.SelectObject(&bmps[2]);//"1raw"
		GetObjectA(bmps[2],sizeof(BITMAP),(LPVOID)&bm);	
		pDC->BitBlt(points.x,points.y,bm.bmWidth,bm.bmHeight,&dcmem,0,0,SRCCOPY);
	}
	if(Stone_infor[Stone_infor[0].color-1].color==2&&Stone_infor[0].color>=2)
	{
		points.x=38+(28*(Stone_infor[Stone_infor[0].color-1].x-1));
		points.y=38+(28*(Stone_infor[Stone_infor[0].color-1].y-1));
		dcmem.SelectObject(&bmps[1]);//"1raw"
		GetObjectA(bmps[1],sizeof(BITMAP),(LPVOID)&bm);	
		pDC->BitBlt(points.x,points.y,bm.bmWidth,bm.bmHeight,&dcmem,0,0,SRCCOPY);
	}

	if(Stone_infor[Stone_infor[0].color].color==1&&Stone_infor[0].color>=1)
	{

		points.x=38+(28*(Stone_infor[Stone_infor[0].color].x-1));
		points.y=38+(28*(Stone_infor[Stone_infor[0].color].y-1));
		dcmem.SelectObject(&bmps[0]);//"1raw"
		GetObjectA(bmps[0],sizeof(BITMAP),(LPVOID)&bm);	
		pDC->BitBlt(points.x,points.y,bm.bmWidth,bm.bmHeight,&dcmem,0,0,SRCCOPY);
	}
	if(Stone_infor[Stone_infor[0].color].color==2&&Stone_infor[0].color>=1)
	{
		points.x=38+(28*(Stone_infor[Stone_infor[0].color].x-1));
		points.y=38+(28*(Stone_infor[Stone_infor[0].color].y-1));
		dcmem.SelectObject(&bmps[4]);//"1raw"
		GetObjectA(bmps[4],sizeof(BITMAP),(LPVOID)&bm);	
		pDC->BitBlt(points.x,points.y,bm.bmWidth,bm.bmHeight,&dcmem,0,0,SRCCOPY);
	}


	if(flat_draw)
	{
		for(int i=0;i<924;i++)
		{
			if(Ai.informations[i].value==2)
			{
				if(Ai.informations[i].color==1)
				{
					if(m_config.two1==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   2;   
						lp.lopnColor   =   RGB(100,   0,   150);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
				else
				{
					if(m_config.two2==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   2;   
						lp.lopnColor   =   RGB(100,  150,   0);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
			}
		}
		for(int i=0;i<924;i++)
		{
			if(Ai.informations[i].value==3)
			{
				if(Ai.informations[i].color==1)
				{
					if(m_config.three1==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   3;   
						lp.lopnColor   =   RGB(175,   0, 175);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
				else
				{
					if(m_config.three2==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   3;   
						lp.lopnColor   =   RGB(175, 175,   0);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
			}
		}
		for(int i=0;i<924;i++)
		{
			if(Ai.informations[i].value==4)
			{
				if(Ai.informations[i].color==1)
				{
					if(m_config.four1==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   4;   
						lp.lopnColor   =   RGB(126, 75,188);      
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
				else
				{
					if(m_config.four2==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   4;   
						lp.lopnColor   =   RGB(250,  200,   0);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
			}
		}
		for(int i=0;i<924;i++)
		{
			if(Ai.informations[i].value==5)
			{
				if(Ai.informations[i].color==1)
				{
					if(m_config.five1==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   5;   
						lp.lopnColor   =   RGB(108, 36,227);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}
				else
				{
					if(m_config.five2==true)
					{
						CPen   pen;   
						LOGPEN   lp;   
						lp.lopnStyle   =   PS_SOLID;   
						lp.lopnWidth.x   =   5;   
						lp.lopnColor   =   RGB(0,   255,   0);   
						pen.CreatePenIndirect(&lp);   
						CPen   *pOldPen   =   pDC->SelectObject(&pen);
						points.x=51+(28*(Ai.informations[i].pos[0].x));
						points.y=51+(28*(Ai.informations[i].pos[0].y));
						//points=point_point(Ai.point_six[0]);
						POINT points1;
						//points1=point_point(Ai.point_six[1]);
						points1.x=51+(28*(Ai.informations[i].pos[1].x));
						points1.y=51+(28*(Ai.informations[i].pos[1].y));
						pDC->MoveTo(points.x,points.y);
						pDC->LineTo(points1.x,points1.y);
					}
				}

			}				
		}	
	}
	if(flat_six)
	{

		CPen   pen;   
		LOGPEN   lp;   
		lp.lopnStyle   =   PS_SOLID;   
		lp.lopnWidth.x   =   6;   
		lp.lopnColor   =   RGB(0, 0,  255);   
		pen.CreatePenIndirect(&lp);   
		CPen   *pOldPen   =   pDC->SelectObject(&pen);   
		points.x=51+(28*(Ai.point_six[0].x));
		points.y=51+(28*(Ai.point_six[0].y));
		//points=point_point(Ai.point_six[0]);
		POINT points1;
		//points1=point_point(Ai.point_six[1]);
		points1.x=51+(28*(Ai.point_six[1].x));
		points1.y=51+(28*(Ai.point_six[1].y));
		pDC->MoveTo(points.x,points.y);
		pDC->LineTo(points1.x,points1.y);
	}	
	if(m_config.number_stones)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,0,0));
		for(int i=1;i<=Stone_infor[0].color;i++)
		{
			CString number;
			number.Format(_T("%d"),i);
			points.x=38+(28*(Stone_infor[i].x-1));
			points.y=38+(28*(Stone_infor[i].y-1))+5;
			if(i<10)
				pDC->TextOutW(points.x+10,points.y,number,1);
			else if(i<100)
				pDC->TextOutW(points.x+6,points.y,number,2);
			else
				pDC->TextOutW(points.x,points.y,number,3);
		}
	}

}


// CX666View 打印

BOOL CX666View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CX666View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CX666View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CX666View 诊断

#ifdef _DEBUG
void CX666View::AssertValid() const
{
	CView::AssertValid();
}

void CX666View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CX666Doc* CX666View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CX666Doc)));
	return (CX666Doc*)m_pDocument;
}
#endif //_DEBUG


// CX666View 消息处理程序

void CX666View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	(this->GetDC())->SetBkColor(RGB(0, 128, 0));
	// TODO: 在此添加专用代码和/或调用基类
}

BOOL CX666View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect   rect;   
	this->GetClientRect(&rect);   
	CRect rect1=rect;
	::SelectObject(pDC->GetSafeHdc(),GetStockObject(DC_PEN));
	pDC->SetDCPenColor(RGB(200,200,200));
	SelectObject(pDC->GetSafeHdc(),m_brush);
	pDC->Rectangle(0,0,631,615);
	if(rect.right>631)
	{
		rect1.left=rect.left+630;
		pDC->FillSolidRect(&rect1,RGB(200,200,200));
	}
	if(rect.bottom>615)
	{
		rect1=rect;
		rect1.top=614;
		pDC->FillSolidRect(&rect1,RGB(200,200,200));
	}

	return true;

	//return CView::OnEraseBkgnd(pDC);
}

HBRUSH CX666View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	return hbr;
}

void CX666View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(flat_six)
		return;
	int x;
	int y;

	if(point.x>=36&&point.x<=569&&point.y>=36&&point.y<=569)
	{
		x=((point.x-22)/28)+((point.x-22)%28)/14;

		y=((point.y-22)/28)+((point.y-22)%28)/14;
		if(Ai.stone_pen[x-1][y-1]!=0)
			return;

		num_order++;
		Ai.stone_depth=num_order;
	}
	else
		return;
	color=color_witch/3+1;
	Ai.stone_pen[x-1][y-1]=color;
	Stone_infor[0].color++;
	Stone_infor[num_order].x=x;
	Stone_infor[num_order].y=y;
	Stone_infor[num_order].color=color;
	if(Ai.had_six(1)==1)
	{
		flat_six=true;
		this->Invalidate(1);
		this->MessageBox(_T("黑子胜利了！"));
		return;
	}
	if(Ai.had_six(2)==2)
	{
		flat_six=true;
		this->Invalidate(1);
		this->MessageBox(_T("白子胜利了！"));
		return;
	}

	if(color_witch==0)
	{
		color_witch=3;
	}
	else if(color_witch<4)
	{
		color_witch++;
	}
	else
	{
		color_witch=1;
	}
	Ai.restarinfstructs();
	this->Invalidate(1);

	if(computer2==true)//进攻
	{
		Ai.restarinfstructs();
		if(color_witch==3)
		{
			num_order++;
			Ai.stone_depth=num_order;
			int x1=0,x2=0,y1=0,y2=0;
			if(flat_fine)
			{

				//开局库查找
				fine_math(x1,y1,x2,y2);
			}

			if(!flat_fine)
				Ai.thenexttowstone(x1,y1,x2,y2,2);
			//Ai.thenextone(x1,y1,2);
			Ai.stone_pen[x1][y1]=2;
			Ai.stone_pen[x2][y2]=2;
			Stone_infor[num_order].x=x1+1;
			Stone_infor[num_order].y=y1+1;
			Stone_infor[num_order].color=2;
			num_order++;
			Stone_infor[num_order].x=x2+1;
			Stone_infor[num_order].y=y2+1;
			Stone_infor[num_order].color=2;
			color_witch=1;
			Stone_infor[0].color+=2;
			if(Ai.had_six(2)==2)
		{
			flat_six=true;
			this->Invalidate(1);
			this->MessageBox(_T("白子胜利了！"));
			return;
		}
		Ai.restarinfstructs();
		this->Invalidate(1);
		}
		
	}
	else if(computer1==true)//进攻
	{
		Ai.restarinfstructs();
		if(color_witch==1)
		{
			num_order++;
			Ai.stone_depth=num_order;
			int x1=0,x2=0,y1=0,y2=0;
			if(flat_fine)
			{

				//开局库查找
				fine_mathblack(x1,y1,x2,y2);
			}
			if(!flat_fine)
				Ai.thenexttowstone(x1,y1,x2,y2,1);
			//Ai.thenextone(x1,y1,1);
			Ai.stone_pen[x1][y1]=1;
			//Ai.restarinfstructs();
			//Ai.thenextone_turntow(x2,y2,1);
			Ai.stone_pen[x2][y2]=1;
			Stone_infor[num_order].x=x1+1;
			Stone_infor[num_order].y=y1+1;
			Stone_infor[num_order].color=1;
			num_order++;
			Stone_infor[num_order].x=x2+1;
			Stone_infor[num_order].y=y2+1;
			Stone_infor[num_order].color=1;
			color_witch=3;
			Stone_infor[0].color+=2;
			if(Ai.had_six(1)==1)
		{
			flat_six=true;
			this->Invalidate(1);
			this->MessageBox(_T("黑子胜利了！"));
			return;
		}
		Ai.restarinfstructs();
		this->Invalidate(1);
		}
		
	}


	CView::OnLButtonDown(nFlags, point);
}

void CX666View::OnCon()
{

	m_config.DoModal();
	computer1=m_config.computer1;
	computer2=m_config.computer2;
	Ai.computer1=computer1;
	Ai.computer2=computer2;
	if(m_config.five1||m_config.five2||m_config.four1||m_config.four2||m_config.three1||m_config.three2||m_config.two1||m_config.two2)
	{
		flat_draw=true;
		this->Invalidate(1);
	}
	else
		flat_draw=false;
	if(m_config.number_stones)
		this->Invalidate(1);
	if(computer2==true)
	{
		if(color_witch==3)
		{
			num_order++;
			Ai.stone_depth=num_order;
			int x1=0,x2=0,y1=0,y2=0;
			if(flat_fine)
			{

				//开局库查找
				fine_math(x1,y1,x2,y2);
			}

			if(!flat_fine)
				Ai.thenexttowstone(x1,y1,x2,y2,2);

			Ai.stone_pen[x1][y1]=2;

			Ai.stone_pen[x2][y2]=2;
			Stone_infor[num_order].x=x1+1;
			Stone_infor[num_order].y=y1+1;
			Stone_infor[num_order].color=2;
			num_order++;
			Stone_infor[num_order].x=x2+1;
			Stone_infor[num_order].y=y2+1;
			Stone_infor[num_order].color=2;
			color_witch=1;
			Stone_infor[0].color+=2;
		}
		if(Ai.had_six(1)==1)
		{
			flat_six=true;
			this->Invalidate(1);
			this->MessageBox(_T("黑子胜利了！"));
			return;
		}

		this->Invalidate(1);
	}
	else if(computer1==true)
	{
		if(color_witch==1)
		{
			num_order++;
			Ai.stone_depth=num_order;
			int x1=0,x2=0,y1=0,y2=0;
			if(flat_fine)
			{

				//开局库查找
				fine_mathblack(x1,y1,x2,y2);
			}

			if(!flat_fine)
				Ai.thenexttowstone(x1,y1,x2,y2,1);
			//Ai.thenextone(x1,y1,1);
			Ai.stone_pen[x1][y1]=1;

			Ai.stone_pen[x2][y2]=1;
			Stone_infor[num_order].x=x1+1;
			Stone_infor[num_order].y=y1+1;
			Stone_infor[num_order].color=1;
			num_order++;
			Stone_infor[num_order].x=x2+1;
			Stone_infor[num_order].y=y2+1;
			Stone_infor[num_order].color=1;
			color_witch=3;
			Stone_infor[0].color+=2;
		}
		else if(color_witch==0)
		{
			num_order++;
			Ai.stone_depth=num_order;
			Ai.stone_pen[9][9]=0;
			Stone_infor[num_order].x=10;
			Stone_infor[num_order].y=10;
			Stone_infor[num_order].color=1;
			Stone_infor[0].color++;
			color_witch=3;
		}
		if(Ai.had_six(2)==2)
		{
			flat_six=true;
			this->Invalidate(1);
			this->MessageBox(_T("白子胜利了！"));
			return;
		}
		this->Invalidate(1);
	}
}

void CX666View::OnNew()
{
	Stone_infor[0].color=0;
	//Stone_back[0].x=0;
	//Stone_white[0].x=0;
	m_color=0;
	num_order=0;
	color=0;
	color_witch=0;
	flat_six=false;
	//flat_draw=false;
	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
		{
			Ai.stone_pen[i][j]=0;
		}
		Ai.restarinfstructs();
		this->Invalidate(1);
}

void CX666View::OnBack()
{
	//computer1=false;
	//computer2=false;
	flat_six=false;
	if(Stone_infor[0].color>0)
	{
		int x=Stone_infor[Stone_infor[0].color].x-1;
		int y=Stone_infor[Stone_infor[0].color].y-1;
		Ai.stone_pen[x][y]=0;
		Stone_infor[0].color--;
	}
	else
		return;
	//Stone_back[0].x--;
	//Stone_white[0].x--;
	if(num_order>0)
		num_order--;
	if(num_order<3)
	{
		if(num_order==0)
			color_witch=0;
		else
			color_witch=num_order+2;
	}
	else
		color_witch=(num_order+1)%4+1;

	Ai.restarinfstructs();
	this->Invalidate(1);
}

void CX666View::OnFront()
{
	if(Ai.stone_depth>Stone_infor[0].color)
	{
		Stone_infor[0].color++;
		int x=Stone_infor[Stone_infor[0].color].x-1;
		int y=Stone_infor[Stone_infor[0].color].y-1;
		Ai.stone_pen[x][y]=Stone_infor[Stone_infor[0].color].color;
		if(color_witch<4)
		{
			color_witch++;
		}
		else
		{
			color_witch=1;
		}
		num_order++;
		if(Ai.had_six(1)==1)
		{
			flat_six=true;
			this->Invalidate(1);
			this->MessageBox(_T("黑子胜利了！"));
			return;
		}
		if(Ai.had_six(2)==2)
		{
			flat_six=true;
			this->Invalidate(1);
			this->MessageBox(_T("白子胜利了！"));
			return;
		}
		Ai.restarinfstructs();
		this->Invalidate(1);
	}
}

void CX666View::OnSave()
{
	CFile fp;
	if(!(fp.Open(_T("棋谱.yao"),CFile::modeCreate))) 
	{

		return;
	}

	fp.Close();
	if(!(fp.Open(_T("棋谱.yao"),CFile::modeWrite))) 
	{
		//AfxMessageBox("Open file failed!");
		return;
	}
	/*int save_stone[1084];
	for(int i=0;i<Stone_infor[0].color;i++)
	{
	s
	}*/
	fp.Write(Stone_infor,(Stone_infor[0].color+1)*12);
	fp.Close();
}

void CX666View::OnSaveAs()
{

	CFileDialog FileDlg( FALSE,  _T("*.yao"),  _T("stone.yao"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("棋谱文件(*.yao)|*.yao||"));

	if(IDOK == FileDlg.DoModal())
	{
		CFile fp;
		if(!(fp.Open(FileDlg.GetFileName(),CFile::modeCreate))) 
		{

			return;
		}

		fp.Close();
		if(!(fp.Open(FileDlg.GetFileName(),CFile::modeWrite))) 
		{
			//AfxMessageBox("Open file failed!");
			return;
		}
		/*int save_stone[1084];
		for(int i=0;i<Stone_infor[0].color;i++)
		{
		s
		}*/
		fp.Write(Stone_infor,(Stone_infor[0].color+1)*12);
		fp.Close();
	}

}

void CX666View::OnOpen()
{
	CFileDialog dlg( TRUE,NULL,_T("*.yao"),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("棋谱文件 (*.yao)|*.yao|"));	


	if(IDOK==dlg.DoModal())
	{
		CFile fp;

		if(!(fp.Open(dlg.GetFileName(),CFile::modeRead))) 
		{
			return;
		}
		//int number=0;
		//int save_stone[1084];
		fp.Read(Stone_infor,fp.GetLength());
		//fp.Read(&Stone_infor[1],number*12);
		//Stone_infor[0].color=number;
		fp.Close();
		flat_six=false;
		num_order=Stone_infor[0].color;
		Ai.stone_depth=Stone_infor[0].color;
		if(num_order<3)
		{
			if(num_order==0)
				color_witch=0;
			else
				color_witch=num_order+2;
		}
		else
			color_witch=(num_order+1)%4+1;
		for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
			{
				Ai.stone_pen[i][j]=0;
			}
			for(int i=1;i<=Stone_infor[0].color;i++)
			{

				Ai.stone_pen[Stone_infor[i].x-1][Stone_infor[i].y-1]=Stone_infor[i].color;
			}
			if(Ai.had_six(1)==1)
			{
				flat_six=true;
				this->Invalidate(1);
				this->MessageBox(_T("黑子胜利了！"));
				return;
			}
			if(Ai.had_six(2)==2)
			{
				flat_six=true;
				this->Invalidate(1);
				this->MessageBox(_T("白子胜利了！"));
				return;
			}

			Ai.restarinfstructs();
			this->Invalidate(1);
	}
}

void CX666View::OnFrontall()
{
	while(Ai.stone_depth>Stone_infor[0].color)
	{
		Stone_infor[0].color++;
		int x=Stone_infor[Stone_infor[0].color].x-1;
		int y=Stone_infor[Stone_infor[0].color].y-1;
		Ai.stone_pen[x][y]=Stone_infor[Stone_infor[0].color].color;
		if(color_witch<4)
		{
			color_witch++;
		}
		else
		{
			color_witch=1;
		}
		num_order++;

	}
	if(Ai.had_six(1)==1)
	{
		flat_six=true;
		this->Invalidate(1);
		this->MessageBox(_T("黑子胜利了！"));
		return;
	}
	if(Ai.had_six(2)==2)
	{
		flat_six=true;
		this->Invalidate(1);
		this->MessageBox(_T("白子胜利了！"));
		return;
	}
	Ai.restarinfstructs();
	this->Invalidate(1);
}

void CX666View::OnBackall()
{
	flat_six=false;
	while(Stone_infor[0].color>0)
	{
		int x=Stone_infor[Stone_infor[0].color].x-1;
		int y=Stone_infor[Stone_infor[0].color].y-1;
		Ai.stone_pen[x][y]=0;
		Stone_infor[0].color--;

		//Stone_back[0].x--;
		//Stone_white[0].x--;
		if(num_order>0)
			num_order--;
		if(num_order<3)
		{
			if(num_order==0)
				color_witch=0;
			else
				color_witch=num_order+2;
		}
		else
			color_witch=(num_order+1)%4+1;
	}
	Ai.restarinfstructs();
	this->Invalidate(1);
}

void CX666View::OnIn()
{
	CFileDialog dlg( TRUE,NULL,_T("*.txt"),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("棋谱文件 (*.txt)|*.txt|"));	


	if(IDOK==dlg.DoModal())
	{
		CFile fp;

		if(!(fp.Open(dlg.GetFileName(),CFile::modeRead))) 
		{
			return;
		}
		char str[1000];
		if(fp.GetLength()>1000)
		{
			fp.Close();
			return;
		}
		fp.Read(str,fp.GetLength());

		fp.Close();
		flat_six=false;
		char *p=str;
		int number=1;
		while(*p)
		{
			if(*p<='s'&&*p>='a')
			{
				Stone_infor[number].x=*p-'a'+1;
				p++;
				while(*p)
				{
					if(*p<='9'&&*p>='0')
					{
						int y=*p-'0'; 
						if(y==1)
						{
							p++;
							if(*p<='9'&&*p>='0')
							{
								y=10+(*p-'0');
								Stone_infor[number].y=y;
								p++;
								number++;
								break;
							}
							else
							{
								Stone_infor[number].y=y;
								number++;
								break;
							}
						}
						else
						{
							Stone_infor[number].y=y;
							p++;
							number++;
							break;
						}

					}
					else
						p++;
				}
			}
			else
				p++;
		}
		Stone_infor[0].color=number-1;
		num_order=Stone_infor[0].color;
		Ai.stone_depth=Stone_infor[0].color;
		//Stone_infor[1].color=1;
		for(int i=1;i<=Stone_infor[0].color;i++)
		{
			if((i%4)>1)
				Stone_infor[i].color=2;
			else
				Stone_infor[i].color=1;
		}
		if(num_order<3)
		{
			if(num_order==0)
				color_witch=0;
			else
				color_witch=num_order+2;
		}
		else
			color_witch=(num_order+1)%4+1;
		for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
			{
				Ai.stone_pen[i][j]=0;
			}
			for(int i=1;i<=Stone_infor[0].color;i++)
			{

				Ai.stone_pen[Stone_infor[i].x-1][Stone_infor[i].y-1]=Stone_infor[i].color;
			}
			if(Ai.had_six(1)==1)
			{
				flat_six=true;
				this->Invalidate(1);
				this->MessageBox(_T("黑子胜利了！"));
				return;
			}
			if(Ai.had_six(2)==2)
			{
				flat_six=true;
				this->Invalidate(1);
				this->MessageBox(_T("白子胜利了！"));
				return;
			}

			Ai.restarinfstructs();
			this->Invalidate(1);
	}
}

void CX666View::OnInputchunk()
{
	CFile fp;

	struct Chunk chunk[362];
	chunk[0].length=0;
	chunk[0].x=0;
	chunk[0].y=0;
	if(Stone_infor[0].color>=1)
	{
		chunk[1].x=Stone_infor[1].x-1;
		chunk[1].y=Stone_infor[1].y-1;
	}
	else
		return;
	for(int i=2;i<Stone_infor[0].color;i=i+2)
	{
		int x1=Stone_infor[i].x;
		int y1=Stone_infor[i].y;
		int x2=Stone_infor[i+1].x;
		int y2=Stone_infor[i+1].y;
		if(x2<x1||(x2==x1&&y2<y1))
		{
			int number=x2;
			x2=x1;
			x1=number;
			number=y2;
			y2=y1;
			y1=number;
		}
		chunk[i].x=x1-1;
		chunk[i].y=y1-1;
		chunk[i+1].x=x2-1;
		chunk[i+1].y=y2-1;
	}
	if(Stone_infor[0].color%2==false&&Stone_infor[0].color>1)
	{
		chunk[Stone_infor[0].color].x=Stone_infor[Stone_infor[0].color].x-1;
		chunk[Stone_infor[0].color].y=Stone_infor[Stone_infor[0].color].y-1;
	}

	chunk[0].length=(sizeof(struct Chunk))*Stone_infor[0].color;
	for(int i=1;i<=Stone_infor[0].color;i++)
	{
		chunk[i].length=(sizeof(struct Chunk))*(Stone_infor[0].color-i);
	}
	if(!(fp.Open(_T("database.yaos"),CFile::modeCreate |CFile::modeNoTruncate))) 
	{
		return;
	}
	fp.Close();
	if(!(fp.Open(_T("database.yaos"),CFile::modeReadWrite))) 
	{
		return;
	}
	if(fp.GetLength()>4)
	{
	}
	else
	{
		fp.Write(&chunk[1],chunk[0].length);
	}
	fp.Close();
}

// 查找白方开局库
void CX666View::fine_math(int &x1,int &y1,int &x2,int &y2)
{
	CFile fp;
	if(!(fp.Open(_T("database.yaos"),CFile::modeRead))) 
	{
		flat_fine=false;
		return;
	}
	int length=0;
	int len=0;
	if((length=fp.GetLength())<(len=3*sizeof(struct Chunk)))
	{
		fp.Close();
		flat_fine=false;
		return;
	}
	struct Chunk node;
	fp.Seek(m_fine,CFile::begin);
	fp.Read(&node,sizeof(struct Chunk));
	m_fine+=sizeof(struct Chunk);
	if(Stone_infor[0].color==1)
	{

		if(Stone_infor[num_order-1].x-1==node.x&&Stone_infor[num_order-1].y-1==node.y&&node.length>=2*sizeof(struct Chunk))//第一个子(黑子)
		{
			fp.Read(&node,sizeof(struct Chunk));//第二个子
			m_fine+=sizeof(struct Chunk);
			x1=node.x;
			y1=node.y;
			if(node.length>=sizeof(struct Chunk))
			{
				fp.Read(&node,sizeof(struct Chunk));//第三个子
				m_fine+=sizeof(struct Chunk);
				x2=node.x;
				y2=node.y;
				fine_legth=node.length;
			}
			else
			{
				flat_fine=false;
			}
		}
		else
		{
			flat_fine=false;
		}
	}
	else//从第四个子开始
	{
		int xx1=Stone_infor[num_order-1].x-1;
		int yy1=Stone_infor[num_order-1].y-1;
		int xx2=Stone_infor[num_order-2].x-1;
		int yy2=Stone_infor[num_order-2].y-1;
		if(xx2<xx1||(xx2==xx1&&yy2<yy1))//对子重新排列
		{
			int number=xx2;
			xx2=xx1;
			xx1=number;
			number=yy2;
			yy2=yy1;
			yy1=number;
		}
		if(xx1==node.x&&yy1==node.y&&node.length>=3*sizeof(struct Chunk))//下的黑子1中库中的子相同
		{
			fp.Read(&node,sizeof(struct Chunk));
			m_fine+=sizeof(struct Chunk);
			fine_legth=node.length;
			if(xx2==node.x&&yy2==node.y&&node.length>=2*sizeof(struct Chunk))//下的黑子2中库中的子相同
			{
				fp.Read(&node,sizeof(struct Chunk));
				m_fine+=sizeof(struct Chunk);
				x1=node.x;
				y1=node.y;
				if(node.length>=sizeof(struct Chunk))
				{
					fp.Read(&node,sizeof(struct Chunk));
					m_fine+=sizeof(struct Chunk);
					x2=node.x;
					y2=node.y;
					fine_legth=node.length;
				}
				else
				{
					flat_fine=false;
				}

			}
			else//下的黑子2中库中的子不相同
			{
				int legth=0;
				while(fine_legth>legth)
				{
					fp.Read(&node,sizeof(struct Chunk));
					m_fine+=sizeof(struct Chunk);
					if(xx2==node.x&&yy2==node.y&&node.length>=2*sizeof(struct Chunk))//下的黑子2中库中的子相同
					{
						fp.Read(&node,sizeof(struct Chunk));
						m_fine+=sizeof(struct Chunk);
						x1=node.x;
						y1=node.y;
						if(node.length>=sizeof(struct Chunk))
						{
							fp.Read(&node,sizeof(struct Chunk));
							m_fine+=sizeof(struct Chunk);
							x2=node.x;
							y2=node.y;
							fine_legth=node.length;
							m_fine+legth;
							return;
						}
						else
						{
							flat_fine=false;
						}
					}
					else
					{
						legth+=node.length;
					}
				}
				flat_fine=false;
			}
		}
		else//下的黑子1中库中的子不相同
		{
			int legth=0;
			while(fine_legth>legth)
			{
				fp.Seek(m_fine,CFile::begin);
				fp.Read(&node,sizeof(struct Chunk));
				m_fine+=sizeof(struct Chunk);
				if(xx1==node.x&&yy1==node.y&&node.length>=3*sizeof(struct Chunk))//下的黑子1中库中的子相同
				{
					fp.Read(&node,sizeof(struct Chunk));
					m_fine+=sizeof(struct Chunk);
					fine_legth=node.length;
					if(xx2==node.x&&yy2==node.y&&node.length>=2*sizeof(struct Chunk))//下的黑子2中库中的子相同
					{
						fp.Read(&node,sizeof(struct Chunk));
						m_fine+=sizeof(struct Chunk);
						x1=node.x;
						y1=node.y;
						if(node.length>=sizeof(struct Chunk))
						{
							fp.Read(&node,sizeof(struct Chunk));
							m_fine+=sizeof(struct Chunk);
							x2=node.x;
							y2=node.y;
							fine_legth=node.length;
						}
						else
						{
							flat_fine=false;
						}

					}
					else//下的黑子2中库中的子不相同
					{
						int legths=0;
						while(fine_legth>legths)
						{
							fp.Seek(m_fine,CFile::begin);
							fp.Read(&node,sizeof(struct Chunk));
							m_fine+=sizeof(struct Chunk);
							if(xx2==node.x&&yy2==node.y&&node.length>=2*sizeof(struct Chunk))//下的黑子2中库中的子相同
							{
								fp.Read(&node,sizeof(struct Chunk));
								m_fine+=sizeof(struct Chunk);
								x1=node.x;
								y1=node.y;
								if(node.length>=sizeof(struct Chunk))
								{
									fp.Read(&node,sizeof(struct Chunk));
									m_fine+=sizeof(struct Chunk);
									x2=node.x;
									y2=node.y;
									fine_legth=node.length;
									m_fine+=node.length;
									return;
								}
								else
								{
									flat_fine=false;
									return;
								}
							}
							else
							{
								legths+=node.length;
							}
						}
						flat_fine=false;
					}
				}
				else
				{
					legth+=node.length;
					m_fine+=node.length;
				}
			}
			flat_fine=false;
		}
	}

}

// 查找黑方开局库
void CX666View::fine_mathblack(int &x1,int &y1,int &x2,int &y2)
{
	CFile fp;
	if(!(fp.Open(_T("databaseBlack.yaos"),CFile::modeRead))) 
	{
		flat_fine=false;
		return;
	}
	int length=0;
	int len=0;
	if((length=fp.GetLength())<(len=3*sizeof(struct Chunk)))
	{
		fp.Close();
		flat_fine=false;
		return;
	}
	struct Chunk node;
	
	if(Stone_infor[0].color==3)
	{
		fp.Seek(m_fine,CFile::begin);
		fp.Read(&node,sizeof(struct Chunk));
		m_fine+=sizeof(struct Chunk);

		if(Stone_infor[1].x-1==node.x&&Stone_infor[1].y-1==node.y&&node.length>=2*sizeof(struct Chunk))//第一个子(白子)
		{
			fine_legth=node.length;
			
			
		}
		else
		{
			flat_fine=false;
		}
	}
	//从第2个子开始
	{
		int xx1=Stone_infor[num_order-1].x-1;
		int yy1=Stone_infor[num_order-1].y-1;
		int xx2=Stone_infor[num_order-2].x-1;
		int yy2=Stone_infor[num_order-2].y-1;
		if(xx2<xx1||(xx2==xx1&&yy2<yy1))//对子重新排列
		{
			int number=xx2;
			xx2=xx1;
			xx1=number;
			number=yy2;
			yy2=yy1;
			yy1=number;
		}
		
			int legth=0;
			while(fine_legth>legth)//
			{
				fp.Seek(m_fine,CFile::begin);
				fp.Read(&node,sizeof(struct Chunk));
				m_fine+=sizeof(struct Chunk);
				if(xx1==node.x&&yy1==node.y&&node.length>=3*sizeof(struct Chunk))//下的白子1中库中的子相同
				{
					fp.Read(&node,sizeof(struct Chunk));
					m_fine+=sizeof(struct Chunk);
					fine_legth=node.length;
					if(xx2==node.x&&yy2==node.y&&node.length>=2*sizeof(struct Chunk))//下的白子2中库中的子相同
					{
						fp.Read(&node,sizeof(struct Chunk));
						m_fine+=sizeof(struct Chunk);
						x1=node.x;
						y1=node.y;
						if(node.length>=sizeof(struct Chunk))
						{
							fp.Read(&node,sizeof(struct Chunk));
							m_fine+=sizeof(struct Chunk);
							x2=node.x;
							y2=node.y;
							fine_legth=node.length;
							return;
						}
						else
						{
							flat_fine=false;
						}

					}
					else//下的白子2中库中的子不相同
					{
						int legths=0;
						while(fine_legth>legths)
						{
							fp.Seek(m_fine,CFile::begin);
							fp.Read(&node,sizeof(struct Chunk));
							m_fine+=sizeof(struct Chunk);
							if(xx2==node.x&&yy2==node.y&&node.length>=2*sizeof(struct Chunk))//下的白子2中库中的子相同
							{
								fp.Read(&node,sizeof(struct Chunk));
								m_fine+=sizeof(struct Chunk);
								x1=node.x;
								y1=node.y;
								if(node.length>=sizeof(struct Chunk))
								{
									fp.Read(&node,sizeof(struct Chunk));
									m_fine+=sizeof(struct Chunk);
									x2=node.x;
									y2=node.y;
									fine_legth=node.length;
									return;
								}
								else
								{
									flat_fine=false;
									return;
								}
							}
							else
							{
								legths+=node.length;
								m_fine+=node.length;
							}
						}
						flat_fine=false;
					}
				}
				else
				{
					legth+=node.length;
					fine_legth=node.length;
				}
			}
			flat_fine=false;
		
	}
}

void CX666View::OnBlack()
{
	CFile fp;

	struct Chunk chunk[362];
	chunk[0].length=0;
	chunk[0].x=0;
	chunk[0].y=0;
	if(Stone_infor[0].color>=1)
	{
		chunk[1].x=Stone_infor[1].x-1;
		chunk[1].y=Stone_infor[1].y-1;
	}
	else
		return;
	for(int i=2;i<Stone_infor[0].color;i=i+2)
	{
		int x1=Stone_infor[i].x;
		int y1=Stone_infor[i].y;
		int x2=Stone_infor[i+1].x;
		int y2=Stone_infor[i+1].y;
		if(x2<x1||(x2==x1&&y2<y1))
		{
			int number=x2;
			x2=x1;
			x1=number;
			number=y2;
			y2=y1;
			y1=number;
		}
		chunk[i].x=x1-1;
		chunk[i].y=y1-1;
		chunk[i+1].x=x2-1;
		chunk[i+1].y=y2-1;
	}
	if(Stone_infor[0].color%2==false&&Stone_infor[0].color>1)
	{
		chunk[Stone_infor[0].color].x=Stone_infor[Stone_infor[0].color].x-1;
		chunk[Stone_infor[0].color].y=Stone_infor[Stone_infor[0].color].y-1;
	}

	chunk[0].length=(sizeof(struct Chunk))*Stone_infor[0].color;
	for(int i=1;i<=Stone_infor[0].color;i++)
	{
		chunk[i].length=(sizeof(struct Chunk))*(Stone_infor[0].color-i);
	}
	if(!(fp.Open(_T("databaseBlack.yaos"),CFile::modeCreate |CFile::modeNoTruncate))) 
	{
		return;
	}
	fp.Close();
	if(!(fp.Open(_T("databaseBlack.yaos"),CFile::modeReadWrite))) 
	{
		return;
	}
	if(fp.GetLength()>4)
	{
	}
	else
	{
		fp.Write(&chunk[1],chunk[0].length);
	}
	fp.Close();
}
