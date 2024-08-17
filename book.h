#ifndef __BOOK_H__
#define __BOOK_H__

typedef struct book
{
    char id[12];
    char bookname[48];
    char author[24];
    char publition[48];
    char time[48];
    int inventory;
}Book;
typedef struct user
{
    char username[24];
    char password[24];
}User;

typedef struct node
{
    Book book;
    User user;
    struct node *next;
}Listnode;

 void user_enroll();
 int login(char *username);
int root_login();
void book_input(Book *book);
void detail_insert(Book *book);
void  check_file();
void listnode_check(Listnode *head);
void listnode_input(Listnode *head);
void check_userfile();
void listnode_check_user(Listnode *head);
void listnode_userinput(Listnode *head);
void borrow(char *name);
void password_back();
void book_delete();
void listnode_check_borrow(Listnode *head);
void listnode_borrow_input(Listnode *head);
void back(char *uuname);
void print_borrow();
void print_interface(char *filename); 
void user_delete();
#endif