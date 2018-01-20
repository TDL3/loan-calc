//This file was created by TDL3(Jack Simpkins) on Jan 20th 2018
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>

void ldatres();      //���������Ϣ
void reset();        //���������Ϣ
void menu();         //�˵�
void inputdata();    //¼�������Ϣ
void type1();        //�ȶ��
void type2();        //�ȶϢ
int  passinit();     //�����ʼ��
void login();        //��½
void passchange();   //��������


struct password
{
	char pasc[12];
	char temp[12];
}pass;

struct loandata
{
	char  id[20];
	char  name[8];
	char  company[20];
	float loan;
	float time;
	float rate;
	char  op[12];
	int   flag;
}dat;


int main()
{
	int i;
	if (passinit()) login();
	system("cls");
	puts("--------��½�ɹ���-------\n");
	menu();
	scanf("%d", &i);
	while (i)
	{
		if (i == 1)
		{
			system("cls");
			type1();
			system("cls");
		}
		else if (i == 2)
		{
			system("cls");
			type2();
			system("cls");
		}
		else if (i == 3)
		{
			system("cls");
			passchange();
			system("cls");
		}
		else if (i == 4)
		{
			puts("��л���ʹ�ã�\n�������BUG�����н��黶ӭ��֪���ϣ�\nEmail:jacksimpkins7@gmail.com");
			getch();
			exit(1);
		}
		menu();
		scanf("%d", &i);
	}
	return 1;
}

void type1()
{
	int i;
	double s, r, x, a, b, c, m, n = 0;
	inputdata();
	m = dat.time * 12;
	s = dat.loan;
	r = dat.rate / 100 / 12;
	a = s / m;
	for (i = 1; i <= m; i++)
	{
		x = a + s * r;
		s = s - a;
		n = n + x;
	}
	s = dat.loan;
	printf("���֤�� ����\t��λ\t����\t����\t����\t��ʽ\t�ܶ�\t�Ŵ�Ա\n");
	printf("%s %s\t%s\t%.0f\t%.2f\t%.2f\t��Ϣ\t%.2f\t%s\n", dat.id, dat.name, dat.company, dat.loan, dat.time, dat.rate, n, dat.op);
	printf("\n----------------------------------------------------------------------------------\n");
	printf("����\t������Ϣ\t������Ϣ\t��������\tʣ�౾��\tʣ�໹��\n");
	for (i = 1; i <= m; i++)
	{
		printf("%d\t", i);
		b = s * r;
		x = a + b;
		s = s - a;
		printf("%.2f\t     ", x);
		printf("%.2f \t    ", b);
		printf("%.2f \t    ", a);
		printf("%.2f\t     ", s);
		printf("%.2f\n", n = n - x);
	}
	system("pause");
}

void type2()
{
	int i;
	double s, r, x, a, b, c, m, n;
	inputdata();
	m = dat.time * 12;
	r = dat.rate / 100 / 12;
	for (i = 1, a = 1 + r, b = a; i <= m; i++) b = a * b;
	s = dat.loan;
	x = s * r*b / (b - 1);
	n = x * m;
	printf("���֤�� ����\t��λ\t����\t����\t����\t��ʽ\t�ܶ�\t�Ŵ�Ա\n");
	printf("%s %s\t%s\t%.0f\t%.2f\t%.2f\t��Ϣ\t%.2f\t%s\n", dat.id, dat.name, dat.company, dat.loan, dat.time, dat.rate, n, dat.op);
	printf("\n----------------------------------------------------------------------------------\n");
	printf("����\t������Ϣ\t������Ϣ\t��������\tʣ�౾��\tʣ�໹��\n");
	for (i = 1; i <= m; i++)
	{
		printf("%d \t", i);
		printf("%.2f \t", x);
		printf("%.2f \t", s*r);
		printf("%.2f \t", c=x - s * r);
		printf("%.2f \t", s = s - c);
		printf("%.2f \t\n", n = n - x);
	}
	system("pause");
}

void ldatres()
{
	memset(dat.id, 0, sizeof(dat.id));

	memset(dat.name, 0, sizeof(dat.name));
	memset(dat.company, 0, sizeof(dat.company));
}

void reset()
{
	memset(pass.pasc, 0, sizeof(pass.pasc));
	memset(pass.temp, 0, sizeof(pass.temp));
}

void menu()
{
	printf("----------Yeah!----------\n\n\t1. �ȶ��\n\t2. �ȶϢ\n\t3. �޸�����\n\t4. �˳�\n\n----------Yeah!----------\n");
}

