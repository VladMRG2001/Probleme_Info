#include <iostream>
#include <fstream>
using namespace std;
ifstream f("back.in");
ofstream g("back.out");

struct poz
{
    int x,y;
};

int x[101],alpin[11][11],k,n,m,ii,ji,as,ev,p,maxim=-100,imax,jmax,nrmax;
poz poz[100],pmax[20],d[9]= {(0,0),(-1,0),(0,-1),(-1,-1),(1,1),(1,0),(0,1),(-1,1),(1,-1)};

void citire()
{
    f>>m>>n>>p;
    int i,j;
    for(i=1; i<=m; i++)
        for(j=1; j<=n; j++)
            {
                f>>alpin[i][j];
                if(alpin[i][j]>maxim)
                    maxim=alpin[i][j];
            }
        for(i=1; i<=m; i++)
        for(j=1; j<=n; j++)
        if(alpin[i][j]==maxim)
        {
            nrmax++;
            pmax[nrmax].x=i;
            pmax[nrmax].y=j;
        }
}

int succ(int k)
{
    if(x[k]<8)
    {
        x[k]++;
        poz[k].x=poz[k-1].x+d[x[k]].x;
        poz[k].y=poz[k-1].y+d[x[k]].y;
    }
    return 0;
}
bool valid(int k)
{
    if(poz[k].x<1|| poz[k].x>n || poz[k].y<1 || poz[k].y>n)
        return 0;
    if(alpin[poz[k].x][poz[k].y]<=alpin[poz[k-1].x][poz[k-1].y])
        return 0;
    if(alpin[poz[k].x][poz[k].y]>p)
        return 0;
    for(int i=1; i<=k-1; i++)
        if(poz[k].x==poz[i].x && poz[k].y==poz[i].y)
            return 0;
    return 1;

}

int sol(int k)
{
    if(poz[k].x==pmax[k].x||poz[k].y==pmax[k].y)
        return 1;
    else return 0;
}

void tipar(int k)
{
    int i;
    for(i=1; i<=k; i++)
        g<<'('<<poz[i].x<<'),('<<poz[i].y<<')';
    g<<'\n';
}

void bt(int k)
{
    x[k]=0;
    while(succ(k))
        if(valid(k))
            if(sol(k))
                tipar(k);
            else bt(k-1);
}

int main()
{
    citire();
    bt();
}

