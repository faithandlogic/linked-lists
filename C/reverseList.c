// imports libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definition of a node for a singly linked list
typedef struct node {
    char* name;
    struct node* next;
}
node;

// prototypes of functions, easy reference for parameters and return values
// prints the data of all nodes of list
void printList(node* list);
// appends a node to the end of the list
node* appendNode(node *list, char* data);
// allocates memory for a new node (used within functions)
node* allocNode(node *list);
// inserts node before a specified data within list
node* insertNodeBefore(node *list, char* data, char* nextData);
// prepends a node to the start of the list
node* prependNode(node *list, char* data);
// inserts a node after a specified data within the linked list
node* insertNodeAfter(node *list, char* data, char* nextData);
// deletes a node from the list
node* removeNode(node* list, char* data);
// returns middle node of the list
node* middleList(node* list);
// reverses the entire linked list example: [1,2,3] -> [3,2,1]
node* reverseList(node *list);

int main(void) {
    // list named 'list' is initialized with a head string "Nuh"
    node* list = appendNode(NULL,"Nuh");
    // "Yusuf" is added to the end of the list
    appendNode(list,"Yusuf");
    // "Musa" is added to the end of the list
    appendNode(list,"Musa");
    // "Eesa" is inserted before "Yusuf"
    insertNodeBefore(list,"Yaqub", "Yusuf");
    // prepends "Adam" to the lsit, "list" / the head of the list is assigned to a new node, whose data is "Adam", whose next is node points to previous head
    list = prependNode(list, "Adam");
    // prints all the nodes in the list
    printList(list);
    // reverses all the pointers of the current list and reassigns the tail to the head
    list = reverseList(list);
    // prints all the nodes of the newly reversed list
    printList(list);
}
/**
 * @brief allocates memory for a node, checks if memory is available
 * @param list head of the list used to free the list if there is no memory available
 * @return node* returns empty node
 */
node* allocNode(node* list) {
    node *n = malloc(sizeof(node));
    if(n == NULL) {
        node *tmp = list->next;
        while(list != NULL) {
            tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return n;
}
/**
 * @brief adds node to the end of a list
 * 
 * @param list used for allocNode() to create a new node, used to traverse list and append a node to the tail
 * @param data used to assign a data value to the new node
 * @return node* returns the new completed node
 */
node* appendNode(node* list, char* data) {
    node *n = allocNode(list);
    if(n != NULL) {
        n->name = data;
        n->next = NULL;
        if (list==NULL) {
            return n;
        }
        while(list->next != NULL) {
            list = list->next;
        }
        // list is tail now
        list->next = n;
    }
    return n;
}
/**
 * @brief inserts a node before the node with the provided data
 * 
 * @param list used to traverse list through head
 * @param data data of node to be inserted
 * @param nextData data of node to come after new node
 * @return node*
 */
node* insertNodeBefore(node* list, char* data, char* nextData) {
    node* n = allocNode(list);
    if(n != NULL) {
        n->name = data;
        n->next = NULL;
        //n->next = list->next;
        if (list->next==NULL) {
            return n;
        }
        while(list->next->name != nextData) {
            list = list->next;
            if (list->next ==NULL) {
                printf("Warning: %s not found for insertion before\n", nextData);
                return NULL;
            }
        }
        n->next = list->next;
        list->next = n;
    }
    return n;
}
/**
 * @brief inserts node after given data
 * 
 * @param list used to traverse list 
 * @param data datat of new node to be inserted
 * @param beforeData data of node that will be right before new node
 * @return node* 
 */
node* insertNodeAfter(node* list, char* data, char* beforeData) {
    node* n = allocNode(list);
    if(n != NULL) {
        n->name = data;
        n->next = NULL;
        if (list->next==NULL) {
            return n;
        }
        while(list->next->name != beforeData) {
            list = list->next;
            if (list->next == NULL) {
                printf("Warning: %s not found for insertion \n", beforeData);
                return NULL;
            }
        }
        n->next = list->next->next->next;
        list->next->next = n;
    }
    return n;
}
/**
 * @brief creates a new head of the list
 * 
 * @param list used to prepend node before the head
 * @param data data of new node
 * @return node* 
 */
node* prependNode(node* list, char* data){
    node *n = allocNode(list);
    n->next = list;
    list = n;
    list->name = data;
    return list;
}
/**
 * @brief reverses entire list 
 * 
 * @param list used to traverse list
 * @return node* returned in order to set new head
 */
node* reverseList(node* list) {
    node* previous = allocNode(list);
    node* next = allocNode(list);
    previous = NULL;
    for(node* current = list;current != NULL;current = next){
        next = current->next;
        current->next = previous;
        previous = current;
    }
    list = previous;
    return list;
}
/**
 * @brief deletes a node from list
 * 
 * @param list used to traverse node
 * @param data used to identify node to be deleted
 * @return node* 
 */
node* removeNode(node* list, char* data) {
    node* delete = list;
    node* previous = allocNode(list);
    if (delete != NULL && delete->name == data) {
        list = delete->next; // Changed head
        free(delete); // free old head
        return list;
    }
    while (delete->name != data) {
        previous = delete;
        delete = delete->next;
    }
    previous->next = delete->next;
    return list;
}
/**
 * @brief prints list using loop
 * @param list used to traverse each node, starts from head
 */
void printList(node* list) {
    for(node* current = list;current != NULL;current = current->next) {
        printf("%s\n", current->name );
    }
    printf("\n");
    return;
}
/**
 * @brief two pointers traverse list one at double speed
 * 
 * @param list original list to be traversed
 * @return node* final tmp value returned as middle
 */
node* middleList(node* list) {
    int count = 0;
    node* tmp = list;
    for(; list != NULL && list->next !=NULL; list = list->next->next) {
         tmp = tmp->next; 
    }
    return tmp;
}
