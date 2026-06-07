#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Element {
    int val;
    int idx;
};

bool compareElements(const Element& a, const Element& b) {
    return a.val < b.val;
}

void findTriplet(const vector<int>& arr) {
    int n = arr.size();
    if (n < 3) {
        cout << "No triplets found" << endl;
        return;
    }

    vector<Element> elements(n);
    for(int i = 0; i < n; i++) {
        elements[i] = {arr[i], i};
    }

    sort(elements.begin(), elements.end(), compareElements);

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        int target = -elements[i].val;

        while (left < right) {
            int currentSum = elements[left].val + elements[right].val;

            if (currentSum == target) {
                vector<int> result = {elements[i].idx, elements[left].idx, elements[right].idx};
                sort(result.begin(), result.end());
                cout << "Output: [" << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
                return;
            } 
            else if (currentSum < target) {
                left++;
            } 
            else {
                right--;
            }
        }
    }
    cout << "Output: No triplets found" << endl;
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

    findTriplet(arr);

    return 0;
}

/*
//*LEETCODE 15 - 3Sum
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n=nums.size();

        sort(nums.begin(),nums.end());

        for(int i=0;i<n-2;i++){
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }

            int left=i+1;
            int right=n-1;
            while(left<right){
                int sum=nums[i]+nums[left]+nums[right];
                if(sum==0){
                    result.push_back({nums[i],nums[left],nums[right]});

                    while(left<right && nums[left]==nums[left+1])   left++;
                    while(left<right && nums[right]==nums[right-1])   right--;
                    left++;
                    right--;
                }
                else if(sum<0){
                    left++;
                }
                else    right--;
            }
        }
        return result;
    }
};
*/