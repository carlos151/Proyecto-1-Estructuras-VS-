#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "listaSimple.h"
#include "Listadoble_Super.h"
#include "Listadoblecircular_Inventario.h"
#include "Listadoblecircular_Usr.h"

using namespace std;

class estructuraListas {
public:
	estructuraListas() {}
	lista listaCiudades;
	listaD listaSuper;
	listaDC listaInventario;
	listaDC_usrAux listaUsuarios;
};

//metodos de las estructuras de datos
void insertarCiudad(lista &pLista, string datos) {
	string codigo, ciudad;
	bool bandera = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera) {
				codigo.operator+=(datos[i]);
			}
			else {
				ciudad.operator+=(datos[i]);
			}
		}
		else {
			bandera = true;
		}
	}
	if (!pLista.buscar(codigo)) {
		pLista.InsertarFinal(codigo, ciudad);
	}
}

void insertarSuper(estructuraListas &listas, string datos) {
	string codigo, codCiudad, nombre;
	bool bandera1 = false;
	bool bandera2 = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera1) {
				codCiudad.operator+=(datos[i]);
			}
			else if (!bandera2) {
				codigo.operator+=(datos[i]);
			}
			else {
				nombre.operator+=(datos[i]);
			}
		}
		else if (!bandera1) {
			bandera1 = true;
		}
		else {
			bandera2 = true;
		}
	}
	if (listas.listaCiudades.buscar(codCiudad) && !(listas.listaSuper.buscarSuper(codigo))) {
		listas.listaSuper.InsertarFinal(codCiudad, codigo, nombre);
	}
}

void insertarProducto(estructuraListas &listas, string datos) {
	string codSuper, codigo, nombre, cantidad, precio;
	bool bandera1 = false;
	bool bandera2 = false;
	bool bandera3 = false;
	bool bandera4 = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera1) {
				codSuper.operator+=(datos[i]);
			}
			else if (!bandera2) {
				codigo.operator+=(datos[i]);
			}
			else if (!bandera3) {
				nombre.operator+=(datos[i]);
			}
			else if (!bandera4) {
				cantidad.operator+=(datos[i]);
			}
			else {
				precio.operator+=(datos[i]);
			}
		}
		else if (!bandera1) {
			bandera1 = true;
		}
		else if (!bandera2) {
			bandera2 = true;
		}
		else if (!bandera3) {
			bandera3 = true;
		}
		else {
			bandera4 = true;
		}
	}
	if (listas.listaSuper.buscarSuper(codSuper) && listas.listaInventario.ListaVacia()) {
		listas.listaInventario.InsertarFinal(codSuper, codigo, nombre, cantidad, precio);
	}
	else if (listas.listaSuper.buscarSuper(codSuper) && !listas.listaInventario.buscarProducto(codigo)) {
		listas.listaInventario.InsertarFinal(codSuper, codigo, nombre, cantidad, precio);
	}
}

void insertarUsuario(estructuraListas &listas, string datos) {
	string codCiudad, cedula, nombre, telefono, tipo;
	bool bandera1 = false;
	bool bandera2 = false;
	bool bandera3 = false;
	bool bandera4 = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera1) {
				codCiudad.operator+=(datos[i]);
			}
			else if (!bandera2) {
				cedula.operator+=(datos[i]);
			}
			else if (!bandera3) {
				nombre.operator+=(datos[i]);
			}
			else if (!bandera4) {
				telefono.operator+=(datos[i]);
			}
			else {
				tipo.operator+=(datos[i]);
			}
		}
		else if (!bandera1) {
			bandera1 = true;
		}
		else if (!bandera2) {
			bandera2 = true;
		}
		else if (!bandera3) {
			bandera3 = true;
		}
		else {
			bandera4 = true;
		}
	}

	if (listas.listaCiudades.buscar(codCiudad) && listas.listaUsuarios.listaVacia(stoi(tipo)) && !listas.listaUsuarios.buscarUsuario(cedula)) {
		listas.listaUsuarios.InsertarUsuario(codCiudad, cedula, nombre, telefono, tipo, stoi(tipo));
	}
	else if (listas.listaCiudades.buscar(codCiudad) && !listas.listaUsuarios.buscarUsuario(cedula)) {
		listas.listaUsuarios.InsertarUsuario(codCiudad, cedula, nombre, telefono, tipo, stoi(tipo));
	}
}

void leerArchivo(estructuraListas &listas, string file_name, int tipo) {
	string STRING;
	ifstream infile;
	infile.open(file_name);
	while (!infile.eof()) {
		getline(infile, STRING);
		switch (tipo) {
		case 0:
			insertarCiudad(listas.listaCiudades, STRING);
			break;
		case 1:
			insertarUsuario(listas, STRING);
			break;
		case 2:
			insertarSuper(listas, STRING);
			break;
		case 3:
			insertarProducto(listas, STRING);
			break;
		}
	}
	infile.close();
}

