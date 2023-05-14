#include <iostream>
#include <vector>
#include <sstream> //ChatGPT - manipular cadenas de caracteres
#include <iomanip>

using namespace std;

struct tPolinomio {			
    int grado;                /* Grado del polinomio */
    vector<double> coef;      /* Coeficientes */
};

void leerPolinomios(vector<tPolinomio>& polinomios);			//Funcion prototipo
void sumaPolinomios(const vector<tPolinomio>& polinomios);

int main() {													//Funcion principal
    vector<tPolinomio> polinomios;		//Almacena polinomios
    
	leerPolinomios(polinomios);									//Llamada de funcion
    sumaPolinomios(polinomios);

    return 0;
}

void leerPolinomios(vector<tPolinomio>& polinomios) {			//Definicion de funcion
    int n;
    cout<<"Introduzca la cantidad de polinomios a sumar: ";
    cin>>n;
    cin.ignore(); 	//ignora valores pendientes
    cout<<endl;

    for (int i = 0; i < n; ++i) {
        string line; 				//declara la variable line
        cout<<"Polinomio "<<i + 1<<" (ponga 2 veces la tecla enter para saltar al siguiente): ";
        getline(cin, line);
        cin.ignore();
        line += '+';

        int state = 0;				//ChatGPT - seguimiento del estado actual
        double coef = 0; 					//coeficiente
        int grado = 0;
        double sign = 1; 					//signo
        stringstream num; 			//ChatGPT - convertir los valores numericos en la linea de entrada a numeros.
        for (char c : line) {
            if (c == '+' or c == '-') {		//Determina + o -
                if (state == 0) {			//Se encuentra el coeficiente
                    num >> coef;
                    coef *= sign;			//Signo
                    grado = 0;
                } else if (state == 1) {
                    num >> coef;
                    coef *= sign;
                    grado = 1;
                } else if (state == 2) {
                    num >> grado;
                }
                polinomios.push_back(tPolinomio{grado, {coef}});  //ChatGPT - El objeto tPolinomio se crea con el grado y coeficiente 
                num.clear();	//Restablece
                num.str("");	//Limpia

                if (c == '+') { // + o - 
                    sign = 1;
                } else {
                    sign = -1;
                }
                state = 0;
            } else if (c == 'x') {
                if (state == 0) {
                    if (num.str().empty()) {  //coeficiente 1
                        coef = sign;
                    } else {
                        num >> coef;
                        coef *= sign;
                    }
                }
                num.clear();
                num.str("");
                state = 1;
            } else if (c == '*') {
                continue;
            } else if (isdigit(c) or c == '.') {   //ChatGPT - digito o punto decimal
                num << c;
                if (state == 2) {
                    num >> grado;
                    num.clear();
                    num.str("");
                    state = 0;
                } else if (state == 1) {
                    state = 2;
                }
            }
        }
    }
}

void sumaPolinomios(const vector<tPolinomio>& polinomios) {
    int maxGrado = 0;
    for (const auto& polinomio : polinomios) {
        if (polinomio.grado > maxGrado) {
            maxGrado = polinomio.grado;		//Actualiza
        }
    }

    vector<double> suma(maxGrado + 1, 0.0);  //coeficientes de la suma
    for (const auto& polinomio : polinomios) {
        if (polinomio.grado <= maxGrado) {
            suma[polinomio.grado] += polinomio.coef[0];
        }
    }

    cout << fixed << setprecision(1);	//Con un decimal
    cout<<endl<<"El polinomio suma es de grado "<<maxGrado<<":"<<endl;

	bool firstTerm = true;						//ChatGPT - Impimir +
	for (int i = maxGrado; i >= 0; --i) {
	    if (suma[i] != 0) {
	        if (!firstTerm) {
	            cout<<" + ";
	        }
	        if (i == 0) {
	            cout<<suma[i];
	        } else {
	            cout<<suma[i]<<"*x"<<i;
	        }
	        firstTerm = false;
	    }
	}
	cout << endl;
}