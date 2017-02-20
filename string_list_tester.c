/* string_list_tester.c
  
   SENG 265 - Summer 2016
   Assignment 2
   
   Template for a tester for the StringList datatype.
   
   Do not change any of the function signatures or the contents
   of main() or your submission may be invalid.
  
   B. Bird - 05/26/2016
   
   Stephanie Goodale
   V00832053
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_list.h"

#define TEST_FAILED 0
#define TEST_PASSED 1

/* Each of the test functions below should return TEST_FAILED if the test fails
   and TEST_PASSED if the test is passed.
*/

int test1(){
	//First test case: Basic functionality I
	//Test only the StringList_Init, StringList_Size,
	//and StringList_AddFront functions.
	//(Note that since you cannot use StringList_Destroy, this function
	// will produce a memory leak. However, this is acceptable in a testing
	// context).
	printf("Test case 1: _Init, _Size, _AddFront\n");
	StringList L;
	StringList_Init(&L);
	//test size
	int size = StringList_Size(&L);
	if (size != 0) {
		return TEST_FAILED;
	}
	//add one
	char* str = "Hello";
	StringList_AddFront(&L, str);
	size = StringList_Size(&L);
	if (size != 1) {
		return TEST_FAILED;
	}
	//add two
	str = "CSC";
	StringList_AddFront(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}
	//print
	/*
	StringListNode* a = StringList_GetIndex(&L, 0);
	printf("Element 1: %s\n", a->element);
	StringListNode* b = StringList_GetIndex(&L, 1);
	printf("Element 2: %s\n", b->element);
	StringListNode* c = StringList_GetIndex(&L, 2);
	printf("Element 3: %s\n", c->element);
	*/
	
	return TEST_PASSED;
}

int test2(){
	//Second test case: Basic functionality II
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	printf("Test case 2: _Init, _Size, _AddFront, _AddBack\n");
	StringList L;
	StringList_Init(&L);
	//test size
	int size = StringList_Size(&L);
	if (size != 0) {
		return TEST_FAILED;
	}
	//add one
	char* str = "Hello";
	StringList_AddBack(&L, str);
	size = StringList_Size(&L);
	if (size != 1) {
		return TEST_FAILED;
	}
	//add two
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}
	
	return TEST_PASSED;
}

int test3(){
	//Third test case: Basic functionality III
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	//Use a different methodology for this test than test 2.
	//Second test case: Basic functionality II
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	printf("Test case 3: _Init, _Size, _AddFront, _AddBack\n");
	StringList L;
	StringList_Init(&L);
	//test size
	int size = StringList_Size(&L);
	if (size != 0) {
		return TEST_FAILED;
	}
	//add one
	char* str = "Hello";
	StringList_AddBack(&L, str);
	size = StringList_Size(&L);
	if (size != 1) {
		return TEST_FAILED;
	}
	//add two
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	str = "Bill";
	StringList_AddFront(&L, str);
	str = "Bird";
	StringList_AddFront(&L, str);
	size = StringList_Size(&L);
	if (size != 5) {
		return TEST_FAILED;
	}
	
	return TEST_PASSED;
}

int test4(){
	//Fourth test case: List membership I
	//Test the StringList_GetIndex function, using any of the functions
	//tested in previous test cases if necessary.
	printf("Test case 4: _Init, _Size, _AddFront, _AddBack, _GetIndex\n");
	StringList L;
	StringList_Init(&L);
	//test size and nullity of head
	int size = StringList_Size(&L);
	StringListNode* head = StringList_GetIndex(&L, 0);
	if (size != 0 || head != NULL) {
		return TEST_FAILED;
	}

	//add one
	char* str = "Hello";
	StringList_AddBack(&L, str);
	size = StringList_Size(&L);
	StringListNode* last = StringList_GetIndex(&L, size-1);
	if (size != 1 || strcmp(last->element, str) != 0) {
		return TEST_FAILED;
	}
	//add two
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}

	//test valid index retrievals
	StringListNode* a = StringList_GetIndex(&L, 0);
	StringListNode* b = StringList_GetIndex(&L, 1);
	StringListNode* c = StringList_GetIndex(&L, 2);
	if (strcmp(a->element, "265") != 0 ||
	strcmp(b->element, "Hello") != 0 ||
	strcmp(c->element, "CSC") != 0) {
		return TEST_FAILED;
	}
	
	//test out of bounds index
	if (StringList_GetIndex(&L, 3) != NULL) {
		return TEST_FAILED;
	}
	
	return TEST_PASSED;
}

