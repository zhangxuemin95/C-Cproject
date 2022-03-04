#include"Compress.h"
int Decompress(const char* pFilename) {
	FILE* in = fopen(pFilename, "rb");
	HEAD* shead = (HEAD*)malloc(sizeof(HEAD));
	fread(shead, sizeof(HEAD), 1, in);
	fclose(in);
	HTNode pHT[512] = { {0, 0, 0} };
	for (int i = 1; i <= 256; i++) {
		pHT[i].weight = shead->weight[i - 1];
	}
	HuffmanTreeing(pHT, 256, 512);
	//TestHufTree(pHT);//测试
	string newFilename = HuffmanDecoding(pFilename, 511, pHT, shead);
	free(shead);
	shead = NULL;
	return OK;
}
int Compress(const char* pFilename) {
	int weight[256] = { 0 };
	FILE* in = fopen(pFilename, "rb");
	int ch;
	while ((ch = getc(in)) != EOF) {
		weight[ch]++;
	}
	fclose(in);
	HTNode pHT[512] = { {0, 0, 0} };//空出零位
	for (int i = 1; i <= 256; i++) {
		pHT[i].weight = weight[i - 1];
	}
	string pHC[512] = { "" };
	HuffmanTreeing(pHT, 256, 512);
	HuffmanCoding(511, pHT, pHC);
	int nSize = 0;
	for (int i = 1; i <= 256; i++) {
		nSize += weight[i - 1] * pHC[i].length();
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	BUFFER pBuffer = NULL;
	HEAD shead = { "", 0, {0}, 0 };
	int pos = Encode(pFilename, pHC, pBuffer, nSize, shead);
	/*for (int i = 0; i < pos; i++) {
		cout << bitset<8>(pBuffer[i]);
	}*///输出二进制文件
	initHead(pFilename, shead);
	cout << shead.length << "字节" << endl;
	int length = writeFile(pFilename, shead, pBuffer, nSize);
	cout << "压缩比率： ";
	printf("%0.4f%%", length * 1.0 / shead.length*100);
	return 0;
}

int Encode(const char* pFilename, const HuffmanCode pHC, BUFFER &pBuffer, const int nSize, HEAD &shead) {
	//开辟缓冲区
	FILE* in = fopen(pFilename, "rb");
	pBuffer = (BUFFER)malloc(nSize * sizeof(unsigned char));
	if (!pBuffer) {
		cerr << "开辟缓冲区失败" << endl;
		return ERROR;
	}
	string cd = "";//工作区
	int pos = 0;//缓冲区指针
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		cd += pHC[ch + 1];
		while (cd.length() >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);
			cd = cd.erase(0, 8);
		}
	}
	if (cd.length() > 0) {
		shead.tail = cd.length();
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);
	in = NULL;
	return pos;
}

int initHead(const char* pFilename, HEAD& shead) {
	FILE* in = fopen(pFilename, "rb");
	strcpy(shead.type, "HUF");
	shead.length = 0;
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		shead.length++;
		shead.weight[ch]++;
	}
	fclose(in);
	in = NULL;
	return OK;
}

int writeFile(const char* pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize) {
	char filename[256] = "";
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	FILE* out = fopen(filename, "wb");
	fwrite(&sHead, sizeof(HEAD), 1,out);
	fwrite(pBuffer, sizeof(char), nSize, out);
	int length = sizeof(HEAD) + strlen(filename) + 1 + nSize;
	fclose(out);
	out = NULL;
	cout << "生成压缩文件: " << filename << endl << length << "字节" << endl;
	return length;
}

unsigned char Str2byte(string pBinStr) {
	unsigned char b = 0x00;
	for (int i = 0; i < 8 && i < pBinStr.length(); i++) {
		b = b << 1;
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}

string Str3byte(int byte) {
	char b[9] = { 0 };
	b[8] = '\0';
	for (int i = 7; i >= 0; i--) {
		b[i] = (char)((byte % 2) + 48);
		byte /= 2;
	}
	string a = b;
	return a;
}

string Str4byte(int byte, int tail) {
	string a = "";
	int i = 0;
	while (byte > 0 || i < tail)
	{
		a += (char)((byte % 2) + 48);
		byte /= 2;
		i++;//                                     检查
	}
	return a;
}

string HuffmanDecoding(const char* pFilename, int root, HuffmanTree pHT, HEAD* shead) {
	string Filename = pFilename;
	int count = 0;
	int mark = root;
	Filename.replace(Filename.find_last_of('.'), Filename.length(), "");
	Filename.insert(Filename.find_first_of('.'), "1");
	char filename[256];
	int i;
	for (i = 0; i < Filename.length(); i++) {
		filename[i] = Filename[i];
	}
	filename[i] = '\0';
	int ch = 0;
	int length = 0;
	FILE* in = fopen(pFilename, "rb");
	while ((ch = fgetc(in)) != EOF)
	{
		length++;
	}
	length -= sizeof(HEAD);
	fclose(in);
	in = fopen(pFilename, "rb");
	fseek(in, sizeof(HEAD), SEEK_SET(0));
	FILE* out = fopen(filename, "wb");
	string cd = "";
	while ((ch = fgetc(in)) != EOF)
	{
		count++;
		if (count < length) { 
			cd += Str3byte(ch); 
		}
		else
		{
			cd += Str4byte(ch, shead->tail);
		}
		int i = 0;
		while (i < cd.length()) {
			if (pHT[root].lchild == 0 && pHT[root].rchild == 0) {
				fputc(root - 1, out);
				root = mark;
			}
			else
			{
				if (cd[i] == '0') {
					root = pHT[root].lchild;
					cd.erase(0, 1);
				}
				else
				{
					root = pHT[root].rchild;
					cd.erase(0, 1);
				}
			}
		}
	}
	cout << endl << mark << endl;
	fclose(in);
	in = NULL;
	fclose(out);
	out = NULL;
	return Filename;
}
