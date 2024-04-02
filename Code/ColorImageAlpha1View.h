
// ColorImageAlpha1View.h: CColorImageAlpha1View 클래스의 인터페이스
//

#pragma once


class CColorImageAlpha1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImageAlpha1View() noexcept;
	DECLARE_DYNCREATE(CColorImageAlpha1View)

// 특성입니다.
public:
	CColorImageAlpha1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CColorImageAlpha1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayScale();
	afx_msg void OnChangeSatur();
	afx_msg void OnPickOrange();
	afx_msg void OnEmboss();
	afx_msg void OnEmbossHsi();
	afx_msg void OnAddImage();
	afx_msg void OnDarkImage();
	afx_msg void OnReverseImage();
	afx_msg void OnBwImage();
	afx_msg void OnGammaImage();
	afx_msg void OnParabolaCap();
	afx_msg void OnParabolaCup();
	afx_msg void OnAndImage();
	afx_msg void OnOrImage();
	afx_msg void OnXorImage();
	afx_msg void OnBlurImage();
	afx_msg void OnSharpImage();
	afx_msg void OnEdgeImage();
	afx_msg void OnZoomIn1();
	afx_msg void OnZoomIn2();
	afx_msg void OnZoomIn3();
	afx_msg void OnZoomOut();
	afx_msg void OnMoveImage();
	afx_msg void OnRotate1();
	afx_msg void OnRotate2();
	afx_msg void OnRotate3();
	afx_msg void OnReverseImage1();
	afx_msg void OnReverseImage2();
	afx_msg void OnHistoStretch();
	afx_msg void OnEndIn();
	afx_msg void OnHistoEqual();
};

#ifndef _DEBUG  // ColorImageAlpha1View.cpp의 디버그 버전
inline CColorImageAlpha1Doc* CColorImageAlpha1View::GetDocument() const
   { return reinterpret_cast<CColorImageAlpha1Doc*>(m_pDocument); }
#endif