int test5(){
	//Fifth test case: List membership II
	//Test the StringList_InList function, using any of the functions
	//tested in previous test cases if necessary.
	printf("Test case 5: _Init, _Size, _AddFront, _AddBack, _GetIndex, _InList\n");
	StringList L;
	StringList_Init(&L);
	
	//test string not in list
	char* word = "Why";
	if (StringList_InList(&L, word) != NULL) {
		return TEST_FAILED;
	}

	//add three
	char* str = "Hello";
	StringList_AddBack(&L, str);
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);

	int size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}

	//test valid strings in list
	StringListNode* a = StringList_InList(&L, "CSC");
	StringListNode* b = StringList_InList(&L, "Hello");
	StringListNode* c = StringList_InList(&L, "265");
	
	StringListNode* d = StringList_GetIndex(&L, 0);
	StringListNode* e = StringList_GetIndex(&L, 1);
	StringListNode* f = StringList_GetIndex(&L, 2);

	if (c != d || b != e || a != f) {
		return TEST_FAILED;
	}

	//test out of bounds index
	word = "Bill Bird";
	if (StringList_InList(&L, word) != NULL) {
		return TEST_FAILED;
	}
	
	return TEST_PASSED;
}

int test6(){
	//Sixth test case: Deletion I
	//Test the StringList_Remove and StringList_RemoveNode functions,
	//using any of the functions tested in previous test cases if necessary.
	printf("Test case 6: _Init, _Size, _AddFront, _AddBack, _GetIndex, _InList, _Remove, _RemoveNode\n");
	StringList L;
	StringList_Init(&L);
	
	//Test word not in list
	char* word = "Bill";
	if (StringList_Remove(&L, word) != 0) {
		return TEST_FAILED;
	}	

	//add five
	char* str = "Hello";
	StringList_AddBack(&L, str);
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	str = "265";
	StringList_AddBack(&L, str);
	str = "computer";
	StringList_AddBack(&L, str);

	int size = StringList_Size(&L);
	if (size != 5) {
		return TEST_FAILED;
	}
	
	//test word not in list
	word = "Nothing";
	if (StringList_Remove(&L, word) != 0){
		return TEST_FAILED;
	}
	
	//test remove method using string
	//test removing head
	word = "265";
	StringList_Remove(&L, word);
	StringListNode* a = StringList_GetIndex(&L, 0);
	StringListNode* b = StringList_GetIndex(&L, 1);
	StringListNode* c = StringList_GetIndex(&L, 2);
	StringListNode* d = StringList_GetIndex(&L, 3);
	size = StringList_Size(&L);
	if (size != 4) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "CSC") != 0 ||
	strcmp(c->element, "265") != 0 ||
	strcmp(d->element, "computer") != 0) {
		return TEST_FAILED;
	}

	//test removing tail
	word = "computer";
	StringList_Remove(&L, word);
	a = StringList_GetIndex(&L, 0);
	b = StringList_GetIndex(&L, 1);
	c = StringList_GetIndex(&L, 2);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "CSC") != 0 ||
	strcmp(c->element, "265") != 0) {
		return TEST_FAILED;
	}
	
	//test removing in between word
	word = "CSC";
	StringList_Remove(&L, word);
	a = StringList_GetIndex(&L, 0);
	b = StringList_GetIndex(&L, 1);
	size = StringList_Size(&L);
	if (size != 2) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "265") != 0) {
		return TEST_FAILED;
	}
	
	//test remove method using node
	//add some nodes
	str = "School";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	str = "Bill Bird";
	StringList_AddBack(&L, str);
	size = StringList_Size(&L);
	if (size != 5) {
		return TEST_FAILED;
	}

	//test removing head
	StringListNode* remove = StringList_GetIndex(&L, 0);
	StringList_RemoveNode(&L, remove);
	a = StringList_GetIndex(&L, 0);
	b = StringList_GetIndex(&L, 1);
	c = StringList_GetIndex(&L, 2);
	d = StringList_GetIndex(&L, 3);
	size = StringList_Size(&L);
	if (size != 4) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "265") != 0 ||
	strcmp(c->element, "School") != 0 ||
	strcmp(d->element, "Bill Bird") != 0) {
		return TEST_FAILED;
	}
	
	//test removing tail
	remove = StringList_GetIndex(&L, 3);
	StringList_RemoveNode(&L, remove);
	a = StringList_GetIndex(&L, 0);
	b = StringList_GetIndex(&L, 1);
	c = StringList_GetIndex(&L, 2);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "265") != 0 ||
	strcmp(c->element, "School") != 0) {
		return TEST_FAILED;
	}

	//test removing in between word
	remove = StringList_GetIndex(&L, 1);
	StringList_RemoveNode(&L, remove);
	a = StringList_GetIndex(&L, 0);
	b = StringList_GetIndex(&L, 1);
	size = StringList_Size(&L);
	if (size != 2) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "School") != 0) {
		return TEST_FAILED;
	}

	return TEST_PASSED;
}

