#include "std_types.h"
#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAR "cls"

#define ADMIN_USER "AhmedOsama"
#define ADMIN_PASS "12345678"

int main ( void )
{
	uint8 userInput ; 			/* variable to store user's choices   */
	uint8 adminUsername[20] ;	/* Array to save admin input username */
	uint8 adminPassword[20] ;	/* Array to save admin input password */
	
	/* -------------------- Main Menu -------------------- */
	do
	{
		/* Clear command prompt screen then show welcome message */
		system ( CLEAR ) ;	
		printf ( "\n					Welcome to IMT Bank System\n" ) ;
		
		/* Show list of items available in main menu */
		printf ( "\n Choose between Admin Window, Client Window or Exit by choosing order of operation in the following list :" ) ;
		printf ( "\n\n 1- Admin Window" ) ;
		printf ( "\n\n 2- Client Window" ) ;
		printf ( "\n\n 3- Exit" ) ;
		printf ( "\n\n Your choice : " ) ;
		scanf ( " %c" , &userInput ) ;
		
		/* -------------------- Admin Menu -------------------- */
		if ( '1' == userInput )
		{
			/* Take admin's username and password */
			printf ( "\n Enter username : " ) ;
			getchar() ;
			gets ( adminUsername ) ;
			printf ( "\n Enter password : " ) ;
			gets ( adminPassword ) ;
			
			/* Verify admin's username and password */
			if ( ( 0 == strcmp ( adminUsername , ADMIN_USER ) ) && ( 0 == strcmp ( adminPassword , ADMIN_PASS ) ) )
			{
				/* Admin's username and password are verified */
				do
				{
					/* Clear command prompt screen then show welcome message */
					system ( CLEAR ) ;
					printf ( "\n					Welcome to Admin Window\n" ) ;
					
					/* Show list of items available in admin window */
					printf ( "\n Choose your desired operation from the following list :" ) ;
					printf ( "\n\n 1- Create New Account" ) ;
					printf ( "\n\n 2- Open Existing Account" ) ;
					printf ( "\n\n 3- Exit" ) ;
					printf ( "\n\n Your choice : " ) ;
					scanf ( " %c" , &userInput ) ;

					if ( '1' == userInput )
					{
						system ( CLEAR ) ;
						printf ( "\n					Welcome to Admin Window\n" ) ;
						createNewAccount() ;
					}
					else if ( '2' == userInput )
					{
						system ( CLEAR ) ;
						printf ( "\n					Welcome to Admin Window\n" ) ;
						openExistingAccountByAdmin() ;
					}
					else if ( '3' == userInput )
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
				} while ( '5' != userInput ) ;	
			}
			else
			{
				printf ( "\n Username or password is not correct\n" ) ;
				printf ( "\n Press any key to continue...\n" ) ;
				getchar();
			}		
		}
		
		/*			Client Menu			*/
		else if ( '2' == userInput )
		{
			system ( CLEAR ) ;
			printf ( "\n					Welcome to Client Window\n" ) ;
			openExistingAccountByClient() ;
		}
		
		/*			Exit the system			*/
		else if ( '3' == userInput )
		{
			printf ( "\n Thank you for using IMT Bank System\n" ) ;
			printf ( "\n Press any key to continue...\n" ) ;
			getchar();
			getchar();
		}
		else
		{
			printf ( "\n Invalid choice\n" ) ;
			printf ( "\n Press any key to continue...\n" ) ;
			getchar();
			getchar();
		}
	} while ( '3' != userInput ) ;
	
	system ( CLEAR ) ;
}
