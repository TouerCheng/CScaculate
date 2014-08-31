#include "ls.h"
//检查用户名下标sdaasd
/*int find_name(const char *name)
{
	int i;

	if (name == NULL)
	{
		printf("NULL NAME");
		return -2;
	}
	for(i=0;users[i].username[0] != ' ';i++)
	{
		if(strcmp(users[i].username,name)==0)
			return i;
	}
	return i;
}*/

void* send_data(void *client_fd)
{
	char send_msg[200];

	while (1) 
	{
		//printf("请输入要发送的信息：");
		fgets(send_msg,sizeof(send_msg),stdin);

		if (send_msg[strlen(send_msg) - 1] == '\n') 
		{
			send_msg[strlen(send_msg) - 1] = '\0';
		}

		if (send(*(int *)client_fd,send_msg,sizeof(send_msg),0) == -1) 
		{
			perror("发送消息出错");
			exit(1);
		}
	}
}

void my_err(const char *err_string,int line)
{
printf("line is %d",line);
perror(err_string);
exit(1);
}

void my_sleep()
{
	 int i = 1;
        while(i++<7)
        {
                printf(".");
                fflush(stdout);
              usleep(300000);
        }
        sleep(1);
	printf("\n");		

}
void *sleepthid(void *b)
{
//printf("%d",(*(int*)(b)));
while((*(int*)(b))==0)
{
	   int i = 1;
        while(i++<7)
        {
                printf(".");
                fflush(stdout);
              usleep(300000);
        }
        usleep(100000);
	printf("\b\b\b\b\b\b      \b\b\b\b\b\b");
}
}


num *mynum(char *q)
{	
	int n=(int)strlen(q);
	int i,j;
	int dian=-1;
	num *p=(num *)calloc(1,sizeof(num));

	for(i=0;i<=n;i++)
		p->s[i]=q[i];
	
	if(p->s[0]=='-')
	{
		for(i=1;i<=n;i++)
		{
			q[i-1]=q[i];	
		}
		p->T=-1;
		n--;
	}
	else
		p->T=1;
	for(i=0;i<n;i++)
	{
		if(q[i]=='.')
			dian=i;
	}
	if(dian==-1)
	{
		for(i=n-1,j=0;i>=0;i--,j++)
		{
			p->zheng[59-j]=q[i]-'0';
		}
		p->zhlen=n;
		p->xlen=0;
	}
	else
	{
		for(i=dian-1,j=0;i>=0;i--,j++)
		{
			p->zheng[59-j]=q[i]-'0';
		}
		for(j=0,i=dian+1;i<n;i++,j++)
		{
			p->xshu[j]=q[i]-'0';
		}
		p->zhlen=dian;
		p->xlen=n-dian-1;
	}
	return p;
		
}

void push(zhan *p,char *e)
{
	int i,c=(int)strlen(e);
	if(p->top==29)
	{
		printf("进栈时栈满\n");
		exit(1);
	}
	p->top++;

	for(i=0;i<=c;i++)
		p->data[p->top][i]=e[i];

	return;
	
}
void pop(zhan *p,char *e)
{
	int i,c=strlen(p->data[p->top]);
	if(p->top==-1)
	{
		printf("出栈时栈空\n");
		exit(1);
	}
	
	for(i=0;i<=c;i++)
		e[i]=p->data[p->top][i];
	p->top--;
	return;
	
}
void pushint(zhanint *s,char e)
{
	if(s->top == 99)
	{
		printf("转后缀时候栈满\n");
	 	exit(1);
	}
	s->top++;
	s->a[s->top]=e;
}
void popint(zhanint *s,char *e)
{
	if(s->top ==-1)
	{	
		printf("转中缀时候栈空\n");
		exit(1);
	}
	*e=s->a[s->top];
	s->top--;
}
void yuchuli(char *e)
{
	int i,j,k;
	int c = (int)strlen(e);
	int zuo1=0,zuo2=0,you1=0,you2=0;
	
	//括号匹配验证
	for(i=0;i<c;i++)
	{
		if(e[i]=='(') zuo1++;
		if(e[i]==')') you1++;
		if(e[i]=='[') zuo2++;
		if(e[i]==']') you2++;
	}
	if(zuo1!=you1) { printf("()不匹配\n"); exit(1); }
	if(zuo2!=you2) { printf("[]不匹配\n"); exit(1);	}
	
	//++ -- +- -+的转换
	
	for(j=0;j<c;j++)
	for(i=0;i<(int)strlen(e)-1;i++)
	{
		if(e[i]=='+'&&e[i+1]=='+')
		{
			for(k=i;k<(int)strlen(e);k++)
			{
				e[k]=e[k+1];
			}
			break;
		}
		if(e[i]=='+'&&e[i+1]=='-')
                {
                        for(k=i;k<(int)strlen(e);k++)
                        {
                                e[k]=e[k+1];
                        }
                        break;
                }
		if(e[i]=='-'&&e[i+1]=='+')
                {
			e[i+1]='-';
                        for(k=i;k<(int)strlen(e);k++)
                        {
                                e[k]=e[k+1];
                        }
                        break;
                }
		 if(e[i]=='-'&&e[i+1]=='-')
                {
                        e[i+1]='+';
                        for(k=i;k<(int)strlen(e);k++)
                        {
                                e[k]=e[k+1];
                        }
                        break;
                }

	}

	if(e[0]=='-')
	{
		for(k=(int)strlen(e);k>=0;k--)
			e[k+1]=e[k];
		e[0]='0';
	}

	//(-的解决
	for(j=0;j<c;j++)
        for(i=0;i<(int)strlen(e)-1;i++)
	{
		if(e[i]=='('&&e[i+1]=='-')
		{
			for(k=(int)strlen(e);k>=i+1;k--)
			e[k+1]=e[k];
			
			e[i+1]='0';
			break;			
		}
	}
	
	//函数的转换
		

}

