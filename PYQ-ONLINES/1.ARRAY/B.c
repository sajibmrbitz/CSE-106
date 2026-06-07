#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int scores[n];
    for(int i=0;i<n;i++){
        scanf("%d",&scores[i]);
    }

    for(int i=0;i<n;i++){
        int isleader=1;
        for(int j=i+1;j<n;j++){
            if(scores[j]>scores[i]){
                isleader=0;
                break;
            }
        }
        if(isleader){
            printf("%d ",scores[i]);
        }
    }
    

    return 0;
}

/*
You are given an array of integers representing the scores achieved by players in a
game, listed in the order they finished. A player is considered a "leader" if their
score is greater than or equal to every player's score who finished after them. The
last player is always a leader.
Write a C program to find all the leaders in the array and print their scores in the
order they appear.

Input: An array scores (-10^9 ≤ scores[i] ≤ 10^9) of size n (1 ≤ n ≤ 10^4) where each
element is an integer.
Output: Leaders’ score in appeared order.

Example 1:
Input: n = 6, scores[] = {4, -1, -3, 2, -2, 0}
Output: 4, 2, 0

Example 2:
Input: n = 6, scores[] = {45, 78, 23, 19, 34, 15}
Output: 78, 34, 15
*/