int test7(){
	//Seventh test case: Deletion II
	//Test the StringList_Remove, StringList_RemoveNode and StringList_Destroy functions,
	//using any of the functions tested in previous test cases if necessary.
	//Use a different methodology for this test than test 6.
	printf("Test case 7: _Init, _Size, _AddFront, _AddBack, _GetIndex, _InList, _Remove, _RemoveNode, _Destroy\n");
	StringList L;	
	StringList_Init(&L);
	
	//test destroy
	StringList_Destroy(&L);
	StringListNode* head = StringList_GetIndex(&L, 0);
	int size = StringList_Size(&L);
	if (size != 0 || head != NULL) {
		return TEST_FAILED;
	}	
		
	//add three
	char* str = "Hello";
	StringList_AddBack(&L, str);
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}
	
	//test remove with string
	StringList_Remove(&L, "Hello");
	StringListNode* node = StringList_GetIndex(&L, 0);
	StringList_RemoveNode(&L, node);
	size = StringList_Size(&L);
	node = StringList_GetIndex(&L, 0);
	if (size != 1 || strcmp(node->element, "CSC") != 0) {
		return TEST_FAILED;
	}

	str = "dad";
	StringList_AddBack(&L, str);
	
	//test destroy
	StringList_Destroy(&L);
	head = StringList_GetIndex(&L, 0);
	size = StringList_Size(&L);
	if (size != 0 || head != NULL) {
		return TEST_FAILED;
	}
	
	return TEST_PASSED;
}

int test8(){
	//Eighth test case: Stress Test
	//Test all of the methods of the StringList, in an attempt to simulate the
	//actual use of the data structure in practice. For logistical reasons, 
	//keep in mind that your test must complete within 30 seconds for the 
	//automated system, so some types of exhaustive testing are not practical
	//here.
	printf("Test case 8: Stress Test\n");
	//test Init
	StringList L;
	StringList_Init(&L);
	//test AddFront and AddBack
	char* str = "Hello";
	StringList_AddBack(&L, str);
	str = "CSC";
	StringList_AddBack(&L, str);
	str = "265";
	StringList_AddFront(&L, str);
	str = "265";
	StringList_AddBack(&L, str);
	str = "computer";
	StringList_AddBack(&L, str);
	
	//test Size
	int size = StringList_Size(&L);
	if (size != 5) {
		return TEST_FAILED;
	}
	
	//test Remove and RemoveNode methods
	char* word = "computer";
	StringList_Remove(&L, word);
	StringListNode* remove = StringList_GetIndex(&L, 0);
	StringList_RemoveNode(&L, remove);
	StringListNode* a = StringList_GetIndex(&L, 0);
	StringListNode* b = StringList_GetIndex(&L, 1);
	StringListNode* c = StringList_GetIndex(&L, 2);
	size = StringList_Size(&L);
	if (size != 3) {
		return TEST_FAILED;
	}
	if (strcmp(a->element, "Hello") != 0 ||
	strcmp(b->element, "CSC") != 0 ||
	strcmp(c->element, "265") != 0) {
		return TEST_FAILED;
	}

	char* arr[4] = {"Hello", "CSC", "265"};	

	//test forwards traversal
	StringListNode* curr = StringList_GetIndex(&L, 0);
	char* compare = arr[0];
	int i = 0;
	while (curr != NULL) {
		compare = arr[i];
		if (strcmp(compare, curr->element) != 0 ) {
			return TEST_FAILED;
		}
		curr = curr->next;
		i++;
	}

	//test backwards traversal
	curr = StringList_GetIndex(&L, size-1);
	compare = arr[size-1];
	i = size-1;
	while (curr != NULL) {
		compare = arr[i];
		if (strcmp(compare, curr->element) != 0 ) {
			return TEST_FAILED;
		}
		curr = curr->previous;
		i--;
	}
	
	//test InList
	word = "CSC";
	if (StringList_InList(&L, word) == NULL) {
		return TEST_FAILED;
	}	
	
	//test Destroy
	StringList_Destroy(&L);
	StringListNode* head = StringList_GetIndex(&L, 0);
	size = StringList_Size(&L);
	if (size != 0 || head != NULL) {
		return TEST_FAILED;
	}	
	
	return TEST_PASSED;

}




/* Do not change any of the code below, to ensure consistency during all vs. all testing */

void show_usage(){
	fprintf(stderr,"Usage: ./string_list_tester <test_number>\n");
	fprintf(stderr,"Where <test_number> is an integer between 1 and 8.\n");
}

int main(int argc, char** argv){
	if (argc < 2){
		show_usage();
		return 0;
	}
	//The atoi function converts a string to an integer (and returns 0 if
	//the conversion fails).
	int test_number = atoi(argv[1]);
	
	if (test_number <= 0 || test_number > 8){
		show_usage();
		return 0;
	}
	
	int result = 1;
	switch(test_number){
		case 1:
			result = test1();
			break;
		case 2:
			result = test2();
			break;
		case 3:
			result = test3();
			break;
		case 4:
			result = test4();
			break;
		case 5:
			result = test5();
			break;
		case 6:
			result = test6();
			break;
		case 7:
			result = test7();
			break;
		case 8:
			result = test8();
			break;
	}
	
	if (result == TEST_PASSED){
		printf("\nTEST PASSED\n");
	}else{
		printf("\nTEST FAILED\n");
	}
	
	return 0;
}
