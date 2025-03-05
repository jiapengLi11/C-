#pragma once
#include<graphics.h>//easyx
#include<vector>
using namespace std;//�����ռ�

//��ʾ����λ��
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {};//��ʼ�����캯��
};

//��ʾ���ӵ�����
typedef enum {
	CHESS_WHITE = -1,
    CHESS_BLACK =  1
}chess_kind;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	//���̳�ʼ������������ͼƬ��Դ����ʼ�������������
	void init();
	//�жϣ��У��У��Ƿ���Ч����Ч�����ڲ���pos��

	bool clickBoard(int x, int y, ChessPos *pos);

	//������ָ��λ�ã�pos�������ӣ�chess��
	void chessDown(ChessPos *pos, chess_kind chess);
	 
	//��ȡ���̴�С��13��15��19��
	int getGradeSize();

	//��ȡָ��λ���Ǻ��壬�ף���
	int getChessData(ChessPos *pos);
	int getChessData(int row, int col);

	//��ֽ������
	bool checkOver();

private:
	IMAGE chessBlackImg;//����
	IMAGE chessWhiteImg;//����

	int gradeSize;//���̴�С
	int margin_x;//�������߽�
	int margin_y;//���̶����߽�
	float chessSize;//���Ӵ�С(С����)
	/*
		�洢��ǰ��ֵ����ӷֲ�����
		���磺chessMap[3][5]��ʾ���̵ĵ�3�е�5�е����������0���հף�1�����ӣ�-1�����ӣ�
	*/
	vector<vector<int>>chessMap;
	/*
		��ʾ���ڸ�˭���壨���ӣ�
		true���ú����ߣ�false���ð�����
	*/
	// ��������Ϣ�洢����ά������
	void updateGameMap(ChessPos* pos);

	bool playerFlag;
private:
	// ��鵱ǰ˭Ӯ˭�䣬���ʤ���ѷ־ͷ���true�����򷵻�false
	bool checkWin();
private:
	// ĳһ���ӵ��λ��
	ChessPos lastPos;


};

