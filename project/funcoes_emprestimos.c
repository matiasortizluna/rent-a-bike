#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constantes.h"
#include "estruturas.h"

#include "funcoesbasicas.h"
#include "funcoes_bicicletas.h"
#include "funcoes_utentes.h"
#include "funcoes_emprestimos.h"
#include "funcoes_lista.h"
#include "funcoes_adicionales.h"

char menuPrestamos1()
{
    char opcao;
    do
    {
        printf("\n----------Menu Emprestimos----------\n");
        printf("(N)ovo Pedido de Emprestimo.\n");
        printf("(C)onsultar um Elemento de Emprestimo.\n");
        printf("(M)ostrar Lista de  Emprestimos.\n");

        printf("\n(V)oltar ao Menu Principal.\n");

        printf("Opcao -> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='N' && opcao!='C' && opcao!='M' && opcao!='V')
        {
            printf("Insera um caracter valido porfavor.\n");
        }

    }
    while (opcao!='N' && opcao!='C' && opcao!='M' && opcao!='V');

    return opcao;
}

int acrescentarNumeroRegistro (int codigo)
{
    codigo++;
    return codigo;      //Funçao Auxiliar que acrescenta o Numero Registro sempre for preciso.
}

void Mostrar_Dados_Emprestimos(tipoPrestamo dados[],int Cantidad_Emprestimos)
{
    int conta;
    if (Cantidad_Emprestimos>0)
    {
        for (conta=0; conta<Cantidad_Emprestimos; conta++)
        {
            printf("\n----------------------------------------\n");
            printf("\nNumero de Registro : %d",dados[conta].Numero_Registro);
            printf("\n\n ID Utente: %d",dados[conta].ID_Utente_Reserva);
            imprimirCampus("\t\t\t\tCampus Origen: ",dados[conta].Campus_Origen_Prestamo);
            printf("\n Designacao da Bicicleta: %d",dados[conta].ID_Bicicleta_Reserva);
            imprimirCampus("\t\tCampus Destino: ",dados[conta].Campus_Destino_Prestamo);
            imprimirData("\n\n Data e Hora de Emprestimo: ",dados[conta].Data_Hora_Prestamo);

        }
    }
    else
    {
        printf("\nNao tem dados.\n");
    }
}

void consultarDadosPrestamo(tipoPrestamo dados[],int CantidadPrestamos)
{
    int IDpreciso;
    int posicao;

    if (CantidadPrestamos>0)
    {
        posicao=procuraNumeroRegistro_paraPrestamos("\nDigite o Numero de Registro do Emprestimo que precisa informacao: ",dados,CantidadPrestamos,&IDpreciso);

        if (posicao!=-1)        //Se o Numero de Registro inserido, existir, apresenta a Informaçao.
        {
            printf("\n----------------------------------------\n");
            printf("\nNumero de Registro : %d",dados[posicao].Numero_Registro);
            printf("\n\n ID Utente: %d",dados[posicao].ID_Utente_Reserva);
            printf("\n\n ID Bicicleta: %d",dados[posicao].ID_Bicicleta_Reserva);
            imprimirCampus("\t\t\t\tCampus Origen: ",dados[posicao].Campus_Origen_Prestamo);
            printf("\n Designacao da Bicicleta: %d",dados[posicao].ID_Bicicleta_Reserva);
            imprimirCampus("\t\tCampus Destino: ",dados[posicao].Campus_Destino_Prestamo);
            imprimirData("\n\n Data e Hora de Emprestimo: ",dados[posicao].Data_Hora_Prestamo);
        }
        else
        {
            printf("\nNao encontram-se Emprestimo com esse Numero de Registro.\n");
        }
    }
    else
    {
        printf("\nNao tem dados.\n");
    }
}

int procuraNumeroRegistro_paraPrestamos(char texto[MAX_STRING],tipoPrestamo Prestamos[],int cantidadPrestamos,int *numeroRegistroPreciso)
{

    int conta;
    int posicao=-1;

    *numeroRegistroPreciso=lerInteiro(texto,1000,1200);

    for (conta=0; conta<cantidadPrestamos; conta++)
    {
        if (*numeroRegistroPreciso==Prestamos[conta].Numero_Registro)   //Compara o Numero de Registro preciso, com Numero de Registro dos outros Pedidos de Emprestimos
                                                                    //Que estam na Lista de Emprestimos.
        {
            posicao=conta;              //Guarda-se a posiçao onde for encontrados.

        }
    }

    return posicao;
}

char menuDevolucionBicicleta()
{

    char opcao;
    do
    {
        printf("\nGostaria Devolver a Bicicleta?\n");
        printf("(S)im.\n");
        printf("(N)ao.\n");
        printf("Opcao -> ");

        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='S' && opcao!='N')
        {
            printf("Insera um caracter valido porfavor.\n");
        }
    }
    while (opcao!='S' && opcao!='N');

    return opcao;
                    //Menu que pregunta se o Utente quer devolver a Bicicleta.
}

char estadoDevolucionBicicleta()
{

    char opcao1;
    char caracter='\0';

    opcao1=menuDevolucionBicicleta();

    switch(opcao1)
    {

    case 'S':           //Se a resposta fosse sim, retorna o caracter D. de Disponivel.
        caracter='D';
        break;
    case 'N':           //Se a resposta fosse não, retorna o caracter E. de Emprestada
        caracter='E';
        break;
    }

    return caracter;
}

