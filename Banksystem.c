/*
Bank management System in C
Made By - Devang Vijay Khetia
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct user 
{
	int accountnumber;
	char fname[50];
	char lname[50];
	unsigned long long int aadhar;
	int balance;
	char acctype[8];     //current or saving
	unsigned long long int mobnum;         //try with unsigned long long int
	int dob;            // Enter in DD-MM-YYYY format
	int pin;            //ATM PIN number (4 digit)
	char usrname[20];  //for logging in account
	char usrpass[20];     //for logging in account
};
struct user totacc[100];

void delay(int num_s)       // num_s is number of seconds
{
	int ms = 1000*num_s;
	clock_t start_time = clock();
	while(clock()<start_time+ms)
		;
}

int main()
{
	int opcode,i=0,g,genacc;
	char uname[20],upass[20],ask[2]="y",uask[5],newlname[50];
	int x,depmoney,withmoney,upin,payeemoney,payeeacc,contflag,modifyopcode,newpin;
	unsigned long long int newmobnum;
	printf("***************Welcome to Bank Services******************");
	while(1)
	{
	printf("\nSelect an operation to be performed:\n");
	printf("1. Create an account\n2. Sign in to your account\n");
	scanf("%d",&opcode);
	switch(opcode)
	{
		case 1:
			printf("Please enter your first name:\n"); //Name should as fname 
			scanf("%s",totacc[i].fname);
			printf("Please enter your last name:\n"); //Name should as fname 
			scanf("%s",totacc[i].lname);	
			printf("Please enter the type of account: [Current or Saving]\n");
			scanf("%s",totacc[i].acctype);
			printf("Please enter your aadhar card number:\n");
			scanf("%llu",&totacc[i].aadhar);
			//Setting initial balance = 0;
			totacc[i].balance=0;
			printf("Please enter your mobile number without country code:\n");
			scanf("%llu",&totacc[i].mobnum);
			printf("Please enter your date of birth as DD-MM-YYYY:\n");
			scanf("%d",&totacc[i].dob);
			srand(time(0));
			genacc = (rand()%100)+1;
			printf("Your Generated account number is %d\n",genacc);
			totacc[i].accountnumber = genacc;
			printf("Please set your 4 digit pin number:\n");
			scanf("%d",&totacc[i].pin);
			printf("Please create your username:\n");
			scanf("%s",totacc[i].usrname);
			printf("Please enter your password:\n");
			scanf("%s",totacc[i].usrpass);
			printf("Your request is being processed......\n");
			for(int p=0;p<3;p++)
			{
				delay(1);
			}
			printf("Account Created\n");
			i=i+1;
			break;
		case 2:
			label:
				printf("Please enter your username:\n");
				scanf("%s",uname);
				printf("Please enter your password:\n");
				scanf("%s",upass);
				for(int j=0;j<101;j++)
				{
					int b = strcmp(totacc[j].usrname,uname);
					int c = strcmp(totacc[j].usrpass,upass);
					if((b==0) && (c==0))
						{
							printf("Welcome %s %s\n",totacc[j].fname,totacc[j].lname);
							x=j;
							break;
						}
					else if(j==100)
					{
						printf("Incorrect credentials...\n");
						printf("Please try again\n");
						for(int l=0;l<1;l++)
						{
							delay(1);
						}
						goto label;
					}
				}
			int signop; //opcode for performing an operation
			do
			{
				printf("Please select the operation to be performed:\n");
				printf("1. Check balance\n2. Deposit money\n3. Withdraw money\n4. Transfer money\n5. Modify details\n6. View account details\n");
				scanf("%d",&signop);
				switch(signop)
				{
					case 1:
						// checking balance.
						printf("Available balance = %d\n",totacc[x].balance);
						break;
					case 2:
						//depositing money
						printf("Enter the amount to be deposited:\n");
						scanf("%d",&depmoney);
						totacc[x].balance+=depmoney;
						break;
					case 3:
						//withdrawing money 
						printf("Enter the amount to be withdrawed:\n");
						scanf("%d",&withmoney);
						if(totacc[x].balance - withmoney > 100)
						{
							printf("Please enter your ATM pin number:\n");
							scanf("%d",&upin);
							if(totacc[x].pin==upin)
							{
								printf("ATM pin number matched successfully\n");
								totacc[x].balance-=withmoney;
								// give delay of 2 seconds. Add this feature later
								printf("Amount successfully withdrawed\n");
								printf("Please collect your cash\n");
							}
							else
								printf("ATM pin number match failed\n");
						}
						else
							printf("Insufficient balance\n");
						break;
					case 4:
						//trnf();  transferring money to other account in the same bank
						printf("Please enter the account number of payee\n");
						scanf("%d",&payeeacc);
						printf("Please enter the amount to be transferred\n");
						scanf("%d",&payeemoney);
						printf("Checking payee details\n");
						for(g=0;g<101;g++)
						{
							//check payee details
							//proceed only if details matched else exit
							if(totacc[g].accountnumber == payeeacc)
							{
								printf("You are transferring %d Rs to %s %s\n",payeemoney,totacc[g].fname,totacc[g].lname);
								int l;
								for(l=0;l<3;l++)
								{
									delay(1);
								}
								printf("Transaction successful\n");
								break;
							}
							//break;
						}
						totacc[g].balance+=payeemoney;
						totacc[x].balance-=payeemoney;
						break;
					case 5:
						//modify details of particular account;
						printf("Which of the following details are to be modified?\n");
						printf("1. Last name (surname)\n2. Mobile number\n3ATM pin\n");
						scanf("%d",&modifyopcode);
						if(modifyopcode==1)
						{
							printf("Please enter the new surname:\n");
							scanf("%s",newlname); 
							strcpy(totacc[x].lname,newlname);
						}
						else if(modifyopcode==2)
						{
							printf("Please enter new mobile number without country code:\n");
							scanf("%llu",&newmobnum); 
							totacc[x].mobnum = newmobnum;
						}
						else if(modifyopcode==3)
						{
							printf("Please enter new 4 digit ATM pin number:\n");
							scanf("%d",&newpin);
							totacc[x].pin = newpin;
						}
						break;
					case 6:
						printf("Account number:       %d\n",totacc[x].accountnumber);
						printf("Account type:         %s\n",totacc[x].acctype);
						printf("Account Holder name:  %s %s\n",totacc[x].fname,totacc[x].lname);
						printf("Available balance is: %d\n",totacc[x].balance);
						printf("Mobile number:        %llu\n",totacc[x].mobnum);
						printf("Aadhar card number:   %llu\n",totacc[x].aadhar);
						printf("Date of Birth:        %d\n",totacc[x].dob);
						break;
					default:
						printf("Please enter a valid choice:\n");
						break;
				}
				printf("Do you want to perform any operation?[y/n]\n");
				scanf("%s",uask);
				contflag=strcmp(ask,uask);
				if(contflag==1)
				{
					printf("Logging out.......\n");
					for(int o=0;o<3;o++)
					{
						delay(1);
					}
					break;
				}
			}while(contflag==0);
			break;
		default:
			printf("Please Select the Correct Operation\n");
			break;
		}
	}
	return 0;
}
