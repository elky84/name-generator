// NameGeneratorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Generator.h"

// CNameGeneratorDlg dialog
class CNameGeneratorDlg : public CDialog
{
// Construction
public:
	CNameGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NAMEGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Custom Data
	Generator m_Generator;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonGenerate();
	CComboBox m_combobox_CompositeRule;
	CStatic m_staticName;
	CButton m_bRemoveLastestUsed;
};
