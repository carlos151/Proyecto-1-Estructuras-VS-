#include <iostream>
#include <string>
#include "listaCarrito.h"

using namespace std;

class nodoUsr {
   public:
   nodoUsr(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo)
    {
       codCiudad = pCiudad;
       cedula = pCedula;
       nombre = pNombre;
       telefono = pTelefono;
       tipo = pTipo;
	   if (pTipo == "0" || pTipo == "3") { descuento = 5; }
       siguiente = NULL;
       anterior =NULL;
    }

  nodoUsr(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo,nodoUsr * signodo)
    {
       codCiudad = pCiudad;
       cedula = pCedula;
       nombre = pNombre;
       telefono = pTelefono;
       tipo = pTipo;
       if(pTipo=="0" || pTipo=="3"){descuento = 5;}
       siguiente = signodo;
    }

  int getDescuento(){return descuento;}
  
  void descuentoExtra() {
	  descuento = 10;
  }

  void vaciarCarrito() {
	  carrito->~listaC();
  }

 private:
   string codCiudad,cedula,nombre,telefono,tipo;
   int descuento,numFacturas;
   nodoUsr *siguiente;
   nodoUsr *anterior;
   listaC *carrito = new listaC;
   int compras = 0;
   int adminLogins = 0;
        
   friend class listaDC_usr;
};
typedef nodoUsr *pnodoUsr;

class listaDC_usr {
   public:
    listaDC_usr() { primero = actual = NULL; }
    ~listaDC_usr();
    
    void InsertarInicio(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo);
    void InsertarFinal(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo);
    void InsertarPos (string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo, int pos);
    void EliminarInicio();
    void EliminarFinal();
    void EliminarPos(int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Borrar(int v);
    void Mostrar();
    void Mostrar(pnodoUsr aux);
    void Siguiente();
    pnodoUsr Primero();
    void Ultimo();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
    bool buscarUsuario(string pCedula);
	void consultarDescuentos();
	void consultarDescuento(string pCodigo);
	void comprar(string cedula,string nombre,string codSuper, int cantidad, float precio);
	void mostrarCarro(string pCedula);
	void descuentoExtra(string pCedula);
	void facturar(string pCedula);
	void masCompras();
	void menosCompras();
	void cantCompras(string pCedula);
	void adminMasTrabajo();
	void adminMenosTrabajo();
	void aumentarLogin(string pCedula);
    
   private:
    pnodoUsr primero;
    pnodoUsr actual;


    friend class listaDC_usrAux;
    friend class nodoUsr_tipo;
};

listaDC_usr::~listaDC_usr()
{
   pnodoUsr aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      primero->anterior=aux->anterior;
      aux->anterior->siguiente=primero;
      delete aux;
   }
   actual = NULL;
}

int listaDC_usr::largoLista()
{
    int cont=0;
    pnodoUsr aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void listaDC_usr::InsertarInicio(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo)
{
   if (ListaVacia())
   {
     primero = new nodoUsr(pCiudad,pCedula,pNombre,pTelefono,pTipo);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoUsr nuevo=new nodoUsr (pCiudad,pCedula,pNombre,pTelefono,pTipo);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}
 
void listaDC_usr::InsertarFinal(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo)
{
   if (ListaVacia())
     {
     pnodoUsr nuevo = new nodoUsr(pCiudad,pCedula,pNombre,pTelefono,pTipo);
     primero = nuevo;
     primero->anterior=primero;
     primero->siguiente=primero;
     
   }  
   else
   { 
     pnodoUsr nuevo = new nodoUsr(pCiudad,pCedula,pNombre,pTelefono,pTipo);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }    
}


void listaDC_usr::InsertarPos(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoUsr(pCiudad,pCedula,pNombre,pTelefono,pTipo);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(pCiudad,pCedula,pNombre,pTelefono,pTipo);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(pCiudad,pCedula,pNombre,pTelefono,pTipo);
        else
        {     
             pnodoUsr aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoUsr nuevo= new nodoUsr(pCiudad,pCedula,pNombre,pTelefono,pTipo);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
       }
   }
}   

void listaDC_usr::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoUsr temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoUsr aux = primero;
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoUsr temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
    }
}

