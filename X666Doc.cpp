// X666Doc.cpp : CX666Doc 类的实现
//

#include "stdafx.h"
#include "X666.h"

#include "X666Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CX666Doc

IMPLEMENT_DYNCREATE(CX666Doc, CDocument)

BEGIN_MESSAGE_MAP(CX666Doc, CDocument)
END_MESSAGE_MAP()


// CX666Doc 构造/析构

CX666Doc::CX666Doc()
{
	// TODO: 在此添加一次性构造代码

}

CX666Doc::~CX666Doc()
{
}

BOOL CX666Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CX666Doc 序列化

void CX666Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CX666Doc 诊断

#ifdef _DEBUG
void CX666Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CX666Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CX666Doc 命令
