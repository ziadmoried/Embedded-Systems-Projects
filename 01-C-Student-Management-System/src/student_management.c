#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include<string.h>
#include <stdbool.h>

struct student{    //GLOBAL to easy use in any function
	int id;
	char name[50];
	int age;
	float gpa;

};
struct node{
	struct student data;
	struct node*next;
};



struct node*head=NULL;
//(functions)
int cont(void) ;
void add_new_student( const struct student *const ptr);
void display_list (void);
void search_student(int id);
void update_student(int id);
void Delete_student(int id);
void clean_all(void);
void calculate_avg_gpa(void);
void highest_gpa(void);
int main() {
	int flag = 1, option;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("Choose the option you need:\n");

	while (flag) {
		printf(
			"1) Add a student\n"
			"2) Display students\n"
			"3) Search for a student by ID\n"
			"4) Update student information\n"
			"5) Delete a Student\n"
			"6) Calculate Average GPA\n"
			"7) Find Student with Highest GPA\n"
			"8) Exit\n"
		);

		scanf("%d", &option);

		switch (option) {
			case 1: {
				struct student new_student;
				printf("Enter ID:  \n");
				scanf("%d", &new_student.id);
				printf("Enter name:  \n");
				scanf("%s", new_student.name);
				printf("Enter age: \n");
				scanf("%d", &new_student.age);
				printf("Enter GPA: \n");
				scanf("%f", &new_student.gpa);
				add_new_student(&new_student);
				break;
			}
			case 2:
				display_list();
				break;
			case 3: {
				int id;
				printf("Enter ID: \n");
				scanf("%d", &id);
				search_student(id);
				break;
			}
			case 4: {
				int id;
				printf("Enter ID to update: \n");
				scanf("%d", &id);
				update_student(id);
				break;
			}
			case 5: {
				int id;
				printf("Enter ID to delete: \n");
				scanf("%d", &id);
				Delete_student(id);
				break;
			}
			case 6:
				calculate_avg_gpa();
				break;
			case 7:
				highest_gpa();
				break;
			case 8:
				flag = 0; // Exit loop
				continue;
			default:
				printf("ERROR: Enter a valid option\n");
				break;
		}

printf("=========================================================\n");
		flag = cont();
	}
	clean_all();
	printf("======================================================\n");
	printf("# Thanks For Using Our System :) \n");

	return 0;
}





int cont(void) // mogard function 3shan kol ma a5ls as2lo akml w htb2a fe kolo
{

	int on,off=2;
	while(off==2){
		printf("do you need to continue if yes enter 1 if not enter 2 \n");
		printf("======================================================\n");
		scanf("%d",&on);
		if(on==1){
			off=1;
		}
		else if(on==2){
			off=0;
		}
		else{
			printf("ERROR \n");
		}
	}
	return off;
}

//////////
void add_new_student( const struct student *const ptr){

	struct node*ptr_node=head;//hat7ark beh w el head sabet;
	struct node*current=NULL;
	while(ptr_node !=NULL){
if(ptr->id==ptr_node->data.id) /*3shan el data mtkararsh kza mra
	                          (kan momken a5do fe function bra lw7do bs kda ashal 3shan el b3de mytl8btsh)*/
{
	printf("WARRNING: The data you have entered arealdy taken for another student enter new id \n ");
	return;
}
else{
	ptr_node=ptr_node->next;  //kml 3ady lw msh mtkarar
}

}
struct node* link=malloc(sizeof(struct node)); //hna ba7gz mkan le node gdeda

	link->data=(*ptr);
	link->next=NULL;
	if(head==NULL) //msh hat7sl 8er mra wa7da el hya awl mra el hya first node b3d kda el head msh hyb2a null tany
	{
		head=link;
		return;
	}
	current=head;
	while(current->next !=NULL) //loop with current to make it on the last node
	{
		current=current->next;
	}
	current->next=link; //3shan a3rf amsk node gdeda beh


}
/////////////////////////// here i displayed the data of students
void display_list (void){
	int pos=0;
	if(head==NULL)
		{
			printf("WARRNING : YOU HAVENT ENTERED DATA YET GO AND ENTER DATA FIRST \n");
		}
	struct node*ptr=head; //loop from head
	while(ptr !=NULL){

		printf("student postion is (%d) name : %s || ID : %.d  ||  AGE : %d  || GRADE : %.02f  \n",pos,ptr->data.name,ptr->data.id,ptr->data.age,ptr->data.gpa);
		ptr=ptr->next;
		pos++;
	}


}

