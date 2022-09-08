#include <iostream>
#include <fstream>

using namespace std;

int mayor(double mat_p[][5], int cant_cli, string cli[], string prod[])
{
    const int cant_prod {5};
    int max_cli=0;          // variables para encontrar
    int aux=0;              // al cliente con mas productos 
    int cont;               // que superen 13000Kg
    for(int i=0 ; i < cant_cli ; i++){
        cout<< cli[i] <<": ";
        cont=0;
        for(int j=0 ; j < cant_prod ; j++){
            if(mat_p[i][j] > 13000){
                cout<< prod[j];
                cont++;
                if(j+1 < cant_prod)
                    cout<<", ";
            }
        }
        if(cont > aux){
            max_cli = i;
            aux = cont;
        }
        cout<< endl;
    }
    return max_cli;
}

void sortdoble(double mat_d[][5], int cliente, int v_aux[], int cant_pro)
{
	int i, pos, imax;
    for (pos = 0; pos < cant_pro - 1 ; pos++) {
		imax = pos;
		for (i = pos+1 ; i < cant_pro ; i++)
			if (mat_d[cliente][i] < mat_d[cliente][imax])
				imax = i;
		swap(mat_d[cliente][pos], mat_d[cliente][imax]);
		swap(v_aux[pos], v_aux[imax]);
	}
}

int main()
{
    const int cant_cli {8};
    const int cant_pro {5};
    ifstream archi1, archi2;
    double mat_p[cant_cli][cant_pro];    // matriz de peso acumulado
    double mat_d[cant_cli][cant_pro];    // matriz de distacia total
    string vec_c[cant_cli];    // vector de nombres de clientes
    string vec_p[cant_pro];    // vector de nombres de productos
    int vec_aux[cant_cli];     // vector auxiliar para no modificar el de nombres
    int vec_e[cant_pro] {};    // vector para contar cantidad de entregas por producto
    int aux=0;          // auxiliar para cargar vectores
    int cc=0;           // codigo cliente para cargar las matrices
    int cp=0;           // codigo producto para cargar las matrices
    int max_cli=0;      // cliente con mayor cant de prod que superan 13000Kg
    double pe=0;        // peso total para cargar las matrices
    double di=0;        // distancia recorrida para cargar las matrices
    archi1.open("Nombres.txt");
    archi2.open("Datos.txt");
    if(!archi1) {
        cout<<"Error al abrir el archivo de nombres."<< endl;
        return 1;
    }
    if(!archi2) {
        cout<<"Error al abrir el archivo de datos."<< endl;
        archi1.close();
        return 1;
    }
    for(int i=0; i < (cant_cli+cant_pro); i++) {
        if(i < cant_cli)
            archi1>> vec_c[i];
        else
            archi1>> vec_p[aux++];
    }
    archi1.close();
    while(archi2>> cc >> cp >> pe >> di){
        mat_p[cc][cp]+=pe;
        mat_d[cc][cp]+=di;
        vec_e[cp]++;
    }
    archi2.close();
    cout<<"Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:"<< endl;
    max_cli = mayor(mat_p, cant_cli, vec_c, vec_p);
    for(int i=0; i < cant_pro ; i++)        // carga el vector auxiliar
        vec_aux[i] = i;
    sortdoble(mat_d, max_cli, vec_aux, cant_pro);
    cout<< endl <<"Listado de Km recorridos por tipo de producto (ascendente):"<< endl;
    for (int i=0; i < cant_pro; i++)
		cout << vec_p[vec_aux[i]] << ": " << mat_d[max_cli][i] << endl;
    cout<< endl <<"Cantidad de entregas para el tipo de producto "<< vec_p[vec_aux[cant_pro-1]] 
        <<": "<< vec_e[vec_aux[cant_pro-1]] << endl;
    return 0;
}