// Solution 1 - Merge Approach - O(n)
double findMedianSortedArrays_merge(int* nums1, int size1, int* nums2, int size2) {
    // init.
    int total = size1 + size2;
    int merged[total];
    
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (nums1[i] < nums2[j]) {
            merged[k++] = nums1[i++];
        } else {
            merged[k++] = nums2[j++];
        }
    }
    // Copy remaining elements
    while (i < size1) merged[k++] = nums1[i++];
    while (j < size2) merged[k++] = nums2[j++];
    
    
    // Prog.
    if (total % 2 == 1) {
        return merged[total / 2];
    } else {
        return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
    }
}

// Solution 2 - Binary Search - O(log(min(m,n)))
double findMedianSortedArrays_binary_search(int* nums1, int size1, int* nums2, int size2) {
    // Make sure size1 <= size2.
    if (size1 > size2) return findMedianSortedArrays_binary_search(nums2, size2, nums1, size1);
    
    // If empty.
    if (size1 == 0) {
        if (size2 % 2 == 1) return nums2[size2 / 2];
        else return (nums2[size2 / 2 - 1] + nums2[size2 / 2]) / 2.0;
    }
    
    // Init.
    int left = 0, right = size1;
    int total = size1 + size2;
    int mid = (total + 1) / 2;
    int max_left;
    int min_right;
    
    int i, j;
    // Prog.
    while (left <= right) {
        i = (left + right) / 2;
        j = mid - i;
        
        if (i < size1 && nums2[j - 1] > nums1[i]) {
            left = i + 1;
        } else if (i > 0 && nums1[i - 1] > nums2[j]) {
            right = i - 1;
        } else {
            if (i == 0) max_left = nums2[j - 1];
            else if (j == 0) max_left = nums1[i - 1];
            else max_left = (nums1[i - 1] > nums2[j - 1]) ? nums1[i - 1] : nums2[j - 1];
            
            if (total % 2 == 1) return max_left;
            

            if (i == size1) min_right = nums2[j];
            else if (j == size2) min_right = nums1[i];
            else min_right = (nums1[i] < nums2[j]) ? nums1[i] : nums2[j];
            
            return (max_left + min_right) / 2.0;
        }
    }
    return 0.0;
}
