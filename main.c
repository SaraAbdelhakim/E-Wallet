#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int year, month, day;
}Date;

void date_print(Date d)
{
    printf("%4d/%02d/%02d", d.year, d.month, d.day);
}

//structure containing the data of one input
struct node
{
    Date date;
    char category[15];
    double amount;
    struct node *next;
}*income=NULL, *expense=NULL;


struct record
{
    double x,y;
}*ph=NULL;

//creating new inputs
void insert(Date d, char* c, double m, struct node** p_node)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* p;
    if(*p_node==NULL)
    {
        new_node->date = d;
        strcpy(new_node->category,c);
        new_node->amount = m;

        new_node->next=NULL;
        *p_node=new_node;
    }

    else
    {
        p= *p_node;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        new_node->date = d;
        strcpy(new_node->category,c);
        new_node->amount = m;

        new_node->next=NULL;
        p->next=new_node;
    }

}

//display the income and expense records
void show(int choice)
{
    char another = 'Y';
    if(choice==3)
    {
        while(another == 'Y' || another=='y')
        {
            FILE *fp1 = NULL;
            fp1 = fopen("income.bin", "rb");
            if(fp1 == NULL)
                printf("\nNo Data Available Yet.\n\n\n");  //at the beginning it will show this mesg cuz we haven't added any data yet

            else
            {
                struct node *p1 =income;
                while(p1!= NULL)
                {
                    printf("\nDate: ");
                    date_print(p1->date);
                    printf("\tCategory: %s\tAmount: %.2lf HUF", p1->category, p1->amount);
                    printf("\n");
                    p1= p1->next;
                }
            }
            printf("\n****************************************\n");
            printf("\Show again (Y/N) ");
            //flush the output buffer of the stream
            fflush(stdin);
            another = getche();
            printf("\n****************************************\n");
        }
    }
    if(choice==4)
    {
        while(another == 'Y' || another=='y')
        {
            FILE *fp2 = NULL;
            fp2 = fopen("expense.bin", "rb");
            if(fp2 == NULL)
                printf("\nNo Data Available Yet.\n\n\n");

            else
            {
                struct node *p2 =expense;
                while(p2!= NULL)
                {
                    printf("\nDate: ");
                    date_print(p2->date);
                    printf("\tCategory: %s\tAmount: %.2lf HUF", p2->category, p2->amount);
                    printf("\n");
                    p2= p2->next;
                }
            }
            printf("\n****************************************\n");
            printf("\Show again (Y/N) ");
            fflush(stdin);
            another = getche();
            printf("\n****************************************\n");
        }
    }
}

//save the income into the income file
void save_income(struct node *p)
{
    FILE *fp = NULL;
    fp = fopen("income.bin", "wb");
    if(fp==NULL)
    {
        printf("\nFailed to save income.");
    }
    else
    {
        struct node *p1=p;
        struct node *p2=NULL;
        while(p1!=NULL)
        {
            p2=p1->next;
            p1->next=NULL;
            fseek(fp,0,SEEK_END);
            fwrite(p1,sizeof(struct node),1,fp);

            p1->next=p2;
            p2=NULL;
            p1=p1->next;
        }
        fclose(fp);
        fp= NULL;
        printf("\nSaved Successfully.");
    }
}

//save the expense into the expense file
void save_expense(struct node *p)
{
    FILE *fp = NULL;
    fp = fopen("expense.bin", "wb");
    if(fp==NULL)
    {
        printf("\nFailed to save expense.");
    }
    else
    {
        struct node *p1=p;
        struct node *p2=NULL;
        while(p1!=NULL)
        {
            p2=p1->next;
            p1->next=NULL;
            fseek(fp,0,SEEK_END);
            fwrite(p1,sizeof(struct node),1,fp);

            p1->next=p2;
            p2=NULL;
            p1=p1->next;
        }
        fclose(fp);
        fp= NULL;
        printf("\nSaved Successfully.");
    }
}

