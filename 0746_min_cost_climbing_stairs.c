#include <stdio.h>

// Solution - Memory Saving Approach - O(n)
int minCostClimbingStairs(int* cost, int costSize) {
    // Bdry.
    if (costSize == 0) return 0;
    if (costSize == 1) return cost[0];
    
    // Init.
    int prev1 = 0;
    int prev2 = 0;
    int current = 0;
    
    // Prog.
    for (int i = 2; i <= costSize; i++) {
        current = (prev1 + cost[i-1]) < (prev2 + cost[i-2]) ?
                  (prev1 + cost[i-1]) : (prev2 + cost[i-2]);
        
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}