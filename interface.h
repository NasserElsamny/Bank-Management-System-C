

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include"STD_TYPES.h"

typedef struct Account_t
{
	u8 Full_Name[100];
	u8 Full_Address[100];
	unsigned long long int NationalID;
	u16 Age;
	u32 BankAccountID;
	u8 Guardian_Name[100];
	u64 GuardianNationalID;
	u8 AccountStatus[10];
	u64 Balance;
	u8 Password[13]; 
	struct Account_t* Link;
	
}BankAccount;


u32 Bank_u32Welcome(void);
void Bank_u32AdminLogin(void);
u32 Bank_u32AdminMainMenu(void);
u8 Bank_u8Check(u8 a[],u8 b[]); 
void Bank_vCreateFirstAccount(BankAccount*);
void Bank_vCreateNewAccount(BankAccount*);
void Bank_vExit(void);
void Bank_vGenerateRandomPassword(char password[]);
void Bank_vShowAccountInfo(BankAccount*);
BankAccount* Bank_pOpenExistingAccount(BankAccount* head);
void Bank_vGetCash(BankAccount*);
void Bank_vChangeAccountPassword(BankAccount*);
void Bank_vDeposit(BankAccount*);
u32 Bank_u32CountAccounts(BankAccount* head);
u8 Bank_u8ExistingAccountOptions(void);
void Bank_vChangeAccountStatus(BankAccount*);
u8 Bank_u8MakeTransaction(BankAccount*, BankAccount*);
BankAccount* Bank_vClientLogin(BankAccount*);
u32 Bank_u32ClientMainMenu(void);

#endif