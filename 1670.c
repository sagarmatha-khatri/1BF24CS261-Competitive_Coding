#include <stdio.h>
#include <stdlib.h>

// Doubly Linked List Node
typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

// Linked List Structure with Sentinel Head/Tail nodes
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Main Queue Structure
typedef struct {
    LinkedList* left;
    LinkedList* right;
} FrontMiddleBackQueue;

// Helper: Create a double-linked list with dummy head and tail
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = (Node*)malloc(sizeof(Node));
    list->tail = (Node*)malloc(sizeof(Node));
    list->head->prev = NULL;
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->tail->next = NULL;
    list->size = 0;
    return list;
}

// Helper: Insert a node right before 'target'
void insertBefore(Node* target, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->prev = target->prev;
    newNode->next = target;
    target->prev->next = newNode;
    target->prev = newNode;
}

// Helper: Remove and free 'target' node, returns its value
int removeNode(Node* target) {
    int val = target->val;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    free(target);
    return val;
}

// Helper: Balance both halves so size(right) is size(left) or size(left) + 1
void balance(FrontMiddleBackQueue* obj) {
    if (obj->left->size > obj->right->size) {
        // Move tail of left to head of right
        Node* nodeToMove = obj->left->tail->prev;
        insertBefore(obj->right->head->next, nodeToMove->val);
        removeNode(nodeToMove);
        obj->left->size--;
        obj->right->size++;
    } else if (obj->right->size > obj->left->size + 1) {
        // Move head of right to tail of left
        Node* nodeToMove = obj->right->head->next;
        insertBefore(obj->left->tail, nodeToMove->val);
        removeNode(nodeToMove);
        obj->right->size--;
        obj->left->size++;
    }
}

FrontMiddleBackQueue* frontMiddleBackQueueCreate() {
    FrontMiddleBackQueue* obj = (FrontMiddleBackQueue*)malloc(sizeof(FrontMiddleBackQueue));
    obj->left = createLinkedList();
    obj->right = createLinkedList();
    return obj;
}

void frontMiddleBackQueuePushFront(FrontMiddleBackQueue* obj, int val) {
    insertBefore(obj->left->head->next, val);
    obj->left->size++;
    balance(obj);
}

void frontMiddleBackQueuePushMiddle(FrontMiddleBackQueue* obj, int val) {
    if (obj->left->size < obj->right->size) {
        insertBefore(obj->left->tail, val);
        obj->left->size++;
    } else {
        insertBefore(obj->right->head->next, val);
        obj->right->size++;
    }
    balance(obj);
}

void frontMiddleBackQueuePushBack(FrontMiddleBackQueue* obj, int val) {
    insertBefore(obj->right->tail, val);
    obj->right->size++;
    balance(obj);
}

int frontMiddleBackQueuePopFront(FrontMiddleBackQueue* obj) {
    if (obj->left->size == 0 && obj->right->size == 0) return -1;
    
    int val;
    if (obj->left->size > 0) {
        val = removeNode(obj->left->head->next);
        obj->left->size--;
    } else {
        val = removeNode(obj->right->head->next);
        obj->right->size--;
    }
    balance(obj);
    return val;
}

int frontMiddleBackQueuePopMiddle(FrontMiddleBackQueue* obj) {
    if (obj->left->size == 0 && obj->right->size == 0) return -1;

    int val;
    if (obj->left->size == obj->right->size) {
        val = removeNode(obj->left->tail->prev);
        obj->left->size--;
    } else {
        val = removeNode(obj->right->head->next);
        obj->right->size--;
    }
    balance(obj);
    return val;
}

int frontMiddleBackQueuePopBack(FrontMiddleBackQueue* obj) {
    if (obj->left->size == 0 && obj->right->size == 0) return -1;

    int val = removeNode(obj->right->tail->prev);
    obj->right->size--;
    balance(obj);
    return val;
}

void freeLinkedList(LinkedList* list) {
    Node* curr = list->head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(list);
}

void frontMiddleBackQueueFree(FrontMiddleBackQueue* obj) {
    freeLinkedList(obj->left);
    freeLinkedList(obj->right);
    free(obj);
}
