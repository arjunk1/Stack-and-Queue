#include <stdio.h>
#include<limits.h>
#include<stdlib.h>
#include <string.h>
  
int subRecursivePermuteIntoStack(int *ip, int *op, int n);
struct Stack
{
int maximumsz; 
int top;
int *items;
};

struct Stack* createStack(int maxcap)
{
struct Stack *it = (struct Stack*)malloc(sizeof(struct Stack));

it->maximumsz = maxcap;
it->top = -1;
it->items = (int*)malloc(sizeof(int) * maxcap);

return it;
}

int isStackEmpty(struct Stack *it)
{
return it->top == -1; 
}

int stackPop(struct Stack *it)
{

if (isStackEmpty(it))
{
printf("Stack Empty. Program will end\n\n");
exit(EXIT_FAILURE);
}


return it->items[it->top--];
}


int stackSize(struct Stack *it)
{
return it->top + 1;
}

int isStackFull(struct Stack *it)
{
return it->top == it->maximumsz - 1; 
}

int stackTop(struct Stack* it)
{
    if (isStackEmpty(it))
        return INT_MIN;
   return it->items[it->top];
}

void stackPush(struct Stack *it, int x)
{
    if (isStackFull(it))
    {
        printf("Stack Full. Program will end\n\n");
        exit(EXIT_FAILURE);
    }

    it->items[++it->top] = x;
}

struct Queue
{
    int front, rear, size;
    unsigned maxcap;
    int* array;
};
 

struct Queue* createQueue(unsigned maxcap)
{
    struct Queue* tempQueue = (struct Queue*) malloc(sizeof(struct Queue));
    
    tempQueue->rear = maxcap - 1; 
    tempQueue->front = tempQueue->size = 0;  
    tempQueue->maxcap = maxcap;
    tempQueue->array = (int*) malloc(tempQueue->maxcap * sizeof(int));
    
    return tempQueue;
}

int isQueueEmpty(struct Queue* tempQueue)
{  return (tempQueue->size == 0); }
 
int front(struct Queue* tempQueue)
{
    if (isQueueEmpty(tempQueue))
        return INT_MIN;
    return tempQueue->array[tempQueue->front];
}
 

int isQueueFull(struct Queue* tempQueue)
{  return ( tempQueue->maxcap==tempQueue->size);  }

void putIntoQueue(struct Queue* tempQueue, int item)
{
    if (isQueueFull(tempQueue))
        return;
    tempQueue->rear = (tempQueue->rear + 1)%tempQueue->maxcap;
    tempQueue->array[tempQueue->rear] = item;
    tempQueue->size = tempQueue->size + 1;
}


int rear(struct Queue* tempQueue)
{
    if (isQueueEmpty(tempQueue))
        return INT_MIN;
    return tempQueue->array[tempQueue->rear];
}

int removeFromQueue(struct Queue* tempQueue)
{
    if (isQueueEmpty(tempQueue))
        return INT_MIN;
    int item = tempQueue->array[tempQueue->front];
    tempQueue->size = tempQueue->size - 1;
    tempQueue->front = (tempQueue->front + 1)%tempQueue->maxcap;
    return item;
}


void swap(int *a, int *b)
{
    int foo;  
    foo = *a;
    *a = *b;
    *b = foo;
}
 

void recursivePermuteIntoStack(int left, int right,int *inp,int *c)
{
   int i;
   for (i = left; i <= right; i++)
   {
      swap((c+left), (c+i));
      recursivePermuteIntoStack(left+1, right,inp,c);
      swap((c+left), (c+i)); //backtrack
   }
   
   if (left == right) {
       int o=subRecursivePermuteIntoStack(inp,c,right+1);
        if(o==1)
        {
        for(i=0;i<=right;i++)
        printf("%d",c[i]);
        printf("\n");
    }
   }
   
}
 

int subRecursivePermuteIntoStack(int *ip, int *op, int n)
{

    struct Queue* secondQueue = createQueue(1000);
    for (int i=0;i<n;i++)
        putIntoQueue(secondQueue,op[i]);  
 
     struct Queue* firstQueue = createQueue(1000);
    for (int i=0;i<n;i++)
        putIntoQueue(firstQueue,ip[i]);

    struct Stack* stack= createStack(1000);
    while (!isQueueEmpty(firstQueue))
    {
        int foo = front(firstQueue);
        removeFromQueue(firstQueue);
        if (foo == front(secondQueue))
        {
            removeFromQueue(secondQueue);
            while (!isStackEmpty(stack))
            {   
                if(front(secondQueue) != stackTop(stack))
                    break;
                else
                {
                    removeFromQueue(secondQueue);
                    stackPop(stack);
                }
            }
        }
        else
            stackPush(stack,foo);
    }
    return (isQueueEmpty(firstQueue)&&isStackEmpty(stack));
}

int main()
{
    int firstQueue[1000];
    int secondQueue[1000];
    int size;
    scanf("%d" , &size);
     for (int i =0;i<size;i++){
        scanf("%d", &firstQueue[i]);
     }
    int i;
    for(i=0;i<size;i++)
        secondQueue[i]=firstQueue[i];
    recursivePermuteIntoStack(0,size-1,firstQueue,secondQueue);
    return 0;
}