//ʵ��  	������һ��Ӣ�ľ��ӣ���ÿ�����ʵĵ�һ����ĸ��Ϊ��д
//���2316 ���Ž�
#include <stdio.h>

void main()
{
	char str[100], * p;
	printf("���������ݣ�\n");
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