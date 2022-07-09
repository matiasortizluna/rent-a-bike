#ifndef FUNCOES_ADICIONALES_H_INCLUDED
#define FUNCOES_ADICIONALES_H_INCLUDED

#include "estruturas.h"

char menuCampus1(char texto[MAX_STRING]);

char menuPrincipal(int quantidadeBicicletas,int quantidadeUtentes,int quantidadeEmprestimos, int elementosNaLista, int distanciaTotal);

char menuGuardarOsDadosDeTodo();

char menuCargarOsDadosDeTodo();

void distanciaMedia(tipoBicicleta Bicicletas[],int cantidadBicicletas);

void percentagemEmprestimosTipoUtente(tipoPrestamo Historico[],int historioPres);

void DadosEstadisticos(tipoBicicleta Bicicletas[],int cantidadBicicletas,tipoUtente Utentes[],int cantidadUtentes,tipoPrestamo Historico[],int historioPres);

int UtenteOcupado(tipoPrestamo Lista[],tipoPrestamo Prestamos[],int elementosNaLista,int cantidadPrestamos,int IDpreciso);

void campusOrigenMaisEmprestimos(tipoPrestamo Historico[],int historioPres);

void QuemUtilizoAquelaBicicleta(tipoBicicleta Bicicletas[],int Quantidade_Bicicletas,tipoUtente Utentes[],int Quantidade_Utente,tipoPrestamo Historico[],int historioPres);

void emprestimosEntreDuasDatas(tipoPrestamo Historico[],int historioPres);

char menuDadosEST();

#endif // FUNCOES_ADICIONALES_H_INCLUDED
