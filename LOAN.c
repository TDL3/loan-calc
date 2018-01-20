//This file was created by TDL3(Jack Simpkins) on Jan 20th 2018
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>

void ldatres();      //清空名款信息
void reset();        //清空密码信息
void menu();         //菜单
void inputdata();    //录入贷款信息
void type1();        //等额本金
void type2();        //等额本息
int  passinit();     //密码初始化
void login();        //登陆
void passchange();   //更改密码


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
	puts("--------登陆成功！-------\n");
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
			puts("感谢你的使用！\n如果遇到BUG或者有建议欢迎告知我呦！\nEmail:jacksimpkins7@gmail.com");
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
	printf("身份证号 姓名\t单位\t贷款\t期限\t利率\t方式\t总额\t信贷员\n");
	printf("%s %s\t%s\t%.0f\t%.2f\t%.2f\t本息\t%.2f\t%s\n", dat.id, dat.name, dat.company, dat.loan, dat.time, dat.rate, n, dat.op);
	printf("\n----------------------------------------------------------------------------------\n");
	printf("次数\t偿还本息\t偿还利息\t偿还本金\t剩余本金\t剩余还款\n");
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
	printf("身份证号 姓名\t单位\t贷款\t期限\t利率\t方式\t总额\t信贷员\n");
	printf("%s %s\t%s\t%.0f\t%.2f\t%.2f\t本息\t%.2f\t%s\n", dat.id, dat.name, dat.company, dat.loan, dat.time, dat.rate, n, dat.op);
	printf("\n----------------------------------------------------------------------------------\n");
	printf("次数\t偿还本息\t偿还利息\t偿还本金\t剩余本金\t剩余还款\n");
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
	printf("----------Yeah!----------\n\n\t1. 等额本金\n\t2. 等额本息\n\t3. 修改密码\n\t4. 退出\n\n----------Yeah!----------\n");
}

void inputdata()
{
	char c;
	if (dat.flag)
	{
		printf("检测到已存在数据，要继续使用吗？(Y/N)\n");
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
		printf("----------数据录入----------\n请输入身份证号:");
		scanf("%s", dat.id);
		printf("请输入姓名:");
		scanf("%s", dat.name);
		printf("请输入公司名:");
		scanf("%s", dat.company);
		printf("请输入操作员名:");
		scanf("%s", dat.op);
		printf("请输入贷款额数:");
		scanf("%f", &dat.loan);
		printf("请输入贷款时限（年）:");
		scanf("%f", &dat.time);
		printf("请输入利率:");
		scanf("%f", &dat.rate);
		dat.flag = 1;
		system("cls");
		printf("--------数据录入完成--------\n");
	}

}

int passinit()
{
	int i; char c;
	FILE *in;
	if ((in = fopen("pasc.pass", "r")) == NULL)
	{
		in = fopen("pasc.pass", "w+");
		printf("看起来你是第一次登陆，请输入6-12位密码:\n");
	sec: scanf("%s", pass.pasc);
		printf("请再次输入密码:\n");
		scanf("%s", pass.temp);
		if (0 == strcmp(pass.pasc, pass.temp))
		{
			fputs(pass.pasc, in);
			printf("密码设置成功 ⊙ω⊙\n");
			fclose(in);
			return 0;
		}
		else
		{
			printf("两次输入的密码不匹配，要从新设置吗？(Y/N)\n");
			fflush(stdin);
			c = getchar();
			if (c == 'Y' || c == 'y')
			{
				reset();
				printf("请输入密码:\n");
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
		printf("呀！程序出错了，请重启试试看\n");
		exit(-1);
	}
	while (fscanf(out, "%c", &pass.pasc[i++]) != EOF);
	fclose(out);
	while (1)
	{
		if (j-- == 3) printf("请输入密码来登入:\n");
		else
		{
			printf("密码输入错误，您还可以尝试%d次:\n", j + 1);
			memset(pass.temp, 0, sizeof(pass.temp));
		}
		gets(pass.temp);
		if (0 == (strcmp(pass.pasc, pass.temp))) break;
		else if (j == 0)
		{
			printf("抱歉，失败次数过多，拒绝访问");
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
		puts("哦不，程序出错了！重启程序试试吧");
		exit(-1);
	}
	out = fopen("pasc.pass", "r");
	while (fscanf(out, "%c", &pass.pasc[i++]) != EOF);
	fclose(out);
	while (1)
	{
		puts("请输入原密码:");
		scanf("%s", pass.temp);
		if (0 == (strcmp(pass.pasc, pass.temp)))
		{
			while (1)
			{
				reset();
				printf("请输入新密码:");
				scanf("%s", pass.pasc);
				printf("请再次输入新密码:");
				scanf("%s", pass.temp);
				if (0 == (strcmp(pass.pasc, pass.temp)))
				{
					remove("pasc.pass");
					in = fopen("pasc.pass", "w+");
					fputs(pass.pasc, in);
					fclose(in);
					puts("密码修改成功！=^_^=");
					flag = 1;
					break;
				}
				else
				{
					fflush(stdin);
					printf("两次密码不一样，要重试吗？(Y/N)\n");
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
			printf("原密码输入错误，要重试吗？(Y/N)\n");
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

