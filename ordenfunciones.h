#include "funciones.h"
#include <stdio.h>
void Inicioprograma();


// Función para iniciar el programa
void Inicioprograma(){
    printf("Programa iniciado correctamente.\n");
    printf("Bienvenido al sistema de prediccion de contaminacion.\n");

    // ======================== INGRESO DE DATOS ========================
    
    FuncionOregano();

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

};