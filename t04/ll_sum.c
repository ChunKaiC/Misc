#include <stdio.h>
#include <stdlib.h>


struct ll_node {
    int value;
    struct ll_node *next;
};


// This overly complex code reads integers from stdin and places them in 
// a linked list. Then, it sums the items in the list and prints the result.
int main() {
    int user_inp;
    int sum = 0;

    // Using a dummy head node
    struct ll_node *front = malloc(sizeof(struct ll_node));
    struct ll_node *current = front;
    struct ll_node *previous;

    while (scanf("%d", &user_inp) != EOF) {
	current->value = user_inp;
        current->next = malloc(sizeof(struct ll_node));
	previous = current;
        current = current->next;
    }
    free(current);
    previous->next = NULL;

    current = front;
    
    while (current != NULL) {
	sum += current->value;
	previous = current;
	current= current->next;
	free(previous);
    }
    printf("The sum of the inputs is %d.\n", sum);
    return 0; 
}