void hou(char a[],char b[])
{
	int i=0;
	int j=0;
	char tmp;
	zhanint c;
	(c.top)=-1;
	while(a[i]!='\0')
	{
		//sin(
		if(a[i]=='s'&&a[i+1]=='i'&&a[i+2]=='n')
		{
			pushint(&c,65);
			i=i+4;
		}
		//cos(
                else if(a[i]=='c'&&a[i+1]=='o'&&a[i+2]=='s')
                {
                        pushint(&c,66);
                        i=i+4;
                }
		 //tan(
                else if(a[i]=='t'&&a[i+1]=='a'&&a[i+2]=='n')
                {
                        pushint(&c,67);
                        i=i+4;
                }
		//log(
                else if(a[i]=='l'&&a[i+1]=='o'&&a[i+2]=='g'&&a[i+3]=='(')
                {
                        pushint(&c,68);
                        i=i+4;
                }
		//log10(
                else if(a[i]=='l'&&a[i+1]=='o'&&a[i+2]=='g'&&a[i+3]=='1')
                {
                        pushint(&c,69);
                        i=i+6;
                }
		//ln(
                else if(a[i]=='l'&&a[i+1]=='n'&&a[i+2]=='(')
                {
                        pushint(&c,70);
                        i=i+3;
                }
		//pow(
                else if(a[i]=='p'&&a[i+1]=='o'&&a[i+2]=='w'&&a[i+3]=='(')
                {
                        pushint(&c,71);
                        i=i+4;
                }
         	//exp(
                else if(a[i]=='e'&&a[i+1]=='x'&&a[i+2]=='p'&&a[i+3]=='(')
                {
                        pushint(&c,72);
                        i=i+4;
                }
		//fact(
                else if(a[i]=='f'&&a[i+1]=='a'&&a[i+2]=='c'&&a[i+3]=='t')
                {
                        pushint(&c,73);
                        i=i+5;
                }
		//mod(
                else if(a[i]=='m'&&a[i+1]=='o'&&a[i+2]=='d'&&a[i+3]=='(')
                {
                        pushint(&c,74);
                        i=i+4;
                }
		  //sqrt(
                else if(a[i]=='s'&&a[i+1]=='q'&&a[i+2]=='r'&&a[i+3]=='t')
                {
                        pushint(&c,75);
                        i=i+5;
                }
		  //cuberoot(
                else if(a[i]=='c'&&a[i+1]=='u'&&a[i+2]=='b'&&a[i+3]=='e')
                {
                        pushint(&c,76);
                        i=i+9;
                }
		  //yroot(
                else if(a[i]=='y'&&a[i+1]=='r'&&a[i+2]=='o'&&a[i+3]=='o')
                {
                        pushint(&c,77);
                        i=i+6;
                }
		//avg([
		else if(a[i]=='a'&&a[i+1]=='v'&&a[i+2]=='g'&&a[i+3]=='('&&a[i+4]=='[')
		{
			b[j++]='[';
			b[j++]=' ';
			pushint(&c,78);
			i=i+5;
		}
		//sum([
                else if(a[i]=='s'&&a[i+1]=='u'&&a[i+2]=='m'&&a[i+3]=='('&&a[i+4]=='[')
                {
                        b[j++]='[';
                        b[j++]=' ';
                        pushint(&c,79);
                        i=i+5;
                }
		//var([
                else if(a[i]=='v'&&a[i+1]=='a'&&a[i+2]=='r'&&a[i+3]=='('&&a[i+4]=='[')
                {
                        b[j++]='[';
                        b[j++]=' ';
                        pushint(&c,80);
                        i=i+5;
                }
		//varp([
                else if(a[i]=='v'&&a[i+1]=='a'&&a[i+2]=='r'&&a[i+3]=='p'&&a[i+4]=='(')
                {
                        b[j++]='[';
                        b[j++]=' ';
                        pushint(&c,81);
                        i=i+6;
                }
		//stdev([
                else if(a[i]=='s'&&a[i+1]=='t'&&a[i+2]=='d'&&a[i+3]=='e'&&a[i+4]=='v'&&a[i+5]=='(')
                {
                        b[j++]='[';
                        b[j++]=' ';
                        pushint(&c,82);
                        i=i+7;
                }
		//stdev([
                else if(a[i]=='s'&&a[i+1]=='t'&&a[i+2]=='d'&&a[i+3]=='e'&&a[i+4]=='v'&&a[i+5]=='p')
                {
                        b[j++]='[';
                        b[j++]=' ';
                        pushint(&c,83);
                        i=i+8;
                }
		//])
		else if(a[i]==']'&&a[i+1]==')')
		{
			while(c.a[c.top]<78)
                        {
                                popint(&c,&tmp);
                                b[j++]=' ';
                                b[j++]=tmp;
			}
			popint(&c,&tmp);
                        b[j++]=' ';
                        b[j++]=tmp;
			i=i+2;

		}
		else if(a[i]==',')
		{
			while(c.a[c.top]<65)
                        {
                                popint(&c,&tmp);
                                b[j++]=' ';
                                b[j++]=tmp;
                        }
			b[j++]=' ';
			i++;
		}
		// num
		else if((a[i]>=48&&a[i]<=57)||a[i]=='.')
		{
			b[j++]=a[i];
			i++;
		}
		//(
		else if(a[i]=='(')
		{
			pushint(&c,a[i]);
			i++;
		}
		//)
		else if(a[i]==')')
		{
			while(c.a[c.top]=='+'||c.a[c.top]=='-'||c.a[c.top]=='*'||c.a[c.top]=='/')
			{
				popint(&c,&tmp);
				b[j++]=' ';
				b[j++]=tmp;
			}
			if(c.a[c.top]=='(')
				popint(&c,&tmp);
			else
			{
				popint(&c,&tmp);
                                b[j++]=' ';
                                b[j++]=tmp;
			}
			i++;
		}
		else if(a[i]=='+' || a[i]=='-')
		{
			while((c.top)!=-1 && (c.a[c.top]=='+'||c.a[c.top]=='-'||c.a[c.top]=='*'||c.a[c.top]=='/'))
			{
				popint(&c,&tmp);
				b[j++]=' ';
				b[j++]=tmp;
			}
			b[j++]=' ';
			pushint(&c,a[i]);
			i++;
		}
		else if(a[i]=='*' || a[i]=='/')
		{
			while((c.top)!=-1 && (c.a[c.top]=='*'||c.a[c.top]=='/'))
			{
				popint(&c,&tmp);
				b[j++]=' ';
				b[j++]=tmp;
		    }
			b[j++]=' ';
			pushint(&c,a[i]);
			i++;
		}
	
	}
	while((c.top)!=-1)
	{
		popint(&c,&tmp);
		b[j++]=' ';
		b[j++]=tmp;
	}
	b[j]='\0';
}



