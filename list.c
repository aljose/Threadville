#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



typedef struct snode {
	pthread_t *threadPointer;
	struct snode *next;
} tnode;


typedef tnode *tpointer;

void insertFront(tpointer *head, pthread_t *pointer);
void printList(tpointer head);
void clearList(tpointer *head);

/*int main() {
	tpointer head;
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	head=NULL;
	printf("Insert -1 to finish\n");

	//scanf("%d", &e);
	insertFront(&head, &thread1);
	insertFront(&head, &thread2);
	insertFront(&head, &thread3);

	printList(head);
	clearList(&head);

	return 0;
}*/

void insertFront(tpointer *head,  pthread_t *pointer) {
	tpointer nuevo;
	nuevo=(tpointer) malloc(sizeof(tnode));
	nuevo->threadPointer=pointer;
	nuevo->next=*head;
	*head=nuevo;
}

void printList(tpointer head) {
	while(head!=NULL) {
		printf("%p\n", head->threadPointer);
		head=head->next;
	}
}

void clearList(tpointer *head) {
	tpointer current;
	while(*head!=NULL) {
		current=*head;
		*head=(*head)->next;
		free(current);
	}
}

