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


//定义学生结构
//名字，学号，成绩,年龄，性别, 班级
typedef struct Student
{
	int number;
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	int class;//所在班级 输入数字
	double score;

	char account[MAX_ACCOUNT];
	char password[MAX_PASSWORD];
	struct Student* prev;//双向链表的前一个
	struct Student* next; 
}Student;

//教师结构体 用来存储所在班级 账号密码
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

//学生：成绩查询，查询本班成绩，返回上一级
//教师：增删查改学生信息，查看班内成绩，返回上一级
//管理员：增删改查账密以及学生信息，从文件录入所有账号密码，从文件导出所有账号密码，返回上一级

void studentInit(Student** pphead);//初始化链表
void studentPrint(Student* pos);//打印指定结点的数据

void Register();//注册
Student* getNode(char* account, char* password);//得到一个新结点

Student* numberSearch(Student* phead, int number);//按学号查询学生信息--返回结点
void studentChange(Student** pphead, Student* pos);//按照结点修改学生信息
void studentAccChange(Student** pphead, Student* pos);//修改学生的账号密码

void studentAdd(Student** pphead, char* account,char* password);//添加学生信息
void insertFront(Student** pphead, Student* pos);//任意位置前添加新结点
void insertBack(Student** pphead, Student* pos);//任意位置后添加新结点

void studentPop(Student** pphead, Student* pos);//删除指定位置的数据

void teacherInit(Teacher** pphead);//教师结构体的初始化
void teacherAdd(Teacher** pphead);//教师信息添加
void teacherLook(Student* phead);//教师查看班内成绩


int ifInt();//判断输入是否是整数

Student* accStudentSearch(Student* phead, char* account);//根据账号查找学生
Teacher* accTeacherSearch(Teacher* phead, char* account);//根据账号查找学生


