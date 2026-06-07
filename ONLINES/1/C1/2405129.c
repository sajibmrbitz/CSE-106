#include <stdio.h>

int main(){

    int n,t,found=0;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    scanf("%d",&t);

    int l=0,r=n-1;
    while(l<r){
        if(arr[l]+arr[r]==t){
            printf("(%d,%d)",l,r);
            found=1;
            break;
        }
        else if(arr[l]+arr[r]<t){
            l++;
        }
        else    r--;
        
    }
    if(!found){
        printf("No pairs found\n");
    }

    return 0;
}