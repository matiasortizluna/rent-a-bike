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

char menuLista1()
{
    char opcao;
    do
    {
        printf("\n----------Menu Lista de Espera----------\n");
        printf("(M)ostrar os Elementos da Lista.\n");
        printf("(A)pagar um Elemento da Lista.\n");
        printf("(E)ditar um Elemento da Lista.\n");

        printf("\n(V)oltar ao Menu Principal.\n");
        printf("Opcao -> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);

        if (opcao!='M' && opcao!='A' && opcao!='E' && opcao!='V')
        {
            printf("Insera um caracter valido porfavor.\n");
        }
    }
    while (opcao!='M' && opcao!='A' && opcao!='E' && opcao!='V');

    return opcao;
}

tipoPrestamo *eliminaElementoLista(tipoPrestamo *Lista,int *cantidad,int posicaoEliminar)
{
    int conta;

    if (posicaoEliminar!=-1)
    {
        for (conta=posicaoEliminar; conta<(*cantidad); conta++) //Inicia-se desde a posiçao requerida.
        {
            Lista[conta] = Lista[conta+1];//Desaparecem os dados do Elemento da Lista de Espera que quere ser eliminado, e é adicionado os dados do seguinte
                                                    // e assim até chegar ao final
        }

        (*cantidad)--;                                          //Resta-se 1, à quantidade de elementos na Lista de Espera.
        Lista = realloc(Lista,(*cantidad)*sizeof(tipoPrestamo));        //Faz-se um realloc porque a quantiadade de Pedidos em Lista de Espera, mudou.

    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    return Lista;   //Retorna o vetor, ao ser um ponteiro e variavel dinamica é preciso, para não ter problemas de perdida de informçao.

}

void MostrarDadosLista(tipoPrestamo Lista[],int elementosNaLista)
{
    int conta;

    if(elementosNaLista>0)
    {

        for (conta=0; conta<elementosNaLista; conta++)
        {
            printf("\n----------------------------------------\n");

            printf("\nNumero de Registro : %d",Lista[conta].Numero_Registro);

            printf("\n ID Utente: %d",Lista[conta].ID_Utente_Reserva);
            printf("\n Designacao Bicicleta: %d",Lista[conta].ID_Bicicleta_Reserva);

            imprimirCampus("\n Campus Origen: ",Lista[conta].Campus_Origen_Prestamo);
            imprimirCampus("\t\tCampus Destino: ",Lista[conta].Campus_Destino_Prestamo);

            imprimirData("\n Data e Hora de Emprestimo: ",Lista[conta].Data_Hora_Prestamo);

        }
    }
    else
    {

        printf("\nNao tem dados.\n");
    }

}

int procuraNumeroRegistro_paraLista(tipoPrestamo Lista[],int elementosNaLista,int numeroRegistroPreciso)
{

    int conta;
    int posicao=-1;

    for (conta=0; conta<elementosNaLista; conta++)
    {
        if (numeroRegistroPreciso==Lista[conta].Numero_Registro)    //É enviado um Numero de Registro especifico para comparar com os elementos da Lista de Espera.
        {
            posicao=conta;      //Se foram iguais, guarda-se a posicao no vetor de Lista de Espera.
        }
    }

    return posicao;
}

char menuAvisoDeSeguridadApagarElementoLista()
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

    return opcao;
                    //Ulitmo aviso de seguridad para Apagar o Elemento na Lista de Espera.
}

void apagarElementoLista(tipoPrestamo *Lista,int *elementosNaLista)
{
    int posicao;
    int numeroRegistroPreciso;
    char opcaoMenuSeguridadLista;
    if (*elementosNaLista>0)
    {
        MostrarDadosLista(Lista,*elementosNaLista);

        numeroRegistroPreciso=lerInteiro("\nInsera o Numero De Registro que gostaria Eliminar: ",1000,1100);
        posicao=procuraNumeroRegistro_paraLista(Lista,*elementosNaLista,numeroRegistroPreciso);

        if (posicao!=-1)    //Se o Numero de Registro existir, então prosigue-se.
        {
            opcaoMenuSeguridadLista=menuAvisoDeSeguridadApagarElementoLista();  //Pregunta-se uma ultima vez se quer eliminar o Elemento.

            switch(opcaoMenuSeguridadLista)
            {
            case 'S':   //Se a opçao fosse Sim ...

                Lista=eliminaElementoLista(Lista,&(*elementosNaLista),posicao); //Então elimina-se esse Elemento da Lista de Espera, eniva-se a posiçao exacta.

                printf("\nOperacao Feita.\n");

                break;
            case 'N':   //Se a opçao fosse Não ..

                printf("\nOperacao Cancelada.\n");

                break;
            }
        }
        else
        {
            printf("\nNao encontram-se Emprestimo com esse Numero de Registro.\n");
        }
    }
    else
    {
        printf("\nNao tem dados. Operacao Invalida.\n");
    }
}

void editarCampusDestinoEmprestimoNaLista(tipoPrestamo Lista[],int elementosNaLista)
{
    int numeroPreciso;
    int posicao;

    if (elementosNaLista>0)
    {
        MostrarDadosLista(Lista,elementosNaLista);

        numeroPreciso=lerInteiro("\nInsera o Numero de Registro do Emprestimo que deseja alterar o seu Campus destino: ",1000,1200);
        posicao=procuraNumeroRegistro_paraLista(Lista,elementosNaLista,numeroPreciso);

        if(posicao!=-1) //Se a posiçao fosse encomtrada ...
        {                                                   //Imprime o campus Anterior, e da para que insere a nova opçao.

            imprimirCampus("\nCampus Destino (Anterior): ",Lista[posicao].Campus_Destino_Prestamo);
            Lista[posicao].Campus_Destino_Prestamo=menuCampus1("\nCampus Destino (Novo): ");

            printf("\nOperacao Feita.\n");
        }
        else
        {
            printf("Nao existe esse funcionario.\nInsera de novo porfavor.\n");
        }
    }
    else
    {
        printf("\nOperacao Invalida. Nao tem dados.\n");
    }
}

void gravarFicheiroDadosLista (tipoPrestamo Lista[], int quant)
{
    int erro;
    FILE *ficheiro;

    ficheiro=fopen("dadosLista.dat","wb");
    if (ficheiro== NULL)
    {
        printf("Ficheiro Inesistente\n");
    }
    else
    {
        fwrite(&quant,sizeof(int),1,ficheiro);
        fwrite(Lista,sizeof(tipoPrestamo),quant,ficheiro);
        erro = fclose(ficheiro);
        if (erro != 0)
        {
            printf ("Erro %d no fecho ficheiro\n", erro);
        }
    }
    //Grava os dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso

}

tipoPrestamo  *leFicheiroDadosLista (tipoPrestamo Lista[],int *quant)
{
    FILE *ficheiro;

    ficheiro=fopen("dadosLista.dat","rb");
    if (ficheiro== NULL)
    {
        printf("Ficheiro Inesistente\n");
        free(Lista);
        Lista=NULL;
        *quant=0;
    }
    else
    {

        fread(&(*quant),sizeof(int),1,ficheiro);
        Lista=realloc(Lista,(*quant)*sizeof(tipoPrestamo));
        if (Lista == NULL && *quant !=0)
        {
            printf("Error ler o ficheiro\n");
            *quant=0;
        }
        else
        {
            fread(Lista,sizeof(tipoPrestamo),*quant,ficheiro);
            fclose(ficheiro);
        }
    }

    return Lista;//Retorna um vetor, porque ao ser um vetor dinamico, há mudanças dentro da funçao que tem que ter efeito também afora dela.

      //Leitura dos dados num Ficheiro Binario, foneçe avisos de ERRO quando é preciso.
}

int atribucaoBicicletaListaOrdemEntrada(tipoPrestamo Lista[],int elementosNaLista,tipoBicicleta Bicicletas[],int Quantidade_Bicicletas)
{

    int posicaoLista=0,BicicletasDisponibles;

    if (elementosNaLista>0) //Se existesse algum elemento na Lista de Espera.
    {

        BicicletasDisponibles=QuaantidadeBicletasDisponibles(Quantidade_Bicicletas,Lista[posicaoLista].Campus_Origen_Prestamo,Bicicletas);  //Calcula-se quantas Bicicletas DIsponiveis há nesse Campus.

        if (BicicletasDisponibles>0)    //Se houvesse ...
        {
                //Envia-se o Campus Origem do Elemento da Lista, e retorna um ID de uma Bicicleta, ou seja, o ELemento na Lista de Espera já tem Bicicleta.

            Lista[posicaoLista].ID_Bicicleta_Reserva=asignacaoBicicleta(Quantidade_Bicicletas,Bicicletas,Lista[posicaoLista].Campus_Origen_Prestamo);

        }
    }
    else
    {
        printf("\nNehum elemento esta à espera de uma Bicicleta Disponible.\n");
    }
                            //Retorna a posiçao do Elemento da Lista de Espera que acaba de ser asignado uma Bicicleta.
    return posicaoLista;
}

int descubrirUtenteDesdeEmprestimo(tipoPrestamo ElementoEmprestimo,tipoUtente Utentes[],int Quantidade_Utente)
{
                            //Receve-se Um Elemento de tipo Emprestimo.
    int posicao;
    int conta;

    for (conta=0; conta<Quantidade_Utente; conta++)
    {

        if (ElementoEmprestimo.ID_Utente_Reserva==Utentes[conta].ID_Utente)     //Compara-se o ID do Elemento com os IDs dos Utentes
        {
                                        //NO caso fossem iguais, guarda-se a posiçao.
            posicao=conta;
            Utentes[posicao].QuantidadePrestamos_Feitos++;      //E acrescenta-se a quantidade de Emprestamos Feitos pelo Utente.
            conta=Quantidade_Utente;                       //Termina a procura.
        }
    }

    return posicao; //Retorna-se a posiçao do Utente.
}

char menuAtribucaoListaEspera()
{
    char opcao;
    do
    {
        printf("\n----------Menu Atribucao Lista de Espera----------\n");
        printf("\nA Atribucao das Bicicletas Na Lista de Espera prefere que seja por: \n");

        printf("(O)rdem de Entrada do Pedido.\n");
        printf("(D)istancia Per Percorrer.\n");


        printf("Opcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='O' && opcao!='D')
        {
            printf("\nDevera ingresar alguma opcao Para continuar.\n");
            }

    }
    while (opcao!='O' && opcao!='D');

    return opcao;
}

int calcularDistanciaAntes(char campusOrigen,char campusDestino)
{

    int origen,destino,minimo;

    switch (campusOrigen)//Dependendo do Campus de Origem, da um numero à varivel origem.
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

    switch (campusDestino)//Dependendo do Campus Destino, da um numero à varivel destino.
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

    minimo=abs(destino-origen);//Calcula a resta, como um valor absoluto para não ter valores negativos.
                    //E assim temos uma distância minima que pode ser considerada.

    return minimo;
}

void ListarListaPorDistanciaCres(tipoPrestamo Lista[],int elementosNaLista)
{

    int conta,conta1,conta2;
    int minimos[elementosNaLista];  //Cria-se um vetor auxiliar que guarde as distancias minimas de percorrer nos campus, vai ter os mesmos elementos que a Lista de Espera
                                    //Parar que os Elementos estejem associados, e não exista perdida de informaçao.
    int AUX;
    int changes=1;              //Variaveis precisas para fazer a troca de Dados.
    tipoPrestamo Temporal;

    if (elementosNaLista>0) //Se há elementos na Lista ...
    {
        for(conta=0; conta<elementosNaLista; conta++)   //Calcula as distanciâs minimas de cada um dos elementos da Lista de Espera, cada um esta associado com as posiçoes.
        {
            minimos[conta]=calcularDistanciaAntes(Lista[conta].Campus_Origen_Prestamo,Lista[conta].Campus_Destino_Prestamo);
        }

        for(conta1=0; conta1<elementosNaLista-1 && changes!=0; conta1++)
        {
            changes=0;
            for (conta2=0; conta2 < elementosNaLista-conta1-1; conta2++)
            {                                           //Compara as distâncias minimas, um elemento com aquele que vai seguir.
                if(minimos[conta2+1] < minimos[conta2])     //Se fosse menor.   //Como os elementos estam associados com as mesmas posiçoes,então, não da problema.
                {
                    changes=1;

                    AUX=minimos[conta2];
                    minimos[conta2]=minimos[conta2+1];          //Faz-se a troca dos elementos no Vetor Auxiliar.
                    minimos[conta2+1]=AUX;

                    Temporal=Lista[conta2];
                    Lista[conta2]=Lista[conta2+1];              //E também nos Elementos da Lista de Espera.
                    Lista[conta2+1]=Temporal;
                }
            }
        }

        printf("\n\tLista de Espera Atualizada por Distancia entre os campi Crescente\n");  //Da uma mensagem de Actualizaçao.

    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    //Funçao para listar os dados da Lista de Espera em Ordem Crescente.
}

void ListarListaPorDistanciaDecres(tipoPrestamo Lista[],int elementosNaLista)
{

    int conta,conta1,conta2;
    int minimos[elementosNaLista];//Cria-se um vetor auxiliar que guarde as distancias minimas de percorrer nos campus, vai ter os mesmos elementos que a Lista de Espera
                                    //Parar que os Elementos estejem associados, e não exista perdida de informaçao.

    int AUX;
    int changes=1;              //Variaveis precisas para fazer a troca de Dados.
    tipoPrestamo Temporal;

    if (elementosNaLista>0)     //Se há elementos na Lista ...
    {
        for(conta=0; conta<elementosNaLista; conta++)//Calcula as distanciâs minimas de cada um dos elementos da Lista de Espera, cada um esta associado com as posiçoes.
        {
            minimos[conta]=calcularDistanciaAntes(Lista[conta].Campus_Origen_Prestamo,Lista[conta].Campus_Destino_Prestamo);
        }

        for(conta1=0; conta1<elementosNaLista-1 && changes!=0; conta1++)
        {
            changes=0;
            for (conta2=0; conta2 < elementosNaLista-conta1-1; conta2++)
            {
                                                 //Compara as distâncias minimas, um elemento com aquele que vai seguir.
                if(minimos[conta2+1] > minimos[conta2])//Se fosse maior.   //Como os elementos estam associados com as mesmas posiçoes,então, não da problema.
                {
                    changes=1;

                    AUX=minimos[conta2];
                    minimos[conta2]=minimos[conta2+1];          //Faz-se a troca dos elementos no Vetor Auxiliar.
                    minimos[conta2+1]=AUX;

                    Temporal=Lista[conta2];
                    Lista[conta2]=Lista[conta2+1];               //E também nos Elementos da Lista de Espera.
                    Lista[conta2+1]=Temporal;
                }
            }
        }


        printf("\n\tLista de Espera Atualizada por Distancia entre os campi Decrescente\n"); //Da uma mensagem de Actualizaçao.

    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    //Funçao para listar os dados da Lista de Espera em Ordem Decrescente.
}

char menuListaDistancia()
{

    char opcao;
    do
    {
        printf("\nDistancias: \n");
        printf("(D)ecrescente. (Prioridade Distancias Maiores)\n");
        printf("(C)recentes. (Prioridade Distancias Menores)\n");
        printf("Opcao -> ");

        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='D' && opcao!='C')
        {
            printf("Insera um caracter valido porfavor.\n");
        }
    }
    while (opcao!='D' && opcao!='C');

    return opcao;

    //Menu que permite determinar se Ditanciâs consideradas tem que ser Decrescentes, ou Crescentes.
}

void escreveFichTextoNumeroRegistro(int numeroRegistro)
{
    FILE *fich;
    fich = fopen("NumerosRegistros.txt","w");
    if (fich == NULL)
    {
        printf ("\nError abrir ficheiro Averias\n");
    }
    else
    {
        fprintf(fich,"%d",numeroRegistro);
        fclose(fich);
    }

    //Grava o Numero de Registro até que chegou o Programa, num Ficheiro de Texto, foneçe avisos de ERRO quando é preciso
}

void leFichTextoNumeroRegistro(int *numeroRegistro)
{
    FILE *fich;

    fich = fopen("NumerosRegistros.txt","r");

    if (fich == NULL)
    {
        printf ("Erro abrir fich");
    }
    else
    {
        fscanf(fich,"%d", &(*numeroRegistro));

    }
    fclose(fich);

    //Le o Numero de Registro até que chegou o Programa anterior para que não sejam repetidos, num Ficheiro de Texto, foneçe avisos de ERRO quando é preciso
}
