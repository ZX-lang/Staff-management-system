#include"workerManager.h"
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_FileEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;    
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())//�ļ�Ϊ��
	{
		cout << "�ļ�Ϊ��" << endl;
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
	cout << "***��ӭʹ��ְ������ϵͳ***" << endl;
	cout << "*******0 �˳��������*****" << endl;
	cout << "*******1 ����ְ����Ϣ*****" << endl;
	cout << "*******2 ��ʾְ����Ϣ*****" << endl;
	cout << "*******3 ɾ����ְְ��*****" << endl;
	cout << "*******4 �޸�ְ����Ϣ*****" << endl;
	cout << "*******5 ����ְ����Ϣ*****" << endl;
	cout << "*******6 ���ձ������*****" << endl;
	cout << "*******7 ��������ĵ�*****" << endl;
	cout << "**************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp()
{
	cout << "������ְ������" << endl;
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
		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int did;
			cout << "�������" << i + 1 << "��ְ�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��ְ������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
		cout << "��ӳɹ�" << endl;
		this->save();
	}
	else
	{
		cout << "������������" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
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
	cout << "������Ҫɾ����ְ�����" << endl;
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
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "��ְ��������" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::Mod_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		int id;
		cout << "������Ҫ�޸ĵ�ְ�����" << endl;
		cin >> id;
		int ret = isExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newId;
			string newName;
			int newDeptid;
			cout << "��������ְ����" << endl;
			cin >> newId;
			cout << "������������" << endl;
			cin >> newName;
			cout << "��������ְλ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "1���ϰ�" << endl;
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
			cout << "�޸�ʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "1������ְ����Ų�" << endl;
		cout << "1������ְ��������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "����ְ��id" << endl;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����Ϣ����" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else if(select==2)
		{
			string name;
			cout << "����ְ������" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					flag = true;
					cout << "���ҳɹ�����Ϣ����" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!flag)
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1������" << endl;
		cout << "2������" << endl;
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
		cout << "����ɹ�" << endl;
		this->save();
		cout << "�����" << endl;
		this->show_Emp();
	}
}
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
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
		cout << "��ճɹ�" << endl;
	}
	system("pasue");
	system("cls");

}