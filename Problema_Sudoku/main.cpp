#include <iostream>
#include <fstream>
///sudoku
using namespace std;
struct pozitie
{
    int x,y;
} v[100];   ///vectorul in care se retin pozitiile din matrice care se completeaza in bt
int x[100],a[10][10],n,k,p;   ///x este vectorul solutie, x[k] apartine {1,2,...9}, valoarea de pe pozitia (v[k].x,v[k].y)
ofstream g("sudoku.out");

void init(int k)
{
    x[k]=0;
}

int succ(int k)
{
    if(x[k]<9)
    {
        x[k]++;
        return 1;
    }
    return 0;
}

int linie(int l, int x)  ///verifica daca pe linia l se gaseste valoarea x
{
    for(int i=1; i<=9; i++)
        if(a[l][i]==x) return 1;
    return 0;
}

int coloana(int c, int x)   ///verifica daca pe coloana c se gaseste valoarea x
{
    for(int i=1; i<=9; i++)
        if(a[i][c]==x) return 1;
    return 0;
}

void patrat(int x, int y, int &l, int &c)
///determina coordonatele coltului stanga sus al patratului de 3x3 in care se gaseste pozitia (x,y)
{
    if(x%3==0) l=(x/3-1)*3+1;
    else l=x/3*3+1;
    if(y%3==0) c=(y/3-1)*3+1;
    else c=y/3*3+1;
}

int epatrat(int l, int c, int x)
///verifica daca in patratul de 3x3 cu coltul stanga sus de coordonate (l,c) se gaseste valoarea x
{
    for(int i=l; i<l+3; i++)
        for(int j=c; j<c+3; j++)
            if(a[i][j]==x) return 1;
    return 0;
}

int valid(int k)
{
    if(linie(v[k].x,x[k])==1) return 0;     ///verifica daca pe linia v[k].x se mai gaseste valoarea x[k]
    if(coloana(v[k].y,x[k])==1) return 0;   ///verifica daca pe coloana v[k].y se mai gaseste valoarea x[k]
    int l,c;
    patrat(v[k].x,v[k].y,l,c);  ///determina patratul unde se gaseste pozitia unde se gaseste (v[k].x, v[k].y)
    if(epatrat(l,c,x[k])==1) return 0;  ///verifica daca in patrat se mai gaseste x[k]
    for(int i=1; i<=k-1; i++)
        if(x[i]==x[k])      ///daca x[k] se repeta in solutie
        {
            if(v[i].x==v[k].x || v[i].y==v[k].y) return 0;  ///daca se gaseste pe aceeasi linie sau coloana
            int l1,c1;
            patrat(v[i].x,v[i].y,l1,c1);        ///daca sunt in acelasi patrat
            if(l==l1 && c==c1) return 0;
        }
    return 1;
}

int sol(int k)
{
    return k==p;        ///cand s-au completat toate pozitiile
}

void copiere(int b[][10],int a[][10])
{
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
            b[i][j]=a[i][j];
}

void tipar(int k)
{
    int b[10][10],i,j;
    copiere(b,a);       ///copiez matricea initiala in matricea b ca sa afisez matricea obtinuta
    for(i=1; i<=k; i++) b[v[i].x][v[i].y]=x[i];   ///construiesc matricea solutie
    for(i=1; i<=9; i++)
    {
        for(j=1; j<=9; j++)
            g<<b[i][j]<<' ';
        g<<endl;
    }
}

void citire()
{
    ifstream f("sudoku.in");
    p=0;
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
        {
            f>>a[i][j];
            if(a[i][j]==0)   ///determin vectorul cu pozitiile necompletate
            {
                p++;
                v[p].x=i;
                v[p].y=j;
            }
        }
    f.close();
}

void bt(int k)
{
    init(k);
    while(succ(k))
        if(valid(k))
            if(sol(k))
                tipar(k);
            else bt(k+1);
}

int main()
{
    citire();
    bt(1);
    return 0;
}
