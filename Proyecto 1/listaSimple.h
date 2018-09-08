#include <iostream>
#include <string>
using namespace std;

class nodo {
   public:
    nodo(string pCodigo,string pCiudad)
    {
       codigo = pCodigo;
       ciudad = pCiudad;
       siguiente = NULL;
    }

nodo(string pCodigo,string pCiudad, nodo * signodo)
    {
       codigo = pCodigo;
       ciudad = pCiudad;
       siguiente = signodo;
    }

   private:
    string codigo;
    string ciudad;
    nodo *siguiente;
    
        
   friend class lista;
};

typedef nodo *pnodo;

class lista {
   public:
    lista() { primero = actual = NULL; }
    ~lista();
    
    void InsertarInicio(string pCodigo,string pCiudad);
    void InsertarFinal(string pCodigo,string pCiudad);
    void InsertarPos (string pCodigo,string pCiudad, int pos);
    void EliminarInicio();
    void EliminarFinal();
    void EliminarPos(int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Borrar(string pCodigo,string pCiudad);
    void Mostrar();
    void Siguiente();
    void Primero();
    void Ultimo();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    bool buscar(string pCodigo);
    int largoLista();
    
   private:
    pnodo primero;
    pnodo actual;
};

lista::~lista()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   actual = NULL;
}

int lista::largoLista(){
    int cont=0;

    pnodo aux;
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

void lista::InsertarInicio(string pCodigo,string pCiudad)
{
   if (ListaVacia())
     primero = new nodo(pCodigo,pCiudad);
   else
     primero=new nodo (pCodigo,pCiudad,primero);
}
 
void lista::InsertarFinal(string pCodigo,string pCiudad)
{
   if (ListaVacia())
     primero = new nodo(pCodigo,pCiudad);
   else
     { pnodo aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(pCodigo,pCiudad);
      }    
}


void lista::InsertarPos(string pCodigo,string pCiudad,int pos)
{
   if (ListaVacia())
     primero = new nodo(pCodigo,pCiudad);
   else{
        if(pos <=1){
          pnodo nuevo = new nodo(pCodigo,pCiudad);
          nuevo->siguiente= primero;
          primero= nuevo;     
        }      
        else{
             pnodo aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodo nuevo= new nodo(pCodigo,pCiudad);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             
        }
        }
}
      
void lista::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodo aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }
                
              pnodo temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void lista::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodo aux = primero;
                primero=primero->siguiente;                
                delete aux;
            }
        }
}



void lista:: borrarPosicion(int pos){
     if(ListaVacia()){
              cout << "Lista vacia" <<endl;
    }else{
         if((pos>largoLista())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==1){
        primero=primero->siguiente;
        }else{
          int cont=2;
            pnodo aux=  primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            aux->siguiente=aux->siguiente->siguiente;
            }
        }
     }

}
 

void lista::Mostrar()
{
   nodo *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->codigo << ";" << aux->ciudad << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

void lista::Siguiente()
{
   if(actual) actual = actual->siguiente;
}

void lista::Primero()
{
   actual = primero;
}

void lista::Ultimo()
{
   actual = primero;  
   if(!ListaVacia()) 
      while(actual->siguiente) Siguiente();
}

bool lista::buscar(string pCodigo){
    pnodo aux = primero;
    while(aux != NULL){
        if(aux->codigo == pCodigo){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}
