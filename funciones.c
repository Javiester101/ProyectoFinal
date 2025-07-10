#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funciones.h"
// Limites de contaminacion segun la OMS
#define LIM_PM25 15
#define LIM_PM10 45
#define LIM_NO2 25
#define LIM_SO2 40
#define LIM_CO 4
#define ANO_ACTUAL 2025

// Declaracion de la funcion que incluye el contenido de un archivo en el reporte
void incluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo);

void ingresarDatos() {
    int esValido = 0;
    float valorTemporal = 0;
    int zonaElegida = -1;

    // Mostrar menu de zonas
    printf("Seleccione la zona para ingresar los datos:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }
    do {
        printf("Ingrese el numero de la zona (1-%d): ", cantidad);
        if (scanf("%d", &zonaElegida) != 1 || zonaElegida < 1 || zonaElegida > cantidad) {
            printf("Opcion invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
            zonaElegida = -1;
        }
    } while (zonaElegida < 1 || zonaElegida > cantidad);
    zonaElegida -= 1; // Para usar como indice

    // Asignar el ano como constante
    fecha.anio = ANO_ACTUAL;
    printf("Ano de registro: %d\n", fecha.anio);

    // Validacion del mes
    esValido = 0;
    valorTemporal = 0;
    do {
        printf("Ingrese el mes: ");

        if (scanf("%f", &valorTemporal) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }

        if (ceilf(valorTemporal) != valorTemporal) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }

        fecha.mes = (int)valorTemporal;

        if (fecha.mes >= 1 && fecha.mes <= 12) {
            // Validacion especial para 2025: no permitir meses 1 a 5
            if (fecha.anio == 2025 && fecha.mes <= 5) {
                printf("No se puede realizar la validacion para meses de enero a mayo de 2025.\n");
                continue;
            }
            esValido = 1;
        } else {
            printf("Mes invalido. Debe estar entre 1 y 12.\n");
        }
    } while (esValido == 0);
    
    // Validacion del dia
    esValido = 0;
    valorTemporal = 0;
    int max_dia = 31;
    do {
        // Determinar la cantidad de días del mes
        if (fecha.mes == 2) {
            if ((fecha.anio % 4 == 0 && fecha.anio % 100 != 0) || (fecha.anio % 400 == 0)) {
                max_dia = 29;
            } else {
                max_dia = 28;
            }
        } else if (fecha.mes == 4 || fecha.mes == 6 || fecha.mes == 9 || fecha.mes == 11) {
            max_dia = 30;
        } else {
            max_dia = 31;
        }

        printf("Ingrese el dia (actual): ");
        if (scanf("%f", &valorTemporal) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            esValido = 0;
            continue;
        }

        if (ceilf(valorTemporal) != valorTemporal) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            esValido = 0;
            continue;
        }

        fecha.dia = (int)valorTemporal;

        if (fecha.dia >= 1 && fecha.dia <= max_dia) {
            esValido = 1;
        } else {
            printf("Dia invalido. Debe ser entre 1 y %d.\n", max_dia);
            esValido = 0;
        }
    } while (esValido == 0);

    // Validacion de la hora
    esValido = 0;
    valorTemporal = 0;

    do {
        printf("Ingrese la hora actual (0 - 23): ");

        if (scanf("%f", &valorTemporal) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }

        if (ceilf(valorTemporal) != valorTemporal) {
            printf("Debe ingresar un numero entero. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }

        fecha.hora = (int)valorTemporal;

        if (fecha.hora >= 0 && fecha.hora <= 23) {
            esValido = 1;
        } else {
            printf("Hora invalida. Debe estar entre 0 y 23.\n");
        }
    } while (esValido == 0);

    printf("Fecha y hora de registro: %02d/%02d/%04d %02d:00\n",
        fecha.dia, fecha.mes, fecha.anio, fecha.hora);


    // Ingreso de datos de contaminación SOLO para la zona seleccionada
    printf("Ingrese los niveles de contaminacion para la zona: %s\n", zonas[zonaElegida].nombre);
    for (int j = 0; j < 5; j++) {
        float contaminacion;
        int esValido = 0;
        while (esValido == 0) {
            printf("Ingrese la concentracion de %s: ", zonas[zonaElegida].contaminantes[j].nombre);
            if (scanf("%f", &contaminacion) != 1) {
                printf("Nivel de concentracion invalido. Debe ser un numero flotante. Intente nuevamente:\n");
                while (getchar() != '\n');
            } else if (contaminacion < 0) {
                printf("El valor no puede ser negativo. Ingrese un valor valido:\n");
            } else {
                zonas[zonaElegida].datosContaminacion[j] = contaminacion;
                esValido = 1;
            }
        }
    }

}
// Función para guardar los datos de contaminación en un archivo CSV
//Datos de CO
void GuardarDatosCO (){
    //Abre el archivo CSV para guardar los datos de CO2
    FILE *archivo = fopen("C:\\Users\\nicol\\OneDrive\\Escritorio\\Simuladores\\CODES\\Code in C\\Semestre 2\\ProyectoFinalProgramacion\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosCO.csv", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.dia, fecha.mes, fecha.anio, fecha.hora,
                zonas[i].nombre,
                zonas[i].datosContaminacion[4]);  // Índice 4 = CO
    }

    fclose(archivo);
    printf("Datos de CO guardados correctamente en el archivo historico.\n");
}


//Datos de SO2
void GuardarDatosSO2 (){
    //Abre el archivo CSV para guardar los datos de SO2
    FILE *archivo = fopen("C:\\Users\\nicol\\OneDrive\\Escritorio\\Simuladores\\CODES\\Code in C\\Semestre 2\\ProyectoFinalProgramacion\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosSO2.csv", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.dia, fecha.mes, fecha.anio, fecha.hora,
                zonas[i].nombre,
                zonas[i].datosContaminacion[3]);  // Índice 3 = SO2
    }

    fclose(archivo);
    printf("Datos de SO2 guardados correctamente en el archivo historico.\n");
}



