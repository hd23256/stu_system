#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define admintea_csv_Address teadata.txt;//教师登陆信息的数据表
//#define adminstu_csv_Address studata.txt;//学生登陆信息的数据表
#define Login_password "202005"			//最高权限注册密码,十位数以内

//#define studata_csv_Address stu.txt;//学生信息的数据表
typedef struct STUDENT
{
	char account[16];//学号
	char Class[8];//班级
	char name[10];//姓名
	char score[5];//分数
	struct STUDENT* pNext;
}stu_infor;

int student_number;//记录学生的学号
char* GetString()//记录输入的字符串
{
	//动态分配内存
	char c;
	int size = 5;
	char* str = (char*)malloc(size);
	char* newstr = NULL;
	char* pMark = str;
	int count = 0;
	while((c=getchar()) != '\n')
	{
		*str = c;
		str++;
		count++;
		if(count + 1 == size)
		{
			*str = '\0';
			size+=5;
			newstr = (char*)malloc(size);
			strcpy_s(newstr,size,pMark);
			free(pMark);
			pMark = newstr;
			str = newstr + count;
		}
	}
	*str = '\0';
	return pMark;
}
int RegisterTea()//教师注册  1为注册成功  0为注册失败
{
	char account[16],password[16],jur[11];//账号，密码，注册密码
	FILE *fp;
	int turn = 1;	//用于检测账号是否已注册的开关
	char password_che[16];	    //用于检测两次输入的密码是否一致
	char str1_account[16]={0},str2_password[16]={0};     //检验账号，检验密码
	printf("请输入您的工号：");
	scanf("%s",account);
	do{
		printf("请输入密码：");
		scanf("%s",password);
		printf("请再次输入密码：");
		scanf("%s",password_che);
		if(strcmp(password,password_che))
			printf("密码不一致，请重新输入！\n\n");
	}while(strcmp(password,password_che));
	printf("请输入注册密码：");
	scanf("%s",jur);
	if(strcmp(jur,Login_password))
	{
		printf("注册密码错误，注册失败！\n");
		return 0;
	}
	else
	{
		if((fp=fopen("admintea_csv_Address","a+"))==NULL)//检验"教师登陆信息的数据表"是否成功打开
		{
			printf("注册失败！\n");//多半是"admintea_csv_Address"地址不存在
			return 0;
		}
		else
		{
			while(!feof(fp))//feof 函数用于检测文件的末尾指示器（end-of-file indicator）是否被设置。
			{
				fscanf(fp,"%s%s",str1_account,str2_password);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
				if(!strcmp(str1_account,account))//如果"教师登陆信息的数据表"已有我输入的账号，进入
				{
					turn=0;//账号已注册
					break;
				}
			}//遍历整个"教师登陆信息的数据表"
			if(turn)
			{
				//把我输入的账号和密码存进"教师登陆信息的数据表"中
				fseek(fp,0,2);//文件定位，将文件指针指向文件末尾
				fprintf(fp,"%s %s\n",account,password);
				fflush(fp);//fflush()会强迫将缓冲区内的数据写回指定的文件中。
				printf("注册成功！\n");
				fclose(fp);//关闭文件
				return 1;
			}
			else
			{
				printf("账号已注册！\n");
				fclose(fp);//关闭文件
				return 0;
			}
		}
	}
}
int RegisterStu()//学生注册  1为注册成功  0为注册失败 和教师注册相同只是改变"学生登陆信息的数据表"文件位置
{
	char account[16],password[16],jur[11];//账号，密码，注册密码
	FILE *fp;
	int turn = 1;	//用于检测账号是否已注册的开关
	char password_che[16];	    //用于检测两次输入的密码是否一致
	char str1_account[16]={0},str2_password[16]={0};     //检验账号，检验密码
	printf("请输入您的学号：");
	scanf("%s",account);
	do{
		printf("请输入密码：");
		scanf("%s",password);
		printf("请再次输入密码：");
		scanf("%s",password_che);
		if(strcmp(password,password_che))
			printf("密码不一致，请重新输入！\n\n");
	}while(strcmp(password,password_che));
	printf("请输入注册密码：");
	scanf("%s",jur);
	if(strcmp(jur,Login_password))
	{
		printf("注册密码错误，注册失败！\n");
		return 0;
	}
	else
	{
		if((fp=fopen("adminstu_csv_Address","a+"))==NULL)//检验"学生登陆信息的数据表"是否成功打开
		{
			printf("注册失败！\n");//多半是"adminstu_csv_Address"地址不存在
			return 0;
		}
		else
		{
			while(!feof(fp))//feof 函数用于检测文件的末尾指示器（end-of-file indicator）是否被设置。
			{
				fscanf(fp,"%s%s",str1_account,str2_password);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
				if(!strcmp(str1_account,account))//如果"学生登陆信息的数据表"已有我输入的账号，进入
				{
					turn=0;//账号已注册
					break;
				}
			}//遍历整个"学生登陆信息的数据表"
			if(turn)
			{
				//把我输入的账号和密码存进"学生登陆信息的数据表"中
				fseek(fp,0,2);//文件定位，将文件指针指向文件末尾
				fprintf(fp,"%s %s\n",account,password);
				fflush(fp);//fflush()会强迫将缓冲区内的数据写回指定的文件中。
				printf("注册成功！\n");
				fclose(fp);//关闭文件
				student_number=atoi(account);//记录这个学生的学号
				return 1;
			}
			else
			{
				printf("账号已注册！\n");
				fclose(fp);//关闭文件
				return 0;
			}
		}
	}
}
int LoginTea()//教师登录  1为登录成功  0为登录失败
{
	char account[16],password[16];//账号，密码
	char str1_account[16]={0},str2_password[16]={0};//检验账号，检验密码
	int turn=0;//用于检验账号密码是否匹配
	FILE *fp;
	printf("请输入您的工号：");
	scanf("%s",account);
	printf("请输入密码：");
	scanf("%s",password);
	if((fp=fopen("admintea_csv_Address","r"))==NULL)//检验"教师登陆信息的数据表"是否成功打开
	{
		printf("登录失败！\n");//多半是"admintea_csv_Address"地址不存在
		return 0;
	}
	else
	{
		while(!feof(fp))//feof 函数用于检测文件的末尾指示器（end-of-file indicator）是否被设置。
		{
			fscanf(fp,"%s%s",str1_account,str2_password);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
			if(!strcmp(str1_account,account)&&!strcmp(str2_password,password))//如果"教师登陆信息的数据表"已有我输入的账号，进入
			{
				turn=1;//输入的账号和密码是正确的
				break;
			}
		}//遍历整个"教师登陆信息的数据表"
		if(turn)
		{
			printf("登录成功！\n");
			fclose(fp);
			return 1;
		}
		else
		{
			printf("账号或密码错误，登录失败！\n");
			fclose(fp);
			return 0;
		}
	}
}
int LoginStu()//学生登录  1为登录成功  0为登录失败
{
	char account[16],password[16];//账号，密码
	char str1_account[16]={0},str2_password[16]={0};//检验账号，检验密码
	int turn=0;//用于检验账号密码是否匹配
	FILE *fp;
	printf("请输入您的工号：");
	scanf("%s",account);
	printf("请输入密码：");
	scanf("%s",password);
	if((fp=fopen("adminstu_csv_Address","r"))==NULL)//检验"教师登陆信息的数据表"是否成功打开
	{
		printf("登录失败！\n");//多半是"adminstu_csv_Address"地址不存在
		return 0;
	}
	else
	{
		while(!feof(fp))//feof 函数用于检测文件的末尾指示器（end-of-file indicator）是否被设置。
		{
			fscanf(fp,"%s%s",str1_account,str2_password);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
			if(!strcmp(str1_account,account)&&!strcmp(str2_password,password))//如果"学生登陆信息的数据表"已有我输入的账号，进入
			{
				turn=1;//输入的账号和密码是正确的
				break;
			}
		}//遍历整个"学生登陆信息的数据表"
		if(turn)
		{
			student_number=atoi(account);//记录这个学生的学号
			printf("登录成功！\n");
			fclose(fp);
			return 1;
		}
		else
		{
			printf("账号或密码错误，登录失败！\n");
			fclose(fp);
			return 0;
		}
	}
}
void PrintLogin()
{
	//打印登陆界面
	printf("\n");
	printf("────欢迎使用学生成绩管理系统───\n");
	printf("请选择身份登录或注册：\n");
	printf("1.教师注册\n");
	printf("2.教师登录\n");
	printf("3.学生注册\n");
	printf("4.学生登录\n");
	printf("0.退出系统\n");
	printf("───────────────────\n");
}
//以上为登陆函数部分
void PrintMenuStu()
{	//打印学生菜单
	printf("\n");
	printf("────欢迎使用学生成绩管理系统────\n");
	printf("\n");
	printf("请选择操作项目:\n");
	printf("     1.查询成绩\n");
	printf("     2.退出登录\n");
	printf("     0.退出系统\n");
	printf("────────────────────\n");
}
char GetKey()//获取一个字符
{
	char c,z;
	int flag = 1;
	while((c = getchar()) != '\n' || 1 == flag)
	{
		z = c;
		flag = 0;
	}
	return z;
}
int Get_a_student_information_and_printf(int stu_num)
{
	FILE *fp;//用来打开学生信息文件
	char Myaccount[16];//参数的字符串形式
	char account[16];//文件中的学号
	char Class[8];//文件中的班级
	char name[10];//文件中的姓名
	char score[5];//文件中的分数

	itoa(stu_num,Myaccount,10);//将整形数转化为字符串
	if((fp=fopen("studata_csv_Address","r"))==NULL)
	{
		printf("学生信息文件未打开成功，登录失败！\n");
		return 0;
	}
	else
	{
		while(!feof(fp))//feof 函数用于检测文件的末尾指示器（end-of-file indicator）是否被设置。
		{
			fscanf(fp,"%s%s%s%s",account,Class,name,score);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
			if(!strcmp(Myaccount,account))//如果"学生登陆信息的数据表"已有我输入的账号，进入
			{
				printf("学号：%s 姓名：%s\n",account,name);
				printf("班级：%s\t 分数：%s\n",Class,score);
				printf("查找成功！\n");
				printf("返回菜单");
				system("pause");
				fclose(fp);
				return 1;
				break;
			}
		}//遍历整个"学生登陆信息的数据表"
		printf("学生文件中没有你！\n去找教师添加你的信息吧！\n");
		fclose(fp);
		return 0;
	}
}
void store_stu_innfor(stu_infor* pHead)
{
	//保存学生信息
	FILE *fp;//用来打开学生信息文件
	if((fp=fopen("studata_csv_Address","w"))==NULL)
	{
		printf("学生信息文件未打开成功，登录失败！\n");
		return;
	}
	else
	{
		printf("开始保存数据");
		while(pHead!=NULL)
		{
			fprintf(fp,"%s %s %s %s\n",pHead->account,pHead->Class,pHead->name,pHead->score);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
			fflush(fp);//fflush()会强迫将缓冲区内的数据写回指定的文件中。
			pHead = pHead->pNext;
		}
		fclose(fp);
		printf("────────────────────\n");
		printf("\n保存成功！\n");
		return;
	}
}
void PrintMenuTea()
{//教师系统的菜单
	printf("────欢迎使用学生成绩管理系统────\n");
	printf("1.添加学生\n");
	printf("2.删除学生\n");
	printf("3.修改学生信息\n");
	printf("4.查看学生信息\n");
	printf("5.排序\n");
	printf("6.退出登录\n");
	printf("0.退出系统\n");
	printf("────────────────────\n");
}
void read_stu_infor(stu_infor** ppHead,stu_infor** ppEnd)
{
	FILE *fp;//用来打开学生信息文件
	char account[16];//文件中的学号
	char Class[8];//文件中的班级
	char name[10];//文件中的姓名
	char score[5];//文件中的分数
	if((fp=fopen("studata_csv_Address","r"))==NULL)
	{
		printf("学生信息文件未打开成功，登录失败！\n");
		return;
	}
	else
	{
		while(!feof(fp))//feof 函数用于检测文件的末尾指示器（end-of-file indicator）是否被设置。
		{
			stu_infor* pNode = (stu_infor*)malloc(sizeof(stu_infor));
			fscanf(fp,"%s %s %s %s\n",pNode->account,pNode->Class,pNode->name,pNode->score);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
			pNode->pNext=NULL;
			if(NULL == *ppHead)
			{
				*ppHead = pNode;
			}
			else
			{
				(*ppEnd)->pNext = pNode;
			}
			*ppEnd = pNode;
		}//遍历整个"教师登陆信息的数据表"
		fclose(fp);
		return;
	}
}
void Add_newstu(stu_infor** ppEnd)//添加学生
{
	stu_infor* pNode = (stu_infor*)malloc(sizeof(stu_infor));
	printf("----------开始添加学生信息----------\n");
	printf("请输入10位学号：");
	scanf("%s",pNode->account);
	printf("\n请输入班级：");
	scanf("%s",pNode->Class);
	printf("\n请输入姓名：");
	scanf("%s",pNode->name);
	printf("\n请输入分数：");
	scanf("%s",pNode->score);
	pNode->pNext=NULL;
	//获得一个学生节点的信息
	(*ppEnd)->pNext = pNode;
	*ppEnd=pNode;
	//将他存入链表中
	printf("学生录入成功！\n");
	return;
}
void Delete(stu_infor** ppHead,stu_infor** ppEnd)//删除学生
{
	char account[16];
	stu_infor* pDel;
	stu_infor* pMark = *ppHead;
	printf("----------开始删除学生信息----------\n");
	printf("请输入10位学号：");
	scanf("%s",account);
	printf("\n去删除学号为%s的这个同学中\n",account);

	if(!strcmp((*ppHead)->account,account))//删除头节点
	{
		pDel = *ppHead;
		*ppHead = (*ppHead)->pNext;
		free(pDel);
		return;
	}
	while(pMark->pNext != NULL)
	{
		if(!strcmp(pMark->pNext->account,account))
		{
			pDel = pMark->pNext;
			pMark->pNext = pMark->pNext->pNext;
			free(pDel);
			if(pMark->pNext == NULL)
			{
				*ppEnd = pMark;
			}
			printf("删除完成！\n");
			system("pause");
			return;
		}
		pMark = pMark->pNext;
	}
	printf("没有这个学生\n");
	system("pause");
	return;
}
void new_Look_infor(stu_infor* pHead)
{
	char option;//记录选项
	int i=0;//记录个数
	char account[16];//学号
	char Class[8];//班级
	char name[10];//姓名
	char score[5];//分数

	printf("────────────────────\n");
	printf("你想要通过哪些信息去查找！支持前缀模糊查询！\n");
	printf("1.学号\n");
	printf("2.班级\n");
	printf("3.姓名\n");
	printf("*按其他键返回菜单*\n");
	printf("────────────────────\n");
	printf("你的选择是：\n");
	option = GetKey();
	switch(option)
	{
	case '1':
		printf("请输入学号：");
		scanf("%s",account);
		break;
	case '2':
		printf("请输入班级：");
		scanf("%s",Class);
		break;
	case '3':
		printf("请输入姓名：");
		scanf("%s",name);
		break;
	default:
		system("cls");
		printf("已返回菜单\n");
		return;
		break;
	}
	printf("以下是可能的学生\n");
	while(pHead!=NULL)
	{
		if((!strcmp(account,pHead->account))||(!strcmp(Class,pHead->Class))||(!strcmp(name,pHead->name)))
		{
			printf("\n──────────────────────────\n");
			printf("学号：%s 姓名：%s\n",pHead->account,pHead->name);
			printf("班级：%s\t 分数：%s\n",pHead->Class,pHead->score);
			printf("───────────────────────────\n");
			i++;
		}
		pHead=pHead->pNext;
	}
	printf("以上数据共有%d个",i);
	system("pause");
	return;
}
void rec_infor(stu_infor* pHead)
{
	//修改信息
	char account[16];
	char option;//记录选项
	printf("你想修改谁的信息\n");
	printf("请输入他的学号：");
	scanf("%s",account);

	printf("你想修改哪项信息？\n");
	printf("1.班级\n");
	printf("2.姓名\n");
	printf("3.学分\n");
	printf("*按其他键按返回主菜单*\n");
	printf("----------\n");
	option = GetKey();
	while(pHead!=NULL)
	{
		if(!strcmp(pHead->account,account))
		{
			switch(option)
			{
			case '1':
				printf("%s修改前的班级为%s",pHead->name,pHead->Class);
				printf("\n请输入班级：");
				scanf("%s",pHead->Class);
				break;
			case '2':
				printf("%s修改前的姓名为%s",pHead->name,pHead->name);
				printf("\n请输入姓名：");
				scanf("%s",pHead->name);
				break;
			case '3':
				printf("%s修改前的分数为%s",pHead->name,pHead->score);
				printf("\n请输入分数：");
				scanf("%s",pHead->score);
				break;
			default:
				printf("*已返回主菜单*");
				return;
				break;
			}
			printf("\n%s修改后的结果为\n",pHead->account);
			printf("姓名：%s\t班级：%s\n分数：%s\n",pHead->name,pHead->Class,pHead->score);
			system("pause");
			return ;
		}
		pHead=pHead->pNext;
	}
	printf("没有这个同学！\n");
	system("pause");
	return;
}

