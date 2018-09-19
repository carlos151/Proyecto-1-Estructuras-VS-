#include <iostream>
#include <string>
using namespace std;

class nodoDC {
   public:
   nodoDC(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio)
    {
       codSuper = pCodSuper;
       codigo = pCodigo;
       nombre = pNombre;
       cantidad = pCantidad;
       precio = pPrecio;
       siguiente = NULL;
       anterior =NULL;
    }

  nodoDC(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio,nodoDC * signodo)
    {
       codSuper = pCodSuper;
       codigo = pCodigo;
       nombre = pNombre;
       cantidad = pCantidad;
       precio = pPrecio;
       siguiente = signodo;
    }

  string getSuper() { return codSuper; }

  string getNombre() { return nombre; }

  string getCantidad() { return cantidad; }

  string getPrecio() { return precio; }

  void modificarCantidad(int cant) {
	  cantidad = to_string(stoi(cantidad) - cant);
  }

  int compras = 0;

 private:
   string codSuper,codigo,nombre,cantidad,precio;
   nodoDC *siguiente;
   nodoDC *anterior;
   bool modificado = false;
        
   friend class listaDC;
};
typedef nodoDC *pnodoDC;

class listaDC {
   public:
    listaDC() { primero = actual = NULL; }
    ~listaDC();
    
    void InsertarInicio(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio);
    void InsertarFinal(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio);
    void InsertarPos (string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio, int pos);
    void EliminarInicio();
    void EliminarFinal();
    void EliminarPos(int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Borrar(int v);
    void Mostrar();
    void Siguiente();
    void Primero();
    void Ultimo();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
    bool buscarProducto(string pCodigo);
    int  buscarProductoPos(string pCodigo);
	pnodoDC buscarNodoPos(string pCodigo);
    void modificar(string pCodigo,string cambio,int atributo);
    string consultarPrecio(string pCodigo);
    void consultarProductosSuper(string pCodigoSuper);
	void ultimosDosAgregados(string pCodigoSuper);
	void ultimoModificado();
	void ultimoProdBorrado();
	void productoMasVendido();
	void productoMenosVendido();
    
   private:
	void resetearBanderasMod();

	string ultimoBorrado = "";
    pnodoDC primero;
    pnodoDC actual;
};

listaDC::~listaDC()
{
   pnodoDC aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      primero->anterior=aux->anterior;
      aux->anterior->siguiente=primero;
      delete aux;
   }
   actual = NULL;
}

int listaDC::largoLista()
{
    int cont=0;

    pnodoDC aux = primero;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux->siguiente != primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void listaDC::InsertarInicio(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio)
{
  
   if (ListaVacia())
   {
     primero = new nodoDC(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoDC nuevo=new nodoDC (pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}
 
void listaDC::InsertarFinal(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio)
{
   if (ListaVacia())
     {
     primero = new nodoDC(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoDC nuevo = new nodoDC(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }    
}


void listaDC::InsertarPos(string pCodSuper,string pCodigo,string pNombre,string pCantidad,string pPrecio,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoDC(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
        else
        {     
             pnodoDC aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoDC nuevo= new nodoDC(pCodSuper,pCodigo,pNombre,pCantidad,pPrecio);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
       }
   }
}   

void listaDC::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoDC temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoDC aux = primero;
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoDC temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
    }
}

void listaDC::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoDC temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoDC aux = primero->anterior;
        pnodoDC temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente; 
        primero->anterior=aux;
        delete temp;
      }
    }
}

void listaDC:: borrarPosicion(int pos)
{
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos>largoLista())||(pos<0))
        cout << "Error en posicion" << endl;
   else
   {
	   if (pos == 0) {
		   ultimoBorrado = primero->nombre + ";" + primero->codigo;
		   BorrarInicio();
	   }
      else
      {
       int cont=1;
       pnodoDC aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoDC temp = aux->siguiente;
	   ultimoBorrado = temp->nombre + ";" + temp->codigo;
       aux->siguiente=aux->siguiente->siguiente;
       delete temp;
     }
    }
  }
}

