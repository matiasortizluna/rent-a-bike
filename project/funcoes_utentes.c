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

int procura_ID_Utente(tipoUtente dados[MAX_UTENTES],int Quantidade_Utentes,int numedeprocu)
{
    int conta,posicao=-1;

    for (conta=0; conta<Quantidade_Utentes; conta++)
    {
        if (numedeprocu==dados[conta].ID_Utente)
        {
            posicao=conta;                      //Guarda a posicao do vetor onde esta o ID que esta a procura.
            conta=Quantidade_Utentes;            //Deixa de procurar pelo ID.
        }
    }
    return posicao;
}

int ler_ID_Utente(char texto[MAX_STRING],int minimo, int maximo,tipoUtente dados[MAX_UTENTES],int Quantidade_Utentes)
{
    int numprocu;
    int posicao;

    do
    {
        numprocu=lerInteiro(texto,minimo,maximo);
        posicao=procura_ID_Utente(dados,Quantidade_Utentes,numprocu);
        if (posicao==-1)
        {
            printf("Ninguem tem esse numero. Prosiga.\n");
        }
        else
        {
            printf("Ja existe esse numero. Tente novamente.\n");
                                //Se o Numero introduzido já existe, então permite que o Utilizador insere novamente.
        }
    }
    while (posicao!=-1);

    return numprocu;
}

