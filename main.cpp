#include <iostream>
using namespace std;
struct Comando
{
    char cmd;
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
    string buscar;
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
            cout<<"---El codigo del jugador es: "<<buscarJugador(jugadores, N, buscar)<<endl;
            break;
        case 3:
            juego(jugadores,N,n);
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

void presentarJugadores(Jugador jugadores[], int N)
{
    Jugador temp;
    for (int i = 0; i < N; i++)
    {
        for( int j=0 ; j < N - 1; j++)
            if (jugadores[j].nombre > jugadores[j+1].nombre)
            {
                temp = jugadores[j];
                jugadores[j] = jugadores[j+1];
                jugadores[j+1] = temp;
            }
    }
    for(int i = 0; i < N; i++)
    {
        cout<<"Jugador "<<jugadores[i].nombre<<endl;
    }
}

int buscarJugador(Jugador jugadores[], int N, string buscar)
{
    for (int i = 0; i < N; i++)
    {
        if(buscar==jugadores[i].nombre)
        {
            return jugadores[i].codigo;
        }
    }
}

void juego(Jugador jugadores[], int N, int n)
{
    bool lapiz=false;
    int ubix=0,ubiy=0,salto=1,cont=1, j=0;
    char dir='v';
    for (int i=0; i<N; i++)
    {
        lapiz=false;
        salto=1;
        cont=1;
        ubix=-salto;
        ubiy=0;
        cout<<"Nombre jugador: "<<jugadores[i].nombre<<endl;
        cout<<"Comandos: ";
        while(jugadores[i].comandos[j].cmd!='#')
        {
            cout<<jugadores[i].comandos[j].cmd<<" ";
            j++;
        }
        cout<<endl;
        j=0;
        while(jugadores[i].comandos[j].cmd!='#')
        {
            switch (jugadores[i].comandos[j].cmd)
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
                {
                    salto=-1;
                    dir='v';
                }
                if(cont%4==1)
                {
                    salto=1;
                    dir='h';
                }
                if(cont%4==2)
                {
                    salto=1;
                    dir='v';
                }
                if(cont%4==3)
                {
                    salto=-1;
                    dir='h';
                }
                break;
            case 'N':
                switch(dir)
                {
                case 'v':
                    for(int f=0; f<jugadores[i].comandos[j].pos; f++)
                    {
                        ubiy+=salto;
                        if(lapiz)
                        {
                            jugadores[i].comandos[j].mundo[ubix][ubiy]='*';
                        }
                    }
                    break;
                case 'h':
                    for(int f=0; f<jugadores[i].comandos[j].pos; f++)
                    {
                        ubix+=salto;
                        if(lapiz)
                        {
                            jugadores[i].comandos[j].mundo[ubix][ubiy]='*';
                        }
                    }
                    break;
                }
                break;
            case '#':
                break;
            }
            jugadores[i].curx=ubix;
            jugadores[i].cury=ubiy;
            j++;
        }
        for(int x=0; x<n; x++)
        {
            for(int y=0; y<n; y++)
            {
                cout<<mundo[x][y];
            }
            cout<<endl;
        }
        cout<<endl;
    }
}
void inicializar(Jugador jugadores[],char solucion,int N)
{
    string nombres[N] = {"Katherine","Patricia","Liliana","Lizzeth","Marisol"};
    char comandos[N*9] = {'B','N','D','N','D','N','D','N','#','A','N','B','N','D','N','D','N','#','A','N','B','N','D','N','D','D','#','A','N','B','N','D','N','D','N','#','B','N','A','N','B','N','D','D','#'};
    int pos[N*9] = {0,8,0,7,0,7,0,6,0,0,3,0,1,0,7,0,3,0,0,3,0,1,0,7,0,0,0,0,7,0,1,0,7,0,7,0,0,1,0,6,0,1,0,0,0};
    for(int i=0; i<3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            solucion[i][j]=' ';
        }
    }

    for (int x = 0; x < N; x++)
    {
        jugadores[x].codigo=x+1;
        jugadores[x].nombre=nombres[x];
        jugadores[x].curx=0;
        jugadores[x].cury=0;
        for (int i = x+9; i < (x+9)+9; ++i)
        {
            jugadores[x].comandos[i].cmd=comandos[i];
            jugadores[x].comandos[i].pos=pos[i];
        }
        for(int i=0; i<15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                jugadores[x].mundo[i][j]=' ';
            }
        }
    }
}
