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
		perror("-------------------�޷�����Ŀ���ļ�-------------------");
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
	//�������˵�
	mainMenu();
	choice = ifInt();
	system("cls");//����

	switch (choice)
	{
	case 0://�˳�
		printf("----------------��л����ʹ��-----------------\n");
		return 0;
	case 1://ѧ����¼
		logMenu();
		printf("�˺ţ�");
		scanf("%s", account);
		getchar();
		printf("\n");
		if (!strcmp("return", account))//����
		{
			system("cls");
			goto Menu;
			break;
		}
		printf("���룺");
		scanf("%s", password);
		//Sleep(10000);
		//system("cls");//����
		Student* pos = accStudentSearch(S, account);//�����˺Ų�����Ϣ
		if (pos)//�и��˺�
		{
			if (strcmp(password, pos->password))//�����������
			{
				printf("----------�˺Ż������������-------------\n");
				Sleep(1000);
				system("cls");
				goto Menu;
			}
			else
			{
			stuChoose:
				system("cls");
				stuMenu();//����ѧ��ҳ��
				choice = ifInt();
				system("cls");

				switch (choice)
				{
				case 1://�ɼ���ѯ
					printf("����������ѧ��:");
					scanf("%d", &num);
					pos = numberSearch(S, num);
					if (pos == NULL)
					{
						printf("----------ѧ����������-------------\n");
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
				case 2://������һ��
					goto Menu;
					break;
				default:
					printf("-------------�����������������------------\n");
					Sleep(1000);
					system("cls");
					goto stuChoose;
					break;
				}
			}
		}
		else//û�и��˺�
		{
			printf("----------�˺Ż������������-----------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		break;

	case 2://��ʦ��¼
		//����������˺ű�������
		logMenu();
		printf("�˺ţ�");
		scanf("%s", account);
		printf("\n");
		if (!strcmp("return", account))//����
		{
			system("cls");
			goto Menu;
			break;
		}
		printf("���룺");
		scanf("%s", password);
		getchar();


		Teacher* pos_ = accTeacherSearch(T, account);//�����˺Ų�����Ϣ
		if (pos_)//�и��˺�
		{
			if (strcmp(password, pos_->password))//�����������
			{
				printf("-----------�˺Ż������������-----------\n");
				Sleep(1000);
				system("cls");
			}
			else//�����ʦҳ��
			{
			tea:
				system("cls");
				teaMenu();
				choice = ifInt();
				system("cls");

				switch (choice)
				{
				case 1://������Ϣ
					studentAdd(&S, NULL, NULL);
					goto tea;
					break;
				case 2://ɾ����Ϣ
					printf("��������Ҫɾ����ѧ��ѧ�ţ�");
					scanf("%d", &num);
					printf("\n");
					pos = numberSearch(S, num);
					if (pos)
					{
						studentPop(&S, pos);
					}
					else
					{
						printf("ѧ������\n");
					}
					goto tea;
					break;
				case 3://�޸���Ϣ
					printf("��������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
					scanf("%d", &num);
					printf("\n");
					pos = numberSearch(S, num);
					if (pos)
					{
						studentChange(&S, pos);
					}
					else
					{
						printf("ѧ������!\n");
					}
					goto tea;
					break;
				case 4://������Ϣ
					printf("��������Ҫ���ҵ�ѧ��ѧ�ţ�");
					scanf("%d", &num);
					printf("\n");
					pos = numberSearch(S, num);
					if (pos)
					{
						studentPrint(pos);
					}
					else
					{
						printf("ѧ������\n");
						goto tea;
					}
					break;
				case 5://�鿴���ڳɼ�
					teacherLook(S);
					goto tea;
					break;
				case 6://������һ��
					goto Menu;
					break;
				default://�������
					printf("�����������������\n");
					goto tea;
					break;
				}
			}
		}
		else//û�и��˺�
		{
			printf("-----------�˺Ż������������-----------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		break;

	case 3://����Ա��¼

		logMenu();
		printf("�˺ţ�");
		scanf("%s", account);
		getchar();


		if (!strcmp("return", account))//����
		{
			system("cls");
			goto Menu;
		}

		printf("���룺");
		scanf("%s", password);
	admMenu:
		if (!strcmp(admAccount, account) && !strcmp(admPassword, password))//��¼
		{
			system("cls");
			admMenu();
			choice = ifInt();
			
			switch (choice)
			{
			case 1://ɾ���˺�����
				printf("��������Ҫɾ����ѧ��ѧ�ţ�");
				num = ifInt();
				pos = numberSearch(S, num);
				if (pos == NULL)
				{
					printf("-----------ѧ����������------------\n");
					Sleep(1000);
					system("cls");
				}
				else
				{
					studentPop(&S, pos);
				}
				goto admMenu;
				break;
			case 2://�޸��˺�����
				printf("��������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
				num = ifInt();
				pos = numberSearch(S, num);
				if (pos == NULL)
				{
					printf("----------ѧ����������-----------\n");
					Sleep(1000);
					system("cls");
				}
				else
				{
					studentAccChange(&S, pos);
				}
				goto admMenu;
				break;
			case 3://�����˺�����
				printf("��������Ҫ���ҵ�ѧ��ѧ�ţ�");
				num = ifInt();
				pos = numberSearch(S, num);
				if (pos == NULL)
				{
					printf("----------ѧ����������-----------\n");
					Sleep(1000);
					system("cls");
				}
				else
				{
					pasSearch(pos);
				}
				goto admMenu;
				break;
			case 4://���ļ���ȡ�����˺�����
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
			case 5://���ļ����������˺�����
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
			case 6://¼���ʦ�˺�
				teacherInit(&T);
				teacherAdd(&T);
				goto admMenu;
				break;
			case 0://������һ��
				system("cls");
				goto Menu;
				break;

			}
		}
		else//û�и��˺�
		{
			printf("------------�˺Ż������������------------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}

		break;
	case 4://�����޸�
		printf("�����������˺�:\n");
		scanf("%s", account);
		pos = accStudentSearch(S, account);
		if (pos == NULL)
		{
			printf("------------���˺Ų�����--------------\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		else
		{
			printf("���룺");
			pasChange(&S, pos);
			printf("�޸ĳɹ���\n");
			Sleep(1000);
			system("cls");
			goto Menu;
		}
		break;
	case 5://�˺�ע��
		registerMenu();
		Register();
		goto Menu;
		break;
	default:
		printf("----------�����������������-----------\n");
		Sleep(1000);
		system("cls");
		goto Menu;
		break;
	}
	return 0;
}