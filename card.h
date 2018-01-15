#include <afxwin.h>
class card
{
	int now_x,now_y,ID,w,h;
	int intent_x, intent_y;
	bool initial,initial_done;
	bool open;
	bool close;
	bool Delete,delete_done;
	bool move,move_done;//移動動畫開關
	double move_vx, move_vy;//移動量
	int addw=1;
public:
	card(int in_x = 50, int in_y = 50){
		now_x = in_x;
		now_y = in_y;
		w = 150; h = 200;
		initial = false,initial_done=false;
		move_vy = 30;
		open = false; move = false; move_done = false;
		Delete = false; delete_done = false;
	
	}
	void draw(CDC *dc);
	void initialization(int in_y){ intent_y = in_y; };
	void initial_move(){ initial = true; };
	bool getinitial(){ return initial_done; };
	void setXY(int inx, int iny){ now_x = inx;  now_y = iny; };
	void MoveTo(int inx, int iny);
	void setID(int id){ ID = id; };
	void turn1(){ if(w>0) w-=4; };
	void card_Open(){ open = true; };
	void card_close(){ close = true; };//卡牌蓋上
	void setW(int inw){ w = inw; };
	bool getMove(){ return move; };//取得是否移動完畢
	bool checkMove(){ return move_done; };
	void resetMove(){ move_done = false; };
	int getX(){ return now_x; };
	int getY(){ return now_y; };
	int getW(){ return w; };
	int getID(){ return ID; };
	void card_Delete(){ Delete = true; };
	int getDelete(){ return delete_done; };
	~card(void);
};

