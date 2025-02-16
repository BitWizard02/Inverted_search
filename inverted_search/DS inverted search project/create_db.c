/***************************************************************************************************************************************************
*Date           :Mon 25 Nov 2024 
*File           :create_database.c
*Title          :To create the database
*Description    :The list of the files can be provided by storing all the file names in another file, FileList the names of the files which 
		:are to be documented are provided by this file. When a file is added or removed, FileList is changed accordingly.
		:So read the file names and start indexing.
****************************************************************************************************************************************************/
#include "main.h"
status create_db(f_list *head, c_db *arr)
{
    f_list *temp = head;
    char index[30];
    int key;

    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->f_name, "r");
        while (fscanf(fptr, "%s", index) != EOF)
        {
            key = tolower(index[0]) % 97;
            if (key < 0 || key > 25)
                key = 26;

            if (arr[key].m_link == NULL)
            {
                m_node *m_new = malloc(sizeof(m_node));
                if (m_new == NULL)
                    return e_failure;

                s_node *s_new = malloc(sizeof(s_node));
                if (s_new == NULL)
                    return e_failure;

                m_new->file_count = 1;
                strcpy(m_new->word, index);
                m_new->m_sub_link = s_new;
                m_new->m_main_link = NULL;

                s_new->word_count = 1;
                strcpy(s_new->file_name, temp->f_name);
                s_new->s_sub_link = NULL;

                arr[key].m_link = m_new;
            }
            else
            {
                int f = 0;
                m_node *temp1 = arr[key].m_link;
                m_node *prev = NULL;
                while (temp1 != NULL)
                {
                    if (strcmp(temp1->word, index) == 0)
                    {
                        f = 1;
                        s_node *st = temp1->m_sub_link;
                        s_node *st_prev = NULL;
                        while (st != NULL)
                        {
                            if (strcmp(st->file_name, temp->f_name) == 0)
                            {
                                ++st->word_count;
                                break;
                            }
                            st_prev = st;
                            st = st->s_sub_link;
                        }

                        if (st == NULL)
                        {
                            s_node *s_new = malloc(sizeof(s_node));
                            s_new->word_count = 1;
                            strcpy(s_new->file_name, temp->f_name);
                            s_new->s_sub_link = NULL;
                            ++temp1->file_count;
                            st_prev->s_sub_link = s_new;
                        }
                    }
                    prev = temp1;
                    temp1 = temp1->m_main_link;
                }
                if (f == 0)
                {
                    m_node *m_new = malloc(sizeof(m_node));
                    if (m_new == NULL)
                        return e_failure;

                    s_node *s_new = malloc(sizeof(s_node));
                    if (s_new == NULL)
                        return e_failure;

                    m_new->file_count = 1;
                    strcpy(m_new->word, index);
                    m_new->m_sub_link = s_new;
                    m_new->m_main_link = NULL;

                    s_new->word_count = 1;
                    strcpy(s_new->file_name, temp->f_name);
                    s_new->s_sub_link = NULL;

                    prev->m_main_link = m_new;
                }
            }
        }
        fclose(fptr);
        temp = temp->link;
    }
}

