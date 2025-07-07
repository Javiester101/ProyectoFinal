#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LIM_PM25 15
#define LIM_PM10 45
#define LIM_NO2 25
#define LIM_SO2 40
#define LIM_CO 4

//Se definenn los limites de contamacion segun la OMS para así tener la restriccion

//Se declara la función que incluirá el contenido de un archivo en el reporte
//Es la unica funcion que se declara antes de su uso ya que cuando se genera el reporte, se necesita incluir los archivos de recomendaciones y alertas
void IncluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo);

//Estructuras
struct Contaminante {
        char nom[20];
    };
    struct registroFecha {
        int day;
        int month;
        int year;
        int hour;   
    };
    typedef struct registroFecha Fecha;
    struct Zona {
        char nombre[20];
        struct Contaminante contaminantes[5];
        float contamDatos[5];
        float pendiente[5];
    };

    struct Zona zonas[5] = {
        {"Belisario",  {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.16809, -0.277532929, 0.154716942, -0.007614, 0.01113441}},
        {"Centro",     {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, { 0.0554,   0.964459,    -0.072728931, -0.0739445, 0.00633295}},
        {"Cotocollao", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, { 0.107786, 0.047835,     0.033273232, -0.0051026, 0.004077135}},
        {"Los Chillos",{{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, { 0.254448, -1.14707,     0.343161221,  0.00399695, 0.00917739}},
        {"Tumbaco",    {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.0696,   0.346828,     0.243433055,  0.01567613, -0.00264876}}
    };

    struct Zona zonas24[5] = {
        {"Belisario", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.002}},
        {"Centro",    {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.00380303030303031}},
        {"Cotocollao",  {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{-0.004893939}},
        {"Los Chillos",   {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}},
        {"Tumbaco", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0},{0}}
    };

    int cantidad = 5; // Número de zonas

    struct registroFecha fecha;



void FuncionOregano(){
//Funcion de Ingreso de datos

 // Validación del año
    int valido = 0;
    float valido2 = 0;

    REPETIR:
        while (valido == 0) {
        printf("Ingrese el periodo actual entre 2025 - 2100: ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero, ingrese de nuevo.\n");
            while (getchar() != '\n'); // Limpia el buffer
            goto REPETIR;
        }

        // Validación de que el número ingresado sea un entero
        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero, ingrese de nuevo.\n");
            while (getchar() != '\n'); // Limpia el buffer
            goto REPETIR;
        }

        fecha.year = (int)valido2; // Convertir float a int

        if (fecha.year >= 2025 && fecha.year <= 2100) {
            valido = 1;
        } else {
            printf("Periodo invalido. Debe ser entre 2025 y 2100.\n");
            goto REPETIR;
        }
    }

   // Validación del mes
    valido = 0;
    valido2 = 0;

    REPETIR_MES:
    while (valido == 0) {
        printf("Ingrese el mes actual (1 - 12): ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_MES;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_MES;
        }

        fecha.month = (int)valido2;

        if (fecha.month >= 1 && fecha.month <= 12) {
            // Validación especial para 2025: no permitir meses 1 a 5
            if (fecha.year == 2025 && fecha.month <= 5) {
                printf("No se puede realizar la validacion para meses de enero a mayo de 2025.\n");
                goto REPETIR_MES;
            }
            valido = 1;
        } else {
            printf("Mes invalido. Debe estar entre 1 y 12.\n");
            goto REPETIR_MES;
        }
    }


    // Validación del día
    valido = 0;
    valido2 = 0;

    REPETIR_DIA:
    while (valido == 0) {
        int max_dia = 31;

        // Determinar la cantidad de días del mes
        if (fecha.month == 2) {
            if ((fecha.year % 4 == 0 && fecha.year % 100 != 0) || (fecha.year % 400 == 0)) {
                max_dia = 29;
                printf("Febrero tiene 29 dias en el periodo %d.\n", fecha.year);
            } else {
                max_dia = 28;
                printf("Febrero tiene 28 dias en el periodo %d.\n", fecha.year);
            }
        } else if (fecha.month == 4 || fecha.month == 6 || fecha.month == 9 || fecha.month == 11) {
            max_dia = 30;
            printf("Este mes tiene 30 dias.\n");
        } else {
            max_dia = 31;
            printf("Este mes tiene 31 dias.\n");
        }

        printf("Ingrese el dia actual (1 - %d): ", max_dia);

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_DIA;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_DIA;
        }

        fecha.day = (int)valido2;

        if (fecha.day >= 1 && fecha.day <= max_dia) {
            valido = 1;
        } else {
            printf("Dia invalido. Debe ser entre 1 y %d.\n", max_dia);
            goto REPETIR_DIA;
        }
    }

    // Validación de la hora
    valido = 0;
    valido2 = 0;

    REPETIR_HORA:
    while (valido == 0) {
        printf("Ingrese la hora actual (0 - 23): ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_HORA;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_HORA;
        }

        fecha.hour = (int)valido2;

        if (fecha.hour >= 0 && fecha.hour <= 23) {
            valido = 1;
        } else {
            printf("Hora invalida. Debe estar entre 0 y 23.\n");
            goto REPETIR_HORA;
        }
    }

    printf("Fecha y hora de registro: %02d/%02d/%04d %02d:00\n",
        fecha.day, fecha.month, fecha.year, fecha.hour);


    // Ingreso de datos de contaminación
    printf("Ingrese los niveles de contaminacion para las siguientes zonas:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < 5; j++) {
            float contaminacion;
            int valido = 0;
            while (valido == 0) {
                printf("Ingrese la concentracion de %s: ", zonas[i].contaminantes[j].nom);
                if (scanf("%f", &contaminacion) != 1) {
                    printf("Nivel de concentracion invalido. Debe ser un numero flotante. Intente nuevamente:\n");
                    while (getchar() != '\n'); // Limpia el buffer
                } else if (contaminacion < 0) {
                    printf("El valor no puede ser negativo. Ingrese un valor valido:\n");
                } else {
                    zonas[i].contamDatos[j] = contaminacion;
                    valido = 1;
                }
            }
        }
    }

}





