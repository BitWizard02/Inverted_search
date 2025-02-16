/*
Name: Veerabhadresshwar Guggari
Date: 25/11/2024
Description: Inverted Search
Input: ./a.out file1.txt file2.txt
Output: .***** Open files are successfully *****
		&&&&& Read and Validate is Completed &&&&&

		Select your choice among the following options:
		1. Create DataBase
		2. Display DataBase
		3. Search DataBase
		4. Save DataBase
		5. Update DataBase
		6. Exit
		Enter your choice : 1
		---- DataBase Created Successfully ----
		Do you want to continue (y/n) : y
*/

#include "main.h"

int main(int argc, char *argv[])
{
	int option, f = 0;   // declare the variables
	char choose;
	f_list *head = NULL;
	c_db arr[27];

	for (int i = 0; i < 27; i++)
	{
		arr[i].key = i;
		arr[i].m_link = NULL;
	}
	if (argc <= 1)    // to check command line argument is passed or not
	{
		printf("Error : Insufficient Arguements\nUsage : ./a.out file1.txt file2.txt\n");
		return 0;
	}
	else
	{
		if (read_and_validate(argc, argv, &head) == e_success)   // to store the Command line argument and remove repeated filenames
			printf("&&&&& Read and Validate is Completed &&&&&\n");
		else
		{
			printf("&&&&& Error : Read and Validate is Completed &&&&&\n");
			return 0;
		}
	}
	// first execute and then check the condition
	do
	{
		printf("\nSelect your choice among the following options:\n1. Create DataBase\n2. Display DataBase\n3. Search DataBase\n4. Save DataBase\n5. Update DataBase\n6. Exit\nEnter your choice : ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			if (f == 0)
			{
				f = 1;
				// create database function call
				if (create_db(head, arr) == e_success)
					printf("----- DataBase Created Successfully -----\n");
				else
					printf("----- Error : Failed To Create Database -----\n");
			}
			else
				printf("Create DataBase Is Not Possible After Update DataBase\n");
			break;
		case 2:
			// display database function call
			display_db(arr);
			break;
		case 3:
			// search database function call
			if (search_db(arr) == DATA_NOT_FOUND)
				printf("***** Word Not Found *****\n");
			break;
		case 4:
			// save database functin call
			if (save_db(arr) == e_success)
				printf("***** Database Saved Successfully *****\n");
			else
				printf("***** Error : Failed To Save Database *****\n");
			break;
		case 5:
			if (f == 0)
			{
				//f = 1;
				// update database function call
				if (update_db(arr) == e_success)
					printf("***** Database Updated Successfully *****\n");
				else
					printf("***** Error : Failed To Update Database *****\n");
			}
			else
				printf("Update Database Is Not Possible After Create Database\n");
			break;
		case 6:
			printf("***** Exit Successfully *****\n");
			return 0;
			break;
		default:
			printf("Invalid choice. Please enter a valid option.\n");
			break;
		}
		printf("Do you want to continue (y/n) : ");
		scanf(" %c", &choose);
	} while (choose == 'y' || choose == 'Y');    // to continue again the process
	return 0;
}

