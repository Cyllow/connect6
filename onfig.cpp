// onfig.cpp : 实现文件
//

#include "stdafx.h"
#include "X666.h"
#include "onfig.h"


// Config 对话框

IMPLEMENT_DYNAMIC(Config, CDialog)

Config::Config(CWnd* pParent /*=NULL*/)
	: CDialog(Config::IDD, pParent)
	, computer1(FALSE)
	, computer2(FALSE)
	, two1(FALSE)
	, three1(FALSE)
	, four1(FALSE)
	, five1(FALSE)
	, two2(FALSE)
	, three2(FALSE)
	, four2(FALSE)
	, five2(FALSE)
	, number_stones(FALSE)
{

}

Config::~Config()
{
}

void Config::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_PLAYER1, computer1);
	DDX_Check(pDX, IDC_PLAYER2, computer2);
	DDX_Check(pDX, IDC_CHECK1, two1);
	DDX_Check(pDX, IDC_CHECK3, three1);
	DDX_Check(pDX, IDC_CHECK5, four1);
	DDX_Check(pDX, IDC_CHECK7, five1);
	DDX_Check(pDX, IDC_CHECK2, two2);
	DDX_Check(pDX, IDC_CHECK4, three2);
	DDX_Check(pDX, IDC_CHECK6, four2);
	DDX_Check(pDX, IDC_CHECK8, five2);
	DDX_Check(pDX, IDC_CHECK9, number_stones);
}


BEGIN_MESSAGE_MAP(Config, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &Config::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Config 消息处理程序


void Config::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}