//Datos de NO2
void GuardarDatosNO2 (){
    //Abre el archivo CSV para guardar los datos de NO2
    FILE *archivo = fopen("C:\\Users\\nicol\\OneDrive\\Escritorio\\Simuladores\\CODES\\Code in C\\Semestre 2\\ProyectoFinalProgramacion\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosNO2.csv", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.dia, fecha.mes, fecha.anio, fecha.hora,
                zonas[i].nombre,
                zonas[i].datosContaminacion[2]);  // Índice 2 = NO2
    }

    fclose(archivo);
    printf("Datos de NO2 guardados correctamente en el archivo historico.\n");
}


//Datos de PM10
void GuardarDatosPM10 (){
    //Abre el archivo CSV para guardar los datos de PM10
    FILE *archivo = fopen("C:\\Users\\nicol\\OneDrive\\Escritorio\\Simuladores\\CODES\\Code in C\\Semestre 2\\ProyectoFinalProgramacion\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosPM10.csv", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.dia, fecha.mes, fecha.anio, fecha.hora,
                zonas[i].nombre,
                zonas[i].datosContaminacion[1]);  // Índice 1 = PM10
    }

    fclose(archivo);
    printf("Datos de PM10 guardados correctamente en el archivo historico.\n");
}

//Datos de PM2.5
void GuardarDatosPM25 (){
    //Abre el archivo CSV para guardar los datos de PM2.5
    FILE *archivo = fopen("C:\\Users\\nicol\\OneDrive\\Escritorio\\Simuladores\\CODES\\Code in C\\Semestre 2\\ProyectoFinalProgramacion\\ProyectoFinalProgramacion\\ProyectoFinal\\DatosHistoricosPM25.csv", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo CSV para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%02d/%02d/%04d;%02d:00;%s;%.2f\n",
                fecha.dia, fecha.mes, fecha.anio, fecha.hora,
                zonas[i].nombre,
                zonas[i].datosContaminacion[0]);  // Índice 0 = PM2.5
    }

    fclose(archivo);
    printf("Datos de PM2.5 guardados correctamente en el archivo historico.\n");
}


