#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void findMaxSubarray(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;

    long long max_so_far = LLONG_MIN;
    long long current_max = 0;
    int start = 0, end = 0, s = 0;

    for (int i = 0; i < n; i++) {
        current_max += arr[i];

        if (current_max > max_so_far) {
            max_so_far = current_max;
            start = s;
            end = i;
        }

        if (current_max < 0) {
            current_max = 0;
            s = i + 1;
        }
    }

    cout << "Output: [" << start << ", " << end << "]" << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    if (!(cin >> n)) return 0;

    vector<int> arr(n);
    cout << "Enter the elements separated by space: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    findMaxSubarray(arr);

    return 0;
}

/*
//*LEETCODE 53. Maximum Subarray
class Solution {
public:
    int maxSubArray(vector<int>& nums){
        int maxSum=nums[0];
        int currentSum=0;
        for(int i=0;i<nums.size();i++){
            currentSum+=nums[i];
            if(currentSum>maxSum){
                maxSum=currentSum;
            }
            if(currentSum<0){
                currentSum=0;
            }
        }
        return maxSum;
    }
};
*/