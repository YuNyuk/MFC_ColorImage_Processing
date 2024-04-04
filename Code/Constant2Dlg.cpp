// Constant2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant2Dlg.h"


// CConstant2Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant2Dlg, CDialog)

CConstant2Dlg::CConstant2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT2, pParent)
	, m_constant2(0)
{

}

CConstant2Dlg::~CConstant2Dlg()
{
}

void CConstant2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT2, m_constant2);
	DDV_MinMaxDouble(pDX, m_constant2, 0, 10);
}


BEGIN_MESSAGE_MAP(CConstant2Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant2Dlg 메시지 처리기
