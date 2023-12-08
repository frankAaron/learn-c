#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <time.h>
#include <stdbool.h>

#define ID_LINE 11
#define MAX_PASSWORD_LINE 17
#define USER_NAME 10
#define Class 50
#define AGE 100
#define MAX_TRIES 5

typedef struct {
	char class[Class];
	char user_identify;
	char user_name[USER_NAME];
	char user_id[ID_LINE];
	char password[MAX_PASSWORD_LINE];
	char age[AGE];
}Information;

Information user[100] = { 0 };
int num_s = 1;
int num_t = 1;

//Check whether the input format is correct
static check_format(char user_age[], char user_id[], wchar_t user_name[]) {
	//check ID 
	if (strlen(user_id) != 10) {
		printf("----|your id's format you entered is incorrect,please enter 10 digital!\n");
		return 0;
	}
	//The function of isdigit is to check if the input is a letter
	for (int i = 0; i < 10; i++) {
		if (!isdigit(user_id[i])) {
			printf("----|your id's format you entered is letter!,we need digit!\n");
			return 0;
		}
	}

	//check age
	for (int i = 0; i < 2; i++) {
		if (!isdigit(user_age[i])) {
			printf("----|The age is not legal, please re-enter.\n");
			return 0;
		}
	}

	//check name
	//The wcslen function returns the length of the user_name string
	//!iswalpha ignore capital
	//!iswspace ignore space 
	fgetws(user_name, 50, stdin);
	for (int i = 0; i < wcslen(user_name); i++) {
		if (iswdigit(user_name[i])) {
			printf("----|The name is formatted incorrectly, please re-enter it (numbers are not allowed)\n");
			return 0;
		}
		if (!iswalpha(user_name[i]) && !iswspace(user_name[i])) {
			printf("----|The name is formatted incorrectly, please re-enter it(enter letters)\n");
			return 0;
		}
	}

	return 1;
}

//Generate a verification code
void captcha() {
	char code[7] = { 0 };
	char enter_code[7];
	srand(time(NULL));
	// Randomly generate 6 digits as a verification code
	for (int i = 0; i < 6; i++) {
		int r = rand() % 10;
		code[i] = r + '0';
	}
	code[6] = '\0';

	printf("----|the captcha is：");
	for (int i = 0; i < 6; i++) {
		printf("%c", code[i]);
	}
	printf("\n");
	printf("----|please enter captcha:");
	int times = 0;
	while (times < MAX_TRIES) {
		scanf("%s", enter_code);
		if (strcmp(enter_code, code) == 0) {
			printf("----|loading……\n======|welcome|==========\n");
			printf("====|Welcome to Zhu Yujie(Aaron)'s platform|====\n");
			printf("\n");
			return;
		}
		else {
			printf("----|the captcha was wrong!\n");
			srand(time(NULL));
			for (int i = 0; i < 6; i++) {
				int r = rand() % 10;
				code[i] = r + '0';
			}
			code[6] = '\0';
			printf("----|the captcha is：");
			for (int i = 0; i < 6; i++) {
				printf("%c", code[i]);
			}
			printf("\n");
			printf("----|please enter again:");
			times++;
		}
	}
	printf("----|Can you polish your eyes?\n");
	printf("----|You maybe is a robot\n");
}

//check repetitive information 
int check_repeat_s(FILE* fp, char class[], char name[], char id[], char password[], char age[]) {
	char line[Class + USER_NAME + ID_LINE + MAX_PASSWORD_LINE + AGE + 10];
	char class_line[Class + 1], name_line[USER_NAME + 1], id_line[ID_LINE + 1], password_line[MAX_PASSWORD_LINE + 1], age_line[AGE + 1];
	while (fgets(line, sizeof(line), fp) != NULL) {
		sscanf(line, "%s %s %s %s %s", class_line, name_line, id_line, password_line, age_line);
		if (strcmp(class_line, user->class) == 0 && strcmp(name_line, user->user_name) == 0 && strcmp(id_line, user->user_id) == 0 && strcmp(password_line, user->password) == 0 && strcmp(age_line, user->age) == 0) {
			return 1;
		}
	}
	return 0;
}

