#include<D:\C语言\通信网构建\SqList.h>
#include<iostream>
#include<cstring>
#define numMAX 20
#define StrMAX 100
#define MAX 10000
using namespace std;
struct Vex {
	string Code;
	string Name;
	Vex* operator =(Vex svex) {
		this->Code = svex.Code;
		this->Name = svex.Name;
		return this;
	}
	bool operator == (Vex svex) {
		if (this->Code == svex.Code && this->Name == svex.Name) return true;
		else return false;
	}
};
struct Edge {
	Vex vex1;
	Vex vex2;
	int weight;
	Edge* operator =(Edge sedge) {
		this->vex1 = sedge.vex1;
		this->vex2 = sedge.vex2;
		this->weight = sedge.weight;
		return this;
	}
	bool operator==(Edge sedge) {
		if (this->vex1 == sedge.vex1 && this->vex2 == sedge.vex2 && this->weight == sedge.weight) return true;
		else return false;
	}
	bool operator < (Edge sedge) {
		if (this->weight < sedge.weight) return true;
		else return false;
	}
};
class Graph
{
public:
	int AdjMatrix[numMAX][numMAX]; //邻接矩阵
	SqList<Vex> Vexs;
	SqList<Edge> Edges;
	int VexNum;
public:
	Graph();
	~Graph();
	bool InsertVex(Vex svex);
	bool DeleteVex(Vex &svex);
	bool UpdateVex(string code, Vex svex);
	bool InsertEdge(Edge sedge);
	bool DeleteEdge(Edge& sedge);
	bool UpdateEdge(Edge sedge);
	Edge GetEdge(string vex1Code, string vex2Code);
	Vex GetVex(string vexCode);
	void SetVexNum(int num);
	int PrimMinTree(Edge aPath[]);
	int KrusKalMinTree(Edge aPath[]);
};

Graph::Graph()
{
	VexNum = 0;
	int i, j;
	for(i = 0; i < numMAX; i++)
		for (j = 0; j < numMAX; j++) {
			if (j == i) AdjMatrix[i][j] = 0;
			else AdjMatrix[i][j] = 10000;
		}
}

Graph::~Graph()
{
	Vexs.~SqList();
	Edges.~SqList();
}

bool Graph::InsertVex(Vex svex)
{
	if (Vexs.Insert(svex) == 1) {
		VexNum++;
		return true;
	}
	else return false;
}

bool Graph::DeleteVex(Vex& svex)
{
	int index = Vexs.Locate(svex);
	if (index == -1)return false;
	else
	{
		Vexs.Delete(index, svex); // 可能出错，位置错开
		string code = svex.Code;
		int i = (int)code[1];
		for (int j = 0; j < VexNum; j++) {
			if (AdjMatrix[i][j] != 10000 || AdjMatrix[j][i] != 10000)
				if (i != j) AdjMatrix[i][j] = AdjMatrix[j][i] = 10000;
		}
		VexNum--;
		return true;
	}
}
bool Graph::UpdateVex(string code, Vex svex)
{
	int index = 0;
	Vex vex;
	for (int i = 1; i <= VexNum; i++) {
		Vexs.GetElem(i, vex);
		if (vex.Code == code) {
			index = Vexs.Locate(vex);
			break;
		}
	}
	if (index == 0)return false;
	else
	{
		Vexs.SetElem(index, svex);
		return false;
	}
}
bool Graph::InsertEdge(Edge sedge)
{
	if (Edges.Insert(sedge) == 1)
	{
		Vex svex1 = sedge.vex1;
		Vex svex2 = sedge.vex2;
		int adjvx1 = svex1.Code[1] - 48;
		int adjvx2 = svex2.Code[1] - 48;
		AdjMatrix[adjvx1][adjvx2] = sedge.weight;
		AdjMatrix[adjvx2][adjvx1] = sedge.weight;
		return true;
	}
	else
	{
		return false;
	}
}
bool Graph::DeleteEdge(Edge& sedge)
{
	int index = Edges.Locate(sedge);
	if (index == -1) return false;
	else
	{
		int adjvx1 = sedge.vex1.Code[1];
		int adjvx2 = sedge.vex2.Code[2];
		AdjMatrix[adjvx1][adjvx2] = AdjMatrix[adjvx2][adjvx1] = 10000;
		return true;
	}
}
bool Graph::UpdateEdge(Edge sedge)
{
	int index = 0;
	int length = Edges.GetLength();
	Edge edge;
	for (int i = 1; i <= length; i++) {
		Edges.GetElem(i, edge);
		if (edge.vex1 == sedge.vex1 && edge.vex2 == sedge.vex2) {
			index = Edges.Locate(edge);
			break;
		}
	}
	if (index == 0)return false;
	else
	{
		Edges.SetElem(index, sedge);
		int adjvx1 = sedge.vex1.Code[1];
		int adjvx2 = sedge.vex2.Code[2];
		AdjMatrix[adjvx1][adjvx2] = AdjMatrix[adjvx2][adjvx1] = sedge.weight;
		return false;
	}
}

