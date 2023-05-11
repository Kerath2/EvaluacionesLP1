/*
 * Alumno : Gerardo Miguel Tacay Terrazos
 * Codigo: 20193503
 */

#include "Clientes.h"
#include "funciones.h"


int main(int argc, char** argv) {
     char ***cli_NombreCategoria, ***pro_CodigoDescripcion, ***ped_Codigo;
     int **cli_DniTelefono, ***ped_FechaCantidad;
     double **pro_PrecioDescuento;
     
     CargaDeClientes (cli_DniTelefono, cli_NombreCategoria, "Clientes.csv");
     ReporteDeClientes (cli_DniTelefono, cli_NombreCategoria, "PruebaClientes.txt");
     
     
     CargaDePedidosYProductos(cli_DniTelefono, pro_CodigoDescripcion, 
     pro_PrecioDescuento, ped_Codigo, ped_FechaCantidad, "Pedidos.csv");
     
  
     ReporteDePedidosYProductos(cli_DniTelefono, pro_CodigoDescripcion, 
     pro_PrecioDescuento, ped_Codigo, ped_FechaCantidad, 
     "PruebaProductosPedidos.txt");
     

//     ReporteRlacionDePedidos (cli_DniTelefono, cli_NombreCategoria, pro_CodigoDescripcion, 
//     pro_PrecioDescuento, ped_Codigo, ped_FechaCantidad, 
//     “ReporteDeRelacionDePedidos.txt”);
 return 0;
 
}