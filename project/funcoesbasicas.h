#ifndef FUNCOESBASICAS_H_INCLUDED
#define FUNCOESBASICAS_H_INCLUDED

#include "estruturas.h"

void limpaBufferStdin();

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);

void lerDataHora(tipoDataHora *Dados, char texto[MAX_STRING]);

void imprimirProfesion(char texto[MAX_STRING],char opcionEscogida);

void imprimirCampus(char texto[MAX_STRING],char opcionEscogida);

void imprimirData(char texto[MAX_STRING],tipoDataHora dados);

int lerDistancia(char campusDestino,char campusOrigen);

#endif // FUNCOESBASICAS_H_INCLUDED
