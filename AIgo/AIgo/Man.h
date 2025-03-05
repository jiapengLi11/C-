#pragma once
#include"Chess.h"

class Man
{
public:
	//成员函数
	void init(Chess *chess);//初始化
	void go();//下棋

private:
	Chess* chess; //棋盘数据成员
};

