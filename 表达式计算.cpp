#include <iostream>
#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
#define MAXSIZE 100 //ջ�ռ�ĳ�ʼ������

typedef struct{
    char *base;	//ջ��ָ��
    char *top;	//ջ��ָ��
    int stacksize;	//ջ���õ��������
}Stack_char;

typedef struct{
    double *base;	//ջ��ָ��
    double *top;	//ջ��ָ��
    int stacksize;	//ջ���õ��������
}Stack_double;

template <typename Stack ,typename any>
//����ջ
int Create_Stack(Stack &s,any type)
{
    any c = type;
    s.base = new any[MAXSIZE];  //��ջ����ռ�
    if(!s.base) return 1;   //����ʧ��
    s.top = s.base; //top��baseָ��ͬһλ��
    s.stacksize = MAXSIZE;  //stack���Ϊջ����󳤶�
    return 0;
}

template <typename Stack ,typename any>
//��ջ��ѹ��Ԫ��
double Push_Stack(Stack &s,any c)
{
    if(s.top-s.base==s.stacksize){  //ջ��
        return 1;
    }
    *s.top++ = c;   //ѹ��ջ����ջ��ָ���1
    return 0;
}
template <typename Stack>
//Ԫ�س�ջ��ɾ����
int Pop_Stack(Stack &s)
{
    if(s.top==s.base){  //ջ��
        return 1;
    }
    --s.top;   //ջ��Ԫ�ظ���c
}
template <typename Stack>
//��ȡջ��Ԫ�أ���ɾ����
double Get_Stack(Stack &s)
{
    if(s.top!=s.base)   //ջ�ǿ�
    {
        return *(s.top-1);
    }
}

bool isInteger(double a){
    double absolute = abs(a);
    return absolute == floor(absolute);
}

// ����ƥ����
bool checkBracket(char str[]){
    int cntSmall = 0, cntMiddle = 0, cntBig = 0;
    for(int i=0;i<strlen(str);i++){
        if(str[i] == '('){
            if(cntSmall == 1)
                return false;
            else
                cntSmall = 1;
        }else if(str[i] == '['){
            if(cntMiddle == 1)
                return false;
            else
                cntMiddle = 1;
        }else if(str[i] == '{'){
            if(cntBig == 1)
                return false;
            else
                cntBig = 1;
        }else if(str[i] == ')'){
            if(cntSmall == 0)
                return false;
            else
                cntSmall = 0;
        }else if(str[i] == ']'){
            if(cntMiddle == 0)
                return false;
            else
                cntMiddle = 0;
        }else if(str[i] == '}'){
            if(cntBig == 0)
                return false;
            else
                cntBig = 0;
        }
    }
    if(cntSmall || cntMiddle || cntBig) return false;
    return true;
}

// ��׺���ʽת��׺���ʽ

//������ȽϺ���
//   Compare(ջ����C)    
char Compare(char stack_top,char c){
    char priority[8][8]={
        {'<','<','<','<','<','>','<','>'},
        {'<','<','<','<','<','>','<','>'},
        {'>','>','<','<','<','>','<','>'},
        {'>','>','<','<','<','>','<','>'},
        {'>','>','<','<','<','>','<','>'},
        {'>','>','>','>','>','>','0','>'},
        {'<','<','<','<','<','=','<','0'}, // �Ҹо�ԭ����ע�ʹ��ˣ�����Ӧ���� = �������ҿպ�������0�����﷨�Ƿ�
        {'<','<','<','<','<','0','<','='}  // = ��ʾ����#������Ҳ�����������ʽ��ֵ��ɡ�������#�������������������Ĵ�����һ���ģ�
    };                                    
    /*
       /// ������ԭ���ľ��������ջ��Ԫ�أ��ϲ��ǵ�ǰԪ��C              ������
       /// �Ұ������������һ�£���������ǵ�ǰԪ�أ��ϲ���ջ��Ԫ����   ������
    char priority[8][8]={
              --------- ��ǰԪ�� C ----------
              +   -   *   /   %   (   )   #
      |  +  {'>','>','<','<','<','<','>','>'},
      |  -  {'>','>','<','<','<','<','>','>'},
      |  *  {'>','>','>','>','>','<','>','>'}, 
 ջ��    /  {'>','>','>','>','>','<','>','>'}, 
 Ԫ��    %  {'>','>','>','>','>','<','>','>'},
      |  (  {'<','<','<','<','<','<','=','0'},  
      |  )  {'>','>','>','>','>','0','>','>'}, 
      |  #  {'<','<','<','<','<','<','0','='}
    };
    
    
    char priority[8][8]={
               --------- ջ��Ԫ��  ----------
               +   -   *   /   %   (   )   #
       |  +  {'<','<','<','<','<','>','<','>'},
       |  -  {'<','<','<','<','<','>','<','>'},
       |  *  {'>','>','<','<','<','>','<','>'},
 ��ǰ     /  {'>','>','<','<','<','>','<','>'},
 Ԫ��C    %  {'>','>','<','<','<','>','<','>'},
       |  (  {'>','>','>','>','>','>','0','>'},
       |  )  {'<','<','<','<','<','=','<','0'},
       |  #  {'<','<','<','<','<','0','<','='}
    };
       C
      (#
    
    */
    int i,j;    //�У���
    switch(c){  //��ת���ж�Ӧ�ķ���
        case'+':i=0;break;
        case'-':i=1;break;
        case'*':i=2;break;
        case'/':i=3;break;
        case'%':i=4;break;
        case'(':i=5;break;
        case')':i=6;break;
        case'#':i=7;break;   // # �Ǳ��ʽ�Ľ�����
    }
    switch(stack_top){  //��ת���ж�Ӧ�ķ���
        case'+':j=0;break;
        case'-':j=1;break;
        case'*':j=2;break;
        case'/':j=3;break;
        case'%':j=4;break;
        case'(':j=5;break;
        case')':j=6;break;
        case'#':j=7;break;   // # �Ǳ��ʽ�Ľ�����
    }
    return priority[i][j];
}

