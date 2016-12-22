
// lotteryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "lottery.h"
#include "lotteryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ClotteryDlg �Ի���




ClotteryDlg::ClotteryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClotteryDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClotteryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_selPath);
}

BEGIN_MESSAGE_MAP(ClotteryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &ClotteryDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_START, &ClotteryDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &ClotteryDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// ClotteryDlg ��Ϣ�������

BOOL ClotteryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ClotteryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void ClotteryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR ClotteryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ClotteryDlg::OnBnClickedButtonSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szPath[MAX_PATH];
	CString str;

	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = _T("please select ");
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if(lp && SHGetPathFromIDList(lp, szPath))
	{
		//str.Format(_T("selected %s"), szPath);
		//AfxMessageBox(str);
		//CWnd::SetDlgItemTextW(IDC_EDIT_FILEPATH,szPath);
		m_selPath.SetWindowTextW(szPath);
	}
	else
	{
		AfxMessageBox(_T("error"));
	}

	//load img in here
}

static BOOL b_Started = 0;
static BOOL b_Stopped = 0;
void ClotteryDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!b_Started)
	{
	b_Stopped = 0;
	b_Started = 1;
	//clear m_filePath;
	m_fileName.clear();
	// get dir name
	UpdateData(TRUE);
	CString filePath;
	GetDlgItemText(IDC_EDIT_FILEPATH, filePath);
	UpdateData(FALSE);
	filePath = filePath + _T("\\*.*");
	
	/*
	if(!filePath.IsEmpty())
	{
		CString str;
		str.Format(_T("selected %s"), filePath);
		AfxMessageBox(str);
	}
	*/

	// get files in that dir
	CFileFind ff;
	BOOL isFind = ff.FindFile(filePath);
	while(isFind)
	{
		isFind = ff.FindNextFile();
		
		if(isFind)
		{
			if(!ff.IsDirectory() && !ff.IsDots())
			{
				CString name = ff.GetFileName();
				CString path = ff.GetFilePath();
				m_fileName.push_back(path);
			}
		}
	}

	// select, find a method to select the lucky one.
	/* test
	//CString selectedPath = SelectLuckyOne(m_fileName)��
	srand(unsigned(time(0)));
	CString selectedPath = m_fileName[rand()%m_fileName.size()];
	*/
	SetTimer(1, 500, NULL);


	//output
	//ShowImage(GetDlgItem(IDC_STATIC_SHOWPIC)->GetDC(), selectedPath, 0, 0);
	}
	
}

BOOL ClotteryDlg::ShowImage(CDC* pDC, CString strPath, int x, int y)
{
	IPicture *pPic=NULL; 
	OleLoadPicturePath(CComBSTR(strPath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture,(LPVOID*)&pPic);
	if (NULL==pPic)
	{
		return FALSE;
	}

	OLE_XSIZE_HIMETRIC hmWidth;  
	OLE_YSIZE_HIMETRIC hmHeight;  
	pPic->get_Width(&hmWidth);  
	pPic->get_Height(&hmHeight);

	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth=rtWnd.right-rtWnd.left;
	int iWndHeight=rtWnd.bottom-rtWnd.top;

	if(FAILED(pPic->Render(*pDC,x,y,iWndWidth,iWndHeight,0,hmHeight,hmWidth,-hmHeight,NULL)))  
	{
		pPic->Release();
		return FALSE;
	}

	pPic->Release(); 
	return TRUE;
}

BOOL ClotteryDlg::ShowJpgGif(CDC* pDC,CString strPath, int x, int y)

{
	CFileStatus fstatus;  
	CFile file;  
	ULONGLONG cb;  

	if (!file.Open(strPath,CFile::modeRead))
	{
		return FALSE;
	}
	if (!file.GetStatus(strPath,fstatus))
	{
		return FALSE;
	}
	if ((cb =fstatus.m_size)<=0)
	{
		return FALSE;
	}

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (unsigned int)cb);  
	if (hGlobal== NULL) 
	{
		return FALSE;
	}

	LPVOID pvData = NULL;  
	pvData = GlobalLock(hGlobal);
	if (pvData == NULL)  
	{  
		GlobalFree(hGlobal);
		return FALSE;
	} 

	IStream *pStm;  
	file.Read(pvData,(unsigned int)cb);  
	GlobalUnlock(hGlobal);  
	CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);  

	IPicture *pPic; 
	if(OleLoadPicture(pStm,(LONG)fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)!=S_OK) 
	{ 
		GlobalFree(hGlobal);
		return FALSE;
	}

	OLE_XSIZE_HIMETRIC hmWidth;  
	OLE_YSIZE_HIMETRIC hmHeight;  
	pPic->get_Width(&hmWidth);  
	pPic->get_Height(&hmHeight);  

	
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth=rtWnd.right-rtWnd.left;
	int iWndHeight=rtWnd.bottom-rtWnd.top;

	if(FAILED(pPic->Render(*pDC,x,y,iWndWidth,iWndHeight,0,hmHeight,hmWidth,-hmHeight,NULL)))  
	{
		pPic->Release();
		GlobalFree(hGlobal);
		return false;
	}

	pPic->Release(); 
	GlobalFree(hGlobal);
	return true;
}

CString* ClotteryDlg::SelectLuckyOne(std::vector<CString>&)
{
	
	return 0;
}
static unsigned int g_Ntimes = 0;
void ClotteryDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(b_Stopped)
		return;
	switch (nIDEvent)   
    {   
    case 1:
		if(g_Ntimes >= m_fileName.size())
			g_Ntimes = 0;
		//else
			//g_Ntimes++;
		ShowImage(GetDlgItem(IDC_STATIC_SHOWPIC)->GetDC(), m_fileName[g_Ntimes++], 0, 0);

        break;   
	}
	CDialogEx::OnTimer(nIDEvent);
}


void ClotteryDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!b_Stopped)
	{
	b_Stopped = 1;
	KillTimer(1);
	if(g_Ntimes >= m_fileName.size())
			g_Ntimes = 0;
	ShowImage(GetDlgItem(IDC_STATIC_SHOWPIC)->GetDC(), m_fileName[g_Ntimes], 0, 0);
	b_Started = 0;
	}

}
