#define _CRT_SECURE_NO_WARNINGS


#include"File.h"
#include"SMS.h"
#include"UI.h"

// 写入学生信息到文件
void writeStudentsToFile(Student* head, const char* filename) {//结点 名字
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("无法打开文件");
        return;
    }
    Student* current = head;
    while (current != NULL ) {//循环写入 
        fwrite(current, sizeof(Student), 1, file);
        current = current->next;
        if (current == head)
        {
            fclose(file);
            return;
        }
    }
    fclose(file);
}

// 从文件中读取学生信息并构建链表
Student* readStudentsFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");//二进制方式读
    if (file == NULL) {
        perror("无法打开文件");
        return NULL;
    }
    Student* head = NULL;
    Student* tail = NULL;
    Student* newStudent;
    while (1) {
        newStudent = (Student*)malloc(sizeof(Student));
        if (fread(newStudent, sizeof(Student), 1, file) != 1) {//读取完了 跳出
            free(newStudent);
            break;
        }
        newStudent->next = NULL;
        newStudent->prev = NULL;
        if (head == NULL) {
            head = newStudent;
            tail = newStudent;
            head->prev = head->next = head;
        }
        else {
            newStudent->prev = tail;
            newStudent->next = head;
            head->prev->next = newStudent;
            head->prev = newStudent;
        }
    }
    fclose(file);
    return head;
}


// 写入教师信息到文件
void writeTeachersToFile(Teacher* head, const char* filename) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("无法打开文件");
        return;
    }
    Student* current = head;
    while (current != NULL) {//循环写入 
        fwrite(current, sizeof(Teacher), 1, file);
        current = current->next;
    }
    fclose(file);
}


// 从文件中读取教师信息并构建链表
Teacher* readTeachersFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");//二进制方式读
    if (file == NULL) {
        perror("无法打开文件");
        return NULL;
    }
    Teacher* head = NULL;
    Teacher* tail = NULL;
    Teacher* newTeacher;
    while (1) {
        newTeacher = (Teacher*)malloc(sizeof(Teacher));
        if (fread(newTeacher, sizeof(Teacher), 1, file) != 1) {//读取完了 跳出
            free(newTeacher);
            break;
        }
        newTeacher->next = NULL;
        if (head == NULL) {
            head = newTeacher;
            tail = newTeacher;
        }
        else {
            tail->next = newTeacher;
            tail = newTeacher;
        }
    }
    fclose(file);
    return head;
}