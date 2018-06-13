#include <iostream>
#include <cstring> 
#include <stdio.h>
#include <stdlib.h>//标准库头文件
#include<fstream>
#include"studentinfomation.h"
#include "kechenglist.h"
#pragma warning(disable : 4996)

using namespace std;




void setup();
int lookfor(int m);
void lookforbyId(int m);//修改数据的时候先把该位同学的所有数据和下标打印，最后通过下标修改
void edit();
void Delete();
int dq(studentinfomation st[]);//文件操作,返回信息总数
//void save(studentinfomation st[]);//保存
void save(studentinfomation *st);
void saveAll();//保存所有数据
void TJByTime();//统计某段时间内旷课学生姓名及旷课次数，按旷课次数由多到少排列
void TJByTimekecheng();//统计某段时间内有旷课的课程，并且按旷课人次排序
void buildTxt(); //一键生成txt文档
void sore(int time);
studentinfomation studentList[100];
studentinfomation kuangkeList[100];//学生姓名及旷课次数
kechenglist kechengList[100];//统计旷课的课程宽阔人次

int Number = 0; //信息总数


int main()
{
	FILE *fp;
	char yesorno;

	if ((fp = fopen("studentinfo.txt", "rb")) == NULL)//新建student.dat
	{
		
		cout << " ========>提示：文件不存在，是否要创建一个?(y/n) \n";
		
		cin >> yesorno;
		if (yesorno == 'y' || yesorno == 'Y')
		{
			fp = fopen("studentinfo.txt", "wb");
			fclose(fp);//关闭文件保存
		}
		else
			exit(0);//正常退出
	}
	else
	{
		Number = dq(studentList);
	}
	system("cls");//清

loop:
	cout << "****************************************************\n";
	cout << "**************欢迎使用本考勤系统********************\n";
	cout << "****************************************************\n";
	cout << "            请选择服务                              \n";
	cout << "          1 - 录入学生考勤信息                      \n";
	cout << "          2 - 查找学生考勤信息                      \n";
	cout << "          3 - 修改学生考勤信息                      \n";
	cout << "          4 - 删除学生考勤信息                      \n";
	cout << "          5 - 查看规定时间内学生的旷课数，并排序    \n";
	cout << "          6 - 查看规定时间内课程的旷课人次，并排序  \n";
	cout << "          7 - 查看全部数据                          \n";
	cout << "          8 - 一键生成txt文档                       \n";
	cout << "          0 - 退出                                  \n";
	cout << "****************************************************\n";

	int menu, num, tem;
	//student_info* studentInfoList=new student_info[100];
	cin >> menu;
	system("cls");

	switch (menu)
	{
	case 1:// 录入学生信息
	{
		//setup(studentInfoList);
		setup();
		system("cls");
		goto loop;
		break;
	}

	case 2://查找学生信息
	{
		cout << "请输入您想查询的学号:";
		cin >> num;
		tem = lookfor(num);
		if (tem != -1)
		{
			//cout << "学号\t姓名\t考勤日期\t第几节课\t课程名\t\t考勤类型\n";
			//cout << studentList[tem]._Id << "\t" << studentList[tem]._name << "\t" << studentList[tem]._date << "\t\t" << studentList[tem]._whichClass <<"\t\t"<< studentList[tem]._className<< "\t\t"<< studentList[tem]._whichkind<< endl;
			lookforbyId(num);
		}
		else
			cout << "对不起,该学号不存在!\n";
		system("pause");
		system("cls");
		goto loop;
		break;
	}
	case 3://修改学生信息
	{
		edit();
		system("cls");
		goto loop;
		break;
	}
	case 4://删除学生信息
	{
		Delete();
		system("cls");
		goto loop;
		break;
	}
	case 5://5 - 查看规定时间内学生的旷课数，并排序
	{
		TJByTime();
		system("cls");
		goto loop;
		break;
	}
	case 6://统计某段时间内有旷课的课程，并且按旷课人次排序
	{
		TJByTimekecheng();
		system("cls");
		goto loop;
		break;
	}
	case 7://查看全部信息
	{
		cout << "学号\t姓名\t考勤日期\t第几节课\t课程名\t\t考勤类型\n\n";
		for (int i = 0; i < Number-1; i++) {
			if(studentList[i]._Id!=0)
			cout << studentList[i]._Id << "\t" << studentList[i]._name << "\t" << studentList[i]._date << "\t\t" << studentList[i]._whichClass << "\t\t" << studentList[i]._className << "\t\t" << studentList[i]._whichkind << endl;
		}
		system("pause");
		system("cls");
		goto loop;
		break;
	}
	case 8://退出 
	{
		buildTxt(); //一键生成txt文档
		system("pause");
		system("cls");
		goto loop;
		break;
	}
	
	case 0://退出 
	{
		cout << "谢谢使用!\n";
		break;
	}

	default:
	{
		cout << "错误的请求!\n";
		system("cls");
		goto loop;
		break;
	}
	}
	return 0;
}


