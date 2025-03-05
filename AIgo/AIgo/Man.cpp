#include "Man.h"

void Man::init(Chess * chess)
{
	this->chess = chess;
}

//��������
void Man::go()
{
	//��꺯��
	MOUSEMSG msg;
	//����λ��
	ChessPos pos;
	while (1) {
		//��ȡ�������Ϣ
		msg = GetMouseMsg();
		//ͨ��chess�����ж�����λ���Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	
	}
	//����
	chess->chessDown(&pos, CHESS_BLACK);
}
