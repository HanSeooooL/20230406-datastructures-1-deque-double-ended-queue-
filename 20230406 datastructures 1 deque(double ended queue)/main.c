//
//  main.c
//  20230406 datastructures 1 deque(double ended queue)
//
//  Created by 한설 on 2023/04/06.
//  원형 덱 구현

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int Element;

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error( char str[]) //에러메세지 출력(스택에서의 error와 같음)
{
    printf("%s\n", str);
    exit(1);
}


Element peek(void);
void enqueue(Element val);
Element dequeue(void);
void print_queue(char msg[]);
void print_deque(char msg[]) {print_queue(msg);};
void init_deque(void) {front = rear = 0;}   //큐 초기화
void add_rear(Element val) { enqueue(val);}
int is_empty(void) {return front == rear;}  //큐 공백 확인
int is_full(void) {return front == (rear + 1) % MAX_QUEUE_SIZE;}    //큐 포화 확인
int size(void) {return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;}   //큐 크기 확인
Element delete_rear(void);
Element get_rear(void);
Element delete_front() {return dequeue();}

void add_front( Element val) {
    if(is_full())
        error("덱 포화 에러");
    data[front] = val;
    front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

Element delete_rear(void)
{
    Element ret;
    if(is_empty())
        error("덱 공백 에러");
    ret = data[rear];
    rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return ret;
}

Element get_rear(void)
{
    if(is_empty())
        error("덱 공백 에러");
    return data[rear];
}

void enqueue(Element val)   //큐에 원소 삽입 (스택에서의 push와 비슷)
{
    if(is_full())
        error("큐 포화 에러");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element dequeue(void)   //큐 선입 원소 출력 및 제거 (스택에서의 pop과 비슷하지만 큐는 먼저 들어온 원소가 먼저 출력됨.)
{
    if(is_empty())
        error("큐 공백 에러");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

Element peek(void)  //큐 가장 앞에 있는 원소 출력 (스택에서의 peek과 비슷)
{
    if(is_empty())
        error("큐 공백 에러");
    return data[(front+1) % MAX_QUEUE_SIZE];
}

void print_queue(char msg[])
{
    int i, maxi = rear;
    if (front >= rear)
        maxi += MAX_QUEUE_SIZE;
    printf("%s[%2d]= ",msg, size());
    for(i = front + 1; i <= maxi; i++)
        printf("%2d ", data[i % MAX_QUEUE_SIZE]);
    printf("\n");
}

int main(int argc, const char * argv[]) {
    int i;
    init_deque();
    for(i = 1; i < 10; i++)
    {
        if(i % 2) add_front(i);
        else add_rear(i);
    }
    print_deque("원형 덱 홀수-짝수");
    printf("\tdelete_front() --> %d\n", delete_front());
    printf("\tdelete_rear() --> %d\n", delete_rear());
    printf("\tdelete_front() --> %d\n", delete_front());
    print_queue("원형 덱 삭제-홀짝홀");
    return 0;
}
