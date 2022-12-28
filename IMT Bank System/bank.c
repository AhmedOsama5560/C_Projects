#include "std_types.h"
#include "bank.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CLEAR "cls"

static uint64 generatedId = 1000000000 ;

typedef struct AccountNode
{
	uint8 	clientName[51] ;
    uint8 	clientAddress[51] ;
	uint64 	clientNationalId ;
	uint16 	clientAge ;
	uint64 	clientBankId ;
	uint8 	guardianName[51] ;
    uint64 	guardianNationalId ;
    uint8	bankAccountStatus ;
	uint64	clientBalance ;
	uint8	accountPassword[9] ;
	
	struct AccountNode * nextNodePtr ;
} AccountNode ;

/* Global linked list pointer */
AccountNode * headPtr = NULL ;

static uint8* randomPasswordGeneration ( void )
{
    // Initialize counter
    uint8 i = 0;
	
	// Stores the random password
	static uint8 password[9] = "" ;
  
    // Seed the random-number generator
    // with current time so that the
    // numbers will be different every time
    srand((uint32)(time(NULL)));
  
    uint8 numbers[] = "0123456789" ;	
    
    // Iterate over the range [0, 8]
    for ( i = 0 ; i < 9 ; i++ )
	{	
		password[i] = numbers [ rand() % 10 ] ;
    }
	password[8] = '\0' ;
	
	return password ;
}