int asignacaoBicicleta(int Quantidade_Bicicletas,tipoBicicleta Bicicletas[],char campusOrigen)
{
    int numeroID=0;
    int conta;

    for (conta=0; conta<Quantidade_Bicicletas; conta++)     //Compara se o Campus de Origem enviada, e igual que o Campus de Origem das Bicicletas.
    {
        if(campusOrigen == Bicicletas[conta].Campus_Origen_Bicicleta)   //Se fosse, também é preciso saber se estam disponiveis, então faz-se isso.
        {
            if (Bicicletas[conta].Estado_Bicicleta=='D')    //Se a Bicicleta pretendida estivera Disponivel...
            {
                numeroID=Bicicletas[conta].ID_Bicicleta;        //Guarda-se o seu ID numa variavel especifica.
                Bicicletas[conta].Estado_Bicicleta='E';         //O estado da Bicicleta muda para Emprestada.
                conta=Quantidade_Bicicletas;                    //Termina a procura.
            }
        }
    }
    return numeroID;    //Retorna se o ID da Bicicleta pretendida.
}

void gravarFicheiroDadosPrestamos (tipoPrestamo Prestamos[], int quant)
{
    int erro;
    FILE *ficheiro;

    ficheiro=fopen("dadosPrestamos.dat","wb");
    if (ficheiro== NULL)
    {
        printf("Ficheiro Inesistente\n");
    }
    else
    {
        fwrite(&quant,sizeof(int),1,ficheiro);
        fwrite(Prestamos,sizeof(tipoPrestamo),quant,ficheiro);
        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf ("Erro %d no fecho ficheiro\n", erro);
        }
    }
    //Grava os dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso
}

tipoPrestamo  *leFicheiroDadosPrestamos (tipoPrestamo Prestamos[],int *quant)
{
    FILE *ficheiro;

    ficheiro=fopen("dadosPrestamos.dat","rb");
    if (ficheiro== NULL)
    {
        printf("Ficheiro Inesistente\n");
        free(Prestamos);
        Prestamos=NULL;
        *quant=0;
    }
    else
    {

        fread(&(*quant),sizeof(int),1,ficheiro);
        Prestamos=realloc(Prestamos,(*quant)*sizeof(tipoPrestamo));
        if (Prestamos == NULL && *quant !=0)
        {

            printf("Error ler o ficheiro\n");
            *quant=0;

        }
        else
        {

            fread(Prestamos,sizeof(tipoPrestamo),*quant,ficheiro);
            fclose(ficheiro);
        }
    }
    return Prestamos;       //Retorna um vetor, porque ao ser um vetor dinamico, há mudanças dentro da funçao que tem que ter efeito também afora dela.

      //Leitura dos dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso.

}

void leDadosPedidoEmprestimo (tipoPrestamo *Prestamos, int numeroRegistro,int IDUtente,char TipoUtente)
{

    Prestamos->Numero_Registro=numeroRegistro;      //Agrega-se o Numero de Registro respectivo.

    Prestamos->ID_Utente_Reserva = IDUtente;        //Agrega-se o ID do Utente que esta a fazer o Pedido de Emprestimo

    Prestamos->Tipo_Utente_Reserva = TipoUtente;    //Agrefa-se o Tipo/Profesion do Utente respectivo

    lerDataHora(&Prestamos->Data_Hora_Prestamo,"Insera a Data e Hora de Emprestimo: ");     //A data e Hora de Emprestimo.

    Prestamos->Campus_Origen_Prestamo = menuCampus1("Campus Origen: ");

    do
    {

        Prestamos->Campus_Destino_Prestamo = menuCampus1("Campus Destino: ");

        if (Prestamos->Campus_Destino_Prestamo==Prestamos->Campus_Origen_Prestamo)
        {

            printf("\nNao pode inserir o mesmo Campus de Destino.\n");

        }   //Volta a preguntar por o Campus de Destino, se for iguais.

    }
    while(Prestamos->Campus_Destino_Prestamo==Prestamos->Campus_Origen_Prestamo);

    Prestamos->ID_Bicicleta_Reserva = 0;    //Dados inicializados a 0.

    //Funçao que le os Dados de um Novo Pedido de Emprestimo.
}

tipoPrestamo *eliminaElementoPrestamo(tipoPrestamo *Prestamos,int *cantidad,int posicaoEliminar)
{
    int conta;

    if (posicaoEliminar!=-1)
    {
        for (conta=posicaoEliminar; conta<(*cantidad); conta++)
        {
            Prestamos[conta] = Prestamos[conta+1];  //Desaparecem os dados do Emprestimo que quere ser eliminado, e é adicionado os dados do seguinte
                                                    // e assim até chegar ao final
        }

        (*cantidad)--;      //Resta-se 1, à quantidade de elementos na Lista de Emprestimos.
        Prestamos = realloc(Prestamos,(*cantidad)*sizeof(tipoPrestamo));    //Faz-se um realloc porque a quantiadade de Pedidos de Emprestimos, mudou.
    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    return Prestamos;       //Retorna o vetor, ao ser um ponteiro e variavel dinamica é preciso, para não ter problemas de perdida de informçao.
}
