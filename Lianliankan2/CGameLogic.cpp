#include "pch.h"
#include "CGameLogic.h"
#include "CGameControl.h"
#include "global.h"
bool CGameLogic::SearchValidPath(int** pGameMap, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++) {
			if (pGameMap[i / 16][i % 16] != pGameMap[j / 16][j % 16] || pGameMap[i / 16][i % 16] == BLANK) continue;
			else
			{
				Vertex v1 = { i / 16, i % 16,  pGameMap[i / 16][i % 16] };
				Vertex v2 = { j / 16, j % 16,  pGameMap[j / 16][j % 16] };
				if (IsLink(pGameMap, v1, v2)) return true;
				else
				{
					ClearStack();
				}
			}
		}
	}
	return false;
}
void CGameLogic::ResetGraph(int** pGameMap)
{
	for (int i = 0; i < 100; i++) {
		//随机得到两个数坐标
		int nRow1 = rand() % CGameControl::s_nRows; int nCol1 = rand() % CGameControl::s_nCols;
		int nRow2 = rand() % CGameControl::s_nRows; int nCol2 = rand() % CGameControl::s_nCols;
		int nTmp = pGameMap[nRow1][nCol1];
		pGameMap[nRow1][nCol1] = pGameMap[nRow2][nCol2];
		pGameMap[nRow2][nCol2] = nTmp;
	}
}
bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	if (v1.nRow == v2.nRow) {
		return LinkInRow(pGameMap, v1, v2) || TwoCornorLink(pGameMap, v1, v2);
	}
	if (v1.nCol == v2.nCol) {
		return LinkInCol(pGameMap, v1, v2) || TwoCornorLink(pGameMap, v1, v2);
	}
	return OneCornorLink(pGameMap, v1, v2) || TwoCornorLink(pGameMap, v1, v2);
}
void CGameLogic::Clear(int** pGameMap, Vertex v1, Vertex v2)
{
	//将地图中要消去图片位置的值设为 -1
	pGameMap[v1.nRow][v1.nCol] = BLANK;
	pGameMap[v2.nRow][v2.nCol] = BLANK;

}
int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}
CGameLogic::CGameLogic()
{
}

CGameLogic::~CGameLogic()
{
}