static uint8 numOfWords ( uint8 * str )
{
	uint8 counter = 0 ;
	uint8 i = 0 ;
	while ( str[i] != '\0' )
	{
		if ( ' ' == str[i] && '\0' != str[i+1] && ' ' != str[i+1] )
		{
			counter++ ;
		}
		else
		{
			
		}
		i++ ;
	}
	return counter + 1 ;
}
static bool strAlldigits ( uint8 * str )
{
	uint8 i = 0 ;
	while ( str[i] != '\0' && str[i] >= '0' && str[i] <= '9' )
	{
		i++ ;
	}
	return str[i] == '\0' ;
}
static uint8 numOfDigits ( uint64 num )
{
	uint8 digitsCount = 0 ;
	while ( num != 0 )
	{
		num /= 10 ;
		digitsCount++ ;
	}
	return digitsCount ;
}
static void makeTransaction ( AccountNode * openAccountPtr )
{
	AccountNode * transactionAccountPtr = headPtr ;
	uint64 id ;
	uint64 moneyAmount ;
	
	printf ( "\n Enter ID of client you want to make transaction with : " ) ;
	scanf ( "%llu" , &id ) ;
	
	if ( openAccountPtr -> clientBankId == id )
	{
		printf ( "\n Invalid input. Input ID is the same as your ID.\n" ) ;
	}
	else
	{
		while ( transactionAccountPtr != NULL && transactionAccountPtr -> clientBankId != id )
		{
			transactionAccountPtr = openAccountPtr -> nextNodePtr ;
		}
		if ( transactionAccountPtr == NULL )
		{
			printf ( "\n ID is not found\n" ) ;
		}
		else if ( transactionAccountPtr -> bankAccountStatus == 'R' )
		{
			printf ( "\n Account of ID : %llu is in Restricted status. You cannot make transaction\n" , id ) ;
		}
		else if ( transactionAccountPtr -> bankAccountStatus == 'C' )
		{
			printf ( "\n Account of ID : %llu is in Closed status. You cannot make transaction\n" , id ) ;
		}
		else
		{
			printf ( "\n Enter the amount of money you want to transfer to account of ID %llu : " , id ) ;
			scanf ( "%llu" , &moneyAmount ) ;
			if ( openAccountPtr -> clientBalance < moneyAmount )
			{
				printf ( "\n Your balance is not enough to make this transaction\n" ) ;
			}
			else
			{
				openAccountPtr -> clientBalance			-= moneyAmount ;
				transactionAccountPtr -> clientBalance 	+= moneyAmount ;
				printf ( "\n %llu EGP has been transfered to %llu successfully\n" , moneyAmount , id ) ;
			}
		}
	}
	
	/* System pause */
	printf ( "\n Press any key to continue...\n" ) ;
	getchar();
	getchar();
}
static void changeAccountStatus ( AccountNode * openAccountPtr )
{
	uint8 userInput ;
	if ( 'A' == openAccountPtr -> bankAccountStatus )
	{
		printf ( "\n Account %llu is in Active status\n" , openAccountPtr -> clientBankId ) ;
		printf ( "\n Enter R to change status to Restricted status\n" ) ; 
		printf ( "\n Enter C to change status to Closed status\n" ) ;
		printf ( "\n Your choice : " ) ;
		scanf ( " %c" , &userInput ) ;
		if ( 'R' == userInput )
		{
			openAccountPtr -> bankAccountStatus = 'R' ;
			printf ( "\n Account status has been changed to Restricted status successfully\n" ) ;
		}
		else if ( 'C' == userInput )
		{
			openAccountPtr -> bankAccountStatus = 'C' ;
			printf ( "\n Account status has been changed to Closed status successfully\n" ) ;
		}
		else
		{
			printf ( "\n Invalid Choice\n" ) ;
		}
	}
	else if ( 'R' == openAccountPtr -> bankAccountStatus )
	{
		printf ( "\n Account %llu is in Restricted status\n" , openAccountPtr -> clientBankId ) ;
		printf ( "\n Enter A to change status to Restricted status\n" ) ; 
		printf ( "\n Enter C to change status to Closed status\n" ) ;
		printf ( "\n Your choice : " ) ;
		scanf ( " %c" , &userInput ) ;
		if ( 'A' == userInput )
		{
			openAccountPtr -> bankAccountStatus = 'A' ;
			printf ( "\n Account status has been changed to Active status successfully\n" ) ;
		}
		else if ( 'C' == userInput )
		{
			openAccountPtr -> bankAccountStatus = 'C' ;
			printf ( "\n Account status has been changed to Closed status successfully\n" ) ;
		}
		else
		{
			printf ( "\n Invalid Choice\n" ) ;
		}
	}
	else
	{
		printf ( "\n Account %llu is in Restricted status\n" , openAccountPtr -> clientBankId ) ;
		printf ( "\n Enter A to change status to Restricted status\n" ) ; 
		printf ( "\n Enter R to change status to Closed status\n" ) ;
		printf ( "\n Your choice : " ) ;
		scanf ( " %c" , &userInput ) ;
		if ( 'A' == userInput )
		{
			openAccountPtr -> bankAccountStatus = 'A' ;
			printf ( "\n Account status has been changed to Active status successfully\n" ) ;
		}
		else if ( 'R' == userInput )
		{
			openAccountPtr -> bankAccountStatus = 'R' ;
			printf ( "\n Account status has been changed to Restricted status successfully\n" ) ;
		}
		else
		{
			printf ( "\n Invalid Choice\n" ) ;
		}
	}
	
	/* System pause */
	printf ( "\n Press any key to continue...\n" ) ;
	getchar();
	getchar();
}
static void changeAccountPassword ( AccountNode * openAccountPtr )
{
	uint8 newPassword[9] ;
	printf ( "\n Enter your old password : " ) ;
	getchar();
	fgets ( newPassword , 9 , stdin ) ;
	if ( 0 != strcmp ( newPassword , openAccountPtr -> accountPassword ) )
	{
		printf ( "\n Incorrect password\n" ) ;
	}
	else
	{
		printf ( "\n Enter your new password : " ) ;
		getchar();
		fgets ( newPassword , 9 , stdin ) ;
		
		if ( 8 != strlen ( newPassword ) )
		{
			printf ( "\n Password must be 8 digits\n" ) ;
		}
		else if ( ! strAlldigits ( newPassword ) )
		{
			printf ( "\n Password must contain only numeric digits\n" ) ;
		}
		else
		{
			strcpy ( openAccountPtr -> accountPassword , newPassword ) ;
			printf ( "\n Password has been set to %s successfully\n" , openAccountPtr -> accountPassword ) ;
		}
	}
	
	/* System pause */
	printf ( "\n Press any key to continue...\n" ) ;
	getchar();
	getchar();
}
static void getCash ( AccountNode * openAccountPtr )
{
	uint64 moneyAmount ;
	
	printf ( "\n Enter the amount of money you want to get : " ) ;
	scanf ( "%llu" , &moneyAmount ) ;
	
	if ( openAccountPtr -> clientBalance < moneyAmount )
	{
		printf ( "\n Your balance is not enough to get this amount of money\n" ) ;
	}
	else
	{
		openAccountPtr -> clientBalance	-= moneyAmount ;
		printf ( "\n %llu EGP has been withdrawn successfully\n" , moneyAmount ) ;
	}
	
	/* System pause */
	printf ( "\n Press any key to continue...\n" ) ;
	getchar();
	getchar();
}

