#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define MAX_NAME 50
#define MAX_SEX 5
#define MAX_CLASS 200
#define MAX_ACCOUNT 20 
#define MAX_PASSWORD 20
#define MAX 100


//����ѧ���ṹ
//���֣�ѧ�ţ��ɼ�,���䣬�Ա�, �༶
typedef struct Student
{
	int number;
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int class;//���ڰ༶ ��������
	double score;

	char account[MAX_ACCOUNT];
	char password[MAX_PASSWORD];
	struct Student* prev;//˫�������ǰһ��
	struct Student* next; 
}Student;

//��ʦ�ṹ�� �����洢���ڰ༶ �˺�����
typedef struct Teacher
{
	char name[MAX_NAME];
	int class;
	char account[MAX_ACCOUNT];
	char password[MAX_PASSWORD];

	struct Teacher* next;
}Teacher;

Student* S;
Teacher* T;

//ѧ�����ɼ���ѯ����ѯ����ɼ���������һ��
//��ʦ����ɾ���ѧ����Ϣ���鿴���ڳɼ���������һ��
//����Ա����ɾ�Ĳ������Լ�ѧ����Ϣ�����ļ�¼�������˺����룬���ļ����������˺����룬������һ��

void studentInit(Student** pphead);//��ʼ������
void studentPrint(Student* pos);//��ӡָ����������

void Register();//ע��
Student* getNode(char* account, char* password);//�õ�һ���½��

Student* numberSearch(Student* phead, int number);//��ѧ�Ų�ѯѧ����Ϣ--���ؽ��
void studentChange(Student** pphead, Student* pos);//���ս���޸�ѧ����Ϣ
void studentAccChange(Student** pphead, Student* pos);//�޸�ѧ�����˺�����

void studentAdd(Student** pphead, char* account,char* password);//���ѧ����Ϣ
void insertFront(Student** pphead, Student* pos);//����λ��ǰ����½��
void insertBack(Student** pphead, Student* pos);//����λ�ú�����½��

void studentPop(Student** pphead, Student* pos);//ɾ��ָ��λ�õ�����

void teacherInit(Teacher** pphead);//��ʦ�ṹ��ĳ�ʼ��
void teacherAdd(Teacher** pphead);//��ʦ��Ϣ���
void teacherLook(Student* phead);//��ʦ�鿴���ڳɼ�


int ifInt();//�ж������Ƿ�������

Student* accStudentSearch(Student* phead, char* account);//�����˺Ų���ѧ��
Teacher* accTeacherSearch(Teacher* phead, char* account);//�����˺Ų���ѧ��


