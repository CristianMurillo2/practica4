#include "enrutador.h"
#include <iostream>
#include <fstream>
#include <string.h>

void enrutador::modificar_enlace(char _conexion, int _peso)
{
    if(map1.find(_conexion)!=map1.end()) map1[_conexion]=_peso;
    else{
        cout<<"Esta conexión no existe."<<endl;
    }
}

void enrutador::agregar_enlace(char _conexion, int _peso)
{
    if(map1.find(_conexion)==map1.end()) map1.insert(pair<char,int>(_conexion,_peso));
}

void enrutador::eliminar_enlace(char _conexion)
{
    if(map1.find(_conexion)!=map1.end()) map1.erase(_conexion);
}

bool enrutador::eliminar_enlace_A(char _conexion)
{
    bool l=false;
    if((map1.find(_conexion)!=map1.end()) && (map1.size()>2)){
        l=true;
        map1.erase(_conexion);
    }
    return l;
}

void enrutador::mostrar_enlaces(int aux)
{
    map<char,int>::iterator it1;
        for(it1=map1.begin();it1!=map1.end();it1++){
            if(aux==0){
            cout << it1->first <<" "<< it1->second << endl;
            }
            else{
                cout << it1->first <<" ";
                for(int i=0;i<aux;i++){
                    cout<<"   ";
                }
                cout<< it1->second<<endl;
            }
        }
}

void enrutador::guardar_enlaces(char clave,string filename)
{
    fstream ofs(filename,ios::app);
    ifstream fin;
    char rout1,rout2;
    int peso;
    bool band;
    map<char,int>::iterator it;
    for(it=map1.begin();it!=map1.end();it++){
        if(it->second!=0){
            band=true;
            fin.open(filename);
            while (!fin.eof()) {
                fin>>rout1>>rout2>>peso;
                if((rout1==it->first)&&(rout2==clave)&&(peso==it->second)){
                    band=false;
                }
            }
            fin.close();
            if(band==true){
                ofs<<clave<<" "<<it->first<<" "<<it->second<<"\n";
            }
        }
    }
    ofs.close();
}

int enrutador::existeconexion(char nodo, vector<char> c, int _Minimo)
{
    if(map1.find(nodo)!=map1.end()){
        for(int k=0;k<c.size();k++){
            if(c[k]==nodo){
                return 101;
            }
            else if(map1[nodo]==0){
                return 101;
            }
        }
        return map1[nodo]+_Minimo;
    }
    else{
        return 101;
    }
}
