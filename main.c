#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "book.h"

char uuname[24];

int main(int argc, char const *argv[])
{
    #if 1
    Book book;
    int n,n1,n2,n3,n4,rec,rec1;
    int quit=1;
    while(quit){
    print_interface("./ui/interface01");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        user_enroll();
        break;
    case 2:
            flag1:
            print_interface("./ui/login1");
            scanf("%d",&n1);   
            switch (n1)
            {
            case 1:
                
                 rec=root_login();
                if(rec==1)
                {
                flag3:       
                print_interface("./ui/root");
                                scanf("%d",&n2);
                                switch (n2)
                                {
                                case 1:
                                    flag2: 
                                    print_interface("./ui/root_check");
                                    scanf("%d",&n4);
                                                    switch (n4)
                                                    {
                                                    case 1:
                                                    check_file();
                                                        goto flag2;
                                                    case 2:
                                                    check_userfile();
                                                        goto flag2;
                                                    case 3:
                                                    print_borrow();
                                                        goto flag2;
                                                    case 4:
                                                    goto flag3;
                                                        break;
                                                    default:
                                                    printf("输入错误！\n");
                                                    return 0;
                                                        break;
                                                    }
                                break;
                                case 2:
                                        detail_insert(&book);
                                         book_input(&book);
                                        
                                goto flag3;
                                case 3:
                                        book_delete();
                                goto flag3;

                                case 4:
                                user_delete();
                                goto flag3;
                                case 5:
                                goto flag1;
                                break;
                                 default:
                                  printf("输入错误！\n");
                                                    return 0;
                                    break;
                                }
                }
                
                break;
            case 2:
                 rec1=login(uuname);
                if(rec1==1)
                {
                    flag4:
                        print_interface("./ui/user");
                scanf("%d",&n3);
                                switch (n3)
                                {
                                case 1:
                                check_file();
                                    goto flag4;
                                case 2:
                                borrow(uuname);
                                    goto flag4;
                                case 3:
                                back(uuname);
                                    goto flag4;
                                case 4:
                                goto flag1;
                                    break;
                                default:
                                 printf("输入错误！\n");
                                                    return 0;
                                    break;
                                }
                 break;
            default:
                        // printf("输入错误！\n");
                        //                             return 0;
            break;
            }
                }
                
        break;
    case 3:
    password_back();
    break;
    case 4:
    quit=0;
    break;
    default:
     printf("输入错误！\n");
                        return 0;
    break;
    }
}
#endif
    return 0;
}

                    