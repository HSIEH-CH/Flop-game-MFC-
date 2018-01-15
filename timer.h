#include <afxwin.h>
class timer
{
	int now_x, now_y, ID, w, h;
	int intent_x, intent_y;
	int add;
public:
	timer(){
		now_x = 1400;
		now_y = 50;
		w = 50; h = 70;
		add = 0;
		intent_y = 50;
	}
	void draw(CDC *dc);
	void setXY(int inx, int iny){ now_x = inx; now_y = iny; };
	void setID(int id){ ID = id; };
	~timer(void);
};

