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

//generar la estructura de datos
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

//interfaz de consola
void menuAdministrador(estructuraListas &listas);
void menu(estructuraListas &listas);

void reportesAdministrador(estructuraListas &listas) {
	cout << endl;
	cout << "1.Ultimos dos productos ingresados al inventario.(Indicar codigo del super)" << endl;
	cout << "2.Ultimo producto modificado" << endl;
	cout << "3.Ultimo producto eliminado" << endl;
	cout << "4.Producto mas vendido" << endl;
	cout << "5.Producto menos vendido" << endl;
	cout << "6.Cliente que mas compro" << endl;
	cout << "7.Cliente que menos compro" << endl;
	cout << "8.Cantidad de compras por cliente" << endl;
	cout << "9.Super mas visitado" << endl;
	cout << "10.Super menos visitado" << endl;
	cout << "11.Administrador que mas trabajo" << endl;
	cout << "12.Administrador que menos trabajo" << endl;
	cout << "13.Volver" << endl;
	string respuesta,codigo;
	cout << "Que desea hacer: ";
	cin >> respuesta;
	switch (stoi(respuesta)){
		case 1:
			cout << "Codigo de super: ";
			cin >> codigo;
			if (!listas.listaSuper.buscarSuper(codigo)) {
				cout << "Super no encontrado" << endl;
			}
			else {
				listas.listaInventario.ultimosDosAgregados(codigo);
			}
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 2:
			listas.listaInventario.ultimoModificado();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 3:
			listas.listaInventario.ultimoProdBorrado();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 4:
			listas.listaInventario.productoMasVendido();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 5:
			listas.listaInventario.productoMenosVendido();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 6:
			listas.listaUsuarios.masCompras();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 7:
			listas.listaUsuarios.menosCompras();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 8:
			cout << "Cedula: ";
			cin >> codigo;
			if (listas.listaUsuarios.buscarUsuario(codigo)) {
				listas.listaUsuarios.cantCompras(codigo);
			}
			else {
				cout << "Cliente no encontrado" << endl;
			}
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 9:
			listas.listaSuper.masVisitas();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 10:
			listas.listaSuper.menosVisitas();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 11:
			listas.listaUsuarios.adminMasTrabajo();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 12:
			listas.listaUsuarios.adminMenosTrabajo();
			cout << endl;
			reportesAdministrador(listas);
			break;
		case 13:
			cout << endl;
			menuAdministrador(listas);
			break;
		default:
			cout << "Respuesta invalida" << endl;
			break;
	}
}

void insertarProductoEnInventario(estructuraListas &listas, string codigo) { 
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
		cout << "Precio: ";
		cin >> precio;
		listas.listaInventario.InsertarFinal(codSuper, codigo, nombre, cantidad, precio);
	}
	else {
		cout << "El producto ya existe" << endl;
	}
}

void eliminarProducto(estructuraListas &listas, string codigo) {
	if (listas.listaInventario.buscarProducto(codigo)) {
		int posicion = listas.listaInventario.buscarProductoPos(codigo);
		listas.listaInventario.borrarPosicion(posicion);
	}
	else{
		cout << "Producto no encontrado" << endl;
	}
}

void modificarProducto(estructuraListas &listas,string codigo){
	if(listas.listaInventario.buscarProducto(codigo)){
		string respuesta;
		cout << "Que desea modificar?" << endl;
		cout << "1.Codigo de super" << endl;
		cout << "2.Codigo del producto" << endl;
		cout << "3.Nombre" << endl;
		cout << "4.Cantidad" << endl;
		cout << "5.Precio" << endl;
		cout << "Inserte el numero de lo que quiere modificar: ";
		cin >> respuesta;
		if(stoi(respuesta) != 1 && stoi(respuesta) != 2 && stoi(respuesta) != 3 && stoi(respuesta) != 4 && stoi(respuesta) != 5){
			cout << "Respuesta invalida" << endl;
		}
		else{
			string cambio;
			cout << "Cual es el cambio? ";
			cin >> cambio;
			listas.listaInventario.modificar(codigo,cambio,stoi(respuesta));
		}
	}
	else{
		cout << "Producto no encontrado" << endl;
	}
}