Edge Graph::GetEdge(string vex1Code, string vex2Code)
{
	Edge noedge; noedge.weight = 10000;
	bool flag = false;
	int j = Edges.GetLength();
	Edge sedge;
	for (int i = 1; i <= j; i++) {
	Edges.GetElem(i, sedge);
		if ((sedge.vex1.Code == vex1Code && sedge.vex2.Code == vex2Code) || (sedge.vex2.Code == vex1Code && sedge.vex1.Code == vex2Code)) {
			flag = true;
			break;
		}
	}
	if (flag) return sedge;
	else return noedge;
}

Vex Graph::GetVex(string vexCode)
{
	bool flag = false;
	Vex novex;
	novex.Code = "no";
	novex.Name = "no";
	int j = Vexs.GetLength();
	Vex svex;
	for (int i = 1; i <= j; i++) {
		Vexs.GetElem(i, svex);
		if (svex.Code == vexCode) {
			flag = true;
			break;
		}
	}
	if (flag) return svex;
	else return novex;
}

void Graph::SetVexNum(int num)
{
	VexNum = num;
}

int Graph::PrimMinTree(Edge aPath[])
{
	struct Closedge
	{
		string code;
		int lowcost;
		string point;
	};
	Vex u;
	Vexs.GetElem(1, u);
	Vex svex;
	Closedge* close = new Closedge[VexNum];
	for (int i = 0; i < VexNum; i++) {
		Vexs.GetElem(i + 1, svex);
		close[i].code = svex.Code;
		if (svex == u) {
			close[i].point = "over";
			close[i].lowcost = 0;
		}
		else
		{
			close[i].point = u.Code;
			int m = svex.Code[1] - 48;
			int n = u.Code[1] - 48;
			close[i].lowcost = AdjMatrix[m][n];
		}
	}
	int Lowcost;
	int x;
	int m = 0;
	while (m < (VexNum - 1)) {
		Lowcost = 10000;
		for (int j = 0; j < VexNum; j++) {
			if (close[j].lowcost < Lowcost && close[j].lowcost != 0) { Lowcost = close[j].lowcost; x = j; }
		}
		aPath[m++] = GetEdge(close[x].code, close[x].point);
		u = GetVex(close[x].code);
		for (int i = 0; i < VexNum; i++) {
			if (close[i].lowcost != 0) {
				if (close[i].code == u.Code) {
					close[i].point = "over";
					close[i].lowcost = 0;
				}
				else
				{
					if (close[i].lowcost > GetEdge(close[i].code, u.Code).weight)
					{
						close[i].point = u.Code;
						close[i].lowcost = GetEdge(close[i].code, u.Code).weight;
					}
				}
			}
		}
	}
	delete[] close;
	close = NULL;
	return 1;
}

