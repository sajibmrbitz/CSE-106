#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int stocks[n];
    for(int i=0;i<n;i++){
        scanf("%d",&stocks[i]);
    }

    int max=stocks[0];
    for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
            int sum=0;
            for(int k=i;k<=j;k++){
                sum+=stocks[k];
            }
            if(sum>max){
                max=sum;
            }
        }
    }

    printf("%d",max);

    return 0;
}
/*
You are working as a software developer for a stock trading company. The
company wants to analyze the daily profit and loss from a particular stock over a
period of days. The data is represented as an array of integers, where each element
indicates the profit (positive number) or loss (negative number) for that day.
Your task is to write a C program that finds the maximum profit that can be
achieved within a contiguous sequence of days.

Input: An integer array stocks (-10^9 ≤ stocks[i] ≤ 10^9) of size n (1 ≤ n ≤ 500)

representing daily profit/loss values.
Output: maximum profit.

Example 1:
Input: n = 9, stocks[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4}
Output: 6
Explanation: The subarray {4, -1, 2, 1} has the largest sum.

Example 2:
Input: n = 5, stocks[] = {5, 4, 1, 7, 8}
Output: 25
*/

//* EFFICIENT: kadane's Algorithm *//
/*
#include <stdio.h>

int main()
{
    int n;
    if (scanf("%d", &n) != 1) return 0; 

    int stocks[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &stocks[i]);
    }

    //*Initialize variables
    //*max_so_far holds the best result found. 
    //*We init with stocks[0] to handle cases where all numbers are negative.
    long long max_so_far = stocks[0]; 
    long long current_max = stocks[0];

    for(int i = 1; i < n; i++){
        //*Logic: Should we start a new subarray at current element, 
        //*or extend the existing subarray?
        //*Equivalent to: current_max = max(stocks[i], current_max + stocks[i])
        if (current_max + stocks[i] > stocks[i]) {
            current_max += stocks[i];
        } else {
            current_max = stocks[i];
        }

        //*Update the global maximum if the current subarray is better
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
    }

    printf("%lld", max_so_far);

    return 0;
}
*/