/*
typedef struct node
{
        char s[121];  *接收实数/
        int zheng[60]; *存放整数部分*
        int xshu[60]; *存放小数部分*
        int zhlen; *整数部分的长度*
        int xlen; *小数部分的长度*
        int T; *符号位,T= -1表示该数为负,T=1表示该数为非负数*
}num;
*/


char * change(num *e)
{
	int i,j=0;
	for(i=0;i<=59;i++)
	{
		if(e->zheng[i]!=0)
		{
			e->zhlen=60-i;
			break;
		}
		if(i==59) 
		{
			e->zhlen=1;
			break;
		}
	}
	for(i=59;i>=0;i--)
	{
		if(e->xshu[i]!=0)
		{
			e->xlen=i+1;
			break;
		}
		if(i==0)
		{
			e->xlen=0;
			break;
		}
	}
	char *c=(char*)calloc(1,120);
	for(i=(e->zhlen-1);i>=0;i--)
		c[j++]=e->zheng[59-i]+'0';
	if(e->xlen!=0)
	{
		c[j++]='.';
		for(i=0;i<e->xlen;i++)
			c[j++]=e->xshu[i]+'0';
	}
	c[j]='\0';
	if(e->T==-1)
	{	for(i=j;i>=0;i--)
			c[i+1]=c[i];
		c[0]='-';
	}
	return c;
}

int panduan(num *e1,num *e2)
{	
	int i;
	int tmp;
	for(i=0;i<=59;i++)
	{
		tmp=e1->zheng[i]-e2->zheng[i];
		if(tmp!=0) break;
	}
	
	if(tmp>0)  return  1;
	if(tmp<0)  return -1;
	
	for(i=0;i<=59;i++)
        {
                tmp=e1->xshu[i]-e2->xshu[i];
                if(tmp!=0) break;
        }

	if(tmp>0)  return  1;
        if(tmp<0)  return -1;

	return 0;
}

