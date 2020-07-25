/*
 ============================================================================
 Name        : Prompt.c
 Author      :
 Version     :
 Copyright   :
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_entry(char *entry) {
	printf("You entered: %s\n", entry);
}

typedef struct linkedList{
	int value;
	struct linkedList *next;
	struct linkedList *prev;
} linkedList;

int get_value(linkedList *List, int ind){
	linkedList *p = List;
	int value;

	for(int i = 0; i < ind; i++){
		value = p->value;
		p = p->next;
	}

	return value;
}

void insert_node(linkedList *List, int value){
	linkedList *p = List;
	linkedList *node = (linkedList*) malloc(sizeof(linkedList));
	node->value = value;
	node->next = NULL;

	while(p->next != NULL){
		p = p->next;
	}

	p->next = node;
	node->prev = p;
}

int remove_node(linkedList *List, int ind){
	linkedList *p = List, *pred;
	int value;

	for(int i = 0; i < ind-1; i++){
		value = p->value;
		pred = p;
		p = p->next;
	}

	pred->next = p->next;
	p->next->prev = pred;
	free(p);
	return value;
}

int get_value_from_string(char *string){
	int digit, value = 0;
	char c;

	for(int i = 0; i < strlen(string); i++){
		c = string[i];
		if(c >= '0' && c <= '9'){
			digit = c - '0';
			value = value*10 + digit;
		}
	}

	return value;
}

void list_elem(linkedList *List){
	linkedList *p = List;
	while(p != NULL){
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	char input[201];
	linkedList *head = NULL;
	int value, len_list = 0;

	while(1) {
		printf("prompt> ");
		if (fgets(input, 200, stdin) == NULL) {
			printf("An error ocurred.\n");
			break;
		}

		if (strncmp(input, "exit\n", 5) == 0) {
			//printf("Leaving. Good bye.\n");
			break;
		}

		if (strstr(input, "put") != NULL){
			value = get_value_from_string(input);
			if(head == NULL){
				linkedList *aux = malloc(sizeof(linkedList));
				aux->value = value;
				aux->next = NULL;
				aux->prev = NULL;
				head = aux;
			}
			else{
				insert_node(head, value);
			}
			len_list += 1;
			list_elem(head);
		}

		else if(strstr(input, "get") != NULL){
			value = get_value_from_string(input);
			if(head != NULL){
				printf("%d\n", get_value(head, value));
			}
		}

		else if(strncmp(input, "list\n", 5) == 0) {
			if(head != NULL){
				list_elem(head);
			}
		}

		else if(strstr(input, "remove") != NULL){
			value = get_value_from_string(input);
			if(head != NULL){
				if(value == 1){
					linkedList *aux;
					aux = head;
					head = head->next;
					head->prev = NULL;
					printf("%d\n", aux->value);
					free(aux);
				}
				else{
					printf("%d\n", remove_node(head, value));
				}
				len_list -= 1;
				list_elem(head);
			}
		}

		else if(strncmp(input, "clear\n", 6) == 0) {
			if(head != NULL){
				linkedList *p = head, *aux;
				while(p != NULL){
					aux = p;
					p = p->next;
					free(aux);
				}
				head = NULL;
				len_list = 0;
			}
		}

		else if(strncmp(input, "first\n", 6) == 0) {
			if(head != NULL){
				printf("%d\n", head->value);
			}
		}

		else if(strncmp(input, "last\n", 5) == 0) {
			if(head != NULL){
				linkedList *p = head;
				while(p->next != NULL){
					p = p->next;
				}
				printf("%d\n", p->value);
			}
		}

		//print_entry(input);
	}

	return EXIT_SUCCESS;
}
