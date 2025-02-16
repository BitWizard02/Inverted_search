#include "main.h"
#include<stdlib.h>
/*update database function definition*/
status update_db(c_db *hash_t)
{
    char newfile[100],c;
    int index;
    /*reading the backedup file from user*/
    printf("Enter the file to update: \n");
    scanf("%s", newfile);
    /*opening the backup file in read mode*/
    FILE *fptr = fopen(newfile, "r");
    /*validating file is exist or not*/
    if (fptr == NULL) 
    {
	printf("File not found\n");
	return e_failure;
    }
    /*reading line by line from backup file untill fptr reaches EOF*/
    while (fscanf(fptr, "%s", newfile) != EOF)
    {
	if(newfile[0] != '#')
	    return e_failure;
	/* Extracting index from the line*/
	index = atoi(strtok(&newfile[1], ";"));
	/*Create a new main node and updating the data*/
	m_node *m_new = malloc(sizeof(m_node));
	if (m_new == NULL)
	{
	    return e_failure;
	}
	m_new->m_main_link = NULL;
	strcpy(m_new->word, strtok(NULL, ";"));
	m_new->file_count = atoi(strtok(NULL, ";"));
	/*Creating a new subword node and updating the data*/
	s_node *s_new = malloc(sizeof(s_node));
	s_node *stemp;
	if (s_new == NULL)
	{
	    return e_failure;
	}
	s_new->s_sub_link = NULL;
	strcpy(s_new->file_name, strtok(NULL, ";"));
	s_new->word_count = atoi(strtok(NULL, ";"));
	m_new->m_sub_link = s_new;
	stemp = s_new;
	/*Loop to create more sub nodes based on file count*/
	for (int i = 0; i < (m_new->file_count)-1; i++) 
	{
	    s_node *s_new = malloc(sizeof(s_node));
	    if (s_new == NULL)
	    {
		return e_failure;
	    }
	    s_new->s_sub_link = NULL;
	    strcpy(s_new->file_name, (strtok(NULL, ";")));
	    s_new->word_count = atoi(strtok(NULL, ";"));
	    stemp->s_sub_link = s_new;
	    stemp = s_new;
	}
	/* Inserting the new main node into the hashtable*/
	 m_node *temp = hash_t[index].m_link;
	if (temp == NULL)
	{
	    hash_t[index].m_link = m_new;
	} 
	else
	{
	    while (temp->m_main_link)
	    {
		temp = temp->m_main_link;
	    }
	    temp->m_main_link = m_new;
	}  
    }
    fclose(fptr);
    return e_success;
}


