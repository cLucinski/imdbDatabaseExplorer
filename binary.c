/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary.h"

struct node * new_node(void * structPtr, char * keyPtr)
{
  struct node * n;
  n = malloc(sizeof(struct node));

  n->data = structPtr;
  n->key = keyPtr;
  n->child[0] = NULL;
  n->child[1] = NULL;

  return n;
}

struct node * add_node(struct node * curLocation, struct node * toAdd)
{
  if (curLocation == NULL)
  {
    return new_node(toAdd, toAdd->key);
  }
  else
  {
    if (strcmp(curLocation->key, toAdd->key) > 0)  /*Current node is greater than toAdd*/
    {
      curLocation->child[0] = add_node(curLocation->child[0], toAdd);  /*Add to left child*/
    }
    else if (strcmp(curLocation->key, toAdd->key) < 0)  /*Current node is less than toAdd*/
    {
      curLocation->child[1] = add_node(curLocation->child[1], toAdd);  /*Add to right child*/
    }
    else
    {
      curLocation->child[0] = add_node(curLocation->child[0], toAdd);  /*If equal, add to left child*/
    }
  }
  return curLocation;
}

struct node * find_node(struct node * curLocation, char * keyPtr)
{
  if (curLocation == NULL || strcmp(curLocation->key, keyPtr) == 0)
  {
    return curLocation;
  }
  else if (strcmp(curLocation->key, keyPtr) > 0)
  {
    return find_node(curLocation->child[0], keyPtr);
  }
  else if (strcmp(curLocation->key, keyPtr) < 0)
  {
    return find_node(curLocation->child[1], keyPtr);
  }
  else
  {
    return find_node(curLocation->child[0], keyPtr);
  }
}

void free_tree( struct node * root )
{
  if (root)
  {
    free_tree( root->child[0] );
    free_tree( root->child[1] );
    free( root );
  }
}
