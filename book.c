#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "book.h"

void user_enroll()
{
    FILE *fp;
    char username[24];
    char password[24];
    char name[24];
    fp=fopen("user.text","a+");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }
    printf("请输入姓名>>");
    getchar();
    fgets(username,sizeof(username),stdin);
    printf("请输入密码>>");
    username[strlen(username)-1]='\0';
    fgets(password,sizeof(password),stdin);

    while(fgets(name,sizeof(name),fp))
    {
        strcpy(name,strtok(name,":"));
        if(strcmp(name,username)==0)
        {
            printf("该用户名以存在，无法注册！\n");
            return ;
        }
    }
    
    fputs(username,fp);
    fputs(":",fp);
    fputs(password,fp);
    printf("注册成功！\n");
    fclose(fp);
}

int login(char *username)
{
    int flag;
    FILE *fp;
    //char username[24];
    char password[24];
    char name[24];
    char pass[24];
    fp=fopen("user.text","r+");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return 0;
    }
    getchar();
    printf("请输入姓名>>");
    fgets(username,sizeof(username),stdin);
    printf("请输入密码>>");
    username[strlen(username)-1]='\0';
    fgets(password,sizeof(password),stdin);    

    while(fgets(name,sizeof(name),fp))
    {
        strcpy(name,strtok(name,":"));
        strcpy(pass,strtok(NULL,":"));
        if(strcmp(name,username)==0 && strcmp(pass,password)==0)
        {
            printf("欢迎%s,登录成功！\n",username);
            flag=1;
            return flag;
        }
    }
    printf("登入失败，用户名或密码错误！\n");
    flag=0;
    fclose(fp);
    return flag;
}

int root_login()
{
    getchar();
    int flag;
    FILE *fp;
    char rootname[24];
    char password[24];
    char name[24];
    char pass[24];
    char data[48];
    fp=fopen("root.text","r");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return 0;
    }

    printf("请输入姓名>>");
    fgets(rootname,sizeof(rootname),stdin);
    printf("请输入密码>>");
    rootname[strlen(rootname)-1]='\0';
    fgets(password,sizeof(password),stdin);    

    while(fgets(data,sizeof(data),fp))
    {
        strcpy(name,strtok(data,":"));
        strcpy(pass,strtok(NULL,":"));
        if(strcmp(name,rootname)==0 && strcmp(pass,password)==0)
        {
            printf("管理员登录成功！\n");
            flag=1;
            return flag;
        }
    }
    printf("管理员登入失败，用户名或密码错误！\n");
    flag=0;
    fclose(fp);
    return flag;
}

void book_input(Book *book)
{

    FILE *fp;
    fp=fopen("bookfile.text","a+");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }


    fprintf(fp,"%s:%s:%s:%s:%d\n",book->id,book->bookname,book->author,book->publition,book->inventory);
    printf("插入成功!\n");
    fclose(fp);
}

void detail_insert(Book *book)
{
    char id[12];
    char bookname[48];
    char author[24];
    char publition[48];
    int inventory;

    printf("请输入书的id>>");
    scanf("%s",id);
    printf("请输入书的名字>>");
    scanf("%s",bookname);
    printf("请输入书的作者>>");
    scanf("%s",author);
    printf("请输入书的出版社>>");
    scanf("%s",publition);
    printf("请输入书的库存量>>");
    scanf("%d",&inventory);

    strcpy(book->id,id);
    strcpy(book->bookname,bookname);
    strcpy(book->author,author);
    strcpy(book->publition,publition);
    book->inventory=inventory;
}

void  check_file()
{
    Listnode *head=malloc(sizeof(Listnode));
    head->next=NULL;
    listnode_check(head);
    Listnode *p=head->next;
    printf("******************图书信息******************\n");
    while(p)
    {
        printf("id:(%s)---<<%s>>---作者:(%s)---出版社:(%s)---库存:(%d)\n",p->book.id,p->book.bookname,p->book.author,p->book.publition,p->book.inventory);
        p=p->next;
    }
    printf("********************************************\n");
}

