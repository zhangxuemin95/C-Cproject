#include<stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int* missile = (int*)malloc(n * sizeof(int));
	int* record = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &missile[i]);
	}
	for (int i = 0; i < n; i++) {
		record[i] = 0;
	}
	for (int i = n - 1; i >= 0; i--) {
		record[i] = 1;
		int max = i;
		int increase = 0;
		for (int j = i + 1; j < n; j++) {
			if (missile[i] >= missile[j] && record[j] >= record[max]) {
				max = j;
				increase = record[j];
			}
		}
		record[i] += increase;
	}
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (record[i] > record[max])
			max = i;
	}
	printf("%d", record[max]);
	free(missile); missile = NULL;
	free(record); record = NULL;
}