#include "red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <limits>


void red::agregar_enrutador(char nombre)
{
    if(enrutadores.find(nombre) != enrutadores.end()) {
        cout << "Error: El enrutador '" << nombre << "' ya existe." << endl;
        return;
    }

    enrutador rou;
    rou.agregar_enlace(nombre,0);
    enrutadores.insert(pair<char,enrutador>(nombre,rou));
    cout << "Enrutador '" << nombre << "' agregado exitosamente." << endl;
}

void red::eliminar_enrutador(char nombre)
{
    map<char,enrutador>::iterator it;

    if(enrutadores.find(nombre) == enrutadores.end()) {
        cout << "No se pudo eliminar: El enrutador '" << nombre << "' no existe." << endl;
        return;
    }

    enrutadores.erase(nombre);


    for(it=enrutadores.begin();it!=enrutadores.end();it++){
        it->second.eliminar_enlace(nombre);
    }
    cout << "Enrutador '" << nombre << "' eliminado exitosamente." << endl;
}

void red::modificar_enrutador_A(char nombre,int nodos,int exec)
{
    map<char,enrutador>::iterator it;
    int peso;
    for(int i=exec;i<nodos;i++){
        peso=1+rand()%101;
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==nombre){
                it->second.agregar_enlace(char('A'+i),peso);
            }
        }
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==char('A'+i)){
                it->second.agregar_enlace(nombre,peso);
            }
        }
    }
}

void red::eliminar_A(char nombre,int nodos,float proba,int exec)
{
    map<char,enrutador>::iterator it;
    int ran;
    float y;
    bool l,aux;
    for(int i=exec;i<nodos;i++){
        y=proba*(RAND_MAX+1)-1;
        ran=rand();
        l=ran<=y;
        if(l==false){
            aux=false;
            for(it=enrutadores.begin();it!=enrutadores.end();it++){
                if(it->first==nombre){
                    if(char('A'+i)!=nombre){
                        aux=it->second.eliminar_enlace_A(char('A'+i));
                    }
                }
            }
            if(aux==true){
                for(it=enrutadores.begin();it!=enrutadores.end();it++){
                    if(it->first==char('A'+i)){
                        if(char('A'+i)!=nombre) it->second.eliminar_enlace_A(nombre);
                    }
                }
            }
        }
    }
}

void red::modificar_enrutador(char nombre)
{
    map<char,enrutador>::iterator it;
    int a,aux;
    char b;

    if(enrutadores.find(nombre) == enrutadores.end()){
        cout << "No se pudo modificar: El enrutador '" << nombre << "' no existe." << endl;
        return;
    }

    cout<<"Ingrese: \n 0. Para modificar enlace \n 1. Para agregar enlace \n 2. Para eliminar enlace \n";
    cin>>a;
    cout << "Ingrese la letra del enrutador con el que desea conectar/modificar: ";
    cin >> b;


    if(enrutadores.find(b) == enrutadores.end()){
        cout << "Error: El enrutador '" << b << "' no existe. No se puede crear/modificar el enlace." << endl;
        return;
    }
    if (nombre == b) {
        cout << "Error: No se puede crear un enlace de un enrutador consigo mismo." << endl;
        return;
    }



    if(a==0){
        cout<<"Ingrese el peso del enlace: ";
        cin>>aux;
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==nombre){
                it->second.modificar_enlace(b,aux);
            }
        }
    }
    else if (a==1) {
        cout<<"Ingrese el peso del enlace: ";
        cin>>aux;
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==nombre){
                it->second.agregar_enlace(b,aux);
            }
        }
    }
    else{
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==nombre){
                it->second.eliminar_enlace(b);
            }
        }
    }

    if(a==0){
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==b){
                it->second.modificar_enlace(nombre,aux);
            }
        }
    }
    else if (a==1) {
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==b){
                it->second.agregar_enlace(nombre,aux);
            }
        }
    }
    else{
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==b){
                it->second.eliminar_enlace(nombre);
            }
        }
    }
    cout << "Operacion realizada exitosamente." << endl;
}

void red::print()
{
    if (enrutadores.empty()) {
        cout << "La red esta vacia." << endl;
        return;
    }

    vector<char> nombres_routers;
    map<char,enrutador>::iterator it;

    for(it = enrutadores.begin(); it != enrutadores.end(); it++){
        nombres_routers.push_back(it->first);
    }

    cout << "\nTabla de Costos de Enrutamiento (inf = sin conexion directa):\n" << endl;

    cout << "\t|";
    for(char nombre : nombres_routers) {
        cout << "\t" << nombre;
    }
    cout << "\t|" << endl;

    cout << "--------|";
    for(size_t i = 0; i < nombres_routers.size() + 1 ; i++) {
        cout << "--------";
    }
    cout << "|" << endl;

    for(char nombre_fila : nombres_routers) {
        cout << nombre_fila << "\t|";

        enrutador& router_fila = enrutadores.at(nombre_fila);
        const map<char, int>& conexiones = router_fila.getConexiones();

        for(char nombre_col : nombres_routers) {

            auto it_enlace = conexiones.find(nombre_col);

            if (it_enlace == conexiones.end()) {
                cout << "\t" << "-";
            } else {
                cout << "\t" << it_enlace->second;
            }
        }
        cout << "\t|" << endl;
    }
    cout << endl;
}

