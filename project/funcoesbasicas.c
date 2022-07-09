#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesbasicas.h"
#include "funcoes_bicicletas.h"
#include "funcoes_utentes.h"
#include "funcoes_emprestimos.h"
#include "funcoes_lista.h"
#include "funcoes_adicionales.h"

void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d): ", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)
        if (controlo == 0)
        {
            printf("Insera um numero inteiro porfavor.\n");
        }
        else
        {
            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido.\n");
            }
        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);
    return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        //   puts(mensagem);
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
        {
            limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
        }
        else
        {
            vetorCaracteres[tamanhoString-1] ='\0';          //substitui \n da string armazenada em vetor por \0
        }
        if (tamanhoString == 1)
        {
            printf("\nNao foram introduzidos caracteres. Insera de novo porfavor.");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    }
    while (tamanhoString == 1);
}

void lerDataHora(tipoDataHora *Dados, char texto[MAX_STRING])
{

    printf("%s\n",texto);       //Imprime o Texto que foi enviado.

    Dados->ano=lerInteiro("Ano: ",2018,2020);       //Le o Ano
    Dados->mes=lerInteiro("Mes: ",1,12);            //Le o Mes

    if (Dados->mes==2)      //Se o Mes fosse Fevereiro
    {
        Dados->dia=lerInteiro("Dia: ",1,28);    //Só da para inserir ate o dia 28.
    }
    else
    {
        if (Dados->mes ==1 || Dados->mes ==3 || Dados->mes ==5 || Dados->mes ==7 || Dados->mes ==8 || Dados->mes ==10 || Dados->mes ==12)
        {
            Dados->dia = lerInteiro("Dia: ",1,31);      //Se o Mes fosse de 31 dias, da para escrever isso.
        }
        else
        {

            Dados->dia = lerInteiro("Dia: ",1,30);      //Se o Mes fosse de 30 dias, só permite inserir até 30.
        }
    }

    Dados->hora=lerInteiro("Hora: ",0,23);  //Le a hora.

    //Funçao que Le a Data e Hora.
}

void imprimirProfesion(char texto[MAX_STRING],char opcionEscogida)
{
    printf("%s",texto);
    switch(opcionEscogida)
    {
    case 'E':
        printf("Estudiante.");
        break;
    case 'D':
        printf("Docente.");
        break;
    case 'T':
        printf("Tecnico Administrativo.");
        break;
    case 'C':
        printf("Convidado.");
        break;
    }
    //Funçao Auxiliar que dependendo da opcao, da para escrever a opçao de uma maneira melhor.
}

void imprimirCampus(char texto[MAX_STRING],char opcionEscogida)
{
    printf("%s",texto);
    switch(opcionEscogida)
    {
    case '1':
        printf("Campus 1 (ESECS).");
        break;
    case '2':
        printf("Campus 2 (ESTG).");
        break;
    case '5':
        printf("Campus 5.");
        break;
    case 'R':
        printf("Residencias.");
        break;
    }
    //Funçao Auxiliar que dependendo da opcao, da para escrever a opçao de uma maneira melhor.
}

void imprimirData(char texto[MAX_STRING],tipoDataHora dados)
{

    printf("%s\n",texto);
    printf("\tAno: %d\t",dados.ano);
    printf("Mes: %d\t",dados.mes);
    printf("Dia: %d\t",dados.dia);
    printf("Hora: %d\n",dados.hora);

    //Funçao Auxiliar que imprime a Data
}

int lerDistancia(char campusDestino,char campusOrigen)
{

    int numero,origen,destino,minimo;

    switch (campusOrigen)   //Dependendo do Campus de Origem, da um numero à varivel origem.
    {
    case 'R':
        origen=DISTANCIA_R;
        break;
    case '1':
        origen=DISTANCIA_1;
        break;
    case '2':
        origen=DISTANCIA_2;
        break;
    case '5':
        origen=DISTANCIA_5;
        break;
    }

    switch (campusDestino)   //Dependendo do Campus Destino, da um numero à varivel destino.
    {
    case 'R':
        destino=DISTANCIA_R;
        break;
    case '1':
        destino=DISTANCIA_1;
        break;
    case '2':
        destino=DISTANCIA_2;
        break;
    case '5':
        destino=DISTANCIA_5;
        break;
    }

    minimo=abs(destino-origen);     //Calcula a resta, como um valor absoluto para não ter valores negativos.
                    //E assim temos uma distância minima que o utilizador pode inserir.

    numero=lerInteiro("\nInsera a Distancia Percorrida: ",minimo,MAX_DISTANCIAS);   //Embora o Utilizador possa escrever a distância que percorreu; tem valor minimo.

    return numero;

    //Funçao Auxiliar que le as Distâncias.
}
