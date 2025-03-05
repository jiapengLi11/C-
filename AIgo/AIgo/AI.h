#pragma once
#include "Chess.h"

//�ڽ���AI��ʼ��ʱ������Ҫ�����������ݳ�Ա��
//���̶��󣺱�ʾ���ĸ���������
//�������飺�洢AI�������������ļ�ֵ�������Ա�AI�������ž���


class AI
{
public:
	void init(Chess *chess);//��ʼ��
	void go();//����

private:
	//���̶���
	Chess* chess;
	//��������
	vector<vector<int>>scoreMap;
private:
	// AI����ֽ�������
	void calculateScore();
private:
	//�ҳ���ֵ��ߵĵ�����
	ChessPos think();

};

