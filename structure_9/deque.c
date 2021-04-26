
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} DequeType;

int size(DequeType *q){
    return (q->rear-q->front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
}


void init_deque(DequeType *q) {
    q->front = q->rear = 0;
}

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int is_empty(DequeType *q) {
    return (q->front == q->rear);
}

int is_full(DequeType *q) {
    return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}

void print_queue(DequeType *q, char msg[]) {
    int i = q->front;
    printf("%s[%d] = ", msg, size(q));

    if (!is_empty(q)) {
            int i = q->front;
            do {
                i = (i + 1) % (MAX_QUEUE_SIZE);
                printf(" %d ", q->data[i]);
                if (i == q->rear){
                    break;
                }
            } while (i != q->front);        }
        printf("\n");
}



void add_rear(DequeType *q, element item) {
    if (is_full(q)) {
        error("큐 포화 상태 !!");
    }

    q->rear = (q->rear+1)%MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}


element delete_front(DequeType *q) {
    if (is_empty(q))
        error("큐 공백 상태 !!");

    q->front = (q->front+1)%MAX_QUEUE_SIZE;

    return q->data[q->front];
}


element get_front(DequeType *q) {
    if (is_empty(q))
        error("큐 공백 상태 !!");

    return q->data[(q->front+1)%MAX_QUEUE_SIZE];
}

void add_front(DequeType *q, element val) {
    if (is_full(q))
        error("큐 포화 상태 !!");

    q->data[q->front] = val;
    q->front=(q->front-1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType *q) {
    int prev = q->rear;

    if (is_empty(q))
        error("큐 공백 상태 !!");

    q->rear = (q->rear-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;

    return q->data[prev];
}

element get_rear(DequeType *q) {
    if (is_empty(q))
        error("큐 공백 상태 !!");

    return q->data[q->rear];
}

int main() {
    DequeType queue;

    init_deque(&queue);
    for (int i=1; i<10; i++) {
        if(i%2){
            add_front(&queue, i);
        }
        else{
            add_rear(&queue, i);
        }
    }
    
    
    printf("학번: 201968063 | 이름: 알레셰르\n");
    print_queue(&queue, "원형 덱 홀수-짝수 ");
    printf("\tdelete_front() --> %d\n", delete_front(&queue));
    printf("\tdelete_front() --> %d\n", delete_rear(&queue));
    printf("\tdelete_front() --> %d\n", delete_front(&queue));
    print_queue(&queue, "원형 덱 삭제-홀짝홀 ");
}