void CalcularCO24h() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[4];
        float tendencia = zonas[i].valoresTendencia[4];
        float prediccion = valor_actual + tendencia * 1;
        zonas24[i].datosContaminacion[4] = prediccion;
        printf("Prediccion CO (24h) en %s: actual=%.3f, tendencia=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, tendencia, prediccion);
    }
}

void MostrarPrediccionCO24Horas() {
    printf("\n========= PREDICCION DE CO PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion CO");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[4];
        float tendencia = zonas[i].valoresTendencia[4];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + tendencia * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("============================================================================\n");
}

void CalcularSO224h() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[3];
        float tendencia = zonas[i].valoresTendencia[3];
        float prediccion = valor_actual + tendencia * 1;
        zonas24[i].datosContaminacion[3] = prediccion;
        printf("Prediccion SO2 (24h) en %s: actual=%.3f, tendencia=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, tendencia, prediccion);
    }
}

void MostrarPrediccionSO2_24Horas() {
    printf("\n========= PROMEDIO DE PREDICCION DE SO2 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion SO2");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[3];  // SO2 actual
        float tendencia = zonas[i].valoresTendencia[3];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + tendencia * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}

void CalcularNO224h() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[2];
        float tendencia = zonas[i].valoresTendencia[2];
        float prediccion = valor_actual + tendencia * 1;
        zonas24[i].datosContaminacion[2] = prediccion;
        printf("Prediccion NO2 (24h) en %s: actual=%.3f, tendencia=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, tendencia, prediccion);
    }
}

void MostrarPrediccionNO2_24Horas() {
printf("\n========= PREDICCION DE NO2 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion NO2");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[2];  // NO2 actual
        float tendencia = zonas[i].valoresTendencia[2];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + tendencia * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}

void CalcularPM1024h() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[1];
        float tendencia = zonas[i].valoresTendencia[1];
        float prediccion = valor_actual + tendencia * 1;
        zonas24[i].datosContaminacion[1] = prediccion;
        printf("Prediccion PM10 (24h) en %s: actual=%.3f, tendencia=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, tendencia, prediccion);
    }
}

void MostrarPrediccionPM10_24Horas() {
    printf("\n========= PREDICCION DE PM10 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion PM10");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[1];
        float tendencia = zonas[i].valoresTendencia[1];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + tendencia * h;
            suma += prediccion;
        }

        float promedio = suma / 24.0;

        printf("%-15s | %-10.3f\n", zonas[i].nombre, promedio);
    }

    printf("=============================================================================\n");
}

void CalcularPM2524h() {
    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[0];
        float tendencia = zonas[i].valoresTendencia[0];
        float prediccion = valor_actual + tendencia * 1;
        zonas24[i].datosContaminacion[0] = prediccion;
        printf("Prediccion PM2.5 (24h) en %s: actual=%.3f, tendencia=%.6f, predicho=%.3f\n",
               zonas[i].nombre, valor_actual, tendencia, prediccion);
    }
}