static void depositInAccount ( AccountNode * openAccountPtr )
{
	uint64 moneyAmount ;
	
	printf ( "\n Enter the amount of money you want to deposit : " ) ;
	scanf ( "%llu" , &moneyAmount ) ;
	
	openAccountPtr -> clientBalance	+= moneyAmount ;
	printf ( "\n %llu EGP has been deposited successfully\n" , moneyAmount ) ;
	
	/* System pause */
	printf ( "\n Press any key to continue...\n" ) ;
	getchar();
	getchar();
}

static void printBankAccount ( AccountNode * accountNodePtr )
{
	printf ( "\n Client's Information :" ) ;
	printf ( "\n\n Name                   : %s" 	, accountNodePtr -> clientName ) ;
	printf ( "\n\n Address                : %s" 	, accountNodePtr -> clientAddress ) ;
	printf ( "\n\n National ID            : %llu" 	, accountNodePtr -> clientNationalId ) ;
	printf ( "\n\n Age                    : %hu" 	, accountNodePtr -> clientAge ) ;
	if ( accountNodePtr -> clientAge < 21 )
	{
		printf ( "\n\n Guardian's Name        : %s" 	, accountNodePtr -> guardianName ) ;
		printf ( "\n\n Guardian's National ID : %llu" 	, accountNodePtr -> guardianNationalId ) ;
	}
	printf ( "\n\n Status                 : " ) ;
	if ( 'A' == accountNodePtr -> bankAccountStatus )
	{
		printf ( "Active" ) ;
	}
	else if ( 'R' == accountNodePtr -> bankAccountStatus )
	{
		printf ( "Restricted" ) ;
	}
	else
	{
		printf ( "Closed" ) ;
	}
	printf ( "\n\n Balance                : %llu" 	, accountNodePtr -> clientBalance ) ;
}

void createNewAccount ( void )
{
	/* Creating new account node */
    AccountNode * newNodePtr = ( AccountNode * ) malloc ( sizeof ( AccountNode ) ) ;
	
	/* If there is no sufficient memory , exit the function with failure return status */
    if ( newNodePtr == NULL )
    {
        printf ( "\n An error has occured\n" ) ;
    }
	else
	{
		printf ( "\n Enter new account information :\n" ) ;
		
		printf ( "\n Enter Client Name : " ) ;
		getchar() ;
		gets ( newNodePtr -> clientName ) ;
		
		while ( numOfWords ( newNodePtr -> clientName ) < 4 )
		{
			printf ( "\n Invalid name. Name must be full\n" ) ;
			printf ( "\n Enter Client Name : " ) ;
		
			gets ( newNodePtr -> clientName ) ;
		}
		
		
		printf ( "\n Enter Client Address : " ) ;
		gets ( newNodePtr -> clientAddress ) ;
		
		printf ( "\n Enter Client National ID : " ) ;
		scanf ( "%llu" , & newNodePtr -> clientNationalId ) ;
		
		while ( numOfDigits ( newNodePtr -> clientNationalId ) != 14 )
		{
			printf ( "\n National ID must contain 14 digits\n" ) ;
			printf ( "\n Enter Client National ID : " ) ;
			scanf ( "%llu" , & newNodePtr -> clientNationalId ) ;
		}
		
		printf ( "\n Enter Client Age : " ) ;
		scanf ( "%hu" , & newNodePtr -> clientAge ) ;
		
		if ( newNodePtr -> clientAge < 21 )
		{
			printf ( "\n Client's age is less than 21 years so there must be a guardian\n" ) ;
			
			printf ( "\n Enter Guardian Name : " ) ;
			getchar() ;
			gets ( newNodePtr -> guardianName ) ;
		
			while ( numOfWords ( newNodePtr -> guardianName ) < 4 )
			{
				printf ( "\n Invalid name. Name must be full\n" ) ;
				printf ( "\n Enter Guardian Name : " ) ;
			
				gets ( newNodePtr -> guardianName ) ;
			}
			
			printf ( "\n Enter Guardian National ID : " ) ;
			scanf ( "%llu" , & newNodePtr -> guardianNationalId ) ;
			
			while ( numOfDigits ( newNodePtr -> guardianNationalId ) != 14 )
			{
				printf ( "\n National ID must contain 14 digits\n" ) ;
				printf ( "\n Enter Guardian National ID : " ) ;
				scanf ( "%llu" , & newNodePtr -> guardianNationalId ) ;
			}
		}
		else
		{
			newNodePtr -> guardianNationalId = 0 ;
			strcpy ( newNodePtr -> guardianName , "" ) ;
		}
		
		newNodePtr -> clientBankId = generatedId ;
		newNodePtr -> bankAccountStatus = 'A' ;
		
		printf ( "\n Enter Client Initial Balance : " ) ;
		scanf ( "%llu" , & newNodePtr -> clientBalance ) ;
		
		strcpy ( newNodePtr -> accountPassword , randomPasswordGeneration() ) ;
			
		printf ( "\n New account has been successfully created\n" ) ;
		printf ( "\n Generated ID       : %llu\n" , newNodePtr -> clientBankId ) ; 
		printf ( "\n Generated Password : %s\n" , newNodePtr -> accountPassword ) ;
		generatedId++ ;
		
		
		newNodePtr -> nextNodePtr = headPtr ;
		headPtr = newNodePtr ;
	}
	
	printf ( "\n Press any key to continue...\n" ) ;
	getchar();
	getchar();
	
}

