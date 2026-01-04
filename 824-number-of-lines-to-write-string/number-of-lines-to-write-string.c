#include <stdio.h>

int* numberOfLines(int* widths, int widthsSize, char* s, int* returnSize) {
    static int result[2];
    int lines = 1;
    int currWidth = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int w = widths[s[i] - 'a'];

        if (currWidth + w > 100) {
            lines++;
            currWidth = w;
        } else {
            currWidth += w;
        }
    }

    result[0] = lines;
    result[1] = currWidth;
    *returnSize = 2;
    return result;
}
