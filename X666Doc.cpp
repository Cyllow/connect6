// X666Doc.cpp : CX666Doc ���ʵ��
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


// CX666Doc ����/����

CX666Doc::CX666Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CX666Doc::~CX666Doc()
{
}

BOOL CX666Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CX666Doc ���л�

void CX666Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CX666Doc ���

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


// CX666Doc ����
