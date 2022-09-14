#include<stdio.h>
#include"STD_TYPES.h"
#include"interface.h"
#include<stdlib.h>
#include <time.h>
#include <string.h>



int main(void)
{
	//Create first bank account
	BankAccount* head = (BankAccount*)malloc(sizeof(BankAccount));
	Bank_vCreateFirstAccount(head);
	
	//Pointer to Existing Account
	BankAccount* ExistingAccount = NULL; 
	
	//Variable to store Existing Account menu choice
	u8 ExistingAccountOption;
	
	//Choose Admin or Client window
	u32 AdminOrClient;
	Label0:
	AdminOrClient = Bank_u32Welcome();
	switch(AdminOrClient)
	{
		//Case 1 for Admin window
		case 1: Bank_u32AdminLogin();
				Label1: 
				switch(Bank_u32AdminMainMenu())
				{	
					//Case 1.1 to Creat New Account
					case 1: Bank_vCreateNewAccount(head); goto Label1; break;
					
					//Case 1.2 to Open Existing Account
					case 2: ExistingAccount = Bank_pOpenExistingAccount(head);
							Label2:
							ExistingAccountOption = Bank_u8ExistingAccountOptions();
							switch(ExistingAccountOption)
							{
								//Case 1.2.1 to Make Transaction
								case 1: Bank_u8MakeTransaction(head , ExistingAccount);
										goto Label2; break;
								
								//Case 1.2.2 to Change Account Status
								case 2: Bank_vChangeAccountStatus(ExistingAccount);
										goto Label2; break;
								
								//Case 1.2.3 to Get Cash
								case 3: Bank_vGetCash(ExistingAccount);
										goto Label2; break;
								
								//Case 1.2.4 to Deposit in Account	
								case 4: Bank_vDeposit(ExistingAccount);
										goto Label2; break;
								
								//Case 1.2.5 to Show Account Details
								case 5: Bank_vShowAccountInfo(ExistingAccount);
										goto Label2; break;
								
								//Case 1.2.6 to Return to Main Menu
								case 6: goto Label1; break;
							}
							break;
					
					//Case 1.3 to Exit System
					case 3: Bank_vExit(); goto Label0; break;
				}
		//Case 2 for Client window		
		case 2: 
				Label4:
				ExistingAccount = Bank_vClientLogin(head);
				Label3:
				switch(Bank_u32ClientMainMenu())
				{
					//Case 2.1 to Make Transaction
					case 1: Bank_u8MakeTransaction(head , ExistingAccount);
							goto Label3; break;
					
					//Case 2.2 to Change Account Password
					case 2: Bank_vChangeAccountPassword(ExistingAccount);
							goto Label3; break;
					
					//Case 2.3 to Get Cash		
					case 3: Bank_vGetCash(ExistingAccount);
							goto Label3; break;

					//Case 2.4 to Deposit in Account	
					case 4: Bank_vDeposit(ExistingAccount);
							goto Label3; break;

					//Case 2.5 to Show Account Details
					case 5: Bank_vShowAccountInfo(ExistingAccount);
							goto Label3; break;
					
					//Case 2.6 to Return to Main Menu
					case 6: goto Label4; break;
					
					//Case 2.7 to Exit System
					case 7: Bank_vExit(); goto Label0; break;
				}
				break;
	}
	
	return 0;
}