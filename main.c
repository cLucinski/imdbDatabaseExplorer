/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

/*
   Notes:
 * In search queue type
   > exit
   to exit loop and close program.
 * Titles are added out of order in principals data. Different algorithm was devised to handle it.
 */

#include <stdio.h>
#include <string.h>

#include "binary.h"
#include "common.h"
#include "name.h"
#include "principals.h"
#include "title.h"

int main(int argc, char const *argv[])
{
  struct name_array_info * nameArrayInfo;
  struct title_array_info * titleArrayInfo;
  struct principals_array_info * principalsArrayInfo;

  struct node * titleNameTree;
  struct node * titleName;
  struct node * titleTconstTree;
  struct node * titleTconst;

  struct node * nameNameTree;
  struct node * nameName;
  struct node * nameNconstTree;
  struct node * nameNconst;

  struct node * princTconstTree;
  struct node * princTconst;
  struct node * princNconstTree;
  struct node * princNconst;

  char searchMethod[256];
  char searchString[256];

  int i;
  int j;

  /*Array and trees based on title information*/
  titleArrayInfo = get_title( argv[1] );
  titleNameTree = new_node((struct title_array_info *) (titleArrayInfo), titleArrayInfo->address[0].primaryTitle);
  for (i = 1; i < titleArrayInfo->numItems; ++i)
  {
    add_node(titleNameTree, new_node(&(titleArrayInfo->address[i]), titleArrayInfo->address[i].primaryTitle));
  }
  titleTconstTree = new_node((struct title_array_info *) (titleArrayInfo), titleArrayInfo->address[0].tconst);
  for (i = 1; i < titleArrayInfo->numItems; ++i)
  {
    add_node(titleTconstTree, new_node(&(titleArrayInfo->address[i]), titleArrayInfo->address[i].tconst));
  }

  /*Array and trees based on name information*/
  nameArrayInfo = get_name(argv[1]);
  nameNameTree = new_node((struct name_array_info *) (nameArrayInfo), nameArrayInfo->address[0].primaryName);
  for (i = 1; i < nameArrayInfo->numItems; ++i)
  {
    add_node(nameNameTree, new_node(&(nameArrayInfo->address[i]), nameArrayInfo->address[i].primaryName));
  }
  nameNconstTree = new_node((struct name_array_info *) (nameArrayInfo), nameArrayInfo->address[0].nconst);
  for (i = 1; i < nameArrayInfo->numItems; ++i)
  {
    add_node(nameNconstTree, new_node(&(nameArrayInfo->address[i]), nameArrayInfo->address[i].nconst));
  }

  /*Array and trees based on principals information*/
  principalsArrayInfo = get_principals(argv[1]);
  princTconstTree = new_node((struct principals_array_info *) (principalsArrayInfo), principalsArrayInfo->address[0].tconst);
  for (i = 1; i < principalsArrayInfo->numItems; ++i)
  {
    add_node(princTconstTree, new_node(&(principalsArrayInfo->address[i]), principalsArrayInfo->address[i].tconst));
  }
  princNconstTree = new_node((struct principals_array_info *) (principalsArrayInfo), principalsArrayInfo->address[0].nconst);
  for (i = 1; i < principalsArrayInfo->numItems; ++i)
  {
    add_node(princNconstTree, new_node(&(principalsArrayInfo->address[i]), principalsArrayInfo->address[i].nconst));
  }



  /*Search*/
  while (1) {
    printf("> ");
    scanf("%s", searchMethod);
    fgets(searchString, 50, stdin);
    for (i = 0; i < strlen(searchString); ++i)
    {
      while (searchString[i] == ' ')
      {
        for (j = i; j < strlen(searchString); ++j)
        {
          searchString[j] = searchString[j + 1];
        }
      }
      if (searchString[i] != ' ')
      {
        break;
      }
    }
    searchString[strlen(searchString) - 1] = '\0';
    while (searchString[strlen(searchString) - 1] == ' ')
    {
      searchString[strlen(searchString) - 1] = '\0';
    }

    /*Exit case, type "exit"*/
    if (strcmp(searchMethod, "exit") == 0)
    {
      break;
    }

    /*Begin binary search through trees*/
    if (strcmp(searchMethod, "name") == 0) /*Search for name*/
    {
      nameName = find_node(nameNameTree, searchString);  /*Find name and nconst*/
      if (nameName == NULL)  /*If name cannot be found, quit searching*/
      {
        continue;
      }
      princNconst = find_node(princNconstTree, ((struct name_array_info *) (nameName->data))->address->nconst);  /*Find nconst and tconst*/
      titleTconst = find_node(titleTconstTree, ((struct principals_array_info *) (princNconst->data))->address->tconst);  /*Find tconst and title*/
      if (titleTconst != NULL && princNconst != NULL)
      {
        printf("%s : %s\n", ((struct title_array_info *) (titleTconst->data))->address->primaryTitle,
                                    ((struct principals_array_info *) (princNconst->data))->address->characters);  /*Print title and character(s)*/
      }
      /*Search for more entries*/
      while (((princNconst != NULL)) && ((princNconst->child[0] != NULL) || (princNconst->child[1] != NULL)))
      {
        if (princNconst->child[0] != NULL)
        {
          princNconst = find_node(princNconst->child[0], ((struct name_array_info *) (nameName->data))->address->nconst);
          if (princNconst == NULL)
          {
            continue;
          }
          titleTconst = find_node(titleTconstTree, ((struct principals_array_info *) (princNconst->data))->address->tconst);
          if (titleTconst != NULL && princNconst != NULL)
          {
            printf("%s : %s\n", ((struct title_array_info *) (titleTconst->data))->address->primaryTitle,
                                        ((struct principals_array_info *) (princNconst->data))->address->characters);
          }
        }
        else if ((princNconst->child[1] != NULL))
        {
          princNconst = find_node(princNconst->child[1], ((struct name_array_info *) (nameName->data))->address->nconst);
          if (princNconst == NULL)
          {
            continue;
          }
          titleTconst = find_node(titleTconstTree, ((struct principals_array_info *) (princNconst->data))->address->tconst);
          if (titleTconst != NULL && princNconst != NULL)
          {
            printf("%s : %s\n", ((struct title_array_info *) (titleTconst->data))->address->primaryTitle,
                                        ((struct principals_array_info *) (princNconst->data))->address->characters);
          }
        }
        else
        {
          break;
        }
      }
    }
    else if (strcmp(searchMethod, "title") == 0) /*Search for title*/
    {
      titleName = find_node(titleNameTree, searchString);  /*Find title and tconst*/
      if (titleName == NULL)
      {
        continue;
      }
      princTconst = find_node(princTconstTree, ((struct title_array_info *) (titleName->data))->address->tconst);  /*Find tconst and nconst*/
      if (princTconst == NULL)
      {
        continue;
      }
      nameNconst = find_node(nameNconstTree, ((struct principals_array_info *) (princTconst->data))->address->nconst);  /*Find nconst and name*/


      /*Check that the values to be printed exist*/
      if ((((struct name_array_info *) (nameNconst->data))->address->primaryName) != NULL &&
          (((struct principals_array_info *) (princTconst->data))->address->characters) != NULL)
      {
        printf("%s : %s\n", ((struct name_array_info *) (nameNconst->data))->address->primaryName,
                                    ((struct principals_array_info *) (princTconst->data))->address->characters);  /*Print name and character(s)*/
      }
      /*Search for more*/
      while (((princTconst != NULL)) && ((princTconst->child[0] != NULL) || (princTconst->child[1] != NULL)))
      {
        if (princTconst->child[0] != NULL)  /*If left child exists, search there*/
        {
          princTconst = find_node(princTconst->child[0], ((struct title_array_info *) (titleName->data))->address->tconst);
          if (princTconst == NULL)
          {
            continue;
          }
          nameNconst = find_node(nameNconstTree, ((struct principals_array_info *) (princTconst->data))->address->nconst);

          /*Check that the values to be printed exist*/
          if ((((struct name_array_info *) (nameNconst->data))->address->primaryName) != NULL &&
                  (((struct principals_array_info *) (princTconst->data))->address->characters) != NULL)
          {
            printf("%s : %s\n", ((struct name_array_info *) (nameNconst->data))->address->primaryName,
                                        ((struct principals_array_info *) (princTconst->data))->address->characters);
          }
        }
        else if (princTconst->child[1] != NULL)  /*If right child exists, search there*/
        {
          princTconst = find_node(princTconst->child[1], ((struct title_array_info *) (titleName->data))->address->tconst);
          if (princTconst == NULL)
          {
            continue;
          }
          nameNconst = find_node(nameNconstTree, ((struct principals_array_info *) (princTconst->data))->address->nconst);

          /*Check that the values to be printed exist*/
          if ((((struct name_array_info *) (nameNconst->data))->address->primaryName) != NULL &&
              (((struct principals_array_info *) (princTconst->data))->address->characters) != NULL)
          {
            printf("%s : %s\n", ((struct name_array_info *) (nameNconst->data))->address->primaryName,
                                        ((struct principals_array_info *) (princTconst->data))->address->characters);
          }
        }
      }
    }
    else
    {
      printf("Invalid search.\n");
    }
  }
  /*Free trees upon exit.*/
  free_tree(princNconstTree);
  free_tree(princTconstTree);
  free_tree(nameNameTree);
  free_tree(nameNconstTree);
  free_tree(titleNameTree);
  free_tree(titleTconstTree);
  /*Was unable to properly free arrays*/

  return 0;
}
