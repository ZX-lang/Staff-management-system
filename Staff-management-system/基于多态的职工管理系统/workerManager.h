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
	//���캯��
	WorkerManager();
	//չʾ�˵�
	void showMenu();
	//��������
	~WorkerManager();
	//�˳�ϵͳ
	void exitSystem();
	//���ְ��
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
	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmpArray;
	bool m_FileEmpty;
};