int check_repeat_t(FILE* fp, char class[], char name[], char id[], char password[], char age[]) {
	char line[Class + USER_NAME + ID_LINE + MAX_PASSWORD_LINE + AGE + 10];
	char class_line[Class + 1], name_line[USER_NAME + 1], id_line[ID_LINE + 1], password_line[MAX_PASSWORD_LINE + 1], age_line[AGE + 1];
	while (fgets(line, sizeof(line), fp) != NULL) {
		sscanf(line, "%s %s %s %s %s", class_line, name_line, id_line, password_line, age_line);
		if (strcmp(class_line, user->class) == 0 && strcmp(name_line, user->user_name) == 0 && strcmp(id_line, user->user_id) == 0 && strcmp(password_line, user->password) == 0 && strcmp(age_line, user->age) == 0) {
			return 1;
		}
	}
	return 0;
}

//teacher function
int choice_t() {
	int choice;
	printf("----|You can execute the following commands:");
	printf("|1:View student information\n");
	printf("|2:Change your password\n");
	printf("|3:exit\n");
	printf("----|please enter your choice:");
	scanf("%d", &choice);
	switch (choice) {
	case 1: {
		FILE* fp = fopen("s.txt", "r");
		if (fp == NULL) {
			printf("----|Unable to open database file!\n");
			return 0;
		}
		else {
			for (int i = 0; i < num_s; i++) {
				fprintf(fp, "%d %s %s %s %s %s\n", num_s, user->class, user->user_name, user->user_id, user->password, user->age);
			}
		}
		return 0;
	}
	case 2: {
		FILE* fp = fopen("t.txt", "a+");
		if (fp == NULL) {
			printf("----|Unable to open database file!\n");
			return 0;
		}
		else {
			printf("----|Please enter your name:");
			scanf("%s", user->user_name);
			char new_password[50];
			char line[256];
			int line_number = 1;
			bool found = 0;
			while (fgets(line, sizeof(line), fp) != NULL) {
				if (strstr(line, user->user_name)) {
					sscanf(line, "%s %s %s %s %s\n", user->class, user->user_name, user->user_id, new_password, &user->age);
					found = 1;
					break;
				}
				line_number++;
			}
			if (found) {
				printf("----|Your new password is:");
				scanf("%s", &user->password);
				fprintf(fp, "%d %s %s %s %s %s\n", num_s, user->class, user->user_name, user->user_id, user->password, user->age); // 写入新密码到文件
				printf("----|Password successfully updated!\n");
			}
			else {
				printf("----|Name not found in the file!\n");
			}
			fclose(fp);
		}
	}
	case 3:
		printf("================|Exiting|=====================\n");
		printf("\n");
		exit(0);
	default:
		printf("----|your choice is wrong\n");
		printf("================|Exiting|=====================\n");
		exit(0);
	}
}

