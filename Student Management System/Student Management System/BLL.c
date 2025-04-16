#define _CRT_SECURE_NO_WARNINGS

#include"SMS.h"
#include"UI.h"
#include"File.h"


extern const char admAccount[MAX_ACCOUNT] = "admin";
extern const char admPassword[MAX_PASSWORD] = "123456";

int main()
{
	const char* targetFilename = "SMS.txt";
	const char* sourceFilename[10] = { "BLL.c","SMS.h","UI.h","test.c","SMS.c","DAL.c"};
	FILE* target = fopen(targetFilename, "w");
	if (target == NULL) {
		perror("-------------------无法创建目标文件-------------------");
		return 1;
	}
	fclose(target);
	for (int i = 0; i < 6; i++)
	{
		File(sourceFilename[i], targetFilename);
	}

	FILE* studentFile = fopen("StudentMessage", "a");
	fclose(studentFile);
	FILE* teacherFile = fopen("TeacherMessage", "a");
	fclose(teacherFile);


	studentInit(&S);
	teacherInit(&T);

	int choice;
	int num;
	char account[MAX_ACCOUNT];
	char password[MAX_PASSWORD];

	T = readTeachersFromFile("TeacherMessage");
	S = readStudentsFromFile("StudentMessage");

	Student* p = S;


Menu:
	//进入主菜单
	mainMenu();
	choice = ifInt();
	system("cls");//清屏

	switch (choice)
	{
	case 0://退出
		printf("----------------感谢您的使用-----------------\n");
		return 0;
	case 1://学生登录
		logMenu();
		printf("账号：");
		scanf("%s", account);
		getchar();
		printf("\n");
		if (!strcmp("return", account))//返回
		{
			system("cls");
			goto Menu;
			break;
		}
		printf("密码：");
		scanf("%s", password);
		//Sleep(10000);
		//system("cls");//清屏
		Student* pos = accStudentSearch(S, account);//根据账号查找信息
		if (pos)//有该账号
		{
			if (strcmp(password, pos->password))//密码输入错误
			{
				printf("----------账号或密码输入错误-------------\n");
				Sleep(1000);
				system("cls");
				goto Menu;
			}
			else
			{
			stuChoose:
				system("cls");
				stuMenu();//进入学生页面
				choice = ifInt();
				system("cls");

				switch (choice)
				{
				case 1://成绩查询
					printf("请输入您的学号:");
					scanf("%d", &num);
					pos = numberSearch(S, num);
					if (pos == NULL)
					{
						printf("----------学号输入有误！-------------\n");
						Sleep(1000);
						system("cls");
					}
					else
					{
						studentPrint(pos);
						Sleep(2000);
						
					}
					goto stuChoose;
					break;
				case 2://返回上一级
					goto Menu;
					break;
				default:
					printf("-------------输入错误，请重新输入------------\n");
					Sleep(1000);
					system("cls");
					goto stuChoose;
					break;
				}
			}
		}
		else//没有该账号
		{
			printf("----------账号或密码输入错误-----------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		break;

	case 2://教师登录
		//根据输入的账号遍历查找
		logMenu();
		printf("账号：");
		scanf("%s", account);
		printf("\n");
		if (!strcmp("return", account))//返回
		{
			system("cls");
			goto Menu;
			break;
		}
		printf("密码：");
		scanf("%s", password);
		getchar();


		Teacher* pos_ = accTeacherSearch(T, account);//根据账号查找信息
		if (pos_)//有该账号
		{
			if (strcmp(password, pos_->password))//密码输入错误
			{
				printf("-----------账号或密码输入错误-----------\n");
				Sleep(1000);
				system("cls");
			}
			else//进入教师页面
			{
			tea:
				system("cls");
				teaMenu();
				choice = ifInt();
				system("cls");

				switch (choice)
				{
				case 1://增加信息
					studentAdd(&S, NULL, NULL);
					goto tea;
					break;
				case 2://删除信息
					printf("请输入您要删除的学生学号：");
					scanf("%d", &num);
					printf("\n");
					pos = numberSearch(S, num);
					if (pos)
					{
						studentPop(&S, pos);
					}
					else
					{
						printf("学号有误\n");
					}
					goto tea;
					break;
				case 3://修改信息
					printf("请输入您要修改的学生学号：");
					scanf("%d", &num);
					printf("\n");
					pos = numberSearch(S, num);
					if (pos)
					{
						studentChange(&S, pos);
					}
					else
					{
						printf("学号有误!\n");
					}
					goto tea;
					break;
				case 4://查找信息
					printf("请输入您要查找的学生学号：");
					scanf("%d", &num);
					printf("\n");
					pos = numberSearch(S, num);
					if (pos)
					{
						studentPrint(pos);
					}
					else
					{
						printf("学号有误！\n");
						goto tea;
					}
					break;
				case 5://查看班内成绩
					teacherLook(S);
					goto tea;
					break;
				case 6://返回上一级
					goto Menu;
					break;
				default://输入错误
					printf("输入错误，请重新输入\n");
					goto tea;
					break;
				}
			}
		}
		else//没有该账号
		{
			printf("-----------账号或密码输入错误-----------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		break;

	case 3://管理员登录

		logMenu();
		printf("账号：");
		scanf("%s", account);
		getchar();


		if (!strcmp("return", account))//返回
		{
			system("cls");
			goto Menu;
		}

		printf("密码：");
		scanf("%s", password);
	admMenu:
		if (!strcmp(admAccount, account) && !strcmp(admPassword, password))//登录
		{
			system("cls");
			admMenu();
			choice = ifInt();
			
			switch (choice)
			{
			case 1://删除账号密码
				printf("请输入您要删除的学生学号：");
				num = ifInt();
				pos = numberSearch(S, num);
				if (pos == NULL)
				{
					printf("-----------学号输入有误！------------\n");
					Sleep(1000);
					system("cls");
				}
				else
				{
					studentPop(&S, pos);
				}
				goto admMenu;
				break;
			case 2://修改账号密码
				printf("请输入您要修改的学生学号：");
				num = ifInt();
				pos = numberSearch(S, num);
				if (pos == NULL)
				{
					printf("----------学号输入有误！-----------\n");
					Sleep(1000);
					system("cls");
				}
				else
				{
					studentAccChange(&S, pos);
				}
				goto admMenu;
				break;
			case 3://查找账号密码
				printf("请输入您要查找的学生学号：");
				num = ifInt();
				pos = numberSearch(S, num);
				if (pos == NULL)
				{
					printf("----------学号输入有误！-----------\n");
					Sleep(1000);
					system("cls");
				}
				else
				{
					pasSearch(pos);
				}
				goto admMenu;
				break;
			case 4://从文件读取所有账号密码
				p = S;
				while (p)
				{
					pasSearch(p);
					p = p->next;
					if (p == S)
					{
						break;
					}
				}
				goto Menu;
				break;
			case 5://从文件导出所有账号密码
				p = S;
				while (p)
				{
					pasSearch(p);
					p = p->next;
					if (p == S)
					{
						break;
					}
				}

				goto Menu;
				break;
			case 6://录入教师账号
				teacherInit(&T);
				teacherAdd(&T);
				goto admMenu;
				break;
			case 0://返回上一级
				system("cls");
				goto Menu;
				break;

			}
		}
		else//没有该账号
		{
			printf("------------账号或密码输入错误------------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}

		break;
	case 4://密码修改
		printf("请输入您的账号:\n");
		scanf("%s", account);
		pos = accStudentSearch(S, account);
		if (pos == NULL)
		{
			printf("------------该账号不存在--------------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		else
		{
			printf("密码：");
			pasChange(&S, pos);
			printf("修改成功！\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		break;
	case 5://账号注册
		registerMenu();
		Register();
		goto Menu;
		break;
	default:
		printf("----------输入错误，请重新输入-----------\n");
		Sleep(1000);
		system("cls");
		goto Menu;
		break;
	}
	return 0;
}