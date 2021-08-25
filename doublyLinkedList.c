/***********************************
* EECS2031A - A2
* Filename: a2List.c
* Author: Garg, Gaurav
* Email: gauravg@my.yorku.ca
* eecs username: gauravg
* york_num: 217643453
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 50
#define MAX_LEN 30

int len();
char get(int index);
void delete (char d);
void insertAfter(char c, int index);
void insert(char c);
int search(char key);

struct twoInts
{
    int int1;
    int int2;
};

struct node
{ // list 'node' struct
    char data;
    struct node *next;
    struct node *prev;
};

void init();
void display();
// more declarations if needed

struct node *head; // global variable, the head of the linkedlist

int main()
{
    int i, index;
    char key;

    struct twoInts *arr[MAX_LEN]; // an array of ten pionters to structs

    char buffer[BUFFER_SIZE];
    int value1, value2;
    int count = 0;

    FILE *file;
    file = fopen("data.txt", "r");

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) // or  while (fscanf(file, "%d %d", &value1, &value2) == 2)
    {
        sscanf(buffer, "%d %d", &value1, &value2); // tokenize buffer and store into value1 and value2

        // call malloc to allocate memory for arr[count]
        arr[count] = malloc(sizeof(int));

        // set the two fields pointed by arr[count] with value1 value2
        arr[count]->int1 = value1;
        arr[count]->int2 = value2;

        count++;
    }

    fclose(file);

    /* print the fields of stuctures pointed by the pointer array */
    for (i = 0; i < count; i++)
    {
        printf("arr[%d]: %d %d\n", i, arr[i]->int1, arr[i]->int2);
    }

    // now building up the list by reading from the array of structures
    printf("\n");
    init();

    i = 0;
    for (; i < count; i++)
    {
        // read two ints from each structure pointed in the array, sum up and added into the list
        int value = arr[i]->int1 + arr[i]->int2;
        insert(value); // no more coding in main

        printf("insert %c: (%d)", value, len());
        display();
    }

    char removeList[] = {'B', 'S', 'A', 'O', 'R', 'K', 'Y', 'U', 'L', '\0'}; // \0 is the terminating token
    i = 0;
    while ((key = removeList[i]) != '\0')
    {
        delete (key);
        printf("remove %c: (%d)", key, len());
        display();
        i++;
    }

    // insert again
    char addList[] = "YORKULABS";
    i = 0;
    while ((key = addList[i]) != '\0')
    {
        insert(key);
        printf("insert %c: (%d)", key, len());
        display();
        i++;
    }

    int v = get(0);
    printf("\nget(0): %c\n", v);
    v = get(3);
    printf("get(3): %c\n", v);
    v = get(6);
    printf("get(6): %c\n", v);
    v = get(7);
    printf("get(7): %c\n", v);
    v = get(8);
    printf("get(8): %c\n", v);

    key = 'x';
    index = 2;
    insertAfter(key, index);
    printf("\ninsert %c after index %d: (%d)\n", key, index, len());
    display();
    key = 'y';
    index = 0;
    insertAfter(key, index);
    printf("insert %c after index %d: (%d)\n", key, index, len());
    display();
    key = 'z';
    index = 6;
    insertAfter(key, index);
    printf("insert %c after index %d: (%d)\n", key, index, len());
    display();

    v = get(0);
    printf("\nget(0): %c\n", v);
    v = get(3);
    printf("get(3): %c\n", v);
    v = get(6);
    printf("get(6): %c\n", v);
    v = get(7);
    printf("get(7): %c\n", v);
    v = get(8);
    printf("get(8): %c\n", v);

    // search
    printf("\n");
    char searchList[] = "yorkUxyZAb";
    int len = strlen(searchList);
    i = 0;
    while (i < len)
    {
        char key = *(searchList + i);
        printf("search %c ....  ", key);

        if (search(key))
            printf("found\n");
        else
            printf("not found\n");
        i++;
    }
}

/* Initialize the list. */
void init()
{
    head = NULL;
}

/* Print the content of the list. */
void display()
{
    if (head == NULL)
    {
        printf("\n");
        return;
    }
    struct node *current = head;
    while (current->next != NULL)
    {
        printf("%3c", current->data); // *(current).data
        current = current->next;      // current = *(current).next;
    }                                 //printf( "\n" );
    printf("%3c", current->data);
    printf("    <-->  ");
    while (current != NULL)
    {
        printf("%3c", current->data); // *(current).data
        current = current->prev;      // current = *(current).prev;
    }
    printf("\n");
}

/* return the length of the linked list */
int len()
{
    struct node *curr = head;
    int length = 0;
    while (curr != NULL)
    {
        length++;
        curr = curr->next;
    }
    return length;
}

/* get the data at node index */
char get(int index)
{
    struct node *curr = head;
    int i;
    for (i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->data;
}

/* search the list for key, return whether it is found */
int search(char key)
{
    struct node *curr = malloc(sizeof(struct node));
    for(curr = head; curr != NULL; curr = curr->next){
        if(curr->data == key){
            return 1;
        }
    }
    return 0;
}

/* Insert a new data element with key d into the end of the list. */
/* Hint: You need to consider the special case that the list is empty,
   and the general case that the list is not empty */

void insert(char c) //  at the end
{
    struct node *curr = head;
    struct node *newNodeP = malloc(sizeof(struct node));
    /* special case: list is empty, need to change head  */
    if (head == NULL)
    { /* the list is empty */

        newNodeP->data = c;
        newNodeP->next = NULL;
        newNodeP->prev = NULL;
        head = newNodeP;
    }
    else
    {
        while (curr->next != NULL)
        {
            curr = curr->next;
        }

        newNodeP->data = c;
        newNodeP->next = curr->next;
        newNodeP->prev = curr;
        curr->next = newNodeP;
    }
}

/* insert in the middle.
  insert new node with data d, after the node of index 'index'
  assume the list is not empty, and index is in [0, len()-1]
 */
void insertAfter(char c, int index)
{
    struct node *curr = head;
    struct node *newNodeP = malloc(sizeof(struct node));
    int i = 0;
    for (i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    newNodeP->data = c;
    newNodeP->next = curr->next;
    curr->next->prev = newNodeP;
    curr->next = newNodeP;
    newNodeP->prev = curr;
}

/* lab version */
/* Remove the node with value d from the list */
/* assume the list is not empty */
/* assume no duplicated keys in the list */
/* assume the node to be deleted is in the list */
/* You do not have to free the space (welcome to do so)  */
void delete (char d)
{
    /* special case: to be removed is the first, need to change head  */
    if (head->data == d)
    {
        // IF THERE IS ONLY ONE ELEMENT THEN REMOVE IT BY POINTING THE HEAD TO A NULL VALUE
        if (len() == 1)
        {
            head = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }
    }

    else // general case, remove from the middle or the last
    {
        struct node *curr = head;
        while (curr->data != d)
        {
            curr = curr->next;
        }

        // REMOVING LAST ELEMENT
        if (curr->next == NULL)
        {
            curr->prev->next = NULL;
            curr->prev = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
    }
}
