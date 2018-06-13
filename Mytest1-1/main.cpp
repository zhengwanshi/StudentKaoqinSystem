#include <iostream>
#include <cstring> 
#include <stdio.h>
#include <stdlib.h>//��׼��ͷ�ļ�
#include<fstream>
#include"studentinfomation.h"
#include "kechenglist.h"
#pragma warning(disable : 4996)

using namespace std;




void setup();
int lookfor(int m);
void lookforbyId(int m);//�޸����ݵ�ʱ���ȰѸ�λͬѧ���������ݺ��±��ӡ�����ͨ���±��޸�
void edit();
void Delete();
int dq(studentinfomation st[]);//�ļ�����,������Ϣ����
//void save(studentinfomation st[]);//����
void save(studentinfomation *st);
void saveAll();//������������
void TJByTime();//ͳ��ĳ��ʱ���ڿ���ѧ�����������δ����������δ����ɶൽ������
void TJByTimekecheng();//ͳ��ĳ��ʱ�����п��εĿγ̣����Ұ������˴�����
void buildTxt(); //һ������txt�ĵ�
void sore(int time);
studentinfomation studentList[100];
studentinfomation kuangkeList[100];//ѧ�����������δ���
kechenglist kechengList[100];//ͳ�ƿ��εĿγ̿����˴�

int Number = 0; //��Ϣ����


int main()
{
	FILE *fp;
	char yesorno;

	if ((fp = fopen("studentinfo.txt", "rb")) == NULL)//�½�student.dat
	{
		
		cout << " ========>��ʾ���ļ������ڣ��Ƿ�Ҫ����һ��?(y/n) \n";
		
		cin >> yesorno;
		if (yesorno == 'y' || yesorno == 'Y')
		{
			fp = fopen("studentinfo.txt", "wb");
			fclose(fp);//�ر��ļ�����
		}
		else
			exit(0);//�����˳�
	}
	else
	{
		Number = dq(studentList);
	}
	system("cls");//��

loop:
	cout << "****************************************************\n";
	cout << "**************��ӭʹ�ñ�����ϵͳ********************\n";
	cout << "****************************************************\n";
	cout << "            ��ѡ�����                              \n";
	cout << "          1 - ¼��ѧ��������Ϣ                      \n";
	cout << "          2 - ����ѧ��������Ϣ                      \n";
	cout << "          3 - �޸�ѧ��������Ϣ                      \n";
	cout << "          4 - ɾ��ѧ��������Ϣ                      \n";
	cout << "          5 - �鿴�涨ʱ����ѧ���Ŀ�������������    \n";
	cout << "          6 - �鿴�涨ʱ���ڿγ̵Ŀ����˴Σ�������  \n";
	cout << "          7 - �鿴ȫ������                          \n";
	cout << "          8 - һ������txt�ĵ�                       \n";
	cout << "          0 - �˳�                                  \n";
	cout << "****************************************************\n";

	int menu, num, tem;
	//student_info* studentInfoList=new student_info[100];
	cin >> menu;
	system("cls");

	switch (menu)
	{
	case 1:// ¼��ѧ����Ϣ
	{
		//setup(studentInfoList);
		setup();
		system("cls");
		goto loop;
		break;
	}

	case 2://����ѧ����Ϣ
	{
		cout << "�����������ѯ��ѧ��:";
		cin >> num;
		tem = lookfor(num);
		if (tem != -1)
		{
			//cout << "ѧ��\t����\t��������\t�ڼ��ڿ�\t�γ���\t\t��������\n";
			//cout << studentList[tem]._Id << "\t" << studentList[tem]._name << "\t" << studentList[tem]._date << "\t\t" << studentList[tem]._whichClass <<"\t\t"<< studentList[tem]._className<< "\t\t"<< studentList[tem]._whichkind<< endl;
			lookforbyId(num);
		}
		else
			cout << "�Բ���,��ѧ�Ų�����!\n";
		system("pause");
		system("cls");
		goto loop;
		break;
	}
	case 3://�޸�ѧ����Ϣ
	{
		edit();
		system("cls");
		goto loop;
		break;
	}
	case 4://ɾ��ѧ����Ϣ
	{
		Delete();
		system("cls");
		goto loop;
		break;
	}
	case 5://5 - �鿴�涨ʱ����ѧ���Ŀ�������������
	{
		TJByTime();
		system("cls");
		goto loop;
		break;
	}
	case 6://ͳ��ĳ��ʱ�����п��εĿγ̣����Ұ������˴�����
	{
		TJByTimekecheng();
		system("cls");
		goto loop;
		break;
	}
	case 7://�鿴ȫ����Ϣ
	{
		cout << "ѧ��\t����\t��������\t�ڼ��ڿ�\t�γ���\t\t��������\n\n";
		for (int i = 0; i < Number-1; i++) {
			if(studentList[i]._Id!=0)
			cout << studentList[i]._Id << "\t" << studentList[i]._name << "\t" << studentList[i]._date << "\t\t" << studentList[i]._whichClass << "\t\t" << studentList[i]._className << "\t\t" << studentList[i]._whichkind << endl;
		}
		system("pause");
		system("cls");
		goto loop;
		break;
	}
	case 8://�˳� 
	{
		buildTxt(); //һ������txt�ĵ�
		system("pause");
		system("cls");
		goto loop;
		break;
	}
	
	case 0://�˳� 
	{
		cout << "ллʹ��!\n";
		break;
	}

	default:
	{
		cout << "���������!\n";
		system("cls");
		goto loop;
		break;
	}
	}
	return 0;
}