void inputdata()
{
	char c;
	if (dat.flag)
	{
		printf("��⵽�Ѵ������ݣ�Ҫ����ʹ����(Y/N)\n");
		fflush(stdin);
		c = getchar();
		if (c != 'y' && c != 'Y')
		{
			ldatres();
			dat.flag = 0;
			system("cls");
			inputdata();
		}
	}
	else
	{
	    system("cls");
		printf("----------����¼��----------\n���������֤��:");
		scanf("%s", dat.id);
		printf("����������:");
		scanf("%s", dat.name);
		printf("�����빫˾��:");
		scanf("%s", dat.company);
		printf("���������Ա��:");
		scanf("%s", dat.op);
		printf("������������:");
		scanf("%f", &dat.loan);
		printf("���������ʱ�ޣ��꣩:");
		scanf("%f", &dat.time);
		printf("����������:");
		scanf("%f", &dat.rate);
		dat.flag = 1;
		system("cls");
		printf("--------����¼�����--------\n");
	}

}

int passinit()
{
	int i; char c;
	FILE *in;
	if ((in = fopen("pasc.pass", "r")) == NULL)
	{
		in = fopen("pasc.pass", "w+");
		printf("���������ǵ�һ�ε�½��������6-12λ����:\n");
	sec: scanf("%s", pass.pasc);
		printf("���ٴ���������:\n");
		scanf("%s", pass.temp);
		if (0 == strcmp(pass.pasc, pass.temp))
		{
			fputs(pass.pasc, in);
			printf("�������óɹ� �Ѧء�\n");
			fclose(in);
			return 0;
		}
		else
		{
			printf("������������벻ƥ�䣬Ҫ����������(Y/N)\n");
			fflush(stdin);
			c = getchar();
			if (c == 'Y' || c == 'y')
			{
				reset();
				printf("����������:\n");
				goto sec;
			}
			else
			{
				fclose(in);
				remove("pasc.pass");
				exit(0);
			}
		}
	}
	return 1;
}

void login()
{
	int i = 0, j = 3, k;
	FILE *out;
	if ((out = (fopen("pasc.pass", "r"))) == NULL)
	{
		printf("ѽ����������ˣ����������Կ�\n");
		exit(-1);
	}
	while (fscanf(out, "%c", &pass.pasc[i++]) != EOF);
	fclose(out);
	while (1)
	{
		if (j-- == 3) printf("����������������:\n");
		else
		{
			printf("������������������Գ���%d��:\n", j + 1);
			memset(pass.temp, 0, sizeof(pass.temp));
		}
		gets(pass.temp);
		if (0 == (strcmp(pass.pasc, pass.temp))) break;
		else if (j == 0)
		{
			printf("��Ǹ��ʧ�ܴ������࣬�ܾ�����");
			exit(-1);
		}
	}
}

void passchange()
{
	int i = 0, flag = 0; char c, v;
	FILE *out, *in;
	reset();
	if ((out = fopen("pasc.pass", "r")) == NULL)
	{
		puts("Ŷ������������ˣ������������԰�");
		exit(-1);
	}
	out = fopen("pasc.pass", "r");
	while (fscanf(out, "%c", &pass.pasc[i++]) != EOF);
	fclose(out);
	while (1)
	{
		puts("������ԭ����:");
		scanf("%s", pass.temp);
		if (0 == (strcmp(pass.pasc, pass.temp)))
		{
			while (1)
			{
				reset();
				printf("������������:");
				scanf("%s", pass.pasc);
				printf("���ٴ�����������:");
				scanf("%s", pass.temp);
				if (0 == (strcmp(pass.pasc, pass.temp)))
				{
					remove("pasc.pass");
					in = fopen("pasc.pass", "w+");
					fputs(pass.pasc, in);
					fclose(in);
					puts("�����޸ĳɹ���=^_^=");
					flag = 1;
					break;
				}
				else
				{
					fflush(stdin);
					printf("�������벻һ����Ҫ������(Y/N)\n");
					v = getchar();
					if (v != 'y' && v != 'Y');
					{
						flag = 1;
						break;
					}
				}
			}
		}
		else
		{
			printf("ԭ�����������Ҫ������(Y/N)\n");
			fflush(stdin);
			c = getchar();
			if (c == 'y' || c == 'Y') memset(pass.temp, 0, sizeof(pass.temp));
			else
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
}

