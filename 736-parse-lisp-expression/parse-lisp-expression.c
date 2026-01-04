#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Scope {
    char var[32];
    int val;
    struct Scope* next;
} Scope;

int eval(char** s, Scope* scope);

int getValue(char* var, Scope* scope) {
    while (scope) {
        if (strcmp(scope->var, var) == 0)
            return scope->val;
        scope = scope->next;
    }
    return 0;
}

void skipSpace(char** s) {
    while (**s == ' ') (*s)++;
}

char* parseToken(char** s) {
    skipSpace(s);
    char* start = *s;
    while (**s && **s != ' ' && **s != ')') (*s)++;
    int len = *s - start;
    char* token = (char*)malloc(len + 1);
    strncpy(token, start, len);
    token[len] = '\0';
    return token;
}

int eval(char** s, Scope* scope) {
    skipSpace(s);

    if (**s == '(') {
        (*s)++; // skip '('
        skipSpace(s);

        char* op = parseToken(s);

        if (strcmp(op, "add") == 0) {
            int a = eval(s, scope);
            int b = eval(s, scope);
            (*s)++; // skip ')'
            free(op);
            return a + b;
        }

        if (strcmp(op, "mult") == 0) {
            int a = eval(s, scope);
            int b = eval(s, scope);
            (*s)++; // skip ')'
            free(op);
            return a * b;
        }

        // let expression
        Scope* local = scope;
        while (1) {
            skipSpace(s);
            if (**s == '(' || isdigit(**s) || **s == '-') {
                int result = eval(s, local);
                (*s)++;  // skip ')'
                free(op);
                return result;
            }

            char* var = parseToken(s);
            skipSpace(s);

            if (**s == ')') {
                int val = getValue(var, local);
                (*s)++;
                free(var);
                free(op);
                return val;
            }

            int val = eval(s, local);
            Scope* node = malloc(sizeof(Scope));
            strcpy(node->var, var);
            node->val = val;
            node->next = local;
            local = node;
            free(var);
        }
    }

    // number or variable
    if (isalpha(**s)) {
        char* var = parseToken(s);
        int val = getValue(var, scope);
        free(var);
        return val;
    }

    int sign = 1;
    if (**s == '-') {
        sign = -1;
        (*s)++;
    }
    int num = 0;
    while (isdigit(**s)) {
        num = num * 10 + (**s - '0');
        (*s)++;
    }
    return sign * num;
}

int evaluate(char* expression) {
    return eval(&expression, NULL);
}