void listaDC_usr::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoUsr temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoUsr aux = primero->anterior;
        pnodoUsr temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente; 
        primero->anterior=aux;
        delete temp;
      }
    }
}

void listaDC_usr:: borrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos>largoLista())||(pos<0))
        cout << "Error en posicion" << endl;
   else
   {
      if(pos==1)
        BorrarInicio();
      else
      {
       int cont=2;
       pnodoUsr aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoUsr temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       delete temp;
     }
    }
  }
}

void listaDC_usr::Mostrar()
{
   pnodoUsr aux=primero;
   while(aux->siguiente!=primero)
     {
                
      cout << aux->codCiudad << ";" << aux->cedula << ";" << aux->nombre << ";" << aux->telefono << ";" << aux->tipo << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->codCiudad << ";" << aux->cedula << ";" << aux->nombre << ";" << aux->telefono << ";" << aux->tipo <<"->";
     cout<<endl;
}   

void listaDC_usr::Mostrar(pnodoUsr aux)
{
   while(aux->siguiente!=primero)
     {   
      cout << aux->codCiudad << ";" << aux->cedula << ";" << aux->nombre << ";" << aux->telefono << ";" << aux->tipo << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->codCiudad << ";" << aux->cedula << ";" << aux->nombre << ";" << aux->telefono << ";" << aux->tipo <<"->";
     cout<<endl;
}   

pnodoUsr listaDC_usr::Primero(){
  return primero;
}

bool listaDC_usr::buscarUsuario(string pCedula){
  pnodoUsr aux = primero;
  while(aux->siguiente != primero){
    if(aux->cedula == pCedula){return true;}
    aux = aux->siguiente;
  }
  if(aux->cedula == pCedula){return true;}
  return false;
}

void listaDC_usr::consultarDescuentos() {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		cout << aux->nombre << ": " << aux->descuento << "%" << endl;
		aux = aux->siguiente;
	}
	cout << aux->nombre << ": " << aux->descuento << "%" << endl;
}

void listaDC_usr::consultarDescuento(string pCodigo) {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCodigo) {
			cout << "Descuento: " << aux->descuento << "%" << endl;
			return;
		}
		aux = aux->siguiente;
	}
	if (aux->cedula == pCodigo) {
		cout << "Descuento: " << aux->descuento << "%" << endl;
	}
}

void listaDC_usr::comprar(string pCedula,string nombre,string codSuper, int cantidad, float precio) {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCedula) { 
			cout << "hola" << endl;
			if (aux->carrito->codSuper == "") { aux->carrito->codSuper = codSuper; }

			if (aux->carrito->codSuper == codSuper) {
				aux->compras++;
				aux->carrito->InsertarFinal(nombre, cantidad, precio);
				cout << "Producto agregado al carrito!" << endl;
			}
			else { cout << "El producto esta en un super distinto al del carrito" << endl; return; }
			
		}
		aux = aux->siguiente;
	}
	if (aux->carrito->codSuper == "") { aux->carrito->codSuper = codSuper; }
	if (aux->cedula == pCedula && aux->carrito->codSuper == codSuper) {
		aux->compras++;
		aux->carrito->InsertarFinal(nombre, cantidad, precio);
		cout << "Producto agregado al carrito!" << endl;
	}
	else if(aux->cedula == pCedula) { cout << "El producto esta en un super distinto al del carrito" << endl; return; }
}

void listaDC_usr::mostrarCarro(string pCedula) {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCedula) {
			aux->carrito->Mostrar();
			return;
		}
		aux = aux->siguiente;
	}
	if (aux->cedula == pCedula) {
		if (aux->carrito == NULL) {
			cout << "Carrito vacio" << endl;
			return;
		}
		else {
			aux->carrito->Mostrar();
			return;
		}
	}
}

