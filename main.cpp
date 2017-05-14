#include <iostream>
using namespace std;
struct Comando
{
    char comd;
    int pos;
};
struct Jugador
{
    int codigo;
    string nombre;
    Comando comandos[50];
    char mundo[15][15];
    int curx;
    int cury;
};
int menu();
void inicializar(Jugador jugadores[],char solucion,int N);
void presentarJugadores(Jugador jugadores[], int N);
int buscarJugador(Jugador jugadores[], int N, string buscar);
void juego(Jugador jugadores[], int N, int n);

int main()
{
    int N=5, opt=0, n=0;
    Jugador jugadores[N];
    char solucion[3][4];
    cout<<"Ingrese la cantidad de filas y columnas: ";
    cin>>n;
    string nombres[N] = {"Katherine","Patricia","Liliana","Lizzeth","Marisol"};
    string buscar;
    char comandos[N*9] = {'B','N','D','N','D','N','D','N','#','A','N','B','N','D','N','D','N','#','A','N','B','N','D','N','D','D','#','A','N','B','N','D','N','D','N','#','B','N','A','N','B','N','D','D','#'};
    int pos[N*9] = {0,8,0,7,0,7,0,6,0,0,3,0,1,0,7,0,3,0,0,3,0,1,0,7,0,0,0,0,7,0,1,0,7,0,7,0,0,1,0,6,0,1,0,0,0};
    char mundo[n*n*N];
    for(int x=0; x<N*n*n; x++)
    {
        mundo[x]=' ';
    }
    cout<<endl;
    do
    {
        opt=menu();
        switch (opt)
        {
        case 1:
            presentarJugadores(nombres, N);
            break;
        case 2:
            cout<<"Ingrese el nombre del jugador a ubicar: ";
            cin>>buscar;
            cout<<"El jugador se encuentra en la posicion "<<buscarJugador(nombres, N, buscar)<<endl;
            break;
        case 3:
            juego(nombres,comandos,mundo,pos,N,n);
            break;
        case 4:
        default:
            cout<<"Hasta luego..."<<endl;
            break;
        }
    }
    while (opt>0&&opt<5);
    return 0;
}

int menu()
{
    int opt=0;
    cout<<"----------Simulador Logo----------"<<endl;
    cout<<"1. Mostrar jugadores"<<endl;
    cout<<"2. Buscar jugador"<<endl;
    cout<<"3. Simular juego"<<endl;
    cout<<"4. Validar dibujos"<<endl;
    cout<<"5. Salir"<<endl;
    cout<<"--------Ingrese su eleccion: ";
    cin>>opt;
    return opt;
}

void presentarJugadores(string nombres[], int N)
{
    string temp=" ";
    string aux[N];
    for(int i=0; i<N; i++)
    {
        aux[i]=nombres[i];
    }
    for (int i = 0; i < N; i++)
    {
        for( int j=0 ; j < N - 1; j++)
            if (aux[j] > aux[j+1])
            {
                temp = aux[j];
                aux[j] = aux[j+1];
                aux[j+1] = temp;
            }
    }
    for(int i = 0; i < N; i++)
    {
        cout<<"Jugador "<<aux[i]<<endl;
    }
}

int buscarJugador(string nombres[], int N, string buscar)
{
    for (int i = 0; i < N; i++)
    {
        if(buscar==nombres[i])
        {
            return i;
        }
    }
}

void juego(string nombres[], char cmd[],char mundo[],int pos[], int N, int n)
{
    bool lapiz=false;
    int ubi=0,salto=1,cont=1;
    for (int i=0; i<N; i++)
    {
        lapiz=false;
        salto=1;
        cont=1;
        ubi=i*(n*n)- salto;
        cout<<"Nombre jugador: "<<nombres[i]<<endl;
        cout<<"Comandos: ";
        for(int x=i*9; x<(i*9)+9; x++)
        {
            cout<<cmd[x]<<" ";
        }
        cout<<endl;
        for (int j=i*9; j<(i*9)+9; j++)
        {
            switch (cmd[j])
            {
            case 'B':
                lapiz=true;
                break;
            case 'A':
                lapiz=false;
                break;
            case 'D':
                cont++;
                if(cont%4==0)
                    salto=-n;
                if(cont%4==1)
                    salto=1;
                if(cont%4==2)
                    salto=n;
                if(cont%4==3)
                    salto=-1;
                break;
            case 'N':
                for(int f=0; f<pos[j]; f++)
                {
                    ubi+=salto;
                    if(lapiz)
                    {
                        mundo[ubi]='*';
                    }
                }
                break;
            case '#':
                break;
            }
        }
        for(int x=(i*n*n); x<(i*n*n)+(n*n); x++)
        {
            if(x%n==0)
                cout<<endl;
            cout<<mundo[x];
        }
        cout<<endl;
    }
}
