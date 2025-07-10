#include <stdio.h>
#include "funciones.h"

int main()
{
    int opc,hecho = 0; // Variable para controlar si se han ingresado datos

    do{
        printf ("\n=== Prediccion de Contaminacion ===\n");
        printf ("1. Ingresar datos de contaminacion\n");
        printf ("2. Calcular niveles de contaminacion en las proximas 24 horas\n");
        printf ("3. Generar reporte de contaminacion por zona\n");
        printf ("4. Mostrar reporte por zona ya generado\n");
        printf ("5. Salir\n");
        printf ("Ingrese una opcion: ");
        if (scanf("%d", &opc) != 1) {
            printf("Debe ingresar un numero entero.\n");
            while (getchar() != '\n'); // Limpia el buffer
            opc = -1; // Para que entre al default
        }

        switch (opc) {
            case 1:
                ingresarDatos();
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
                if (hecho < 2)
                {
                    printf("Debe ingresar los datos de contaminacion antes de generar el reporte por zona.\n");
                    break;
                }
                menuReporteZona();
                break;
            case 4:
                mostrarReporteZonaGenerado();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    }while (opc != 5);
    return 0;
}