void listaDC_usr::descuentoExtra(string pCedula) {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCedula) {
			aux->descuentoExtra();
			return;
		}
		aux = aux->siguiente;
	}
	if (aux->cedula == pCedula) { aux->descuentoExtra(); }
}

void listaDC_usr::facturar(string pCedula) {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCedula) { 
			aux->numFacturas++;
			aux->carrito->facturar(pCedula,aux->telefono,aux->numFacturas,aux->descuento,aux->nombre);
		}
		aux = aux->siguiente;
		aux->vaciarCarrito();
	}
	if (aux->cedula == pCedula) { 
		aux->numFacturas++;
		aux->carrito->facturar(pCedula,aux->telefono,aux->numFacturas,aux->descuento,aux->nombre);
	}
	aux->vaciarCarrito();
}

void listaDC_usr::masCompras() {
	pnodoUsr aux = primero;
	pnodoUsr cliente = aux;
	while (aux->siguiente != primero) {
		if (aux->compras > cliente->compras) {cliente = aux;}
		aux = aux->siguiente;
	}
	if (aux->compras > cliente->compras) { cliente = aux; }
	if (cliente->compras == 0) {
		cout << "Nadie ha comprado" << endl;
		return;
	}
	cout << cliente->nombre << endl;
}

void listaDC_usr::menosCompras() {
	pnodoUsr aux = primero;
	pnodoUsr cliente = aux;
	while (aux->siguiente != primero) {
		if (aux->compras < cliente->compras) { cliente = aux; }
		aux = aux->siguiente;
	}
	if (aux->compras < cliente->compras) { cliente = aux; }
	cout << cliente->nombre << endl;
}

void listaDC_usr::cantCompras(string pCedula) {
	cout << "Cantidad de compras de ";
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCedula) { cout << aux->nombre << ": " << aux->compras << endl; return; }
		aux = aux->siguiente;
	}
	if (aux->cedula == pCedula) { cout << aux->nombre << ": " << aux->compras << endl; }
}

void listaDC_usr::adminMasTrabajo() {
	cout << endl;
	pnodoUsr aux = primero;
	pnodoUsr admin = aux;
	while (aux->siguiente != primero) {
		if (aux->adminLogins > admin->adminLogins) { admin = aux; }
		aux = aux->siguiente;
	}
	if (aux->adminLogins > admin->adminLogins) { admin = aux; }
	if (admin->adminLogins == 0) { cout << "Ningun admin ha trabajado" << endl; }
	else {
		cout << "Admin que mas trabajo: ";
		cout << admin->nombre << endl;
	}
}

void listaDC_usr::adminMenosTrabajo() {
	cout << endl;
	pnodoUsr aux = primero;
	pnodoUsr admin = aux;
	while (aux->siguiente != primero) {
		if (aux->adminLogins < admin->adminLogins) { admin = aux; }
		aux = aux->siguiente;
	}
	if (aux->adminLogins < admin->adminLogins) { admin = aux; }
	cout << "Admin que menos trabajo: ";
	cout << admin->nombre << endl;
}

void listaDC_usr::aumentarLogin(string pCedula) {
	pnodoUsr aux = primero;
	while (aux->siguiente != primero) {
		if (aux->cedula == pCedula) { aux->adminLogins++; }
		aux = aux->siguiente;
	}
	if (aux->cedula == pCedula) { aux->adminLogins++; }
}

class nodoUsr_tipo {
  public:
    nodoUsr_tipo(string pTipo){
      tipo = pTipo;
      siguiente = NULL;
      anterior = NULL;
    }

    nodoUsr_tipo(string pTipo,nodoUsr_tipo *signodo){
      tipo = pTipo;
      siguiente = signodo;
    }

    nodoUsr_tipo(string pTipo,nodoUsr_tipo *signodo,nodoUsr_tipo *antnodo){
      tipo = pTipo;
      siguiente = signodo;
      anterior = antnodo;
    }

    void attach_list(listaDC_usr pLista){
      listaUsrs = pLista;
    }

  private:
    string tipo;
    nodoUsr_tipo *siguiente;
    nodoUsr_tipo *anterior;
    listaDC_usr listaUsrs;

