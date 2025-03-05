#include "Man.h"

void Man::init(Chess * chess)
{
	this->chess = chess;
}

//棋手下棋
void Man::go()
{
	//鼠标函数
	MOUSEMSG msg;
	//落子位置
	ChessPos pos;
	while (1) {
		//获取鼠标点击信息
		msg = GetMouseMsg();
		//通过chess对象判断落子位置是否有效
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	
	}
	//落子
	chess->chessDown(&pos, CHESS_BLACK);
}
