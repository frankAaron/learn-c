//ʵ��  	���һ�������ж�һ���ַ����Ƿ��ǻ��ġ������ġ���һ��˳����ͷ������һ�����ַ�����
// ���磺��121�� ��abcba�� ��ABCCBA�������������������ַ���������жϽ����
//���2316 ���Ž�
#include <stdio.h>
#include <string.h>

int palindrome(char str[100]) {
    int l = strlen(str);
    for (int i = 0; i < l / 2; i++) {
        if (str[i] != str[l - i - 2]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[100];
    fgets(str, sizeof(str), stdin); 
    if (palindrome(str) == 1) {
        printf("is");
    }
    else {
        printf("is not");
    }
    return 0;
}