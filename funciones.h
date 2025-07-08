#include <stdio.h>

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

    // Declaraciones de variables globales (no definiciones)
    extern struct Zona zonas[5];
    extern struct Zona zonas24[5];
    extern int cantidad;
    extern struct registroFecha fecha;


void Inicioprograma();
void IncluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo);
void ingresoDatos();
void GuardarDatosCO ();
void GuardarDatosSO2 ();
void GuardarDatosNO2 ();
void GuardarDatosPM10 ();
void GuardarDatosPM25 ();
void PredecirCOPendienteCalculada();
void MostrarPrediccionCO24Horas();
void PredecirSO2Pendiente();
void MostrarPrediccionSO2_24Horas();
void PredecirNO2Pendiente();
void MostrarPrediccionNO2_24Horas();
void PredecirPM10Pendiente();
void MostrarPrediccionPM10_24Horas();
void PredecirPM25Pendiente();
void MostrarPrediccionPM25_24Horas();
void GenerarReporte();
void IncluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo);
void MostrarReporte();
void MenuDeOpciones ();

// Función para iniciar el programa
/*void Inicioprograma(){
    printf("Programa iniciado correctamente.\n");
    printf("Bienvenido al sistema de prediccion de contaminacion.\n");

    // ======================== INGRESO DE DATOS ========================
    
    ingresoDatos();

    // ======================== GUARDAR DATOS ===========================
    GuardarDatosCO();
    GuardarDatosPM10();
    GuardarDatosPM25();
    GuardarDatosNO2();
    GuardarDatosSO2();

    // ======================== PREDICCIONES 24 HORAS ===================
    PredecirCOPendienteCalculada();
    PredecirPM10Pendiente();
    PredecirPM25Pendiente();
    PredecirNO2Pendiente();
    PredecirSO2Pendiente();
    // ======================== MOSTRAR PREDICCIONES POR HORA ==========
    
    MostrarPrediccionPM10_24Horas();
    MostrarPrediccionNO2_24Horas();
    MostrarPrediccionSO2_24Horas();
    MostrarPrediccionCO24Horas();
    MostrarPrediccionPM25_24Horas();
    

    // ======================== GENERAR REPORTE FINAL ===================
    GenerarReporte();
    MostrarReporte();
    MenuDeOpciones();

};*/