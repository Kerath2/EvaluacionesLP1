/*
 * Alumno : Gerardo Miguel Tacay Terrazos
 * Codigo: 20193503
 */
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iomanip>
using namespace std;
void CargaDeClientes (int ** &cli_DniTelefono, char ***& cli_NombreCategoria,const char *);
void ReporteDeClientes (int ** cli_DniTelefono, char *** cli_NombreCategoria,const char *);
void CargaDePedidosYProductos(int **cli_DniTelefono, char ***&pro_CodigoDescripcion, 
double **&pro_PrecioDescuento, char ***&ped_Codigo, int ***&ped_FechaCantidad, const char* nombArch);  
int leerCadena(ifstream &arch, char *&cad);
void sacaCambioDeLinea(char *&codigo);
void incrementaEspaciosSND(char ***&pro_CodigoDescripcion,double **&pro_PrecioDescuento,int &nd,int &cap);
void llenaCodDescripcion(char **&nivelII,char *codigo,char *descripcion);
int estaRepetido(char ***pro_CodigoDescripcion,char * descripcion,int ndS);
void llenaPrecioDesc(double *&nivelII,double precio,double descuento);
int devuelveIndice(int **cli_DniTelefono,int dni,int numC);
void IncrementaEsp(int **&nivelI, char ** &codNivelI,int &nd, int &cap);
void llenaFechaCantidad(int *&datos,int fecha, int cantidad);
void llenaCodigo(char *&datos,char * codigo);
void   ReporteDePedidosYProductos(int ** cli_DniTelefono,char*** pro_CodigoDescripcion, 
     double **pro_PrecioDescuento, char***ped_Codigo, int *** ped_FechaCantidad, 
     const char * nombrArch);
#endif /* FUNCIONES_H */

