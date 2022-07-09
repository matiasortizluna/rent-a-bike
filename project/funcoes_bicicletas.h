#ifndef FUNCOES_BICICLETAS_H_INCLUDED
#define FUNCOES_BICICLETAS_H_INCLUDED

#include "estruturas.h"

char menuBicicletas1();

char Menu_Estado_Bicicleta();

int procura_ID_Bicicleta(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas,int numedeprocu);

int ler_ID_Bicicleta(char texto[MAX_STRING],int minimo, int maximo,tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas);

void imprimirEstadoBicicleta(char text[MAX_STRING],char opcionEscogida);

void lerDadosBicicletas(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas);

void Mostrar_Dados_Bicicletas(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas);

void gravarFicheiroDadosBicicleta (tipoBicicleta vBicicleta[MAX_BICICLETAS], int quant);

void  leFicheiroDadosBicicleta (tipoBicicleta vBicicleta[MAX_BICICLETAS],int *quant);

void consultarDadosBicicleta(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas);

void acresentarBicicleta (tipoBicicleta dados[MAX_BICICLETAS],int *Quantidade_Bicicletas);

void repararBicicleta(tipoBicicleta Bicicletas[],int cantidadBicicletas);

int QuaantidadeBicletasDisponibles(int Quantidade_Bicicletas,char CampusOrigenPrestamo,tipoBicicleta Bicicletas[]);

char Menu_Estado_Avaria();

void escreveFichTextoAverias(tipoAveria Averias[], int cantidadAverias);

tipoAveria lerDadosAveria(int BicicletaUsada, int distanciaAteEsseMomento);

void UltimaBicicleta(tipoUtente Utentes[],int Quantidade_Utente,tipoBicicleta Bicicletas[],int Quantidade_Bicicletas,tipoPrestamo Historico[],int historioPres);

#endif // FUNCOES_BICICLETAS_H_INCLUDED
