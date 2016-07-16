// NameGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NameGenerator.h"
#include "NameGeneratorDlg.h"

#include "Str.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNameGeneratorDlg dialog




CNameGeneratorDlg::CNameGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNameGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPOSITE_RULE, m_combobox_CompositeRule);
	DDX_Control(pDX, IDC_STATIC_NAME, m_staticName);
	DDX_Control(pDX, IDC_CHECK_REMOVE_LASTEST_USED, m_bRemoveLastestUsed);
}

BEGIN_MESSAGE_MAP(CNameGeneratorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CNameGeneratorDlg::OnBnClickedButtonGenerate)
END_MESSAGE_MAP()


// CNameGeneratorDlg message handlers

BOOL CNameGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_combobox_CompositeRule.InsertString(GENERATECONDITION_NONE, _T("조합 안함"));
	m_combobox_CompositeRule.InsertString(GENERATECONDITION_1, _T("1단 조합"));
	m_combobox_CompositeRule.InsertString(GENERATECONDITION_2, _T("2단 조합"));
	m_combobox_CompositeRule.InsertString(GENERATECONDITION_3, _T("3단 조합"));

	m_combobox_CompositeRule.SetCurSel(0);

	if(false == m_Generator.Load())
	{
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNameGeneratorDlg::OnPaint()
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
HCURSOR CNameGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CNameGeneratorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_NAME)
	{
		// TODO:  Change any attributes of the DC here
		pDC->SetTextColor(RGB(0, 155, 255));

		CFont font;
		font.CreateFont(150, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, _T("Arial"));
		CFont* oldFont = (CFont*)pDC->SelectObject(&font);
		UNREFERENCED_PARAMETER(oldFont);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CNameGeneratorDlg::OnBnClickedButtonGenerate()
{
	std::wstring strName;
	if(m_bRemoveLastestUsed.GetCheck())
		strName = m_Generator.GenerateRemoveLastestUsed((GENERATE_CONDITION)m_combobox_CompositeRule.GetCurSel());
	else
		strName = m_Generator.Generate((GENERATE_CONDITION)m_combobox_CompositeRule.GetCurSel());

	m_staticName.SetWindowText(WCHAR_TO_WCHAR(strName.c_str()));
}
