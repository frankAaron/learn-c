// ���2316 ���Ž�
#include"stdio.h"
int main() {
	for (int i = 2; i < 1000; i++) {
		int sum = 0;
		for (int j = 1; j < i; j++) {
			if (i % j == 0) {
				sum += j;
			}
		}
		if (sum == i) {
			printf("%d its factors are ", i);
			for (int j = 1; j < i; j++) {
				if (i % j == 0) {
					printf("%d,", j);
				}
			}
			printf("\n");
		}
	}
	return 0;
}