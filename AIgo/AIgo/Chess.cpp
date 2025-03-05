#include "Chess.h"
#include<math.h>
#include<conio.h>
#include<mmsystem.h>//��������
#pragma comment(lib,"winmm.lib")

// ���Easyx��֧��png��ʽͼƬ�ĺ���   ���������Χ�ڱ�
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); // ��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); // ��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); // ��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       // ��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     // ��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    // ���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; // ���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); // 0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); // ��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   // G
			int sb = src[srcX] & 0xff;              // B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; // ���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  // ��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         // ��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              // ��p=sa/255 , FP=sb , BP=db
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
	playerFlag = CHESS_BLACK;//����
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
	//������Ϸ����
	initgraph(897, 895);
	//��ʾ����ͼƬ
	loadimage(0, "resource/����2.jpg");
	//���ſ�ʼ��ʾ��
	mciSendString("play resource/start.wav", 0, 0, 0);
	//��������ͼƬ
	loadimage(&chessBlackImg, "resource/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "resource/white.png", chessSize, chessSize, true);
	//������0
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}
	//ȷ��˭������
	playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos * pos)
{//��ʵ����������
	int col = (x - margin_x) / chessSize;//x����Ե����һ�����Ӵ�Сȡ��
	// ��ʵ����������
	int row = (y - margin_y) / chessSize;
	//�������Ͻ������꣨׼ȷ���꣩
	int leftTopPosX = margin_x + chessSize * col;
	//�������Ͻ������꣨׼ȷ���꣩
	int leftTopPosY = margin_y + chessSize * row;
	//�����λ�þ�����ʵ����λ�õ���ֵ
	int offset = chessSize * 0.4;
	//���Ӿ����ĸ��ǵľ���
	int len;
	//�����Ƿ���Ч0��Ч1��Ч
	bool res = false;
	do {
		//���Ӿ������ϽǾ��� ���ɶ���
		len = sqrt((x - leftTopPosX)*(x - leftTopPosX) + (y - leftTopPosY)*(y - leftTopPosY));
		//// ������Ӿ������Ͻǵľ���С����ֵ���ҵ�ǰλ��û������
		//�ͱ��浱ǰ����λ�ã�������������Ч
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {//�˴�Ϊ�գ���������
				res = true;
			}
			break;//С������ֵ����Ч���ӣ�����ѭ����������������ж���������
		}
		// ���Ӿ������Ͻǵľ���
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		// ������Ӿ������Ͻǵľ���С����ֵ���ҵ�ǰλ��û�����ӣ��ͱ��浱ǰ����λ�ã�������������Ч
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				res = true;
			}
			break;
		}
		// ���Ӿ������½ǵľ���
		x2 = leftTopPosX;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		// ������Ӿ������Ͻǵľ���С����ֵ���ҵ�ǰλ��û�����ӣ��ͱ��浱ǰ����λ�ã�������������Ч
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
		// ���Ӿ������½ǵľ���
		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		// ������Ӿ������Ͻǵľ���С����ֵ���ҵ�ǰλ��û�����ӣ��ͱ��浱ǰ����λ�ã�������������Ч
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
	// ���������Ƿ���Ч���жϽ��
	return res;
}

void Chess::chessDown(ChessPos * pos, chess_kind chess)//��������
{
	// ����������Ч
	mciSendString("play resource/down7.wav", 0, 0, 0);
	// ��ȡ���ӵ�����λ�ã���Ҫע���ͼ����������Ͻǣ�����Ϊ�������ӵ����ĵ������ߺ����ߵĽ��紦�����ӵ��к������궼��Ҫ��0.5��������С
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	// �������������ڶ�Ӧλ����������ͼƬ
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

// ʤ���ж�
bool Chess::checkOver()
{
	// checkWin()��������鵱ǰ˭��˭�䣬���ʤ���ѷ־ͷ���true�����򷵻�false
	if (checkWin())
	{
		// ��ͣ
		Sleep(1500); 

		// ˵�����壨���֣�Ӯ
		if (playerFlag == false)
		{
			mciSendString("play resource/win.mp3", 0, 0, 0);
			loadimage(0, "resource/ʤ��.jpg");
		}
		// ˵�����壨AI��Ӯ
		else
		{
			mciSendString("play resource/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "resource/ʧ��.jpg");
		}
		// ��ͣ
		_getch();
		return true;
	}
	return false;
}


void Chess::updateGameMap(ChessPos * pos)
{
	//�洢ĳ���ӵ�λ��
	lastPos = *pos;
	// �洢������Ϣ
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	// �ڰ׷���������
	playerFlag = !playerFlag;
}

// ��鵱ǰ˭��˭�䣬���ʤ���ѷ־ͷ���true�����򷵻�false
bool Chess::checkWin()
{
	// ĳһ���ӵ��λ��
	int row = lastPos.row;
	int col = lastPos.col;
	// ���ӵ��ˮƽ����
	for (int i = 0; i < 5; i++)
	{
		if (((col - i) >= 0) && ((col - i + 4) < gradeSize) && (chessMap[row][col - i] == chessMap[row][col - i + 1]) && (chessMap[row][col - i] == chessMap[row][col - i + 2]) && (chessMap[row][col - i] == chessMap[row][col - i + 3]) && (chessMap[row][col - i] == chessMap[row][col - i + 4]))
		{
			return true;
		}
	}
	// ���ӵ�Ĵ�ֱ����
	for (int i = 0; i < 5; i++)
	{
		if (((row - i) >= 0) && ((row - i + 4) < gradeSize) && (chessMap[row - i][col] == chessMap[row - i + 1][col]) && (chessMap[row - i][col] == chessMap[row - i + 2][col]) && (chessMap[row - i][col] == chessMap[row - i + 3][col]) && (chessMap[row - i][col] == chessMap[row - i + 4][col]))
		{
			return true;
		}
	}
	// ���ӵ����б����
	for (int i = 0; i < 5; i++)
	{
		if (((row + i) < gradeSize) && (row + i - 4 >= 0) && (col - i >= 0) && ((col - i + 4) < gradeSize) && (chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1]) && (chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2]) && (chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3]) && (chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]))
		{
			return true;
		}
	}
	// ���ӵ����б����
	for (int i = 0; i < 5; i++)
	{
		if (((row - i + 4) < gradeSize) && (row - i >= 0) && (col - i >= 0) && ((col - i + 4) < gradeSize) && (chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1]) && (chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2]) && (chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3]) && (chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]))
		{
			return true;
		}
	}
	return false;
}

