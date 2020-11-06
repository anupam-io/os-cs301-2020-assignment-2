// Note: This file contains all the functions realted to queue


#include "definitions.h"

qnode* new_node(int val){
	qnode* t = (qnode*)malloc(sizeof(qnode));
	t->data = val;
	t->next = t->prev = NULL;
	return t;
}

queue* new_queue(){
    queue* q = (queue*)malloc(sizeof(queue));
    q->curr_size = 0;
    q->front = q->back = NULL;
    return q;
}

void push(queue* q, int data){    
    if(q->front == NULL){
        q->back = new_node(data);
        q->front = q->back;
    } else {
        qnode* l = new_node(data);
        q->back->next = l;
        l->prev = q->back;
        q->back = l;
    }

    q->curr_size++;
}


int find(queue* q, int val){
    qnode* t = q->front;
    while(t!=NULL){
        if(t->data == val){
            return 1;
        }

        t = t->next;
    }

    return 0;
}


int find_and_remove(queue* q, int val){
    qnode* t = q->front;
    while(t!=NULL){
        if(t->data == val){
            if(t->next == NULL && t->prev == NULL){
                free(t);
                q->front = q->back = NULL;
            } else if(t->prev == NULL){
                qnode* new_front = t->next;
                new_front->prev = NULL;
                q->front = new_front;
                free(t);
            } else if(t->next == NULL){
                qnode* new_back = t->prev;
                new_back->next = NULL;
                q->back = new_back;
                free(t);
            } else {
                qnode* left = t->prev;
                qnode* right = t->next;
                left->next = right;
                right->prev = left;
                free(t);
            }

            q->curr_size--;
            return 1;
        }

        t = t->next;
    }

    return 0;
}


void pop(queue* q){
    if(q->curr_size == 0){
        printf("pop() called on empty queue.\n");
    }

    qnode* t = q->front;
    if(t){
        qnode* new_front = t->next;
        free(t);
        if(new_front){
            new_front->prev = NULL;
        }
        q->front = new_front;
        q->curr_size--;
    }
}

void remove_random(queue* q){
    int r = rand()%q->curr_size;
    qnode* a = q->front;
    for(int i = 0; i<r; i++){
        a = a->next;
    }
    find_and_remove(q, a->data);
}

queue* copy_queue(queue* source){
    queue* target = new_queue();
    qnode* t = source->front;

    while(t){
        push(target, t->data);
        t = t->next;
    }
    return target;
}