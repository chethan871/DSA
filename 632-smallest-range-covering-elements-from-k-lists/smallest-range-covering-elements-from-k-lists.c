#include <stdlib.h>
#include <limits.h>

/* Node for heap */
typedef struct {
    int val;
    int row;
    int idx;
} Node;

/* Swap helper */
void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify down */
void heapify(Node heap[], int size, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && heap[left].val < heap[smallest].val)
        smallest = left;
    if (right < size && heap[right].val < heap[smallest].val)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

/* Extract minimum element */
Node extractMin(Node heap[], int *size) {
    Node root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return root;
}

/* Insert element into heap */
void insertHeap(Node heap[], int *size, Node val) {
    int i = (*size)++;
    heap[i] = val;

    while (i > 0 && heap[(i - 1) / 2].val > heap[i].val) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* MAIN FUNCTION */
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    Node heap[3500];
    int heapSize = 0;
    int maxVal = INT_MIN;

    for (int i = 0; i < numsSize; i++) {
        Node node = {nums[i][0], i, 0};
        insertHeap(heap, &heapSize, node);
        if (nums[i][0] > maxVal)
            maxVal = nums[i][0];
    }

    int rangeStart = 0, rangeEnd = INT_MAX;

    while (heapSize == numsSize) {
        Node minNode = extractMin(heap, &heapSize);

        if (maxVal - minNode.val < rangeEnd - rangeStart) {
            rangeStart = minNode.val;
            rangeEnd = maxVal;
        }

        int nextIdx = minNode.idx + 1;
        if (nextIdx < numsColSize[minNode.row]) {
            int nextVal = nums[minNode.row][nextIdx];
            insertHeap(heap, &heapSize, (Node){nextVal, minNode.row, nextIdx});
            if (nextVal > maxVal)
                maxVal = nextVal;
        } else {
            break;
        }
    }

    int *result = (int*)malloc(2 * sizeof(int));
    result[0] = rangeStart;
    result[1] = rangeEnd;
    *returnSize = 2;
    return result;
}
