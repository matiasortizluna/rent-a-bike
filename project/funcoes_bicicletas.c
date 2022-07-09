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

char menuBicicletas1()
{
    char opcao;
    do
    {
        printf("\n----------Menu Bicicletas----------\n");
        printf("(I)nserir dados das bicicletas.\n");
        printf("(C)onsultar Info Bicicleta.\n");
        printf("(M)ostrar Dados das Bicicletas.\n");
        printf("(A)crescentar Bicicleta.\n");
        printf("(R)eparar Bicicleta.\n");
        printf("\n(V)oltar ao Menu Principal.\n");

        printf("Opcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='I' && opcao!='C' && opcao!='M' && opcao!='A' && opcao!='R'&& opcao!='V')
        {
            printf("Insera uma opcao valida.\n");
        }
    }
    while (opcao!='I' && opcao!='C' && opcao!='M' && opcao!='A' && opcao!='R' && opcao!='V');

    return opcao;
}

char Menu_Estado_Bicicleta()
{
    char opcao;
    do
    {
        printf("\nIndique el estado de la bicicleta: ");
        printf("\n(D)isponible.");
        printf("\n(E)mprestada.");
        printf("\n(A)variada");

        printf("\nOpcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);

        limpaBufferStdin();

        if (opcao!='D' && opcao!='E' && opcao!='A')
        {
            printf("Insera uma opcao valida\n");
            }
    }
    while (opcao!='D' && opcao!='E' && opcao!='A');

    return opcao;
}

int procura_ID_Bicicleta(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas,int numedeprocu)
{
    int conta,posicao=-1;

    for (conta=0; conta<Quantidade_Bicicletas; conta++)
    {
        if (numedeprocu==dados[conta].ID_Bicicleta)
        {
            posicao=conta;                  // Guarda a posicao do vetor onde esta o ID que esta a procura.
            conta=Quantidade_Bicicletas;    //Deixa de procurar pelo ID da bicicleta.
        }
    }
    return posicao;     //Se ninguém tem esse numero, retorna -1
}

int ler_ID_Bicicleta(char texto[MAX_STRING],int minimo, int maximo,tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas)
{
    int numprocu;
    int posicao;
    do
    {
        numprocu=lerInteiro(texto,minimo,maximo);
        posicao=procura_ID_Bicicleta(dados,Quantidade_Bicicletas,numprocu);
        if (posicao==-1)
        {
            printf("Ninguem tem esse numero. Prosiga.\n");
        }
        else
        {
            printf("Ja existe esse numero. Tente novamente.\n");
        }               //Se o Numero introduzido já existe, então permite que o Utilizador insere novamente.
    }
    while (posicao!=-1);

    return numprocu;
}

void imprimirEstadoBicicleta(char text[MAX_STRING],char opcionEscogida)
{
    printf("%s",text);
    switch(opcionEscogida)
    {
    case 'D':
        printf("Disponivel.");
        break;
    case 'E':
        printf("Emprestada.");
        break;
    case 'A':
        printf("Averiada.");
        break;
    }       //Funçao auxiliar para transformar um caracter em texto, com o objetivo que seja mais facil para o Utilizador perceber a informaçao
            // apresentada no ecrã.
}

void lerDadosBicicletas(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas)
{
    int conta,elemento;

    //Elemento = Elemento que vamos inserir     Conta=Posiçao do vetor Bicicletas(dados)

    for (conta=0; conta<Quantidade_Bicicletas; conta++)
    {
        elemento=conta+1;
        printf("\n%d. ",elemento);
        dados[conta].ID_Bicicleta = ler_ID_Bicicleta("Insera o ID da Bicicleta: ",1,15,dados,Quantidade_Bicicletas);
        dados[conta].Estado_Bicicleta = Menu_Estado_Bicicleta();
        dados[conta].Campus_Origen_Bicicleta = menuCampus1("Campus Origen Bicicleta: ");
        lerString("\nInsera o modelo da bicicleta: ",dados[conta].Modelo_Bicicleta,20);
        dados[conta].Prestamos_Bicicleta=0;
        dados[conta].Distancia_Total=0;
        dados[conta].Vezes_Averias=0;       // Estos dados são inicializados a 0.
        dados[conta].Vezes_Reparada=0;
    }
}

void Mostrar_Dados_Bicicletas(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas)
{
    int conta;

    if (Quantidade_Bicicletas>0)
    {
        for (conta=0; conta<Quantidade_Bicicletas; conta++)
        {
            printf("\nID Bicicleta: %d",dados[conta].ID_Bicicleta);
            imprimirEstadoBicicleta("\t\tEstado da bicleta: ",dados[conta].Estado_Bicicleta);
            printf("\tPrestamos Feitos: %d",dados[conta].Prestamos_Bicicleta);
            imprimirCampus("\tCampus Origen Bicicleta: ",dados[conta].Campus_Origen_Bicicleta);
            printf("\nModelo da Bicicleta: %s",dados[conta].Modelo_Bicicleta);
            printf("\tDistancia Percorrida: %d km",dados[conta].Distancia_Total);
            printf("\t\tAverias da Bicicleta: %d",dados[conta].Vezes_Averias);
            printf("\tReparaciones da Bicicleta: %d\n",dados[conta].Vezes_Reparada);
        }
    }
    else
    {
        printf("\nNao tem dados.\n");
    }
}

void gravarFicheiroDadosBicicleta (tipoBicicleta vBicicleta[MAX_BICICLETAS], int quant)
{
    int error;
    FILE *ficheiro;

    ficheiro=fopen("dadosBicicleta.dat","wb");
    if (ficheiro== NULL)
    {
        printf("\nNao existe o Ficheiro.\n");
    }
    else
    {
        fwrite(&quant,sizeof(int),1,ficheiro);
        fwrite(vBicicleta,sizeof(tipoBicicleta),quant,ficheiro);
        error = fclose(ficheiro);
        if (error != 0)
        {
            printf ("\nError %d no fecho de ficheiro.\n", error);
        }
    }
    //Grava os dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso
}

void  leFicheiroDadosBicicleta (tipoBicicleta vBicicleta[MAX_BICICLETAS],int *quant)
{
    int error;
    FILE *ficheiro;

    ficheiro=fopen("dadosBicicleta.dat","rb");
    if (ficheiro== NULL)
    {
        printf("\nNao existe o Ficheiro.\n");
    }
    fread(quant,sizeof(int),1,ficheiro);
    fread(vBicicleta,sizeof(tipoBicicleta),*quant,ficheiro);
    error=fclose(ficheiro);
    if (error!= 0)
    {
        printf("\nError %d em fecho de ficheiro.\n",error);
    }
}    //Leitura dos dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso.

void acresentarBicicleta (tipoBicicleta dados[MAX_BICICLETAS],int *Quantidade_Bicicletas)
{

    if (*Quantidade_Bicicletas==MAX_BICICLETAS)
    {
        printf("\nOperacao Invalida. Nao e posivel acrescentar mais bicicletas.\n");
    //Impossível Acrescentar mais Bicicletas se já se alcanzou o limite.
    }
    else
    {

        printf("\n%d. ",(*Quantidade_Bicicletas)+1);
        dados[*Quantidade_Bicicletas].ID_Bicicleta=ler_ID_Bicicleta("Insera o ID da Bicicleta: ",1,MAX_BICICLETAS,dados,*Quantidade_Bicicletas);
        dados[*Quantidade_Bicicletas].Estado_Bicicleta = Menu_Estado_Bicicleta();
        dados[*Quantidade_Bicicletas].Campus_Origen_Bicicleta = menuCampus1("Campus Origen Bicicleta: ");
        lerString("\nInsera o modelo da bicicleta: ",dados[*Quantidade_Bicicletas].Modelo_Bicicleta,20);
        dados[*Quantidade_Bicicletas].Prestamos_Bicicleta=0;
        dados[*Quantidade_Bicicletas].Distancia_Total=0;        //Dados inicializados a 0 igualmente.
        dados[*Quantidade_Bicicletas].Vezes_Averias=0;
        dados[*Quantidade_Bicicletas].Vezes_Reparada=0;
        (*Quantidade_Bicicletas)++;                         //Acrescenta a quantidade das Bicicletas.
    }
}

void consultarDadosBicicleta(tipoBicicleta dados[MAX_BICICLETAS],int Quantidade_Bicicletas)
{
    int IDpreciso;
    int posicao;
    if (Quantidade_Bicicletas>0)
    {

        IDpreciso=lerInteiro("\nDigite o ID da Bicicleta que precisa informacao: ",1,MAX_BICICLETAS);
        posicao=procura_ID_Bicicleta(dados,Quantidade_Bicicletas,IDpreciso);

        if (posicao!=-1)
        {
            printf("\nID Bicicleta: %d",dados[posicao].ID_Bicicleta);
            imprimirEstadoBicicleta("\t\tEstado da bicleta: ",dados[posicao].Estado_Bicicleta);
            imprimirCampus("\tCampus Origen Bicicleta: ",dados[posicao].Campus_Origen_Bicicleta);
            printf("\nModelo da Bicicleta: %s",dados[posicao].Modelo_Bicicleta);
            printf("\tEmprestimos Feitos: %d",dados[posicao].Prestamos_Bicicleta);
            printf("\tDistancia Percorrida: %d km",dados[posicao].Distancia_Total);
            printf("\tAvarias da Bicicleta: %d\n",dados[posicao].Vezes_Averias);
        }
        else
        {

            printf("\nNao encontram-se dados sobre essa Bicicleta.\n");

        }

    }
    else
    {
        printf("\nNao tem dados.\n");
    }
}

void repararBicicleta(tipoBicicleta Bicicletas[],int cantidadBicicletas)
{

    int numprocu;
    int posicao;

    if (cantidadBicicletas>0)
    {
        numprocu=lerInteiro("\nDigite o ID da Bicicleta que quere reparar: ",1,MAX_BICICLETAS);
        posicao=procura_ID_Bicicleta(Bicicletas,cantidadBicicletas,numprocu);

        if (posicao!=-1)
        {

            if(Bicicletas[posicao].Estado_Bicicleta=='A')   //No caso que emcomtre-se a Bicicleta, verfica-se também se precisa de uma reparaçao.
            {
                Bicicletas[posicao].Vezes_Reparada++;       //Acrescenta a quantidade de Vezes Reparada.
                Bicicletas[posicao].Estado_Bicicleta = 'D'; //Muda o estado da Bicicleta para ªDisponivelª
                printf("\nOperacao Feita.\n");          //Da aviso ao Utilizador
            }
            else
            {
                printf("\nOperacao Cancelada.\nA Bicicleta nao esta Averiada.\n");  //Se o ID existesse, mas não é preciso reparar.
            }

        }
        else
        {

            printf("\nNao existe essa Bicicleta.\n");
        }
    }
}

int QuaantidadeBicletasDisponibles(int Quantidade_Bicicletas,char CampusOrigenPrestamo,tipoBicicleta Bicicletas[])
{
    int conta;
    int bicicletasDisponibles=0;

    for(conta=0; conta<Quantidade_Bicicletas; conta++)
    {
        if(CampusOrigenPrestamo == Bicicletas[conta].Campus_Origen_Bicicleta)   // Se o Campus de Origem é igual
        {
            if (Bicicletas[conta].Estado_Bicicleta=='D')    //E se a Bicicleta esta disponivel.
            {
                bicicletasDisponibles++;    // só nesse caso, acrescenta a quantidade das Bicicletas Disponiveis.
            }
        }
    }
    return bicicletasDisponibles;
}

char Menu_Estado_Avaria()
{
    char opcao;
    do
    {
        printf("\nA Bicicleta sufrio alguma avaria? ");
        printf("\n(S)im.");
        printf("\n(N)ao.");

        printf("\nOpcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);

        limpaBufferStdin();

        if (opcao!='S' && opcao!='N')
        {
            printf("Insera uma opcao valida\n");
                }
    }
    while (opcao!='S' && opcao!='N');

    //Menu que pregunta ao Utilizador se a Bicicleta sufriu alguma averia.

    return opcao;
}

tipoAveria lerDadosAveria(int BicicletaUsada, int distanciaAteEsseMomento)
{

    tipoAveria NovosDados;

    NovosDados.designacaoBicicleta = BicicletaUsada;        //Damos o Numero da Bicicleta Usada, que, esta Averiada.

    NovosDados.distanciaPercorrida = distanciaAteEsseMomento;   //Damos o valor da Distancia Percorrida até esse momento,

    lerDataHora(&(NovosDados.DataEHora),"Insera a Data e Hora de Avaria: ");

    lerString("Comentario:",NovosDados.Descricao,MAX_DESCRIPCION);  //Comentario sobre a Avaria

    return NovosDados;
}

void escreveFichTextoAverias(tipoAveria Averias[], int cantidadAverias)
{
    FILE *fich;
    int i;
    fich = fopen("averias.txt","w");
    if (fich == NULL)
    {
        printf ("\nError abrir ficheiro Averias\n");
    }
    else
    {
        fprintf(fich,"\nNova Escrita.\n");
        fprintf(fich,"Total Averias: %d", cantidadAverias);
        for (i=0; i<cantidadAverias; i++)
        {
            fprintf(fich,"\n-----------\n");
            fprintf(fich,"Designacao Bicicleta: %d\n",Averias[i].designacaoBicicleta);
            fprintf(fich,"Comentario: %s\n",Averias[i].Descricao);
            fprintf(fich,"Distancia Percorrida: %d\n",Averias[i].distanciaPercorrida);
            fprintf(fich,"Data e Hora da Averia: \n");
            fprintf(fich,"Dia: %d\t",Averias[i].DataEHora.dia);
            fprintf(fich,"Mes: %d\t",Averias[i].DataEHora.dia);
            fprintf(fich,"Ano: %d\t",Averias[i].DataEHora.ano);
            fprintf(fich,"Hora: %d\n",Averias[i].DataEHora.hora);

        }
        fclose(fich);
    }
    //Escreve um Ficheiro de Texto sobre as Averias. (no formato requerido)
}

void UltimaBicicleta(tipoUtente Utentes[],int Quantidade_Utente,tipoBicicleta Bicicletas[],int Quantidade_Bicicletas,tipoPrestamo Historico[],int historioPres)
{

    int conta;
    int posicaoUtente;
    int posicaoHistorico;
    int numprocu;
    int posicaoBicicleta;

    if(Quantidade_Utente>0) //Só se há Utentes entra.
    {
        numprocu=lerInteiro("\nInsera o ID do Utente que precisa informacao: ",1,MAX_ID_UTENTES);
        posicaoUtente=procura_ID_Utente(Utentes,Quantidade_Utente,numprocu);

        if (posicaoUtente==-1)
        {
            printf("Ninguem tem esse numero. Tente Novamente.\n");
        }
        else
        {
            if (historioPres>0 && Quantidade_Bicicletas>0) //Só se há dados de Emroestimos que já terminarom e dados de Bicicletas entra.
            {

                for(conta=0; conta<historioPres; conta++)
                {
                    if (Utentes[posicaoUtente].ID_Utente==Historico[conta].ID_Utente_Reserva)   //Compara se o Utente requerido é igual
                                                                                                //ao Utente de algum Emprestimo.
                    {
                        posicaoHistorico=conta; //Se é, pois guarda-se a sua posiçao, se encontra-se um novo Emprestimo, a posiçao muda.

                    }
                    //Como a Estrutura Historico, guarda os Emprestimos que foram terminados, então os ultimos emprestimos vam ter a informaçao sobre a
                    // ultima Bicicleta.
                }


            for(conta=0; conta<Quantidade_Bicicletas; conta++)
            {

                if (Historico[posicaoHistorico].ID_Bicicleta_Reserva==Bicicletas[conta].ID_Bicicleta)   //Compara o ID da Bicicleta no Emprestimo com os dados das
                                                                                                        //Bicicletas para determinar a posiçao no vetor Bicicletas
                {

                    posicaoBicicleta=conta;     //Guarda-se a posiçao.

                }
            }

            printf("\nA ultima Bicicleta Utilizada por Utente %d, com Numero Registro %d, foi: \n",Utentes[posicaoUtente].ID_Utente,Historico[posicaoHistorico].Numero_Registro);

        //Agora que temos a posiçao no vetor de Bicicletas, então podemos apresentar os seus dados no ecrã.

            printf("\nID Bicicleta: %d",Bicicletas[posicaoBicicleta].ID_Bicicleta);
            imprimirEstadoBicicleta("\t\tEstado da bicleta: ",Bicicletas[posicaoBicicleta].Estado_Bicicleta);
            imprimirCampus("\tCampus Origen Bicicleta: ",Bicicletas[posicaoBicicleta].Campus_Origen_Bicicleta);
            printf("\nModelo da Bicicleta: %s",Bicicletas[posicaoBicicleta].Modelo_Bicicleta);
            printf("\tPrestamos Feitos: %d",Bicicletas[posicaoBicicleta].Prestamos_Bicicleta);
            printf("\tDistancia Percorrida: %d km",Bicicletas[posicaoBicicleta].Distancia_Total);
            printf("\tAverias da Bicicleta: %d\n",Bicicletas[posicaoBicicleta].Vezes_Averias);

        }
        else{

        printf("\nNao tem dados de Emprestimos Registrados e/ou de Bicicletas.\n");

    }
        }
    }
    else
    {
        printf("\nNao tem dados de Utentes.\n");
    }

    //Funçao que apresenta os dados da Ultima Bicicleta Utilizada pelo Utente requerido pelo Utilizador.
}
