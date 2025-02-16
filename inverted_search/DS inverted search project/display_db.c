#include "main.h"

// function to display the contents
status display_db(c_db *hash_t)
{
    printf("%-7s %-15s %-15s %-15s %-10s\n", "-----", "----", "---------", "----------", "---------");
    printf("%-7s %-15s %-15s %-15s %-10s\n", "Index", "Word", "Filecount", "Files Name", "Wordcount");
    printf("%-7s %-15s %-15s %-15s %-10s\n", "-----", "----", "---------", "----------", "---------");
    for (int key = 0; key < 27; key++)
    {
        m_node *temp2 = hash_t[key].m_link;
        while (temp2 != NULL)
        {
            printf("[%d]     %-18s %-13d", key, temp2->word, temp2->file_count);
            s_node *stemp = temp2->m_sub_link;
            while (stemp != NULL)
            {
                printf("%-18s  %d   ", stemp->file_name, stemp->word_count);
                stemp = stemp->s_sub_link;
            }
            printf("\n");
            temp2 = temp2->m_main_link;
        }
    }
    return e_success;
}

