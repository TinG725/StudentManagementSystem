#pragma once

#include<stdio.h>
#include<windows.h>

void mainMenu( );//--选择 ->  登录界面 or 账号相关

void logMenu();//登录都是一样的--->只有账号和密码，其他的情况在上一级提到
void registerMenu();//注册

void teaMenu();//教师菜单
void stuMenu();//学生菜单
void admMenu();//管理员菜单

void pasChange(Student** pphead, Student* pos);//修改账号密码
void pasSearch(Student* pos);//查找账号密码



