#define _CRT_SECURE_NO_WARNINGS

#include "SMS.h"
#include"UI.h"
#include"File.h"



//这一层是数据访问层 数据的增删查改
// 
//初始化学生链表
void studentInit(Student** pphead)
{
	*pphead = (Student*)malloc(sizeof(Student));
	(*pphead)->number = -1;
	strcpy((*pphead)->name, "nobody");
	(*pphead)->score = -1;
	(*pphead)->next = (*pphead)->prev = *pphead;
}

//得到一个新结点
Student* getNode(char* account,char* password)
{
	int number;
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int class;
	double score;

	printf("学号：");
	scanf("%d", &number);
	getchar();
	printf("姓名：");
	scanf("%s", name);
	printf("年龄：");
	scanf("%d", &age);
	getchar();
	printf("性别：");
	scanf("%s", sex);
	printf("班级：");
	scanf("%d", &class);
	printf("分数：");
	scanf("%lf", &score);

	Student* newNode = (Student*)malloc(sizeof(Student));
	if (newNode == NULL)
	{
		perror("malloc fail!\n");
		exit(1);
	}
	newNode->number = number;
	strcpy(newNode->name, name);
	newNode->age = age;
	strcpy(newNode->sex, sex);
	newNode->class = class;
	newNode->score = score;

	if (account && password)//要手动输入账号密码
	{
		strcpy(newNode->account, account);
		strcpy(newNode->password, password);

	}
	else//已经有了账号密码 直接赋值即可
	{
		scanf(" %s %s", account, password);
		strcpy(newNode->account, account);
		strcpy(newNode->password, password);
	}

	return newNode;
}

//打印指定结点的数据
void studentPrint(Student* pos)
{
	assert(!studentEmpty(pos));
	printf("学号：%d 姓名：%s 成绩：%.2lf\n", pos->number, pos->name, pos->score);
}

//判空--如果是空，返回1
int studentEmpty(Student* phead)
{
	return phead->number == -1;
}

//添加学生信息 -- 双向链表
void studentAdd(Student** pphead,char* account, char* password)
{
	assert(!studentEmpty(pphead));
	
	Student* newNode = getNode(account, password);

	//如果链表中还没有学生信息 特殊处理 直接等于新结点
	if (studentEmpty(*pphead))
	{
		*pphead = newNode;
		(*pphead)->next = (*pphead)->prev = newNode;
	}

	//链表中已经有了学生信息
	else
	{
		newNode->prev = (*pphead)->prev;
		newNode->next = *pphead;
		(*pphead)->prev->next = newNode;
		(*pphead)->prev = newNode;
	}
	writeStudentsToFile(newNode, "StudentMessage");
}

//按学号查询学生信息--返回结点
Student* numberSearch(Student* phead, int number)
{
	Student* pcur = phead;
	while (pcur)
	{
		if (number == pcur->number)
		{
			return pcur;
		}
		pcur = pcur->next;
		if (pcur == phead)
		{
			break;
		}
	}

	//pcur为空--表示未查找到
	return NULL;
}

//按照结点修改学生信息---老师修改分数
void studentChange(Student** pphead, Student* pos)
{
	assert(!studentEmpty(pos));
	double score;
	scanf("%lf", &score);
	pos->score = score;
}

//修改学生的账号密码
void studentAccChange(Student** pphead, Student* pos)
{
	char* account = "123";
	char* password = "123"; 
	scanf("%s %s", account, password);

	strcpy(account, pos->account);
	strcpy(password, pos->password);
}

//任意位置前添加新结点
void insertFront(Student** pphead, Student* pos)
{
	//判空
	assert(!studentEmpty(pphead) && !studentEmpty(pos));

	Student* newNode = getNode(NULL, NULL);

	newNode->next = pos;
	newNode->prev = pos->prev;
	pos->prev->next = newNode;
	pos->prev = newNode;

}

//任意位置后添加新结点
void insertBack(Student** pphead, Student* pos)
{
	//判空
	assert(!studentEmpty(pphead) && !studentEmpty(pos));

	Student* newNode = getNode(NULL, NULL);

	newNode->next = pos->next;
	newNode->prev = pos;
	pos->next->prev = newNode;
	pos->next = newNode;


}

