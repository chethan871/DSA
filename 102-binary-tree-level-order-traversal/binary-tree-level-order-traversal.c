// Definition for a binary tree node is already provided by the platform.

typedef struct {
    struct TreeNode **data;
    int front, rear, size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * capacity);
    q->front = q->rear = 0;
    q->size = capacity;
    return q;
}

void enqueue(Queue* q, struct TreeNode* node) { q->data[q->rear++] = node; }
struct TreeNode* dequeue(Queue* q) { return q->data[q->front++]; }
int isEmpty(Queue* q) { return q->front == q->rear; }

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) { *returnSize = 0; *returnColumnSizes = NULL; return NULL; }

    int** res = (int**)malloc(sizeof(int*) * 2000);
    *returnColumnSizes = (int*)malloc(sizeof(int) * 2000);
    *returnSize = 0;

    Queue* q = createQueue(2000);
    enqueue(q, root);

    while (!isEmpty(q)) {
        int levelSize = q->rear - q->front;
        int* level = (int*)malloc(sizeof(int) * levelSize);

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = dequeue(q);
            level[i] = node->val;
            if (node->left) enqueue(q, node->left);
            if (node->right) enqueue(q, node->right);
        }

        res[*returnSize] = level;
        (*returnColumnSizes)[*returnSize] = levelSize;
        (*returnSize)++;
    }

    free(q->data);
    free(q);
    return res;
}
