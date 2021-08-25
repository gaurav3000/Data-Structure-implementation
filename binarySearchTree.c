/***********************************
* EECS2031A - A2
* Filename: a2.BST.c
* Author: Garg, Gaurav
* Email: gauravg@my.yorku.ca
* eecs username: gauravg
* york_num: 217643453
************************************/

// Binary Search Tree operations in C

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

struct node
{
   int key;
   struct node *left, *right;
};

struct node *root;

// Inorder Traversal
void inorderT(struct node *r)
{
   if (r != NULL)
   {
      // Traverse left
      inorderT(r->left);

      // Traverse root
      printf("%d -> ", r->key);

      // Traverse right
      inorderT(r->right);
   }
}

void inorder()
{

   inorderT(root);
}

/*********************************************************************/
// Create a root node with key item
void createRoot(int item)
{
   root = malloc(sizeof(struct node));
   root->key = item;
   root->left = NULL;
   root->right = NULL;
}

void insertTree(struct node *r, int key)
{
   if (r == NULL)
   {
      createRoot(key);
   }
   else if (key < r->key)
   {
      if (r->left != NULL)
      {
         return insertTree(r->left, key);
      }
      r->left = malloc(sizeof(struct node));
      r->left->key = key;
      r->left->left = NULL;
      r->left->right = NULL;
   }
   else if (key > r->key)
   {
      if (r->right != NULL)
      {
         return insertTree(r->right, key);
      }
      r->right = malloc(sizeof(struct node));
      r->right->key = key;
      r->right->left = NULL;
      r->right->right = NULL;
   }
}

/*  insert key into the tree. the tree may or may not be empty */
void insert(int key)
{
   return insertTree(root, key);
}

// return the pointer to the node with min key
struct node *minValueNode()
{
   struct node *curr = root;
   while (curr->left != NULL)
   {
      curr = curr->left;
   }
   return curr;
}

int sizeOfTree(struct node *r)
{
   if (r == NULL)
   {
      return 0;
   }
   return 1 + sizeOfTree(r->left) + sizeOfTree(r->right);
}

// return number node in the tree
int size()
{
   return sizeOfTree(root);
}

int searchTree(struct node *r, int key)
{
   if (r != NULL)
   {
      if (r->key == key)
      {
         return 1;
      }
      else if (key < r->key)
      {
         return searchTree(r->left, key);
      }
      else if (key > r->key)
      {
         return searchTree(r->right, key);
      }
   }
   return 0;
}

// search key, return 'true' or 'false'
int search(int key)
{
   return searchTree(root, key);
}
/*********************************************************************/

// Driver code
int main()
{

   char buffer[BUFFER_SIZE];
   int value;
   int count = 0;

   createRoot(100);
   printf("size: %d\n", size());
   printf("Inorder traversal: ");
   inorder();
   printf("\n\n");

   root = NULL; // empty the tree

   FILE *file;
   file = fopen("data2.txt", "r");
   root = NULL;

   fgets(buffer, BUFFER_SIZE, file);
   sscanf(buffer, "%d", &value); // store into value
   printf("insert %d\n", value);
   insert(value);
   printf("size %d\n", size());
   printf("Inorder traversal: ");
   inorder();
   printf("\n");

   // print the min key ...
   printf("min key: %d\n", minValueNode()->key);

   int searchList[] = {14, 33, 8, 83, 100, 52, -1};
   int i = 0;
   int key;
   while ((key = searchList[i]) != -1)
   {
      printf("search %3d ....  ", key);
      if (search(key))
         printf("found\n");
      else
         printf("not found\n");
      i++;
   }
   printf("\n");

   // read 4 more
   i;
   for (i = 0; i < 4; i++)
   {
      fgets(buffer, BUFFER_SIZE, file);
      sscanf(buffer, "%d", &value);
      printf("insert %d\n", value);
      insert(value);
   }

   printf("size %d\n", size());
   printf("Inorder traversal: ");
   inorder();
   printf("\n");

   // print the min key ...
   printf("min key: %d\n", minValueNode()->key);

   i = 0;
   while ((key = searchList[i]) != -1)
   {
      printf("search %3d ....  ", key);
      if (search(key))
         printf("found\n");
      else
         printf("not found\n");
      i++;
   }
   printf("\n");

   // read 6 more
   i;
   for (i = 0; i < 6; i++)
   {
      fgets(buffer, BUFFER_SIZE, file);
      sscanf(buffer, "%d", &value);
      printf("insert %d\n", value);
      insert(value);
   }

   printf("size %d\n", size());
   printf("Inorder traversal: ");
   inorder();
   printf("\n");

   // print the min key ...
   printf("min key: %d\n", minValueNode()->key);

   i = 0;
   while ((key = searchList[i]) != -1)
   {
      printf("search %3d ....  ", key);
      if (search(key))
         printf("found\n");
      else
         printf("not found\n");
      i++;
   }
   printf("\n");

   fclose(file);
}
