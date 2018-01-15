#include "timer.h"
#include <afxwin.h>
#include "resource.h"



void DrawTransparentTimer(CDC *pDC, UINT IDImage, CRect &rect, COLORREF rgbMask)
{
	CDC ImageDC, MaskDC;

	CBitmap Image;
	CBitmap maskBitmap;

	Image.LoadBitmap(IDImage);
	ImageDC.CreateCompatibleDC(pDC);
	ImageDC.SelectObject(&Image);

	MaskDC.CreateCompatibleDC(pDC);
	maskBitmap.CreateBitmap(rect.Width(), rect.Height(), 1, 1, NULL);
	MaskDC.SelectObject(&maskBitmap);

	ImageDC.SetBkColor(rgbMask);
	MaskDC.BitBlt(0, 0, rect.Width(), rect.Height(), &ImageDC, 0, 0, SRCCOPY);

	ImageDC.SetBkColor(RGB(0, 0, 0));
	ImageDC.SetTextColor(RGB(255, 255, 255));
	ImageDC.BitBlt(0, 0, rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &ImageDC, 0, 0, SRCPAINT);

}

void timer::draw(CDC *dc){
	UINT PictureID = 0;
	CRect Field;
	int width = w;
	int height = h;
	if (now_y < intent_y) now_y+= add;
	if (add < 10) add += 1;
	switch (ID)
	{
	case 0:PictureID = IDB_BITMAP13; break;
	case 1:PictureID = IDB_BITMAP14; break;
	case 2:PictureID = IDB_BITMAP15; break;
	case 3:PictureID = IDB_BITMAP16; break;
	case 4:PictureID = IDB_BITMAP17; break;
	case 5:PictureID = IDB_BITMAP18; break;
	case 6:PictureID = IDB_BITMAP19; break;
	case 7:PictureID = IDB_BITMAP20; break;
	case 8:PictureID = IDB_BITMAP21; break;
	case 9:PictureID = IDB_BITMAP22; break;
	case 10:PictureID = IDB_BITMAP23; width = 150; break;
	case 11:PictureID = IDB_BITMAP24; width = 150; break;
	case 12:PictureID = IDB_BITMAP25; width = 20; break;
	default:
		break;
	}
	
	Field.left = now_x; Field.right = now_x + width; Field.top = now_y; Field.bottom = now_y + height;
	DrawTransparentTimer(dc, PictureID, Field, RGB(255, 255, 255));
}



timer::~timer(void)
{
}
