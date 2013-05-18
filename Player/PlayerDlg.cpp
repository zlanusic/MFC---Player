
// PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Player.h"
#include "PlayerDlg.h"
#include "vfw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPlayerDlg dialog




CPlayerDlg::CPlayerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPlayerDlg::IDD, pParent)
{
	m_Path = ("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PLAY, m_Play);
	DDX_Control(pDX, IDC_PAUSE, m_Pause);
	DDX_Text(pDX, IDC_PATH, m_Path);

}

BEGIN_MESSAGE_MAP(CPlayerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	
	ON_BN_CLICKED(ID_BROWSE, &CPlayerDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(ID_EXIT, &CPlayerDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_PAUSE, &CPlayerDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_PLAY, &CPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_STOP, &CPlayerDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CPlayerDlg message handlers

BOOL CPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPlayerDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	m_Video = NULL;
	if(m_Video == NULL)
	{
		CFileDialog avi(TRUE,NULL,NULL,OFN_HIDEREADONLY,"MP3 Files (*.mp3)|*.mp3|AVI Files(*.avi)|*.avi|");
		if(avi.DoModal() == IDOK)
		{
			m_Path = avi.GetPathName();
			UpdateData(FALSE);

		}
	}

}

void CPlayerDlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	if(m_Video !=NULL)
	{
		MCIWndDestroy(m_Video);
		OnOK();
	}
	CDialog::OnCancel();

}

void CPlayerDlg::OnBnClickedPause()
{
	// TODO: Add your control notification handler code here
	if(Pause)
	{
		m_Pause.SetWindowText("Pause");
		MCIWndResume(m_Video);
		Pause = FALSE;
	}
	else
	{
		m_Pause.SetWindowText("NoPause");
		MCIWndPause(m_Video);
		Pause = TRUE;
	}

}

void CPlayerDlg::OnBnClickedPlay()
{
	// TODO: Add your control notification handler code here
		m_Video = NULL;
	if(m_Video == NULL)
	{
		m_Video = MCIWndCreate(GetSafeHwnd(), AfxGetInstanceHandle(), WS_CHILD | WS_VISIBLE | MCIWNDF_NOMENU, m_Path);
		
	}
	else
	{
		MCIWndHome(m_Video);
	}
	MCIWndPlay(m_Video);
	Pause = FALSE;
	m_Play.EnableWindow(FALSE);

}

void CPlayerDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
		MCIWndStop(m_Video);
	if(m_Video !=NULL)
	{
		MCIWndDestroy(m_Video);
	
	}
	m_Play.EnableWindow(TRUE);

}
