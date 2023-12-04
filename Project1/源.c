//实验	有一个已经排好序的数组，要求输入一个数后，按原来排序的规律将它插入数组中

// 软件2316 朱昱杰
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