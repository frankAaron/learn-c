//���2316 ���Ž�
#include<stdio.h>
#include <math.h>
int fection(int x,int n,int y) {
	if (n > 0) {
		y *= x;
		return fection(x, n - 1, y);
	}
	else {
		return y;
	}
}
int main() {
	int x, n, y = 1;
	printf("������");
	scanf_s("%d",&x);
	printf("ָ����");
	scanf_s("%d",&n);
	printf("answer is :%d",fection(x, n, y));
}