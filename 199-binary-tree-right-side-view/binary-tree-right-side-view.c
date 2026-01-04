#include <stdio.h>
#include <stdlib.h>

// Queue for BFS
typedef struct {
    struct TreeNode **data;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * capacity);
    q->front = 0;
    q->rear = 0;
    q->size = capacity;
    return q;
}

void enqueue(Queue* q, struct TreeNode* node) {
    q->data[q->rear++] = node;
}

struct TreeNode* dequeue(Queue* q) {
    return q->data[q->front++];
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// Right side view function
int* rightSideView(struct TreeNode* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    int* res = (int*)malloc(sizeof(int) * 1000); // max 1000 nodes
    *returnSize = 0;

    Queue* q = createQueue(1000);
    enqueue(q, root);

    while (!isEmpty(q)) {
        int levelSize = q->rear - q->front;
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = dequeue(q);
            if (node->left) enqueue(q, node->left);
            if (node->right) enqueue(q, node->right);
            // Rightmost node at this level
            if (i == levelSize - 1) res[(*returnSize)++] = node->val;
        }
    }

    free(q->data);
    free(q);
    return res;
}
