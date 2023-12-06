//实验  	设计一函数，判断一个字符串是否是回文。“回文”是一种顺序读和反序读都一样的字符串，
// 例如：“121” “abcba” “ABCCBA”。在主函数中输入字符串并输出判断结果。
//软件2316 朱昱杰
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