/*
�������
*/
void setup()
{
	char str;
	for (int i = 0; i<100; i++)
	{
		cout << "������ѧ��ѧ�š����������ڡ��ڼ��ڿΡ��γ������������\n";		
		cin >> studentList[i]._Id>> studentList[i]._name >> studentList[i]._date>> studentList[i]._whichClass >> studentList[i]._className >> studentList[i]._whichkind;
		save(&studentList[i]);//׷�ӷ�ʽ����һ������
		Number++;
		cout << "������y/n)\n";		
		cin >> str;
		if (str == 'n')			
			break;
	}
	//��������꣬��������
	//saveAll();
	Number = dq(studentList);
}
/*
ͨ��ѧ�Ų������ݣ��������ݵ�λ��*/
int lookfor(int m)
{
	for (int i = 0; i<Number; i++)
	{
		if (m == studentList[i]._Id)
			return i;
	}
	return -1;
}
void lookforbyId(int m)//�޸����ݵ�ʱ���ȰѸ�λͬѧ���������ݺ��±��ӡ�����ͨ���±��޸�
{
	cout << "�±�\tѧ��\t����\t��������\t�ڼ��ڿ�\t�γ���\t\t��������\n";
	for (int i = 0; i<Number; i++)
	{
		if (m == studentList[i]._Id) {			
			cout << i<<"\t"<<studentList[i]._Id << "\t" << studentList[i]._name << "\t" << studentList[i]._date << "\t\t" << studentList[i]._whichClass << "\t\t" << studentList[i]._className << "\t\t" << studentList[i]._whichkind << endl;
			
		}			
	}
	
}

void edit()
{
	
	int t, m,n;
	cout << "��ѡ��ѧ�ţ�" << endl;
	cin >> m;
	lookforbyId(m);//���ҳ���ͬѧ���������ݺ��±�λ��
	cout << "��ѡ���¼�±꣺" << endl;
	cin >> n;
	if (n != -1)
	{
		cout << "******************************\n";
		cout << "             ��ѡ��:          \n";
		cout << "        1 - �޸�����          \n";
		cout << "        2 - �޸�����          \n";
		cout << "        3 - �޸ĵڼ��ڿ�      \n";
		cout << "        4 - �޸Ŀγ���        \n";
		cout << "        5 - �޸Ŀ�������      \n";
		cout << "        6 - �޸�ѧ��          \n";
		cout << "******************************\n";
		cin >> t;

		switch (t)
		{
		case 1:
			cout << "������ѧ��������\n";
			cin >> studentList[n]._name;
		
			break;
		case 2:
			cout << "������ѧ���µĿ�������\n";			
			cin >> studentList[n]._date;
			
			break;
		case 3:
			cout << "������ѧ���µĿ��ڵڼ��ڿ�\n";
			cin >> studentList[n]._whichClass;
		
			break;
		case 4:
			cout << "������ѧ���µĿγ�\n";
			cin >> studentList[n]._className;
		
			break;
		case 5:
			cout << "������ѧ���µĿ�������\n";
			cin >> studentList[n]._whichkind;			
			break;
		case 6:
			cout << "������ѧ���µ�ѧ��\n";
			cin >> studentList[n]._Id;
			break;
		}
		//�޸����ݺ󱣴�

		FILE *fp = NULL;
		int i;
		fp = fopen("studentinfo.txt", "wb");
		for (i = 0; i<Number; i++)
		{
			fwrite(&studentList[i], sizeof(studentinfomation), 1, fp);
		}
		fclose(fp);	
	}
	else
		cout << "��ѧ�Ų�����!\n";
}

void Delete()
{
	int temp, m;
	int i = 0;
	cout << "��ѡ��ѧ�ţ�" << endl;
	cin >> m;
	temp = lookfor(m);
	if (temp != -1)
	{	
		for (i = temp; i < Number - 1; i++) {
			studentList[i] = studentList[i + 1];
		}
		Number--;
		FILE *fp = NULL;
		fp = fopen("studentinfo.txt", "wb");
		for (i = 0; i<Number; i++)
		{
			fwrite(&studentList[i], sizeof(studentinfomation), 1, fp);
		}
		fclose(fp);
		printf("ɾ���ɹ�;\n");
	}
	else
		cout << "��ѧ�Ų�����!\n";	
}

