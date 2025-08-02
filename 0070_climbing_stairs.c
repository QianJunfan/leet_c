#include <stdio.h>

// Solution 1 - Iteration Approach - O(n)
int climbStairs_iter(int n) {
    // Bdry.
    if (n == 1) return 1;
    
    // Init.
    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 1;
    
    // Prog.
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp [i - 2];
    }
    
    return dp[n];
}

// Solution 2 - Recursion Approach - O(2^N) ~ Out of time
int climbStairs_Recursion(int n) {
    // Bdry.
    if (n == 1) return 1;
    if (n == 2) return 2;
    
    // Prog.
    return climbStairs_Recursion(n-1) + climbStairs_Recursion(n-2);
}

// Solution 3 - Space Saving Approach - O(n)
int climbStairs_spc_sav(int n) {
    // Bdry.
    if (n == 1) return 1;
    
    // Init.
    int sta_0 = 1;
    int sta_1 = 1;
    int sta_2;
    
    // Prog.
    for (int i = 2; i <= n; i++) {
        sta_2 = sta_0 + sta_1;
        sta_0 = sta_1;
        sta_1 = sta_2;
    }
    
    return sta_1;
}



