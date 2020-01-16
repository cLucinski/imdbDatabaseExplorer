/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "title.h"
#include "common.h"

struct title_array_info * get_title(const char * dirPath)
{
  FILE * fp;
  struct title_basics * titleArr;
  struct title_array_info * arrayInfo;
  char buffer[256];
  char column[256];
  char colBuffer1[256];
  char colBuffer2[256];
  char reverseBuffer[256];
  char * fullPath;
  long titleCount;
  int i;

  fullPath = malloc(strlen(dirPath) + strlen("/title.basics.tsv") + 1);
  strcpy(fullPath, dirPath);
  strcat(fullPath, "/title.basics.tsv");

  fp = fopen(fullPath, "r");
  if (fp == NULL)
  {
    perror("Error opening file");
  }

  titleCount = 0;
  while (fgets(buffer, 256, fp))
  {
    get_column(buffer, colBuffer1, 1);
    get_column(buffer, colBuffer2, 4);

    if (strstr(colBuffer1, "movie") && strstr(colBuffer2, "0"))
    {
      ++titleCount;
    }
  }

  titleArr = malloc(sizeof(struct title_basics) * titleCount);

  fseek(fp, 0, SEEK_SET);
  i = 0;
  while (fgets(buffer, 256, fp))
  {
    if (strstr(get_column(buffer, column, 1), "movie") && strstr(get_column(buffer, column, 4), "0"))
    {
      strcpy(reverseBuffer, get_column(buffer, column, 0));
      reverse_string(reverseBuffer);
      titleArr[i].tconst = strdup(reverseBuffer);  /*Reverse insertion for a more-balanced tree*/
      titleArr[i].primaryTitle = strdup(get_column(buffer, column, 2));
      ++i;
    }
  }

  fclose(fp);
  free(fullPath);

  arrayInfo = malloc(sizeof(struct title_array_info));
  arrayInfo->numItems = titleCount;
  arrayInfo->address = titleArr;

  return arrayInfo;
}