// 初始化地图
int** CGameLogic::InitMap()
{
	// TODO: 在此处添加实现代码.
	//获得地图大小和花色
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	//开辟内存区域
	int** pGameMap = new int*[nRows];
	if (pGameMap == NULL) {
		// throw new CGameException(_T("内存操作异常\n"));
	}
	else
	{
		for (int i = 0; i < nRows; i++) {
			pGameMap[i] = new int[nCols];
			if (pGameMap[i] == NULL) {
				//throw new CGameException(_T("内存操作异常\n"));
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}
	//多少花色
	if ((nRows * nCols) % (nPicNum * 2) != 0) {
		ReleaseMap(pGameMap);
		////throw new CGameException(_T("游戏花色与游戏题图大小不匹配!"));
	}
	
		int nRepeatNum = nCols * nRows / nPicNum;
		int nCount = 0;
		for (int i = 0; i < nPicNum; i++) {
			//重复数
			for (int j = 0; j < nRepeatNum; j++) {
				pGameMap[nCount / nCols][nCount % nCols] = i;
				nCount++;
			}
		}
		//随机找到两个位置的图片并进行交换
		srand((int)time(NULL));
		int nVertexNum = nRows * nCols;
		for (int i = 0; i < nVertexNum; i++) {
			//随机得到两个数坐标
			int nIndex1 = rand() % nVertexNum;
			int nIndex2 = rand() % nVertexNum;
			int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
			pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
			pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
		}
	return pGameMap;
}


// 释放游戏地图
void CGameLogic::ReleaseMap(int** pGameMap)
{
	if (pGameMap == NULL) return;
	for (int i = 0; i < CGameControl::s_nRows; i++) {
		delete[] pGameMap[i];
	}
	delete[] pGameMap;
	pGameMap = NULL;
	// TODO: 在此处添加实现代码.
}

bool CGameLogic::IsBlank(int** pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++) {
		for (int j = 0; j < CGameControl::s_nCols; j++) {
			if (pGameMap[i][j] != BLANK) return false;
		}
	}
	return true;
}

// 判断横向相连
bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow = v1.nRow;
	int nCol1 = v1.nCol;
	int nCol2 = v2.nCol;
	if (nCol1 > nCol2) {
		int s = nCol1;
		nCol1 = nCol2;
		nCol2 = s;
	}
	for (int i = nCol1 + 1; i <= nCol2; i++) {
		if (i == nCol2) {
			PushVertex(v1);
			PushVertex(v2);
			return true;
		}
		if (pGameMap[nRow][i] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.nRow;
	int nRow2 = v2.nRow;
	int nCol = v1.nCol;
	if (nRow1 > nRow2) {
		int s = nRow1;
		nRow1 = nRow2;
		nRow2 = s;
	}
	for (int i = nRow1 + 1; i <= nRow2; i++) {
		if (i == nRow2) {
			PushVertex(v1);
			PushVertex(v2);
			return true;
		}
		if (pGameMap[i][nCol] != BLANK) break;
	}
	return false;
}

bool CGameLogic::OneCornorLink(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.nRow; int nCol1 = v2.nCol;
	int nRow2 = v2.nRow; int nCol2 = v1.nCol;
	Vertex v3 = { nRow1, nCol1, -1 };
	Vertex v4 = { nRow2, nCol2 , -1 };
	if (LineX(pGameMap, v1.nCol, nCol1, v1.nRow) && LineY(pGameMap, v2.nRow, nRow1, v2.nCol) && pGameMap[nRow1][nCol1] == BLANK) {
		PushVertex(v1);
		PushVertex(v3);
		PushVertex(v2);
		return true;
	}
	if (LineX(pGameMap, v2.nCol, nCol2, v2.nRow) && LineY(pGameMap, v1.nRow, nRow2, v1.nCol) && pGameMap[nRow2][nCol2] == BLANK) {
		PushVertex(v1);
		PushVertex(v4);
		PushVertex(v2);
		return true;
	}
	return false;
}

bool CGameLogic::TwoCornorLink(int** pGameMap, Vertex v1, Vertex v2)
{
	//同列两拐角
	/*if (v1.nCol == v2.nCol) {
		for (int i = 0; i < CGameControl::s_nCols; i++) {
			if (i == v1.nCol) continue;
			else
			{
				if (LineX(pGameMap, v1.nCol, i, v1.nRow) && LineX(pGameMap, v2.nCol, i, v2.nRow) && LineY(pGameMap, v1.nRow, v2.nRow, i) &&
					pGameMap[v1.nRow][i] == BLANK && pGameMap[v2.nRow][i] == BLANK) {
					Vertex v3 = { v1.nRow, i, -1 };
					Vertex v4 = { v2.nRow, i, -1 };
					PushVertex(v1);
					PushVertex(v3);
					PushVertex(v4);
					PushVertex(v2);
					return true;
				}
			}
		}
		return false;
	}
	//同行两拐角
	if (v1.nRow == v1.nRow) {
		for (int i = 0; i < CGameControl::s_nRows; i++) {
			if (i == v1.nRow) continue;
			else
			{
				if (LineY(pGameMap, v1.nRow, i, v1.nCol) && LineY(pGameMap, v2.nRow, i, v2.nCol) && LineX(pGameMap, v1.nCol, v2.nCol, i) &&
					pGameMap[i][v1.nCol] == BLANK && pGameMap[i][v2.nCol] == BLANK) {
					Vertex v3 = { i, v1.nCol, -1 };
					Vertex v4 = { i, v2.nCol, -1 };
					PushVertex(v1);
					PushVertex(v3);
					PushVertex(v4);
					PushVertex(v2);
					return true;
				}
			}
		}
		return false;
	}
	int stRow = (v1.nRow > v2.nRow) ? v2.nRow : v1.nRow;
	int enRow = (v1.nRow > v2.nRow) ? v1.nRow : v2.nRow;
	int stCol = (v1.nCol > v2.nCol) ? v2.nCol : v1.nCol;
	int enCol = (v1.nCol > v2.nCol) ? v1.nCol : v2.nCol;
	//不同行不同列两拐角
	for (int i = stRow + 1; i < enRow; i++) {
		if (LineY(pGameMap, i, v1.nRow, v1.nCol) && LineY(pGameMap, i, v2.nRow, v2.nCol) && LineX(pGameMap, v1.nCol, v2.nCol, i) &&
			pGameMap[i][v1.nCol] == BLANK && pGameMap[i][v2.nCol] == BLANK) {
			Vertex v3 = { i, v1.nCol, -1 };
			Vertex v4 = { i, v2.nCol, -1 };
			PushVertex(v1);
			PushVertex(v3);
			PushVertex(v4);
			PushVertex(v2);
			return true;
		}
	}
	for (int i = stCol + 1; i < enCol; i++) {
		if (LineX(pGameMap, v1.nCol, i, v1.nRow) && LineX(pGameMap, v2.nCol, i, v2.nRow) && LineY(pGameMap, v1.nRow, v2.nRow, i) &&
			pGameMap[v1.nRow][i] == BLANK && pGameMap[v2.nRow][i] == BLANK) {
			Vertex v3 = { v1.nRow, i, -1 };
			Vertex v4 = { v2.nRow, i, -1 };
			PushVertex(v1);
			PushVertex(v3);
			PushVertex(v4);
			PushVertex(v2);
			return true;
		}
	}
	return false;*/
	for (int i = 0; i < CGameControl::s_nCols; i++) {
		if (i == v1.nCol || i == v2.nCol) continue;
		if (LineX(pGameMap, v1.nCol, i, v1.nRow) && LineX(pGameMap, v2.nCol, i, v2.nRow) && LineY(pGameMap, v1.nRow, v2.nRow, i) && pGameMap[v1.nRow][i] == BLANK && pGameMap[v2.nRow][i] == BLANK) {
			Vertex v3 = { v1.nRow, i, -1 };
			Vertex v4 = { v2.nRow, i, -1 }; 
			PushVertex(v1);
			PushVertex(v3);
			PushVertex(v4);
			PushVertex(v2);
			return true;
		}
	}
	for (int i = 0; i < CGameControl::s_nRows; i++) {
		if (i == v1.nRow || i == v2.nRow) continue;
		if (LineY(pGameMap, i, v1.nRow, v1.nCol) && LineY(pGameMap, i, v2.nRow, v2.nCol) && LineX(pGameMap, v1.nCol, v2.nCol, i) &&pGameMap[i][v1.nCol] == BLANK && pGameMap[i][v2.nCol] == BLANK) {
			Vertex v3 = { i, v1.nCol, -1 };
			Vertex v4 = { i, v2.nCol, -1 };
			PushVertex(v1);
			PushVertex(v3);
			PushVertex(v4);
			PushVertex(v2);
			return true;
		}
	}
	return false;
}
/// <summary>
/// LineX 和 LineY均不判断端点
/// </summary>
/// <param name="pGameMap"></param>
/// <param name="nRow1"></param>
/// <param name="nRow2"></param>
/// <param name="nCol"></param>
/// <returns></returns>
bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol)
{
	if (nRow1 > nRow2) {
		int s = nRow1;
		nRow1 = nRow2;
		nRow2 = s;
	}
	for (int i = nRow1 + 1; i < nRow2; i++) {
		if (pGameMap[i][nCol] != BLANK ) return false;
	}
	return true;
}

bool CGameLogic::LineX(int** pGameMap, int nCol1, int nCol2, int nRow)
{
	if (nCol1 > nCol2) {
		int s = nCol1;
		nCol1 = nCol2;
		nCol2 = s;
	}
	for (int i = nCol1 + 1; i <= nCol2; i++) {
		if (i == nCol2) return true;
		if (pGameMap[nRow][i] != BLANK) break;
	}
	return false;
}

void CGameLogic::PushVertex(Vertex v)
{
	if (m_nVexNum == 4) {

	}
	else
	{
		m_avPath[m_nVexNum] = v;
		m_nVexNum++;
	}
}

void CGameLogic::PopVertex(Vertex &v)
{
	if (m_nVexNum == 0) {

	}
	else {
		v = m_avPath[m_nVexNum];
		m_nVexNum--;
	}
}

void CGameLogic::ClearStack()
{
	m_nVexNum = 0;
}