//链表读取文件数据
void listnode_check(Listnode *head)
{
    FILE *fp;
    char data[124];
    char id[12];
    char bookname[48];
    char author[24];
    char publition[48];
    int inventory;
    Listnode *p=head;
    fp=fopen("bookfile.text","r");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }
    while(fgets(data,sizeof(data),fp))
    {
        Listnode *temp=malloc(sizeof(Listnode));
        temp->next=NULL;

        strcpy(temp->book.id,strtok(data,":"));
        strcpy(temp->book.bookname,strtok(NULL,":"));
        strcpy(temp->book.author,strtok(NULL,":"));
        strcpy(temp->book.publition,strtok(NULL,":"));
        temp->book.inventory=atoi(strtok(NULL,"\n"));

        p->next=temp;
        p=p->next;
    }

    fclose(fp);
}

void listnode_input(Listnode *head)
{
    FILE *fp;
    Listnode *p=head->next;
    fp=fopen("bookfile.text","w");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }
    while(p)
    {
        fprintf(fp,"%s:%s:%s:%s:%d\n",p->book.id,p->book.bookname,p->book.author,p->book.publition,p->book.inventory);
        p=p->next;
    }

    fclose(fp);
}

void listnode_userinput(Listnode *head)
{
    FILE *fp;
    Listnode *p=head->next;
    fp=fopen("user.text","w");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }
    while(p)
    {
        fprintf(fp,"%s:%s\n",p->user.username,p->user.password);
        p=p->next;
    }

    fclose(fp);
}

void borrow(char *name)
{
    char endt[40];
    char t[48];
    time_t curentime;
    time(&curentime);
    // struct tm *st=gmtime(&curentime);
    // st->tm_mday++;
    
    FILE *fp0;
    Listnode *head=malloc(sizeof(Listnode));
    
    fp0=fopen("borrow.text","a+");
    if(fp0==NULL)
    {
        printf("The file open error\n");
        return ;
    }
    getchar();
    char id[12];
    head->next=NULL;
    listnode_check(head);
    Listnode *p=head->next;
    printf("请输入要借阅的书籍号>>");
    scanf("%s",id);

    while(p)
    {
        if(strcmp(id,p->book.id)==0)
        {
            if(p->book.inventory>0)
            {
                p->book.inventory-=1;
                printf("借阅成功！\n");
                strcpy(t,ctime(&curentime));
                // strcpy(endt,asctime(st));
                t[strlen(t)-1]='\0';
                // endt[strlen(endt)-1]='\0';
                fprintf(fp0,"%s:%s:%s\n",name,p->book.bookname,t);
                listnode_input(head);
                fclose(fp0);
                return ;
            }
            else{
                printf("该书籍已被借光，请选择其他书籍\n");
                return ;
            }
        }
        p=p->next;
    }
    printf("未查询到对应书籍请检查输入!\n");
    fclose(fp0);
}

void listnode_check_user(Listnode *head)
{
    FILE *fp;
    char data[124];
    char username[48];
    char password[24];
    Listnode *p=head;
    fp=fopen("user.text","r");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }


    while(fgets(data,sizeof(data),fp))
    {
        Listnode *temp=malloc(sizeof(Listnode));
        temp->next=NULL;

        strcpy(temp->user.username,strtok(data,":"));
        strcpy(temp->user.password,strtok(NULL,"\n"));

        p->next=temp;
        p=p->next;
    }

    fclose(fp);
}

void check_userfile()
{
    Listnode *head=malloc(sizeof(Listnode));
    head->next=NULL;
    listnode_check_user(head);
    Listnode *p=head->next;
    printf("****************用户信息*******************\n");
    while(p)
    {
        printf("用户名:%s <---> 密码:%s\n",p->user.username,p->user.password);
        p=p->next;
    }
    printf("*******************************************\n");
}

void password_back()
{
    char username[24];
    char name[24];
    char makesure[24];
    char password[24];
    char data[48];

    Listnode *head=malloc(sizeof(Listnode));
    listnode_check_user(head);
    Listnode *p=head->next;
    //check_userfile();
    printf("请输入用户名>>");
    scanf("%s",username);
    while(p)
    {
        if(strcmp(username,p->user.username)==0)
        {
            flag:
            printf("请输入新密码>>");
            scanf("%s",password);
            printf("请在次确认密码>>");
            scanf("%s",makesure);
            if(strcmp(password,makesure)!=0)
            {
                printf("二次密码输入错误请重新输入！\n");
                printf("*********************\n");
                goto flag;
            }
            else{
                strcpy(p->user.password,password);
                listnode_userinput(head);
                printf("密码修改成功！\n");
                return ;
            }
        }
        p=p->next;
    }
    
    printf("没有找到该用户名!\n");

}

