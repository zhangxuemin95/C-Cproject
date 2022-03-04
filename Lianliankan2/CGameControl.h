#pragma once
#include "CGameLogic.h"
#include"global.h"
#ifndef CGAMECONTROL_H
#define CGAMECONTROL_H
class CGameControl
{
public:
	CGameControl();
	virtual ~CGameControl();
	static const int s_nRows = 10;
	static const int s_nCols = 16;
	static const int s_nPicNum = 10;
	Vertex m_svSelectFirst;// ѡ�еĵ�һ����
	Vertex m_svSelectSecond;// ѡ�еĵڶ�����
private:
	int** m_pGameMap;
	CGameLogic m_GameLogic;
public:
	bool Help(Vertex avPath[4], int& nVexNum);
	void Close();
	void Reset(); // ����
	int IsWin(int time); // �ж��Ƿ��ʤ
	void SetFirstPoint(int nRow, int nCol);
	void SetSecondPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4], int& nVexNum); // �����ж�, ·���ݶ�Ϊ��������
	void StartGame();
	// �õ�һ��Ԫ��
	int GetElement(int nRow, int nCol);
};
#endif // !CGAMECONTROL_H