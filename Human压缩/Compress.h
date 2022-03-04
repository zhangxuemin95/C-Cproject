#include"Huffman.h"
#define ERROR 0
#define OK 1
struct HEAD
{
	char type[4];// 文件类型
	int length;  //原文件长度
	int weight[256];  //权值数值
	int tail; //文件末尾哈夫曼码长度
};
int Compress(const char* pFilename);
typedef  unsigned char* BUFFER;
unsigned char Str2byte(string pBinStr);
int Encode(const char* pFilename, const HuffmanCode pHC, unsigned char* &pBuffer, const int nSize, HEAD &shead);
int initHead(const char* pFilename, HEAD& shead);
int writeFile(const char* pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize);
int Decompress(const char* pFilename);
string Str3byte(int byte);
string HuffmanDecoding(const char* pFilename, int root, HuffmanTree pHT, HEAD* shead);
string Str4byte(int byte, int tail);