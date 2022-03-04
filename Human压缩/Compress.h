#include"Huffman.h"
#define ERROR 0
#define OK 1
struct HEAD
{
	char type[4];// �ļ�����
	int length;  //ԭ�ļ�����
	int weight[256];  //Ȩֵ��ֵ
	int tail; //�ļ�ĩβ�������볤��
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