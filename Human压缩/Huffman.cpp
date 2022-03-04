#include"Huffman.h"
HuffmanTree HuffmanTreeing(HTNode pHT[], int nSize1,int nSize2) {
	int min = 0, secmin = 0;
	for (int i = nSize1 + 1; i < nSize2; i++) {
		min = Select(pHT, i);
		pHT[min].parent = i;
		secmin = Select(pHT, i);
		pHT[secmin].parent = i;
		if (pHT[min].weight > pHT[secmin].weight) {
			pHT[i].lchild = secmin;
			pHT[i].rchild = min;
			pHT[i].weight = pHT[min].weight + pHT[secmin].weight;
		}
		else {
			pHT[i].rchild = secmin;
			pHT[i].lchild = min;
			pHT[i].weight = pHT[min].weight + pHT[secmin].weight;
		}
	}
	return pHT;
}

int Select(HuffmanTree pHT, int nSize) {
	int mainValue = 0x7FFFFFFf;
	int min = 0;
	for (int i = 1; i < nSize; i++) {
		if (pHT[i].parent == 0 && pHT[i].weight < mainValue) {
			mainValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}

void HuffmanCoding(int root, HuffmanTree pHT, HuffmanCode pHC) {
	if (pHT[root].parent != 0) {
		if (pHT[pHT[root].parent].lchild == root) {
			pHC[root] = pHC[pHT[root].parent] + "0";
		}
		if (pHT[pHT[root].parent].rchild == root) {
			pHC[root] = pHC[pHT[root].parent] + "1";
		}
	}
	if (pHT[root].lchild != 0) {
		HuffmanCoding(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild != 0) {
		HuffmanCoding(pHT[root].rchild, pHT, pHC);
	}
}

