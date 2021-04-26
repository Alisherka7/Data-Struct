#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
#define Element int

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

int n;


void init_deque() {
    front = rear = 0;
}

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int is_empty() {
    return (front == rear);
}

int size(){
    return (rear-front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
}

int is_full() {
    return ((rear+1)%MAX_QUEUE_SIZE == front);
}

void print_queue(char msg[]) {
    printf("%s[%d] = ", msg, size());

    if (!is_empty()) {
            int i = front;
            do {
                i = (i + 1) % (MAX_QUEUE_SIZE);
                printf(" %d ", data[i]);
                if (i == rear){
                    break;
                }
            } while (i != front);
        }
        printf("\n");
}



void add_rear(Element item) {
    if (is_full()) {
        error("큐 포화 상태 !!");
    }

    rear = (rear+1)%MAX_QUEUE_SIZE;
    data[rear] = item;
}


Element delete_front() {
    if (is_empty())
        error("큐 공백 상태 !!");

    front = (front+1)%MAX_QUEUE_SIZE;

    return data[front];
}


Element get_front() {
    if (is_empty())
        error("큐 공백 상태 !!");

    return data[(front+1)%MAX_QUEUE_SIZE];
}

void add_front(Element val) {
    if (is_full())
        error("큐 포화 상태 !!");

    data[front] = val;
    front=(front-1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

Element delete_rear() {
    int prev = rear;

    if (is_empty())
        error("큐 공백 상태 !!");

    rear = (rear-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;

    return data[prev];
}

Element get_rear() {
    if (is_empty())
        error("큐 공백 상태 !!");

    return data[rear];
}

int main() {


    init_deque();
    for (int i=1; i<10; i++) {
        if(i%2){
            add_front(i);
        }
        else{
            add_rear(i);
        }
    }
    
    
    printf("학번: 201968063 | 이름: 알레셰르\n");
    print_queue("원형 덱 홀수-짝수 ");
    printf("\tdelete_front() --> %d\n", delete_front());
    printf("\tdelete_front() --> %d\n", delete_rear());
    printf("\tdelete_front() --> %d\n", delete_front());
    print_queue("원형 덱 삭제-홀짝홀 ");
}

