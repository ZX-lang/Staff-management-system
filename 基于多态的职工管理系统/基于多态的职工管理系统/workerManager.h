#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#define FILENAME "empFile.txt"
using namespace std;
class WorkerManager
{
public:
	//构造函数
	WorkerManager();
	//展示菜单
	void showMenu();
	//析构函数
	~WorkerManager();
	//退出系统
	void exitSystem();
	//添加职工
	void Add_Emp();
	void save();
	int get_EmpNum();
	void init_Emp();
	void show_Emp();
	void del_Emp();
	int isExist(int id);
	void Mod_Emp();
	void Find_Emp();
	void Sort_Emp();
	void Clean_File();
	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmpArray;
	bool m_FileEmpty;
};
