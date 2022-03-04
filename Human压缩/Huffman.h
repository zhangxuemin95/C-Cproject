#include<iostream>
#include<cstring>
#include<bitset>
using namespace std;
struct HTNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
};
typedef HTNode* HuffmanTree;
typedef string* HuffmanCode;
int Select(HuffmanTree pHT, int nSize);
HuffmanTree HuffmanTreeing(HTNode pHT[], int nSize1, int nSize2);
void HuffmanCoding(int root, HuffmanTree pHT, HuffmanCode pHC);
void TestHufTree(HuffmanTree pHT);
void TestHufTree(int root, HuffmanTree pHT);
void TestHuffCode(int sum, HuffmanCode pHC);