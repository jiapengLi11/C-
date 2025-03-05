#pragma once
#include<graphics.h>//easyx
#include<vector>
using namespace std;//命名空间

//表示落子位置
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {};//初始化构造函数
};

//表示棋子的种类
typedef enum {
	CHESS_WHITE = -1,
    CHESS_BLACK =  1
}chess_kind;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	//棋盘初始化：加载棋盘图片资源，初始化棋盘相关数据
	void init();
	//判断（行，列）是否有效，有效保存在参数pos中

	bool clickBoard(int x, int y, ChessPos *pos);

	//在棋盘指定位置（pos），落子（chess）
	void chessDown(ChessPos *pos, chess_kind chess);
	 
	//获取棋盘大小（13，15，19）
	int getGradeSize();

	//获取指定位置是黑棋，白，空
	int getChessData(ChessPos *pos);
	int getChessData(int row, int col);

	//棋局结束检查
	bool checkOver();

private:
	IMAGE chessBlackImg;//黑子
	IMAGE chessWhiteImg;//白子

	int gradeSize;//棋盘大小
	int margin_x;//棋盘左侧边界
	int margin_y;//棋盘顶部边界
	float chessSize;//棋子大小(小方格)
	/*
		存储当前棋局的棋子分布数据
		例如：chessMap[3][5]表示棋盘的第3行第5列的落子情况（0：空白；1：黑子；-1：白子）
	*/
	vector<vector<int>>chessMap;
	/*
		表示现在该谁下棋（落子）
		true：该黑子走；false：该白子走
	*/
	// 将落子信息存储到二维数组中
	void updateGameMap(ChessPos* pos);

	bool playerFlag;
private:
	// 检查当前谁赢谁输，如果胜负已分就返回true，否则返回false
	bool checkWin();
private:
	// 某一落子点的位置
	ChessPos lastPos;


};

