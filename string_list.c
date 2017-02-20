/* string_list.c
   05/26/2016
   
   Stephanie Goodale
   V00832053 
   
   SENG 265 - Summer 2016
   Assignment 2
  
   Implementatins of a linked list containing C strings.
*/

#include "string_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* StringList_init(L)
   Initialize the provided StringList instance.
   
   Pre-conditions:
     L is a pointer to a StringList struct.
   Post-conditions:
     The head and tail pointers of L have been
     initialized to NULL.
*/ 
void StringList_Init(StringList* L) {
	L->head = NULL;
	L->tail = NULL;
}

/* StringList_destroy(L)
   Free all storage associated with each node of the StringList
   object and reset all pointers to NULL.
   
   Pre-conditions:
     L is a pointer to a StringList struct which has been
	 initialized with StringList_init and has not already
	 been destroyed.
   Post-conditions:
     Each node of L, and its associated string, has been freed.
	 The head and tail pointers of L have been set to NULL.
*/ 
/*
void StringList_Destroy(StringList* L) {
	int size = StringList_Size(L);
	StringListNode* curr = StringList_GetIndex(L, 0);
	for (int i = 0; i < size; i++) {
		curr = StringList_GetIndex(L, i);
		if (curr != NULL) {	
			StringList_RemoveNode(L, curr);
		}
	}
	L->head = NULL;
	L->tail = NULL;
}
*/
void StringList_Destroy(StringList* L) {
	while (L->head != NULL) {
		StringList_RemoveNode(L, L->head);
	}
	L->head = NULL;
	L->tail = NULL;
}



/* StringList_size(L)
   Return the number of nodes in the list L
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
   Return value:
     The number of nodes in L.
*/ 
int StringList_Size(StringList* L){
	int count = 0;
	StringListNode* curr = L->head;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;	
}


/* StringList_AddFront(L, str)
   Create a new list node containing a copy of the string str and
   add the node to the front (head) of the list L.
   
   Note: The created node must not contain a pointer to the string
   str. Instead, it should contain a pointer to a new array containing
   a copy of str.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     A new node containing a copy of str has been attached
	 to the beginning of the list L.
   Return value:
     A pointer to the created node.
*/ 
StringListNode* StringList_AddFront(StringList* L, char* str) {
	StringListNode* curr = (StringListNode*)malloc(sizeof(StringListNode));
	curr->element = (char*)malloc((strlen(str)+1)*sizeof(char));
	strcpy(curr->element, str);
	if (L->head == NULL) {
		L->head = curr;
		L->tail = curr;
		curr->previous = NULL;
		curr->next = NULL;
	} else {
		L->head->previous = curr;
		curr->next = L->head;
		curr->previous = NULL;
		L->head = curr;
	}
	return L->head;
}


/* StringList_AddBack(L, str)
   Create a new list node containing a copy of the string str and
   add the node to the back (tail) of the list L.
   
   Note: The created node must not contain a pointer to the string
   str. Instead, it should contain a pointer to a new array containing
   a copy of str.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     A new node containing a copy of str has been attached
	 to the end of the list L.
   Return value:
     A pointer to the created node.
*/ 
StringListNode* StringList_AddBack(StringList* L, char* str){
	StringListNode* curr = (StringListNode*)malloc(sizeof(StringListNode));
	curr->element = (char*)malloc(strlen(str)*sizeof(char*));
	strcpy(curr->element, str);
	if (L->tail == NULL) {
		L->head = curr;
		L->tail = curr;
		curr->previous = NULL;
		curr->next = NULL;
	} else {
		L->tail->next = curr;
		curr->previous = L->tail;
		curr->next = NULL;
		L->tail = curr;
	}
	return L->tail;
}

