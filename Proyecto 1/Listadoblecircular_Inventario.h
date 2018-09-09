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

 private:
   string codSuper,codigo,nombre,cantidad,precio;
   nodoDC *siguiente;
   nodoDC *anterior;
    
        
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
    void modificar(string pCodigo,string cambio,int atributo);
    string consultarPrecio(string pCodigo);
    void consultarProductosSuper(string pCodigoSuper);
    
   private:
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
        while(aux!=primero)
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
      if(pos==0)
        BorrarInicio();
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
  while(aux->siguiente != primero){
    if(aux->codigo == pCodigo){
      switch(atributo){
        case 1:
          aux->codSuper = cambio;
          break
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
        return
      }
    }
    aux = aux->siguiente;
  }
  if(aux->codigo == pCodigo){
    switch(atributo){
        case 1:
          aux->codSuper = cambio;
          break
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

string listaDC::consultarPrecio(string pCodigo){
  pnodoDC aux = primero;
  while(aux->siguiente != primero){
    if(aux->codigo == pCodigo){return aux->precio;}
    aux = aux->siguiente;
  }
  if(aux->codigo == pCodigo){return aux->precio;}
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