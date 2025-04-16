#define _CRT_SECURE_NO_WARNINGS

#include"SMS.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void writeStudentsToFile(Student* head, const char* filename);
Student* readStudentsFromFile(const char* filename);

void writeTeachersToFile(Teacher* head, const char* filename);
Teacher* readTeachersFromFile(const char* filename);
