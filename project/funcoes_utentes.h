#ifndef FUNCOES_UTENTES_H_INCLUDED
#define FUNCOES_UTENTES_H_INCLUDED

#include "estruturas.h"

int procura_ID_Utente(tipoUtente dados[MAX_UTENTES],int Quantidade_Utentes,int numedeprocu);

int ler_ID_Utente(char texto[MAX_STRING],int minimo, int maximo,tipoUtente dados[MAX_UTENTES],int Quantidade_Utentes);

char Menu_Utentes_Profesion();

void Mostrar_Dados_Utentes(tipoUtente Utentes[MAX_UTENTES],int Quantidade_Utentes);

void gravarFicheiroDadosUtentes (tipoUtente vUtentes[MAX_UTENTES], int Quantidade_Utentes);

void  leFicheiroDadosUtentes (tipoUtente vUtente[MAX_UTENTES],int *Quantidade_Utentes);

tipoUtente lerDadosDeNovoUtente(tipoUtente Utentes[],int Quantidade_Utentes);

char menuUtentes1();

void editarUtente(tipoUtente Utentes[],int Quantidade_Utentes);

char menuAvisoDeSeguridadApagarUtente();

void eliminaUtente(tipoUtente Utentes[], int *Quantidade_Utentes);

void consultardadosUtente(tipoUtente dados[MAX_UTENTES],int Quantidade_Utentes);

void DadosUtentesQuantidadeEmprestimosDECRE(tipoUtente Utentes[],int cantidadUtentes);

int devolverBicicleta(tipoBicicleta Bicicletas[], tipoPrestamo Prestamos[],int Quantidade_Bicicletas,int cantidadPrestamos,tipoUtente Utentes[],int cantidadUtentes,int *distanciaTotal,int *estado,char *opcaoAvaria,int *posicaoBicicletaPrecisa);

#endif // FUNCOES_UTENTES_H_INCLUDED
