// X666Doc.h : CX666Doc ��Ľӿ�
//


#pragma once


class CX666Doc : public CDocument
{
protected: // �������л�����
	CX666Doc();
	DECLARE_DYNCREATE(CX666Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CX666Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


