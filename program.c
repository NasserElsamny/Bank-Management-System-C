#include<stdio.h>
#include"STD_TYPES.h"
#include"interface.h"
#include<stdlib.h>
#include <time.h>
#include <string.h>


u32 Bank_u32Welcome(void)
{	
	u32 admin=0;
	printf("Welcome To ITI Bank\n");
	
	//Ask to choose if admin or client
	printf("Please choose 1 for Admin or 2 for Client:\n");
	scanf("%d",&admin);
	
	//Check validity of User's choice
	while((admin < 1) || (admin > 2))
	{
		printf("Wrong choice\n");
		printf("Please choose 1 for Admin or 2 for Client:\n");
		scanf("%d",&admin);
	}		
	return admin;
}

void Bank_u32AdminLogin(void)
{
	printf("Welcome to Admin window\n\n");
	u8 admin_username[20];
	u8 admin_password[20];
	
	//Ask admin to enter username and password
	printf("Username: ");
	scanf(" %20s",&admin_username);
	printf("Password: ");
	scanf(" %20s",&admin_password);
	
	//Check for Admin's username and password
	u8 CheckUsername = Bank_u8Check(admin_username , "admin"); 
	u8 CheckPassword = Bank_u8Check(admin_password , "Admin1234"); 
	while((CheckUsername != 0) || (CheckPassword != 0))
	{
		printf("Wrong username or password\n");
		printf("Please try again\n");
		printf("Username: ");
		scanf(" %s",&admin_username);
		printf("Password: ");
		scanf(" %s",&admin_password);
		CheckUsername = Bank_u8Check(admin_username , "admin"); 
		CheckPassword = Bank_u8Check(admin_password , "Admin1234"); 
	}
	printf("Login Successful\n");
}

u32 Bank_u32AdminMainMenu(void)
{
	//Choose from options in Admin window
	u32 AdminChoice = 0;
	printf("Enter 1 to Create New Account\n");
	printf("Enter 2 to Open Existing Account\n");
	printf("Enter 3 to Exit System\n");
	scanf("%d",&AdminChoice);
	//Check for Admin's choice
	while(AdminChoice < 1 || AdminChoice > 3)
	{
		printf("Invalid input please try again\n");
		printf("Enter 1 to Create New Account\n");
		printf("Enter 2 to Open Existing Account\n");	
		printf("Enter 3 to Exit System\n");
		scanf("%d",&AdminChoice);
	}
	return AdminChoice;
}
	