void red::guardar_red(string filename)
{
    fstream ofs(filename, ios::out | ios::trunc);
    if (!ofs.good()) {
        cout << "\nError abriendo archivo " << filename << "\n";
        return;
    }

    set<pair<char, char>> enlacesGuardados;
    map<char, enrutador>::iterator it;

    for (it = enrutadores.begin(); it != enrutadores.end(); it++) {
        char enrutadorOrigen = it->first;
        const map<char, int>& conexiones = it->second.getConexiones();
        map<char, int>::const_iterator itCon;

        for (itCon = conexiones.begin(); itCon != conexiones.end(); itCon++) {
            char enrutadorDestino = itCon->first;
            int peso = itCon->second;

            if (peso == 0) continue;

            if (enlacesGuardados.find({enrutadorDestino, enrutadorOrigen}) == enlacesGuardados.end()) {
                ofs << enrutadorOrigen << " " << enrutadorDestino << " " << peso << "\n";
                enlacesGuardados.insert({enrutadorOrigen, enrutadorDestino});
            }
        }
    }
    ofs.close();
    cout << "\nLa red ha sido guardada en el archivo " << filename << "\n";
}

void red::leer_red(string filename)
{
    fstream ifs(filename, ifstream::in);
    if (!ifs.good()) {
        cout << "\nError abriendo archivo " << filename << "\n";
        return;
    }

    cout << "\nCargando red del archivo " << filename << ":\n";
    string linea;
    while (getline(ifs, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        char rout1, rout2;
        int peso;

        if (ss >> rout1 >> rout2 >> peso) {
            agregar_enrutador(rout1);
            agregar_enrutador(rout2);
            agregar_enrutador_archivo(rout1, rout2, peso);
        }
    }
    ifs.close();
}

void red::agregar_enrutador_archivo(char nombre, char nombre2, int peso)
{
    map<char,enrutador>::iterator it;
    for(it=enrutadores.begin();it!=enrutadores.end();it++){
        if(it->first==nombre){
            it->second.agregar_enlace(nombre2,peso);
        }
    }
    for(it=enrutadores.begin();it!=enrutadores.end();it++){
        if(it->first==nombre2){
            it->second.agregar_enlace(nombre,peso);
        }
    }
}

void red::caminocorto(char in, char out)
{
    map<char,enrutador>::iterator it;
    map<char,vector<int>>::iterator ite;
    map<char,vector<int>> distancias;
    vector<char> visitados;
    vector<char> nodosexistentes;
    vector<int> vec;
    int numiter = 0;
    int j = 1;
    int Minimo = 0;
    char letra = ' ';

    vec.push_back(0);
    vector <char> camino;
    camino.push_back(in);

    for(it=enrutadores.begin();it!=enrutadores.end();it++){
        nodosexistentes.push_back(it->first);
        distancias.insert(pair<char,vector<int>>(it->first,vec));
        numiter=numiter+1;
    }

    if(enrutadores.find(in)==enrutadores.end() || enrutadores.find(out)==enrutadores.end()){
        cout << "Nodo de inicio o fin no existe en la red." << endl;
        return;
    }

    for(it=enrutadores.begin();it!=enrutadores.end();it++){
        if(it->first==in){
            visitados.push_back(in);
            for(int i=0;i<nodosexistentes.size();i++){
                int costo = it->second.existeconexion(nodosexistentes[i],visitados,Minimo);
                distancias[nodosexistentes[i]].push_back(costo);
            }

            int min = numeric_limits<int>::max();
            for(ite=distancias.begin();ite!=distancias.end();ite++){
                if((ite->second[j]>0)&&(ite->second[j]<min)){
                    letra=ite->first;
                    min=ite->second[j];
                }
            }
            Minimo=min;
            j++;
        }
    }

    int c=numiter;
    while(c-1>1){
        for(it=enrutadores.begin();it!=enrutadores.end();it++){
            if(it->first==letra){
                visitados.push_back(letra);
                for(int i=0;i<nodosexistentes.size();i++){
                    int costo = it->second.existeconexion(nodosexistentes[i],visitados,Minimo);
                    distancias[nodosexistentes[i]].push_back(costo);
                }

                int min=numeric_limits<int>::max();
                int aux1=numiter-j;
                int aux2=numiter-aux1;

                for(ite=distancias.begin();ite!=distancias.end();ite++){
                    if((ite->second[aux2]>0)&&(ite->second[aux2]<min)){
                        letra=ite->first;
                        min=ite->second[aux2];
                    }
                }
                for(ite=distancias.begin();ite!=distancias.end();ite++){
                    if(ite->first==letra){
                        for(int n=0;n<ite->second.size();n++){
                            if(ite->second[n]<min && ite->second[n]!=0){
                                min=ite->second[n];
                            }
                        }
                    }
                }
                Minimo=min;
                j++;
            }
        }
        c--;
    }

    int caminoCorto=numeric_limits<int>::max(),aux = -1;
    for(ite=distancias.begin();ite!=distancias.end();ite++){
        if(ite->first==out){
            for(int n=0;n<ite->second.size();n++){
                if(ite->second[n]<caminoCorto && ite->second[n]!=0){
                    caminoCorto=ite->second[n];
                    aux=n;
                }
            }
        }
    }

    if (caminoCorto == numeric_limits<int>::max()) {
        cout << "No se encontro ruta entre " << in << " y " << out << endl;
        return;
    }

    for(int i=0;i<aux;i++){
        if (i < visitados.size()) {
            camino.push_back((visitados[i]));
        }
    }
    camino.push_back(out);
    cout<<"El camino mas corto entre "<<in<<" y "<<out<<" es: "<<caminoCorto<<endl;
    cout<<"Ruta: \n";
    for(int i=0;i<camino.size();i++){
        if(camino[i]==out){
            cout<<camino[i]<<" ";
            break;
        }
        else{
            if(i == 0 || camino[i]!=camino[i-1]) cout<<camino[i]<<" ";
        }
    }
    cout << endl;
}