    friend class listaDC_usrAux;
};
typedef nodoUsr_tipo *pnodoUsr_tipo;

class listaDC_usrAux {
  public:
    listaDC_usrAux() {
      primero = new nodoUsr_tipo("0");
      pnodoUsr_tipo aux = primero;
      for(int i = 1;i < 4;i++){
        pnodoUsr_tipo nuevo = new nodoUsr_tipo(to_string(i),NULL,aux);
        aux->siguiente = nuevo;
        listaDC_usr l1;
        aux->attach_list(l1);
        aux = aux->siguiente;
      }
      primero->anterior = aux;
    }
   
    void Mostrar();
    void Mostrar(int tipo);
    void InsertarUsuario(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo,int tipo);
    bool buscarUsuario(string cedula);
    bool verificarUsuario(string cedula,int tipo);
    bool listaVacia(int tipo);
    void consultarDescuentos();
	void consultarDescuento(string pCodigo, int tipo);
	void comprar(string cedula, string nombre,string codSuper, int cantidad, float precio);
	void verCarrito(string cedula);
	void descuentoExtra(string cedula);
	void facturar(string cedula);
	void masCompras();
	void menosCompras();
	void cantCompras(string cedula);
	void adminMasTrabajo();
	void adminMenosTrabajo();
	void aumentarLogin(string pCedula);

  private:
    pnodoUsr_tipo primero,actual;
};

void listaDC_usrAux::Mostrar(){
  cout << primero->tipo << "->" << primero->siguiente->tipo << "->" << primero->siguiente->siguiente->tipo << "->" << primero->siguiente->siguiente->siguiente->tipo << "->" << endl;
}

void listaDC_usrAux::Mostrar(int tipo){
  switch(tipo){
    case 0:
      if(primero->listaUsrs.ListaVacia()){break;}
      cout << "Usuarios tipo 0: ";
      primero->listaUsrs.Mostrar();
      break;
    case 1:
      if(primero->siguiente->listaUsrs.ListaVacia()){break;}
      cout << "Usuarios tipo 1: ";
      primero->siguiente->listaUsrs.Mostrar();
      break;
    case 2:
      if(primero->siguiente->siguiente->listaUsrs.ListaVacia()){break;}
      cout << "Usuarios tipo 2: ";
      primero->siguiente->siguiente->listaUsrs.Mostrar();
      break;
    case 3:
      if(primero->siguiente->siguiente->siguiente->listaUsrs.ListaVacia()){break;}
      cout << "Usuarios tipo 3: ";
      primero->siguiente->siguiente->siguiente->listaUsrs.Mostrar();
      break;
  }
}

void listaDC_usrAux::InsertarUsuario(string pCiudad,string pCedula,string pNombre,string pTelefono,string pTipo,int tipo){
  switch(tipo){
    case 0:
      primero->listaUsrs.InsertarFinal(pCiudad,pCedula,pNombre,pTelefono,pTipo);
      break;
    case 1:
      primero->siguiente->listaUsrs.InsertarFinal(pCiudad,pCedula,pNombre,pTelefono,pTipo);
      break;
    case 2:
      primero->siguiente->siguiente->listaUsrs.InsertarFinal(pCiudad,pCedula,pNombre,pTelefono,pTipo);
      break;
    case 3:
      primero->siguiente->siguiente->siguiente->listaUsrs.InsertarFinal(pCiudad,pCedula,pNombre,pTelefono,pTipo);
      break;
  }
}

bool listaDC_usrAux::buscarUsuario(string cedula){
    pnodoUsr_tipo aux = primero;
    for(int i = 0;i < 4;i++){
      if(!(aux->listaUsrs.ListaVacia()) && aux->listaUsrs.buscarUsuario(cedula)){
        return true;
      }
      aux = aux->siguiente;
    } 
    return false;
}