//Datos de CO
void GuardarDatosCO (){
    //Abre el archivo CSV para guardar los datos de CO2
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosCO.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[4]);  // Índice 4 = CO
    }

    fclose(archivo);
    printf("Datos de CO guardados correctamente en el archivo historico.\n");
}


//Datos de SO2
void GuardarDatosSO2 (){
    //Abre el archivo CSV para guardar los datos de SO2
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosSO2.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[3]);  // Índice 3 = SO2
    }

    fclose(archivo);
    printf("Datos de SO2 guardados correctamente en el archivo historico.\n");
}



//Datos de NO2
void GuardarDatosNO2 (){
    //Abre el archivo CSV para guardar los datos de NO2
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosNO2.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[2]);  // Índice 2 = NO2
    }

    fclose(archivo);
    printf("Datos de NO2 guardados correctamente en el archivo historico.\n");
}


//Datos de PM10
void GuardarDatosPM10 (){
    //Abre el archivo CSV para guardar los datos de PM10
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosPM10.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[1]);  // Índice 1 = PM10
    }

    fclose(archivo);
    printf("Datos de PM10 guardados correctamente en el archivo historico.\n");
}

//Datos de PM2.5
void GuardarDatosPM25 (){
    //Abre el archivo CSV para guardar los datos de PM2.5
    FILE *archivo = fopen("C:\\Users\\jaime\\Documents\\Ejercicios VSCode\\.vscode\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosPM25.csv", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.day, fecha.month, fecha.year, fecha.hour,
                zonas[i].nombre,
                zonas[i].contamDatos[0]);  // Índice 0 = PM2.5
    }

    fclose(archivo);
    printf("Datos de PM2.5 guardados correctamente en el archivo historico.\n");
}