void consultarPrecio(estructuraListas &listas,string codigo){
	if(listas.listaInventario.buscarProducto(codigo)){
		cout << listas.listaInventario.consultarPrecio(codigo) << endl;
	}
	else{
		cout << "Producto no encontrado" << endl;
	}
}

void consultarDescuentos(estructuraListas &listas) {
	listas.listaUsuarios.consultarDescuentos();
}

void consultarProductosSuper(estructuraListas &listas,string codSuper){
	if(listas.listaSuper.buscarSuper(codSuper)){
		listas.listaInventario.consultarProductosSuper(codSuper);
	}
	else{
		cout << "Super no encontrado" << endl;
	}
}

void registrarCliente(estructuraListas &listas,string cedula){
	if(!listas.listaUsuarios.buscarUsuario(cedula)){
		string codCiudad,nombre,telefono;
		cout << "Nombre: ";
		cin >> nombre;
		cout << "Codigo de ciudad: ";
		cin >> codCiudad;
		cout << "Telefono: ";
		cin >> telefono;
		listas.listaUsuarios.InsertarUsuario(codCiudad,cedula,nombre,telefono,"0",0);
		cout << "Cliente registrado con exito" << endl;
	}
	else{
		cout << "El usuario ya existe" << endl;
	}
}

void consultarDescuento(estructuraListas &listas, string cedula,int tipo) {
	listas.listaUsuarios.consultarDescuento(cedula, tipo);
}

void comprarProducto(estructuraListas &listas, string cedula) {
	string codSuper,codigo,cantidad;
	cout << "Codigo de super: ";
	cin >> codSuper;
	if (!listas.listaSuper.buscarSuper(codSuper)) {
		cout << "Super no encontrado" << endl;
		cout << endl;
		return;
	}
	else {
		cout << "Codigo del producto: ";
		cin >> codigo;
		if (!listas.listaInventario.buscarProducto(codigo)) {
			cout << "Producto no encontrado" << endl;
			cout << endl;
		}
		else {
			pnodoDC producto = listas.listaInventario.buscarNodoPos(codigo);
			listas.listaSuper.visitarSuper(codSuper);
			producto->compras++;
			if (producto->getSuper() != codSuper) {
				cout << "Ese producto no se encuentra en el super indicado" << endl;
				return;
			}
			cout << "Cantidad: ";
			cin >> cantidad;
			int pCantidad = stoi(producto->getCantidad());
			if (pCantidad == 0) {
				cout << "No quedan" << endl;
				return;
			}
			while (pCantidad < stoi(cantidad)) {
				cout << "Solo hay " << pCantidad << endl;
				cout << "Cuantos quiere: ";
				cin >> cantidad;
			}
			producto->modificarCantidad(stoi(cantidad));
			string nombre = producto->getNombre();
			float precio = stof(producto->getPrecio());
			listas.listaUsuarios.comprar(cedula, nombre,codSuper, pCantidad, precio);
		}
	}
}

