#include <stdio.h>
#include <stdlib.h>
#include "robot_moving_event.h"

// 큐 초기화
void initQueue(TaskQueue* q) {
    q->front = -1;
    q->rear = -1;
    pthread_mutex_init(&q->mutex, NULL); // mutex 초기화
}

// 큐가 비어있는지 확인
int isEmpty(TaskQueue* q) {
    return q->front == -1;
}

// 큐가 가득 찼는지 확인
int isFull(TaskQueue* q) {
    return q->rear == MAX_SIZE - 1;
}

// 큐에 요소 추가
void enqueue(TaskQueue* q, void* value) {
    pthread_mutex_lock(&q->mutex);

    if (isFull(q)) {
        printf("큐가 가득 찼습니다!\n");
        pthread_mutex_unlock(&q->mutex); 
        return;
    }
    if (isEmpty(q)) {
        q->front = 0; // 첫 번째 요소 추가 시 front 초기화
    }
    q->rear++;
    q->task[q->rear] = value;

    pthread_mutex_unlock(&q->mutex); 
}

// 큐에서 요소 제거
void* dequeue(TaskQueue* q) {
    pthread_mutex_lock(&q->mutex); // mutex lock

    if (isEmpty(q)) {
        printf("큐가 비어있습니다!\n");
        pthread_mutex_unlock(&q->mutex); // mutex lock 
        return NULL; // 오류 코드
    }
    void* item = q->task[q->front];
    q->front++;
    if (q->front > q->rear) { // 큐가 비어있게 되면 초기화
        q->front = q->rear = -1;
    }

    pthread_mutex_unlock(&q->mutex); // mutex lock
    return item;

}

// 큐의 첫 번째 요소 확인
void* peek(TaskQueue* q) {
    if (isEmpty(q)) {
        printf("큐가 비어있습니다!\n");
        return NULL; // 오류 코드
    }
    return q->task[q->front];
}
