#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "constantes.h"

typedef struct {

    int ano;    //Tem a opcao que seja entre 2018 e 2020
    int mes;    //Com numeros, e como maximo, 12.
    int dia;    //Dependendo do mes, os dias posiveis.
    int hora;   //Hora, entre 0 y 23.

} tipoDataHora;

typedef struct {

    int ID_Bicicleta;               // ID da bicicleta (unico)
    char Modelo_Bicicleta [20];     // Modelo de bicicleta
    char Estado_Bicicleta;          // Caracter que guarda se esta (D)isponivel, (E)mprestada, (A)variada.
    char Campus_Origen_Bicicleta;   // Caracter que guarda o Campus de Origen.
    int Prestamos_Bicicleta;        //Prestamos feitos pela bicicleta.
    int Vezes_Averias;              //Quantas vezes a bicicleta averiu-se.
    int Vezes_Reparada;             //Quantas vezes a bicicleta reparou-se.
    int Distancia_Total;            //Distancia Recorrida pela Bicicleta.

} tipoBicicleta;

typedef struct {

    int ID_Utente;                  // ID del utente (unico)
    char Nome_Utente[MAX_NOMES];
    int Numero_Telefono;
    char Profesion;                     //Determminar si es: Estudante, Docente, Tecnico Administrativo, Convidado
    int QuantidadePrestamos_Feitos;     //Quantidade de prestamos feitos por cada pessoa.
    int DistanciaTotal_Recorrida;       //De todas as vezes que usou bicicleta, distancia total.

} tipoUtente;

typedef struct {

    int Numero_Registro;                  //Tem que ser unico e gerado pelo computador.
    int ID_Utente_Reserva;               // É o ID do Utente que esta a fazer o pedido de emprestimo.
    char Tipo_Utente_Reserva;            // Guarda o Caracter da profesion do Utente que esta a fazer o Emprestimo.
    int ID_Bicicleta_Reserva;           //É o ID da Bicicleta que esta a ser usado.
    tipoDataHora Data_Hora_Prestamo;    //A data e hora do Pedido de Emprestimo.
    char Campus_Origen_Prestamo;        //Origen do Pedido de Emprestamo.
    char Campus_Destino_Prestamo;       //Destino do Pedido de Emprestamo.

} tipoPrestamo;

typedef struct {

    int designacaoBicicleta;        //A Desgignacao (ID) da Bicicleta que foi usada.
    int distanciaPercorrida;        //A distancia Percorrida ate aquele momento pela Bicicleta.
    tipoDataHora DataEHora;         //A data e Hora da Avaria,
    char Descricao[50];             //O comentario sobre a Avaria.

} tipoAveria;

#endif // ESTRUTURAS_H_INCLUDED
