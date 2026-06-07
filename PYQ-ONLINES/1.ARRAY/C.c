#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int votes[n];
    for(int i=0;i<n;i++){
        scanf("%d",&votes[i]);
    }

    int count[1000001]={0};    // better to declare in global scope to avoid stack overflow
    for(int i=0;i<n;i++){
        count[votes[i]]++;
    }
    int majority=1;
    for(int i=0;i<n;i++){
        float requirement=n/2.0;
        if(count[votes[i]]>requirement){
            printf("%d",votes[i]);
            majority=0;
            break;
        }
    }
    if(majority){
        printf("No Majority Candidate");
    }

    return 0;
}

/*
A university is organizing a student council election. Each student can vote for one
candidate. The university wants to know if any candidate received more than half
of the total votes (i.e., a majority). You are given an array of integers, where each
integer represents the candidate ID voted for by a student. Write a C program to
determine if there is a majority candidate, and if so, print their candidate ID. If no
candidate has a majority, print "No Majority Candidate". Each student voted for
exactly one candidate.

Input: An array votes (1 ≤ votes[i] ≤ 10^6) of size n (1 ≤ n ≤ 10^4) where each
element is a positive integer.
Output: candidate ID if there is a majority candidate or “No Majority Candidate”.

Example 1:
Input: n = 7, votes[] = {2, 2, 1, 2, 3, 2, 2}
Output: 2

Example 2:
Input: n = 7, votes[] = {1, 2, 3, 2, 3, 1, 2}
Output: No Majority Candidate
*/