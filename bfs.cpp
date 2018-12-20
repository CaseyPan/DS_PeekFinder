#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <stack>
#include <vector>
#include <cmath>
#define SIZE 1001

using namespace std;

struct Pair{
    int x;
    int y;
    Pair(int i,int j):x(i),y(j){}
};

int Result;
char maze[SIZE][SIZE];
int shortest[SIZE][SIZE];
int parent_x[SIZE][SIZE];
int parent_y[SIZE][SIZE];
bool visited[SIZE][SIZE]={0};
bool clean[SIZE][SIZE]={0};
int R, C;
int life;
int start_x,start_y;
int steps=0;
vector<Pair> STEP;

void Route(int goal_x, int goal_y)
{
    vector<Pair> route;
    int x = goal_x;
    int y = goal_y;

    while(x!=start_x && y!=start_y){
        clean[x][y]=true;
        route.push_back(Pair(parent_x[x][y], parent_y[x][y]));
        cout << parent_x[x][y] << " " << parent_y[x][y] <<endl;
        x = parent_x[x][y];
        y = parent_y[x][y];
    }

    for (vector<Pair>::reverse_iterator it = route.rbegin() ; it != route.rend(); ++it){
        STEP.push_back(Pair((*it).x, (*it).y));
        steps++;
    }

    for (vector<Pair>::iterator it = route.begin(); it != route.end(); ++it){ //recharge
        STEP.push_back(Pair((*it).x, (*it).y));
        steps++;
    }
    STEP.push_back(Pair(start_x, start_y));
}

void visit(char(*maze)[SIZE], int x, int y, int R, int C, int step, int final_i, int final_j)
{
    visited[x][y]=true;
    if(step==Result) return;
    else if(x==final_i && y==final_j){
        Result=step;
        return;
    }

    maze[x][y]='1';
    if(maze[x+1][y]!='1'&&(x+1)<R){
        if(!visited[x+1][y]){
            parent_x[x+1][y]=x;
            parent_y[x+1][y]=y;
            visit(maze, x+1, y, R, C, step+1, final_i, final_j);//down
        }
    }
    if(maze[x][y+1]!='1'&&(y+1)<C){
        if(!visited[x][y+1]){
            parent_x[x][y+1]=x;
            parent_y[x][y+1]=y;
            visit(maze, x, y+1, R, C, step+1, final_i, final_j);//right
        }
    }
    if(maze[x-1][y]!='1'&&(x-1)>=0){
        if(!visited[x-1][y]){
            parent_x[x-1][y]=x;
            parent_y[x-1][y]=y;
            visit(maze, x-1, y, R, C, step+1, final_i, final_j);//up
        }
    }
    if(maze[x][y-1]!='1'&&(y-1)>=0){
        if(!visited[x][y-1]){
            parent_x[x][y-1]=x;
            parent_y[x][y-1]=y;
            visit(maze, x, y-1, R, C, step+1, final_i, final_j);//left
        }
    }
    maze[x][y]='0';

    return;
}


int main(int argc, char* argv[])
{
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

    Result=1000000;

    //scanf("%d %d %d",&R, &C, &life);
    inFile >> R >> C >> life;

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            //scanf(" %c", &maze[i][j]);
            inFile >> maze[i][j];
            shortest[i][j] = 1000000;
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

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(maze[i][j]=='1'){
                shortest[i][j]=1000000;
            }
            else{
                visit(maze, start_x, start_y, R, C, 0, i, j);
                shortest[i][j]=Result;
            }
            Result = 1000000;
        }
    }


    //cout << "visit_func_done" << endl;

    for(int i=0; i<R; i++){
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
    }

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(maze[i][j]=='0' && clean[i][j]==false) Route(i,j);
        }
    }

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << clean[i][j] << " ";
        }
        cout << endl;
    }


    outFile << steps << "\n";
    for (vector<Pair>::iterator it = STEP.begin() ; it != STEP.end(); ++it){
        outFile << (*it).x  << " " << (*it).y << "\n";
    }

    return 0;
}



