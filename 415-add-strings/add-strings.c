#include <stdlib.h>
#include <string.h>

char* addStrings(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int i = len1 - 1;
    int j = len2 - 1;
    int carry = 0;

    // 🔧 FIX: correct allocation size
    int maxLen = (len1 > len2 ? len1 : len2) + 2;
    char* result = (char*)malloc(maxLen);

    int k = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;

        if (i >= 0)
            sum += num1[i--] - '0';
        if (j >= 0)
            sum += num2[j--] - '0';

        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    result[k] = '\0';

    // Reverse the result string
    for (int l = 0, r = k - 1; l < r; l++, r--) {
        char temp = result[l];
        result[l] = result[r];
        result[r] = temp;
    }

    return result;
}
