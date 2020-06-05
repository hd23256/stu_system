#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//admindata//登陆信息文件的地址，你要自己更改

int Register()//注册  1为注册成功  0为注册失败
{
	char account[16],password[16];//输入的账号，密码
	FILE *fp;
	int turn = 1;//用于检测账号是否已注册的开关
	char password_che[16];//用于检测两次输入的密码是否一致
	char str1_account[16]={0},str2_password[16]={0};//文件中的，检验账号，检验密码
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

	if((fp=fopen("admindata","a+"))==NULL)//检验"登陆信息的数据表"是否成功打开
	{
		printf("注册失败！\n");//多半是admindata地址不存在
		return 0;
	}
	else
	{
		while(!feof(fp))//遍历整个"登陆信息文件"
		{
			fscanf(fp,"%s%s",str1_account,str2_password);
			if(!strcmp(str1_account,account))
			{
				turn=0;//账号已注册
				break;
			}
		}
		if(turn)
		{		
			fprintf(fp,"%s %s\n",account,password);
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
	

int Login()//登录  1为登录成功  0为登录失败
{
	char account[16],password[16];//账号，密码
	char str1_account[16]={0},str2_password[16]={0};//检验账号，检验密码
	int turn=0;//用于检验账号密码是否匹配
	FILE *fp;
	printf("请输入您的工号：");
	scanf("%s",account);
	printf("请输入密码：");
	scanf("%s",password);
	if((fp=fopen("admindata","r"))==NULL)//检验"登陆信息文件"是否成功打开
	{
		printf("登录失败！\n");//多半是"登陆信息文件"地址不存在
		return 0;
	}
	else
	{
		while(!feof(fp))//遍历整个"登陆信息文件"
		{
			fscanf(fp,"%s%s",str1_account,str2_password);
			if(!strcmp(str1_account,account)&&!strcmp(str2_password,password))
			{
				turn=1;//输入的账号和密码是正确的
				break;
			}
		}
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


int main()
{
	int option;//记录选项
	int i = 0;//检测是否注册或登陆成功
	while(i == 0)
	{
		printf("────欢迎使用学生成绩管理系统───\n");
		printf("1.注册\n");
		printf("2.登录\n");
		printf("0.退出\n");
		printf("───────────────────\n");
		scanf("%d",&option);

		switch(option)
		{
		case 1:
			i = Register();
			break;
		case 2:
			i = Login();
			break;
		case 0:
			return 0;
			break;
		default:
			printf("按错了！\n");
			break;
		}
	}
	printf("登陆成功！\n");


	system("pause");
	return 0;
}