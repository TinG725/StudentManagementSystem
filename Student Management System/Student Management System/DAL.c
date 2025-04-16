#define _CRT_SECURE_NO_WARNINGS

#include "SMS.h"
#include"UI.h"
#include"File.h"



//��һ�������ݷ��ʲ� ���ݵ���ɾ���
// 
//��ʼ��ѧ������
void studentInit(Student** pphead)
{
	*pphead = (Student*)malloc(sizeof(Student));
	(*pphead)->number = -1;
	strcpy((*pphead)->name, "nobody");
	(*pphead)->score = -1;
	(*pphead)->next = (*pphead)->prev = *pphead;
}

//�õ�һ���½��
Student* getNode(char* account,char* password)
{
	int number;
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int class;
	double score;

	printf("ѧ�ţ�");
	scanf("%d", &number);
	getchar();
	printf("������");
	scanf("%s", name);
	printf("���䣺");
	scanf("%d", &age);
	getchar();
	printf("�Ա�");
	scanf("%s", sex);
	printf("�༶��");
	scanf("%d", &class);
	printf("������");
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

	if (account && password)//Ҫ�ֶ������˺�����
	{
		strcpy(newNode->account, account);
		strcpy(newNode->password, password);

	}
	else//�Ѿ������˺����� ֱ�Ӹ�ֵ����
	{
		scanf(" %s %s", account, password);
		strcpy(newNode->account, account);
		strcpy(newNode->password, password);
	}

	return newNode;
}

//��ӡָ����������
void studentPrint(Student* pos)
{
	assert(!studentEmpty(pos));
	printf("ѧ�ţ�%d ������%s �ɼ���%.2lf\n", pos->number, pos->name, pos->score);
}

//�п�--����ǿգ�����1
int studentEmpty(Student* phead)
{
	return phead->number == -1;
}

//���ѧ����Ϣ -- ˫������
void studentAdd(Student** pphead,char* account, char* password)
{
	assert(!studentEmpty(pphead));
	
	Student* newNode = getNode(account, password);

	//��������л�û��ѧ����Ϣ ���⴦�� ֱ�ӵ����½��
	if (studentEmpty(*pphead))
	{
		*pphead = newNode;
		(*pphead)->next = (*pphead)->prev = newNode;
	}

	//�������Ѿ�����ѧ����Ϣ
	else
	{
		newNode->prev = (*pphead)->prev;
		newNode->next = *pphead;
		(*pphead)->prev->next = newNode;
		(*pphead)->prev = newNode;
	}
	writeStudentsToFile(newNode, "StudentMessage");
}

//��ѧ�Ų�ѯѧ����Ϣ--���ؽ��
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

	//pcurΪ��--��ʾδ���ҵ�
	return NULL;
}

//���ս���޸�ѧ����Ϣ---��ʦ�޸ķ���
void studentChange(Student** pphead, Student* pos)
{
	assert(!studentEmpty(pos));
	double score;
	scanf("%lf", &score);
	pos->score = score;
}

//�޸�ѧ�����˺�����
void studentAccChange(Student** pphead, Student* pos)
{
	char* account = "123";
	char* password = "123"; 
	scanf("%s %s", account, password);

	strcpy(account, pos->account);
	strcpy(password, pos->password);
}

//����λ��ǰ����½��
void insertFront(Student** pphead, Student* pos)
{
	//�п�
	assert(!studentEmpty(pphead) && !studentEmpty(pos));

	Student* newNode = getNode(NULL, NULL);

	newNode->next = pos;
	newNode->prev = pos->prev;
	pos->prev->next = newNode;
	pos->prev = newNode;

}

//����λ�ú�����½��
void insertBack(Student** pphead, Student* pos)
{
	//�п�
	assert(!studentEmpty(pphead) && !studentEmpty(pos));

	Student* newNode = getNode(NULL, NULL);

	newNode->next = pos->next;
	newNode->prev = pos;
	pos->next->prev = newNode;
	pos->next = newNode;


}