void menuAdministrador(estructuraListas &listas) {
	string respuesta;
	cout << "1.Insertar producto" << endl;
	cout << "2.Eliminar producto" << endl;
	cout << "3.Modificar producto" << endl;
	cout << "4.Consultar precio" << endl;
	cout << "5.Consultar descuentos" << endl;
	cout << "6.Consultar productos de un super" << endl;
	cout << "7.Registrar clientes" << endl;
	cout << "8.Reportes" << endl;
	cout << "9.Ver listas" << endl;
	cout << "10.Cerrar sesion" << endl;
	cout << "Que desea hacer: ";
	cin >> respuesta;
	string codigo;
	string codSuper;
	string cedula;
	switch (stoi(respuesta)) {
	case 1:
		cout << "Codigo:";
		cin >> codigo;
		insertarProductoEnInventario(listas, codigo);
		break;
	case 2:
		cout << "Codigo:";
		cin >> codigo;
		eliminarProducto(listas, codigo);
		break;
	case 3:
		cout << "Codigo:";
		cin >> codigo;
		modificarProducto(listas, codigo);
		break;
	case 4:
		cout << "Codigo:";
		cin >> codigo;
		consultarPrecio(listas, codigo);
		break;
	case 5:
		consultarDescuentos(listas);
		break;
	case 6:
		cout << "Codigo de super:";
		cin >> codSuper;
		consultarProductosSuper(listas, codSuper);
		break;
	case 7:
		cout << "Cedula:";
		cin >> cedula;
		registrarCliente(listas, cedula);
		break;
	case 8:
		reportesAdministrador(listas);
		break;
	case 9:
		cout << "Ciudades: ";
		listas.listaCiudades.Mostrar();
		cout << "Super: ";
		listas.listaSuper.Mostrar();
		cout << "Inventario: ";
		listas.listaInventario.Mostrar();
		listas.listaUsuarios.Mostrar(0);
		listas.listaUsuarios.Mostrar(1);
		listas.listaUsuarios.Mostrar(2);
		listas.listaUsuarios.Mostrar(3);
		break;
	case 10:
		cout << endl;
		menu(listas);
		break;
	default:
		cout << "Respuesta incorrecta" << endl;
		break;
	}
	
	cout << endl;
	menuAdministrador(listas);
}

void menuVendedor(estructuraListas &listas) {
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar descuento de un cliente" << endl;
	cout << "3.Consultar productos de un super" << endl;
	cout << "4.Cerrar sesion" << endl;
	string codigo;
	string respuesta;
	string tipo;
	cout << "Que desea hacer: ";
	cin >> respuesta;
	switch (stoi(respuesta)) {
		case 1:
			cout << "Codigo: ";
			cin >> codigo;
			consultarPrecio(listas, codigo);
			break;
		case 2:
			cout << "Cedula: ";
			cin >> codigo;
			cout << "Tipo (0-3): ";
			cin >> tipo;
			if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
			consultarDescuento(listas, codigo, stoi(tipo));
			break;
		case 3:
			cout << "Codigo de ciudad: ";
			cin >> codigo;
			consultarProductosSuper(listas, codigo);
			break;
		case 4:
			cout << endl;
			menu(listas);
			break;
		default:
			cout << "Respuesta invalida" << endl;
			break;
	}
	cout << endl;
	menuVendedor(listas);
}

void menuCliente(estructuraListas &listas) {
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar descuento" << endl;
	cout << "3.Consultar productos" << endl;
	cout << "4.Comprar(carrito)" << endl;
	cout << "5.Ver carrito" << endl;
	cout << "6.Facturacion" << endl;
	cout << "7.Cerrar sesion" << endl;
	string respuesta, codigo;
	cout << "Que desea hacer: ";
	cin >> respuesta;
	switch (stoi(respuesta)) {
		case 1:
			cout << "Codigo: ";
			cin >> codigo;
			consultarPrecio(listas, codigo);
			cout << endl;
			menuCliente(listas);
			break;
		case 2:
			cout << "Cedula: ";
			cin >> codigo;
			if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
			consultarDescuento(listas, codigo, 0);
			cout << endl;
			menuCliente(listas);
			break;
		case 3:
			cout << "Codigo de super: ";
			cin >> codigo;
			consultarProductosSuper(listas, codigo);
			cout << endl;
			menuCliente(listas);
			break;
		case 4:
			cout << "Cedula: ";
			cin >> codigo;
			if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
			comprarProducto(listas, codigo);
			cout << endl;
			menuCliente(listas);
			break;
		case 5:
			cout << "Cedula: ";
			cin >> codigo;
			if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
			listas.listaUsuarios.verCarrito(codigo);
			cout << endl;
			menuCliente(listas);
			break;
		case 6:
			cout << "Cedula: ";
			cin >> codigo;
			if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
			listas.listaUsuarios.facturar(codigo);
			cout << "Factura lista, carrito reiniciado" << endl;
			cout << endl;
			menuCliente(listas);
		case 7:
			cout << endl;
			menu(listas);
			break;
		default:
			cout << "Respuesta invalida" << endl;
			cout << endl;
			menuCliente(listas);
			break;
	}

}