int dq(studentinfomation st[])//�������ݵ�����
{
	FILE *fp = NULL;
	int i = 0;
	fp = fopen("studentinfo.txt", "rb");
	//while(fread(&st[i],sizeof(struct student),1,fp))

	while (!feof(fp))/*�ж��Ƿ������������и��ļ�������*/
	{		
		fread(&st[i], sizeof(studentinfomation), 1, fp);
		i++;
	}	
	fclose(fp);	
	return i;
}

void save(studentinfomation *st)
{
	FILE *fp = NULL;
	fp = fopen("studentinfo.txt", "ab+");
	fwrite(st, sizeof(studentinfomation), 1, fp);
	fclose(fp);
}
//������������
void saveAll() {
	FILE *fp = NULL;
	int i;
	fp = fopen("studentinfo.txt", "wb");
	for (i = 0; i<Number; i++)
	{
		fwrite(&studentList[i], sizeof(studentinfomation), 1, fp);
	}
	fclose(fp);
}

void TJByTime()//ͳ��ĳ��ʱ���ڿ���ѧ�����������δ����������δ����ɶൽ������
{
	int i = 0;
	int j = 0;
	float t1, t2;
	bool flage = true;
	int cpyTime = 0;
	cout << "�����뿪ʼʱ���"<<endl;
	cin >> t1;
	cout << "�������ֹʱ���" << endl;
	cin >> t2;
	//ͳ�ƿ��δ���
	for (i = 0; i < Number; i++) {
		if(studentList[i]._date>=t1 && studentList[i]._date <= t2)//ʱ��ڵ�Ĺ���
		if (strcmp(studentList[i]._whichkind, "����") == 0) {//��һλѧ��ͬΪ�������ݺϲ������Ҽ�¼����
			//studentList[i]._kuangkeTime++;
			flage = true;
			for (int k = 0; k <=j; k++) {
				if (strcmp(kuangkeList[k]._name, studentList[i]._name) == 0) {
					kuangkeList[k]._kuangkeTime++;
					flage = false;
					break;
				}
			}
			if (flage) {
				strcpy(kuangkeList[j]._name, studentList[i]._name);
				kuangkeList[j]._kuangkeTime=1;
				j++;
				cpyTime++;
			}			
		}
	}
	sore(cpyTime);
	cout << "����\t" <<"���δ���"<< endl;
	for (int i = 0; i < cpyTime; i++) {
		cout << kuangkeList[i]._name << "\t" << kuangkeList[i]._kuangkeTime << endl;
	}
	system("pause");
}

void TJByTimekecheng()//ͳ��ĳ��ʱ�����п��εĿγ̣����Ұ������˴�����
{
	int i = 0;
	int j = 0;
	float t1, t2;
	bool flage = true;
	int cpyTime = 0;
	cout << "�����뿪ʼʱ���" << endl;
	cin >> t1;
	cout << "�������ֹʱ���" << endl;
	cin >> t2;
	//ͳ�ƿ��δ���
	for (i = 0; i < Number; i++) {
		if (studentList[i]._date >= t1 && studentList[i]._date <= t2)//ʱ��ڵ�Ĺ���
			if (strcmp(studentList[i]._whichkind, "����") == 0) {//ͬΪ�������ݺϲ������Ҽ�¼����															   
				flage = true;
				for (int k = 0; k <= j; k++) {
					if (strcmp(kechengList[k]._className, studentList[i]._className) == 0) {
						kechengList[k]._kuangkeTime++;
						flage = false;
						break;
					}
				}
				if (flage) {
					strcpy(kechengList[j]._className, studentList[i]._className);
					kechengList[j]._kuangkeTime = 1;
					j++;
					cpyTime++;
				}
			}
	}
	sore(cpyTime);
	cout << "�γ���\t" << "�����˴�" << endl;
	for (int i = 0; i < cpyTime; i++) {
		cout << kechengList[i]._className<< "\t" << kechengList[i]._kuangkeTime<< endl;
	}
	system("pause");
}

void sore(int time) {//ð�������Ӵ�С����
	
	studentinfomation temp;

	for (int i = 0; i < time; i++) {
		for (int j = 0; j<time - 1 - i; j++) {
			if (kuangkeList[j]._kuangkeTime < kuangkeList[j+1]._kuangkeTime) {
				 temp = kuangkeList[j];
				 kuangkeList[j] = kuangkeList[j+1];
				 kuangkeList[j+1] = temp;
			}
		}
	}	
}

void buildTxt() //һ������txt�ĵ�
{
	ofstream outfile;
	outfile.open("myfile.txt");
	outfile << "ѧ��\t����\t��������\t\t�ڼ��ڿ�\t\t�γ���\t\t��������\n\n";
	for (int i = 0; i < Number - 1; i++) {
		if (studentList[i]._Id != 0)
			outfile << studentList[i]._Id << "\t" << studentList[i]._name << "\t" << studentList[i]._date << "\t\t" << studentList[i]._whichClass << "\t\t" << studentList[i]._className << "\t\t" << studentList[i]._whichkind << endl;
	}
	outfile.close();
	cout << "txt�ĵ��������ɳɹ�����" << endl;
}