//ɾ��ָ��λ�õ�����
void studentPop(Student** pphead, Student* pos)
{
	assert(!studentEmpty(pphead) && !studentEmpty(pos));

	//���Ҫɾ��ͷ����е�����--���⴦��
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

//��ʦ�鿴���ڳɼ�---����ѡ��ҳ
void teacherLook(Student* phead)
{
	Student* pcur = phead; 

	printf("1.��ǰ        2.���\n");
	printf("3.������һ��  0.�˳�\n");
	int choice = 0;//ѡ��1Ϊ���� ѡ��2Ϊ��� ѡ��0Ϊ�˳� ѡ��3Ϊ������һ��

	while (1)
	{
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("%d %s %d %s %lf\n", pcur->prev->number, pcur->prev->name, pcur->prev->age, pcur->prev->sex, pcur->prev->score);//Ŀǰ����һ��
			pcur = pcur->prev;
			break;
		case 2:
			printf("%d %s %d %s %lf\n", pcur->next->number, pcur->next->name, pcur->next->age, pcur->next->sex, pcur->next->score);//Ŀǰ����һ��
			pcur = pcur->next;
			break;
		case 3:
			teaMenu();
			return;
		case 0:
			printf("���˳�ѧ����Ϣ����ϵͳ����л����ʹ�ã�\n");
			return;
		default:
			printf("�����������������\n");
			break;
		}
	}
}

//��ʦ�ĳ�ʼ��--¼�����н�ʦ����Ϣ ����
void teacherInit(Teacher** pphead)
{
	(*pphead) = (Teacher*)malloc(sizeof(Teacher));

	(*pphead)->class = 0;
	(*pphead)->next = NULL;
}

//��ʦ��Ϣ��¼��->ֱ��¼�����е�
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
			printf("---------��ӳɹ�---------\n");
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

		if ((*pphead)->class == 0)//��ʦ�л�û������ ֱ�ӵ����½ڵ�
		{
			(*pphead) = newNode;
		}
		else
		{
			//ʹ��ͷ�� ʱ�临�Ӷ�O��1��
			newNode->next = (*pphead);
			(*pphead) = newNode;
		}
	}
	writeTeachersToFile((*pphead), "TeacherMessage");
}

//ע��
void Register()
{
	char account[MAX_ACCOUNT];
	printf("�������˺ţ�");
	scanf("%s", account);

	if (!strcmp("0", account))//����
	{
		return;
	}

	char password1[MAX_PASSWORD];
	char password2[MAX_PASSWORD];

	while (1)
	{
		printf("���������룺");
		scanf("%s", password1);
		printf("���ٴ�ȷ�����룺");
		scanf("%s", password2);

		if (strcmp(password1, password2))
		{
			printf("��������벻һ�£�����������\n");
		}
		else
		{
			printf("������������Ϣ\n");
			studentAdd(&S, account, password1);

			printf("------------ע��ɹ����뷵�ص�¼!---------------\n");
			Sleep(1000);
			system("cls");
			break;
		}
	}
}

//�޸�����
void pasChange(Student** pphead, Student* pos)
{
	//�ȸ���ѧ�Ų��ҵ���Ϣ��Ȼ����������޸�

	char password[MAX_PASSWORD];
	scanf("%s", password);

	strcpy(pos->password, password);
}

//�����˺�����--����Ա����
//�ȸ���ѧ�Ų��ҵ���Ϣ��Ȼ������˺�����
void pasSearch(Student* pos)
{
	assert(!studentEmpty(pos));

	printf("%s %s\n", pos->account, pos->password);
}



//�����ж�����ֵ�Ƿ�������
//ֱ���ڴ˺�������
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
		if (ch >= '0' && ch <= '9')//�����������
		{
			choice = ch - '0';
			return choice;
		}
		if(ch <= '0' || ch >= '9' || ch != '\n')
		{
			printf("-------�������������һ��������-------\n");
		}
	}

}

//�����˺Ų���ѧ��
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

//�����˺Ų��ҽ�ʦ
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




//�ļ�
void File(const char* sourceFilename, const char* targetFilename)
{
	FILE* sourceFile = fopen(sourceFilename, "r");
	if (sourceFile == NULL) {
		perror("-------------------�޷���Դ�ļ�-------------------");
		return;
	}
	FILE* targetFile = fopen(targetFilename, "a");//׷�ӷ�ʽд��
	if (targetFilename == NULL)
	{
		perror("-------------------�޷���Ŀ���ļ�-------------------");
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