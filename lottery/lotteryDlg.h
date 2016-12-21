
// lotteryDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include <vector>
#include <map>
using namespace std;

// ClotteryDlg 对话框
class ClotteryDlg : public CDialogEx
{
// 构造
public:
	ClotteryDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOTTERY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonStart();
	BOOL ShowImage(CDC* pDc, CString strPath, int x, int y);
	BOOL ShowJpgGif(CDC* pDC,CString strPath, int x, int y);
	CString* SelectLuckyOne(std::vector<CString>&);
	CEdit m_selPath;
	std::vector<CString> m_fileName;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStop();
};