//student function
int choice_s() {
	printf("----|You can execute the following commands:\n");
	int choice;
	printf("|1:change your password\n");
	printf("|2:inquire about information by class\n");
	printf("----|please enter your choice:");
	scanf("%d", &choice);
	switch (choice) {
	case 1: {
		FILE* fp = fopen("s.txt", "a+");
		if (fp == NULL) {
			printf("----|Unable to open database file!\n");
			return 0;
		}
		else {
			printf("----|Please enter your name:");
			scanf("%s", user->user_name);
			char new_password[50];
			char line[256];
			int line_number = 1;
			bool found = 0;
			while (fgets(line, sizeof(line), fp) != NULL) {
				if (strstr(line, user->user_name)) {
					sscanf(line, "%s %s %s %s %s\n", user->class, user->user_name, user->user_id, new_password, &user->age);
					found = 1;
					break;
				}
				line_number++;
			}
			if (found) {
				printf("----|Your new password is:");
				scanf("%s", &user->password);
				fprintf(fp, "%d %s %s %s %s %s\n", num_s, user->class, user->user_name, user->user_id, user->password, user->age);
				printf("----|Password successfully updated!\n");
			}
			else {
				printf("----|Name not found in the file!\n");
			}
			fclose(fp);
		}
		return 0;
	}
	case 2: {
		FILE* fp = fopen("s.txt", "r");
		if (fp == NULL) {
			printf("----|Unable to open database file!\n");
			return 0;
		}
		else {
			char enter_class[50];
			printf("");
			printf("Enter class: ");
			scanf("%s", enter_class);
			for (int i = 0; i < num_s; i++) {
				if (strcmp(user[i].class, enter_class) == 0) {
					fprintf(fp, "%d %s %s %s %s %s\n", num_s, user->class, user->user_name, user->user_id, user->password, user->age);
					break;
				}
			}
		}
		return 0;
	}
	default:
		exit(0);
	}
}

//Check that the id and the password is correct for login
int check_s() {
	char stored_id[17];
	char stored_password[17];
	char len[50];
	int found = 0;

	FILE* file = fopen("s.txt", "r");
	if (file == NULL) {
		printf("----|Unable to open database file!\n");
		return -1;
	}

	while (fgets(len, sizeof(len), file) != NULL) {
		sscanf(len, "%s %s", stored_id, stored_password);
		if (strcmp(stored_id, user->user_id) == 0 && strcmp(stored_password, user->password) == 0) {
			found = 1;
			break;
		}
	}
	fclose(file);

	if (found) {
		captcha();
		printf("--------------------|Logging successful|----------------------\n");
		printf("==============================================================\n");
		printf("====|Welcome to Zhu Yujie(Aaron)'s academic affairs system|====\n");
		printf("\n");
		choice_s();
		return 0;
	}
	else {
		printf("----|No matching user found!\n");
		return -1;
	}
}

int check_t() {
	char stored_id[17];
	char stored_password[17];
	char len[50];
	int found = 0;

	FILE* file = fopen("t.txt", "r");
	if (file == NULL) {
		printf("----|Unable to open database file!\n");
		return -1;
	}

	while (fgets(len, sizeof(len), file) != NULL) {
		sscanf(len, "%s %s", stored_id, stored_password);
		if (strcmp(stored_id, user->user_id) == 0 && strcmp(stored_password, user->password) == 0) {
			found = 1;
			break;
		}
	}
	fclose(file);

	if (found) {
		captcha();
		printf("--------------------|Logging successful|----------------------\n");
		choice_t();
		return 0;
	}
	else {
		printf("---|No matching user found!\n");
		return -1;
	}
}

//enroll student
void enroll_student() {
	printf("---------------------\n");
	printf("----|Please enter the class:");
	scanf("%s", &user->class);
	fflush(stdin);
	printf("----|Please enter your name:");
	scanf("%s", &user->user_name);
	fflush(stdin);
	printf("----|Please enter an 10-digit ID:");
	scanf("%s", &user->user_id);
	fflush(stdin);
	printf("----|Please set a password:");
	scanf("%s", &user->password);
	fflush(stdin);
	printf("----|Please enter your age:");
	scanf("%s", &user->age);
	if (check_format(user->age, user->user_id, user->user_name) == 0) {
		printf("----|Logging out\n");
	}
	else {
		FILE* fp = NULL;
		fp = fopen("s.txt", "a+");
		if (fp == NULL) {
			printf("----|Unable to open database file!\n");
			return;
		}
		else {
			if ((check_repeat_s(fp, user->class, user->user_name, user->user_id, user->password, user->age)) == 0) {
				//fseek将文件指针移动到文件的结尾,来确保第二个信息在第二行
				//SEEK_SET：从文件开始位置计算偏移量。这是默认值。
				//SEEK_CUR：从当前位置计算偏移量。
				//SEEK_END：从文件末尾计算偏移量。
				fseek(fp, 0, SEEK_END);
				fseek(fp, -1, SEEK_CUR);
				fprintf(fp, "%d %s %s %s %s %s\n", num_s, user->class, user->user_name, user->user_id, user->password, user->age);
				printf("============|You are registered in the %d digits\n", num_s);
				num_s++;
				fclose(fp);
				printf("-----Loading......\n ");
				printf("------Registration is successful------\n");
				printf("===========================================\n");
			}
			else
				printf("----------This information already exists----------\n");
			fclose(fp);
		}
	}

}