//reading the data from income file
struct node* read_income(struct node *p)
{
    int i=0;
    FILE *fp = NULL;
    fp = fopen("income.bin", "rb");
    if(fp==NULL)
    {
        printf("\nFailed to Load income.");
    }
    else
    {
        delete_record(p);
        p=NULL;
        fseek(fp,0,SEEK_END);
        long fp_size=ftell(fp);
        rewind(fp);
        //calculates number of inputs or enteries
        int data=(int)(fp_size/(sizeof(struct node)));
        while(i!= data)
        {
            fseek(fp,(sizeof(struct node)*i),SEEK_SET);
            if(p==NULL)
            {
                p=(struct node *)malloc(sizeof(struct node));
                fread(p,sizeof(struct node),1,fp);
                p->next=NULL;
            }
            else
            {
                struct node *p1=p;
                struct node *p2=(struct node *)malloc(sizeof(struct node));
                while(p1->next!=NULL)
                {
                    p1=p1->next;
                }
                fread(p2,sizeof(struct node),1,fp);
                p1->next=p2;
                p2->next=NULL;
            }
            i++;
        }
    }
    return p;
}

//reading the data from expense file
struct node* read_expense(struct node *p)
{
    int i=0;
    FILE *fp = NULL;
    fp = fopen("expense.bin", "rb");
    if(fp==NULL)
    {
        printf("\nFailed to Load expense.");
    }
    else
    {
        delete_record(p);
        p=NULL;
        fseek(fp,0,SEEK_END);
        long fp_size=ftell(fp);
        rewind(fp);
        int data=(int)(fp_size/(sizeof(struct node)));
        while(i!=data)
        {
            fseek(fp,(sizeof(struct node)*i),SEEK_SET);
            if(p==NULL)
            {
                p=(struct node *)malloc(sizeof(struct node));
                fread(p,sizeof(struct node),1,fp);
                p->next=NULL;
            }
            else
            {
                struct node *p1=p;
                struct node *p2=(struct node *)malloc(sizeof(struct node));
                while(p1->next!=NULL)
                {
                    p1=p1->next;
                }
                fread(p2,sizeof(struct node),1,fp);
                p1->next=p2;
                p2->next=NULL;
            }
            i++;
        }
    }
    return p;

}

void delete_record(struct node* p)
{
    struct node *p1= p;
    struct node *p2 = NULL;
    while(p1!=NULL)
    {
        p2 = p1->next;
        free(p1);
        p1 = p2;
    }
}

void save_record(struct record *ph)
{
    FILE *fp;
    fp=fopen("record.bin","wb");
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        fwrite(ph,sizeof(struct record),1,fp);
    }
    else{
        printf("Cannot Save\n");
    }
    fclose(fp);
    fp=NULL;
}

struct record *read_record(void)
{
    FILE *fp;
    fp=fopen("record.bin","rb");
    struct record *p=NULL;

    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_SET);

        p=(struct record*)malloc(sizeof(struct record));
        fread(p,sizeof(struct record),1,fp);
    }
    else
    {
        printf("Cannot open\n");
    }
    return p;
}

double delete_income(struct node* ptr)
{
    double m;
    FILE *fp;
    fp = fopen("income.bin", "rb");
    struct node *temp= ptr;
    struct node *prev = NULL;
    while(temp->next)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    m = temp->amount;

    free(temp);
    printf("\nDeleted Successfully.");
    return m;
}

double delete_expense(struct node* ptr)
{
    double n;
    FILE *fp;
    fp = fopen("expense.bin", "rb");
    struct node *temp= ptr;
    struct node *prev = NULL;
    while(temp->next)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    n = temp->amount;

    free(temp);
    printf("\nDeleted Successfully.");
    return n;
}

