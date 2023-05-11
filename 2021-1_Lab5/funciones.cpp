/*
 * Alumno : Gerardo Miguel Tacay Terrazos
 * Codigo: 20193503
 */

#include "funciones.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#define INCREMENTO 5
using namespace std;
void CargaDePedidosYProductos(int **cli_DniTelefono, char ***&pro_CodigoDescripcion, 
     double **&pro_PrecioDescuento, char ***&ped_Codigo, int ***&ped_FechaCantidad, const char* nombArch){
    
    ifstream arch(nombArch,ios::in); 
    if(!arch){
        cout << "Error en la apertura del archivo para carga de pedidos y productos" << endl;
        exit(1);
    }
    
    //variables
    char *codigo , *descripcion, c;
    double descuento, precio; 
    int cantidad, dni, dd , mm , aa;

    //recordando numero de clientes
    int numC;
    for (int i = 0 ; cli_DniTelefono[i] != nullptr ;i++) numC = i;

    ped_FechaCantidad = new int**[numC];
    ped_Codigo = new char**[numC];
    int capC[numC], ndC[numC];
    for (int i = 0 ; i < numC ;i++){
        ped_FechaCantidad[i] = nullptr;
        ped_Codigo[i] = nullptr;
        capC[i] =0;
        ndC[i] = 0;
    }

    
    
    
    // Inicializar en nullptr
    pro_CodigoDescripcion = nullptr;
    pro_PrecioDescuento = nullptr;

    int nd = 0, cap  = 0 , ndS = 0;
    while(1){
        if(!leerCadena(arch,codigo)) break;
        sacaCambioDeLinea(codigo);
        leerCadena(arch,descripcion);

        
        arch >> cantidad;
        if(arch.fail()){
            arch.clear();
            arch >> c >> descuento >> c >> cantidad;
        }else{
            descuento = 0;
        }
        arch >> c >> precio >> c >> dni >>  c  >> dd >> c >> mm >> c >> aa;
        int fecha = aa*10000 + mm *100+dd;
        
        if(!estaRepetido(pro_CodigoDescripcion,descripcion,ndS-1)){
            if(ndS == cap)
                incrementaEspaciosSND(pro_CodigoDescripcion,pro_PrecioDescuento,ndS,cap);
            pro_CodigoDescripcion[ndS] = nullptr;
            pro_PrecioDescuento[ndS] = nullptr;
            llenaCodDescripcion(pro_CodigoDescripcion[ndS-1],codigo,descripcion);
            llenaPrecioDesc(pro_PrecioDescuento[ndS-1],precio,descuento);
            ndS++;
        }

        int indice = devuelveIndice(cli_DniTelefono,dni,numC);
        if(indice != -1){
            if (ndC[indice] == capC[indice])IncrementaEsp(ped_FechaCantidad[indice],ped_Codigo[indice],ndC[indice],
                    capC[indice]);
            int ** ptro =ped_FechaCantidad[indice];
            char ** ptro1 = ped_Codigo[indice];
            ptro[ndC[indice]] = nullptr;
            ptro1[ndC[indice]] = nullptr;
            llenaFechaCantidad(ptro[ndC[indice]-1],fecha, cantidad) ;
            llenaCodigo(ptro1[ndC[indice]-1],codigo);
            ndC[indice]++;
        }
        nd++;
    }
    
//    for (int i = 0; pro_CodigoDescripcion[i] != nullptr ;i++){
//        cout << pro_CodigoDescripcion[i][0] << " " << pro_CodigoDescripcion[i][1] << endl;
//    }
//    
//    cout << nd << " " << ndS << endl;

//    for (int i = 0; pro_PrecioDescuento[i]!= nullptr ;i++ ){
//        cout << pro_PrecioDescuento[i][0] << " " << pro_PrecioDescuento[i][1] << endl;
//    }
    
    
//    for (int i = 0; i < numC ; i++){
//        for (int j = 0 ; ped_FechaCantidad[i][j] != nullptr ; j++){
//            cout << ped_Codigo[i][j] << " ";
//        }
//        cout << endl;
//    }
//    
}

int leerCadena(ifstream &arch, char *&cad){
    char buff[200];
    arch.getline(buff,200,',');
    if(arch.eof()) return 0;
    cad = new char[strlen(buff)+1];
    strcpy(cad,buff);
    return 1;
}