void PredecirCOPendienteCalculada() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[4];     // CO actual
        float pendiente = zonas[i].pendiente[4];          // Pendiente de CO
        float prediccion = valor_actual + pendiente * 1;  // Para 1 unidad de tiempo (día)

        zonas24[i].contamDatos[4] = prediccion;

        printf("Prediccion CO (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionCO24Horas() {
    printf("\n========= PREDICCION DE CO PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion CO");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[4];
        float pendiente = zonas[i].pendiente[4];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("============================================================================\n");
}


void PredecirSO2Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[3];     // SO2 actual
        float pendiente = zonas[i].pendiente[3];          // Pendiente de SO2
        float prediccion = valor_actual + pendiente * 1;  // Para 1 unidad de tiempo (1 día)

        zonas24[i].contamDatos[3] = prediccion;

        printf("Prediccion SO2 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionSO2_24Horas() {
    printf("\n========= PROMEDIO DE PREDICCION DE SO2 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion SO2");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[3];  // SO2 actual
        float pendiente = zonas[i].pendiente[3];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}

void PredecirNO2Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[2];     // NO2 actual
        float pendiente = zonas[i].pendiente[2];          // Pendiente de NO2
        float prediccion = valor_actual + pendiente * 1;  // Para 1 día

        zonas24[i].contamDatos[2] = prediccion;

        printf("Prediccion NO2 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionNO2_24Horas() {
printf("\n========= PREDICCION DE NO2 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion NO2");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[2];  // NO2 actual
        float pendiente = zonas[i].pendiente[2];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}


void PredecirPM10Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[1];     // PM10 actual
        float pendiente = zonas[i].pendiente[1];          // Pendiente de PM10
        float prediccion = valor_actual + pendiente * 1;  // Para 1 día

        zonas24[i].contamDatos[1] = prediccion;

        printf("Prediccion PM10 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionPM10_24Horas() {
    printf("\n========= PREDICCION DE PM10 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion PM10");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[1];
        float pendiente = zonas[i].pendiente[1];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}


void PredecirPM25Pendiente() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[0];     // PM2.5 actual
        float pendiente = zonas[i].pendiente[0];          // Pendiente PM2.5
        float prediccion = valor_actual + pendiente * 1;

        zonas24[i].contamDatos[0] = prediccion;

        printf("Prediccion PM2.5 (24h) en %s: actual=%.3f, pendiente=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, pendiente, prediccion);
    }
}


void MostrarPrediccionPM25_24Horas() {
    printf("\n========= PREDICCION DE PM2.5 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion PM2.5");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].contamDatos[0];     // PM2.5
        float pendiente = zonas[i].pendiente[0];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + pendiente * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}


