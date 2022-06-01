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
int main(){
	printf("single linked list creation\n");
	initialize();
	create();
	printf("displaying the data\n");
	print();
	return 0;
}
