#include <iostream>

using namespace std;

struct pozitie
{
    int x,y;
};
pozitie d[9]= {{0,0},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1}};
int n,k,ev,as,x[100],nr=0;
pozitie poz[100];

void init(int k)
{
    x[k]=0;
}
int succesor(int k)
{
    if (x[k]<8)
    {
        x[k]++;
        poz[k].x=poz[k-1].x+d[x[k]].x;
        poz[k].y=poz[k-1].y+d[x[k]].y;
        return 1;
    }
    else return 0;
}
int valid(int k)
{
    if (poz[k].x<1 || poz[k].y<1 || poz[k].x>n || poz[k].y>n) return 0;
    for (int i=1; i<k; i++)
        if (poz[k].x==poz[i].x && poz[k].y==poz[i].y) return 0;
    return 1;
}
int solutie(int k)
{
    return k==n*n;
}
void tipar(int k)
{
    int i;
    nr++;
    for (i=1; i<=n*n; i++) cout<<poz[i].x<<","<<poz[i].y<<" ";
    cout<<endl;
}
void bt(int k)
{
    init(k);
    while (succesor(k))
        if(valid(k))
            if(solutie(k)) tipar(k);
            else bt(k+1);
}
int main()
{
    int i,j;
    cout<<"n= "; cin>>n;
    cout<<"linia de pornire "; cin>>i;
    poz[1].x=i;
    cout<<"coloana de pornire "; cin>>j;
    poz[1].y=j;
    bt(2);
    if (!nr) cout<<"Nu exista solutii";
    else cout<<nr<<" solutii\n";
}
