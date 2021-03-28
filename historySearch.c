#include "defs.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Assistant.h"
bool equalsIgnoreCase(char* str1, char* str2)
{
    if (strlen(str1) != strlen(str2))
    {
        return FALSE;
    }
    else
    {
        for (int i = 0; i < strlen(str1); i++)
        {
            if (tolower(str1[i]) != tolower(str2[i]))
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

bool historySearch(char *query)
{
    FILE* infile = fopen("History.txt","r");
    char nameQuery[256] = {0}, jobQuery[256] = {0}, statusQuery[256] = {0};
    char job[256] = {0}, name[256] = {0}, status[256] = {0};
    char buffer[1024] = {0};
    bool foundMatch = FALSE;
    float id = 0;
    int count = 0;

    sscanf(query, "%[^,],%[^,],%[^,]", nameQuery, jobQuery, statusQuery);
    
    while (fgets(buffer, 1024, infile))
    {
        
        sscanf(buffer, "%*d,%[^,],\"%[^\"]\",%*f,%*f,%*f,%[^,],%*[^\n\r]",name,job,status);
        if (strcmp(job, "") == 0){
            sscanf(buffer, "%*d,%[^,],%[^,],%*f,%*f,%*f,%[^,],%*[^\n\r]",name,job,status);

        }
        if (equalsIgnoreCase(name, nameQuery) && equalsIgnoreCase(job, jobQuery) && equalsIgnoreCase(status, statusQuery))
	{
	    termPrinter("Record found in File");
	    termPrinter(buffer);
//	    printf("Query: %s\n", query);
//	    printf("Name: %s, Job: %s, Status: %s.\n", name, job, status);
            return TRUE;
        }
        strcpy(job, "");
    }
    Assistant(nameQuery);
    fclose(infile);
    return FALSE;
}

int main()
{   
    printf("Result: %d\n", historySearch("John Martin,DEPARTMENT HEAD V,FT"));
}