int pd(char *a,char *b)
{
	int tmp;
	num *e1,*e2;
	e1=mynum(a);
	e2=mynum(b);
	tmp=panduan(e1,e2);
	return tmp;
}

int weishu(num *e1,num *e2)
{
	int i,j;
	int tmp1=0,tmp2=0;
	for(i=0;i<=59;i++)
	{
		if((e1->zheng[i])!=0)
		{
			tmp1=60-i;
			break;
		}
	}
	if(tmp1==0)
	for(i=0;i<=59;i++)
	{
		if((e1->xshu[i])!=0)	
		{
			tmp1=-i;
			break;
		}
	}
	for(i=0;i<=59;i++)
        {
                if((e2->zheng[i])!=0)
                {
                        tmp2=60-i;
                        break;
                }
        }
        if(tmp2==0)
        for(i=0;i<=59;i++)
        {
                if((e2->xshu[i])!=0)
                {
                        tmp2=-i;
                        break;
                }
        }
	
	if(tmp1==0) return -1;
	return tmp1-tmp2;
	
	
	
	
}

char * myadd(char *a,char *b)
{	
	int pd;
	num *e1,*e2,*e3;
	e3=(num*)calloc(1,sizeof(num));
	char *c;
	int i,j,xinum,zhnum,tmp=0;
	e1=mynum(a);
	e2=mynum(b);
	if(e1->T==e2->T)
	{
		e3->T=e1->T;
		//xiaoshu
		if((e1->xlen)>(e2->xlen))
			e3->xlen=e1->xlen;
		else
			e3->xlen=e2->xlen;
		for(i=e3->xlen-1;i>0;i--)
		{
			e3->xshu[i-1]=(e2->xshu[i]+e1->xshu[i]+e3->xshu[i])/10;
			e3->xshu[i]=(e2->xshu[i]+e1->xshu[i]+e3->xshu[i])%10;
			//e3->xshu[i-1]=(e2->xshu[i]+e1->xshu[i]+e3->xshu[i])/10;
		}
		//e3->xshu[0]=(e2->xshu[0]+e1->xshu[0]+e3->xshu[0])%10;
		if((e2->xshu[0]+e1->xshu[0]+e3->xshu[0])>=10)
			tmp=1;
		e3->xshu[0]=(e2->xshu[0]+e1->xshu[0]+e3->xshu[0])%10;
		//zhengshu
		if((e1->zhlen)>(e2->zhlen))
                        e3->zhlen=e1->zhlen;
                else
                        e3->zhlen=e2->zhlen;
		e3->zheng[59]=tmp;
		for(i=59;i>59-(e3->zhlen);i--)
		{
			e3->zheng[i-1]=(e2->zheng[i]+e1->zheng[i]+e3->zheng[i])/10;
			e3->zheng[i]=(e2->zheng[i]+e1->zheng[i]+e3->zheng[i])%10;
                        //e3->zheng[i-1]=(e2->zheng[i]+e1->zheng[i]+e3->zheng[i])/10;
		}
		if(e3->zheng[59-e3->zhlen]>0) e3->zhlen++;
	}
	
	//e1+ e2-
	if((e1->T==1) && (e2->T==-1))
	{
		pd=panduan(e1,e2);
		if(pd==0)	e3->T=1;

		if(pd==1)
		{
			e3->T=1;
			if((e1->xlen)>(e2->xlen))
                        	e3->xlen=e1->xlen;
                	else
                        	e3->xlen=e2->xlen;
			for(i=(e3->xlen)-1;i>0;i--)
			{
				if(e1->xshu[i]<e2->xshu[i])
				{
					e1->xshu[i]=e1->xshu[i]+10;
					e1->xshu[i-1]--;
				}
				e3->xshu[i]=e1->xshu[i]-e2->xshu[i];	
			}
			if(e1->xshu[0]<e2->xshu[0])
                        {
                        	e1->xshu[0]=e1->xshu[0]+10;
                        	e1->zheng[59]--;
                        }
                        e3->xshu[0]=e1->xshu[0]-e2->xshu[0];
			
			if((e1->zhlen)>(e2->zhlen))
                                e3->zhlen=e1->zhlen;
                        else
                                e3->zhlen=e2->zhlen;
			for(i=59;i>=60-(e3->zhlen);i--)
			{
				if(e1->zheng[i]<e2->zheng[i])
                                {
                                        e1->zheng[i]=e1->zheng[i]+10;
                                        e1->zheng[i-1]--;
                                }
                                e3->zheng[i]=e1->zheng[i]-e2->zheng[i];
			}
			
		}

		if(pd==-1)
		{
			e3->T=-1;
                        if((e1->xlen)>(e2->xlen))
                                e3->xlen=e1->xlen;
                        else
                                e3->xlen=e2->xlen;
                        for(i=(e3->xlen)-1;i>0;i--)
                        {
                                if(e2->xshu[i]<e1->xshu[i])
                                {
                                        e2->xshu[i]=e2->xshu[i]+10;
                                        e2->xshu[i-1]--;
                                }
                                e3->xshu[i]=e2->xshu[i]-e1->xshu[i];
                        }
                        if(e2->xshu[0]<e1->xshu[0])
                        {
                                e2->xshu[0]=e2->xshu[0]+10;
                                e2->zheng[59]--;
                        }
                        e3->xshu[0]=e2->xshu[0]-e1->xshu[0];
			
			if((e1->zhlen)>(e2->zhlen))
                                e3->zhlen=e1->zhlen;
                        else
                                e3->zhlen=e2->zhlen;
                        for(i=59;i>=60-(e3->zhlen);i--)
                        {
                                if(e2->zheng[i]<e1->zheng[i])
                                {
                                        e2->zheng[i]=e2->zheng[i]+10;
                                        e2->zheng[i-1]--;
                                }
                                e3->zheng[i]=e2->zheng[i]-e1->zheng[i];
                        }

		
		}
	}	

	if((e1->T==-1) && (e2->T==1))
	{
		pd=panduan(e1,e2);
		if(pd==0)	e3->T=1;

		if(pd==1)
		{
			e3->T=-1;
			if((e1->xlen)>(e2->xlen))
                        	e3->xlen=e1->xlen;
                	else
                        	e3->xlen=e2->xlen;
			for(i=(e3->xlen)-1;i>0;i--)
			{
				if(e1->xshu[i]<e2->xshu[i])
				{
					e1->xshu[i]=e1->xshu[i]+10;
					e1->xshu[i-1]--;
				}
				e3->xshu[i]=e1->xshu[i]-e2->xshu[i];	
			}
			if(e1->xshu[0]<e2->xshu[0])
                        {
                        	e1->xshu[0]=e1->xshu[0]+10;
                        	e1->zheng[59]--;
                        }
                        e3->xshu[0]=e1->xshu[0]-e2->xshu[0];
			
			if((e1->zhlen)>(e2->zhlen))
                                e3->zhlen=e1->zhlen;
                        else
                                e3->zhlen=e2->zhlen;
			for(i=59;i>=60-(e3->zhlen);i--)
			{
				if(e1->zheng[i]<e2->zheng[i])
                                {
                                        e1->zheng[i]=e1->zheng[i]+10;
                                        e1->zheng[i-1]--;
                                }
                                e3->zheng[i]=e1->zheng[i]-e2->zheng[i];
			}
			
		}

		if(pd==-1)
		{
			e3->T=1;
                        if((e1->xlen)>(e2->xlen))
                                e3->xlen=e1->xlen;
                        else
                                e3->xlen=e2->xlen;
                        for(i=(e3->xlen)-1;i>0;i--)
                        {
                                if(e2->xshu[i]<e1->xshu[i])
                                {
                                        e2->xshu[i]=e2->xshu[i]+10;
                                        e2->xshu[i-1]--;
                                }
                                e3->xshu[i]=e2->xshu[i]-e1->xshu[i];
                        }
                        if(e2->xshu[0]<e1->xshu[0])
                        {
                                e2->xshu[0]=e2->xshu[0]+10;
                                e2->zheng[59]--;
                        }
                        e3->xshu[0]=e2->xshu[0]-e1->xshu[0];
			
			if((e1->zhlen)>(e2->zhlen))
                                e3->zhlen=e1->zhlen;
                        else
                                e3->zhlen=e2->zhlen;
                        for(i=59;i>=60-(e3->zhlen);i--)
                        {
                                if(e2->zheng[i]<e1->zheng[i])
                                {
                                        e2->zheng[i]=e2->zheng[i]+10;
                                        e2->zheng[i-1]--;
                                }
                                e3->zheng[i]=e2->zheng[i]-e1->zheng[i];
                        }

		
		}
		
	}
	
	

	c=change(e3);

	
	//for(i=0;i<60;i++)
          //      printf("%d  ",e3->zheng[i]);
	//	printf("\n\n");
	 //for(i=0;i<60;i++)
         //       printf("%d  ",e3->xshu[i]);
	//	printf("\n\n");
	//printf("%d\n",e3->zhlen);
	//printf("%d\n",e3->xlen);
	

	//change to char[]
	c=change(e3);
	return c;
}