int main()
{
    double amount, balance=0, income_curr=0, expense_curr=0;
    int choice;
    double m=0, n=0;
    char category[15], another, enter;
    Date d;

    FILE *fp_hist = NULL;
    fp_hist = fopen("record.bin", "rb");
    if(fp_hist!=NULL)
    {
        ph=read_record();
        income_curr=ph->x;
        expense_curr=ph->y;
    }
    else
        printf("\nCannot open.\n");

    FILE *fp_income = NULL;
    fp_income = fopen("income.bin", "rb");
    if(fp_income!=NULL)
        income=read_income(income);
    else
        printf("\nCannot open.\n");

    FILE *fp_expense = NULL;
    fp_expense = fopen("expense.bin", "rb");
    if(fp_expense!=NULL)
        expense=read_expense(expense);
    else
        printf("\nCannot open.\n");

    balance = (income_curr - expense_curr);
    do
    {
        system("COLOR CF");
        //clears the screen after each chosen option
        system("cls");
        printf("\n****************************************\n");
        printf("\nYour Current Income is: %.2lf HUF\n", income_curr);
        printf("Your Current Expense is: %.2lf HUF\n", expense_curr);
        printf("Your Current Balance is: %.2lf HUF\n", balance);
        printf("\n****************************************\n");

        printf("\nChoose an Option From The List Below: \n");
        printf("1. Add Income \n");
        printf("2. Add Expense \n");
        printf("3. Show Income Record \n");
        printf("4. Show Expense Record \n");
        printf("5. Delete Last income \n");
        printf("6. Delete Last expense \n");

        printf("7. Exit \n\n\n");
        printf("Your Option: ");
        scanf("%d", &choice);
        printf("\n****************************************\n");
        switch(choice)
        {
            case 1:
                another = 'Y';
                while(another == 'Y' || another=='y')
                {
                    printf("\nEnter the date of transaction (yyyy/mm/dd):  ");
                    scanf("%04d/%02d/%02d", &d.year, &d.month, &d.day);
                    printf("\nEnter Category: ");
                    scanf("%s", category);
                    printf("\nEnter Amount: ");
                    scanf("%lf", &amount);

                    //updating the current income value
                    income_curr+= amount;
                    //create new node with the data taken from the user
                    insert(d, category, amount, &income);
                    //then write them from the memory to the file to save them
                    save_income(income);
                    printf("\nAdd another Record (Y/N) ");
                    //clears the previous data from the input buffer
                    fflush(stdin);
                    //getche() waits until we type a character
                    another = getche();
                    printf("\n****************************************\n");
                }
                break;
            case 2:
                another = 'Y';
                while(another == 'Y' || another=='y')
                {
                    printf("\nEnter the date of transaction (yyyy/mm/dd):  ");
                    scanf("%04d/%02d/%02d", &d.year, &d.month, &d.day);
                    printf("\nEnter Category: ");
                    scanf("%s", category);
                    printf("\nEnter Amount: ");
                    scanf("%lf", &amount);

                    expense_curr+= amount;
                    insert(d, category, amount, &expense);
                    save_expense(expense);
                    printf("\nAdd another Record (Y/N) ");
                    fflush(stdin);
                    another = getche();
                    printf("\n****************************************\n");
                }
                break;
            case 3:
                printf("\nIncome History:  ");
                printf("\n****************************************\n");
                //display all the income records
                show(3);
                break;
            case 4:
                printf("\nExpense History:  ");
                printf("\n****************************************\n");

                show(4);
                break;
            case 5:
                another = 'Y';
                while(another == 'Y' || another=='y')
                {
                    m = delete_income(income);
                    income_curr-= m;
                    save_income(income);
                    printf("\nDelete another Record (Y/N) ");
                    fflush(stdin);
                    another = getche();
                    printf("\n****************************************\n");
                }
                break;
            case 6:
                another = 'Y';
                while(another == 'Y' || another=='y')
                {
                    n= delete_expense(expense);
                    expense_curr= expense_curr-n;
                    save_expense(expense);
                    printf("\nDelete another Record (Y/N) ");
                    fflush(stdin);
                    another = getche();
                    printf("\n****************************************\n");
                }
                break;
            case 7:
                //saving the values of income and expense before terminating the program
                ph=(struct record*)malloc(sizeof(struct record));
                ph->x=income_curr;
                ph->y=expense_curr;
                save_record(ph);
                printf("\nEND OF PROGRAM.\n");
                printf("\n****************************************\n");
                exit(0);
                break;
            default:
                printf("Please Select an Option from the List.\n");
                break;
        }

    }
    while(choice!=7);

    return 0;
}
