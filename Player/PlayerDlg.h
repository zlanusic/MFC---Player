
// PlayerDlg.h : header file
//

#pragma once


// CPlayerDlg dialog
class CPlayerDlg : public CDialog
{
	// Construction
public:
	CPlayerDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_PLAYER_DIALOG };

	CButton	m_Play;
	CButton	m_Pause;
	CString	m_Path;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedPlay();
    afx_msg void OnBnClickedStop();


	DECLARE_MESSAGE_MAP()

private:
	HWND m_Video;
	BOOL Pause;
	
};
