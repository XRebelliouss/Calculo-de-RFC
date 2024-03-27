#include <iostream>
#include <string>
#include <cctype> // Para toupper()

using namespace std;

class RFCGenerator {
private:
    string apellidoPaterno;
    string apellidoMaterno;
    string primerNombre;
    int day;
    int month;
    int year;

public:
    void capturarDatos() {
        cout << "Ingrese su apellido paterno: ";
        cin >> apellidoPaterno;
        
        cout << "Ingrese su apellido materno: ";
        cin >> apellidoMaterno;

        cout << "Ingrese su nombre: ";
        cin.ignore(); // Limpiar el buffer antes de getline
        getline(cin, primerNombre);

        cout << "Ingrese su fecha de nacimiento (DD MM AAAA): ";
        cin >> day >> month >> year;
    }

    string generarRFC() {
        string rfc;

        // Convertir el apellido paterno a mayúsculas
        for (char &c : apellidoPaterno) {
            c = toupper(c);
        }

        // Primeros 2 caracteres: primera letra del apellido paterno y primera vocal interna
        rfc += toupper(apellidoPaterno[0]);
        for (int i = 1; i < apellidoPaterno.length(); ++i) {
            if (apellidoPaterno[i] == 'A' || apellidoPaterno[i] == 'E' || apellidoPaterno[i] == 'I' ||
                apellidoPaterno[i] == 'O' || apellidoPaterno[i] == 'U') {
                rfc += toupper(apellidoPaterno[i]);
                break;
            }
        }

        // Tercera posición: inicial del apellido materno o X si no tiene
        rfc += (apellidoMaterno != "X") ? toupper(apellidoMaterno[0]) : 'X';

        // Cuarta posición: inicial del primer nombre o X si es inconveniente
        rfc += (primerNombre == "X") ? 'X' : toupper(primerNombre[0]);

        // Quinta y sexta posición: dos últimos dígitos del año de nacimiento
        string yearStr = to_string(year % 100);
        if (yearStr.length() == 1) {
            yearStr = '0' + yearStr; // Agregar cero adelante si es necesario
        }
        rfc += yearStr;

        // Séptima y octava posición: mes de nacimiento
        rfc += (month < 10) ? '0' + to_string(month) : to_string(month);

        // Novena y décima posición: día de nacimiento
        rfc += (day < 10) ? '0' + to_string(day) : to_string(day);

        return rfc;
    }
};

int main() {
    RFCGenerator generador;
    char opcion;

    do {
        generador.capturarDatos();
        string rfc = generador.generarRFC();
        cout << "RFC sin homoclave: " << rfc << endl;

        cout << "¿Desea generar otro RFC sin homoclave? (S/N): ";
        cin >> opcion;
    } while (toupper(opcion) == 'S');

    return 0;
}