void MostrarPrediccionPM25_24Horas() {
    printf("\n========= PREDICCION DE PM2.5 PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("%-15s | %-10s\n", "Zona", "Prediccion PM2.5");
    printf("-------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        float valor_actual = zonas[i].datosContaminacion[0];     // PM2.5
        float tendencia = zonas[i].valoresTendencia[0];
        float suma = 0;

        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + tendencia * h;
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
            fecha.dia, fecha.mes, fecha.anio, fecha.hora);
    fprintf(reporte, "Zona\t\tContaminante\tActual\tPredicción 24h\n");
    // Calcular predicciones para cada zona y contaminante antes de guardar
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            float valor_actual = zonas[i].datosContaminacion[j];
            float tendencia = zonas[i].valoresTendencia[j];
            float suma = 0;
            for (int h = 1; h <= 24; h++) {
                float prediccion = valor_actual + tendencia * h;
                suma += prediccion;
            }
            float promedio = suma / 24.0;
            zonas24[i].datosContaminacion[j] = promedio; // Guardar la predicción promedio de 24h
            fprintf(reporte, "%-12s\t%-12s\t%.2f\t%.2f\n",
                zonas[i].nombre,
                zonas[i].contaminantes[j].nombre,
                zonas[i].datosContaminacion[j],
                zonas24[i].datosContaminacion[j]);
        }
      // Determinar contaminante con mayor contaminación
        int idx_mayor = 0;
        float max_contaminacion = zonas[i].datosContaminacion[0]; //establece el máximo como el primer dato del primer contaminante
        // Recorre los contaminantes para encontrar el de mayor contaminación
        for (int j = 1; j < 5; j++) {
            if (zonas[i].datosContaminacion[j] > max_contaminacion) {
                max_contaminacion = zonas[i].datosContaminacion[j];
                idx_mayor = j;
            }
        }

        fprintf(reporte, "\nContaminante más crítico en %s: %s (%.2f) - ",
                zonas[i].nombre,
                zonas[i].contaminantes[idx_mayor].nombre,
                max_contaminacion);

        // Clasificación y recomendación con archivo correspondiente
        if (max_contaminacion >= 0 && max_contaminacion <= 12.0) {
            fprintf(reporte, "Clasificacion: Buena (Verde)\n");
            incluirArchivoEnReporte(reporte, "contaminacion_n1.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);

        } else if (max_contaminacion > 12.0 && max_contaminacion <= 35.4) {
            fprintf(reporte, "Clasificacion: Moderada (Amarilla)\n");
            incluirArchivoEnReporte(reporte, "contaminacion_n2.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else if (max_contaminacion > 35.4 && max_contaminacion <= 55.4) {
            fprintf(reporte, "Clasificacion: Danina para Grupos Sensibles (Naranja)\n");
            incluirArchivoEnReporte(reporte, "contaminacion_n3.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else if (max_contaminacion > 55.4 && max_contaminacion <= 150.4) {
            fprintf(reporte, "Clasificacion: Danina (Roja)\n");
            incluirArchivoEnReporte(reporte, "contaminacion_n4.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else if (max_contaminacion > 150.4) {
            fprintf(reporte, "Clasificacion: Muy Danina o Peligrosa (Morada/Granate Oscuro)\n");
            incluirArchivoEnReporte(reporte, "contaminacion_n5.txt");
            printf("Se actualizaron las recomendaciones para la zona %s miralas.\n", zonas[i].nombre);
        } else {
            fprintf(reporte, "Valor fuera de rango\n");
        }

    }
    fclose(reporte);
    printf("Reporte generado correctamente.\n");
    int agregarReporte;
    int esValido = 0;
    float valorTemporal = 0;

    do {
        printf("Desea agregar este reporte al reporte general? (1(si)/0(No)): ");

        if (scanf("%f", &valorTemporal) != 1) {
            printf("Debe ingresar un numero. Intente de nuevo.\n");
            while (getchar() != '\n');
            esValido = 0;
            continue;
        }

        if (ceilf(valorTemporal) != valorTemporal) {
            printf("Debe ingresar un numero entero sin decimales. Intente de nuevo.\n");
            while (getchar() != '\n');
            esValido = 0;
            continue;
        }

        agregarReporte = (int)valorTemporal;

        if (agregarReporte == 1) {
            FILE *reporteGeneral = fopen("reporte_general.txt", "a+");
            if (reporteGeneral == NULL) {
                printf("No se pudo abrir el archivo de reporte general.\n");
                return;
            }
            incluirArchivoEnReporte(reporteGeneral, "reporte_contaminacion.txt");
            fclose(reporteGeneral);
            printf("Reporte agregado al reporte general correctamente.\n");
            esValido = 1;
        } else if (agregarReporte == 0) {
            printf("Reporte no agregado al reporte general.\n");
            esValido = 1;
        } else {
            printf("Opcion invalida. Debe ingresar 1 (si) o 0 (no). Intente de nuevo.\n");
            esValido = 0;
        }
    } while (esValido == 0);
}



// Función auxiliar que agrega linea a línea el contenido de un archivo a otro
void incluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo) {
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
           fecha.dia, fecha.mes, fecha.anio, fecha.hora);

    printf("%-12s | %-12s | %-10s | %-15s\n", 
           "Zona", "Contaminante", "Actual", "Prediccion 24h");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%-12s | %-12s | %-10.2f | %-15.2f\n",
                   zonas[i].nombre,
                   zonas[i].contaminantes[j].nombre,
                   zonas[i].datosContaminacion[j],
                   zonas24[i].datosContaminacion[j]);
        }
    }

    printf("================================================================\n");
}