char *myjian(char *a,char *b)
{
	int i;
	char *e;

	if(b[0]=='-') 
		for(i=0;i<(int)strlen(b);i++)
			b[i]=b[i+1];
	else
	{
		for(i=(int)strlen(b);i>=0;i--)
			b[i+1]=b[i];
		b[0]='-';
	}
	
	e=myadd(a,b);
	return e;

}

char *mycheng(char *a,char *b)
{
	char *ee;
	int i=0,j=0,tmp=0,m=0,n=0,k=0;
	int c[240]={0},d[240]={0};
	int q[120]={0},w[120]={0},qlen=0,wlen=0;
	num *e1,*e2,*e3;
	e1=(num *)calloc(1,sizeof(num));
	e2=(num *)calloc(1,sizeof(num));
	e3=(num *)calloc(1,sizeof(num));

	e1=mynum(a);
	e2=mynum(b);
	if((e1->zhlen+e2->zhlen)>59)
	{
		printf("too big number");
		exit(1);
	}

	for(i=120-e1->xlen;i<=119;i++)
		q[i]=e1->xshu[j++];
	tmp=119-e1->xlen;
	j=0;
	for(i=tmp;i>tmp-e1->zhlen;i--)
		q[i]=e1->zheng[59-(j++)];
	qlen=e1->xlen+e1->zhlen;
	
	j=0;
	for(i=120-e2->xlen;i<=119;i++)
                w[i]=e2->xshu[j++];
        tmp=119-e2->xlen;
        j=0;
        for(i=tmp;i>tmp-e2->zhlen;i--)
                w[i]=e2->zheng[59-(j++)];
	wlen=e2->xlen+e2->zhlen;
	
	tmp=0;
	for(i=119,m=0;i>119-qlen;i--,m++)
	for(j=119,n=0;j>119-wlen;j--,n++)
	{
		c[239-m-n]=q[i]*w[j]+c[239-m-n];
		c[238-m-n]=c[239-m-n]/10+c[238-m-n];
		c[239-m-n]=c[239-m-n]%10;
	}
	
	k=0;
	for(i=240-e1->xlen-e2->xlen;i<=239;i++)
	{
		e3->xshu[k++]=c[i];
		if(k==60)
		break;	
	}
	e3->xlen=e1->xlen+e2->xlen;
	//if(e3->xlen>59)
          //      e3->xlen=59;
		
	for(i=0;i<240-e3->xlen;i++) if(c[i]!=0) {tmp=i;break;}
	
	if(i==(240-e3->xlen))  e3->zhlen=1;
	else
	{
		k=0;
		for(i=239-e3->xlen;i>=tmp;i--)
		{
			e3->zheng[59-k]=c[i];
			k++;	
		}	
	}
	
	e3->T=-1;
	if(e1->T==e2->T)
		e3->T=1;
	if(e3->xlen>60)
                e3->xlen=60;

	ee=change(e3);
	
	return ee;

}


