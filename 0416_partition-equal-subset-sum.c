#include <stdbool.h>

// Solution- Brute Force (Wrong Understanding...) - O(n^2)
bool canPartition_wrong(int* nums, int numsSize) {
    for (int cursor = 1; cursor < numsSize; cursor++) {
        int left  = 0;
        int right = 0;
        
        for (int i = 0; i < cursor; i++) {
            left += nums[i];
        }
        
        for (int j = cursor; j < numsSize; j++) {
            right += nums[j];
        }
        
        if (left == right) return true;
    }
    
    return false;
}

// Solution - Brute Force - O(n^2)
bool canPartition_bf(int* nums, int numsSize) {
    // Init.
    int value = 0;
    for (int i = 0; i < numsSize; i++) value += nums[i];
    // Bdry.
    if (value % 2 != 0) return false;
    
    int target = value / 2;
    
    bool dp[target + 1];
    dp[0] = true;
    for (int i = 1; i < target + 1; i++) {
        dp[i] = false;
    }
    

    // Prog.
    for(int i = 0; i < numsSize; i++) {
        for (int j = target; j >= nums[i]; j--) {
            if (dp[j] == true || dp[j - nums[i]] == true) {
                dp[j] = true;
            } else {
                dp[j] = false;
            }
        }
    }
    
    return dp[target];
}