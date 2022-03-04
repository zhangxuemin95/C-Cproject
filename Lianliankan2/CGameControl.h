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
	Vertex m_svSelectFirst;// 选中的第一个点
	Vertex m_svSelectSecond;// 选中的第二个点
private:
	int** m_pGameMap;
	CGameLogic m_GameLogic;
public:
	bool Help(Vertex avPath[4], int& nVexNum);
	void Close();
	void Reset(); // 重排
	int IsWin(int time); // 判断是否获胜
	void SetFirstPoint(int nRow, int nCol);
	void SetSecondPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4], int& nVexNum); // 消子判断, 路径暂定为两个顶点
	void StartGame();
	// 得到一个元素
	int GetElement(int nRow, int nCol);
};
#endif // !CGAMECONTROL_H