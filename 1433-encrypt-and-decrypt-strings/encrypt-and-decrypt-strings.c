#include <stdlib.h>
#include <string.h>

#define HASH 100003
#define MAXLEN 205

typedef struct Node {
    char key[MAXLEN];
    int count;
    struct Node* next;
} Node;

typedef struct {
    char enc[26][3];      // char -> 2 letters
    int valid[26];        // char exists in keys
    Node* table[HASH];
} Encrypter;

/* ---------- Hash ---------- */
unsigned int hashStr(const char* s) {
    unsigned int h = 0;
    while (*s)
        h = h * 131 + (*s++);
    return h % HASH;
}

/* ---------- Insert ---------- */
void insert(Node** table, const char* key) {
    unsigned int h = hashStr(key);
    Node* cur = table[h];

    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            cur->count++;
            return;
        }
        cur = cur->next;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->key, key);
    node->count = 1;
    node->next = table[h];
    table[h] = node;
}

/* ---------- Get Count ---------- */
int getCount(Node** table, const char* key) {
    unsigned int h = hashStr(key);
    Node* cur = table[h];

    while (cur) {
        if (strcmp(cur->key, key) == 0)
            return cur->count;
        cur = cur->next;
    }
    return 0;
}

/* ---------- Encrypt Word (returns 0 if invalid) ---------- */
int encryptWord(Encrypter* obj, const char* word, char* out) {
    int idx = 0;
    for (int i = 0; word[i]; i++) {
        int c = word[i] - 'a';
        if (!obj->valid[c])
            return 0;   // invalid character
        out[idx++] = obj->enc[c][0];
        out[idx++] = obj->enc[c][1];
    }
    out[idx] = '\0';
    return 1;
}

/* ---------- Constructor ---------- */
Encrypter* encrypterCreate(char* keys, int keysSize,
                           char** values, int valuesSize,
                           char** dictionary, int dictionarySize) {
    Encrypter* obj = (Encrypter*)malloc(sizeof(Encrypter));
    memset(obj, 0, sizeof(Encrypter));

    for (int i = 0; i < keysSize; i++) {
        int c = keys[i] - 'a';
        obj->valid[c] = 1;
        obj->enc[c][0] = values[i][0];
        obj->enc[c][1] = values[i][1];
        obj->enc[c][2] = '\0';
    }

    char buffer[MAXLEN];

    for (int i = 0; i < dictionarySize; i++) {
        if (encryptWord(obj, dictionary[i], buffer))
            insert(obj->table, buffer);
    }

    return obj;
}

/* ---------- Encrypt ---------- */
char* encrypterEncrypt(Encrypter* obj, char* word1) {
    char* res = (char*)malloc(2 * strlen(word1) + 1);
    encryptWord(obj, word1, res);
    return res;
}

/* ---------- Decrypt ---------- */
int encrypterDecrypt(Encrypter* obj, char* word2) {
    return getCount(obj->table, word2);
}

/* ---------- Free ---------- */
void encrypterFree(Encrypter* obj) {
    for (int i = 0; i < HASH; i++) {
        Node* cur = obj->table[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(obj);
}
