#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

int count=0;  //count is used only after 5th move in predicton and in original game.
int check(char c,char**board){
for(int x=0;x<3;x++){
  int count=0;
 for(int y=0;y<3;y++){
  if(board[x][y]!=c)
  break;
  count++;
}
if(count==3)
    return 1;
}
for(int x=0;x<3;x++){
  int count=0;
 for(int y=0;y<3;y++){
  if(board[y][x]!=c)
  break;
  count++;
}
if(count==3)
    return 1;
}
int count=0;
for(int x=0,y=0;x<3;x++,y++)
{
    if(board[x][y]==c)
        count++;
    else{break;}
}
if(count==3)
    return 1;
    count=0;
for(int x=2,y=0;y<3;x--,y++)
{
    if(board[x][y]==c)
        count++;
    else{break;}
}
if(count==3)
    return 1;
for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(board[i][j]=='-')
    return -1;
return 0;
}
struct node{
int x1,y1,v,d;
};

node cmove(char **nboard,int depth,int count);

node nextmove(char **nboard, int depth,int count){
node best;best.v=INT_MIN;int c;
for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(nboard[i][j]=='-')
   { nboard[i][j]='x';
     if(count>=5)
     c=check('x',nboard);
     else c=-1;

     if(c==1)
     {
         best.v=10;best.d=depth;
         best.x1=i;best.y1=j;
         nboard[i][j]='-';
        return best;
     }
     else if(c==0){
            best.v=0;best.d=depth;
            best.x1=i;best.y1=j;
            nboard[i][j]='-';
       return best;
     }
     node r=cmove(nboard,depth+1,count+1);

     if(r.v>best.v){
        best.v=r.v;
        best.x1=i;best.y1=j;
     }
     else if(r.v==best.v&&r.d<best.d){
        best.v=r.v;
        best.x1=i;best.y1=j;
     }
        nboard[i][j]='-';
   }
   return best;
}
node cmove(char **nboard,int depth,int count){   // should return minimum value;
   int c; node best;best.v=INT_MAX;
for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(nboard[i][j]=='-')
   { nboard[i][j]='o';
     if(count>=5)
      c=check('o',nboard);
     else c=-1;

     if(c==1)
     {
        best.v=-10;best.d=depth;
        best.x1=i;best.y1=j;
        nboard[i][j]='-';
        return best;
     }
     else if(c==0){
         best.v=0;
         best.x1=i;best.y1=j;
         nboard[i][j]='-';
       return best;
     }
     node r=nextmove(nboard,depth+1,count+1);

     if(r.v<best.v)
     {
         best.v=r.v;
         best.x1=i;best.y1=j;
     }
     else if(r.v==best.v&&r.d<best.d){
        best.v=r.v;
         best.x1=i;best.y1=j;
     }
      nboard[i][j]='-';
   }
 return best;
}
int main(){
    char **board=new char*[3];
    for(int i=0;i<3;i++)
        board[i]=new char[3];
for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    board[i][j]='-';
    char **nboard=new char*[3];
    for(int i=0;i<3;i++)
        nboard[i]=new char[3];
cout<<"if you want to start first enter 1 else 0"<<endl;
int start,c;cin>>start;

while(1){
     if(start==1){
     int x,y;cin>>x>>y;
     if(board[x][y]!='-'){
        cout<<"enter a valid move "<<endl;
        continue;
     }
      board[x][y]='x';
     }
     start=1;count++;
     if(count>=5)
      c=check('x',board);
     else{c=-1;}
     if(c==1)
     {
         cout<<"you win "<<endl;
         break;
     }
     else if(c==0){
        cout<<"draw"<<endl;
        break;
     }
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        nboard[i][j]=board[i][j];
        node c1;
        c1=cmove(nboard,1,count+1);

       board[c1.x1][c1.y1]='o'; count++;
     if(count>=5)
     c=check('o',board);
     else{c=-1;}
     if(c==1){
        cout<<"you loose"<<endl;
        break;
     }
     if(c==0)
     {
         cout<<"draw "<<endl;
         break;
     }
     cout<<"board"<<endl;
for(int i=0;i<3;i++){
    for(int j=0;j<3;j++)
    cout<<board[i][j]<<" ";
    cout<<endl;
    }
    cout<<endl;
}
     cout<<"board"<<endl;
for(int i=0;i<3;i++){
    for(int j=0;j<3;j++)
    cout<<board[i][j]<<" ";
    cout<<endl;
    }
}