bool listaDC_usrAux::listaVacia(int tipo){
    switch(tipo){
    case 0:
      return primero->listaUsrs.ListaVacia();
      break;
    case 1:
      return primero->siguiente->listaUsrs.ListaVacia();
      break;
    case 2:
      return primero->siguiente->siguiente->listaUsrs.ListaVacia();
      break;
    case 3:
      return primero->siguiente->siguiente->siguiente->listaUsrs.ListaVacia();
      break;
    }
}

bool listaDC_usrAux::verificarUsuario(string cedula,int tipo){
    switch(tipo){
      case 0:
        return primero->listaUsrs.buscarUsuario(cedula);
        break;
      case 1:
        return primero->siguiente->listaUsrs.buscarUsuario(cedula);
        break;
      case 2:
        return primero->siguiente->siguiente->listaUsrs.buscarUsuario(cedula);
        break;
      case 3:
        return primero->siguiente->siguiente->siguiente->listaUsrs.buscarUsuario(cedula);
        break;
      }
}

void listaDC_usrAux::consultarDescuentos(){
	primero->listaUsrs.consultarDescuentos();
	primero->siguiente->siguiente->siguiente->listaUsrs.consultarDescuentos();
}

void listaDC_usrAux::consultarDescuento(string pCodigo, int tipo) {
	if()
	switch (tipo) {
		case 0:
			primero->listaUsrs.consultarDescuento(pCodigo);
			break;
		case 3:
			primero->siguiente->siguiente->siguiente->listaUsrs.consultarDescuento(pCodigo);
			break;
	}
}

void listaDC_usrAux::comprar(string cedula, string nombre,string codSuper,int cantidad, float precio) {
	if (primero->listaUsrs.buscarUsuario(cedula)) {
		primero->listaUsrs.comprar(cedula, nombre,codSuper, cantidad, precio);
	}
	else {
		primero->siguiente->siguiente->siguiente->listaUsrs.comprar(cedula, nombre,codSuper, cantidad, precio);
	}
}

void listaDC_usrAux::verCarrito(string cedula) {
	if (primero->listaUsrs.buscarUsuario(cedula)) {
		primero->listaUsrs.mostrarCarro(cedula);
	}
	else {
		primero->siguiente->siguiente->siguiente->listaUsrs.mostrarCarro(cedula);
	}
}

void listaDC_usrAux::descuentoExtra(string cedula) {
	primero->siguiente->siguiente->siguiente->listaUsrs.consultarDescuento(cedula);
}

void listaDC_usrAux::facturar(string cedula) {
	if (primero->listaUsrs.buscarUsuario(cedula)) {
		primero->listaUsrs.facturar(cedula);
	}
	else {
		primero->siguiente->siguiente->siguiente->listaUsrs.facturar(cedula);
	}
}

void listaDC_usrAux::masCompras(){
	cout << endl;
	cout << "Cliente que mas compro:";
	primero->listaUsrs.masCompras();
	cout << endl;
	cout << "Cliente-Funcionario que mas compro:";
	primero->siguiente->siguiente->siguiente->listaUsrs.masCompras();
}

void listaDC_usrAux::menosCompras() {
	cout << endl;
	cout << "Cliente que menos compro:" << endl;
	primero->listaUsrs.menosCompras();
	cout << endl;
	cout << "Cliente-Funcionario que menos compro:" << endl;
	primero->siguiente->siguiente->siguiente->listaUsrs.menosCompras();
}

void listaDC_usrAux::cantCompras(string cedula) {
	if (primero->listaUsrs.buscarUsuario(cedula)) {
		primero->listaUsrs.cantCompras(cedula);
	}
	else {
		primero->siguiente->siguiente->siguiente->listaUsrs.cantCompras(cedula);
	}
}

void listaDC_usrAux::adminMasTrabajo() {
	primero->siguiente->listaUsrs.adminMasTrabajo();
}

void listaDC_usrAux::adminMenosTrabajo() {
	primero->siguiente->listaUsrs.adminMenosTrabajo();
}

void listaDC_usrAux::aumentarLogin(string pCedula) {
	primero->siguiente->listaUsrs.aumentarLogin(pCedula);
}