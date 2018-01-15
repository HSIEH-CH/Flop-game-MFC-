#include "card.h"
#include <afxwin.h>
#include "resource.h"



void DrawTransparentCard(CDC *pDC, UINT IDImage, CRect &rect, COLORREF rgbMask)
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

void card::draw(CDC *dc){
	UINT PictureID = 0;
	CRect Field;
	int width=w;
	int height=h;

	switch (ID)
	{
	case 0:PictureID = IDB_BITMAP11; break;
	case 1:PictureID = IDB_BITMAP1; break;
	case 2:PictureID = IDB_BITMAP2; break;
	case 3:PictureID = IDB_BITMAP3; break;
	case 4:PictureID = IDB_BITMAP4; break;
	case 5:PictureID = IDB_BITMAP5; break;
	case 6:PictureID = IDB_BITMAP6; break;
	case 7:PictureID = IDB_BITMAP7; break;
	case 8:PictureID = IDB_BITMAP8; break;
	case 9:PictureID = IDB_BITMAP9; break;
	case 10:PictureID = IDB_BITMAP10; break;
	default:
		break;
	}
	if (initial){
		now_y += addw;
		if (now_y > intent_y){
			now_y = intent_y;
			initial = false;
			initial_done = true;
			addw = 1;
		}
		if (addw < 100) addw += 4;
	}
	if (move){
		now_x += move_vx;
		now_y += move_vy;
		if (now_x <= intent_x & now_y <= intent_y){
			now_x = intent_x; now_y = intent_y;
			move = false;
			move_done = true;
		}
	}
	if (close){
		if (w < 150)w += addw;
		else {
			w = 150;
			addw = 1;
			close = false;
		}
		if (addw<20)addw += 6;
	}
	if (open){
		if (w >0)w -= addw;
		else {
			w = 0;
			addw = 1;
			open = false;
		}
		if (addw<20)addw += 1;
	}
	if (Delete){
		if (h >0)h -= addw;
		else {
			h = 0;
			addw = 1;
			delete_done = true;
		}
		if (addw<20)addw += 5;
	}
	Field.left = now_x; Field.right = now_x + width; Field.top = now_y; Field.bottom = now_y + height;
	DrawTransparentCard(dc, PictureID, Field, RGB(255, 255, 255));
}
void card::MoveTo(int inx, int iny){ 
	intent_x = inx;
	intent_y = iny;
	move = true;
	move_vx = (intent_x - now_x)/10;
	move_vy = (intent_y - now_y)/10;
};



card::~card(void)
{
}
