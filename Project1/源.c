//ʵ��	��һ���Ѿ��ź�������飬Ҫ������һ�����󣬰�ԭ������Ĺ��ɽ�������������

// ���2316 ���Ž�
#include"stdio.h"

int main() {
	int arr[8] = { 1,2,3,4,5,7,8 };
	int m;
	scanf_s("%d",&m);
	for (int i = 0; i < 8; i++) {
		if (arr[i] >= m) {
			for (int j = 7; j > i; j--) {
				arr[j] = arr[j - 1];
			}
			arr[i] = m;
			break;
		}
	}
	for (int i = 0; i < 8; i++) {
		printf("%d",arr[i]);
	}
	return 0;
}