u8 Bank_u8Check(u8 a[],u8 b[])  
{  
	//Function to compare 2 strings
    u8 flag=0,i=0;    
    
	while(a[i]!='\0' || b[i]!='\0') 
    {  
       if(a[i]!=b[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    }  
    if(flag==0)  
    return 0;  
    else  
    return 1;  
}  

void Bank_vCreateFirstAccount(BankAccount* ptr)
{
	printf("Create first bank account\n");
	printf("Full Name: ");
	fflush(stdin);
	gets(ptr->Full_Name);
	printf("Full Address: ");
	fflush(stdin);
	gets(ptr->Full_Address);
	
	printf("National ID: ");
	scanf("%llu",&ptr->NationalID);
	while((ptr->NationalID < 10000000000000) || (ptr->NationalID > 99999999999999))
	{
		printf("Wrong input, National ID must be a 14 digits number: ");
		scanf("%llu",&ptr->NationalID);
	}
	
	printf("Age: ");
	scanf("%d",&ptr->Age);
	ptr->BankAccountID = 1000000000;
	if((ptr->Age) < 21)
	{
		printf("Guardian Name: ");
		fflush(stdin);
		gets(ptr->Guardian_Name);
		printf("Guardian National ID: ");
		scanf("%llu",&ptr->GuardianNationalID);
		while((ptr->GuardianNationalID < 10000000000000) ||(ptr->GuardianNationalID > 99999999999999))
		{
			printf("Wrong input, National ID must be a 14 digits number: ");
			scanf("%llu",&ptr->GuardianNationalID);
		}
	}	
	else
	{
		strcpy(ptr->Guardian_Name , "None");
		ptr->GuardianNationalID = 0;
	}
	strcpy(ptr->AccountStatus , "Active");
	printf("Balance: ");
	scanf("%llu",&ptr->Balance);
	Bank_vGenerateRandomPassword(ptr->Password); 
	ptr->Link = NULL;
	printf("Account created successfully\n\n");
	
}

void Bank_vCreateNewAccount(BankAccount* head)
{
	BankAccount* first = head;
	BankAccount* ptr = (BankAccount*)malloc(sizeof(BankAccount));
	while(first->Link != NULL)
	{
		first = first->Link;
	}
	first->Link = ptr;
	

	printf("Full Name: ");
	fflush(stdin);
	gets(ptr->Full_Name);
	printf("Full Address: ");
	fflush(stdin);
	gets(ptr->Full_Address);
	
	printf("National ID: ");
	scanf("%llu",&ptr->NationalID);
	while((ptr->NationalID < 10000000000000) || (ptr->NationalID > 99999999999999))
	{
		printf("Wrong input, National ID must be a 14 digits number: ");
		scanf("%llu",&ptr->NationalID);
	}
	
	printf("Age: ");
	scanf("%d",&ptr->Age);
	static u32 FirstBankAccountID = 1000000001;
	ptr->BankAccountID = FirstBankAccountID;
	FirstBankAccountID++;
	if((ptr->Age) < 21)
	{
		printf("Guardian Name: ");
		fflush(stdin);
		gets(ptr->Guardian_Name);
		printf("Guardian National ID: ");
		scanf("%llu",&ptr->GuardianNationalID);
		while((ptr->GuardianNationalID < 10000000000000) ||(ptr->GuardianNationalID > 99999999999999))
		{
			printf("Wrong input, National ID must be a 14 digits number: ");
			scanf("%llu",&ptr->GuardianNationalID);
		}
	}	
	else
	{
		strcpy(ptr->Guardian_Name , "None");
		ptr->GuardianNationalID = 0;
	}
	strcpy(ptr->AccountStatus , "Active");
	printf("Balance: ");
	scanf("%llu",&ptr->Balance);
	Bank_vGenerateRandomPassword(ptr->Password); 
	ptr->Link = NULL;
	printf("Account created successfully\n");
	printf("Redirecting to main menu...\n\n");
}

void Bank_vGenerateRandomPassword(char password[])
{
	int randomizer = 0;

	/* Seed the random-number generator
	 with current time so that the
	 numbers will be different every time*/
	
	srand((unsigned int)(time(NULL)));

	// Array of numbers
	char numbers[] = "0123456789";

	// Array of small alphabets
	char letter[] = "abcdefghijklmnoqprstuvwyzx";

	// Array of capital alphabets
	char LETTER[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";

	// Array of the special symbols
	char symbols[] = "!@#$&";

	// To select the randomizer inside the loop
	randomizer = rand() % 4;

	//Generate password of 12 random characters
	for (u8 i = 0; i < 12; i++) {

		if (randomizer == 1) {
			password[i] = numbers[rand() % 10];
			randomizer = rand() % 4;
			//printf("%c", password[i]);
		}
		else if (randomizer == 2) {
			password[i] = symbols[rand() % 5];
			randomizer = rand() % 4;
			//printf("%c", password[i]);
		}
		else if (randomizer == 3) {
			password[i] = LETTER[rand() % 26];
			randomizer = rand() % 4;
			//printf("%c", password[i]);
		}
		else {
			password[i] = letter[rand() % 26];
			randomizer = rand() % 4;
			//printf("%c", password[i]);
		}
	}
	password[12] = '\0';
}

void Bank_vShowAccountInfo(BankAccount* account)
{
	//Function to print account information
	printf("Full Name: %s\n",account->Full_Name);
	printf("Full Address: %s\n",account->Full_Address);
	printf("National ID: %llu\n",account->NationalID);
	printf("Age: %d\n",account->Age);
	printf("Bank Account ID: %d\n",account->BankAccountID);
	printf("Guardian: %s\n",account->Guardian_Name);
	printf("Guardian National ID: %llu\n",account->GuardianNationalID);
	printf("Account Status: %s\n",account->AccountStatus);
	printf("Balance: $%d\n",account->Balance);
	printf("Password: %s\n",account->Password);
	printf("\n");

}

BankAccount* Bank_pOpenExistingAccount(BankAccount* head)
{
	u32 accountID;
	u8 flag = 0; //flag to check validity of account ID
	
	EnterAccountID:
	printf("Enter Bank Account ID:");
	scanf("%d",&accountID);
	
	BankAccount* ptr = head;
	while(ptr != NULL)
	{
		//Check if account ID exist
		if(ptr->BankAccountID == accountID)
		{
			flag = 1;
			break;
		}
		ptr = ptr->Link;
	}
	if(flag == 0)
	{
		//In case of invalid account ID ask to enter again
		printf("Wrong Account ID.\n");
		goto EnterAccountID;
	}
	return ptr;
}

u8 Bank_u8ExistingAccountOptions(void)
{
	u32 flag=0;
	u8 choice;
	//Ask admin to choose one of available options and check choice's validity
	do
	{
		if (flag == 1)
		{
			printf("Invalid input\n");
		}
		printf("Choose one of the options below:\n");
		printf("Enter 1 to Make Transaction\n");
		printf("Enter 2 to Change Account Status\n");
		printf("Enter 3 to Get Cash\n");
		printf("Enter 4 to Deposit in Account\n");
		printf("Enter 5 to Show Account Details\n");
		printf("Enter 6 to Return to Main Menu\n");
		scanf("%d",&choice);
		flag = 1;
	}while((choice < 1) || (choice > 6));
	printf("\n");
	return choice;
}

void Bank_vExit(void)
{
	
	printf("\nSigned Out\n");
	printf("Thank you\n\n");
}

void Bank_vGetCash(BankAccount* ptr)
{	
	u64 cash = 0;
	u8 repeat = 'n';

		//Ask admin to enter cash amount
		printf("Enter cash amount:");
		scanf("%llu",&cash);
		
		//Check if cash less than balace
		if((cash) < (ptr->Balance))
		{
			ptr->Balance -= cash;
			printf("Successful\n\n");
			printf("Current Balance =$%d \n\n",ptr->Balance);
		}
		else
		{
			printf("There's is no enough balance\n\n");
		}
}

void Bank_vChangeAccountPassword(BankAccount* ptr)
{
	char new_password1[13];
	char new_password2[13];
	u8 check = 1;
	do
	{
		//Ask client to enter new password
		printf("Enter new password\n");
		scanf(" %12s",new_password1);
		//Ask client to enter new password again
		printf("Enter new password again\n");
		scanf(" %12s",new_password2);
		//Check if new password match
		check = Bank_u8Check(new_password1 , new_password2);
		if(check != 0)
		{
			printf("New password don't match please try again\n");
		}
	}while(check != 0);
	//Assign new password to account password
	strcpy(ptr->Password , new_password1);
	printf("Password changed successfully\n\n");
	
}

void Bank_vDeposit(BankAccount* ptr)
{
	u64 deposit = 0;
	printf("Enter deposit amount: \n");
	scanf("%d",&deposit);
	ptr->Balance += deposit; 
	printf("Deposit successful your new balance is $%d \n\n",ptr->Balance);
}

u32 Bank_u32CountAccounts(BankAccount* head)
{
	//Function to count number of existing bank accounts
	u32 count = 0;
	if(head == NULL)
	{
		printf("There are no accounts");
	}
	BankAccount* ptr = head;
	while(ptr != NULL)
	{
		count++;
		ptr = ptr->Link;
	}
	printf("Number of Accounts: %d\n",count);
	return count;
}

u8 Bank_u8MakeTransaction(BankAccount* head , BankAccount* sender)
{
	//Check if sender account is active
	if((Bank_u8Check(sender->AccountStatus , "Active")) != 0)
	{
		printf("Sender Account is not Active\n\n");
		return 0;
	}
	u32 receiverID;
	u64 money = 0;;
	u8 flag = 0; //flag to check validity of account ID
	
	EnterAccountID:
	//Enter receiver account ID
	printf("Enter Bank Account ID you want to transfer money to:");
	scanf("%d",&receiverID);
	
	BankAccount* receiver = head;

	//Loop to check validity of enter Account ID
	while(receiver != NULL)
	{
		//Check if account ID exist
		if(receiver->BankAccountID == receiverID)
		{
			flag = 1;
			break;
		}
		receiver = receiver->Link;
	}
	if(flag == 0)
	{
		//In case of invalid account ID ask to enter again
		printf("Wrong Account ID.\n");
		goto EnterAccountID;
	}
	
	//Check if receiver account is active
	if((Bank_u8Check(receiver->AccountStatus , "Active")) != 0)
	{
		printf("Receiver Account is not Active\n\n");
		return 0;
	}
	
	//Ask to enter amount of money to be transferred
	printf("Enter amount of money to send: ");
	scanf("%llu",&money);
	
	//Check if sender have enough balance
	if(money < sender->Balance)
	{
		sender->Balance -= money;
		receiver->Balance +=  money;
		printf("Transaction Successful\n\n");
	}
	else
	{
		printf("Sorry you don't no enough balance\n\n");
	}
}

void Bank_vChangeAccountStatus(BankAccount* ptr)
{
	
	u32 state = 0;
	u8 flag = 0;
	
	//Ask admin to choose an Account State
	do
	{
		if(flag == 1)
		{
			printf("Invalid input please try again\n");
		}
		printf("Change Account status:\n");
		printf("Enter 1: Active State \n");
		printf("Enter 2: Restricted State \n");
		printf("Enter 3: Closed State \n");
		scanf("%d",&state);
		flag == 1;
	}while(state < 1 || state > 3);
	
	//Assign choosen state to Account State
	switch(state)
	{
		case 1: strcpy(ptr->AccountStatus , "Active"); break;
		case 2: strcpy(ptr->AccountStatus , "Restricted"); break;
		case 3: strcpy(ptr->AccountStatus , "Closed"); break;
	}
	printf("Account Status changed successfully\n");
	printf("Redirecting to main menu\n\n");
}

BankAccount* Bank_vClientLogin(BankAccount* head)
{
	
	u32 account_id;
	u8 client_password[13];
	
	BankAccount* ptr = head;
	u8 flag1 = 0;
	u8 flag2 = 0;
	printf("Welcome to Client Window\n\n");

	//Ask to enter and Account ID and check it's validity
	do
	{
		
		if(flag2 == 1)
		{
			printf("Incorrect Bank Account ID\n");
		}
		printf("Enter Bank Account ID:\n");
		scanf("%d",&account_id);
		
		ptr = head;
		while(ptr != NULL)
		{
			if(ptr->BankAccountID == account_id)
			{
				flag1 = 1;
				break;
			}
			else
			{
				ptr = ptr->Link;	
			}
		}
		flag2 = 1;
	}while(flag1 != 1);
	
	Bank_vShowAccountInfo(ptr);
	
	u8 CheckPassword = 1; //Flag to check if password is correct
	u8 flag3 = 0;
	do
	{
		if(flag3 == 1)
		{
			printf("Wrong Password\n");
		}
		printf("Enter Account Password: \n");
		scanf(" %12s" , &client_password);
		//Compare entered password with account password
		CheckPassword = Bank_u8Check(client_password , ptr->Password); 
		flag3 = 1;
	}while(CheckPassword != 0);
	
	printf("Login Successful\n\n");
	
	return ptr;
}

u32 Bank_u32ClientMainMenu(void)
{
	u32 flag=0;
	u8 choice;
	//Ask client to choose from available options and check choice's validity
	do
	{
		if (flag == 1)
		{
			printf("Invalid input\n");
		}
		printf("Choose one of the options below:\n");
		printf("Enter 1 to Make Transaction\n");
		printf("Enter 2 to Change Account Password\n");
		printf("Enter 3 to Get Cash\n");
		printf("Enter 4 to Deposit in Account\n");
		printf("Enter 5 to Show Account Details\n");
		printf("Enter 6 to Return to Main Menu\n");
		printf("Enter 7 to Exit System\n");
		scanf("%d",&choice);
		flag = 1;
	}while((choice < 1) || (choice > 7));
	printf("\n");
	return choice;
}