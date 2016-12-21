
// lotteryDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include <vector>
#include <map>
using namespace std;

// ClotteryDlg �Ի���
class ClotteryDlg : public CDialogEx
{
// ����
public:
	ClotteryDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOTTERY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
