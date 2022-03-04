#include"Compress.h"
int main() {
	/*cout << "============Huffman============" << endl;
	cout << "�������ļ�����";
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
	cout << "ԭ�ļ�ÿ���ַ���ȨֵΪ��" << endl;
	cout << "Byte " << "Weight" << endl;
	for (int i = 0; i < 256; i++) {
		printf("0x%02X %d\n", i, weight[i]);
	}
	HTNode pHT[512] = { {0, 0, 0} };//�ճ���λ
	for (int i = 1; i <= 256; i++) {
		pHT[i].weight = weight[i-1];
	}
	TestHufTree(HuffmanTreeing(pHT, 256, 512));
	cout << endl;
	cout << "����������������Ľ��Ϊ�� " << endl;
	TestHufTree(511, pHT);
	string pHC[512] = { "" };
	HuffmanCoding(511, pHT, pHC);
	TestHuffCode(256, pHC);
	*/
	cout << "============Huffman============" << endl;
	cout << "������Ҫѹ�����ļ�����";
	char filename[256];
	cin >> filename;
	cout << endl;
	Compress(filename);//108389 677672
	char filename1[256];
	cout << endl;
	cout << "����Ҫ��ѹ���ļ����� ";
	cin >> filename1;
	if (Decompress(filename1) == OK) {
		cout << "��ѹ�ɹ�" << endl;
	}
	cout << "�������ѹ���ļ������֣� ";
	char filename2[256];
	cin >> filename2;
	FILE* in = fopen(filename2, "rb");
	int ch;
	int length = 0;
	while ((ch = fgetc(in)) != EOF)
	{
		length++;
	}
	cout << endl << "��ѹ���ļ���СΪ�� " << length;
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