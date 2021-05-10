#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int TElement;

typedef struct BinTrNode {
    TElement data;
    struct BinTrNode *left;
    struct BinTrNode *right;
} TNode;
TNode *root;


void init_tree() {root = NULL;}
int is_empty_tree() {return root == NULL;}
TNode* get_root() {return root;}

TNode* create_tree(TElement val, TNode* l, TNode* r) {
    TNode* n = (TNode*)malloc(sizeof(TNode));
    n->data = val;
    n->left = l;
    n->right= r;
    return n;
}

void preOrder(TNode* n) {
    if(n != NULL) {
        printf("[%c] ", n->data);
        preOrder(n->left);
        preOrder(n->right);
    }
}

void inOrder(TNode* n) {
    if(n != NULL) {
        inOrder(n->left);
        printf("[%c] ", n->data);
        inOrder(n->right);
    }
}

void postOrder(TNode* n) {
    if(n != NULL) {
        postOrder(n->left);
        postOrder(n->right);
        printf("[%c] ", n->data);
    }
}
//============================= Level Order
typedef TNode* Element;

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error(char str[])
{
    printf("%s \n", str);
    exit(1);
}

void init_queue()    {front = rear = 0;}
int is_empty()        {return front == rear;}
int is_full()        {return front == (rear + 1) % MAX_QUEUE_SIZE;}
int size()            {return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;}

void enqueue(Element val)
{
    if(is_full())
        error("큐 포화 에러");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element dequeue()
{
    if(is_empty())
        error("큐 공백 에러");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}


void levelorder(TNode* root) {
    TNode* n;
    
    if(root == NULL) return;
    init_queue();
    enqueue(root);
    while(!is_empty()) {
        n = dequeue();
        if(n != NULL) {
            printf("[%c] ", n->data);
            enqueue(n->left);
            enqueue(n->right);
        }
    }
}


int calc_size(TNode* n) {
    if (n == NULL) return 0;
    return n->data + calc_size(n->left) + calc_size(n->right);
}
 

int main()
{
    TNode* b, * c, * d, * e, * f;
    init_tree();
    d = create_tree('D', NULL, NULL);
    e = create_tree('E', NULL, NULL);
    b = create_tree('B', d, e);
    f = create_tree('F', NULL, NULL);
    c = create_tree('C', f, NULL);
    root = create_tree('A', b, c);
    
    printf("이름: 알레셰르 | 학번: 201968063\n");
    printf("\n In-Order : ");
    inOrder(root);
    
    printf("\n Pre-Order : ");
    preOrder(root);
    
    printf("\n Post-Order : ");
    postOrder(root);
    
    printf("\n Level-Order : ");
    levelorder(root);
    printf("\n");

}

