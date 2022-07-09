#ifndef FUNCOES_LISTA_H_INCLUDED
#define FUNCOES_LISTA_H_INCLUDED

#include "estruturas.h"

char menuLista1();

tipoPrestamo *eliminaElementoLista(tipoPrestamo *Lista,int *cantidad,int posicaoEliminar);

void MostrarDadosLista(tipoPrestamo Lista[],int elementosNaLista);

int procuraNumeroRegistro_paraLista(tipoPrestamo Lista[],int elementosNaLista,int numeroRegistroPreciso);

char menuAvisoDeSeguridadApagarElementoLista();

void apagarElementoLista(tipoPrestamo *Lista,int *elementosNaLista);

void gravarFicheiroDadosLista (tipoPrestamo Lista[], int quant);

tipoPrestamo  *leFicheiroDadosLista (tipoPrestamo Lista[],int *quant);

void editarCampusDestinoEmprestimoNaLista(tipoPrestamo *Lista,int elementosNaLista);

int atribucaoBicicletaListaOrdemEntrada(tipoPrestamo Lista[],int elementosNaLista,tipoBicicleta Bicicletas[],int Quantidade_Bicicletas);

char menuAtribucaoListaEspera();

int descubrirUtenteDesdeEmprestimo(tipoPrestamo ElementoEmprestimo,tipoUtente Utentes[],int Quantidade_Utente);

void ListarListaPorDistanciaDecres(tipoPrestamo Lista[],int elementosNaLista);

void ListarListaPorDistanciaCres(tipoPrestamo Lista[],int elementosNaLista);

char menuListaDistancia();

void escreveFichTextoNumeroRegistro(int numeroRegistro);

void leFichTextoNumeroRegistro(int *numeroRegistro);

#endif // FUNCOES_LISTA_H_INCLUDED