char *mychu(char *a,char *b)
{
	num *e1,*e2;
	//e1=(num *)calloc(1,sizeof(num));
        //e2=(num *)calloc(1,sizeof(num));
	e1=mynum(a);
	e2=mynum(b);
	
	
	int i,j,n,tmp;
	char *an=(char*)calloc(1,122);
	an[0]='0';an[1]='\0';
	char c[32][40];
	tmp=pd(b,an);
	if (tmp==0)
	{
		printf("被除数不能为0\n");
		exit(1);
	}
	
	//判断位数
	char ten[3]="10";
	int cha;
	cha=weishu(e1,e2);
	for(n=1;n<=cha;n++)
	{
		b=mycheng(b,ten);
	}
	
	
	//小数后精确
	c[0][0]='1';
	c[0][1]='\0';
	for(i=1;i<=31;i++)
	{
		c[i][0]='0';
		c[i][1]='.';
		for(j=2;j<i+1;j++)
			c[i][j]='0';
		c[i][i+1]='1';
		c[i][i+2]='\0';
	}
	
	for(i=0;i<=30;)
	{
		while(1)
		{
			tmp=pd(a,b);
			
			if(tmp==1)	{a=myjian(a,b);an=myadd(an,c[i]);}
			if(tmp==-1)	break;
			if(tmp==0)
			{
				an=myadd(an,c[i]);
				for(n=1;n<=cha;n++)
        			{
        			        an=mycheng(an,ten);
        			}
				if((e1->T)!=(e2->T))
				{
					for(j=(int)strlen(an);j>=0;j--)
						an[j+1]=an[j];
					an[0]='-';
				}
				return an;
			}
			
		}
		i++;
		b=mycheng(b,c[1]);
	}
	for(n=1;n<=cha;n++)
        {
                an=mycheng(an,ten);
        }
	if((e1->T)!=(e2->T))
        {
      		for(j=(int)strlen(an);j>=0;j--)
                	an[j+1]=an[j];
              	an[0]='-';
       	}

	return an;
}


char *mypow(char *a,char *b)
{
	int i,j;
	int  t=0;
	if(b[0]=='-')
	{
		for(i=1;i<=strlen(b);i++)
		{
			b[i-1]=b[i];	
		}
		t=-1;
	}
	int afu=0;
	char zz[122];
	for(i=0;i<=strlen(a);i++)
	{
		zz[i]=a[i];
	}
	if(a[0]=='-')   afu=-1;
	char zero[3]="0";
	int tmp;
	char *eee;
	char e[3]="1";
        char ee[3]="1";
	eee=e;
	if(0==pd(b,zero))
	{
		a=(char *)calloc(3,sizeof(char));
		a[0]='1';
		a[1]='\0';
		return a;
	}	
	a=mycheng(a,e);
	while(1)
	{
		tmp=pd(b,eee);
		if(tmp==-1||tmp==0)	
		break;
		
		a=mycheng(a,zz);
		if(afu==-1)
		{
			for(i=strlen(a);i>=0;i--)
			{
				zz[i+1]=zz[i];
			}
			zz[0]='-';
		}
		eee=myadd(eee,ee);
		
	}
	if(t==-1)
	a=mychu(ee,a);	
	return a;
}

