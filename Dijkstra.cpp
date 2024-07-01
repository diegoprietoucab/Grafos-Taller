#include <iostream>
#include <fstream>

using namespace std;

#define infinito 999

int costo[100][100], numeroVertices;

void inicializarVisitados(bool visitados[])
{
    for (int i = 0; i < numeroVertices; i++)
    {
        visitados[i] = false;
    }
}

void inicializarDistancias(int distancias[])
{
    for (int i = 0; i < numeroVertices; i++)
    {
        distancias[i] = infinito;
    }
}

void inicializarPadres(int padres[])
{
    for (int i = 0; i < numeroVertices; i++)
    {
        padres[i] = i;
    }
}

int encontrarPadre(int i, int padres[])
{
	while (padres[i] != i)
    {
        i = padres[i];
    }
    return i;
}
 

void actualizarPadres(int i, int j, int padres[])   
{
	int a = encontrarPadre(i, padres);
	int b = encontrarPadre(j, padres);
	padres[a] = b;
}
 
void kruskal()
{
    int padres[numeroVertices];
    inicializarPadres(padres);
    for (int aristas = 0; aristas < numeroVertices - 1; aristas++)
    {
		int minimo = infinito;
        int fila = -1; 
        int columna = -1;
		for (int i = 0; i < numeroVertices; i++) 
        {
			for (int j = 0; j < numeroVertices; j++)
            {
				if ((encontrarPadre(i, padres) != encontrarPadre(j, padres)) && (costo[i][j] < minimo))
				{
					minimo = costo[i][j];
					fila = i;
					columna = j;
				}
			}
		}
		actualizarPadres(fila, columna, padres);
        cout << "Lado: "<< fila + 1 << " - "<< columna + 1 << endl; 
        cout << "Costo: " << minimo << endl;
        cout << endl;
	}
}

int buscarMenor()
{
    int menor = infinito;
    int indice;
    for (int i = 0; i < numeroVertices; i++)
    {
        for (int j = 0; j < numeroVertices; j++)
        {
            if ((costo[i][j]) && (costo[i][j] < menor))
            {
                menor = costo[i][j];
                indice = i;
            }
        }
    }
    return indice;
}

void prim()
{
    bool visitados[numeroVertices];
    inicializarVisitados(visitados);
    visitados[buscarMenor()] = true;
    for (int aristas = 0; aristas < numeroVertices - 1; aristas++)
    {   
        int minimo = infinito;
        int fila = 0;
        int columna = 0;
        for (int i = 0; i < numeroVertices; i++)
        {
            if (visitados[i])
            {
                for (int j = 0; j < numeroVertices; j++)
                {
                    if (costo[i][j] < minimo)
                    {
                        if ((!visitados[j]) && (costo[i][j]))
                        {
                            minimo = costo[i][j];
                            fila = i;
                            columna = j;
                        }
                    }
                }
            }
        }
        cout << "Lado: " << fila + 1 << " - " << columna + 1 << endl;
        cout << "Peso: " << costo[fila][columna] << endl;
        cout << endl;
        visitados[columna] = true;
    }
}

int obtenerMinimo(int distancias[] , bool visitados[])
{
    int clave = 0 ; 
    int minimo = infinito; 
    for(int i = 0; i < numeroVertices ; i++)
    {
        if((!visitados[i]) && (distancias[i] < minimo))
        {
            minimo = distancias[i] ; 
            clave = i; 
        }
    }
    return clave; 
}

void mostrarDijkstra(int distancias[] , int padres[])
{
   for(int i = 0; i < numeroVertices ;i++)
   {
       int temporal = padres[i]; 
       cout << i + 1 << " <- ";
       while(temporal != -1)
       {
           cout<< temporal + 1 << " <- ";
           temporal = padres[temporal]; 
       }
       cout << endl; 
       cout << "Distancia: " << distancias[i] ; 
       cout << endl;
       cout << endl;
    } 
}


void dijkstra(int origen)
{
    int padres[numeroVertices];
    int distancias[numeroVertices];
    bool visitados[numeroVertices]; 
    inicializarDistancias(distancias);
    inicializarVisitados(visitados);
    inicializarPadres(padres);
    distancias[origen] = 0; 
    padres[origen] = -1;
    for(int i = 0; i < numeroVertices; i++)
    {
        int minimo = obtenerMinimo(distancias,  visitados); 
        visitados[minimo] = true ;
        for(int j = 0; j < numeroVertices; j++)
        {
            if ((!visitados[j] && ((distancias[minimo]+costo[minimo][j]) < distancias[j]) && (costo[minimo][j] != infinito)))
            {
                padres[j] = minimo; 
                distancias[j] = distancias[minimo] + costo[minimo][j]; 
            }
        }
    }
    mostrarDijkstra(distancias, padres); 
}

void Menu()
{
    cout << "Escriba 1 para ejecutar el algoritmo de Prim" << endl;
    cout << "Escriba 2 para ejecutar el algoritmo de Kruskal" << endl;
    cout << "Escriba 3 para ejecutar el algoritmo de Dijkstra" << endl;
    cout << "Escriba 0 para salir" << endl;
}

int main()
{
    ifstream archivo;
    int nodo1;
    int nodo2;
    int peso;
    int origen;
    int respuesta;
    archivo.open("Grafo.txt", ios::in);
    if (archivo.is_open())
    {
        archivo >> numeroVertices;
        cout << endl;
        for (int j = 0; j < numeroVertices; j ++)
        {   
            for (int i = 0; i < numeroVertices; i++)
            {
                if (i != j)
                {
                    costo[j][i] = infinito;
                }
                else
                {
                    costo[j][i] = 0;
                }
            }
        }
        while(!archivo.eof())
        {
            archivo >> nodo1;
            archivo >> nodo2;
            archivo >> peso;
            costo[nodo1 - 1][nodo2 - 1] = peso;
            costo[nodo2 - 1][nodo1 - 1] = peso;
        }
        do
        {
            Menu();
            cin >> respuesta;
            cout << endl;
            switch(respuesta)
            {
                case 1:
                {
                    prim();
                    break;
                }
                case 2:
                {
                    kruskal();
                    break;
                }
                case 3:
                {
                    cout << "Introduzca el vertice para iniciar el recorrido con Dijkstra: ";
                    cin >> origen;
                    cout << endl;
                    cout << endl;
                    if ((origen < numeroVertices + 1) && (origen > 0))
                    {
                        dijkstra(origen - 1);
                    }
                    else
                    {
                        cout << "ERROR. El vertice introducido no está en el grafo" << endl;
                        cout << endl;
                    }
                    break;
                }
            }
        } while(respuesta != 0);
        cout << "FIN DEL PROGRAMA" << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << "Error. No se pudo abrir el archivo" << endl;
        cout << endl;
    }
    return 0;
}