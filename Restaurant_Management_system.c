#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL,*newnode,*tailc = NULL;	// pointers to maintain customer linked list
struct node *heada = NULL, *taila = NULL;	// pointers to maintain admin linked list
struct node *head_s;


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
        printf("\nThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        printf("\nList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
                printf("%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else
            {
                printf("%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
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

struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\nList is empty\n");
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
    printf("\nEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

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
    printf("\nEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

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
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("Total price: %0.02f\n",total_price);

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
    printf("\n----------------------------------------------\n");
    printf("		ADMIN SECTION				");
    printf("\n----------------------------------------------\n");
    while(1)
    {
    

    	printf("\n1. View total sales");
    	printf("\n2. Add new items in the order menu");
    	printf("\n3. Delete items from the order menu");
    	printf("\n4. Display order menu");
    	printf("\n5. Back To Main Menu \n\n");
    	printf("Enter Your Choice :");



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

                printf("\nEnter serial no. of the food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\nFood item with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("Enter food item name: ");
                scanf("%s",name);
                printf("Enter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\nNew food item added to the list!!\n\n");
                break;
                
            case 3:
                if(deleteadmin())
                {
                    printf("\nUpdated list of food items menu :\n");
                    displayList(heada);
                }
                else
                    printf("\nFood item with given serial number doesn't exist!\n\n");

                break;
                
            case 4:
                printf("\nOrder menu :\n");
                displayList(heada);
                break;

            default:
                printf("\nInvalid option : Please choose valid option\n");
                break;
        }
    }
}

void customer()
{
    int flag=0,j=1;
    char ch;
    printf("\n----------------------------------------------\n");
    printf("		CUSTOMER SECTION			");
    printf("\n----------------------------------------------\n");
    while(1)
    {
        printf("\n1. Place your order");
    	printf("\n2. View your ordered items");
    	printf("\n3. Delete an item from order");
    	printf("\n4. Display final bill");
    	printf("\n5. Back To Main Menu \n\n");
    	printf("Enter Your Choice :");


        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                printf("\nEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("Enter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
                
            case 2:
                printf("\nList of ordered items\n");
                displayList(headc);
                break;
                
            case 3:
                if(deletecustomer())
                {
                    printf("\nUpdated list of your ordered food items \n");
                    displayList(headc);
                }
                else
                    printf("\nFood item with given serial number doesn't exist!!\n");
                break;
                
            case 4:
                calculatetotsales();
                printf("\nFinal Bill\n");
                displaybill();
                headc = deleteList(headc);
                printf("\nPress any key to return to main menu:\n");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\nInvalid Input !! Please choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}

void mainmenu()
{
    printf("\n***RESTAURANT MANAGEMENT SYSTEM***\n\n");
    printf("1. Admin Section \n");
    printf("2. Customer Section \n");
    printf("3. Exit\n\n");
    printf("Enter Your Choice :");
}

int main()
{
    heada = createadmin(heada,1,"Chana Bhatura",100);
    heada = createadmin(heada,2,"Large Pizza",200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice",180);
    heada = createadmin(heada,5,"Spring Roll",80);
    heada = createadmin(heada,6,"Momos",80);
    
    while(1)
    {
        mainmenu();
        int choice;
        scanf("%d",&choice);
        
        if(choice==3)
        {
        	printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
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
            
            default:
                printf("\nInvalid input !! PLease choose valid option\n");
                break;
        }
    }
    return 0;
}
