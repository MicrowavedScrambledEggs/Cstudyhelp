#include <stdio.h>

#define Node_Size sizeof(Name_Node)

typedef struct name_node{
	char name[60];
	struct name_node *next;
} Name_Node;

typedef struct {
	int size;
	struct name_node *start;
	struct name_node *end;
} Linked_List;

void add_top(Linked_List *linked_list);
void add_bot(Linked_List *linked_list);
void add_index(Linked_List *linked_list);
void print_top(Linked_List *linked_list);
void print_bot(Linked_List *linked_list);
void print_index(Linked_List *linked_list);
void print_all(Linked_List *linked_list);
void print_size(Linked_List *linked_list);
void is_empty(Linked_List *linked_list);
void delete_top(Linked_List *linked_list);
void delete_bot(Linked_List *linked_list);
void delete_index(Linked_List *linked_list);
void clear(Linked_List *linked_list);
void print_menu(void);


int main(void){
	
	int choice = 0;
	Linked_List linked_list;
	
	linked_list.size = 0;
	linked_list.start = NULL;
	linked_list.end = NULL;
	
	void (*func_array[13])(Linked_List *) = {is_empty, print_size, add_top, add_bot, 
		add_index, print_all, print_top, print_bot, print_index, delete_top, 
		delete_bot, delete_index, clear};
	
	printf("\nWelcome to string list maker\n");
	
	while(choice != 13){
		do{
			print_menu();
			scanf("%d", &choice);
		} while (choice < 0 || choice > 13);
		if(choice == 13) break;
		func_array[choice](&linked_list);
	}
	
	clear(&linked_list);
	return 0;
}

void print_menu(){
	int i;
	char *options[14] = {"Check list is empty", "Print the size of the list",
		"Add string at top", "Add string at bottom", "Add string at index",
		"Print all strings", "Print string at top of list", "Print string at bottom of list",
		"Print string at a specific index", "Delete string at top of list", 
		"Delete string at bottom of list", "Delete string at a specific index", 
		"Clear the list", "Exit program"};
	
	for(i = 0; i < 14; i++){
		printf("\n%d: %s", i, options[i]);
	}
	printf("\n\nEnter your choice: ");
}

void is_empty(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nList is empty\n");
	} else {
		printf("\nList is not empty\n");
	}
}

void print_size(Linked_List *linked_list){
	
	printf("\nList is size %d\n", linked_list->size);
}

void add_top(Linked_List *linked_list){
	
	Name_Node *to_add = malloc(Node_Size);
	
	printf("\nEnter string to add at top of list: ");
	scanf("%s", &(to_add->name));
	
	to_add->next = linked_list->start;
	linked_list->start = to_add;
	
	if(linked_list->size == 0){
		linked_list->end = to_add;
	}
	linked_list->size = linked_list->size + 1;
}

void add_bot(Linked_List *linked_list){
	
	Name_Node *to_add = malloc(Node_Size);
	
	printf("\nEnter string to add at bottom of list: ");
	scanf("%s", &(to_add->name));
	to_add->next = NULL;
	
	if(linked_list->size == 0){
		linked_list->end = to_add;
		linked_list->start = to_add;
		
	} else {
		linked_list->end->next = to_add;
		linked_list->end = to_add;
	}
	
	linked_list->size = linked_list->size + 1;
}

void add_index(Linked_List *linked_list){
	
	int index;
	
	do{
		printf("\nEnter index where you want to add string: ");
		scanf("%d", &index);
	} while (index < 0 || index > linked_list->size);
	
	if(index == 0){
		add_top(linked_list);
		return;
	} else if (index == linked_list->size){
		add_bot(linked_list);
		return;
	} else {
		int i = 0;
		Name_Node *iter = linked_list->start;
		while (i < index - 1){
			iter = iter->next;
			i++;
		}
		
		Name_Node *to_add = malloc(Node_Size);
		
		printf("Enter string to add at index %d: ", index);
		scanf("%s", &(to_add->name));
		
		to_add->next = iter->next;
		iter->next = to_add;
		
		linked_list->size = linked_list->size + 1;
	}
}

void print_all(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to print\n");
		return;
	}
	
	int i;
	Name_Node *to_print = linked_list->start;
	
	printf("\n");
	for(i = 0; to_print != NULL; i++){
		printf("%d: %s\n", i, to_print->name);
		to_print = to_print->next;
	}
}

void print_top(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to print\n");
		return;
	}
	
	printf("\nString at top: %s\n", linked_list->start->name);
}

void print_bot(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to print\n");
		return;
	}
	
	printf("\nString at bottom: %s\n", linked_list->end->name);
}

void print_index(Linked_List *linked_list){
	
	int index, i;
	Name_Node *to_print;
	
	do{
		printf("\nEnter index of string: ");
		scanf("%d", &index);
	} while (index < 0 || index >= linked_list->size);
	
	to_print = linked_list->start;
	for(i=0; i!=index; i++){
		to_print = to_print->next;
	}
	
	printf("%d: %s\n", index, to_print->name);
}

void delete_top(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to delete\n");
		return;
	}
	Name_Node *tmp = linked_list->start->next;
	free(linked_list->start);
	linked_list->start = tmp;
	linked_list->size = linked_list->size - 1;
}

void delete_bot(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to delete\n");
		return;
	}
		
	if(linked_list->start == linked_list->end){
		free(linked_list->start);
		linked_list->start = NULL;
		linked_list->end = NULL;
		linked_list->size = 0;
	} else {
		int i = 0;
		Name_Node *iter = linked_list->start;
		for(;i < linked_list->size - 2; i++)
			iter = iter->next;
		free(iter->next);
		iter->next = NULL;
		linked_list->end = iter;
		linked_list->size = linked_list->size - 1;
	}
}

void delete_index(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to delete\n");
		return;
	}
	
	int index, i;
	
	do{
		printf("\nEnter index to be deleted: ");
		scanf("%d", &index);
	} while (index < 0 || index >= linked_list->size);
	
	if(index == 0){
		delete_top(linked_list);
		return;
	} else if (index == linked_list->size-1){
		delete_bot(linked_list);
		return;
	} else {
		Name_Node *iter = linked_list->start;
		for(i = 0; i < index - 1; i++)
			iter = iter->next;
		Name_Node *tmp = iter->next->next;
		free(iter->next);
		iter->next = tmp;
		linked_list->size = linked_list->size - 1;
	}
}

void clear(Linked_List *linked_list){
	
	if(linked_list->size == 0){
		printf("\nNothing to delete\n");
		return;
	}
	
	Name_Node *to_free = linked_list->start;
	do{
		Name_Node *tmp = to_free->next;
		free(to_free);
		to_free = tmp;
	}while(to_free != NULL);
	
	linked_list->start = NULL;
	linked_list->end = NULL;
	linked_list->size = 0;
}