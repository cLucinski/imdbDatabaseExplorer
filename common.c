/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

char * get_column(const char * line, char * lineCopy, int colNum)
{
  int numTabs;
  int i;
  int j;
  int tabIndex1;
  int tabIndex2;
  numTabs = 0;
  tabIndex1 = -1;
  tabIndex2 = -1;

  if (colNum == 0)
  {
    tabIndex1 = 0;
  }
  for (i = 0; i < strlen(line); ++i)
  {
    if (line[i] == '\t')
    {
      ++numTabs;
    }
    if ((numTabs == colNum) && (tabIndex1 == -1))
    {
      tabIndex1 = i + 1;
    }
    if (numTabs == (colNum + 1) || line[i] == '\n')
    {
      tabIndex2 = i;
      break;
    }
  }
  j = 0;
  for (i = tabIndex1; i < tabIndex2; ++i)  /*because strncpy wasn't reliable*/
  {
    lineCopy[j] = line[i];
    ++j;
  }
  lineCopy[j] = '\0';

  return lineCopy;
}

/*
 * Algorithm to replace strrev.
 * Found at "https://stackoverflow.com/questions/198199/how-do-you-reverse-a-string-in-place-in-c-or-c".
 */
void reverse_string(char *string)
{
  char *tail;
  if (!string) return;
  tail = string;
  while(*tail) ++tail;
  --tail;
  for( ; string < tail; ++string, --tail)
  {
    char h = *string, t = *tail;
    *string = t;
    *tail = h;
  }
}

char *strdup(const char * s) {
  char * ret;
  ret = malloc(strlen(s) + 1);
  strcpy(ret, s);
  return ret;
}
