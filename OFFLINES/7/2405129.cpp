#include <bits/stdc++.h>
using namespace std;

void GSA(int I, int D, int R, string S, string T){
    int n=S.size();
    int m=T.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1,0));
    for(int i=0;i<=n;i++){
        dp[i][0]=i*D;
    }
    for(int j=0;j<=m;j++){
        dp[0][j]=j*I;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int cost = (S[i-1]==T[j-1])?0:R;
            dp[i][j]=min({dp[i-1][j-1]+cost, dp[i-1][j]+D, dp[i][j-1]+I});
        }
    }

    int i=n,j=m;
    vector<string> operations;

    while(i>0 || j>0){
        if(i==0){
            operations.push_back(string("Insert ")+T[j-1]);
            j--;
        }
        else if(j==0){
            operations.push_back(string("Delete ")+S[i-1]);
            i--;
        }
        else if(dp[i][j]==dp[i][j-1]+I){
            operations.push_back(string("Insert ")+T[j-1]);
            j--;
        }
        else if(dp[i][j]==dp[i-1][j]+D){
            operations.push_back(string("Delete ")+S[i-1]);
            i--;
        }
        else if(S[i-1]==T[j-1] && dp[i][j]==dp[i-1][j-1]){
            operations.push_back(string("Match ")+S[i-1]);
            i--;
            j--;
        }
        else{
            operations.push_back(string("Replace ")+S[i-1]+" with "+T[j-1]);
            i--;
            j--;
        }
        
    }

    cout<<"Minimum Cost: "<<dp[n][m]<<endl;
    cout<<"Operations:"<<endl;

    for(int k=operations.size()-1;k>=0;k--){
        cout<<operations[k]<<"\n";
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int I,D,R;
    cin>>I>>D>>R;
    cin.ignore();

    string S,T;
    getline(cin,S);
    getline(cin,T);

    GSA(I, D, R, S, T);

    return 0;
}