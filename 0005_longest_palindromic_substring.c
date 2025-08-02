#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Solution 1 - Brute Force Approach - O(n^3) - out of time
// Oh, how stupid i am... you do not want to see this...
int checkPalindrome_stupid(const char* string) {
    int  length = (int)strlen(string);
    int     mid;
    int     max = 0;
    
    if (length == 1) return 1;
    if (length == 0) return 0;
    
    if (strlen(string) % 2 == 0) {
        mid = length / 2 - 1;
        for (int i = 0; i <= mid; i++ ) {
            if (string[mid -i] != string[mid + i]) return 0;
            if (string[mid - i] ==  string[mid + i + 1]) {
                max += 2;
            }
        }
    } else {
        mid = (length + 1) / 2 - 1;
        for (int i = 0; i <= mid - 1; i++ ) {
            if (string[mid -i] != string[mid + i]) return 0;
            if (string[mid - i] == string[mid + i]) {
                max += 2;
            }
        }
        return max + 1;
    }
    return max;
}

int checkPalindrome(const char* s) {
    int len = (int)strlen(s);
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len-1-i]) {
            return 0;
        }
    }
    return len;
}

char* longestPalindrome_brute_force(char* string) {
    // Bdry.
    if (!string || *string == '\0') return strdup("");
    if ((int)strlen(string) == 1) {
        char* single = malloc(2);
        if (single) {
            single[0] = string[0];
            single[1] = '\0';
        }
        return single;
    }
    
    // Init.
    int length = (int)strlen(string);
    int     max_len = 1;
    int current_len = 1;
    int       start = 0;
    
    char  current[length + 1];
    char* result = malloc(length + 1);
    if (!result) return NULL;
    
    // Prog.
    for (int i = 0; i < length; i++) {
        current[0] = '\0';
        for (int j = i; j < length; j++) {
            char temp[2] = {string[j], '\0'};
            strcat(current, temp);
            
            current_len = checkPalindrome(current);
            if (current_len) {
                if (current_len > max_len) {
                    max_len = current_len;
                    start = i;
                }
            }
        }
    }
    
    strncpy(result, string + start, max_len);
    result[max_len] = '\0';
    
    return result;
}

// Solution 2 - Manacher Approach- O(n) - Genius!!!
char* pre(const char* string) {
    size_t length = strlen(string);
    if (length == 0) {
        return strdup("^$");
    }
    
    char* newStr = (char*)malloc(3 * length + 3);
    if (!newStr) {
        return NULL;
    }
    
    newStr[0] = '^';
    size_t j = 1;
    for (size_t i = 0; i < length; i++) {
        newStr[j++] = '#';
        newStr[j++] = string[i];
    }
    newStr[j++] = '#';
    newStr[j++] = '$';
    newStr[j] = '\0';
    
    return newStr;
}

char* longestPalindrome_manacher(char* s) {
    if (!s || *s == '\0') return strdup("");
    
    char* T = pre(s);
    int   n =  (int)strlen(T);
    int*  P = (int*)calloc(n, sizeof(int));
    int C = 0, R = 0;
    
    for (int i = 1; i < n-1; i++) {
        int i_mirror = 2 * C - i;
        
        if (R > i) {
            P[i] = (R - i) < P[i_mirror] ? (R - i) : P[i_mirror];
        } else {
            P[i] = 0;
        }
        

        while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
            P[i]++;
        }
        
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
    
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n-1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    
    free(T);
    
    int start = (centerIndex - maxLen) / 2;
    char* result = (char*)malloc(maxLen + 1);
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0';
    
    free(P);
    
    return result;
}








