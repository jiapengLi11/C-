#include "Chess.h"
#include<math.h>
#include<conio.h>
#include<mmsystem.h>//播放音乐
#pragma comment(lib,"winmm.lib")

// 解决Easyx不支持png格式图片的函数   解决棋子周围黑边
void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); // 获取picture的显存指针
	int picture_width = picture->getwidth(); // 获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); // 获取picture的高度，EASYX自带
	int graphWidth = getwidth();       // 获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     // 获取绘图区的高度，EASYX自带
	int dstX = 0;    // 在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; // 在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); // 0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); // 获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   // G
			int sb = src[srcX] & 0xff;              // B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; // 在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  // 公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         // αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              // αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;//黑下
	for (int i = 0; i < gradeSize; i++) {
		vector<int>row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	//创建游戏窗口
	initgraph(897, 895);
	//显示棋盘图片
	loadimage(0, "resource/棋盘2.jpg");
	//播放开始提示音
	mciSendString("play resource/start.wav", 0, 0, 0);
	//加载棋子图片
	loadimage(&chessBlackImg, "resource/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "resource/white.png", chessSize, chessSize, true);
	//棋盘清0
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}
	//确定谁先下棋
	playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos * pos)
{//真实落子列坐标
	int col = (x - margin_x) / chessSize;//x减边缘除以一个格子大小取整
	// 真实落子行坐标
	int row = (y - margin_y) / chessSize;
	//落子左上角列坐标（准确坐标）
	int leftTopPosX = margin_x + chessSize * col;
	//落子左上角行坐标（准确坐标）
	int leftTopPosY = margin_y + chessSize * row;
	//鼠标点击位置距离真实落子位置的阈值
	int offset = chessSize * 0.4;
	//落子距离四个角的距离
	int len;
	//落子是否有效0无效1有效
	bool res = false;
	do {
		//落子距离左上角距离 勾股定理
		len = sqrt((x - leftTopPosX)*(x - leftTopPosX) + (y - leftTopPosY)*(y - leftTopPosY));
		//// 如果落子距离左上角的距离小于阈值并且当前位置没有棋子
		//就保存当前落子位置，并设置落子有效
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {//此处为空，可以落子
				res = true;
			}
			break;//小于门限值，有效落子，跳出循环，不满足则继续判断其他距离
		}
		// 落子距离右上角的距离
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		// 如果落子距离右上角的距离小于阈值并且当前位置没有棋子，就保存当前落子位置，并设置落子有效
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				res = true;
			}
			break;
		}
		// 落子距离左下角的距离
		x2 = leftTopPosX;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		// 如果落子距离右上角的距离小于阈值并且当前位置没有棋子，就保存当前落子位置，并设置落子有效
		if (len < offset)
		{
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0)
			{
				res = true;
			}
			break;
		}
		// 落子距离右下角的距离
		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		// 如果落子距离右上角的距离小于阈值并且当前位置没有棋子，就保存当前落子位置，并设置落子有效
		if (len < offset)
		{
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0)
			{
				res = true;
			}
			break;
		}
	} while (0);
	// 返回落子是否有效的判断结果
	return res;
}

void Chess::chessDown(ChessPos * pos, chess_kind chess)//棋盘落子
{
	// 加载落子音效
	mciSendString("play resource/down7.wav", 0, 0, 0);
	// 获取棋子的落子位置，需要注意绘图的左边是左上角，所以为了让棋子的中心点在行线和列线的交界处，棋子的行和列坐标都需要减0.5倍的棋格大小
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	// 根据棋子类型在对应位置生成棋子图片
	if (chess == CHESS_WHITE)
	{
		putimagePNG(x, y, &chessWhiteImg);
	}
	else
	{
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
}


int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos * pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

// 胜负判定
bool Chess::checkOver()
{
	// checkWin()函数来检查当前谁嬴谁输，如果胜负已分就返回true，否则返回false
	if (checkWin())
	{
		// 暂停
		Sleep(1500); 

		// 说明黑棋（棋手）赢
		if (playerFlag == false)
		{
			mciSendString("play resource/win.mp3", 0, 0, 0);
			loadimage(0, "resource/胜利.jpg");
		}
		// 说明白棋（AI）赢
		else
		{
			mciSendString("play resource/失败.mp3", 0, 0, 0);
			loadimage(0, "resource/失败.jpg");
		}
		// 暂停
		_getch();
		return true;
	}
	return false;
}


void Chess::updateGameMap(ChessPos * pos)
{
	//存储某落子点位置
	lastPos = *pos;
	// 存储落子信息
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	// 黑白方交换行棋
	playerFlag = !playerFlag;
}

// 检查当前谁嬴谁输，如果胜负已分就返回true，否则返回false
bool Chess::checkWin()
{
	// 某一落子点的位置
	int row = lastPos.row;
	int col = lastPos.col;
	// 落子点的水平方向
	for (int i = 0; i < 5; i++)
	{
		if (((col - i) >= 0) && ((col - i + 4) < gradeSize) && (chessMap[row][col - i] == chessMap[row][col - i + 1]) && (chessMap[row][col - i] == chessMap[row][col - i + 2]) && (chessMap[row][col - i] == chessMap[row][col - i + 3]) && (chessMap[row][col - i] == chessMap[row][col - i + 4]))
		{
			return true;
		}
	}
	// 落子点的垂直方向
	for (int i = 0; i < 5; i++)
	{
		if (((row - i) >= 0) && ((row - i + 4) < gradeSize) && (chessMap[row - i][col] == chessMap[row - i + 1][col]) && (chessMap[row - i][col] == chessMap[row - i + 2][col]) && (chessMap[row - i][col] == chessMap[row - i + 3][col]) && (chessMap[row - i][col] == chessMap[row - i + 4][col]))
		{
			return true;
		}
	}
	// 落子点的右斜方向
	for (int i = 0; i < 5; i++)
	{
		if (((row + i) < gradeSize) && (row + i - 4 >= 0) && (col - i >= 0) && ((col - i + 4) < gradeSize) && (chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1]) && (chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2]) && (chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3]) && (chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]))
		{
			return true;
		}
	}
	// 落子点的左斜方向
	for (int i = 0; i < 5; i++)
	{
		if (((row - i + 4) < gradeSize) && (row - i >= 0) && (col - i >= 0) && ((col - i + 4) < gradeSize) && (chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1]) && (chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2]) && (chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3]) && (chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]))
		{
			return true;
		}
	}
	return false;
}