void rank_1(stu_infor** pnewHead)
{
	stu_infor* endpt;//控制循环比较
	stu_infor* p;//临时指针变量
	stu_infor *p1,*p2;
	p1 = (stu_infor*)malloc(sizeof(stu_infor));
	p1->pNext = *pnewHead; //注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址
	*pnewHead = p1;//让pHead指向p1节点，排序完成后，我们再把p1节点释放掉
	for(endpt = NULL;endpt != *pnewHead; endpt = p)
	{
		for(p = p1 = *pnewHead;p1->pNext->pNext != endpt; p1 = p1->pNext)
		{
			if(atoi(p1->pNext->score) < atoi(p1->pNext->pNext->score))//atoi()：将字符串转换为整型值。
			{
				p2 = p1->pNext->pNext;
				p1->pNext->pNext = p2->pNext;
				p2->pNext = p1->pNext;
				p1->pNext = p2;
				p = p1->pNext->pNext;
			}
		}
	}
	p1 = *pnewHead;//把p1的信息去掉
	*pnewHead = (*pnewHead)->pNext;
	free(p1);
	p1 = NULL;
}
void save_rank(stu_infor* pHead)
{
	//保存排序信息
	FILE *fp;//用来打开学生信息文件
	char* file_Address;
	printf("请输入文件保存地址：\n");
	file_Address = GetString();
	if((fp=fopen(file_Address,"w"))==NULL)
	{
		printf("文件未打开成功，失败！\n");
		printf("将返回至主菜单\n");
		return;
	}
	else
	{
		printf("开始保存数据");
		while(pHead!=NULL)
		{
			fprintf(fp,"%s,%s,%s,%s\n",pHead->account,pHead->Class,pHead->name,pHead->score);//这将读取连续字符，直到遇到一个空格字符（空格字符可以是空白、换行和制表符）
			fflush(fp);//fflush()会强迫将缓冲区内的数据写回指定的文件中。
			pHead = pHead->pNext;
		}
		fclose(fp);
		printf("────────────────────\n");
		printf("\n保存成功！\n");
		return;
	}
}
void rank_class(stu_infor* pHead,char Myclass[8])
{
	stu_infor* pnewHead = NULL;
	stu_infor* pnewEnd = NULL;
	char option;//记录选项
	int i = 0;//班级学生数
	while(pHead!= NULL)//将班级符合的学生添加到新链表中
	{
		if(!strcmp(pHead->Class,Myclass))
		{
			stu_infor* pNode = (stu_infor*)malloc(sizeof(stu_infor));
			strcpy(pNode->account,pHead->account);
			strcpy(pNode->Class,pHead->Class);
			strcpy(pNode->name,pHead->name);
			strcpy(pNode->score,pHead->score);
			pNode->pNext=NULL;
			i++;
			if(pnewHead == NULL)
			{
				pnewHead = pNode;
			}
			else
			{
				pnewEnd->pNext=pNode;
			}
			pnewEnd = pNode;
		}
		pHead=pHead->pNext;
	}//遍历旧链表
	
	rank_1(&pnewHead);//排序

	printf("──姓名─────学分────────\n");
	while(pnewHead != NULL)
	{
		printf("%s    %s\n",pnewHead->name,pnewHead->score);
		pnewHead = pnewHead->pNext;
	}
	printf("────────────────────\n");
	system("pause");
	printf("是否需要单独保存\n");
	printf("1.需要\n");
	printf("其他按键不需要\n");
	printf("────────────────────\n");
	option = GetKey();
	if(option == '1')
	{
		save_rank(pnewHead);
	}
	else
	{
		printf("将返回至主菜单\n");
		system("pause");
	}
}

