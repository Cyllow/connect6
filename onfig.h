#pragma once


// Config �Ի���

class Config : public CDialog
{
	DECLARE_DYNAMIC(Config)

public:
	Config(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Config();

// �Ի�������
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ������1
	BOOL computer1;
public:
	// ������2
	BOOL computer2;
public:
	BOOL two1;
public:
	BOOL three1;
public:
	BOOL four1;
public:
	BOOL five1;
public:
	BOOL two2;
public:
	BOOL three2;
public:
	BOOL four2;
public:
	BOOL five2;
public:
	// �Ƿ񻭳���ı��
	BOOL number_stones;
	afx_msg void OnBnClickedCheck1();
};
