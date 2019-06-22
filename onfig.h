#pragma once


// Config 对话框

class Config : public CDialog
{
	DECLARE_DYNAMIC(Config)

public:
	Config(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Config();

// 对话框数据
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 电脑人1
	BOOL computer1;
public:
	// 电脑人2
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
	// 是否画出棋的编号
	BOOL number_stones;
	afx_msg void OnBnClickedCheck1();
};
