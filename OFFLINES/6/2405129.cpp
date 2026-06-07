#include<bits/stdc++.h>
using namespace std;

#define MAX_N 100005

class City{
public:
    int id;
    double x,y;
    City(){
        id=0;
        x=0.0;
        y=0.0;
    }
    City(int id,double x,double y){
        this->id=id;
        this->x=x;
        this->y=y;
    }
};

class Edge{
public:
    int u,v;
    double cost;
    Edge(){
        u=0;
        v=0;
        cost=0.0;
    }
    Edge(int u,int v,double cost){
        this->u=u;
        this->v=v;
        this->cost=cost;
    }
};

int N,M;
vector<City> cities;
vector<int> adj[MAX_N]; 
vector<Edge> finalEdges;
double totalCost=0.0;

int visited[MAX_N];
int stepCount=0;

double Cost(City a,City b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool cmpX(City a,City b){
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}

bool cmpEdge(Edge a,Edge b){
    return a.cost<b.cost;
}

bool dfs(int u,int target){
    if(u==target) return true;
    visited[u]=stepCount;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(visited[v]!=stepCount){
            if(dfs(v,target)) return true;
        }
    }
    return false;
}

bool isConnected(int u,int target){
    stepCount++;
    return dfs(u,target);
}

void solve(int l,int r){
    int cnt=r-l+1;
    if(cnt<=M){
        vector<Edge> tempEdges;
        for(int i=l;i<=r;i++){
            for(int j=i+1;j<=r;j++){
                double d=Cost(cities[i],cities[j]);
                Edge newEdge(cities[i].id,cities[j].id,d);
                tempEdges.push_back(newEdge);
            }
        }

        sort(tempEdges.begin(),tempEdges.end(),cmpEdge);
        for(int i=0;i<tempEdges.size();i++){
            Edge e=tempEdges[i];
            if(!isConnected(e.u,e.v)){
                adj[e.u].push_back(e.v);
                adj[e.v].push_back(e.u);
                finalEdges.push_back(e);
                totalCost+=e.cost;
            }
        }
        return;
    }
    
    int mid=l+(r-l)/2;
    solve(l,mid);
    solve(mid+1,r);
    
    int lStart=max(l,mid-M+1);
    int rEnd=min(r,mid+M);
    Edge minEdge(-1,-1,999999999.0);
    
    for(int i=lStart;i<=mid;i++){
        for(int j=mid+1;j<=rEnd;j++){
            double d=Cost(cities[i],cities[j]);
            if(d<minEdge.cost){
                minEdge=Edge(cities[i].id,cities[j].id,d);
            }
        }
    }
    
    if(minEdge.u!=-1){
        adj[minEdge.u].push_back(minEdge.v);
        adj[minEdge.v].push_back(minEdge.u);
        finalEdges.push_back(minEdge);
        totalCost+=minEdge.cost;
    }
}

int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        int id;
        double x,y;
        cin>>id>>x>>y;
        City newCity(id,x,y);
        cities.push_back(newCity);
    }
    sort(cities.begin(),cities.end(),cmpX);
    solve(0,N-1);
    cout<<fixed<<setprecision(2);
    cout<<"Total Cost: "<<totalCost<<"\n";
    cout<<"Edges:\n";
    for(int i=0;i<finalEdges.size();i++){
        cout<<finalEdges[i].u<<" "<<finalEdges[i].v<<"\n";
    }
    return 0;
}


/*
Time Complexity Analysis:

1. Sorting: sorting all N cities based on their x coordinates 
   takes O(NlogN) time (for STL sorting)

2. Base Case: 
   Here M<=50, which is a small number.
   generating all edge combinations, sorting them and running dfs,
   looks like O(M^3) in worst case, but since M<=50, 
   it can be considered just O(1).

3. Merge Step: 
   Instead of checking all pairs, only checked the boundary cities.
   Max M cities from the left half and M cities from the right half.
   Total distance comparisons =M*M=M^2. 
   Again since M<=50, this merge step can also be considered O(1) time.

4. Recurrence Relation for Divide and Conquer:
   Since dividing takes O(1) and merging also takes O(1), the relation is:
   T(N)=2T(N/2)+O(1)
   By Master Theorem, we get T(N)=O(N)

   Overall Time Complexity =Sorting Time+DnC Time
                           =O(NlogN)+O(N)
                           =O(NlogN)

Space Complexity:
O(N) for vectors and recursion (stack)
*/