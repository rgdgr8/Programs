#include <stdio.h>
#define SIZE 5

int *items;
int *front, *rear;

// Check if the queue is full
int isFull() {
	if ((*front == *rear + 1) || (*front == 0 && *rear == SIZE - 1)) return 1;
	return 0;
}

// Check if the queue is empty
int isEmpty() {
	if (*front == -1) return 1;
	return 0;
}

// Adding an element
int enQueue(int element) {
	if (isFull())
		return 0;
	else {
		if (*front == -1) *front = 0;
		*rear = (*rear + 1) % SIZE;
		items[*rear] = element;
		return 1;
	}
}

// Removing an element
int deQueue() {
	int element;
	if (isEmpty()) {
		return 0;
	} else {
		element = items[*front];
		if (*front == *rear) {
			*front = -1;
			*rear = -1;
		} 
		// Q has only one element, so we reset the 
		// queue after dequeing it. ?
		else {
			*front = (*front + 1) % SIZE;
		}
		return (element);
	}
}

// Display the queue
void display() {
	int i;
	if (isEmpty())
		printf("Empty Queue\n");
	else {
		//printf("Front -> %d ", *front);
		printf("Items -> ");
		for (i = *front; i != *rear; i = (i + 1) % SIZE) {
			printf("%d ", items[i]);
		}
		printf("%d\n", items[i]);
		//printf("\n Rear -> %d \n", *rear);
	}
}
