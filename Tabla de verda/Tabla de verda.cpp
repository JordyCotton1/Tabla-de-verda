#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>

using namespace std;

vector<vector<bool>> generarTablaVariables(const vector<char>& variables) {
    vector<vector<bool>> tablaVariables;
    for (char variable : variables) {
        tablaVariables.push_back({ true, false });
    }
    return tablaVariables;
}

vector<vector<bool>> generarCombinaciones(const vector<char>& variables) {
    vector<vector<bool>> combinaciones;
    int numCombinaciones = pow(2, variables.size());

    for (int i = 0; i < numCombinaciones; ++i) {
        vector<bool> combinacion;
        for (int j = variables.size() - 1; j >= 0; --j) {
            combinacion.push_back((i >> j) & 1);
        }
        combinaciones.push_back(combinacion);
    }

    return combinaciones;
}

bool evaluarExpresion(const string& expresion, const unordered_map<char, bool>& valores) {
    vector<bool> stack;

    for (char token : expresion) {
        if (isalpha(token)) {
            stack.push_back(valores.at(token));
        }
        else if (token == '!') {
            bool val = stack.back();
            stack.pop_back();
            stack.push_back(!val);
        }
        else if (token == '&') {
            bool val2 = stack.back();
            stack.pop_back();
            bool val1 = stack.back();
            stack.pop_back();
            stack.push_back(val1 && val2);
        }
        else if (token == '|') {
            bool val2 = stack.back();
            stack.pop_back();
            bool val1 = stack.back();
            stack.pop_back();
            stack.push_back(val1 || val2);
        }
        else if (token == '>') {
            bool val2 = stack.back();
            stack.pop_back();
            bool val1 = stack.back();
            stack.pop_back();
            stack.push_back(!val1 || val2);
        }
        else if (token == '=') {
            bool val2 = stack.back();
            stack.pop_back();
            bool val1 = stack.back();
            stack.pop_back();
            stack.push_back((!val1 || val2) && (!val2 || val1));
        }
    }

    return stack.back();
}

int main() {
    while (true) {
        string letras;
        cout << "Ingrese las letras a utilizar separadas por comas (para terminar el programa escriba 'salir'): ";
        getline(cin, letras);
        system("cls");

        if (letras == "salir") {
            break;
        }

        vector<char> variables;
        size_t pos = 0;
        while ((pos = letras.find(",")) != string::npos) {
            variables.push_back(letras.substr(0, pos)[0]);
            letras.erase(0, pos + 1);
        }
        variables.push_back(letras[0]);

        string expresion;
        cout << "Ingrese la expresion logica utilizando las letras ingresadas y los siguientes conectores: ! (negacion), & (conjuncion), | (disyuncion), > (implicacion), = (bicondicional): ";
        getline(cin, expresion);
        system("cls");

        vector<vector<bool>> tablaVariables = generarTablaVariables(variables);
        vector<vector<bool>> combinaciones = generarCombinaciones(variables);

        cout << "Tabla de verdad:\n";

        for (char letra : variables) {
            cout << letra << "\t";
        }
        cout << expresion << endl;

        for (const vector<bool>& combinacion : combinaciones) {
            unordered_map<char, bool> valores;
            for (size_t i = 0; i < variables.size(); ++i) {
                valores[variables[i]] = combinacion[i];
            }

            for (bool val : combinacion) {
                cout << val << "\t";
            }
            bool resultado = evaluarExpresion(expresion, valores);
            cout << resultado << endl;
        }

        cout << endl;
    }

    return 0;
}