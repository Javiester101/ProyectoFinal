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
        printf ("3. Generar reporte de contaminacion\n");
        printf ("4. Salir\n");
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
                PredecirCOPendienteCalculada();
                PredecirPM10Pendiente();
                PredecirPM25Pendiente();
                PredecirNO2Pendiente();
                PredecirSO2Pendiente();
                MostrarPrediccionCO24Horas();
                MostrarPrediccionPM10_24Horas();
                MostrarPrediccionPM25_24Horas();
                MostrarPrediccionNO2_24Horas();
                MostrarPrediccionSO2_24Horas();
                
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
                printf("Saliendo del programa...\n");
                exit(0);
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    }while (opc != 4);
    return 0;
}