void openExistingAccountByAdmin	( void )
{
	AccountNode * openAccountPtr = headPtr ;
	uint64 id ;
	uint8 userInput ;
	
	printf ( "\n Enter client's ID : " ) ;
	scanf ( "%llu" , &id ) ;
	
	while ( openAccountPtr != NULL && openAccountPtr -> clientBankId != id )
	{
		openAccountPtr = openAccountPtr -> nextNodePtr ;
	}
	
	if ( openAccountPtr == NULL )
	{
		printf ( "\n ID is not found\n" ) ;
		printf ( "\n Press any key to continue...\n" ) ;
		getchar();
		getchar();
		system ( CLEAR ) ;
	}
	else
	{
		do
		{
			system ( CLEAR ) ;
			printf ( "\n					Welcome to Admin Window\n" ) ;
			
			printBankAccount ( openAccountPtr ) ;
			
			if ( 'A' == openAccountPtr -> bankAccountStatus )
			{
				printf ( "\n\n Choose your desired operation from the following list :" ) ;
				printf ( "\n\n 1- Make Transaction" ) ;
				printf ( "\n\n 2- Change Account Status" ) ;
				printf ( "\n\n 3- Get Cash" ) ;
				printf ( "\n\n 4- Deposit in Account" ) ;
				printf ( "\n\n 5- Return to Main Menu" ) ;
				printf ( "\n\n Your choice : " ) ;
				scanf ( " %c" , &userInput ) ;

				if ( '1' == userInput )
				{
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Admin Window\n" ) ;
					
					makeTransaction( openAccountPtr ) ;
				}
				else if ( '2' == userInput )
				{
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Admin Window\n" ) ;
					
					changeAccountStatus ( openAccountPtr ) ;
				}
				else if ( '3' == userInput )
				{
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Admin Window\n" ) ;
					
					getCash ( openAccountPtr ) ;
				}
				else if ( '4' == userInput )
				{
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Admin Window\n" ) ;
					
					depositInAccount ( openAccountPtr ) ;
				}
				else if ( '5' == userInput )
				{
					
				}
				else
				{
					printf ( "\n Invalid choice\n" ) ;
					printf ( "\n Press any key to continue...\n" ) ;
					getchar();
					getchar();
				}
			}
			else
			{		
				printf ( "\n\n Choose your desired operation from the following list :" ) ;
				printf ( "\n\n 1- Change Account Status" ) ;
				printf ( "\n\n 2- Return to Main Menu" ) ;
				printf ( "\n\n Your choice : " ) ;
				scanf ( " %c" , &userInput ) ;

				if ( '1' == userInput )
				{
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Admin Window\n" ) ;
					
					changeAccountStatus( openAccountPtr ) ;
				}
				else if ( '2' == userInput )
				{
					userInput = '5' ;
				}
				else
				{
					printf ( "\n Invalid choice\n" ) ;
					printf ( "\n Press any key to continue...\n" ) ;
					getchar();
					getchar();
				}
			}
		} while ( '5' != userInput ) ;
	}
}
void openExistingAccountByClient( void )
{
	AccountNode * openAccountPtr = headPtr ;
	uint64 id ;
	uint8 password[9] ;
	uint8 userInput ;
	
	printf ( "\n Enter your ID : " ) ;
	scanf ( "%llu" , &id ) ;
	
	while ( openAccountPtr != NULL && openAccountPtr -> clientBankId != id )
	{
		openAccountPtr = openAccountPtr -> nextNodePtr ;
	}
	
	if ( openAccountPtr == NULL )
	{
		printf ( "\n ID is not found\n" ) ;
		printf ( "\n Press any key to continue...\n" ) ;
		getchar();
		getchar();
		system ( CLEAR ) ;
	}
	else
	{
		printf ( "\n Enter your password : " ) ;
		getchar () ;
		fgets ( password , 9 , stdin ) ;
		if ( 0 != strcmp ( password , openAccountPtr -> accountPassword ) )
		{
			printf ( "\n Incorrect password\n" ) ;
			printf ( "\n Press any key to continue...\n" ) ;
			getchar();
			getchar();
			system ( CLEAR ) ;
		}
		else
		{
			system ( CLEAR ) ;
			printf ( "\n					Welcome to Client Window\n" ) ;
			
			printBankAccount ( openAccountPtr ) ;
			
			if ( 'A' != openAccountPtr -> bankAccountStatus )
			{
				if ( 'R' == openAccountPtr -> bankAccountStatus )
				{
					printf ( "\n\n Account is in Restricted status. No operations can be done.\n" ) ;
				}
				else
				{
					printf ( "\n\n Account is in Closed status. No operations can be done.\n" ) ;
				}
				printf ( "\n Press any key to return to main menu...\n" ) ;
				getchar();
				getchar();
				system ( CLEAR ) ;
			}
			else
			{
				do
				{
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Client Window\n" ) ;
					
					printBankAccount ( openAccountPtr ) ;
					
					printf ( "\n\n Choose your desired operation from the following list :" ) ;
					printf ( "\n\n 1- Make Transaction" ) ;
					printf ( "\n\n 2- Change Account Password" ) ;
					printf ( "\n\n 3- Get Cash" ) ;
					printf ( "\n\n 4- Deposit in Account" ) ;
					printf ( "\n\n 5- Return to Main Menu" ) ;
					printf ( "\n\n Your choice : " ) ;
					scanf ( " %c" , &userInput ) ;
					
					if ( '1' == userInput )
					{
						system ( CLEAR ) ;
						printf ( "\n					Welcome to Client Window\n" ) ;
						
						makeTransaction( openAccountPtr ) ;
					}
					else if ( '2' == userInput )
					{
						system ( CLEAR ) ;
						printf ( "\n					Welcome to Client Window\n" ) ;
						
						changeAccountPassword ( openAccountPtr ) ;
					}
					else if ( '3' == userInput )
					{
						system ( CLEAR ) ;
						printf ( "\n					Welcome to Client Window\n" ) ;
						
						getCash ( openAccountPtr ) ;
					}
					else if ( '4' == userInput )
					{
						system ( CLEAR ) ;
						printf ( "\n					Welcome to Client Window\n" ) ;
						
						depositInAccount ( openAccountPtr ) ;
					}
					else if ( '5' == userInput )
					{
						
					}
					else
					{
						printf ( "\n Invalid choice\n" ) ;
						printf ( "\n Press any key to continue...\n" ) ;
						getchar();
						getchar();
					}
				} while ( '5' != userInput ) ;
				
			}
			
		}
	}
}