/////////// here i search for student with his id

void search_student(int id){
	struct node*ptr=head;
	if(head==NULL)
	{
		printf("WARRNING : YOU HAVENT ENTERED DATA YET GO AND ENTER DATA FIRST \n");
	}
	else{
		while(ptr !=NULL){

			if(ptr->data.id ==id){

printf("student name : %s || ID : %d  ||  AGE : %d  || GRADE : %.02f  \n",ptr->data.name,ptr->data.id,ptr->data.age,ptr->data.gpa);
return;
			}

			else{ //3shan el pointer yt7ark lw mad5lsh fe if condtion
				ptr=ptr->next;
			}

		}

		printf("WARRNING : this id not on the system try again later \n");
		return;



	}


}
/////////////// h3ml update hna ha5od id w acces el mkan sa7eb id b3d ma aloop 3leh w ha8yr el gowah
void update_student(int id){
	int option;
	struct node*ptr=head;
	if(head==NULL){
		printf("WARRNING: NO DATA ON THE SYSTEM \n");
	}
	else{
	while(ptr !=NULL){

		if(ptr->data.id==id){
		printf("enter the option you need to adjust \n "
				"1)name   2)age 3)grade 0) Escape");
			scanf("%d",&option);
			switch(option){
			case 1:
				printf("Enter The new name \n");
				scanf("%s",ptr->data.name);
				break;
			case 2:
				printf("Enter The New age \n");
				scanf("%d",&(ptr->data.age));
				break;
			case 3:
				printf("Enter The new grade");
				scanf("%f",&(ptr->data.gpa));
			break;
			default:
				printf(" \n");
				return;
			}

	}

	        else
				ptr=ptr->next ;



	}

		printf("The ID is not on the system try again \n");
		return;

	}
}

void Delete_student(int id){

	struct node*ptr=head;
	struct node*del=head;
	if(head==NULL){
		printf("this id not in the system \n");
		return;
	}
	else if (ptr->data.id==id){
		head=head->next;
		free(ptr);

	}
	else{
		while(ptr ->next != NULL){

			if(ptr->next->data.id==id){
				del=ptr->next;
				ptr->next=ptr->next->next; //5leto ymsk node el b3d mamso7a
				free(del);
				return;
			}
			ptr = ptr->next; //increment






		}

		printf("This ID not on the system \n");
		return;

	}

}

void clean_all(void){
		struct node*ptr=head;
	if(head==NULL){
		printf("No data on the system arealdy \n");
		return;
	}
	                                   /* i looped here with head and every loop make ptr has address current adress
				                       then make head jump to the another one and ptr in his place then free the ptr */
	else{
		while(head!=NULL){

			ptr=head;
			head=head->next;
			free(ptr);


		}


	}

	}


void calculate_avg_gpa(void) {
		struct node*ptr=head;
		float sum=0,avg=0;
		int count=0;

		if(head==NULL){
			printf("NO data in the system \n");
		}
		else{
			while(ptr!=NULL){
				sum+=ptr->data.gpa;
				count++;
				ptr=ptr->next;

			}
			avg=sum/count;
			printf("The current average is : %f \n",avg);
			return;

		}




	}


void highest_gpa(void){
	struct node*ptr=head;
	struct student max =head->data;

	if(head==NULL){
		printf("No data in the system \n");
		return;
	}

	else{
			while(ptr != NULL){
				if (max.gpa < (ptr->data.gpa))
					max=ptr->data;
				ptr=ptr->next;
			}
			printf("Top Student: %s, ID: %d, Age: %d, GPA: %f\n",max.name,max.id,max.age,max.gpa);
			return;
		}


	}
