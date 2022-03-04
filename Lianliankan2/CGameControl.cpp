#include "pch.h"
#include "CGameControl.h"
#include "CGameLogic.h"
CGameControl::CGameControl()
{
}
CGameControl::~CGameControl()
{
}
bool CGameControl::Help(Vertex avPath[4], int& nVexNum)
{
	if (m_GameLogic.SearchValidPath(m_pGameMap, CGameControl::s_nRows * CGameControl::s_nCols)) {
		nVexNum = m_GameLogic.GetVexPath(avPath);
		m_GameLogic.ClearStack();
		return true;
	}
	return false;
}
void CGameControl::Close()
{
	m_GameLogic.ReleaseMap(m_pGameMap);
}
void CGameControl::Reset()
{
	m_GameLogic.ResetGraph(m_pGameMap);
}
int CGameControl::IsWin(int time)
{
	if (time <= 0) return NOTIME;
	if (m_GameLogic.IsBlank(m_pGameMap) == true) return WIN;
	return GONON;
}
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelectFirst.nRow = nRow;
	m_svSelectFirst.nCol = nCol;
	m_svSelectFirst.nPicNum = GetElement(nRow, nCol);
}
void CGameControl::SetSecondPoint(int nRow, int nCol)
{
	m_svSelectSecond.nRow = nRow;
	m_svSelectSecond.nCol = nCol;
	m_svSelectSecond.nPicNum = GetElement(nRow, nCol);
}
bool CGameControl::Link(Vertex avPath[4], int& nVexNum)
{
	if (m_svSelectFirst.nPicNum != m_svSelectSecond.nPicNum || m_svSelectFirst.nPicNum == BLANK) return false;//点击的不同种照片 或 点击空白
	if (m_svSelectFirst.nRow == m_svSelectSecond.nRow && m_svSelectFirst.nCol == m_svSelectSecond.nCol) return false;//点击同一张照片
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelectFirst, m_svSelectSecond)) {
		nVexNum = m_GameLogic.GetVexPath(avPath);
		m_GameLogic.Clear(m_pGameMap, m_svSelectFirst, m_svSelectSecond);
		m_GameLogic.ClearStack();
		return true;
	}
	return false;
}
//开始游戏
void CGameControl::StartGame()
{
	m_pGameMap = m_GameLogic.InitMap();
	// TODO: 在此处添加实现代码.
}


// 得到一个元素
int CGameControl::GetElement(int nRow, int nCol)
{
	// TODO: 在此处添加实现代码.
	return m_pGameMap[nRow][nCol];
}
