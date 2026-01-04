#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of TreeNode is already provided by LeetCode

// Helper function: append string with realloc
void append(char **str, int *len, const char *s) {
    int n = strlen(s);
    *str = (char*)realloc(*str, (*len + n + 1) * sizeof(char));
    strcpy(*str + *len, s);
    *len += n;
}

// Serialize helper (preorder)
void serializeHelper(struct TreeNode* root, char **str, int *len) {
    if (!root) {
        append(str, len, "#,");
        return;
    }
    char buf[12];
    sprintf(buf, "%d,", root->val);
    append(str, len, buf);
    serializeHelper(root->left, str, len);
    serializeHelper(root->right, str, len);
}

// Serialize function
char* serialize(struct TreeNode* root) {
    char *res = (char*)malloc(1);
    res[0] = '\0';
    int len = 0;
    serializeHelper(root, &res, &len);
    return res;
}

// Deserialize helper
struct TreeNode* deserializeHelper(char **data) {
    if (**data == '\0') return NULL;

    if (**data == '#') {
        *data += 2; // skip "#,"
        return NULL;
    }

    int val = atoi(*data);
    while (**data != ',') (*data)++;
    (*data)++; // skip ','

    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = deserializeHelper(data);
    node->right = deserializeHelper(data);
    return node;
}

// Deserialize function
struct TreeNode* deserialize(char* data) {
    return deserializeHelper(&data);
}