char *myfact(char *a)
{
	char one[3]="1";
	char *e=one;
	while(1)
	{
		e=mycheng(e,a);
		if(pd(a,one)==0)
		break;
		a=myjian(a,one);
	}
	return e;
}
char *mymod(char *a,char *b)
{
	int tmp;
	while(1)
	{
		if(pd(a,b)==-1)
		break;
		a=myjian(a,b);
		
	}
	return a;
}
char *myexp(char *a)
{
	char e[10]="2.71828";
	return mypow(e,a);
}
char *mysin(char *e)
{
	int i;
	int tmp=1;
	int m,n;
	char *a,*b,*an;
	char pi[20]="6.283185306";
	char zero[5]="0";
	char one[5]="1";
	char two[5]="2";
	char *now;
	an=zero;
	now=one;
	char *c;
	char ee[122];
	for(i=0;i<=strlen(e);i++)
	{
		ee[i]=e[i];
	}
	if(ee[0]=='-')	tmp=-1;
	
	if(tmp==-1)
	for(i=1;i<=strlen(e);i++)
	{
		ee[i-1]=ee[i];
	}
	
	char *eee;
	char *p;
	int j=0;
	char zs[122];
	eee=ee;
	if(pd(ee,pi)==1)
	{
		p=mychu(ee,pi);
		for(i=0;i<=strlen(p);i++)
		{
			if(p[i]=='.')
			{
				j=i;
				break;
			}
		}
		if(j==0)   eee=zero;
		else
		{
			for(i=0;i<j;i++)
			{
				zs[i]=p[i];
			}
			zs[i]='\0';
		p=mycheng(zs,pi);
		eee=myjian(ee,p);	
		}		
	}
		
	
	for(i=1;i<20;i++)
	{
		if(i!=1)	now=myadd(now,one);
		b=myfact(myjian(mycheng(two,now),one));
		a=mypow(eee,myjian(mycheng(two,now),one));
		c=mychu(a,b);
		if((i%2)==0)
		{
			an=myjian(an,c);
		}
		else    an=myadd(an,c);
	}
	if(tmp==-1)
	{
		if(an[0]=='-')
		for(i=1;i<=strlen(an);i++)
		{
			an[i-1]=an[i];
		}	
		else
		{
			for(i=strlen(an);i>=0;i--)
				an[i+1]=an[i];
			an[0]='-';
		}
	}
	return an;
}

char *mycos(char *e)
{
	int i;
	int tmp=1;
	int m,n;
	char *a,*b,*an;
	char pi[20]="6.283185306";
	char zero[5]="0";
	char one[5]="1";
	char two[5]="2";
	char four[5]="4";
	char *now;
	an=zero;
	now=one;
	char *c;
	char eeee[122];
	for(i=0;i<=strlen(e);i++)
	{
		eeee[i]=e[i];
	}
	char *ee;
	ee=myadd(eeee,mychu(pi,four));
	if(ee[0]=='-')	tmp=-1;
	
	if(tmp==-1)
	for(i=1;i<=strlen(e);i++)
	{
		ee[i-1]=ee[i];
	}
	
	char *eee;
	char *p;
	int j=0;
	char zs[122];
	eee=ee;
	if(pd(ee,pi)==1)
	{
		p=mychu(ee,pi);
		for(i=0;i<=strlen(p);i++)
		{
			if(p[i]=='.')
			{
				j=i;
				break;
			}
		}
		if(j==0)   eee=zero;
		else
		{
			for(i=0;i<j;i++)
			{
				zs[i]=p[i];
			}
			zs[i]='\0';
		p=mycheng(zs,pi);
		eee=myjian(ee,p);	
		}		
	}
		
	
	for(i=1;i<20;i++)
	{
		if(i!=1)	now=myadd(now,one);
		b=myfact(myjian(mycheng(two,now),one));
		a=mypow(eee,myjian(mycheng(two,now),one));
		c=mychu(a,b);
		if((i%2)==0)
		{
			an=myjian(an,c);
		}
		else    an=myadd(an,c);
	}
	if(tmp==-1)
	{
		if(an[0]=='-')
		for(i=1;i<=strlen(an);i++)
		{
			an[i-1]=an[i];
		}	
		else
		{
			for(i=strlen(an);i>=0;i--)
				an[i+1]=an[i];
			an[0]='-';
		}
	}
	return an;
}