char Menu_Utentes_Profesion()
{
    char opcao;             //Pregunta pela Porfesion de um Utente.
    do
    {
        printf("Indique sua profesion: \n");
        printf("(E) Estudante.\n");
        printf("(D) Docente.\n");
        printf("(T) Tecnico Administrativo.\n");
        printf("(C) Convidado.\n");

        printf("Opcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='E' && opcao!='D' && opcao!='T' && opcao!='C')
        {
            printf("Insera um caracter valido porfavor.\n\n");
        }

    }
    while (opcao!='E' && opcao!='D' && opcao!='T' && opcao!='C');

    return opcao;
}

void Mostrar_Dados_Utentes(tipoUtente Utentes[MAX_UTENTES],int Quantidade_Utentes)
{
    int conta;
    if (Quantidade_Utentes>0)
    {
        for (conta=0; conta<Quantidade_Utentes; conta++)
        {
            printf("\nID: %d",Utentes[conta].ID_Utente);
            printf("\t\tNome: %s",Utentes[conta].Nome_Utente);
            printf("\nTelephone: %d",Utentes[conta].Numero_Telefono);
            imprimirProfesion("\t\tTipo/Profesion: ",Utentes[conta].Profesion);
            printf("\nPrestamos Feitos: %d",Utentes[conta].QuantidadePrestamos_Feitos);
            printf("\tDistancia Percorrida: %d km\n",Utentes[conta].DistanciaTotal_Recorrida);
        }
    }
    else
    {
        printf("\nNao tem dados.\n");
    }
}

void gravarFicheiroDadosUtentes (tipoUtente vUtentes[MAX_UTENTES], int Quantidade_Utentes)
{
    int error;
    FILE *ficheiro;

    ficheiro=fopen("dadosUtentes.dat","wb");
    if (ficheiro== NULL)
    {
        printf("Ficheiro Inexistente\n");
    }
    else
    {
        fwrite(&Quantidade_Utentes,sizeof(int),1,ficheiro);
        fwrite(vUtentes,sizeof(tipoUtente),Quantidade_Utentes,ficheiro);
        error = fclose(ficheiro);
        if (error != 0)
        {
            printf ("Error %d no fecho ficheiro\n", error);
        }
    }
    //Grava os dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso
}

void  leFicheiroDadosUtentes (tipoUtente vUtente[MAX_UTENTES],int *Quantidade_Utentes)
{
    int error;
    FILE *ficheiro;

    ficheiro=fopen("dadosUtentes.dat","rb");
    if (ficheiro== NULL)
    {
        printf("Ficheiro Inexistente\n");
    }
    fread(Quantidade_Utentes,sizeof(int),1,ficheiro);
    fread(vUtente,sizeof(tipoUtente),*Quantidade_Utentes,ficheiro);
    error=fclose(ficheiro);
    if (error!= 0)
    {
        printf("Error %d em fecho de fichiro\n",error);
    }
      //Leitura dos dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso.
}

tipoUtente lerDadosDeNovoUtente(tipoUtente Utentes[],int Quantidade_Utentes)
{
    tipoUtente UtenteNovo;


    if (Quantidade_Utentes==MAX_UTENTES)
    {
        printf("\nOperacao Invalida. Nao e posivel acrescentar Utentes.\n");
    //Impossível Acrescentar mais Utentes se já se alcanzou o limite.
    }
    else
    {
    printf("\n----------Novo Utente----------\n");

    UtenteNovo.ID_Utente = ler_ID_Utente("Ler ID de novo Utente: ",1,MAX_ID_UTENTES,Utentes,Quantidade_Utentes);
    lerString("Insera o nome do Utente: ",UtenteNovo.Nome_Utente,MAX_STRING);
    UtenteNovo.Numero_Telefono = lerInteiro("Insera o numero de telefono: ",1,MAX_TELEPHONE);
    UtenteNovo.Profesion = Menu_Utentes_Profesion();
    UtenteNovo.QuantidadePrestamos_Feitos=0;
    UtenteNovo.DistanciaTotal_Recorrida=0;      //Dados inicializados a 0.

    printf("\nUtente Novo Adicionado.\n");

    return UtenteNovo;

    }

}

char menuUtentes1()
{
    char opcao;
    do
    {
        printf("\n----------Menu Utentes----------\n");
        printf("(N)ovo Utente.\n");
        printf("(D)evolver a Bicicleta.\n");
        printf("(C)onsultar Info Utente.\n");
        printf("(M)ostrar os Dados dos Utentes.\n");        //Sub Menu de Utentes que apresenta as funcionalidades sobre os Utentes.
        printf("(E)ditar Utente.\n");
        printf("(A)pagar Utente.\n");
        printf("(U)ltima Bicicleta por Utente.\n");

        printf("\n(V)oltar ao Menu Principal.\n");

        printf("Opcao -> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='N' && opcao!='D' && opcao!='C' && opcao!='M' && opcao!='E' && opcao!='A' && opcao!='U' && opcao!='V')
        {
            printf("Insera um caracter valido porfavor.\n");
        }

    }
    while (opcao!='N' && opcao!='D' && opcao!='C' && opcao!='M' && opcao!='E' && opcao!='A' && opcao!='U' && opcao!='V');

    return opcao;
}

void editarUtente(tipoUtente Utentes[],int Quantidade_Utentes)
{
    int numedit;
    char opcao;
    int posicao;

    if (Quantidade_Utentes>0)           //Se há Utentes, entra
    {
            printf("\n----------Lista de Utentes Agora----------\n");       //Apresenta a Lista de Utentes nesse momento.
            Mostrar_Dados_Utentes(Utentes,Quantidade_Utentes);

            numedit=lerInteiro("\nInsere o ID do Utente que gostaria editar seus dados: ",1,MAX_ID_UTENTES);
            posicao=procura_ID_Utente(Utentes,Quantidade_Utentes,numedit);

            if(posicao!=-1)
            {
                        //Se o ID do Utente existe, entra.
                do
                {

                    do
                    {
                        printf("\nEDITAR: \n");
                        printf("(I)ID de Utente.\n");
                        printf("(N)Nome do Utente.\n");         //Da a opçao de Editar qualquer Informaçao.
                        printf("(T)Telephone.\n");
                        printf("(P)Tipo/Profesion.\n");
                        printf("\n(V)oltar ao Menu Utentes.\n");

                        printf("Opcao -> ");
                        scanf(" %c",&opcao);
                        opcao=toupper(opcao);
                        limpaBufferStdin();

                        if (opcao!='I' && opcao!='N' && opcao!='T' && opcao!='P' && opcao!='V')
                        {
                            printf("Insera um caracter valido porfavor.\n");
                        }
                    }
                    while (opcao!='I' && opcao!='N' && opcao!='T' && opcao!='P' && opcao!='V');

                    switch (opcao)      //Dependendo da Opçao Escohlida, permite editar os dados respectivos. Sempre apresentam-se os dados anteriores, e pregunta por os novos.
                    {
                    case 'I':
                        printf("\nID (Anterior): %d",Utentes[posicao].ID_Utente);
                        Utentes[posicao].ID_Utente=ler_ID_Utente("\tNovo ID: ",1,MAX_ID_UTENTES,Utentes,Quantidade_Utentes);
                        printf("\nOperacao Feita.\n");
                        break;
                    case 'N':
                        printf("\nNome (Anterior): %s",Utentes[posicao].Nome_Utente);
                        lerString("\tNovo Nome: ",Utentes[posicao].Nome_Utente,MAX_STRING);
                        printf("\nOperacao Feita.\n");
                        break;
                    case 'T':
                        printf("\nTelephone (Anterior): %d",Utentes[posicao].Numero_Telefono);
                        Utentes[posicao].Numero_Telefono=lerInteiro("\tNovo Telephone: ",1,MAX_TELEPHONE);
                        printf("\nOperacao Feita.\n");
                        break;
                    case 'P':
                        printf("\nTipo/Profesion (Anterior): %c",Utentes[posicao].Profesion);
                        printf("\nNovo Tipo/Profesion: \n");
                        Utentes[posicao].Profesion=Menu_Utentes_Profesion();
                        printf("\nOperacao Feita.\n");
                        break;
                    case 'V':
                        printf("\nVoltando para Menu Utentes.\n");      //Volta para o Menu de Utentes.
                        break;
                    }
                }
                while (opcao!='V');     //Não sai do SubMenu de Editar, até que escolha a opçao de Voltar.

            }
            else
            {
                printf("Nao existe esse funcionario.\nTente novamente porfavor.\n");
            }
    }
    else
    {
        printf("\nOperacao Invalida. Nao tem dados.\n");
    }
}

char menuAvisoDeSeguridadApagarUtente()
{
    char opcao;
    do
    {
        printf("\nCerteza gostaria eliminar?\n");
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
                            //Menu como ultima advertência, antes de Eliminar o Utente.
    return opcao;
}

void eliminaUtente(tipoUtente Utentes[], int *Quantidade_Utentes)
{
    int posicao;
    int conta;
    int numEliminar;
    char opcaoAvisoSeguridad;


    if (*Quantidade_Utentes>0)
    {

            printf("\n----------Lista de Utentes Agora----------\n");       //Mostra a Lista dos Utentes nesse momento.
            Mostrar_Dados_Utentes(Utentes,*Quantidade_Utentes);

            numEliminar=lerInteiro("\nInsera o numero ID do Utente que gostaria Eliminar.",1,MAX_ID_UTENTES);
            posicao=procura_ID_Utente(Utentes,*Quantidade_Utentes,numEliminar);

            if (posicao!= -1)               //Se o Utente existe, entra
            {
                opcaoAvisoSeguridad=menuAvisoDeSeguridadApagarUtente();     //Pregunta ao Utilizador, uma ultima vez

                switch (opcaoAvisoSeguridad)
                {
                case 'S':   //Se disse que sim, entra

                    for (conta=posicao; conta < *Quantidade_Utentes; conta++)       //A posiçao é a posiçao inicial.
                    {
                        Utentes[conta] = Utentes[conta+1];      //Desaparecem os dados do Utente que quere ser eliminado, e é adicionado os dados do seguinte
                    }                                           // e assim até chegar ao final

                    (*Quantidade_Utentes)--;                    //E assim os dados do ultimo utente não são precisos porque não há informação nosssa, então elimina-se uma posiçao.

                    printf("\nOperacao Feita.\n");

                    if (*Quantidade_Utentes>0)
                    {
                        printf("\n----------Lista de Utentes (Atualizada)----------\n");    //Se ainda há dados dos Utentes, os mostra.
                        Mostrar_Dados_Utentes(Utentes,*Quantidade_Utentes);
                    }

                    break;
                case 'N':
                    printf("\nOperacao Cancelada.\n");      //Se decidu cancelar a informaçao.

                    break;
                }
            }
            else
            {
                printf ("Nao existe esse funcionario.\nInsera de novo porfavor.\n");    //Se o Utente que pretende eliminar náo existesse.
            }
    }
    else
    {
        printf("\nOperacao Invalida. Nao tem dados.\n");
    }
}

void consultardadosUtente(tipoUtente dados[MAX_UTENTES],int Quantidade_Utentes)
{
    int IDpreciso;
    int posicao;
    if (Quantidade_Utentes>0)
    {
        IDpreciso=lerInteiro("\nDigite o ID do Utente que precisa informacao: ",1,MAX_ID_UTENTES);
        posicao=procura_ID_Utente(dados,Quantidade_Utentes,IDpreciso);                              //Procura o numero nos IDs dos Utentes

        if (posicao!=-1)           //Se o Utente, existir, apresenta a sua informaçao.
        {
            printf("\nID: %d",dados[posicao].ID_Utente);
            printf("\t\tNome: %s",dados[posicao].Nome_Utente);
            printf("\nTelephone: %d",dados[posicao].Numero_Telefono);
            imprimirProfesion("\t\tTipo/Profesion: ",dados[posicao].Profesion);
            printf("\nPrestamos Feitos: %d",dados[posicao].QuantidadePrestamos_Feitos);
            printf("\tDistancia Percorrida: %d km\n",dados[posicao].DistanciaTotal_Recorrida);
        }
        else
        {
            printf("\nNao encontram-se dados de esse Utente.\n");
        }
    }
    else
    {
        printf("\nNao tem dados.\n");
    }
}

int devolverBicicleta(tipoBicicleta Bicicletas[], tipoPrestamo Prestamos[],int Quantidade_Bicicletas,int cantidadPrestamos,tipoUtente Utentes[],int cantidadUtentes,int *distanciaTotal,int *estado,char *opcaoAvaria,int *posicaoBicicletaPrecisa)
{
    int Numprocura;
    int posicaoUtente;
    int posicaoPrestamo;
    int posicaoBicicleta;
    int distanciaPrestamo;
    char opcaoDevolucion;
    int posicionADevolver=-1;

    (*estado)=0;

    if (cantidadUtentes>0)  //Se a Quantidade de Utentes for maior que 0
    {
        Numprocura=lerInteiro("\nInsera o ID do Utente que quere operar: ",1,MAX_ID_UTENTES);
        posicaoUtente=procura_ID_Utente(Utentes,cantidadUtentes,Numprocura);

        if (posicaoUtente==-1)
        {
            printf("\nNinguem tem esse numero. Tente novamente.\n");
        }
        else         //Se a posiçao do Utente existir, entra
        {
            if (Quantidade_Bicicletas>0)    //Se a Quantidade de Bicicletas for maior que 0
            {
                if (cantidadPrestamos>0)    //Se a Quantidade de Pedidos em Lista de Emprestimos for maior que 0
                {
                    for(posicaoPrestamo=0; posicaoPrestamo<cantidadPrestamos; posicaoPrestamo++)    //Compara o ID verificado, com os Elementos da Lista de Emprestimos
                    {

                        if (Numprocura==Prestamos[posicaoPrestamo].ID_Utente_Reserva)     //Se fosse igual, entra
                        {

                            for(posicaoBicicleta=0; posicaoBicicleta<Quantidade_Bicicletas; posicaoBicicleta++)     //Compara o ID da Bicicleta do Elemento da Lista de Emprestimos, com as Bicicletas
                            {

                                if(Prestamos[posicaoPrestamo].ID_Bicicleta_Reserva==Bicicletas[posicaoBicicleta].ID_Bicicleta)  //Se fosse igual, entra.
                                {
                                    opcaoDevolucion=estadoDevolucionBicicleta();        //Pregunta se quesesse devolver a Bicicleta

                                    switch(opcaoDevolucion)
                                    {
                                    case 'D':   //No caso que sim, entra.

                                        Bicicletas[posicaoBicicleta].Estado_Bicicleta='D';      //O Estado da Bicicleta muda a Disponivel.

                                        distanciaPrestamo=lerDistancia(Prestamos[posicaoPrestamo].Campus_Destino_Prestamo,Prestamos[posicaoPrestamo].Campus_Origen_Prestamo);
                                        //Agrega-se a distância do Emprestimo

                                        *distanciaTotal+=distanciaPrestamo;     //Soma-se essa distância à distància total do Programa.

                                        Bicicletas[posicaoBicicleta].Distancia_Total+=distanciaPrestamo;    //Soma-se essa distância à distància da Bicicleta também.

                                        Utentes[posicaoUtente].DistanciaTotal_Recorrida+=distanciaPrestamo; //Soma-se essa distância à distància do Utente também.

                                        Bicicletas[posicaoBicicleta].Prestamos_Bicicleta++;     //Acrescenta-se os Emprestimos Feitos pela Bicicleta.

                                        Bicicletas[posicaoBicicleta].Campus_Origen_Bicicleta=Prestamos[posicaoPrestamo].Campus_Destino_Prestamo;   //Muda o Campus Origem da Bicicleta que usou.

                                        *opcaoAvaria=Menu_Estado_Avaria();      //Pregunta se a Bicicleta sofreu alguma Avaria.

                                        if (*opcaoAvaria=='S')  //No caso que sim ...
                                        {
                                            *posicaoBicicletaPrecisa=posicaoBicicleta;      //Guarda-se a Posiçao da bicicleta, para utilizar no Programa Principal.
                                            Bicicletas[posicaoBicicleta].Vezes_Averias++;   //Acrescenta-se as averias da Bicicleta.
                                            Bicicletas[posicaoBicicleta].Estado_Bicicleta='A';  //Muda-se o estado da Bicicleta.

                                        }

                                        (*estado)=1;    //Muda-se a variavel, que informa se a Devoluçao foi feita, ou não.
                                                        //Se fosse feita, então no programa principal, é eliminado o Pedido de Emprestimo da Lista de Emprestimos.
                                                        //Porque já terminou, e depois é adicionado ao Historico de Emprestimos.

                                        break;
                                    case 'E':   //No caso que não, entra.

                                        Bicicletas[posicaoBicicleta].Estado_Bicicleta='E';      //A Bicicleta, fica com Estado Emprestada, ou seja o Pedido de Emprestimo ainda não termina.
                                                                                            //Se o Utilizador pretende devolver em outro momento, pode faze-lo.

                                        printf("\nOperacao Cancelada pelo Utiilzador.\n A Bicicleta %d fica Emprestada\n",Bicicletas[posicaoBicicleta].ID_Bicicleta);

                                        break;
                                    }
                                }
                            }

                            posicionADevolver=posicaoPrestamo;  //A "posicaoPrestamo" muda ate terminar com a quantidade Prestamos, entao e preciso guardar o
                                                                //verdadero valor da Posicao do prestamo que queremos eliminar.
                        }

                    }
                }
                else
                {
                    printf("\nNao ha dados de Emprestimos. Operacao Invalida.\n");      //Aviso de Erro
                }
            }
            else
            {
                printf("\nNao ha dados de Bicicletas. Operacao Invalida.\n");       //Aviso de Erro
            }
        }
    }
    else
    {
        printf("\nNao ha dados de Utentes. Operacao Invalida.\n");      //Aviso de Erro
    }

    return posicionADevolver;   // Retorna a posiçao do Pedido de Emprestimo.
}

void DadosUtentesQuantidadeEmprestimosDECRE(tipoUtente Utentes[],int cantidadUtentes)
{
    int changes=1;
    int conta1,conta2;
    tipoUtente Temporal;

    if (cantidadUtentes>0)
    {
        for(conta1=0; conta1<cantidadUtentes-1 && changes!=0; conta1++)
        {
            changes=0;
            for (conta2= 0; conta2 < cantidadUtentes-conta1-1; conta2++)
            {
                if(Utentes[conta2+1].QuantidadePrestamos_Feitos > Utentes[conta2].QuantidadePrestamos_Feitos)   //Se o Utente numa posiçao for maior, muda-se os dados.
                {                                                                                             //Para que ao final fiquem ordenados.
                    changes=1;
                    Temporal=Utentes[conta2];               //Faz a mufança dos dados.
                    Utentes[conta2]=Utentes[conta2+1];
                    Utentes[conta2+1]=Temporal;
                }
            }
        }

        printf("\n\tDados Utentes por Quantidade Emprestimos\n");   //Ao final mostra os Dados dos Utentes. por Quantidade de Emprestimos.
        Mostrar_Dados_Utentes(Utentes,cantidadUtentes);

    }
    else
    {
        printf("\nNao tem dados.\n");
    }
            //Funçao que ordena o Vetor de Utenes por Numero de Emprestimos Feitos.
}
