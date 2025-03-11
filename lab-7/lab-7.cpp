#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cuenta {
protected:
    string titular;
    double saldo;
    bool activa;

public:
    Cuenta(string nombre, double saldoInicial) : titular(nombre), saldo(saldoInicial), activa(true) {}
    virtual void depositar(double monto) = 0;
    virtual void retirar(double monto) = 0;
    virtual void consultarSaldo() const = 0;
    virtual ~Cuenta() {}
};

class CuentaBancaria : public Cuenta {
private:
    int intentosFallidos;

public:
    CuentaBancaria(string nombre, double saldoInicial) : Cuenta(nombre, saldoInicial), intentosFallidos(0) {}

    void depositar(double monto) override {
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

    void retirar(double monto) override {
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

    void consultarSaldo() const override {
        cout << "Titular: " << titular << endl;
        cout << "Saldo: " << saldo << endl;
        cout << "Estado: " << (activa ? "Activa" : "Bloqueada") << endl;
    }
};

int main() {
    vector<Cuenta*> cuentas;
    int numCuentas;
    cout << "Ingrese el numero de cuentas (max 30): ";
    cin >> numCuentas;
    if (numCuentas > 30) numCuentas = 30;

    for (int i = 0; i < numCuentas; i++) {
        string nombre;
        double saldoInicial;
        cout << "\nIngrese el nombre del titular de la cuenta " << i + 1 << ": ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese el saldo inicial: ";
        cin >> saldoInicial;
        cuentas.push_back(new CuentaBancaria(nombre, saldoInicial));
    }

    int opcion, cuentaIndex;
    double monto;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Depositar\n";
        cout << "2. Retirar\n";
        cout << "3. Consultar Saldo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion >= 1 && opcion <= 3) {
            cout << "Ingrese el numero de cuenta (1 - " << numCuentas << "): ";
            cin >> cuentaIndex;
            if (cuentaIndex < 1 || cuentaIndex > numCuentas) {
                cout << "Numero de cuenta invalido." << endl;
                continue;
            }
            cuentaIndex--; // Ajuste para índice base 0
        }

        switch (opcion) {
        case 1:
            cout << "Ingrese monto a depositar: ";
            cin >> monto;
            cuentas[cuentaIndex]->depositar(monto);
            break;
        case 2:
            cout << "Ingrese monto a retirar: ";
            cin >> monto;
            cuentas[cuentaIndex]->retirar(monto);
            break;
        case 3:
            cuentas[cuentaIndex]->consultarSaldo();
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    for (Cuenta* cuenta : cuentas) {
        delete cuenta;
    }
    return 0;
}
