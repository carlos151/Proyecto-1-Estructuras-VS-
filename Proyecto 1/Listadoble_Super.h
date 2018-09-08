#include <iostream>
#include <string>
using namespace std;

class nodoD {
   public:
    nodoD(string pCiudad,string pCodigo,string pNombre)
    {
       codigoCiudad = pCiudad;
       codigoSuper = pCodigo;
       nombre = pNombre;
       siguiente = NULL;
       anterior =NULL;
    }

    nodoD(string pCiudad,string pCodigo,string pNombre, nodoD * signodoD)
        {
          codigoCiudad = pCiudad;
          codigoSuper = pCodigo;
          nombre = pNombre;
          siguiente = signodoD;
        }

   private:
    string codigoCiudad,codigoSuper,nombre;
    nodoD *siguiente;
    nodoD *anterior;
    
        
   friend class listaD;
};

typedef nodoD *pnodoD;

class listaD {
   public:
    listaD() { primero = actual = NULL; }
    ~listaD();
    
    void InsertarInicio(string pCiudad,string pCodigo,string pNombre);
    void InsertarFinal(string pCiudad,string pCodigo,string pNombre);
    void InsertarPos (string pCiudad,string pCodigo,string pNombre, int pos);
    void EliminarInicio();
    void EliminarFinal();
    void EliminarPos(int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Borrar(string pCiudad,string pCodigo,string pNombre);
    void Mostrar();
    void Siguiente();
    void Primero();
    void Ultimo();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
    bool buscarSuper(string codigo);
    
   private:
    pnodoD primero;
    pnodoD actual;
};

listaD::~listaD()
{
   pnodoD aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   actual = NULL;
}

int listaD::largoLista(){
    int cont=0;

    pnodoD aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void listaD::InsertarInicio(string pCiudad,string pCodigo,string pNombre)
{
   if (ListaVacia())
     primero = new nodoD(pCiudad,pCodigo,pNombre);
   else
   {
     primero=new nodoD (pCiudad,pCodigo,pNombre,primero);
     primero->siguiente->anterior=primero;
   }
}
 
void listaD::InsertarFinal(string pCiudad,string pCodigo,string pNombre)
{
   if (ListaVacia())
     primero = new nodoD(pCiudad,pCodigo,pNombre);
   else
     { pnodoD aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoD(pCiudad,pCodigo,pNombre);
        aux->siguiente->anterior=aux;       
      }    
}


void listaD::InsertarPos(string pCiudad,string pCodigo,string pNombre,int pos)
{
   if (ListaVacia())
     primero = new nodoD(pCiudad,pCodigo,pNombre);
   else{
        if(pos <=1)
          InsertarInicio(pCiudad,pCodigo,pNombre);    
        else
        {
             pnodoD aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodoD nuevo= new nodoD(pCiudad,pCodigo,pNombre);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;                           
        }
        }
}
      
void listaD::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoD aux = primero;
                while (aux->siguiente->siguiente != NULL) 
                {
                    aux = aux->siguiente;
                }
                
              pnodoD temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void listaD::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoD aux = primero;
                primero=primero->siguiente;                
                delete aux;
            }
        }
}



void listaD:: borrarPosicion(int pos)
{
     if(ListaVacia())
     {
              cout << "Lista vacia" <<endl;
     }
     else
     {
        if((pos>largoLista())||(pos<0))
        {
        cout << "Error en posicion" << endl;
        }
        else
        {
        if(pos==1)
           BorrarInicio();
        else
        {
          if (pos == largoLista())   
             BorrarFinal();
          else
          {   
            int cont=2;
            pnodoD aux=  primero;
            while(cont<pos)
            {
             aux=aux->siguiente;
             cont++;
            }
            pnodoD temp=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            aux->siguiente->anterior=aux;
            delete temp;
          }//else
        }//else
      }//else
    }//else
}
 

void listaD::Mostrar()
{
   nodoD *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->codigoCiudad << ";" << aux->codigoSuper << ";" << aux->nombre << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

void listaD::Siguiente()
{
   if(actual) actual = actual->siguiente;
}

void listaD::Primero()
{
   actual = primero;
}

void listaD::Ultimo()
{
   actual = primero;  
   if(!ListaVacia()) 
      while(actual->siguiente) Siguiente();
}

bool listaD::buscarSuper(string codigo){
  pnodoD aux = primero;
  while(aux != NULL){
      if(aux->codigoSuper == codigo){
        return true;
      }
      aux = aux->siguiente;
  }
  return false;
}
