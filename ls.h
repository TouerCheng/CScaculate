#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
//服务器端的端口
#define SERV_PORT  4500
//链接请求队列最大长度
#define LISTENQ   12

//用户信息无效
#define INVALID_USERINFO 'n'
//用户信息有效
#define VALID_USERINFO 'y'

//收到的是用户名
#define USERNAME  0
//收到的是密码
#define PASSWORD  1

#define BUFSIZE  1024

//结构体高精度数据
typedef struct node 
{
	char s[121];/*接收实数*/  
	int zheng[60];/*存放整数部分*/  
	int xshu[60];/*存放小数部分*/  
	int zhlen;/*整数部分的长度*/  
	int xlen;/*小数部分的长度*/   
	int T;/*符号位,T= -1表示该数为负,T=1表示该数为非负数*/ 
}num;
typedef struct zh
{
	char data[30][122];
	int top;
}zhan;
typedef struct com
{
	char a[100];
	int  top;
}zhanint;

num *mynum(char *q);
void push(zhan *s,char *e);
void pop(zhan *s,char *e);
void yuchuli(char *e);
void popint(zhanint *s,char *e);
void pushint(zhanint *s,char e);
char * myadd(char *a,char *b);
char * myjian(char *a,char *b);
char * change(num *e);
int panduan(num *e1,num *e2);
char *mycheng(char *a,char *b);
int pd(char *a,char *b);
char *mychu(char *a,char *b);
int weishu(num *e1,num *e2);
char *mypow(char *a,char *b);
char *myfact(char *a);
char *mymod(char *a,char *b);
char *myexp(char *a);
char *mysin(char *e);
char *mycos(char *e);
char *mytan(char *e);
char* mylog(char *a,char *b);
char* mylog10(char *b);
char *houchuli(char *a);

//保存用户名密码和结构体的数组
struct userinfo
{
	char username[32];
	char password[32];
};

//以只含有一个空格的字符串作为数组的结束标志
/*struct userinfo users[]=
{
	{"linux","unix"},
	{"4507","4508"},
	{"clh","clh"},
	{"xl","xl"},
	{" "," "}
};*/

void my_err(const char * err_string,int line);
int my_recv(int conn_fd,char * date_buf,int len);
int find_name(const char *name);
void* send_data(void  *client_fd);
void my_sleep();
void *sleepthid(void *b);
#endif
