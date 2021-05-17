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

void init_tree(void) {root = NULL;}
int is_empty_tree(void) {return root == NULL;}
TNode* get_root(void) {return root;}

TNode* create_tree(TElement val, TNode* l, TNode* r) {
    TNode* n = (TNode*)malloc(sizeof(TNode));
    n->data = val;
    n->left = l;
    n->right= r;
    return n;
}

void preOrder(TNode* n) {
    if(n != NULL) {
        printf("[%2d] ", n->data);
        preOrder(n->left);
        preOrder(n->right);
    }
}

void inOrder(TNode* n) {
    if(n != NULL) {
        inOrder(n->left);
        printf("[%2d] ", n->data);
        inOrder(n->right);
    }
}

void postOrder(TNode* n) {
    if(n != NULL) {
        postOrder(n->left);
        postOrder(n->right);
        printf("[%2d] ", n->data);
    }
}


TNode* search(TNode *n, int key) {
    if(n == NULL)    return NULL;
    else if(key == n->data)    return n;
    else if(key < n->data) return search(n->left, key);
    else return search(n->right, key);
}

void search_BST(int key) {
    TNode* n = search(root, key);
    if(n != NULL)
        printf("[탐색 연산] : 성공 [%d] = 0x%x\n", n->data, n);
    else
        printf("[탐색 연산] : 실패 : No %d!\n", key);
}




typedef TNode* Element;


Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

void init_queue(void) { front = rear = 0; ; }
int is_empty(void) { return front == rear; }
int is_full(void) { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size(void) { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Element val)
{
    if (is_full())
        error(" 큐 포화 에러");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}
Element dequeue(void)
{
    if (is_empty())
        error(" 큐 공백 에러");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}
Element peek(void)
{
    if (is_empty())
        error(" 큐 공백 에러");
    return data[(front + 1) % MAX_QUEUE_SIZE];
}


void levelorder(TNode* root)
{
    TNode* n;
    if (root == NULL) return;
    init_queue();
    enqueue(root);
    while (!is_empty()) {
        n = dequeue();
        if (n != NULL) {
            printf("[%d] ", n->data);
            enqueue(n->left);
            enqueue(n->right);
        }
    }
}

int count_node(TNode* n)
{
    if (n == NULL) return 0;
    return 1 + count_node(n->left) + count_node(n->right);
}

int count_leaf(TNode* n)
{
    if (n == NULL) return 0;
    if (n->left == NULL && n->right == NULL) return 1;
    else return count_leaf(n->left) + count_leaf(n->right);
}

int calc_height(TNode* n)
{
    int hLeft, hRight;
    if (n == NULL) return 0;
    hLeft = calc_height(n->left);
    hRight = calc_height(n->right);
    return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}




int insert(TNode *r, TNode *n) {
    if(n->data == r->data) return 0;
    else if(n->data < r->data) {
        if(r->left == NULL)    r->left = n;
        else insert(r->left, n);
    }
    else {
        if(r->right == NULL) r->right = n;
        else insert(r->right, n);
    }
    return 1;
}

void insert_BST(int key) {
    TNode *n = create_tree(key, NULL, NULL);
    if(is_empty_tree())
        root = n;
    else if (insert(root, n) == 0)
        free(n);
}


void delete (TNode *parent, TNode *node) {
    TNode *child, *succ, *succp;
    
    //case 1: 단말 노드 삭제
    if((node->left == NULL && node->right == NULL)) {
        if(parent == NULL) root = NULL;
        else {
            if(parent->left == node)
                parent->left = NULL;
            else parent->right = NULL;
        }
    }
    

    else if(node->left == NULL || node->right == NULL) {
        child = (node->left != NULL) ? node->left : node->right;
        if(node == root) root = child;
        else {
            if (parent->left == node)
                parent->left = child;
            else parent->right = child;
        }
    }
    

    else {
        succp = node;
        succ = node->right;
        while(succ->left != NULL) {
            succp = succ;
            succ = succ->left;
        }
        if(succp->left == succ)
            succp->left = succ->right;
        else succp->right = succ->right;
        
        node->data = succ->data;
        node = succ;
    }
    

    free(node);
}

void delete_BST(int key) {
    TNode *parent = NULL;
    TNode *node = root;
    
    if(node == NULL) return;
    while(node != NULL && node->data != key) {
        parent = node;
        node = (key < node->data) ? node->left : node->right;
    }
    if(node == NULL)
        printf("Error: key is not in the tree!\n");
    else delete(parent, node);
}


 

int main()
{
    printf("이름: 알레셰르 | 학번: 201968063\n");
    printf("[삽입 연산] : 35 18 7 26 12 3 68 22 30 99");
    init_tree();
    insert_BST(35);    insert_BST(18);
    insert_BST(7);    insert_BST(26);
    insert_BST(12);    insert_BST(3);
    insert_BST(68);    insert_BST(22);
    insert_BST(30);    insert_BST(99);
    

    printf("\n   In-Order : ");    inOrder(root);
    printf("\n  Pre-Order : "); preOrder(root);
    printf("\n Post-Order : "); postOrder(root);
    printf("\n Level-Order : "); levelorder(root);
    printf("\n");
    printf(" 노드의 개수 = %d\n", count_node(root));
    printf(" 단말의 개수 = %d\n", count_leaf(root));
    printf(" 트리의 높이 = %d\n", calc_height(root));
    printf("\n");

    search_BST(26);
    search_BST(25);
    printf("\n");
    

    printf("original bintree:  LevelOrder: "); levelorder(root);
    printf("\n");
    printf("case1: < 3> 삭제 "); delete_BST(3);
    printf("   LevelOrder : ");        levelorder(root);
    printf("\n");
    printf("case2: <68> 삭제 ");    delete_BST(68);
    printf("   LevelOrder : ");        levelorder(root);
    printf("\n");
    printf("case3: <18> 삭제 ");    delete_BST(18);
    printf("   LevelOrder : ");        levelorder(root);
    printf("\n");
    printf("case3: <35> root");    delete_BST(35);
    printf("   LevelOrder : ");        levelorder(root);
    printf("\n");
    printf(" 노드의 개수 = %d\n", count_node(root));
    printf(" 단말의 개수 = %d\n", count_leaf(root));
    printf(" 트리의 높이 = %d\n", calc_height(root));
    printf("\n");
    return 0;
}