//删除指定位置的数据
void studentPop(Student** pphead, Student* pos)
{
	assert(!studentEmpty(pphead) && !studentEmpty(pos));

	//如果要删除头结点中的数据--特殊处理
	if (*pphead == pos)
	{
		(*pphead)->next->prev = (*pphead)->prev;
		(*pphead)->prev->next = (*pphead)->next;
		Student* node = *pphead;
		*pphead = (*pphead)->next;
		free(node);
		node = NULL;
	}
	else
	{
		pos->next->prev = pos->prev;
		pos->prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

//教师查看班内成绩---可以选择翻页
void teacherLook(Student* phead)
{
	Student* pcur = phead; 

	printf("1.向前        2.向后\n");
	printf("3.返回上一级  0.退出\n");
	int choice = 0;//选择1为向左 选择2为向后 选择0为退出 选择3为返回上一级

	while (1)
	{
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("%d %s %d %s %lf\n", pcur->prev->number, pcur->prev->name, pcur->prev->age, pcur->prev->sex, pcur->prev->score);//目前的上一个
			pcur = pcur->prev;
			break;
		case 2:
			printf("%d %s %d %s %lf\n", pcur->next->number, pcur->next->name, pcur->next->age, pcur->next->sex, pcur->next->score);//目前的下一个
			pcur = pcur->next;
			break;
		case 3:
			teaMenu();
			return;
		case 0:
			printf("已退出学生信息管理系统，感谢您的使用！\n");
			return;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	}
}

//教师的初始化--录入所有教师的信息 输入
void teacherInit(Teacher** pphead)
{
	(*pphead) = (Teacher*)malloc(sizeof(Teacher));

	(*pphead)->class = 0;
	(*pphead)->next = NULL;
}

//教师信息的录入->直接录入所有的
void teacherAdd(Teacher** pphead)
{
	char name[MAX_NAME];
	char account[MAX_ACCOUNT];
	char password[MAX_PASSWORD];

	int class = 0;
	while (1)
	{
		scanf("%d", &class);
		if (class == 0)
		{
			printf("---------添加成功---------\n");
			Sleep(1000);
			system("cls");
			break;
		}
		Teacher* newNode = (Teacher*)malloc(sizeof(Teacher));
		if (newNode == NULL)
		{
			perror("malloc fail!\n");
			exit(1);
		}

		scanf("%s %s %s", name, account, password);
		newNode->class = class;
		strcpy(newNode->name, name);
		strcpy(newNode->account, account);
		strcpy(newNode->password, password);

		if ((*pphead)->class == 0)//教师中还没有数据 直接等于新节点
		{
			(*pphead) = newNode;
		}
		else
		{
			//使用头插 时间复杂度O（1）
			newNode->next = (*pphead);
			(*pphead) = newNode;
		}
	}
	writeTeachersToFile((*pphead), "TeacherMessage");
}

//注册
void Register()
{
	char account[MAX_ACCOUNT];
	printf("请输入账号：");
	scanf("%s", account);

	if (!strcmp("0", account))//返回
	{
		return;
	}

	char password1[MAX_PASSWORD];
	char password2[MAX_PASSWORD];

	while (1)
	{
		printf("请输入密码：");
		scanf("%s", password1);
		printf("请再次确定密码：");
		scanf("%s", password2);

		if (strcmp(password1, password2))
		{
			printf("输入的密码不一致，请重新输入\n");
		}
		else
		{
			printf("请完善您的信息\n");
			studentAdd(&S, account, password1);

			printf("------------注册成功，请返回登录!---------------\n");
			Sleep(1000);
			system("cls");
			break;
		}
	}
}

//修改密码
void pasChange(Student** pphead, Student* pos)
{
	//先根据学号查找到信息，然后进行密码修改

	char password[MAX_PASSWORD];
	scanf("%s", password);

	strcpy(pos->password, password);
}

//查找账号密码--管理员操作
//先根据学号查找到信息，然后输出账号密码
void pasSearch(Student* pos)
{
	assert(!studentEmpty(pos));

	printf("%s %s\n", pos->account, pos->password);
}



//用来判断输入值是否是整数
//直接在此函数输入
int ifInt()
{
    int choice;

	char ch;


	while (1)
	{
		ch = getchar();
		if (ch == '\n')
		{
			continue;
		}
		if (ch >= '0' && ch <= '9')//输入的是整数
		{
			choice = ch - '0';
			return choice;
		}
		if(ch <= '0' || ch >= '9' || ch != '\n')
		{
			printf("-------输入错误，请输入一个整数！-------\n");
		}
	}

}

//根据账号查找学生
Student* accStudentSearch(Student* phead, char* account)
{
	Student* pcur = phead;
	
	while (pcur)
	{
		if (!strcmp(account, pcur->account))
		{
			return pcur;
		}
		pcur = pcur->next;
		if (pcur == phead)
		{
			break;
		}
	}

	return NULL;
}

//根据账号查找教师
Teacher* accTeacherSearch(Teacher* phead, char* account)
{
	Teacher* pcur = phead;

	while (pcur)
	{
		if (!strcmp(account, pcur->account))
		{
			return pcur;
		}
		pcur = pcur->next;
		if (pcur == phead)
		{
			break;
		}
	}
	return pcur;
}




//文件
void File(const char* sourceFilename, const char* targetFilename)
{
	FILE* sourceFile = fopen(sourceFilename, "r");
	if (sourceFile == NULL) {
		perror("-------------------无法打开源文件-------------------");
		return;
	}
	FILE* targetFile = fopen(targetFilename, "a");//追加方式写入
	if (targetFilename == NULL)
	{
		perror("-------------------无法打开目标文件-------------------");
		fclose(sourceFilename);
		return;
	}
	int ch;
	while ((ch = fgetc(sourceFile)) != EOF)
	{
		fputc(ch, targetFile);
	}
	fclose(sourceFile);
	fclose(targetFile);
}