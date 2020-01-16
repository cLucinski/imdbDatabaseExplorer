/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "name.h"
#include "common.h"

struct name_array_info * get_name(const char * dirPath)
{
  FILE * fp;
  struct name_basics * nameArr;
  struct name_array_info * arrayInfo;
  char buffer[256];
  char column[256];
  char reverseBuffer[256];
  char * fullPath;
  long actCount;
  int i;

  fullPath = malloc(strlen(dirPath) + strlen("/name.basics.tsv") + 1);
  strcpy(fullPath, dirPath);
  strcat(fullPath, "/name.basics.tsv");

  fp = fopen(fullPath, "r");
  if (fp == NULL)
  {
    perror("Error opening file");
  }

  actCount = 0;
  while (fgets(buffer, 256, fp))
  {
    get_column(buffer, column, 4);
    if (strstr(column, "actor") || strstr(column, "actress"))
    {
      ++actCount;
    }
  }

  nameArr = malloc(sizeof(struct name_basics) * actCount);

  fseek(fp, 0, SEEK_SET);
  i = 0;
  while (fgets(buffer, 256, fp))
  {
    get_column(buffer, column, 4);
    if (strstr(column, "actor") || strstr(column, "actress"))
    {
      strcpy(reverseBuffer, get_column(buffer, column, 0));
      reverse_string(reverseBuffer);
      nameArr[i].nconst = strdup(reverseBuffer);

      nameArr[i].primaryName = strdup(get_column(buffer, column, 1));
      ++i;
    }
  }

  fclose(fp);
  free(fullPath);

  arrayInfo = malloc(sizeof(struct name_array_info));
  arrayInfo->numItems = actCount;
  arrayInfo->address = nameArr;

  return arrayInfo;
}