void listaDC::Mostrar()
{
   pnodoDC aux=primero;
   while(aux->siguiente!=primero)
     {
                
      cout << aux->codSuper << ";" << aux->codigo << ";" << aux->nombre << ";" << aux->cantidad << ";" << aux->precio << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->codSuper << ";" << aux->codigo << ";" << aux->nombre << ";" << aux->cantidad << ";" << aux->precio <<"->";
     cout<<endl;
}   

bool listaDC::buscarProducto(string pCodigo){
  pnodoDC aux = primero;
  while(aux->siguiente != primero){
    if(aux->codigo == pCodigo){return true;}
    aux = aux->siguiente;
  }
  if(aux->codigo == pCodigo){return true;}
  return false;
}

int listaDC::buscarProductoPos(string pCodigo){
  int pos = 0;
  pnodoDC aux = primero;
  while(aux->siguiente != primero){
    if(aux->codigo == pCodigo){return pos;}
    aux = aux->siguiente;
    pos++;
  }
  if(aux->codigo == pCodigo){return pos;}
  return -1;
}

void listaDC::modificar(string pCodigo,string cambio,int atributo){
  pnodoDC aux = primero;
  resetearBanderasMod();
  while(aux->siguiente != primero){
    if(aux->codigo == pCodigo){
	  aux->modificado = true;
      switch(atributo){
        case 1:
          aux->codSuper = cambio;
          break;
        case 2:
          aux->codigo = cambio;
          break;
        case 3:
          aux->nombre = cambio;
          break;
        case 4:
          aux->cantidad = cambio;
          break;
        case 5:
          aux->precio = cambio;
          break;
        return;
      }
    }
    aux = aux->siguiente;
  }
  if(aux->codigo == pCodigo){
	aux->modificado = true;
    switch(atributo){
        case 1:
          aux->codSuper = cambio;
          break;
        case 2:
          aux->codigo = cambio;
          break;
        case 3:
          aux->nombre = cambio;
          break;
        case 4:
          aux->cantidad = cambio;
          break;
        case 5:
          aux->precio = cambio;
          break;
    }
  }
}

string listaDC::consultarPrecio(string pCodigo){
  pnodoDC aux = primero;
  while(aux->siguiente != primero){
    if(aux->codigo == pCodigo){return aux->nombre + ": " + aux->precio;}
    aux = aux->siguiente;
  }
  if(aux->codigo == pCodigo){return aux->nombre+": "+aux->precio;}
}

void listaDC::consultarProductosSuper(string pCodigoSuper){
  pnodoDC aux = primero;
  while(aux->siguiente != primero){
    if(aux->codSuper == pCodigoSuper){
      cout << aux->nombre << endl;
    }
    aux = aux->siguiente;
  }
  if(aux->codSuper == pCodigoSuper){
    cout << aux->nombre << endl;
  }
}

pnodoDC listaDC::buscarNodoPos(string pCodigo) {
	pnodoDC aux = primero;
	while (aux->siguiente != primero) {
		if (aux->codigo == pCodigo) { return aux; }
		aux = aux->siguiente;
	}
	if (aux->codigo == pCodigo) { return aux; }
	return false;
}

void listaDC::ultimosDosAgregados(string pCodigoSuper) {
	cout << endl;
	cout << "Ultimos dos productos agregados al super" << endl;
	pnodoDC aux = primero->anterior;
	int cont = 2;
	while (cont != 0 && aux != primero) {
		if (aux->codSuper == pCodigoSuper) {
			cout << aux->nombre << ";" << aux->codigo << endl;
			cont--;
		}
		aux = aux->anterior;
	}
	if (cont != 0 && aux->codSuper == pCodigoSuper) { cout << aux->nombre << ";" << aux->codigo << endl; }
}

void listaDC::resetearBanderasMod() {
	pnodoDC aux = primero;
	aux->anterior->modificado = false;
	while (aux->siguiente != primero) {
		aux->modificado = false;
		aux = aux->siguiente;
	}
}

void listaDC::ultimoModificado() {
	cout << endl;
	cout << "Ultimo producto modificado:" << endl;
	pnodoDC aux = primero;
	bool done = false;
	while (aux->siguiente != primero) {
		if (aux->modificado) {
			cout << aux->nombre << ";" << aux->codigo << endl;
			done = true;
		}
		aux = aux->siguiente;
	}
	if (aux->modificado) {
		cout << aux->nombre << ";" << aux->codigo << endl;
		done = true;
	}
	if (!done) { cout << "No se ha modificado nada" << endl; }
}

void listaDC::ultimoProdBorrado() {
	cout << endl;
	cout << "Ultimo producto borrado:" << endl;
	if (ultimoBorrado == "") {
		cout << "No se ha borrado nada" << endl;
	}
	else {
		cout << ultimoBorrado << endl;
	}

}

void listaDC::productoMasVendido() {
	cout << endl;
	cout << "Producto mas vendido:" << endl;
	pnodoDC aux = primero;
	pnodoDC producto = aux;
	while (aux->siguiente != primero) {
		if (aux->compras > producto->compras) {
			producto = aux;
		}
		aux = aux->siguiente;
	}
	if (aux->compras > producto->compras) {
		producto = aux;
	}
	cout << producto->nombre << ";" << producto->codigo << endl;
}

void listaDC::productoMenosVendido() {
	cout << endl;
	cout << "Producto menos vendido:" << endl;
	pnodoDC aux = primero;
	pnodoDC producto = aux;
	while (aux->siguiente != primero) {
		if (aux->compras < producto->compras) {
			producto = aux;
		}
		aux = aux->siguiente;
	}
	if (aux->compras < producto->compras) {
		producto = aux;
	}
	cout << producto->nombre << ";" << producto->codigo << endl;
}