char *mytan(char *e)
{
	char *a;
	char *b;
	char *c;
	a=mysin(e);
	b=mycos(e);
	c=mychu(a,b);
}

char* mylog(char *a,char *b)
{
	char *zero;
	zero=(char *)calloc(1,3);
	zero[0]='0';
	zero[1]='\0';
	
	char tmp[122]="0";
	char one[3]="1";
	char *shu=one;
	char *tmp1;
	char *tmp2;
	char *an1,*an2;

	if(b[0]=='1'&&b[1]=='\0')	return zero;

	int i=0;
	while(1)
	{
		tmp1=myjian(zero,shu);
		tmp2=myadd(zero,shu);
		
		if(strcmp(mypow(a,tmp1),b)==0) 		
		{
			tmp1=myjian(zero,tmp1);
			return tmp1;
		}
		if(strcmp(mypow(a,tmp2),b)==0) 		return tmp2;	
		
		shu=myadd(shu,one);
		i++;
		if(i==200) return zero;
		
	}
}

char* mylog10(char *b)
{

	char *an;
	char a[5]="10";
	return an=mylog(a,b);
}



char *houchuli(char *a)
{
	int i=0,j=0;
	char b[2000];
	char c[200];
	char temp1[122];
	char temp2[122];
	char *temp;
	char *an=(char *)calloc(122,1);
	yuchuli(a);
	hou(a,b);
	printf("%s\n",b);
	zhan pp;
	zhan *p=&pp;
	while(1)
	{
		if((b[i]>='0'&&b[i]<='9') || b[i]=='.')
		{
			j=0;
			c[j]=b[i];
			i++;
			while(1)
			{
				if((b[i]>='0'&&b[i]<='9') || b[i]=='.')
                		{
                       			j++;
                       			c[j]=b[i];
                        		i++;
				}
				else
					break;
			}
			j++;
			c[j]='\0';
			push(p,c);
		}
		if(b[i]=='[')
		{
		temp1[0]='[';
		temp1[1]='\0';
		push(p,temp1);
		i++;
		}
		
		if(b[i]==79)
		{
			temp1[0]='0';
                        temp1[1]='\0';
			temp=temp1;
			 while(1)
			{
				
				pop(p,temp2);
				if(temp2[0]=='[')	break;
				temp=myadd(temp,temp2);
			}
			push(p,temp);
			i++;
			
		}
		if(b[i]==78)
                {
			char *zxc;
			char zero[3]="0";
			char one[12]="1";
                        temp1[0]='0';
                        temp1[1]='\0';
			zxc=temp1;
                        temp=zero;
                         while(1)
                        {

                                pop(p,temp2);
                                if(temp2[0]=='[')       break;
                                temp=myadd(temp,temp2);
				zxc=myadd(zxc,one);
                        }
			temp=mychu(temp,zxc);
                        push(p,temp);
                        i++;

                }

		if(b[i]=='+')
		{
			pop(p,temp1);
			pop(p,temp2);
			temp=myadd(temp1,temp2);
			push(p,temp);
			i++;
		}
		if(b[i]=='-')
		{
			pop(p,temp1);
			pop(p,temp2);
			temp=myjian(temp2,temp1);
			push(p,temp);
			i++;
		}
		if(b[i]=='*')
		{
			pop(p,temp1);
                        pop(p,temp2);
                        temp=mycheng(temp1,temp2);
                        push(p,temp);
                        i++;
		}
		if(b[i]=='/')
		{
			pop(p,temp1);
                        pop(p,temp2);
                        temp=mychu(temp2,temp1);
                        push(p,temp);
                        i++;
		}
		if(b[i]==65)
		{
			pop(p,temp1);
                        //pop(p,temp2);
                        temp=mysin(temp1);
                        push(p,temp);
                        i++;
		}
		if(b[i]==66)
		{
			 pop(p,temp1);
                        //pop(p,temp2);
                        temp=mycos(temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==67)
		{
			 pop(p,temp1);
                        //pop(p,temp2);
                        temp=mytan(temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==68)
		{
			pop(p,temp1);
                        pop(p,temp2);
                        temp=mylog(temp2,temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==69)
		{
			 pop(p,temp1);
                        //pop(p,temp2);
                        temp=mylog10(temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==71)
		{
			 pop(p,temp1);
                        pop(p,temp2);
                        temp=mypow(temp2,temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==72)
		{
			 pop(p,temp1);
                        //pop(p,temp2);
                        temp=myexp(temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==73)
		{
			 pop(p,temp1);
                        //pop(p,temp2);
                        temp=myfact(temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==74)
		{
			pop(p,temp1);
                        pop(p,temp2);
                        temp=mymod(temp2,temp1);
                        push(p,temp);
                        i++;

		}
		if(b[i]==' ')
		{
			i++;
		}
		if(b[i]=='\0')		break;
	}
		
	pop(p,an);
	return an;
}














		

















