#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

// Variables globales
set<string> soluciones;
vector<int> vars(26);
int numPrints = 0;

void obtener_soluciones(vector<string> hilo1, vector<string> hilo2) {
	vector<int> s(hilo1.size() + hilo2.size() + 1);
	int nivel = 1;

	// Contadores de instrucciones
	int cont1 = 0;
	int cont2 = 0;
	int nPrintsActuales = 0;

	// Salida generada
	string salidaConsola = "";

	// Vector con el valor anterior de cada variable en la asignación de cada nivel
	vector<int> vant(s.size());

	do {
		// Generar
		if (cont1 < hilo1.size() && s[nivel] == 0) {
            s[nivel] = 1;

            // Se actualizan los datos y la salida
            // Si la instruccion a ejecutar es un print se saca por consola
            if (hilo1[cont1].substr(0, 5) == "print") {
                nPrintsActuales++;
                salidaConsola.append(to_string(vars[hilo1[cont1][6] - 'a']));
            } else {
            	// Se guarda el valor de ese nivel por si hubiera que deshacer la asignación
                vant[nivel] = vars[hilo1[cont1][0] - 'a'];
                vars[hilo1[cont1][0] - 'a'] = hilo1[cont1][4] - '0';
            }
            cont1++;
        } else {
		    // Si la instrucción ejecutada antes es del otro hilo hay que deshacerla
			if (s[nivel] == 1) {
				cont1--;
				// Deshacer la ultima instruccion del hilo1
				if (hilo1[cont1].substr(0, 5) == "print") {
					nPrintsActuales--;
					salidaConsola = salidaConsola.substr(0, salidaConsola.size() - 1);
				} else {
					vars[hilo1[cont1][0] - 'a'] = vant[nivel];
				}
			}
			
			s[nivel] = 2;

            // Se actualizan los datos y la salida
            // Si la instruccion a ejecutar es un print se saca por consola
            if (hilo2[cont2].substr(0,5) == "print") {
                nPrintsActuales++;
                salidaConsola.append(to_string(vars[hilo2[cont2][6] - 'a']));
            } else {
            	// Se guarda el valor de ese nivel por si hubiera que deshacer la asignación
                vant[nivel] = vars[hilo2[cont2][0] - 'a'];
                vars[hilo2[cont2][0] - 'a'] = hilo2[cont2][4] - '0';
            }
            cont2++;
		}
		
        // Si solución entonces
		if (nPrintsActuales == numPrints) {
			// Almacenar
			//cout << salidaConsola << endl;
			soluciones.insert(salidaConsola);
		}
		// Si Criterio profundizar
		if (nPrintsActuales < numPrints && nivel < (hilo1.size() + hilo2.size())) {
			nivel++;
		} else
			while(nivel > 0 && !(s[nivel] < 2 && cont2 < hilo2.size())) {
			    // Deshacer la última instrucción
			    if (s[nivel] == 1) {
			    	cont1--;
					if (hilo1[cont1].substr(0, 5) == "print") {
						nPrintsActuales--;
						salidaConsola = salidaConsola.substr(0, salidaConsola.size() - 1);
					} else {
						vars[hilo1[cont1][0] - 'a'] = vant[nivel];
					}
			    } else {
			    	cont2--;
			    	if (hilo2[cont2].substr(0, 5) == "print") {
						nPrintsActuales--;
						salidaConsola = salidaConsola.substr(0, salidaConsola.size() - 1);
					} else {
						vars[hilo2[cont2][0] - 'a'] = vant[nivel];
					}
			    }

			    s[nivel] = 0;
			    nivel--;
			}
	} while (nivel > 0);


}

int main(int argc, char const *argv[]) {
	int reps;
	vector<string> hilo1;
	vector<string> hilo2;
	
	cin >> reps;
	cin.ignore();

	for (int veces = 0; veces < reps; veces++) {
		for (int i = 0; i < 26; ++i)	// todos los valores de 'vars' a 0
			vars[i] = 0;

		string line;

		getline(cin, line);
		while (line != "#") {
			if ("print" == line.substr(0,5)) 
				numPrints++;
			hilo1.push_back(line);
			getline(cin, line);
			
		}

		/*cout << "hilo1:" << endl;
		cout << hilo1.size() << endl;
		for (vector<string>::iterator it=hilo1.begin(); it!=hilo1.end(); ++it)
			cout << *it << endl;*/

		getline(cin, line);
		while (line != "#") {
			if ("print" == line.substr(0,5)) 
				numPrints++;
			hilo2.push_back(line);
			getline(cin, line);
		}

		obtener_soluciones(hilo1, hilo2);

		string sol;

		getline(cin, sol);
		while (sol != "#") {
			if (soluciones.find(sol) == soluciones.end())
				cout << "NO" << endl;
			else
				cout << "YES" << endl;
			getline(cin, sol);
		}

		hilo1.clear();
		hilo2.clear();
		soluciones.clear();
		numPrints = 0;

		if (veces < reps - 1) {
			// Espacio en blanco
			cout << endl;
		}
	}

}

// dentro de un hilo todo se ejecuta secuencialmente
// la longitud de las soluciones validas = num 'prints'