//���㺯��
double Operate(double m,double n,char x,int& status){
    double esp = 1e-8;
    status = 0;
    
    if(x=='+')
        return m+n;
    if(x=='-')
        return n-m;
    if(x=='*')
        return m*n;
    if(x=='/'){
        if(fabs(m) < esp){
            cout<<"�����������"<<endl;
            return status = 1;
        }
        return int(n/m);
    }
    if(x=='%'){
        if(m <= 0){
            cout<<"����ģ��С�ڵ����㣡"<<endl;
            return status = 2;
        }
        if(!isInteger(m)){
            cout<<"����ģ������������"<<endl;
            return status = 3;
        }
        if(!isInteger(n)){
            cout<<"������ģ������������"<<endl;
            return status = 4;
        }
        return (int)n % (int)m;
    }
}

int main(){
    Stack_char op;  //���������ջ
    Stack_double num;   //��������ջ

    double a = 0;
    char b = 'a';
    Create_Stack(num,a);    //��ʼ��ջ
    Create_Stack(op,b);

    Push_Stack(op,'#'); //�������ջѹ��#
    char end[2]="#";    //β����\0
    char s[MAXSIZE];
    cout << "����������ʽ��";
    cin>>s;
    if(checkBracket(s) == false){
        cout<<"�������Ų�ƥ��!"<<endl;
        return 0;
    }
    for(int i=0;i<strlen(s);i++){
        if(s[i] == '[' || s[i] == '{')
            s[i] = '(';
        else if(s[i] == ']' || s[i] == '}')
            s[i] = ')';
    }
    strcat(s,end);// ����ʽβ����#
    char c=s[0];
    int k=1;//�±�
    int status = 0;
    while(c!='#'||Get_Stack(op)!='#'){  //���ʽδ�����������δ��
        double y=0.0;
        double z=0.0;
        int count=0;
        // ����������
        if(c>='0'&&c<='9'){
            while(c>='0'&&c<='9'){  // ��������������
                y=y*10+(c-'0');
                c=s[k++];
                if(c=='.'){ //����С����
                    c=s[k++];
                    while (c>='0'&&c<='9'){
                        ++count;
                        z=z+pow(0.1,count)*(c-'0');
                        c=s[k++];
                    }
                }
            }
            Push_Stack(num,y+z);  // �Ѷ���������������ջ
        }
        else{
            //����������
            switch(Compare(Get_Stack(op),c))
            {
                case'>':  //ջ��Ԫ������Ȩ��,C���ȼ���
                    Push_Stack(op,c);
                    c=s[k++];
                    break;
                case'=':
                    Pop_Stack(op);  //����ƥ��ɹ����������ų�ջ
                    c=s[k++];  // ������һ���ַ�
                    break;
                case'<':  //��ջ������������ջ
                    char x=Get_Stack(op);Pop_Stack(op);
                    double m=Get_Stack(num);Pop_Stack(num);
                    double n=Get_Stack(num);Pop_Stack(num);
                    status = 0;
                    double op_num = Operate(m,n,x,status);
                    if(status != 0){
                        break;
                    }
                    Push_Stack(num,op_num);
                    break;
            }
            if(status){
                break;
            }
        }
    }
    if(status == 0){
        cout << endl << "������Ϊ��"<<setiosflags(ios::fixed) << setprecision(4) <<Get_Stack(num);
    }
    return 0;
}

/*
(6%4-1)*3-6 
-3

1+[(2+3)*4]-5
16

5%2+8*((2-7)/(3%5))%4
����,���Ų�ƥ��

5%2+8*[(2-7)/(3%5)]%4
������ģ����������

3%2*8*[(7-1)/(3%5)]%4
0

5*6/3+4*3
22

 */
