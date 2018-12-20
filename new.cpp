//#include <stdio.h>
#include <iostream>
//#include <stdlib.h>
#include <string.h>
#include <fstream>
//#include <stack>
#include <vector>
#include <queue>
//#include <cmath>
#include <chrono>
#define SIZE 1001

using namespace std;

struct Pair{
    int x;
    int y;
    Pair(int i,int j):x(i),y(j){}
};

//int Result;
char maze[SIZE][SIZE];
//int shortest[SIZE][SIZE];
int parent_x[SIZE][SIZE];
int parent_y[SIZE][SIZE];
bool visited[SIZE][SIZE]={0};
bool clean[SIZE][SIZE]={0};
int R, C;
int life;
int start_x,start_y;
int steps=0;
vector<Pair> STEP;
vector<Pair> order;

void Route(int goal_x, int goal_y)
{
    vector<Pair> route;
    int x = goal_x;
    int y = goal_y;

    //cout << "goal: "<< goal_x << " " << goal_y <<endl;
    //cout << "start:" << start_x << " "<<start_y << endl;

    while(x!=start_x || y!=start_y){
        clean[x][y]=true;
        int new_x = parent_x[x][y];
        int new_y = parent_y[x][y];
        route.push_back(Pair(new_x, new_y));
        //cout << new_x << " " << new_y <<endl;
        x = new_x;
        y = new_y;
    }
    //cout << endl;

    route.pop_back();

    for (vector<Pair>::reverse_iterator it = route.rbegin() ; it != route.rend(); ++it){
        STEP.push_back(Pair((*it).x, (*it).y));
        steps++;
    }

    STEP.push_back(Pair(goal_x, goal_y));

    for (auto it = route.begin(); it != route.end(); ++it){ //recharge
        STEP.push_back(Pair((*it).x, (*it).y));
        steps++;
    }
    STEP.push_back(Pair(start_x, start_y));
    //cout << endl;

    route.clear();
}

void bfs(int x, int y, int R, int C)
{
    queue<Pair> q;

    q.push(Pair(x,y));
    visited[x][y]=true;

    while (!q.empty()) {
        Pair f = q.front();
        order.push_back(Pair(f.x, f.y));
        q.pop();

        //cout << f.x << " " << f.y << endl;

        if(maze[f.x+1][f.y]!='1'&&(f.x+1)<R){
            if(!visited[f.x+1][f.y]){
                //cout << "down\n";
                parent_x[f.x+1][f.y]=f.x;
                parent_y[f.x+1][f.y]=f.y;
                q.push(Pair(f.x+1,f.y));
                visited[f.x+1][f.y]=true;
            }
        }
        if(maze[f.x][f.y+1]!='1'&&(f.y+1)<C){
            if(!visited[f.x][f.y+1]){
                //cout << "right\n";
                parent_x[f.x][f.y+1]=f.x;
                parent_y[f.x][f.y+1]=f.y;
                q.push(Pair(f.x,f.y+1));
                visited[f.x][f.y+1]=true;
            }
        }
        if(maze[f.x-1][f.y]!='1'&&(f.x-1)>=0){
            if(!visited[f.x-1][f.y]){
                //cout << "up\n";
                parent_x[f.x-1][f.y]=f.x;
                parent_y[f.x-1][f.y]=f.y;
                q.push(Pair(f.x-1,f.y));
                visited[f.x-1][f.y]=true;
            }
        }
        if(maze[f.x][f.y-1]!='1'&&(f.y-1)>=0){
            if(!visited[f.x][f.y-1]){
                //cout << "left\n";
                parent_x[f.x][f.y-1]=f.x;
                parent_y[f.x][f.y-1]=f.y;
                q.push(Pair(f.x,f.y-1));
                visited[f.x][f.y-1]=true;
            }
        }
    }
}

/*void visit(char(*maze)[SIZE], int x, int y, int R, int C)
{
    visited[x][y]=true;
    if(maze[x+1][y]!='1'&&(x+1)<R){
        if(!visited[x+1][y]){
            parent_x[x+1][y]=x;
            parent_y[x+1][y]=y;
            visit(maze, x+1, y, R, C);//down
        }
    }
    if(maze[x][y+1]!='1'&&(y+1)<C){
        if(!visited[x][y+1]){
            parent_x[x][y+1]=x;
            parent_y[x][y+1]=y;
            visit(maze, x, y+1, R, C);//right
        }
    }
    if(maze[x-1][y]!='1'&&(x-1)>=0){
        if(!visited[x-1][y]){
            parent_x[x-1][y]=x;
            parent_y[x-1][y]=y;
            visit(maze, x-1, y, R, C);//up
        }
    }
    if(maze[x][y-1]!='1'&&(y-1)>=0){
        if(!visited[x][y-1]){
            parent_x[x][y-1]=x;
            parent_y[x][y-1]=y;
            visit(maze, x, y-1, R, C);//left
        }
    }
}*/


int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

    //open file
    char iname[15] = "/floor.data";
    char ipath[30];

    strcpy(ipath, argv[1]);
    strcat(ipath, iname);

    ifstream inFile;
    inFile.open(ipath);

    //create output file
    char oname[15] = "/final.path";
    char opath[30];

    strcpy(opath, argv[1]);
    strcat(opath, oname);
    ofstream outFile;
    outFile.open(opath);

    //ofstream outFile;
    //outFile.open("final.path");

    //Result=1000000;

    //scanf("%d %d %d",&R, &C, &life);
    inFile >> R >> C >> life;

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            //scanf(" %c", &maze[i][j]);
            inFile >> maze[i][j];
            //shortest[i][j] = 1000000;
            if(maze[i][j]=='R'){
                start_x=i;
                start_y=j;
                parent_x[i][j]=i;
                parent_y[i][j]=j;
            }
        }
    }

    inFile.close();
    //cout << "scan_done" << endl;

    //visit(maze, start_x, start_y, R, C);
    bfs(start_x, start_y, R, C);

    //cout << "visit_func_done" << endl;

    /*for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }*/
    /*for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << parent_x[i][j] << " ";
        }
        cout << endl;
    }
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << parent_y[i][j] << " ";
        }
        cout << endl;
    }*/

    /*for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(maze[i][j]=='0') Route(i,j);
        }
    }*/
    
    //cout << "start:" << start_x << " "<<start_y << endl;
    for (vector<Pair>::reverse_iterator it = order.rbegin() ; it != order.rend(); ++it){
        if(maze[(*it).x][(*it).y]=='0' && clean[(*it).x][(*it).y]==false) Route((*it).x,(*it).y);
    }

    /*for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << clean[i][j] << " ";
        }
        cout << endl;
    }*/

    outFile << steps << "\n";
    for (auto it = STEP.begin() ; it != STEP.end(); ++it){
        outFile << (*it).x  << " " << (*it).y << "\n";
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}