/* StringList_remove(L, str)
   Search the list L for a node containing the provided string str
   and remove the first such node if it is present.
   
   Note that the removal process should free all storage associated
   with the node and the string it contains.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     If a node containing str was found, it has been removed
	 from the list L.
   Return value:
     1 if a node containing str was found.
	 0 otherwise.
*/ 
/*
int StringList_Remove(StringList* L, char* str) {
	int result = 0;
	if (L->head == NULL) {
		return 0;
	}
	assert(L->head != NULL && L->tail != NULL);
	StringListNode* curr = L->head;
	if (StringList_Size(L) == 1) {
		if (strcmp(L->head->element, str) == 0) {
			free(curr->element);
			free(curr);
			L->head = NULL;
			L->tail = NULL;
			result = 1;
		}
	} else if (strcmp(L->head->element, str) == 0) {
		L->head = curr->next;
		curr->next = NULL;
		L->head->previous = NULL;
		result = 1;
		free(curr->element);
		free(curr);
	} else if (strcmp(L->tail->element, str) == 0) {
		curr = L->tail;
		L->tail = curr->previous;
		curr->previous = NULL;
		L->tail->next = NULL;
		result = 1;
		free(curr->element);
		free(curr);
	} else {
		while (curr != NULL) {
			if (strcmp(curr->element, str) == 0) {
				StringListNode* after = curr->next;
				StringListNode* before = curr->previous;
				after->previous = before;
				before->next = after;
				free(curr->element);
				free(curr);
				result = 1;
			}
			curr = curr->next;
		}
	}
	return result;
}
*/
int StringList_Remove(StringList* L, char* str) {
	int result = 0;
	if (L->head == NULL || L->tail == NULL) {
		return 0;
	}
	StringListNode* curr = L->head;
	if (StringList_Size(L) == 1) {
		if (strcmp(L->head->element, str) == 0) {
			StringList_RemoveNode(L, L->head);
			result = 1;
		}
	} else if (strcmp(L->head->element, str) == 0) {
		StringList_RemoveNode(L, L->head);
		result = 1;
	} else if (strcmp(L->tail->element, str) == 0) {
		StringList_RemoveNode(L, L->tail);
		result = 1;
	} else {
		while (curr != NULL) {
			if (strcmp(curr->element, str) == 0) {
				StringList_RemoveNode(L, curr);
				result = 1;
			}
			curr = curr->next;
		}
	}
	return result;
}


/* StringList_RemoveNode(L, node)
   Remove the provided node from the list L.
   
   Note that the removal process should free all storage associated
   with the node and the string it contains.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 node points to a valid node in L.
   Post-conditions:
     node has been removed from L.
*/ 
void StringList_RemoveNode(StringList* L, StringListNode* node) {
	assert(node != NULL);
	assert(L->head != NULL && L->tail != NULL);

	int size = StringList_Size(L);
	
	if (node == L->head && size==1) {
		L->head = NULL;
		L->tail = NULL;
	} else if (node == L->head) {
		L->head = L->head->next;
		L->head->previous = NULL;
	} else if (node == L->tail) {
		L->tail = node->previous;
		assert(L->tail != NULL);
		L->tail->next = NULL;
	} else {
		StringListNode* after = node->next;
		StringListNode* before = node->previous;
		after->previous = before;
		before->next = after;
	}
	free(node->element);
	free(node);
}


/* StringList_InList(L, str)
   Search the list L for a node containing the provided string str
   and return a pointer to the first node containing str if it is found.
   
   The "first" node, in this context, refers to the first node encountered
   on a forward traversal of the list starting at the head.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Return value:
     A pointer to the first node containing str if it was found in the list.
	 NULL otherwise.
*/ 
StringListNode* StringList_InList(StringList* L, char* str){
	StringListNode* curr = L->head;
	while (curr != NULL) {
		if (strcmp(curr->element, str) == 0) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}


/* StringList_GetIndex(L, i)
   Return the node at the provided index i (where index 0 is 
   the node at the head of the list).
   
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
   Return value:
     A pointer to node i if 0 <= i <= size - 1 (where size is the
	 number of elements in the list.
	 NULL if i is not a valid index into the list.
*/ 
StringListNode* StringList_GetIndex(StringList* L, int i){
	if(i>=0 && i<StringList_Size(L)) {
		StringListNode* curr = L->head;	
		int index = 0;
		while (curr != NULL) {
			if (index == i) {
				return curr;
			}
			index++;
			curr = curr->next;
		}
	}
	return NULL;
}