void book_delete()
{
    char id[48];
    Listnode *head=malloc(sizeof(Listnode));
    listnode_check(head);
    Listnode *p=head;
    printf("请输入要删除的书籍号>>");
    scanf("%s",id);
    while(p->next)
    {
        if(strcmp(id,p->next->book.id)==0)
        {
            p->next=p->next->next;
            listnode_input(head);
            printf("删除成功!\n");
            return ;
        }
        p=p->next;
    }
    printf("没有找到相应书籍~\n");
}

void back(char *uuname)
{
    char bookname[48];
    printf("请输入要还书籍的书籍名>>");
    scanf("%s",bookname);
    Listnode *head=malloc(sizeof(Listnode));
    Listnode *head1=malloc(sizeof(Listnode));
    listnode_check_borrow(head);
    listnode_check(head1);
    Listnode *p=head;
    Listnode *q=head1->next;
    while(p->next)
    {
        if(strcmp(p->next->book.bookname,bookname)==0 && strcmp(uuname,p->next->user.username)==0)
        {
            p->next=p->next->next;
            listnode_borrow_input(head);


            while(q)
            {
                if(strcmp(bookname,q->book.bookname)==0)
                {
                    q->book.inventory++;
                    listnode_input(head1);
                    printf("还书成功！\n");
                    return ;
                }
                q=q->next;
            }

            break;
        }
        p=p->next;
    }
    printf("未找到借阅信息！\n");  
    printf("还书失败！\n");
}

void listnode_check_borrow(Listnode *head)
{
    FILE *fp;
    char data[124];
    char username[48];
    char bookname[48];
    char time[48];
    Listnode *p=head;
    fp=fopen("borrow.text","r");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }


    while(fgets(data,sizeof(data),fp))
    {
        Listnode *temp=malloc(sizeof(Listnode));
        temp->next=NULL;

        strcpy(temp->user.username,strtok(data,":"));
        strcpy(temp->book.bookname,strtok(NULL,":"));
        strcpy(temp->book.time,strtok(NULL,"\n"));

        p->next=temp;
        p=p->next;
    }

    fclose(fp);
}

void listnode_borrow_input(Listnode *head)
{
    FILE *fp;
    Listnode *p=head->next;
    fp=fopen("borrow.text","w");
    if(fp==NULL)
    {
        printf("The file open error\n");
        return ;
    }
    while(p)
    {
        fprintf(fp,"%s:%s:%s\n",p->user.username,p->book.bookname,p->book.time);
        p=p->next;
    }

    fclose(fp);
}

void print_borrow()
{
    Listnode *head=malloc(sizeof(Listnode));
    listnode_check_borrow(head);
    Listnode *p=head->next;
    printf("****************借阅信息********************\n");
    while(p)
    {
        printf("借阅人:%s --> 借阅书籍:<<%s>> -->借阅时间:%s\n",p->user.username,p->book.bookname,p->book.time);
        p=p->next;
    }
    printf("*******************************************\n");
}

void print_interface(char *filename)
{
    FILE *fp;
    char data[58];
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("文件打开失败！\n");
        return ;
    }
    while(fgets(data,sizeof(data),fp))
    {
        printf("%s",data);
    }
    printf("\n");
    printf(" **\n");
    printf(" **\n");
    printf("请输入操作(对应数字)>>");
}


void user_delete()
{
    char username[48];
    Listnode *head=malloc(sizeof(Listnode));
    listnode_check_user(head);
    Listnode *p=head;
    printf("请输入要删除的用户>>");\
    scanf("%s",username);
    while(p->next)
    {
        if(strcmp(username,p->next->user.username)==0)
        {
            p->next=p->next->next;
            listnode_userinput(head);
            printf("用户删除成功！\n");
            return ;
        }
        p=p->next;
    }
    printf("未找到用户！\n");
} 