// Definición de variables globales (solo aquí, no en el .h)

struct Zona zonas[5] = {
    {"Carapungo", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.16809, -0.277532929, 0.154716942, -0.007614, 0.01113441}},
    {"Centro", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {0.0554, 0.964459, -0.072728931, -0.0739445, 0.00633295}},
    {"Cotocollao", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {0.107786, 0.047835, 0.033273232, -0.0051026, 0.004077135}},
    {"Sangolqui", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {0.254448, -1.14707, 0.343161221, 0.00399695, 0.00917739}},
    {"Tumbaco", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.0696, 0.346828, 0.243433055, 0.01567613, -0.00264876}}};

struct Zona zonas24[5] = {
    {"Carapungo", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.002}},
    {"Centro", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.00380303030303031}},
    {"Cotocollao", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {-0.004893939}},
    {"Sangolqui", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {0}},
    {"Tumbaco", {{"PM2.5"}, {"PM10"}, {"NO2"}, {"SO2"}, {"CO"}}, {0}, {0}}};

int cantidad = 5;
struct RegistroFecha fecha;

//Función para predicción de 24h por zona con validación de datos
void menuPrediccion24hZona() {
    int zonaSeleccionada = -1;
    printf("Seleccione la zona para mostrar la prediccion de 24h:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }
    do {
        printf("Ingrese el numero de la zona (1-%d): ", cantidad);
        if (scanf("%d", &zonaSeleccionada) != 1 || zonaSeleccionada < 1 || zonaSeleccionada > cantidad) {
            printf("Opción invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
            zonaSeleccionada = -1;
        }
    } while (zonaSeleccionada < 1 || zonaSeleccionada > cantidad);
    zonaSeleccionada -= 1;

    // Validar si se ingresaron datos para la zona seleccionada
    int datosIngresados = 0;
    for (int j = 0; j < 5; j++) {
        if (zonas[zonaSeleccionada].datosContaminacion[j] > 0) {
            datosIngresados = 1;
            break;
        }
    }
    if (!datosIngresados) {
        printf("No se han ingresado datos para la zona %s. Por favor ingrese los datos primero.\n", zonas[zonaSeleccionada].nombre);
        return;
    }

    // Calcular y mostrar predicciones solo para la zona seleccionada
    // CO
    float valor_actual = zonas[zonaSeleccionada].datosContaminacion[4];
    float tendencia = zonas[zonaSeleccionada].valoresTendencia[4];
    float suma = 0;
    for (int h = 1; h <= 24; h++) {
        float prediccion = valor_actual + tendencia * h;
        suma += prediccion;
    }
    float promedio = suma / 24.0;
    printf("\n========= PREDICCION DE LA ZONA PARA LAS PROXIMAS 24 HORAS =========\n");
    printf("Zona: %s | Prediccion CO: %.2f\n", zonas[zonaSeleccionada].nombre, promedio);

    // PM10
    valor_actual = zonas[zonaSeleccionada].datosContaminacion[1];
    tendencia = zonas[zonaSeleccionada].valoresTendencia[1];
    suma = 0;
    for (int h = 1; h <= 24; h++) {
        float prediccion = valor_actual + tendencia * h;
        suma += prediccion;
    }
    promedio = suma / 24.0;
    printf("Zona: %s | Prediccion PM10: %.2f\n", zonas[zonaSeleccionada].nombre, promedio);

    // PM2.5
    valor_actual = zonas[zonaSeleccionada].datosContaminacion[0];
    tendencia = zonas[zonaSeleccionada].valoresTendencia[0];
    suma = 0;
    for (int h = 1; h <= 24; h++) {
        float prediccion = valor_actual + tendencia * h;
        suma += prediccion;
    }
    promedio = suma / 24.0;
    printf("Zona: %s | Prediccion PM2.5: %.2f\n", zonas[zonaSeleccionada].nombre, promedio);

    // NO2
    valor_actual = zonas[zonaSeleccionada].datosContaminacion[2];
    tendencia = zonas[zonaSeleccionada].valoresTendencia[2];
    suma = 0;
    for (int h = 1; h <= 24; h++) {
        float prediccion = valor_actual + tendencia * h;
        suma += prediccion;
    }
    promedio = suma / 24.0;
    printf("Zona: %s | Prediccion NO2: %.2f\n", zonas[zonaSeleccionada].nombre, promedio);

    // SO2
    valor_actual = zonas[zonaSeleccionada].datosContaminacion[3];
    tendencia = zonas[zonaSeleccionada].valoresTendencia[3];
    suma = 0;
    for (int h = 1; h <= 24; h++) {
        float prediccion = valor_actual + tendencia * h;
        suma += prediccion;
    }
    promedio = suma / 24.0;
    printf("Zona: %s | Prediccion SO2: %.2f\n", zonas[zonaSeleccionada].nombre, promedio);
    printf("===============================================================\n");
}

// Nueva función para imprimir reporte, sugerencias y advertencias por zona seleccionada
void menuReporteZona() {
    int zonaSeleccionada = -1;
    printf("Seleccione la zona para mostrar el reporte y sugerencias:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }
    do {
        printf("Ingrese el numero de la zona (1-%d): ", cantidad);
        if (scanf("%d", &zonaSeleccionada) != 1 || zonaSeleccionada < 1 || zonaSeleccionada > cantidad) {
            printf("Opción inválida. Intente de nuevo.\n");
            while (getchar() != '\n');
            zonaSeleccionada = -1;
        }
    } while (zonaSeleccionada < 1 || zonaSeleccionada > cantidad);
    zonaSeleccionada -= 1;

    // Validar si se ingresaron datos para la zona seleccionada
    int datosIngresados = 0;
    for (int j = 0; j < 5; j++) {
        if (zonas[zonaSeleccionada].datosContaminacion[j] > 0) {
            datosIngresados = 1;
            break;
        }
    }
    if (!datosIngresados) {
        printf("No se han ingresado datos para la zona %s. Por favor ingrese los datos primero.\n", zonas[zonaSeleccionada].nombre);
        return;
    }

    // Calcular y actualizar predicciones de 24h para la zona seleccionada
    for (int j = 0; j < 5; j++) {
        float valor_actual = zonas[zonaSeleccionada].datosContaminacion[j];
        float tendencia = zonas[zonaSeleccionada].valoresTendencia[j];
        float suma = 0;
        for (int h = 1; h <= 24; h++) {
            float prediccion = valor_actual + tendencia * h;
            suma += prediccion;
        }
        float promedio = suma / 24.0f;
        zonas24[zonaSeleccionada].datosContaminacion[j] = promedio;
    }

    // Generar el nombre de archivo para la zona
    char filename[64];
    snprintf(filename, sizeof(filename), "reporte_%s.txt", zonas[zonaSeleccionada].nombre);

    // --- Generar el reporte de la zona en un buffer ---
    char buffer[4096];
    int offset = 0;
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
        "\n================ REPORTE DE LA ZONA: %s ================\n",
        zonas[zonaSeleccionada].nombre);
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
        "%-12s | %-10s | %-15s\n", "Contaminante", "Actual", "Prediccion 24h");
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
        "-----------------------------------------------\n");
    for (int j = 0; j < 5; j++) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset,
            "%-12s | %-10.2f | %-15.2f\n",
            zonas[zonaSeleccionada].contaminantes[j].nombre,
            zonas[zonaSeleccionada].datosContaminacion[j],
            zonas24[zonaSeleccionada].datosContaminacion[j]);
    }
    // Determinar contaminante más crítico
    int idx_mayor = 0;
    float max_contaminacion = zonas[zonaSeleccionada].datosContaminacion[0];
    for (int j = 1; j < 5; j++) {
        if (zonas[zonaSeleccionada].datosContaminacion[j] > max_contaminacion) {
            max_contaminacion = zonas[zonaSeleccionada].datosContaminacion[j];
            idx_mayor = j;
        }
    }
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
        "\nContaminante mas critico: %s (%.2f) - ",
        zonas[zonaSeleccionada].contaminantes[idx_mayor].nombre,
        max_contaminacion);
    // Sugerencias y advertencias
    if (max_contaminacion >= 0 && max_contaminacion <= 12.0) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "Clasificacion: Buena (Verde)\n");
        FILE *f = fopen("contaminacion_n1.txt", "r");
        if (f) { char linea[256]; while (fgets(linea, sizeof(linea), f)) offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s", linea); fclose(f); }
    } else if (max_contaminacion > 12.0 && max_contaminacion <= 35.4) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "Clasificacion: Moderada (Amarilla)\n");
        FILE *f = fopen("contaminacion_n2.txt", "r");
        if (f) { char linea[256]; while (fgets(linea, sizeof(linea), f)) offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s", linea); fclose(f); }
    } else if (max_contaminacion > 35.4 && max_contaminacion <= 55.4) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "Clasificacion: Danina para Grupos Sensibles (Naranja)\n");
        FILE *f = fopen("contaminacion_n3.txt", "r");
        if (f) { char linea[256]; while (fgets(linea, sizeof(linea), f)) offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s", linea); fclose(f); }
    } else if (max_contaminacion > 55.4 && max_contaminacion <= 150.4) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "Clasificacion: Danina (Roja)\n");
        FILE *f = fopen("contaminacion_n4.txt", "r");
        if (f) { char linea[256]; while (fgets(linea, sizeof(linea), f)) offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s", linea); fclose(f); }
    } else if (max_contaminacion > 150.4) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "Clasificacion: Muy Danina o Peligrosa (Morada/Granate Oscuro)\n");
        FILE *f = fopen("contaminacion_n5.txt", "r");
        if (f) { char linea[256]; while (fgets(linea, sizeof(linea), f)) offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s", linea); fclose(f); }
    } else {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "Valor fuera de rango\n");
    }
    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "==============================================================\n");

    // Mostrar en pantalla
    printf("%s", buffer);

    // Guardar el reporte en el archivo de la zona
    FILE *f_out = fopen(filename, "w");
    if (f_out) {
        fputs(buffer, f_out);
        fclose(f_out);
        printf("Reporte guardado en %s\n", filename);
    } else {
        printf("No se pudo escribir el archivo de reporte de la zona.\n");
    }
}

