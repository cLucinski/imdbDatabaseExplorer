/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "principals.h"
#include "common.h"

struct principals_array_info * get_principals(const char * dirPath)
{
  FILE * fp;
  struct title_principals * princArr;
  struct principals_array_info * arrayInfo;
  char buffer[256];
  char column[256];
  char reverseBuffer[256];
  char * fullPath;
  long actCount;
  int i;

  fullPath = malloc(strlen(dirPath) + strlen("/title.principals.tsv") + 1);
  strcpy(fullPath, dirPath);
  strcat(fullPath, "/title.principals.tsv");

  fp = fopen(fullPath, "r");
  if (fp == NULL)
  {
    perror("Error opening file");
  }

  actCount = 0;
  while (fgets(buffer, 256, fp))
  {
    get_column(buffer, column, 3);
    if (strstr(column, "actor") || strstr(column, "actress"))
    {
      ++actCount;
    }
  }

  princArr = malloc(sizeof(struct title_principals) * actCount);

  fseek(fp, 0, SEEK_SET);
  i = 0;
  while (fgets(buffer, 256, fp))
  {
    get_column(buffer, column, 3);
    if (strstr(column, "actor") || strstr(column, "actress"))
    {
      strcpy(reverseBuffer, get_column(buffer, column, 0));
      reverse_string(reverseBuffer);
      princArr[i].tconst = strdup(reverseBuffer);  /*Reverse insertion for a more-balanced tree*/

      strcpy(reverseBuffer, get_column(buffer, column, 2));
      reverse_string(reverseBuffer);
      princArr[i].nconst = strdup(reverseBuffer);  /*Reverse insertion for a more-balanced tree*/

      princArr[i].characters = strdup(get_column(buffer, column, 5));
      ++i;
    }
  }

  fclose(fp);
  free(fullPath);

  arrayInfo = malloc(sizeof(struct principals_array_info));
  arrayInfo->numItems = actCount;
  arrayInfo->address = princArr;

  return arrayInfo;
}
