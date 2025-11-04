#include <iostream>
#include "red.h"
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

using namespace std;

int main()
{
    red rd;
    int opc,nodos;
    float proba;
    char aux, ini, fin;
    string filename;
    srand(time(NULL));
    while(true){
        cout << endl << "---Bienvenido al sistema de enrutadores---" << endl << endl;
        cout << "1. Agregar enrutador." << endl;
        cout << "2. Eliminar enrutador." << endl;
        cout << "3. Modificar enrutador." << endl;
        cout << "4. Mostrar tabla de enrutamiento." << endl;
        cout << "5. Guardar red en archivo." << endl;
        cout << "6. Cargar red desde archivo." << endl;
        cout << "7. Mostrar ruta mas eficiente." << endl;
        cout << "8. Generar red aleatoria." << endl;
        cout << "9. Salir." << endl;
        cout << "Seleccione la opcion que desea: ";

        while(!(cin >> opc) || opc < 1 || opc > 9){
            cout << "Ingresa una opcion valida: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(opc==9) break;
        else{
            switch (opc) {
            case 1: {
                string input;
                while (true)
                {
                    cout << "Ingrese el nombre del enrutador que desea agregar (Un solo caracter): ";
                    getline(cin, input);

                    if (input.length() == 1)
                    {
                        aux = input[0];
                        break;
                    }
                    cout << "Debes ingresar EXACTAMENTE un caracter. Intentalo de nuevo." << endl;
                }
                rd.agregar_enrutador(aux);
                break;
            }
            case 2: {
                string input;
                while (true)
                {
                    cout<<"Ingrese el nombre del enrutador que desea eliminar(Un solo caracter): ";
                    getline(cin, input);

                    if (input.length() == 1)
                    {
                        aux = input[0];
                        break;
                    }
                    cout << "Debes ingresar EXACTAMENTE un caracter. Intentalo de nuevo." << endl;
                }
                rd.eliminar_enrutador(aux);
                break;
            }
            case 3: {
                string input;
                while (true)
                {
                    cout << "Ingrese el nombre del enrutador que desea modificar (Un solo caracter): ";
                    getline(cin, input);

                    if (input.length() == 1)
                    {
                        aux = input[0];
                        break;
                    }
                    cout << "Debes ingresar EXACTAMENTE un caracter. Intentalo de nuevo." << endl;
                }
                rd.modificar_enrutador(aux);
                break;
            }
            case 4:
                rd.print();
                break;

            case 5:
                rd.guardar_red("RED.txt");
                break;

            case 6:
                cout<<"Ingrese el nombre del archivo: ";
                getline(cin, filename);
                rd.leer_red(filename);
                break;

            case 7:
                cout<<"Ingrese nodo de inicio: ";
                cin>>ini;
                cout<<"Ingrese nodo del final: ";
                cin>>fin;
                rd.caminocorto(ini,fin);
                break;

            case 8:
                cout<<"Ingrese el numero de enrutadores entre 2 y 26: ";
                while(!(cin >> nodos) || nodos < 2 || nodos > 26){
                    cout << "Ingresa una opcion valida (2 - 26): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout<<"Ingrese valor de probabilidad entre 0 y 1: ";
                while(!(cin >> proba) || proba < 0 || proba > 1){
                    cout << "Ingresa una opcion valida (0 - 1): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                int exc=0;
                for(int i=0;i<nodos;i++){
                    rd.agregar_enrutador(char('A'+i));
                }
                for(int i=0;i<nodos;i++){
                    rd.modificar_enrutador_A(char('A'+i),nodos,exc);
                    exc++;
                }
                exc=0;
                for(int i=0;i<nodos;i++){
                    rd.eliminar_A(char('A'+i),nodos,proba,exc);
                    exc++;
                }
                break;
            }
        }
    }
    cout<< endl << "Saliste del programa." << endl;
    cout << "Presiona Enter para continuar...";
    cin.get();
    return 0;
}
