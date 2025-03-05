#include "ChessGame.h"

ChessGame::ChessGame(Man * man, AI * ai, Chess * chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	ai->init(chess);
	man->init(chess);

}

void ChessGame::play()
{
	//棋盘初始化
	chess->init();

	//开始对局
	while (1) {
		//棋手先走
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

		//AI走
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
