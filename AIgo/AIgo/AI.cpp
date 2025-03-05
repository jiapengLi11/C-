#include "AI.h"

void AI::init(Chess * chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int>row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

// AI����
void AI::go()
{
	// AI���������ӵ�
	ChessPos pos = think();
	// AI��װ˼���������ֻ���ʱ��
	Sleep(1000);
	// ��AI���������ӵ�����
	chess->chessDown(&pos, CHESS_WHITE);
}


void AI::calculateScore()
{
	//����������������
	int personNum = 0;
	//����������������
	int aiNum = 0;
	//�÷����Ͽհ�λ����
	int emptyNum = 0;
	//��������������
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}
	//��ȡ���̴�С
	int size = chess->getGradeSize();
	//�Կ������ӵ�İ˸���������
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//Ϊ�յ�λ�òſ�������
			if (chess->getChessData(row, col) == 0) {
				//���ư˸�����
				for (int y = -1; y <= 0; y++) {
					for (int x = -1; x <= 1; x++) {
						//���ú����ж�����������
						personNum = 0;
						//���ð����ж�����������
						aiNum = 0;
						//���ø÷���հ׸���
						emptyNum = 0;
						//�����ظ�����
						if (y == 0 && x != 1) {
							continue;
						}
						//ԭ���겻��������
						if (!(y == 0 && x == 0)) {
							//��������ڴ����ӣ��ж�����
							for (int i = 1; i <= 4; i++) {
								int curRow = row + i * y;
								int curCol = col + i * x;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
								{
									personNum++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}
							}
							// ����ķ������
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row - i * y;
								int curCol = col - i * x;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
								{
									personNum++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}
							}
							//����
							// ����
							if (personNum == 1)
							{
								scoreMap[row][col] += 10;
							}
							// ����
							else if (personNum == 3)
							{
								// ����
								if (emptyNum == 1)
								{
									scoreMap[row][col] += 30;
								}
								// ����
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 40;
								}
							}
							// ����
							else if (personNum == 3)
							{
								// ����
								if (emptyNum == 1)
								{
									scoreMap[row][col] += 60;
								}
								// ����
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 200;
								}
							}
							// ����
							else if (personNum == 4)
							{
								scoreMap[row][col] += 20000;
							}
							// ��տհ����Ӹ���
							emptyNum = 0;
							// ��������ڸ�λ�����ӣ��ṹ��ʲô���Σ���ʱ�ǰ�����������
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row + i * y;
								int curCol = col + i * x;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
								{
									aiNum++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}
							}
							// ����ķ������
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row - i * y;
								int curCol = col - i * x;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
								{
									aiNum++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}
							}
							// ��ɫ�����޴�����
							if (aiNum == 0)
							{
								scoreMap[row][col] += 5;
							}
							// ����
							else if (aiNum == 1)
							{
								scoreMap[row][col] += 10;
							}
							// ����
							else if (aiNum == 3)
							{
								// ����
								if (emptyNum == 1)
								{
									scoreMap[row][col] += 25;
								}
								// ����
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 50;
								}
							}
							// ����
							else if (aiNum == 3)
							{
								// ����
								if (emptyNum == 1)
								{
									scoreMap[row][col] += 55;
								}
								// ����
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 10000;
								}
							}
							// ����
							else if (aiNum >= 4)
							{
								scoreMap[row][col] += 30000;
							}
						}
					}
				}
			}
		}
	}
}

// �ҳ���ֵ������ߵĵ�����
ChessPos AI::think()
{
	// �����������ļ�ֵ����
	calculateScore();
	// ��ȡ���̴�С
	int size = chess->getGradeSize();
	// �洢�����ֵ���ֵ�ĵ�
	vector<ChessPos> maxPoints;
	// ��ʼ��ֵ���ֵ
	int maxScore = 0;
	// ����������ֵ�������ĵ�
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col) == 0)
			{
				if (scoreMap[row][col] > maxScore)
				{
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore)
				{
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}
	// ����ж����ֵ���ֵ�㣬�����ȡһ����ֵ���ֵ����±�
	int index = rand() % maxPoints.size();
	// ���ؼ�ֵ���ֵ��
	return maxPoints[index];
}

