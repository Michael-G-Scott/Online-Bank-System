#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
struct user{
char ph[10];
char acc[50];
char pswd[15];
float balance;
};
int main(){
	struct user u,u1;
	int opt,choice;
	float temp_amount;
	FILE *fp;
	char filename[50],filename1[50],phone[10]={'\0'},pswd[50],cont='y',phone1[10];
	printf("Hi! How can I help you ?\nPress 1 to register an account\nPress 2 to login to your account\n");
	scanf("%d",&opt);
	if(opt==1){
	system("clear");
	printf("Enter your account number:\t");
	scanf("%s",u.acc);
	printf("Enter your phone number:\t");
	scanf("%s",u.ph);
	printf("Enter your account password:\t");
	scanf("%s",u.pswd);
	u.balance=0.0;
	strcpy(filename,u.ph);
	fp=fopen(strcat(filename,".dat"),"w");
	fwrite(&u,sizeof(struct user),1,fp);
	if(fwrite!=0){
		printf("\nACCOUNT REGISTRATION SUCCESSFUL!\n");
		}
	else{
		printf("\nSomething went wrong,please try again\n");
		}
	fclose(fp);
	}
	if(opt==2){
	system("clear");
	printf("Enter your phone number:  ");
	scanf("%s",phone);
	printf("Enter your password:      ");
	scanf("%s",pswd);
	strcpy(filename,phone);
	fp=fopen(strcat(filename,".dat"),"r");
	if(fp==NULL){
		printf("Account Not Registered!");
		return 0;
		}
	fread(&u,sizeof(struct user),1,fp);
	fclose(fp);
	if(!strcmp(pswd,u.pswd)){
		while(cont=='y'){
		system("clear");
		printf("\nPress 1 to check balance");
		printf("\nPress 2 to deposit cash");
		printf("\nPress 3 to withdraw cash");
		printf("\nPress 4 to transfer cash");
		printf("\nPress 5 to change password");
		printf("\nYour choice: ");
		scanf("%d",&choice);
		switch (choice){
			case 1:
				printf("\n\nYour current balance is Rs.%.2f",u.balance);
				break;
			case 2:
				printf("\nEnter the amount to be deposited in the format Rupees.Paisa: ");
				scanf("%f",&temp_amount);
				u.balance+=temp_amount;
				fp=fopen(filename,"w");
				fwrite(&u,sizeof(struct user),1,fp);
				if(fwrite!=NULL){
					printf("\nSuccessfully deposited");
				}
				else{
					printf("\n\nSomething went wrong.Try again");
				}
				fclose(fp);
				break;
			case 3:
				printf("\nEnter the amount to be withdrawn in the format Rupees.Paisa: ");
				scanf("%f",&temp_amount);
				if(temp_amount>u.balance){
				printf("\nInsufficient balance");
				}
				else{
				u.balance-=temp_amount;
				fp=fopen(filename,"w");
				fwrite(&u,sizeof(struct user),1,fp);
				if(fwrite!=NULL){
					printf("\nSuccessfully withdrawn");
				}
				else{
					printf("\nSomething went wrong try again");
				}
				fclose(fp);
				}
				break;
			case 4:
				printf("\nEnter the phone number to transfer the money to:  ");
				scanf("%s",phone1);
				printf("\nPlease enter the amount to be transferred in the format Rupees.Paisa: ");
				scanf("%f",&temp_amount);
				if(temp_amount>u.balance){
					printf("\nInsufficient balance");
				}
				else{
					strcpy(filename1,phone1);
					fp=fopen(strcat(filename1,".dat"),"r");
					if(fp==NULL){printf("Account not registered");return 0;}
					fread(&u1,sizeof(struct user),1,fp);
					fclose(fp);
					fp=fopen(filename1,"w");
					u1.balance+=temp_amount;
					fwrite(&u1,sizeof(struct user),1,fp);
					fclose(fp);
					if(fwrite!=NULL){
						printf("\nTransaction Successful");
						strcpy(filename,u.ph);
						fp=fopen(strcat(filename,".dat"),"r");
						fread(&u,sizeof(struct user),1,fp);
						u.balance-=temp_amount;
						fwrite(&u,sizeof(struct user),1,fp);
						fclose(fp);
					}
					else{
						printf("\nSomething went wrong, try again");
					}
				}
				break;
			case 5:
				printf("Please enter your new password: ");
				scanf("%s",pswd);
				fp=fopen(filename,"w");
				strcpy(u.pswd,pswd);
				fwrite(&u,sizeof(struct user),1,fp);
				fclose(fp);
				if(fwrite!=NULL){
					printf("\nPassword changed successfully");
				}
				break;
			default: printf("\nInvalid choice");
			}
			printf("\n\nDo you want to continue ? [y/n] ");
			scanf("%s",&cont);
		}
		}
	else{
		printf("\nINVALID PASSWORD");
		}
	}
}
