#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// I reinvented the wheel to get the length of a string :)
int _strlen(const char *str) {
    const char *ptr = str;
    while (*ptr != '\0') {
        ptr ++;
    }
    // Implicit conversion loses integer precision, but the problem states that the string's range is 0 to 5×10⁴, so it's not an issue.
    return (int)(ptr - str);
}



// Solution 1 - Brute Force Approach - O(n^3) ~ extremely slow :...
int lengthOflongestSubstring_brute_force(char* string) {
    // Init.
    int length = _strlen(string);
    if (length == 0) return 0;

    int current_len = 0;
    int max_len     = 1;
    int is_repeated;

    // Prog.
    for (int i = 0; i < length; i++) {
        current_len = 1;

        for(int j = i + 1; j < length; j++) {
            is_repeated = 0;
            for (int k = i; k < j; k++) {
                if (string[k] == string[j]) {
                    is_repeated = 1;
                    break;
                }
            }

            if (is_repeated) {
                break;
            }
        
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        }
    }
    
    return max_len;
}

// Solution 2 - Sliding Window with Hash Table － O(n)
int lengthOflongestSubstring_sliding_window_hash_table(char* string) {
    // Init.
    int length = _strlen(string);
    if (length == 0) return 0;

    int index[128];                     // Use an array to simulate a hash table, recording the last occurrence position of characters.
    memset(index, -1, sizeof(index));   // There are 128 ASCII characters in total, initialized to -1 to indicate they have not appeared yet.

    int current_len = 0;
    int     max_len = 1;
    int       start = 0;
    
    char current;
    
    // Prog.
    for (int end = 0; end < length; end++) {
        current = string[end];
        
        if (index[current] >= start) {
            start = index[current] + 1;
        }
        
        index[current] = end;
        
        current_len = end - start + 1;
        if (current_len > max_len) {
            max_len = current_len;
        }
    }
    
    return max_len;
}



int main() {
    char sample_1[] = "absbdkjpajnbcbbbcabcdefghh";
    char sample_2[] = "11111111112";
    char sample_3[] = "abcdefghij";
    
    printf("%d\n",lengthOflongestSubstring_brute_force(sample_1));
    printf("%d\n",lengthOflongestSubstring_brute_force(sample_2));
    printf("%d\n",lengthOflongestSubstring_brute_force(sample_3));
    return 0;
}