/*
添加数据
*/
void setup()
{
	char str;
	for (int i = 0; i<100; i++)
	{
		cout << "请输入学生学号、姓名、日期、第几节课、课程名、考勤类别：\n";		
		cin >> studentList[i]._Id>> studentList[i]._name >> studentList[i]._date>> studentList[i]._whichClass >> studentList[i]._className >> studentList[i]._whichkind;
		save(&studentList[i]);//追加方式保存一条数据
		Number++;
		cout << "继续（y/n)\n";		
		cin >> str;
		if (str == 'n')			
			break;
	}
	//添加数据完，保存数据
	//saveAll();
	Number = dq(studentList);
}
/*
通过学号查找数据，返回数据的位置*/
int lookfor(int m)
{
	for (int i = 0; i<Number; i++)
	{
		if (m == studentList[i]._Id)
			return i;
	}
	return -1;
}
void lookforbyId(int m)//修改数据的时候先把该位同学的所有数据和下标打印，最后通过下标修改
{
	cout << "下标\t学号\t姓名\t考勤日期\t第几节课\t课程名\t\t考勤类型\n";
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
	cout << "请选择学号：" << endl;
	cin >> m;
	lookforbyId(m);//查找出该同学的所有数据和下标位置
	cout << "请选择记录下标：" << endl;
	cin >> n;
	if (n != -1)
	{
		cout << "******************************\n";
		cout << "             请选择:          \n";
		cout << "        1 - 修改姓名          \n";
		cout << "        2 - 修改日期          \n";
		cout << "        3 - 修改第几节课      \n";
		cout << "        4 - 修改课程名        \n";
		cout << "        5 - 修改考勤类型      \n";
		cout << "        6 - 修改学号          \n";
		cout << "******************************\n";
		cin >> t;

		switch (t)
		{
		case 1:
			cout << "请输入学生的名字\n";
			cin >> studentList[n]._name;
		
			break;
		case 2:
			cout << "请输入学生新的考勤日期\n";			
			cin >> studentList[n]._date;
			
			break;
		case 3:
			cout << "请输入学生新的考勤第几节课\n";
			cin >> studentList[n]._whichClass;
		
			break;
		case 4:
			cout << "请输入学生新的课程\n";
			cin >> studentList[n]._className;
		
			break;
		case 5:
			cout << "请输入学生新的考勤类型\n";
			cin >> studentList[n]._whichkind;			
			break;
		case 6:
			cout << "请输入学生新的学号\n";
			cin >> studentList[n]._Id;
			break;
		}
		//修改数据后保存

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
		cout << "此学号不存在!\n";
}

void Delete()
{
	int temp, m;
	int i = 0;
	cout << "请选择学号：" << endl;
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
		printf("删除成功;\n");
	}
	else
		cout << "此学号不存在!\n";	
}

int dq(studentinfomation st[])//返回数据的条数
{
	FILE *fp = NULL;
	int i = 0;
	fp = fopen("studentinfo.txt", "rb");
	//while(fread(&st[i],sizeof(struct student),1,fp))

	while (!feof(fp))/*判断是否结束，这里会有个文件结束符*/
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
//保存所有数据
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

void TJByTime()//统计某段时间内旷课学生姓名及旷课次数，按旷课次数由多到少排列
{
	int i = 0;
	int j = 0;
	float t1, t2;
	bool flage = true;
	int cpyTime = 0;
	cout << "请输入开始时间点"<<endl;
	cin >> t1;
	cout << "请输入截止时间点" << endl;
	cin >> t2;
	//统计旷课次数
	for (i = 0; i < Number; i++) {
		if(studentList[i]._date>=t1 && studentList[i]._date <= t2)//时间节点的过滤
		if (strcmp(studentList[i]._whichkind, "旷课") == 0) {//把一位学生同为旷课数据合并，并且记录数次
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
	cout << "姓名\t" <<"旷课次数"<< endl;
	for (int i = 0; i < cpyTime; i++) {
		cout << kuangkeList[i]._name << "\t" << kuangkeList[i]._kuangkeTime << endl;
	}
	system("pause");
}

void TJByTimekecheng()//统计某段时间内有旷课的课程，并且按旷课人次排序
{
	int i = 0;
	int j = 0;
	float t1, t2;
	bool flage = true;
	int cpyTime = 0;
	cout << "请输入开始时间点" << endl;
	cin >> t1;
	cout << "请输入截止时间点" << endl;
	cin >> t2;
	//统计旷课次数
	for (i = 0; i < Number; i++) {
		if (studentList[i]._date >= t1 && studentList[i]._date <= t2)//时间节点的过滤
			if (strcmp(studentList[i]._whichkind, "旷课") == 0) {//同为旷课数据合并，并且记录数次															   
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
	cout << "课程名\t" << "旷课人次" << endl;
	for (int i = 0; i < cpyTime; i++) {
		cout << kechengList[i]._className<< "\t" << kechengList[i]._kuangkeTime<< endl;
	}
	system("pause");
}

void sore(int time) {//冒泡排序查从大到小排序
	
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

void buildTxt() //一键生成txt文档
{
	ofstream outfile;
	outfile.open("myfile.txt");
	outfile << "学号\t姓名\t考勤日期\t\t第几节课\t\t课程名\t\t考勤类型\n\n";
	for (int i = 0; i < Number - 1; i++) {
		if (studentList[i]._Id != 0)
			outfile << studentList[i]._Id << "\t" << studentList[i]._name << "\t" << studentList[i]._date << "\t\t" << studentList[i]._whichClass << "\t\t" << studentList[i]._className << "\t\t" << studentList[i]._whichkind << endl;
	}
	outfile.close();
	cout << "txt文档数据生成成功！！" << endl;
}

