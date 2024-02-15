#include "queue.h"


struct node_t* create_queue(struct task_t* task, int size)
{
    // Create the sentinel node at the base of the queue
    struct node_t* queue = create_new_node(NULL);

    // Verify that malloc didn't fail
    if(queue == NULL)
    {
        fprintf(stderr, "create_queue() ERROR: Malloc failed!\n");
        return NULL;
    }

    struct node_t* currentNode = queue;

    // Create and link nodes together to form the queue
    // NOTE: The first "true" node in the queue is linked to the sentinel
    for(int i = 0; i < size; i++)
    {
        currentNode->next = create_new_node(&(task[i]));
        currentNode = currentNode->next;

        if(currentNode == NULL)
        {
            fprintf(stderr, "create_queue() ERROR: Couldn't create a new node!\n");
            return NULL;
        }
    }

    return queue;
}


struct node_t* create_new_node(struct task_t* task)
{
    // Dynamically allocate memory for the new node
    struct node_t* newNode = (struct node_t*)malloc(sizeof(struct node_t));
    
    // Verify that malloc didn't fail
    if(newNode == NULL)
    {
        fprintf(stderr, "create_queue() ERROR: Malloc failed\n");
        return NULL;
    }

    // Initialize node data members
    newNode->task = task;
    newNode->next = NULL;

    return newNode;
}


struct task_t* peek(struct node_t** head)
{
    // Return the top-most task of the queue
    return (*head)->task;
}


void pop(struct node_t** head)
{
    // Check if the queue is empty
    if(is_empty(head))
    {
        return;
    }

    // Pop the old head
    struct node_t* oldHead = *head;
    *head = (*head)->next;

    // Free the memory allocated for the popped head
    free(oldHead);
}


void push(struct node_t** head, struct task_t* task)
{
    // Verify that the queue is initialized properly
    if(head == NULL)
    {
        fprintf(stderr, "push() ERROR: Queue is uninitialized!\n");
        return;
    }

    // Traverse to find the end of the queue
    struct node_t* currentNode = *head;
    while((currentNode != NULL) && (currentNode->next != NULL))
    {
        currentNode = currentNode->next;
    }

    // Create a new node
    struct node_t* newNode = create_new_node(task);

    // Verify that the newNode was created properly
    if(newNode == NULL)
    {
        fprintf(stderr, "push() ERROR: Couldn't create a new node!\n");
        return;
    }

    // Append the node
    if(currentNode == NULL)
    {
        // queue was empty, append to the head
        *head = newNode;
    }
    else
    {
        // Append to the end of the queue
        currentNode->next = newNode;
    }
}


int is_empty(struct node_t** head)
{
    // Verify the first pointer is valid before trying to
    // dereference the second pointer (which would be UB)
    return ((head == NULL) || (*head == NULL));
}


void empty_queue(struct node_t** head)
{
    // Check if queue is empty or uninitialized
    if(is_empty(head))
    {
        return;
    }

    struct node_t* currentNode = *head;
    struct node_t* nextNode;

    // Traverse the queue and free each node
    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    *head = NULL;
}
