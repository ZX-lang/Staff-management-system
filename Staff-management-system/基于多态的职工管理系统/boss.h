#pragma once
#include "worker.h"
#include<iostream>
using namespace std;
class Boss:public Worker
{
public:
	Boss(int id, string name, int dId);
	//��ʾ������Ϣ
	void showInfo();
	//��ȡ��λ����
	string getDeptName();
private:
	 
};