#include"workerManager.h"
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_FileEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;    
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())//文件为空
	{
		cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->m_FileEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
void WorkerManager::showMenu()
{
	cout << "**************************" << endl;
	cout << "***欢迎使用职工管理系统***" << endl;
	cout << "*******0 退出管理程序*****" << endl;
	cout << "*******1 增加职工信息*****" << endl;
	cout << "*******2 显示职工信息*****" << endl;
	cout << "*******3 删除离职职工*****" << endl;
	cout << "*******4 修改职工信息*****" << endl;
	cout << "*******5 查找职工信息*****" << endl;
	cout << "*******6 按照编号排序*****" << endl;
	cout << "*******7 清空所有文档*****" << endl;
	cout << "**************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp()
{
	cout << "请输入职工数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker **newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int did;
			cout << "请输入第" << i + 1 << "个职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个职工姓名" << endl;
			cin >> name;
			cout << "请选择该职工岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> did;
			Worker* worker = NULL;
			switch (did)
			{
			case 1:
				worker = new Employee(id,name,did);
				break;
			case 2:
				worker = new Manager(id, name, did);
				break;
			case 3:
				worker = new Boss(id, name, did);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileEmpty = false;
		cout << "添加成功" << endl;
		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
	system("pasue");
	system("cls");

}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int m_id;
	string m_name;
	int m_DeptId;
	int num = 0;
	while (ifs>> m_id &&ifs>> m_name &&ifs>>m_DeptId)
	{
		num++;
	}
	return num;
}
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int m_id;
	string m_name;
	int m_DeptId;
	int index = 0;
	while (ifs >> m_id && ifs >> m_name && ifs >> m_DeptId)
	{
		Worker* worker = NULL;
		if (m_DeptId == 1)
		{
			worker = new Employee(m_id, m_name, m_DeptId);
		}
		else if (m_DeptId == 2)
		{
			worker = new Manager(m_id, m_name, m_DeptId);
		}
		else
		{
			worker = new Boss(m_id, m_name, m_DeptId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkerManager::show_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(int id)
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			return i;
		}
	}
	return -1;
}
void WorkerManager::del_Emp()
{
	int id;
	cout << "请输入要删除的职工编号" << endl;
	cin >> id;
	int index = this->isExist(id);
	if (index!=-1)
	{
		for (int i = index; i < this->m_EmpNum - 1; i++)
		{
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum -= 1;
		this->save();
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "该职工不存在" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::Mod_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		int id;
		cout << "请输入要修改的职工编号" << endl;
		cin >> id;
		int ret = isExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newId;
			string newName;
			int newDeptid;
			cout << "请输入新职工号" << endl;
			cin >> newId;
			cout << "请输入新姓名" << endl;
			cin >> newName;
			cout << "请输入新职位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "1、老板" << endl;
			cin >> newDeptid;
			Worker* worker = NULL;
			switch (newDeptid)
			{
			case 1:
				worker = new Employee(newId,newName,newDeptid);
				break;
			case 2:
				worker = new Manager(newId, newName, newDeptid);
				break;
			case 3:
				worker = new Boss(newId, newName, newDeptid);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			this->save();
		}
		else
		{
			cout << "修改失败" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "1、按照职工编号查" << endl;
		cout << "1、按照职工姓名查" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "输入职工id" << endl;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "查找成功，信息如下" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else if(select==2)
		{
			string name;
			cout << "输入职工姓名" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					flag = true;
					cout << "查找成功，信息如下" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!flag)
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1、升序" << endl;
		cout << "2、降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int maxIndex = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[j]->m_id < this->m_EmpArray[maxIndex]->m_id)
					{
						maxIndex = j;
					}
				}
				else
				{
					if (this->m_EmpArray[j]->m_id > this->m_EmpArray[maxIndex]->m_id)
					{
						maxIndex = j;
					}
				}
			}
			if (maxIndex != i)
			{
				Worker* worker;
				worker = this->m_EmpArray[maxIndex];
				this->m_EmpArray[maxIndex] = this->m_EmpArray[i];
				this->m_EmpArray[i] = worker;
			}
		}
		cout << "排序成功" << endl;
		this->save();
		cout << "排序后" << endl;
		this->show_Emp();
	}
}
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
		}
		cout << "清空成功" << endl;
	}
	system("pasue");
	system("cls");

}