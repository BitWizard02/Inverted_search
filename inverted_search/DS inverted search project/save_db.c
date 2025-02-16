#include "main.h"
#include <stdio_ext.h>
status save_db(c_db *hash_t)
{
    char file[20];
    char choice;
    //read the backup file from user
    printf("Enter the file name\n");
    scanf("%s",file);

    //open the file
    FILE *fptr = fopen(file, "w");
    if(fptr != NULL)
    {
	//move the pointer
	fseek(fptr, 0 ,SEEK_END);
	if(fptr != 0)
	{
	    printf("can I overwrite the content (y/n)\n");
	    __fpurge(stdin);
	    scanf("%c",&choice);
	    if(choice == 'n')
	    {
		return e_failure;
	    }
	}
    }
    for(int key=0; key<27; key++)
    {
	m_node *temp = hash_t[key].m_link;
	if(temp == NULL)
	    continue;
	//iterate till temp not equals null and save the database
	while(temp != NULL)
	{
	    fprintf(fptr, "%s" , "#");
	    fprintf(fptr, "%d;" , key);
	    fprintf(fptr, "%s;" , temp->word);
	    fprintf(fptr, "%d;" , temp->file_count);
	    s_node *stemp = temp->m_sub_link;
	    while(stemp != NULL)
	    {
		fprintf(fptr,"%s;",stemp->file_name);
		fprintf(fptr,"%d;",stemp->word_count);
		stemp = stemp->s_sub_link;
	    }

	    temp = temp->m_main_link;
	    fprintf(fptr, "%s" , "#");
	    fprintf(fptr, "%s" , "\n");
	}
    }
    fclose(fptr);
    return e_success;
}


