//实验  	输入有一个英文句子，将每个单词的第一个字母改为大写
//软件2316 朱昱杰
#include <stdio.h>

void main()
{
	char str[100], * p;
	printf("请输入内容：\n");
	gets(str);
	p = str;
	for (p = str; *p; p++)
	{
		if (p == str && *p >= 'a' && *p <= 'z') 
			*p = *p - 32;
		if (*p == ' ')
		{
			if (*(p + 1) >= 'a' && *(p + 1) <= 'z') 
				*(p + 1) = *(p + 1) - 32;
		}
	}
	puts(str);
}