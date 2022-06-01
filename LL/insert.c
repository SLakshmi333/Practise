#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *next;
};
struct node *head, *newnode,*temp;
void initialize(){
	head=NULL;
}
void create(){
	int choice;
	while(choice){
	newnode=(struct node*)malloc(sizeof(struct node));
	printf("enter the data:\n");
	scanf("%d",&newnode->data);
	newnode->next=NULL;
	if(head==NULL){
		temp=head=newnode;
	}
	else{
		temp->next=newnode;
		temp=newnode;
	}
	printf("Do you want to continue (0,1)?");
	scanf("%d",&choice);
}
}
int print(){
	temp=head;
	if(temp==NULL)
		printf("list is empty\n");
	else{
		while(temp!=NULL){
			printf("%d->",temp->data);
			temp=temp->next;
		}
	}
	printf("NULL\n");
}
void add_begin(){
	newnode=(struct node*)malloc(sizeof(struct node));
	printf("Enter the data you want to add at begining:\n");
	scanf("%d",&newnode->data);
	newnode->next=head;
	head=newnode;
}
void add_end(){
	newnode=(struct node*)malloc(sizeof(struct node));
	printf("Enter the data you want to add at ending:\n");
	scanf("%d",&newnode->data);
	newnode->next=NULL;
	temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=newnode;
}
int length(){
	int count=0;
	temp=head;
	while(temp!=0){
		count++;
		temp=temp->next;
	}printf("%d",count);
}
void add_atpos(){
	 int count=0;
        temp=head;
        while(temp!=0){
                count++;
                temp=temp->next;
        }printf("%d",count);

	int pos,i=1;
	printf("Enter the position at which you want to add data");
	scanf("%d",&pos);
//	length();
	newnode=(struct node*)malloc(sizeof(struct node));
	if(pos>count)
		printf("not valid position");
	else
	{
		temp=head;
		while(i<pos){
			temp=temp->next;
			i++;
		}
		printf("enter the data to add at pos %d",pos);
		scanf("%d",&newnode->data);
		newnode->next=temp->next;
		temp->next=newnode;
	}
}
int main(){
	printf("single linked list creation\n");
	initialize();
	create();
	printf("displaying the data\n");
	print();
	add_begin();
	add_end();
	add_atpos();
	print();
	printf("Length of list is: ");
	length();
	printf("\n");
	return 0;
}
