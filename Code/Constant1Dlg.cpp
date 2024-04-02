// Constant1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant1Dlg.h"


// CConstant1Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant1Dlg, CDialog)

CConstant1Dlg::CConstant1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT1, pParent)
	, m_constant1(0)
{

}

CConstant1Dlg::~CConstant1Dlg()
{
}

void CConstant1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT1, m_constant1);
	DDV_MinMaxDouble(pDX, m_constant1, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstant1Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant1Dlg 메시지 처리기
