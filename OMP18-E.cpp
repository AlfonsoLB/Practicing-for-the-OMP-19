#include <iostream>
#include <string>

using namespace std;

int main() {
	int nCasos;
	string entrada;
	int e = 0;
	int nMesetas = 0;

	cin >> nCasos;
	getline(cin, entrada);

	while (nCasos > 0) {
		getline(cin, entrada);
		for(char& c : entrada) {
    		// Get '/'
    		if (c == '/') {
    			if (e == 0 || e == 1 || e == 2)  {
    				e++;	
    			} else if (e != 3) {
    				e = 1;	
    			}
    		}

    		// Get '_'
    		if (c == '_') {
    			if (e == 3) {
    				e++;
    			} else if (e != 4) {
    				e = 0;
    			}
    		}

    		// Get '\'
    		if (c == '\\') {
    			if (e == 4 || e == 5 || e == 6) {
    				e++;
    			} else {
    				e = 0;
    			}
    		}

    		// Final state, return to the first state.
    		if (e == 7) {
    			nMesetas++;
    			e = 0;
    		}
		}
		
		cout << nMesetas << endl;
		nMesetas = 0;
		e = 0;
		nCasos--;
	}
}