#include <stdbool.h>
#include <string.h>

bool isIsomorphic(char * s, char * t){
    int map_s[256] = {0};  // mapping from s -> t
    int map_t[256] = {0};  // mapping from t -> s

    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        char c1 = s[i];
        char c2 = t[i];

        if (map_s[(unsigned char)c1] == 0 && map_t[(unsigned char)c2] == 0) {
            map_s[(unsigned char)c1] = c2;
            map_t[(unsigned char)c2] = c1;
        } 
        else {
            if (map_s[(unsigned char)c1] != c2 || map_t[(unsigned char)c2] != c1)
                return false;
        }
    }
    return true;
}
