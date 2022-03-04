#pragma once
#include"global.h"
#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H
class CGameLogic
{
private:
	Vertex m_avPath[4]; //保存在经过连接判断时所经过的顶点
	int m_nVexNum = 0; //顶点个数
public:
	bool SearchValidPath(int** pGameMap, int n);
	void ResetGraph(int** pGameMap);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);
	void Clear(int** pGameMap, Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[4]);// 返回值是顶点个数
	void ClearStack(); // 清除栈
	bool IsBlank(int** pGameMap);// 判断矩阵是否清空
	CGameLogic();
	virtual ~CGameLogic();
	// 初始化地图
	int** InitMap();
	// 释放游戏地图
	void ReleaseMap(int** pGameMap);
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2); // 判断横向连通
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2); // 判断纵向连通
	bool OneCornorLink(int** pGameMap, Vertex v1, Vertex v2); // 判断只有一个拐角的连通
	bool TwoCornorLink(int** pGameMap, Vertex v1, Vertex v2); // 判断两个拐点的连通
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol); // 直线连通y轴
	bool LineX(int** pGameMap, int nCol1, int nCol2, int nRow); // 直线连通x轴
	void PushVertex(Vertex v); // 添加一个路径顶点
	void PopVertex(Vertex &v); // 取出一个路径顶点
};
#endif // !CGAMELOGIC_H


