#pragma once
#include "Chess.h"

//在进行AI初始化时，我们要考虑两个数据成员：
//棋盘对象：表示对哪个棋盘下棋
//评分数组：存储AI对棋盘所有落点的价值评估，以便AI做出最优决策


class AI
{
public:
	void init(Chess *chess);//初始化
	void go();//下棋

private:
	//棋盘对象
	Chess* chess;
	//评分数组
	vector<vector<int>>scoreMap;
private:
	// AI对棋局进行评分
	void calculateScore();
private:
	//找出价值最高的点落子
	ChessPos think();

};

