#include <iostream>
using namespace std;

#define MAX 105
#define UNVISITED 0

int adj[MAX][MAX];
int visited[MAX];

int group[MAX];
int gsize;

void dfs(int u,int n){
    visited[u]=1;
    group[gsize++]=u;

    for(int i=0;i<n;i++){
        if(adj[u][i]==1 && visited[i]==UNVISITED){
            dfs(i,n);
        }
    }
}

int main(){
    int n;
    cin>>n;

    int a,b;
    cin>>a>>b;
    while(a!=-1 && b!=-1){
        adj[a][b]=1;
        adj[b][a]=1;
        cin>>a>>b;
    }

    int gCount=0;

    for(int i=0;i<n;i++) {
        if(visited[i]==UNVISITED){
            gsize=0;
            dfs(i,n);

            if(gsize>1){
                for(int x=0;x<gsize;x++){
                    for(int y=x+1;y<gsize;y++){
                        if(group[x]>group[y]){
                            int temp=group[x];
                            group[x]=group[y];
                            group[y]=temp;
                        }
                    }
                }
                gCount++;
                cout<<"Group "<<gCount<<": {";

                for(int k=0;k<gsize;k++){
                    cout<<group[k];
                    if(k!=gsize-1){
                        cout<<", ";
                    }
                }
                cout<<"} | ";

                int missing=0;
                for(int x=0;x<gsize;x++){
                    for(int y=x+1;y<gsize;y++){
                        int u=group[x];
                        int v=group[y];
                        if(adj[u][v]==0){
                            cout<<"["<<u<<", "<<v<<"] ";
                            missing=1;
                        }
                    }
                }

                if(!missing){
                    cout<<"none";
                }
                cout<<endl;
            }
        }
    }
    return 0;
}
