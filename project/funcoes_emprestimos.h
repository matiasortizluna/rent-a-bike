#ifndef FUNCOES_EMPRESTIMOS_H_INCLUDED
#define FUNCOES_EMPRESTIMOS_H_INCLUDED

#include "estruturas.h"

char menuPrestamos1();

int acrescentarNumeroRegistro (int codigo);

void novoPrestamo(tipoPrestamo Prestamos[],int CantidadPrestamos,int numeroRegistro,tipoUtente Utentes[],int Quantidade_Utentes);

void Mostrar_Dados_Emprestimos(tipoPrestamo dados[],int Cantidad_Emprestimos);

void consultarDadosPrestamo(tipoPrestamo dados[],int CantidadPrestamos);

int procuraNumeroRegistro_paraPrestamos(char texto[MAX_STRING],tipoPrestamo Prestamos[],int cantidadPrestamos,int *numeroRegistroPreciso);

char menuDevolucionBicicleta();

char estadoDevolucionBicicleta();

void gravarFicheiroDadosPrestamos (tipoPrestamo Prestamos[], int quant);

tipoPrestamo  *leFicheiroDadosPrestamos (tipoPrestamo Prestamos[],int *quant);

void leDadosPedidoEmprestimo (tipoPrestamo *Prestamos, int numeroRegistro,int IDUtente,char TipoUtente);

int asignacaoBicicleta(int Quantidade_Bicicletas,tipoBicicleta Bicicletas[],char campusOrigen);

tipoPrestamo *eliminaElementoPrestamo(tipoPrestamo *Prestamos,int *cantidad,int posicaoEliminar);

#endif // FUNCOES_EMPRESTIMOS_H_INCLUDED
