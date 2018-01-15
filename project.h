#include <afxwin.h>
class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
public:

	CMainWindow();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void build(CRect rect);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
};