void menuClienteNoRegistrado(estructuraListas &listas) {
	cout << "CLIENTE NO REGISTRADO" << endl;
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar productos" << endl;
	cout << "3.Registrarse" << endl;
	cout << "Que desea hacer: ";
	string respuesta,codigo;
	cin >> respuesta;
	switch (stoi(respuesta)) {
	case 1:
		cout << "Codigo: ";
		cin >> codigo;
		consultarPrecio(listas, codigo);
		cout << endl;
		menuClienteNoRegistrado(listas);
		break;
	case 2:
		cout << "Codigo de super: ";
		cin >> codigo;
		consultarProductosSuper(listas, codigo);
		cout << endl;
		menuClienteNoRegistrado(listas);
		break;
	case 3:
		cout << "Cedula: ";
		cin >> codigo;
		registrarCliente(listas, codigo);
		cout << endl;
		menu(listas);
		break;
	default:
		cout << "Respuesta invalida" << endl;
		cout << endl;
		menuClienteNoRegistrado(listas);
		break;
	}
}

void menuFuncionario(estructuraListas &listas) {
	cout << "1.Consultar precio" << endl;
	cout << "2.Consultar descuento" << endl;
	cout << "3.Consultar productos" << endl;
	cout << "4.Comprar(carrito)" << endl;
	cout << "5.Ver carrito" << endl;
	cout << "6.Facturación" << endl;
	cout << "7.Descuento extra de 5%" << endl;
	cout << "8.Cerrar sesion" << endl;
	cout << "Que desea hacer: " << endl;
	string respuesta, codigo;
	cin >> respuesta;
	switch (stoi(respuesta)) {
	case 1:
		cout << "Codigo: ";
		cin >> codigo;
		consultarPrecio(listas, codigo);
		cout << endl;
		menuFuncionario(listas);
		break;
	case 2:
		cout << "Cedula: ";
		cin >> codigo;
		if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
		consultarDescuento(listas, codigo, 0);
		cout << endl;
		menuFuncionario(listas);
		break;
	case 3:
		cout << "Codigo de super: ";
		cin >> codigo;
		consultarProductosSuper(listas, codigo);
		cout << endl;
		menuFuncionario(listas);
		break;
	case 4:
		cout << "Cedula: ";
		cin >> codigo;
		if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
		comprarProducto(listas, codigo);
		cout << endl;
		menuFuncionario(listas);
		break;
	case 5:
		cout << "Cedula: ";
		cin >> codigo;
		if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
		listas.listaUsuarios.verCarrito(codigo);
		cout << endl;
		menuFuncionario(listas);
		break;
	case 6:
		cout << "Cedula: ";
		cin >> codigo;
		if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
		listas.listaUsuarios.facturar(codigo);
		cout << "Factura lista, carrito reiniciado" << endl;
		cout << endl;
		menuFuncionario(listas);
	case 7:
		cout << "Cedula: " << endl;
		cin >> codigo;
		if (!listas.listaUsuarios.buscarUsuario(codigo)) { cout << "Usuario no encontrado" << endl; }
		listas.listaUsuarios.descuentoExtra(codigo);
		cout << endl;
		menuFuncionario(listas);
	case 8:
		cout << endl;
		menu(listas);
		break;
	default:
		cout << "Respuesta invalida" << endl;
		cout << endl;
		menuFuncionario(listas);
		break;
	}
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
			menuCliente(listas);
			break;
		case 1:
			listas.listaUsuarios.aumentarLogin(cedula);
			menuAdministrador(listas);
			break;
		case 2:
			menuVendedor(listas);
			break;
		case 3:
			menuFuncionario(listas);
			break;
		}
	}
	else if (!confirmarLogin(listas.listaUsuarios, cedula, tipo) && tipo == "0") {
		menuClienteNoRegistrado(listas);
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
	//listas
	estructuraListas listas;
	cargarArchivos(listas);
	menu(listas);

	cin.get();
	return 0;
}
