#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 100
#define Element int


Element data[MAX_QUEUE_SIZE];
int front;
int rear;

int n;

void init_queue(){
    front = rear = 0;
}

int is_empty(){
    return front == rear;
}

int is_full(){
    return (rear+1)%MAX_QUEUE_SIZE == front;
}

int size(){
    return (rear-front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
}

void enqueue(int d){
    if(is_full()){
        printf("Queue is full\n");
        return;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = d;
}

int dequeue(){
    if(is_empty()){
        printf("Queue is empty\n");
        return 0;
    }
    front = (front + 1)%MAX_QUEUE_SIZE;
    return data[front];
}


void print_queue(char msg[]) {
    printf("%s[%d] = ", msg, size());
    
    if (!is_empty()) {
            int i = front;
            do {
                i = (i + 1) % (MAX_QUEUE_SIZE);
                printf(" %d ", data[i]);
                if (i == rear)
                    break;
            } while (i != front);
        }
        printf("\n");
}



int main(){
    int i;
    init_queue();
    for(i=1; i<10; i++){
        enqueue(i);
    }
    print_queue("선형큐 enqueue 9회");
    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());
    print_queue("선형큐 dequeue 3회");
    return 0;
}