void sacaCambioDeLinea(char *&codigo){
    int tam = strlen(codigo);
    for (int i = 0 ; i <tam ; i++)
        if (codigo[i] == '\n')
            codigo[i] = '-';
    
    char * aux;
    aux = new char[tam+1];
    
    int j = 0;
    for (int i = 1 ; i < tam ; i++){
        aux[j] = codigo[i];
        j++;
    }
    aux[j] = 0;
    delete codigo;
    codigo = aux;
}

void incrementaEspaciosSND(char ***&pro_CodigoDescripcion,double **&pro_PrecioDescuento,int &nd,int &cap){
    char ***auxCodDes;
    double ** auxPreD;
    
    cap += INCREMENTO;
    if(pro_CodigoDescripcion == nullptr){
        
        pro_CodigoDescripcion = new char **[cap];
        pro_CodigoDescripcion[0] = nullptr;
        
        pro_PrecioDescuento = new double*[cap];
        pro_PrecioDescuento[0] = nullptr;
        
        nd = 1;
    }else{
        auxCodDes = new char **[cap];
        auxPreD = new double*[cap];
        for (int i = 0 ; i < nd ; i++){
            auxCodDes[i] = pro_CodigoDescripcion[i];
            auxPreD[i] = pro_PrecioDescuento[i];
        }
        delete pro_CodigoDescripcion;
        pro_CodigoDescripcion = auxCodDes;
        
        delete pro_PrecioDescuento;
        pro_PrecioDescuento = auxPreD;
    }
}

void llenaCodDescripcion(char **&nivelII,char *codigo,char *descripcion){
    nivelII = new char*[2];
    nivelII[0] = codigo;
    nivelII[1] = descripcion;
}

int estaRepetido(char ***pro_CodigoDescripcion,char * descripcion,int ndS){
    if(ndS == 0)
        return 0;
   
    for (int i = 0 ; i < ndS ; i++){
        char ** ptro = pro_CodigoDescripcion[i];
        if(!strcmp(descripcion,ptro[1]))
            return 1;
    }
    
    
    return 0;
}

void llenaPrecioDesc(double *&nivelII,double precio,double descuento){
    nivelII = new double[2];
    nivelII[0] = precio;
    nivelII[1] = descuento;
}

int devuelveIndice(int **cli_DniTelefono,int dni,int numC){
    
    for (int i = 0 ; i < numC ; i++){
        int *ptro = cli_DniTelefono[i];
        if(ptro[0] == dni)
            return i;
    }
    return -1;
}

void IncrementaEsp(int **&nivelI, char ** &codNivelI,int &nd, int &cap){
    int ** aux;
    char **auxCod;
    cap+= INCREMENTO;
    if(nivelI == nullptr){
        nivelI = new int*[cap];
        nivelI[0] = nullptr;
        codNivelI = new char*[cap];
        codNivelI[0] = nullptr;
        nd = 1;
    }else{
        aux = new int*[cap];
        auxCod = new char*[cap];
        for (int i = 0; i < nd ; i++){
            aux[i] = nivelI[i];
            auxCod[i] = codNivelI[i];
        }
        delete nivelI;
        nivelI = aux;
        
        delete codNivelI;
        codNivelI = auxCod;
    
    }
}

void llenaFechaCantidad(int *&datos,int fecha, int cantidad){
    datos = new int[2];
    datos[0] = fecha;
    datos[1] = cantidad;
}
void llenaCodigo(char *&datos,char * codigo){
    datos = codigo;
}
void   ReporteDePedidosYProductos(int ** cli_DniTelefono,char*** pro_CodigoDescripcion, 
//     double **pro_PrecioDescuento, char***ped_Codigo, int *** ped_FechaCantidad, 
//     const char * nombrArch){
//    
//        for (int i = 0; pro_CodigoDescripcion[i] != nullptr ;i++){
//        cout << pro_CodigoDescripcion[i][0] << " " << pro_CodigoDescripcion[i][1] << endl;
//    }
//
//
//    for (int i = 0; pro_PrecioDescuento[i]!= nullptr ;i++ ){
//        cout << pro_PrecioDescuento[i][0] << " " << pro_PrecioDescuento[i][1] << endl;
//    }
//    
//    
//    for (int i = 0;  ped_FechaCantidad[i]!=nullptr ; i++){
//        for (int j = 0 ; ped_FechaCantidad[i][j] != nullptr ; j++){
//            cout << ped_Codigo[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    
}