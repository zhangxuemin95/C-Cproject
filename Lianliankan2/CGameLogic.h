#pragma once
#include"global.h"
#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H
class CGameLogic
{
private:
	Vertex m_avPath[4]; //�����ھ��������ж�ʱ�������Ķ���
	int m_nVexNum = 0; //�������
public:
	bool SearchValidPath(int** pGameMap, int n);
	void ResetGraph(int** pGameMap);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);
	void Clear(int** pGameMap, Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[4]);// ����ֵ�Ƕ������
	void ClearStack(); // ���ջ
	bool IsBlank(int** pGameMap);// �жϾ����Ƿ����
	CGameLogic();
	virtual ~CGameLogic();
	// ��ʼ����ͼ
	int** InitMap();
	// �ͷ���Ϸ��ͼ
	void ReleaseMap(int** pGameMap);
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2); // �жϺ�����ͨ
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2); // �ж�������ͨ
	bool OneCornorLink(int** pGameMap, Vertex v1, Vertex v2); // �ж�ֻ��һ���սǵ���ͨ
	bool TwoCornorLink(int** pGameMap, Vertex v1, Vertex v2); // �ж������յ����ͨ
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol); // ֱ����ͨy��
	bool LineX(int** pGameMap, int nCol1, int nCol2, int nRow); // ֱ����ͨx��
	void PushVertex(Vertex v); // ���һ��·������
	void PopVertex(Vertex &v); // ȡ��һ��·������
};
#endif // !CGAMELOGIC_H


