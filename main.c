/******************************************************************************
Main .c
1. (función que lleva a menú de opciones)

Header 1

2. Ingreso de fecha y hora/ mostrar última fecha de registro (leer de un archivo y mostrar)
3. Elección de zona
4. Ingreso de niveles de contaminación para cada componente 
4.1 Cálculo de niveles en 24 horas
5. Si excede límites aceptables mostrar alerta
6. Mostrar recomendaciones según rangos de contaminación
7. Funciones de archivos para guardar datos, predicciones y recomendaciones a modo de reporte

*******************************************************************************/
#include <stdio.h>
#include "funciones.h"

int main()
{
    int opc,hecho = 0; // Variable para controlar si se han ingresado datos

    do{
        printf ("\n=== Prediccion de Contaminacion ===\n");
        printf ("1. Ingresar datos de contaminacion\n");
        printf ("2. Calcular niveles de contaminacion en las proximas 24 horas\n");
        printf ("3. Generar reporte de contaminacion de totas las zonas\n");
        printf ("4. Generar reporte de contaminacion por zona\n");
        printf ("5. Mostrar reporte por zona ya generado\n");
        printf ("6. Salir\n");
        printf ("Ingrese una opcion: ");
        if (scanf("%d", &opc) != 1) {
            printf("Debe ingresar un número entero.\n");
            while (getchar() != '\n'); // Limpia el buffer
            opc = -1; // Para que entre al default
        }

        switch (opc) {
            case 1:
                ingresoDatos();
                hecho++;
                break;
            case 2:
                if (hecho == 0) {
                    printf("Debe ingresar los datos de contaminacion antes de calcular los niveles.\n");
                    break;
                } else {
                    printf("Niveles de contaminacion calculados correctamente.\n");
                    hecho++;
                }
                menuPrediccion24hZona();
                break;
            case 3:
                if (hecho <2) {
                    printf("Debe ingresar los datos de contaminacion antes de generar el reporte.\n");
                    break;
                }
                GenerarReporte();
                MostrarReporte();
                break;
            case 4:
                if (hecho < 2)
                {
                    printf("Debe ingresar los datos de contaminacion antes de generar el reporte por zona.\n");
                    break;
                }
                menuReporteZona();
                break;
            case 5:
                mostrarReporteZonaGenerado();
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    }while (opc != 6);
    return 0;
}