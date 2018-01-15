#include "project.h"
#include <afxwin.h>
#include <windows.h>
#include <vector>
#include <math.h>
#include <string>
#include <MMSYSTEM.H>
#include "card.h"
#include "resource.h"
#include "timer.h"
using namespace std;
#define ID_TIMER_CLOCK 1

CMyApp myApp;
struct data{
	int x, y;
};
int num_w=4, num_h=3;
vector<data> card_locate;
vector<card> cards,bg_card;
bool gamestart=false;
vector<int> card_n;
int move_n= num_w * num_h;
int total_num = num_w*num_h;
int now_num = 0;
int t = 0;
int game_stage=0;
int select_n = 0;
vector<int> sel_locate;
bool closecard=false;
bool deletecard = false;
int game_start_n = 0;
int second = 0;
timer timer1, timer2;
timer m10, m1, s10, s1;
timer m_m10, m_m1, m_s10, m_s1;
timer best_text,best_space,timer_text,timer_space;
int t1=0,t2=0,total=0;
int mintime=0;
/////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions



BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("翻牌遊戲"),
		WS_SYSMENU,
		CRect(0, 0, 1500, 1000));

}
void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point){

}
void CMainWindow::OnLButtonUp(UINT nFlags, CPoint point){

	if (game_stage == 0 & gamestart){
		
		for (int i = 0; i < cards.size(); i++){
			int x = cards[i].getX(), y = cards[i].getY();
			if (point.x > x & point.x<x + 150 & point.y>y & point.y < y + 200){
				now_num = 0;
				mciSendString("play 點擊.wav", 0, 0, 0);
				game_stage += 1;
				move_n = 0;
				t = 0;
				t1 = 0; t2 = 0; total = 0;
				break;
			}
		}
	}
	else if (game_stage == 1 ){
		for (int i = 0; i < cards.size(); i++){
			if (!cards[i].checkMove()) return;
		}
		second = -1;
		game_stage += 1;
		for (int i = 0; i < bg_card.size(); i++){
			bg_card[i].card_close();
		}
		mciSendString("play 開始音樂.mp3", 0, 0, 0);
	}
	else if (game_stage == 2 & select_n <2){
		for (int i = 0; i < cards.size(); i++){
			int x = cards[i].getX(), y = cards[i].getY();
			if (bg_card[i].getW()==150 & point.x > x & point.x<x + 150 & point.y>y & point.y < y + 200){
				PlaySound("點擊.wav",NULL,SND_ASYNC);
				bg_card[i].card_Open();
				select_n += 1;
				sel_locate.push_back(i);
				if (select_n == 2){
					if (cards[sel_locate[sel_locate.size() - 1]].getID() == cards[sel_locate[sel_locate.size() - 2]].getID()){//相同僅清除儲存選取選擇的項目,不覆蓋
						sel_locate.clear();
						now_num += 2;
						select_n = 0;
						if (total_num == now_num){//全部選完
							game_stage = 0;//重置
							t = 0;
							deletecard = true;
							gamestart = false;
							break;
						}
					}
				}
				break;
			}
		}
	}
}
void CMainWindow::OnRButtonUp(UINT nFlags, CPoint point){

}

void CMainWindow::build(CRect rect){
	cards.clear();
	bg_card.clear();
	card_n.clear();
	card_locate.clear();
	gamestart = false;
	game_start_n = 0;
	game_stage = 0;
	now_num = 0;
	t = 0;
	select_n = 0;
	second = 0;
	closecard = false;
	deletecard = false;
	
	int card_w = rect.Width() / 6, card_h = rect.Height() / 5 + 30;
	int space_w = card_w / 5, space_h = card_h / 5;
	for (int i = 0; i < num_w*num_h / 2; i++){ card_n.push_back(0); }
	for (int i = 0; i < num_h; i++){
		for (int j = 0; j < num_w; j++){
			card img;
			int n = rand() % (num_w*num_h / 2) + 1;
			while (card_n[n - 1] == 2){
				n = rand() % (num_w*num_h / 2) + 1;
			}
			card_n[n - 1] += 1;
			img.setXY(rect.Width() - 160 - i, -200);
			img.initialization(rect.Height() - 210 - i * 2);
			img.setW(150); img.setID(0); bg_card.push_back(img);
			img.setW(150); img.setID(n); cards.push_back(img);

			data locate;
			locate.x = j*card_w + space_w;
			locate.y = i*card_h + space_h;
			card_locate.push_back(locate);

		}

	}
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	CRect rect;
	GetClientRect(&rect);
	if (CFrameWnd::OnCreate(lpcs) == -1)
		return -1;
	if (!SetTimer(ID_TIMER_CLOCK, 1, NULL)) {
		MessageBox((LPCTSTR)"SetTimer failed");
		return -1;
	}
	srand((unsigned)time(NULL));
	mciSendString("play bgm.mp3 repeat", 0, 0, 0);
	build(rect);
	best_text.setID(10);
	best_text.setXY(rect.Width() - 220, 130);
	best_space.setID(12);
	best_space.setXY(rect.Width() - 120, 200);
	timer_text.setID(11);
	timer_text.setXY(rect.Width() - 220, 330);
	timer_space.setID(12);
	timer_space.setXY(rect.Width() - 120, 400);
	return 0;
}



