#define _CRT_SECURE_NO_WARNINGS


#include"File.h"
#include"SMS.h"
#include"UI.h"

// д��ѧ����Ϣ���ļ�
void writeStudentsToFile(Student* head, const char* filename) {//��� ����
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("�޷����ļ�");
        return;
    }
    Student* current = head;
    while (current != NULL ) {//ѭ��д�� 
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

// ���ļ��ж�ȡѧ����Ϣ����������
Student* readStudentsFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");//�����Ʒ�ʽ��
    if (file == NULL) {
        perror("�޷����ļ�");
        return NULL;
    }
    Student* head = NULL;
    Student* tail = NULL;
    Student* newStudent;
    while (1) {
        newStudent = (Student*)malloc(sizeof(Student));
        if (fread(newStudent, sizeof(Student), 1, file) != 1) {//��ȡ���� ����
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


// д���ʦ��Ϣ���ļ�
void writeTeachersToFile(Teacher* head, const char* filename) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("�޷����ļ�");
        return;
    }
    Student* current = head;
    while (current != NULL) {//ѭ��д�� 
        fwrite(current, sizeof(Teacher), 1, file);
        current = current->next;
    }
    fclose(file);
}


// ���ļ��ж�ȡ��ʦ��Ϣ����������
Teacher* readTeachersFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");//�����Ʒ�ʽ��
    if (file == NULL) {
        perror("�޷����ļ�");
        return NULL;
    }
    Teacher* head = NULL;
    Teacher* tail = NULL;
    Teacher* newTeacher;
    while (1) {
        newTeacher = (Teacher*)malloc(sizeof(Teacher));
        if (fread(newTeacher, sizeof(Teacher), 1, file) != 1) {//��ȡ���� ����
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