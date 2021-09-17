#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

 


struct accountUsers
{
	char name[24];
	char password[42];
	int locked;
};
struct accountUsers User[6];

 

void userProfile();
void adminProfile();

 

 

char name[24], password[42], admin_name[24], admin_password[42];
void UserDatabase()
{
	strcpy(User[0].name, "Chris");
	strcpy(User[0].password, "Wipro123");
	User[0].locked=0;

	strcpy(User[1].name, "Nivideni");
	strcpy(User[1].password, "Wipro123");
	User[1].locked=0;

	strcpy(User[2].name, "Bibin");
	strcpy(User[2].password, "Wipro123");
	User[2].locked=0;
	
	strcpy(User[3].name, "Gokila");
	strcpy(User[3].password, "Wipro123");
	User[3].locked=0;

	strcpy(User[4].name, "Krishna");
	strcpy(User[4].password, "Wipro123");
	User[4].locked=0;
    
	strcpy(admin_name, "admin");
	strcpy(admin_password, "admin");
}


int userLogin()
{
	UserDatabase();
	int again = 0;
	int canLogin=0;
	int loginAttempts = 0;
	char tryAgain = 'Y';

	login:
	while(tryAgain == 'Y' || tryAgain == 'y')
	{
		printf("\nEnter you name: ");
		scanf("%s", name);
		printf("\nenter password: ");
		scanf("%s", password);

		if(strcmp(name, admin_name) == 0 && strcmp(password, admin_password) == 0)
		{
			adminProfile();
		}
		else
		{
			for(int i=0; i<5; i++)
			{
				if (strcmp(User[i].name, name) ==0)
				{
					if(strcasecmp(User[i].password, password) == 0)
					{
						userProfile();
						canLogin=1;
					}
					else
					{
						loginAttempts+=1;
						if(loginAttempts >= 3 || User[i].locked == 1)
						{
							User[i].locked = 1;
							printf("Your account has been locked due to too many invalid login attempts\nTo login to your account enter the correct credentials\nIf you want to login again enter 1 or to exit enter 2");
							scanf("%d", &again);
							if(again == 1)
							{
								goto login;
							}
							else
							{
							 exit(0);
							}
						}
						printf("\nInvalid password\n Do you want to try again?\n1. Yes\n2. NO\nEnter 1 or 2");
						scanf("%d", &again);
						if(again == 1)
						{
							goto login;
						}
						else
						{
							main ();
						}
					}
				}
				else if (i==4)
				{
					printf("\nInvalid UserName\n Do you want to try again?\n1. Yes\n2. No\n(1 or 2):");
					scanf("%d", &again);
					if(again == 1)
					{
						tryAgain = 'Y';
					}
					else
					{
					main ();
					}
				}
			}
			
		}
	}
	return canLogin;
}

 


void adminProfile()
{
	/*system("cls");*/
	int transaction=1;
	while(transaction == 1)
	{
		/*system("cls");*/
		printf("\n ADMIN ACCOUNT\n");
		int option;
		printf("\nchoose what you want to do\n\n");

		 

		printf("1 - View Users\n");
		printf("2 - Unauthorised access Report \n");
		printf("3 - Logout\n");
		printf("---------------------------\n");
		printf("Your Choice: ");
		scanf("%d",&option);
		printf("---------------------------\n");
		/*system("cls");*/
		switch(option)
		{
		case 1:
			printf("\n \t\t Users List");
			printf("\n \t\t ----------\n");
			for(int i=0; i<=3; i++)
			{
				printf("\n \t\t %s \n", User[i].name);
			}
			break;
		case 2:
			printf("Unauthorised login attempts this month: 3");
			break;
		case 3:
			printf("\nUser Successfully logged out\n");
			main();
		}
		transaction=0;
		while(transaction!=1 && transaction!=2)
		{
			printf("do you want to continue session?\n");
			printf("1. yes 2. no\n");
			printf("--------------");
			printf("\nYour Choice: ");
			scanf("%d",&transaction);
			if(transaction!=1 && transaction!=2)
			{
				printf("invalid no.\nchoose between 1 and 2 only\n");
			}
			if(transaction == 2)
			{
				exit(0);
			}
			
		}
	}
}

 


void userProfile()
{
	/*system("cls");*/

	float draw,dep,transfer;
	float balance=5000;
	int account,account1,account2;
	int type = rand();
	int transaction=1;

	printf("\n\n---------------------------\n");

	while(transaction == 1)
	{
		int option;
		printf("\nchoose option\n");
		printf("---------------------------\n");
		printf("1. Enquiry\n");
		printf("2. Balance Update\n");
		printf("3. Money Transfer\n");
		printf("4. Logout\n");
		printf("---------------------------\n");
		printf("Your Choice: ");
		scanf("%d",&option);
		printf("---------------------------\n");
		/*system("cls");*/
		switch(option)
		{
			case 1:
				printf("current balance is: Rs %.2f\n\n",balance);
				break;
			case 2:
				printf("how much money to deposit:");
				scanf("%f",&dep);
				if(dep > 0 && dep<=20000)
				{
					printf("\n%.2fRs deposited in your account.\n\n",dep);
					balance+=dep;
				}
				else if(dep>20000)
				{
					printf("\nyou can't deposit that much amount.\n\n");
				}
				else
				{
					printf("\ninvalid amount\n");
				}
				break;
			case 3:
				printf("\n\t\tAccount You Want To Transfer: ");
				scanf("%d",&account2);
				if (isdigit(account2));
				{
					printf("\n **Account Number is invalid");
				}
				printf("\nhow much amount?: ");
				scanf("%f",&transfer);
				if(balance>=transfer)
				{
					printf("\nyour %.2fRs successfully transfered\n\n",transfer);
					balance-=transfer;
				}
				else
				{
					printf("\nyou do not have sufficient balance\n\n");
				}
				break;
			case 4:
				printf("\nUser Successfully Logged out\n");
				main();
			default:
				printf("invalid transaction\n");
		}
		transaction=0;
		while(transaction!=1 && transaction!=2)
		{
			printf("do you want to continue session?\n");
			printf("1. yes 2. no\n");
			printf("--------------");
			printf("\nYour Choice: ");
			scanf("%d",&transaction);
			if(transaction!=1 && transaction!=2)
			{
				printf("invalid no.\nchoose between 1 and 2 only\n");
			}
			if(transaction == 2)
			{
				exit(0);
			}
		}
	}
}

 

 


void main()
{
	int option;
	printf("\nEnter your option\n");
	printf("--------------");
	printf("\n1. User Login \n2. Admin Login\n3. Exit Application\n");
	printf("--------------\n");
	printf("\nYour Choice:\n ");
	scanf("%d",&option);
	if(option == 1 || option == 2)
	{
		userLogin();
	}
	else if(option == 3)
	{
		exit(0);
	}
	else
	{
		printf("Invalid option");
		main();
	}
	
	getch();
	// return(0);
} 