void cargarArchivos(estructuraListas &listas) {
	leerArchivo(listas, "archivos/Ciudad.txt", 0);
	leerArchivo(listas, "archivos/Usuarios.txt", 1);
	leerArchivo(listas, "archivos/supermercado.txt", 2);
	leerArchivo(listas, "archivos/Inventario.txt", 3);
}

//metodos del menú
void reportesAdministrador() {
	cout << "1.Últimos dos productos ingresados al inventario.(Indicar código del super)" << endl;
	cout << "2.Último producto modificado" << endl;
	cout << "3.Último producto eliminado" << endl;
	cout << "4.Producto más vendido" << endl;
	cout << "5.Producto menos vendido" << endl;
	cout << "6.Cliente que más compró" << endl;
	cout << "7.Cliente que menos compró" << endl;
	cout << "8.Cantidad de compras por cliente" << endl;
	cout << "9.Super más visitado" << endl;
	cout << "10.Super menos visitado" << endl;
	cout << "11.Administrador que más trabajó" << endl;
	cout << "12.Administrador que menos trabajó" << endl;
}

void insertarProductoEnInventario(estructuraListas &listas, string codigo) { //incompleta
	if (!listas.listaInventario.buscarProducto(codigo)) {
		string codSuper, nombre, cantidad, precio;
		while (!listas.listaSuper.buscarSuper(codSuper)) {
			cout << "Código del super: ";
			cin >> codSuper;
			if (!listas.listaSuper.buscarSuper(codSuper)) {
				cout << "Ese super no existe" << endl;
			}
		}
		cout << "Nombre del producto: ";
		cin >> nombre;
		cout << "Cantidad:";
		cin >> cantidad;
		cout << "Precio";
		cin >> precio;
		listas.listaInventario.InsertarFinal(codSuper, codigo, nombre, cantidad, precio);
	}
	else {
		cout << "El producto ya existe" << endl;
	}
}

void eliminarProducto(listaDC &l1, string codigo) {
	if (l1.buscarProducto(codigo)) {

	}
}

void menuAdministrador() {
	cout << "1.Insertar producto" << endl;
	cout << "2.Eliminar producto" << endl;
	cout << "3.Modificar producto" << endl;
	cout << "4.Consultar precio" << endl;
	cout << "5.Consultar descuentos" << endl;
	cout << "6.Consultar productos de un super" << endl;
	cout << "7.Registrar clientes" << endl;
	cout << "8.Reportes" << endl;
}

void menuVendedor() {
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar descuento de un cliente" << endl;
	cout << "3.Consultar producto de un super" << endl;
}

void menuCliente() {
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar descuento" << endl;
	cout << "3.Consultar productos" << endl;
	cout << "4.Comprar(carrito)" << endl;
	cout << "5.Facturación" << endl;
}

void menuFuncionario() {
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar descuento" << endl;
	cout << "3.Consultar productos" << endl;
	cout << "4.Comprar(carrito)" << endl;
	cout << "5.Facturación" << endl;
	cout << "6.Descuento extra de 5%" << endl;
}

bool confirmarLogin(listaDC_usrAux &l1, string cedula, string tipo) {
	return l1.verificarUsuario(cedula, stoi(tipo));
}

void menu(estructuraListas &listas) {
	string cedula, tipo;
	cout << "Cedula: ";
	cin >> cedula;
	cout << "Tipo de usuario: ";
	cin >> tipo;
	cout << endl;
	if (confirmarLogin(listas.listaUsuarios, cedula, tipo)) {
		switch (stoi(tipo)) {
		case 0:
			menuCliente();
			break;
		case 1:
			menuAdministrador();
			break;
		case 2:
			menuVendedor();
			break;
		case 3:
			menuFuncionario();
			break;
		}
	}
	else {
		string respuesta;
		cout << "Usuario no registrado" << endl;
		cout << "Reintentar? (y/n)";
		cin >> respuesta;
		cout << endl;
		if (respuesta == "y") { menu(listas); }
	}

}

int main(int argc, char const *argv[]) {
	cout << "hello world!" << endl;

	//listas
	estructuraListas listas;
	cargarArchivos(listas);
	listas.listaCiudades.Mostrar();
	listas.listaSuper.Mostrar();
	listas.listaInventario.Mostrar();
	listas.listaUsuarios.Mostrar();
	listas.listaUsuarios.Mostrar(0);
	listas.listaUsuarios.Mostrar(1);
	listas.listaUsuarios.Mostrar(2);
	listas.listaUsuarios.Mostrar(3);

	menu(listas);
	cin.get();
	return 0;
}