//enroll student
char enroll_teacher() {
	printf("---------------------\n");
	printf("----|Please enter the class:");
	scanf("%s", &user->class);
	fflush(stdin);
	printf("----|Please enter your name:");
	scanf("%s", &user->user_name);
	fflush(stdin);
	printf("----|Please enter an 10-digit ID:");
	scanf("%s", &user->user_id);
	fflush(stdin);
	printf("----|Please set a password:");
	scanf("%s", &user->password);
	fflush(stdin);
	printf("----|Please enter your age:");
	scanf("%s", &user->age);
	if (check_format(user->age, user->user_id, user->user_name) == 0) {
		printf("----|Logging out\n");
	}
	else {
		FILE* fp = NULL;
		fp = fopen("t.txt", "a+");
		if (fp == NULL) {
			printf("----|Unable to open database file!\n");
			return;
		}
		else {
			if ((check_repeat_t(fp, user->class, user->user_name, user->user_id, user->password, user->age)) == 0) {
				fseek(fp, 0, SEEK_END);
				fseek(fp, -1, SEEK_CUR);
				fprintf(fp, "%d %s %s %s %s %s\n", num_t, user->class, user->user_name, user->user_id, user->password, user->age);
				printf("============|You are registered in the %d digits", num_t);
				num_t++;
				fclose(fp);
				printf("-----Loading......\n ");
				printf("------Registration is successful------\n");
				printf("===========================================\n");
			}
			else {
				printf("------This information already exists------\n");
			}
			fclose(fp);
		}
	}

}

int main() {
	char identify[256] = { 0 };
	char choice[256] = { 0 };
	printf("=======|This is the academic affairs simulation system|======\n");
	printf("---------The author: Zhu Yujie(Aaron)-----------\n");
	//login or enroll
	while (1) {
		printf("----|please choose login or enroll or exit:");
		if (scanf("%s", choice) == 1) {
			if (strcmp(choice, "login") == 0) {
				printf("please enter your identify (student or teacher):");
				while (1) {
					if (scanf("%s", identify) == 1) {
						if (strcmp(identify, "student") == 0) {
							printf("----|please enter your id:");
							scanf("%s", &user->user_id);
							printf("----|please enter password:");
							scanf("%s", &user->password);
							check_s();
							break;
						}
						else if (strcmp(identify, "teacher") == 0) {
							printf("----|please enter your id:");
							scanf("%s", &user->user_id);
							printf("----|please enter password:");
							scanf("%s", &user->password);
							check_t();
							break;
						}
					}
					else {
						printf("error!");
					}
				}
			}

			else if (strcmp(choice, "enroll") == 0) {
				printf("please enter your identify (student or teacher)：");
				while (1) {
					if (scanf("%s", identify) == 1) {
						if (strcmp(identify, "student") == 0) {
							enroll_student();
							break;
						}

						else if (strcmp(identify, "teacher") == 0) {
							enroll_teacher();
							break;
						}

						else
							printf("====|identify is error!!!\n");
					}

					else
						printf("====|Please enter the correct identity!\n");
				}
			}

			else if (strcmp(choice, "exit") == 0) {
				printf("=====|Exiting\n");
				printf("=====|Looking forward to seeing you next time\n");
				break;
			}
			else
				printf("choice is error!\n");
		}
	}
	return 0;
}