// Función para mostrar el reporte por zona ya generado
void mostrarReporteZonaGenerado() {
    int zonaSeleccionada = -1;
    printf("Seleccione la zona para mostrar el reporte ya generado:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\n", i + 1, zonas[i].nombre);
    }
    do {
        printf("Ingrese el numero de la zona (1-%d): ", cantidad);
        if (scanf("%d", &zonaSeleccionada) != 1 || zonaSeleccionada < 1 || zonaSeleccionada > cantidad) {
            printf("Opción inválida. Intente de nuevo.\n");
            while (getchar() != '\n');
            zonaSeleccionada = -1;
        }
    } while (zonaSeleccionada < 1 || zonaSeleccionada > cantidad);
    zonaSeleccionada -= 1;

    // Generar el nombre de archivo para la zona
    char filename[64];
    snprintf(filename, sizeof(filename), "reporte_%s.txt", zonas[zonaSeleccionada].nombre);

    FILE *reporte = fopen(filename, "r");
    if (!reporte) {
        printf("No existe un reporte generado para la zona %s. Genere un reporte primero.\n", zonas[zonaSeleccionada].nombre);
        return;
    }
    char linea[512];
    while (fgets(linea, sizeof(linea), reporte)) {
        printf("%s", linea);
    }
    fclose(reporte);
}