#include <iostream>
#include <string>

using namespace std;

class CuentaBancaria {
private:
    string titular;
    double saldo;
    bool activa;
    int intentosFallidos;
    int mesesInactivo;

public:
    // Constructor
    CuentaBancaria(string nombre, double saldoInicial) {
        titular = nombre;
        saldo = saldoInicial;
        activa = true;
        intentosFallidos = 0;
        mesesInactivo = 0;
    }

    // Metodo para depositar dinero
    void depositar(double monto) {
        if (!activa) {
            cout << "No se pueden hacer depositos. La cuenta esta bloqueada." << endl;
            return;
        }
        if (monto <= 0) {
            cout << "El monto debe ser positivo." << endl;
            return;
        }
        saldo += monto;
        cout << "Deposito exitoso. Nuevo saldo: " << saldo << endl;
    }

    // Metodo para retirar dinero
    void retirar(double monto) {
        if (!activa) {
            cout << "No se pueden hacer retiros. La cuenta esta bloqueada." << endl;
            return;
        }
        if (monto <= 0) {
            cout << "El monto debe ser positivo." << endl;
            return;
        }
        if (monto > saldo) {
            intentosFallidos++;
            cout << "Saldo insuficiente. Intento fallido #" << intentosFallidos << endl;
            if (intentosFallidos >= 3) {
                activa = false;
                cout << "La cuenta ha sido bloqueada por intentos fallidos." << endl;
            }
            return;
        }
        saldo -= monto;
        cout << "Retiro exitoso. Nuevo saldo: " << saldo << endl;
        if (saldo < 100) {
            cout << "Advertencia: El saldo es menor a 100." << endl;
        }
    }

    // Metodo para consultar saldo
    void consultarSaldo() {
        cout << "Titular: " << titular << endl;
        cout << "Saldo: " << saldo << endl;
        cout << "Estado: " << (activa ? "Activa" : "Bloqueada") << endl;
    }
};

int main() {
    string nombre;
    double saldoInicial;

    cout << "Ingrese el nombre del titular: ";
    getline(cin, nombre);
    cout << "Ingrese el saldo inicial: ";
    cin >> saldoInicial;

    CuentaBancaria cuenta(nombre, saldoInicial);

    int opcion;
    double monto;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Depositar\n";
        cout << "2. Retirar\n";
        cout << "3. Consultar Saldo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese monto a depositar: ";
            cin >> monto;
            cuenta.depositar(monto);
            break;
        case 2:
            cout << "Ingrese monto a retirar: ";
            cin >> monto;
            cuenta.retirar(monto);
            break;
        case 3:
            cuenta.consultarSaldo();
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}
