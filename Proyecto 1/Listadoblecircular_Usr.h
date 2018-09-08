#include <iostream>
#include <string>
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
       siguiente = signodo;
    }

 private:
   string codCiudad,cedula,nombre,telefono,tipo;
   nodoUsr *siguiente;
   nodoUsr *anterior;
    
        
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
