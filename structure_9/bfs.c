#include<stdio.h>
#define MAZE_SIZE 6

typedef struct {
    short r;
    short c;
}element;

struct note {
    int x;
    int y;
    int f;
    int s;
};
int maze[MAZE_SIZE][MAZE_SIZE] = {
    { 1, 1, 1, 1, 1, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 1 },
    { 1, 0, 1, 0, 1, 1 },
    { 1, 0, 1, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1 },
};
element entry = { 1, 0 };
element end = { 4, 5 };

int main()
{
    printf("BFS: (%d, %d)", entry.r, entry.c);
    struct note que[37];
    int book[51][510] = { 0 };
    int a[51][51] = { 0 };
    
    
    int next[4][2] = {
        { 0,1 },
        { 1,0 },
        { 0,-1 },
        { -1,0 },
    };
    
    int i, j, k, head, tail, tx, ty;
    int flag;
    for (i = 0; i <MAZE_SIZE; i++)
    {
        for (j = 0; j <MAZE_SIZE; j++)
        {
            a[i][j] = maze[i][j];
        }
        
    }
    
    
    head = 1;
    tail = 1;
    
    que[tail].x = entry.r;
    que[tail].y = entry.c;
    que[tail].s = 0;
    que[tail].f = 0;
    tail++;
    book[entry.r][entry.c] = 1;
    
    flag = 0;
    while (head<tail) {
        
        for (k = 0; k <= 3; k++)
        {
            
            tx = que[head].x + next[k][0];
            ty = que[head].y + next[k][1];
            
            if (tx<1 || ty<1 || tx>MAZE_SIZE || ty>MAZE_SIZE)
                continue;
            
            if (a[tx][ty] == 0 && book[tx][ty] == 0)
            {
                printf("(%d, %d)", tx, ty);
                book[tx][ty] = 1;
                que[tail].x = tx;
                que[tail].y = ty;
                que[tail].s = que[head].s + 1;
                tail++;
            }
            
            if (tx == end.r && ty == end.c)
            {
                printf("success");
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
        head++;
    }
    
    
    getchar();
    return 0;
}

