#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//admindata//��½��Ϣ�ļ��ĵ�ַ����Ҫ�Լ�����

int Register()//ע��  1Ϊע��ɹ�  0Ϊע��ʧ��
{
	char account[16],password[16];//������˺ţ�����
	FILE *fp;
	int turn = 1;//���ڼ���˺��Ƿ���ע��Ŀ���
	char password_che[16];//���ڼ����������������Ƿ�һ��
	char str1_account[16]={0},str2_password[16]={0};//�ļ��еģ������˺ţ���������
	printf("���������Ĺ��ţ�");
	scanf("%s",account);
	do{
		printf("���������룺");
		scanf("%s",password);
		printf("���ٴ��������룺");
		scanf("%s",password_che);
		if(strcmp(password,password_che))
			printf("���벻һ�£����������룡\n\n");
	}while(strcmp(password,password_che));

	if((fp=fopen("admindata","a+"))==NULL)//����"��½��Ϣ�����ݱ�"�Ƿ�ɹ���
	{
		printf("ע��ʧ�ܣ�\n");//�����admindata��ַ������
		return 0;
	}
	else
	{
		while(!feof(fp))//��������"��½��Ϣ�ļ�"
		{
			fscanf(fp,"%s%s",str1_account,str2_password);
			if(!strcmp(str1_account,account))
			{
				turn=0;//�˺���ע��
				break;
			}
		}
		if(turn)
		{		
			fprintf(fp,"%s %s\n",account,password);
			printf("ע��ɹ���\n");
			fclose(fp);//�ر��ļ�
			return 1;
		}
		else
		{
			printf("�˺���ע�ᣡ\n");
			fclose(fp);//�ر��ļ�
			return 0;
		}
	}
}
	

int Login()//��¼  1Ϊ��¼�ɹ�  0Ϊ��¼ʧ��
{
	char account[16],password[16];//�˺ţ�����
	char str1_account[16]={0},str2_password[16]={0};//�����˺ţ���������
	int turn=0;//���ڼ����˺������Ƿ�ƥ��
	FILE *fp;
	printf("���������Ĺ��ţ�");
	scanf("%s",account);
	printf("���������룺");
	scanf("%s",password);
	if((fp=fopen("admindata","r"))==NULL)//����"��½��Ϣ�ļ�"�Ƿ�ɹ���
	{
		printf("��¼ʧ�ܣ�\n");//�����"��½��Ϣ�ļ�"��ַ������
		return 0;
	}
	else
	{
		while(!feof(fp))//��������"��½��Ϣ�ļ�"
		{
			fscanf(fp,"%s%s",str1_account,str2_password);
			if(!strcmp(str1_account,account)&&!strcmp(str2_password,password))
			{
				turn=1;//������˺ź���������ȷ��
				break;
			}
		}
		if(turn)
		{
			printf("��¼�ɹ���\n");
			fclose(fp);
			return 1;
		}
		else
		{
			printf("�˺Ż�������󣬵�¼ʧ�ܣ�\n");
			fclose(fp);
			return 0;
		}
	}
}


int main()
{
	int option;//��¼ѡ��
	int i = 0;//����Ƿ�ע����½�ɹ�
	while(i == 0)
	{
		printf("����������ӭʹ��ѧ���ɼ�����ϵͳ������\n");
		printf("1.ע��\n");
		printf("2.��¼\n");
		printf("0.�˳�\n");
		printf("��������������������������������������\n");
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
			printf("�����ˣ�\n");
			break;
		}
	}
	printf("��½�ɹ���\n");


	system("pause");
	return 0;
}