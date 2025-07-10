#include <stdio.h>

//Estructuras
typedef struct Contaminante {
    char nombre[20];
} Contaminante;

typedef struct RegistroFecha {
    int dia;
    int mes;
    int anio;
    int hora;
} RegistroFecha;

typedef struct Zona {
    char nombre[20];
    Contaminante contaminantes[5];
    float datosContaminacion[5];
    float valoresPrediccion[5];
} Zona;

// Declaraciones de variables globales (no definiciones)
extern Zona zonas[5];
extern Zona zonas24[5];
extern int cantidad;
extern RegistroFecha fecha;

// Prototipos de funciones
void incluirArchivoEnReporte(FILE *reporte, const char *nombreArchivo);
void ingresarDatos();
void GuardarDatosCO();
void GuardarDatosSO2();
void GuardarDatosNO2();
void GuardarDatosPM10();
void GuardarDatosPM25();
void CalcularCO24h();
void MostrarPrediccionCO24Horas();
void CalcularSO224h();
void MostrarPrediccionSO2_24Horas();
void CalcularNO224h();
void MostrarPrediccionNO2_24Horas();
void CalcularPM1024h();
void MostrarPrediccionPM10_24Horas();
void CalcularPM2524h();
void MostrarPrediccionPM25_24Horas();
void GenerarReporte();
void MostrarReporte();
void menuPrediccion24hZona();
void menuReporteZona();
void mostrarReporteZonaGenerado();