void rank_any(stu_infor* pHead)
{
	char option;//记录选项
	rank_1(&pHead);//排序
	printf("────────────────────\n");
	printf("1.打印到屏幕\n");
	printf("2.单独保存\n");
	printf("*按其他键返回主菜单*\n");
	printf("────────────────────\n");
	option = GetKey();
	switch(option)
	{
	case '1':
		printf("────────────────────\n");
		printf("────全体学生学分排序──────\n");
		while(pHead != NULL)
		{
			printf("%s\t%s\t%s\t%s\n",pHead->account,pHead->name,pHead->score);
			pHead= pHead->pNext;
		}
		printf("*打印完成*\n");
		printf("────────────────────\n");
		break;
	case '2':
		save_rank(pHead);
		break;
	default:
		return;
		break;
	}
}
void rank(stu_infor* pHead)
{//排序
	char option;//记录选项
	int turn = 0;//判断有没有这个班级的开关
	char Myclass[8];
	if(pHead==NULL)
	{
		printf("没人同学\n");
		printf("将返回主菜单\n");
		system("pause");
		return;
	}
	if(pHead->pNext == NULL)
	{
		printf("只有1名同学\n");
		printf("将返回主菜单\n");
		system("pause");
		return;
	}
	printf("────────────\n");
	printf("本功能可以按分数由高到低排序，可分班级，可以将排好的学生单独导出\n");
	printf("1.所有人排序\n");
	printf("2.按班级排序\n");
	printf("*按其他键返回主菜单*\n");
	printf("────────────\n");
	option = GetKey();
	if(option == '2')//按班级排序
	{
		printf("请输入班级\n");
		scanf("%s",Myclass);
		while(pHead!=NULL)
		{
			if(!strcmp(Myclass,pHead->Class))
			{
				turn = 1;
				break;
			}
			pHead=pHead->pNext;
		}
		if(turn = 0)
		{
			printf("没有这个班级的同学\n");
			printf("将返回主菜单\n");
			system("pause");
			return;
		}
	}
	switch(option)
	{
	case '1'://1.所有人排序
		rank_any(pHead);
		break;
	case '2'://2.按班级排序
		rank_class(pHead,Myclass);
		break;
	default:
		system("cls");
		printf("已返回主菜单\n");
		return;
		break;
	}
	return;
}
int main()
{

	int i=1;//用于跳出while
	char option;//记录选项
	int turn=0;//检验是否登录或注册成功的开关
	int admin=0;//检验用户是以教师或学生身份登录的开关

	stu_infor* pHead = NULL;
	stu_infor* pEnd = NULL;

	while(1)
	{
		if(admin==0)
		{
			i=1;
			while(1)//登陆
			{
				PrintLogin();
				option = GetKey();
				switch(option)
				{
				case '1':
					printf("----------1.教师注册----------\n");
					turn = RegisterTea();
					admin = 1;
					break;
				case '2':
					printf("----------2.教师登录----------\n");
					turn = LoginTea();
					admin = 1;
					break;
				case '3':
					printf("----------3.学生注册----------\n");
					turn = RegisterStu();
					admin = 2;
					break;
				case '4':
					printf("----------4.学生登录----------\n");
					turn = LoginStu();
					admin = 2;
					break;
				case '0':
					printf("----------0.退出系统----------\n");
					return 0;
					break;
				default:
					printf("按错了！");
					break;
				}
				if(turn == 1)//成功登陆或注册
				{
					printf("------按任意键进入操作菜单------\n");
					system("pause");
					system("cls");
					break;
				}
				else//未成功登陆或注册
				{
					printf("接下来你希望：");
					printf("1.返回登录菜单   2.退出管理系统");
					option = GetKey();
					if(option == '1')
					{
						system("cls");
						printf("已返回登录菜单");
					}
					else
					{
						printf("欢迎您再次使用！");
						return 0;
					}
				}
			}
		}
		else if(admin==1)//教师的系统
		{
			i=1;
			read_stu_infor(&pHead,&pEnd);
			while(i<100)
			{
				PrintMenuTea();
				printf("你的选择是：\n");
				option = GetKey();
				switch(option)
				{
				case '1':
					Add_newstu(&pEnd);
					break;
				case '2':
					Delete(&pHead,&pEnd);
					break;
				case '3':
					rec_infor(pHead);
					break;
				case '4':
					new_Look_infor(pHead);
					break;
				case '5':
					rank(pHead);
					break;
				case '6':
					admin=0;//身份状态记为未登录
					printf("按任意键返回登录菜单\n");
					i=100;
					system("pause");
					system("cls");
					store_stu_innfor(pHead);
					break;
				case '0':
					printf("----------0.退出系统----------\n");
					store_stu_innfor(pHead);
					return 0;
					break;
				default:
					printf("按错了！\n");
					break;
				}
			}
		}
		else if(admin==2)//学生的系统
		{
			printf("学生的系统");
			while(i<100)
			{
				PrintMenuStu();
				option = GetKey();
				switch(option)
				{
				case '1':
					Get_a_student_information_and_printf(student_number);
					break;
				case '2':
					admin=0;//身份状态记为未登录
					printf("按任意键返回登录菜单\n");
					system("pause");
					i=100;
					system("cls");
					break;
				case '0':
					printf("----------0.退出系统----------\n");
					return 0;
					break;
				default:
					printf("按错了！");
					break;
				}
			}
		}
	}
	return 0;
}