void CMainWindow::OnTimer(UINT nTimerID) {
		
	CRect rect;
	GetClientRect(&rect);
	CClientDC dc(this);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP12);
	//bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	BITMAP m_bitmap;
	bmp.GetBitmap(&m_bitmap);
	mdc.SelectObject(&bmp);

	if (t%5==0 & game_start_n<total_num){
		cards[game_start_n].initial_move();
		bg_card[game_start_n].initial_move();
		game_start_n += 1;
	}
	if (cards.size() > 0 & !gamestart & !deletecard){
		if (cards[cards.size() - 1].getinitial()) gamestart = true;
	}
	//----------------移動卡片
	
	if (t%5 == 0 & move_n<num_w*num_h){
		cards[(num_w*num_h - 1) - move_n].MoveTo(card_locate[move_n].x, card_locate[move_n].y);
		bg_card[(num_w*num_h - 1) - move_n].MoveTo(card_locate[move_n].x, card_locate[move_n].y);
		bg_card[(num_w*num_h - 1) - move_n].setW(0);
		move_n += 1;
		
	}
	t = (t + 1) % 200; 
	if (second == 0 & game_stage==1){
		for (int i = 0; i < cards.size(); i++){
			if (!cards[i].checkMove()) break;
			if (i == cards.size() - 1){ second = 15; 
				timer1.setXY(rect.Width() - 200, -50); timer1.setID(second / 10);
				timer2.setXY(rect.Width() - 150, -50); timer2.setID(second % 10);
				t = 0;
			}
		}
	}
	//-----------------時間倒數
	if (second > 0 & t % (60-num_w*num_h) == 0 & game_stage==1){
		second -= 1;
		timer1.setXY(rect.Width() - 200, -50); timer1.setID(second / 10);
		timer2.setXY(rect.Width() - 150, -50); timer2.setID(second % 10);
		
		if (second <= 0){
			
			game_stage += 1;
			for (int i = 0; i < bg_card.size(); i++){
				bg_card[i].card_close();
			}
			mciSendString("play 開始音樂.mp3", 0, 0, 0);
		}
	}
	if (game_stage == 1 & second>0){
		timer1.draw(&mdc);
		timer2.draw(&mdc);
	}
	//-----------------
	
	if (select_n == 2){//選了兩張牌,進行比較
		if (bg_card[sel_locate[0]].getW() == 0 & bg_card[sel_locate[1]].getW() == 0){
			
			if (cards[sel_locate[sel_locate.size()-1]].getID() != cards[sel_locate[sel_locate.size()-2]].getID()){//不相同則覆蓋卡牌
				mciSendString("play success.wav", 0, 0, 0);

				closecard = true;
				t = 0;
			}
			select_n = 0;
		}
	}
	if (sel_locate.size()>=2 & t == 4){
		closecard = false;
		bg_card[sel_locate[0]].card_close();
		bg_card[sel_locate[1]].card_close();
		sel_locate.erase(sel_locate.begin());
		sel_locate.erase(sel_locate.begin());
	}

	if (deletecard & t == 50){
		deletecard = false;
		for (int i = 0; i < total_num; i++){
			cards[i].MoveTo(cards[i].getX(), cards[i].getY()-1000);
			cards[i].card_Delete();
			bg_card[i].MoveTo(bg_card[i].getX(), bg_card[i].getY() - 1000);
			bg_card[i].card_Delete();
		}
	}
	
	//顯示計時器
	if (game_stage == 2 & t1 == 0) t1 = time(NULL);
	if (game_stage == 2 & total_num != now_num){ t2 = time(NULL); total = t2 - t1; }
	
	//計時器
	timer_text.draw(&mdc);
	m10.setXY(rect.Width() - 220, 400); m10.setID(total / 600); m10.draw(&mdc);
	m1.setXY(rect.Width() - 170, 400); m1.setID((total / 60) % 10); m1.draw(&mdc);
	timer_space.draw(&mdc);
	s10.setXY(rect.Width() - 100, 400); s10.setID(total / 10); s10.draw(&mdc);
	s1.setXY(rect.Width() - 50, 400); s1.setID(total % 10); s1.draw(&mdc);

	//記錄器
	best_text.draw(&mdc);
	m_m10.setXY(rect.Width() - 220, 200); m_m10.setID(mintime / 600); m_m10.draw(&mdc);
	m_m1.setXY(rect.Width() - 170, 200); m_m1.setID((mintime / 60) % 10); m_m1.draw(&mdc);
	best_space.draw(&mdc);
	m_s10.setXY(rect.Width() - 100, 200); m_s10.setID(mintime / 10); m_s10.draw(&mdc);
	m_s1.setXY(rect.Width() - 50, 200); m_s1.setID(mintime % 10); m_s1.draw(&mdc);
	//---------
	for (int i = 0; i < cards.size(); i++){//判斷卡牌是否消除
		if (!cards[i].getDelete()){//若其中一個存在,跳出迴圈
			break;
		}
		if (mintime == 0 | mintime > total)mintime = total;
		build(rect);
	}
	
	//-----------------------

	for (int i = 0; i < cards.size(); i++){
		cards[i].draw(&mdc);
		bg_card[i].draw(&mdc);
			
	}
	
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &mdc, 0, 0, SRCCOPY);

}

