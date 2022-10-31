#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <windows.h>
int main_flag=0;
struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};
struct offer
{
    char name[25];
    char phone[11];
};
struct node_offer
{
    struct offer d1;
    struct node_offer *next;
};
struct offer s;
struct node *headc = NULL,*newnode,*tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;
struct node_offer *head;
void insert_list();
struct offer check_customer_name()
{ 
    int i;
    struct offer s;
    printf("\n\n\nEnter Your Name:");
    scanf("%[^\n]%*c",s.name);
    label2:
    printf("\nEnter Your Mobile Number:");
    scanf("%s",s.phone);
    int n=strlen(s.phone);
    if(n>=10 && n<=13)
    for(i=0;i<n;i++)
    {
        if(isalpha(s.phone[i]))
        {
            printf("\n\nEnter A Valid Mobile Number!\n\n");
            goto label2;
        }
    }
    else
    {
        printf("\n\nEnter A Valid 10 - 13 Digit Mobile Number!\n\n");
        goto label2;
    }
    return s;
};

void read_binary(FILE *f1)
{
    struct offer s;
    head=NULL;
	while(fread(&s,sizeof(s),1,f1))
    {
    	insert_list(s);
    }
}
void write_binary(FILE *f1)
{
    struct offer s;
    struct node_offer *dumpy=head;
	while(dumpy!=NULL)
	{
        s=dumpy->d1;
        fwrite(&s, sizeof(s), 1, f1);
        dumpy=dumpy->next;
	}
}
void insert_list(struct offer d)
{
   struct node_offer *ptr = (struct node_offer *) malloc(sizeof(struct node_offer));
   struct node_offer *temp=NULL;
    ptr->next = NULL;
    if(ptr == NULL)
        {
            printf("\nOVERFLOW");
        }
        else
        {
            ptr->d1=d;
            if(head == NULL)
            {
                head = ptr;
                //printf("\nNode inserted-Head");
            }
            else
            {
                temp = head;
                while(temp -> next != NULL)
                {
                    temp = temp -> next;
                }
                temp->next = ptr;
                temp=ptr;
                //printf("\nNode inserted-Body");

            }
        }
}
void insert()
{
	struct node_offer *temp=head;
    FILE *f1;
    f1=fopen("data.dat","rb");
    if(!f1)
    {
        printf("\n\n\t\t\t\t\t\tFile Doesn't Exist Please Create It...!\n");
        return;
    }
    read_binary(f1);
    fclose(f1);
    struct offer d;
    fflush(stdin);
    printf("\n\t\t\t\t\t\t Enter the name : ");
    gets(d.name);
    fflush(stdin);
    printf("\n\t\t\t\t\t\t Enter the phone number: ");
    gets(d.phone);
    fflush(stdin);
    insert_list(d);
    FILE *f2;
    f2=fopen("data.dat","wb");
    write_binary(f2);
    fclose(f2);

}
void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View Total Sales\n");
    printf("\t\t\t\t\t\t\t2. Add New Food In The Order Menu\n");
    printf("\t\t\t\t\t\t\t3. Delete Food From The Order Menu\n");
    printf("\t\t\t\t\t\t\t4. Display Order Menu\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\n\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void customermenu()
{
    printf("\n\t\t\t\t\t\t\t1. Place Your Order\n");
    printf("\t\t\t\t\t\t\t2. View Your Order\n");
    printf("\t\t\t\t\t\t\t3. Delete Food From Order\n");
    printf("\t\t\t\t\t\t\t4. Display Final Bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\n\t\t\t\t\t\t\t   Enter Your Choice --->");
}

struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tOOPS !! Sorry This Food Is Not Present In Today's Kitchen!!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        printf("\n\t\t\t\t\t\t\t!! Still No Orders Were Taken !!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* delete(int data,struct node *head, struct node *tail)
{
    if(head==NULL)
    {
        printf("\n\t\t\t\t\t\t\tList Is Empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
	label:
    printf("\n\t\t\t\t\tEnter Code No.Of The Food Which Is To Be Deleted: ");
    int num;
    char fono[100];
    scanf("%s",&fono);
    num=atoi(fono);
    if (isalpha(num))
    {
    	printf("\n\n\t\t\t\t\t\t  Invalid Code Number Please Enter A Valid One!!");
    	goto label;
	}

    struct node* temp=heada;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = delete(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()
{
	label:
    printf("\n\t\t\t\t\tEnter Code No.Of The Food Which Is To Be Deleted: ");
    int num;
    char fono[3];
    scanf("%s",&fono);
    num=atoi(fono);
    if (isalpha(num))
    {
    	printf("\n\n\t\t\t\t\t\t Invalid Code Number Please Enter A Valid One!!");
    	goto label;
	}

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()
{
    int i;
    fflush(stdin);
    struct offer s=check_customer_name();
    FILE *f2;
    f2=fopen("data.dat","rb");
    if(!f2)
	{
	    printf("\n\n\t\t\t\t\t\tFile doesn't exist and it is been created...!\n");
        FILE *f3;
        f3=fopen("data.dat","wb");
        fclose(f3);
	}
    read_binary(f2);
    fclose(f2);
    struct node_offer *temp1=head;
    int flag=0;
    while(temp1!=NULL)
    {
        if(strcmp(temp1->d1.phone,s.phone)==0)
        {
            flag++;
        }
        temp1=temp1->next;
    }
    if(flag!=0)
    {
        printf("\n You Are A Old Customer\n");
        displayList(headc);
        struct node *temp = headc;
        float total_price = 0;
        while (temp!=NULL)
        {
            total_price +=temp->price;
            temp = temp->next;
        }
        int tot;
        tot=(total_price*20)/100;
        total_price=total_price-tot;
        printf("\t\t\t\t\t\t\t** GRAND TOTAL: %0.02f **\n",total_price);
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t You Are A New Customer\n");
        printf("\n\t\t\t\t\t\t\t Welcome To Our Restaurant \n\n");
        insert_list(s);
        FILE *f1;
        f1=fopen("data.dat","ab");
        write_binary(f1);
        fclose(f1);
        displayList(headc);
        struct node *temp = headc;
        float total_price = 0;
        while (temp!=NULL)
        {
            total_price +=temp->price;
            temp = temp->next;
        }

        printf("\t\t\t\t\t\t\t** GRAND TOTAL: %0.02f **\n",total_price);
    }
    //////
}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
	system("cls");
	system("Color F0");
	char password[100];
    char username[20];
	int i=0;

 	printf("\n\t\t\t\t\t\tEnter Your Username: ");
    scanf("%s",username);
    printf("\n\t\t\t\t\t\tEnter Your Password:");
    do
    {
        password[i]=getch();
        printf("*");
        i++;
    }
    while(password[i-1]!='\r');
    password[i-1]='\0';

    if( strcmpi( username,"team2" ) == 0 && strcmp ( password,"password" ) == 0 )
    {

        printf("\n\n\t\t\t\tt\t\t\t**VALID\n");
        printf("\n\t\t\t\t\t\t*****\n");
    }
    else
	{
	    printf("\n\n\t\t\t\t\t\t\t**INVALID\n");
	return 0;
    }
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        adminmenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:

                printf("\n\t\t\t\t\t\t\tEnter Code No. Of The Food [It Should Be 3 Numbers]: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\n\t\t\t\t\t\tFood With Given Serial Number Already Exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\n\t\t\t\t\t\t\tEnter Food Name: ");
                scanf("%s",name);
                printf("\n\t\t\t\t\t\t\tEnter Food Price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew Food Is Added To The List!!\n\n");
                break;
            case 3:
                if(deleteadmin())
                {
                    printf("\n\t\t\t\t\t\t### Updated List Of Food Menu ###\n");
                    displayList(heada);
                }
                else
                    printf("\n\t\t\t\t\t\tOOPS !! Sorry This Food Is Not Present In Today's Kitchen !!\n\n");

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(heada);
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease Choose Valid Option\n");
                break;
        }
    }
}

void customer()
{
	system("cls");
	system("Color F0");
    int flag=0,j=1;
    char ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                main_flag=1;
                displayList(heada);
                printf("\n\t\t\t\t\t\tEnter Code No. Of The Food You Want To Order: ");
                int n;
                scanf("%d",&n);
                printf("\n\t\t\t\t\t\tEnter Quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ### List Of Ordered Food ###\n");
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n\t\t\t\t\t\t### Updated List Of Your Order ###\n");
                    displayList(headc);
                }
                else
                    printf("\n\t\t\t\t\t\t!! This Was Not The Food , You Ordered !!\n");
                break;
            case 4:
                if(main_flag==1)
                {
                    calculatetotsales();
                    printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
                    displaybill();
                    headc = deleteList(headc);
                    printf("\n\t\t\t\t\t\t!! Press Any Key To Return To MAIN MENU: !!\n\t\t\t\t\t\t");
                    fflush(stdin);
                    ch=fgetc(stdin);
                    flag=1;
                }
                else
                {
                    printf("\n|t\t\t\t\t\t\t\t !! Please Place Your Order !!\n");
                }
                main_flag=0;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease Choose Valid Option\n");
                break;
        }
        if(flag==1)
            break;
    }
}

void mainmenu()
{
	system("cls");
	system("Color F3");
    printf("\n \t                                      *******************************************\n");
    printf("  \t                                        WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n");
    printf("\t                                      *******************************************\n\n\n");
    printf("\n\t\t\t\t\t!!! DON'T WASTE FOOD , SOMEONE IS SLEEPING EMPTY STOMACH !!!");
    printf("\n\n\n\t\t\t\t\t\t\t1. ADMIN SECTION \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION \n");
    printf("\t\t\t\t\t\t\t3. Exit \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");

}

int main()
{
	system("Color F3");
    heada = createadmin(heada,123,"Hot and Sour Soup",100);
    heada = createadmin(heada,234,"Manchow Soup",200);
    heada = createadmin(heada,435,"Manchurian Noodles",150);
    heada = createadmin(heada,456,"Fried Rice",180);
    heada = createadmin(heada,678,"Hakka Noodles",80);

    while(1)
    {
        mainmenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
        	system("cls");
        	system("Color F0");
            printf("\n\n\n\n\n\n\t\t\t\t\t\t\t*Thank you!!*\n");
            printf("\n\n\t\t\t\t\t\t*!! Please Visit Again !!*\n");
            break;
        }

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}
