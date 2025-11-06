#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <vector>

class red
{
public:
    void agregar_enrutador(char nombre);
    void eliminar_enrutador(char nombre);
    void modificar_enrutador_A(char nombre,int nodos,int exec);
    void eliminar_A(char nombre,int nodos,float proba,int exec);
    void modificar_enrutador(char nombre);
    void print();
    void guardar_red(string filename);
    void leer_red(string filename);
    void agregar_enrutador_archivo(char nombre,char nombre2,int peso);
    void caminocorto(char in,char out);

private:
    map<char,enrutador> enrutadores;
};

#endif
