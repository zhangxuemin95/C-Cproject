#include"Compress.h"
int main() {
	/*cout << "============Huffman============" << endl;
	cout << "请输入文件名：";
	char filename[256];
	cin >> filename;
	int weight[256] = { 0 };
	FILE* in = fopen(filename, "rb");
	int ch;
	while ((ch = getc(in)) != EOF) {
		weight[ch]++;
	}
	fclose(in);
	cout << endl;
	cout << "原文件每个字符的权值为：" << endl;
	cout << "Byte " << "Weight" << endl;
	for (int i = 0; i < 256; i++) {
		printf("0x%02X %d\n", i, weight[i]);
	}
	HTNode pHT[512] = { {0, 0, 0} };//空出零位
	for (int i = 1; i <= 256; i++) {
		pHT[i].weight = weight[i-1];
	}
	TestHufTree(HuffmanTreeing(pHT, 256, 512));
	cout << endl;
	cout << "先序遍历哈夫曼树的结果为： " << endl;
	TestHufTree(511, pHT);
	string pHC[512] = { "" };
	HuffmanCoding(511, pHT, pHC);
	TestHuffCode(256, pHC);
	*/
	cout << "============Huffman============" << endl;
	cout << "请输入要压缩的文件名：";
	char filename[256];
	cin >> filename;
	cout << endl;
	Compress(filename);//108389 677672
	char filename1[256];
	cout << endl;
	cout << "输入要解压的文件名： ";
	cin >> filename1;
	if (Decompress(filename1) == OK) {
		cout << "解压成功" << endl;
	}
	cout << "请输入解压后文件的名字： ";
	char filename2[256];
	cin >> filename2;
	FILE* in = fopen(filename2, "rb");
	int ch;
	int length = 0;
	while ((ch = fgetc(in)) != EOF)
	{
		length++;
	}
	cout << endl << "解压后文件大小为： " << length;
	fclose(in);
	return 0;
}

void TestHufTree(HuffmanTree pHT) {
	for (int i = 1; i <= 511; i++) {
		printf("pHT[%d]\t\%d\t\%d\t\%d\t\%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

void TestHufTree(int root, HuffmanTree pHT) {
	cout << pHT[root].weight << " ";
	if (pHT[root].lchild != 0) {
		TestHufTree(pHT[root].lchild, pHT);
	}
	if (pHT[root].rchild != 0) {
		TestHufTree(pHT[root].rchild, pHT);
	}
}

void TestHuffCode(int nSize, HuffmanCode pHC) {
	cout << endl;
	cout << "Byte " << "HuffmanCode " << endl;
	for (int i = 1; i <= nSize; i++) {
		printf("0x%02X ", i - 1);
		cout << pHC[i] << endl;
	}
}