void GenerarReporte() {
    FILE *reporte = fopen("reporte_contaminacion.txt", "w");
    
    if (reporte == NULL) {
        printf("No se pudo crear el archivo de reporte.\n");
        return;
    }
    fprintf(reporte, "Fecha y hora de registro: %02d/%02d/%04d %02d:00\n\n", 
            fecha.day, fecha.month, fecha.year, fecha.hour);
    fprintf(reporte, "Zona\t\tContaminante\tActual\tPredicción 24h\tPendiente\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fprintf(reporte, "%-12s\t%-12s\t%.2f\t%.2f\t%.6f\n",
                zonas[i].nombre,
                zonas[i].contaminantes[j].nom,
                zonas[i].contamDatos[j],
                zonas24[i].contamDatos[j],
                zonas[i].pendiente[j]);
        }
        //AQUÍ FALTA IMRIMIR ALERTAS Y RECOMENDACIONES
      // Determinar contaminante con mayor contaminación
        int idx_mayor = 0;
        float max_contaminacion = zonas[i].contamDatos[0]; //establece el máximo como el primer dato del primer contaminante
        // Recorre los contaminantes para encontrar el de mayor contaminación
        for (int j = 1; j < 5; j++) {
            if (zonas[i].contamDatos[j] > max_contaminacion) {
                max_contaminacion = zonas[i].contamDatos[j];
                idx_mayor = j;
            }
        }

        fprintf(reporte, "\nContaminante más crítico en %s: %s (%.2f) - ",
                zonas[i].nombre,
                zonas[i].contaminantes[idx_mayor].nom,
                max_contaminacion);

        // Clasificación y recomendación con archivo correspondiente
        if (max_contaminacion >= 0 && max_contaminacion <= 12.0) {
            fprintf(reporte, "Clasificación: Buena (Verde)\n");
            IncluirArchivoEnReporte(reporte, "contaminacion_n1.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);

        } else if (max_contaminacion > 12.0 && max_contaminacion <= 35.4) {
            fprintf(reporte, "Clasificación: Moderada (Amarilla)\n");
            IncluirArchivoEnReporte(reporte, "contaminacion_n2.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else if (max_contaminacion > 35.4 && max_contaminacion <= 55.4) {
            fprintf(reporte, "Clasificación: Dañina para Grupos Sensibles (Naranja)\n");
            IncluirArchivoEnReporte(reporte, "contaminacion_n3.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else if (max_contaminacion > 55.4 && max_contaminacion <= 150.4) {
            fprintf(reporte, "Clasificación: Dañina (Roja)\n");
            IncluirArchivoEnReporte(reporte, "contaminacion_n4.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else if (max_contaminacion > 150.4) {
            fprintf(reporte, "Clasificación: Muy Dañina o Peligrosa (Morada/Granate Oscuro)\n");
            IncluirArchivoEnReporte(reporte, "contaminacion_n5.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else {
            fprintf(reporte, "Valor fuera de rango\n");
        }

    }
    fclose(reporte);
    printf("Reporte generado correctamente.\n");
    int agregarReporte;
    int valido = 0;
    float valido2 = 0;

    REPETIR_AGREGAR:
    while (valido == 0) {
        printf("Desea agregar este reporte al reporte general? (1(si)/0(No)): ");

        if (scanf("%f", &valido2) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_AGREGAR;
        }

        if (ceilf(valido2) != valido2) {
            printf("Debe ingresar un numero entero sin decimales. Intente de nuevo.\n");
            while (getchar() != '\n');
            goto REPETIR_AGREGAR;
        }

        agregarReporte = (int)valido2;

        if (agregarReporte == 1) {
            FILE *reporteGeneral = fopen("reporte_general.txt", "a+");
            if (reporteGeneral == NULL) {
                printf("No se pudo abrir el archivo de reporte general.\n");
                return;
            }
            IncluirArchivoEnReporte(reporteGeneral, "reporte_contaminacion.txt");
            fclose(reporteGeneral);
            printf("Reporte agregado al reporte general correctamente.\n");
            valido = 1;
        } else if (agregarReporte == 0) {
            printf("Reporte no agregado al reporte general.\n");
            valido = 1;
        } else {
            printf("Opcion invalida. Debe ingresar 1 (si) o 0 (no). Intente de nuevo.\n");
            goto REPETIR_AGREGAR;
        }
    }
}



// Función auxiliar que agrega linea a línea el contenido de un archivo a otro
void IncluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo) {
    FILE *info = fopen(nombreArchivo, "r");
    if (info) {
        char linea[256];
        while (fgets(linea, sizeof(linea), info)) {
            fputs(linea, reporte);
        }
        fclose(info);
    } else {
        fprintf(reporte, "[No se pudo abrir %s]\n", nombreArchivo);
    }
}


void MostrarReporte(){
    printf("================================ REPORTE DE CONTAMINACION ================================\n");
    printf("Fecha y hora de registro: %02d/%02d/%04d %02d:00\n\n", 
           fecha.day, fecha.month, fecha.year, fecha.hour);

    printf("%-12s | %-12s | %-10s | %-15s | %-10s\n", 
           "Zona", "Contaminante", "Actual", "Prediccion 24h", "Pendiente");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%-12s | %-12s | %-10.2f | %-15.2f | %-10.6f\n",
                   zonas[i].nombre,
                   zonas[i].contaminantes[j].nom,
                   zonas[i].contamDatos[j],
                   zonas24[i].contamDatos[j],
                   zonas[i].pendiente[j]);
        }
    }

    printf("==========================================================================================\n");
}




void MenuDeOpciones (){
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
                FuncionOregano();
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
}