int Graph::KrusKalMinTree(Edge aPath[])
{
	int* ctn = new int[VexNum];
	int* rank = new int[VexNum];
	for (int i = 0; i < VexNum; i++) { ctn[i] = i, rank[i] = 1; }
	int x = 0;
	Edge sedge;
	int m = 0;
	int code1;
	int code2;
	Edges.sort();
	for (int i = 1; i <= Edges.GetLength() && m < (VexNum - 1); i++) {
		Edges.GetElem(i, sedge);
		code1 = (sedge.vex1.Code[1] - 48);
		code2 = (sedge.vex2.Code[1] - 48);
		if (ctn[code1] == ctn[code2]) {

		}
		else
		{
			aPath[m++] = sedge;
			if (rank[code1] >= rank[code2]) {
				int a = ctn[code2];
				ctn[code2] = ctn[code1]; rank[code2]--; rank[code1]++;
				for (int i = 0; i < VexNum; i++) {
					if (ctn[i] == a) {
						ctn[i] = ctn[code1];
						rank[i]--;
						rank[code1]++;
					}
					if (ctn[i] == code1) rank[i] = rank[code1];
				}
			}
			else
			{
				int a = ctn[code1];
				ctn[code1] = ctn[code2]; rank[code1]--; rank[code2]++;
				for (int i = 0; i < VexNum; i++) {
					if (ctn[i] == a) {
						ctn[i] = ctn[code2];
						rank[i]--;
						rank[code2]++;
					}
					if (ctn[i] == code2) rank[i] = rank[code2];
				}
			}
		}
		
	}
	delete[] ctn; ctn = NULL;
	delete[] rank; rank = NULL;
	return 1;
}
int main() {
	/*Graph graph;
	Vex v1; v1.Code = "V0"; v1.Name = "北京";
	Vex v2; v2.Code = "V1"; v2.Name = "成都";
	Vex v3; v3.Code = "V2"; v3.Name = "武汉";
	Vex v4; v4.Code = "V3"; v4.Name = "上海";
	Vex v5; v5.Code = "V4"; v5.Name = "广州";
	Vex v6; v6.Code = "V5"; v6.Name = "深圳";
	Edge e1; e1.vex1 = v1; e1.vex2 = v2; e1.weight = 6;
	Edge e2; e2.vex1 = v1; e2.vex2 = v3; e2.weight = 1;
	Edge e3; e3.vex1 = v1; e3.vex2 = v4; e3.weight = 5;
	Edge e4; e4.vex1 = v2; e4.vex2 = v3; e4.weight = 5;
	Edge e5; e5.vex1 = v3; e5.vex2 = v4; e5.weight = 5;
	Edge e6; e6.vex1 = v2; e6.vex2 = v5; e6.weight = 3;
	Edge e7; e7.vex1 = v3; e7.vex2 = v5; e7.weight = 6;
	Edge e8; e8.vex1 = v3; e8.vex2 = v6; e8.weight = 4;
	Edge e9; e9.vex1 = v5; e9.vex2 = v6; e9.weight = 6;
	Edge e10; e10.vex1 = v4; e10.vex2 = v6; e10.weight = 2;
	graph.InsertVex(v1); graph.InsertVex(v2); graph.InsertVex(v3); graph.InsertVex(v4); graph.InsertVex(v5); graph.InsertVex(v6);
	graph.InsertEdge(e1); graph.InsertEdge(e2); graph.InsertEdge(e3); graph.InsertEdge(e4); graph.InsertEdge(e5); graph.InsertEdge(e6); graph.InsertEdge(e7); graph.InsertEdge(e8); graph.InsertEdge(e9); graph.InsertEdge(e10);
	Edge aPath1[6];
	Edge aPath2[6];
	Edge sedge;
	graph.KrusKalMinTree(aPath2);
	graph.PrimMinTree(aPath1);
	for (int i = 0; i < 6; i++)
	{
		cout << aPath1[i].vex1.Code + "  " + aPath1[i].vex2.Code << endl;
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << aPath2[i].vex1.Code + "  " + aPath2[i].vex2.Code << endl;
	}
	graph.~Graph();*/
	Graph graph;
	string code1;
	string code2;
	string name;
	bool flag = true;
	bool guard = true;
	Vex svex, svex1, svex2;
	Edge sedge;
	int i = 0;
	while (flag)
	{
		if (guard) {
			cout << "欢迎进入通信网络构造程序" << endl; guard = false;
		}
		cout << "------------------------------------" << endl;
		cout << "1 信息输入" << endl; cout << "2 城市信息更新" << endl; cout << "3 距离信息更新" << endl; cout << "4 获得通信网" << endl;
		cout << "5 退出程序" << endl;
		cout << "请选择功能" << endl;
		int j;
		cin >> j;
		switch(j)
		{
		case 1 : 
		{cout << "请按照提示完成信息的输入：" << endl;
		cout << "请输入城市个数" << endl;
		int num;
		char ch[3];
		ch[0] = 'V';
		ch[2] = '\0';
		cin >> num;
		cout << "请输入全部城市的名称，并以空格间隔，以回车结束。";
		for (int m = 0; m < num; m++) {
			cin >> name;
			svex.Name = name;
			ch[1] = 48 + i;
			i++;
			svex.Code = ch;
			graph.InsertVex(svex);
		}
		cout << "下面是系统编辑好的信息" << endl;
		for (int m = 0; m < graph.VexNum; m++) {
			graph.Vexs.GetElem(m + 1, svex);
			cout << svex.Code << "  " << svex.Name << endl;
		}
		cout << "请根据城市的编号输入城市间的距离" << endl;
		bool flag1 = true;
		while (flag1)
		{
			cout << "1 输入" << endl;
			cout << "0 结束输入" << endl;
			int m;
			cin >> m;
			switch (m)
			{
			case 0: flag1 = false;
				break;
			default:
				cout << "输入城市编号和距离，以空格间隔" << endl;
				cin >> code1;
				cin >> code2;
				svex1 = graph.GetVex(code1);
				svex2 = graph.GetVex(code2);
				int weight;
				cin >> weight;
				sedge.vex1 = svex1;
				sedge.vex2 = svex2;
				sedge.weight = weight;
				graph.InsertEdge(sedge);
				break;
			}
		}
		break; }
		case 2 : 
		{cout << "请输入要修改的城市编号" << endl;
		cin >> code1;
		svex.Code = code1;
		cout << "请输入修改后的名称" << endl;
		cin >> name;
		svex.Name = name;
		graph.UpdateVex(code1, svex);
		break; }
		case 3 :
		{cout << "请输入要修改的城市编号" << endl;
		cin >> code1;
		cin >> code2;
		svex1 = graph.GetVex(code1);
		svex2 = graph.GetVex(code2);
		sedge.vex1 = svex1;
		sedge.vex2 = svex2;
		cout << "请输入修改后的距离" << endl;
		int weight;
		cin >> weight;
		sedge.weight = weight;
		graph.UpdateEdge(sedge);
		break; }
		case 4 :
		{Edge* aPath = new Edge[i - 1];
		cout << "以输入的第一个城市构建的交通网" << endl;
		graph.PrimMinTree(aPath);
		for (int m = 0; m < (i - 1); m++) {
			cout << aPath[m].vex1.Code + aPath[m].vex1.Name << "  " << aPath[m].vex2.Code + aPath[m].vex2.Name << "  " << aPath[m].weight << endl;
		}
		cout << "按距离构建的交通网" << endl;
		graph.KrusKalMinTree(aPath);
		for (int m = 0; m < (i - 1); m++) {
			cout << aPath[m].vex1.Code + aPath[m].vex1.Name << "  " << aPath[m].vex2.Code + aPath[m].vex2.Name << "  " << aPath[m].weight << endl;
		}
		delete[] aPath;
		aPath = NULL;
		break; }
		default:
		{flag = false;
		break; }
		}
	}
	graph.~Graph();
}