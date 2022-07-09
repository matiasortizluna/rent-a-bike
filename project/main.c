#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "estruturas.h"

#include "funcoesbasicas.h"
#include "funcoes_bicicletas.h"
#include "funcoes_utentes.h"
#include "funcoes_emprestimos.h"
#include "funcoes_lista.h"
#include "funcoes_adicionales.h"

tipoBicicleta Bicicletas2018[15];
int Quantidade_Bicicletas=0;
char opcaoMenuBicicletas1;

tipoUtente Utentes2018[MAX_UTENTES];
char opcaoMenuUtentes1;
int Quantidade_Utente=0;

tipoPrestamo *Prestamos2018=NULL;
char opcaoMenuPrestamos1;
int cantidadPrestamos=0;

tipoPrestamo *RegistroPres=NULL;
int historioPres=0;

tipoPrestamo *ListaEspera2018=NULL;
int elementosNaLista=0;
int numeroProcura;
char opcaoMenuLista1;
char opcaoAtribucaoListaEspera='\0';
char opcaoMenuListaDistancia='\0';
int BicicletasDisponibles=0;
int estado;

tipoAveria *Averias=NULL;
int posicaoBicicletaParaAvaria=0;
int cantidadAverias=0;
char opcaoAveria='\0';

int posicaoUtente;
int posicaoBicicleta;
int posicaoLista;
int posicaoPrestamo=-1;
char opcaoMenuPrincipal;
int distanciaTotal=0;
int numeroRegistro=999;

int main()
{

    do
    {       //Vai-se repetir o Menu Principal até que o Utilizador coloque a opção Fim do programa.

        opcaoMenuPrincipal=menuPrincipal(Quantidade_Bicicletas,Quantidade_Utente,cantidadPrestamos,elementosNaLista,distanciaTotal);
        //São enviados todos estos parametros porque o Menu Principal tem que os aparesentar

        switch(opcaoMenuPrincipal)
        {
        case 'B':       //SUB MENU BICICLETAS
            do
            {           //Só sai do SUB MENU se colocasse a opção Voltar ao Menu Principal.
                opcaoMenuBicicletas1=menuBicicletas1();
                switch (opcaoMenuBicicletas1)
                {
                case 'I':   //Se colocasse a opção Inserir Bicicletas...

                    Quantidade_Bicicletas=lerInteiro("\nInsera a quantidade de bicicletas que va utilizar durante todo o programa.",1,MAX_BICICLETAS);
                    lerDadosBicicletas(Bicicletas2018,Quantidade_Bicicletas);

    //Le os dados das Bicicletas que quer inserir.
                    printf("\nOBicicletas Adicionadas.\n");

                    break;
                case 'C':   //Se colocasse a opção de Consultar a Informação sobre uma Bicicleta só.

                    consultarDadosBicicleta(Bicicletas2018,Quantidade_Bicicletas);
                    break;
                case 'M':   //Se colocasse a opção de Mostrar os Dados das Bicicletas todas.

                    Mostrar_Dados_Bicicletas(Bicicletas2018,Quantidade_Bicicletas);
                    break;
                case 'A':   //Se colocasse a opção de Acrescentar uma Bicicleta mais.

                    acresentarBicicleta(Bicicletas2018,&Quantidade_Bicicletas);
                    break;
                case 'R':   //Se colocasse a opção de Reparar Bicicleta.

                    Mostrar_Dados_Bicicletas(Bicicletas2018,Quantidade_Bicicletas);
                    repararBicicleta(Bicicletas2018,Quantidade_Bicicletas);
                    break;
                }
            }
            while (opcaoMenuBicicletas1!='V');  //Termina o SUB MENU BICICLETA
            break;
        case 'U':  //Apresenta o SUB MENU UTENTES

            do
            {       //Só sai do Sub Menu se colocar a opção Voltar ao Menu Principal.
                opcaoMenuUtentes1=menuUtentes1();
                switch (opcaoMenuUtentes1)
                {
                case 'N':   //Novo Utente

                    Quantidade_Utente++;            //Acrescenta a variavel da Quantidade.
                    if (Quantidade_Utente<MAX_UTENTES)  //Se a quantidade não for maior que o Limite de Utente, deixa acrescentar.
                    {
                        Utentes2018[Quantidade_Utente-1]=lerDadosDeNovoUtente(Utentes2018,Quantidade_Utente);
                        //É retornado os dados do novo utente com um return, à posição respectiva.
                    }
                    else    //Se a Quantidade é a maxima, da um aviso de erro.
                    {
                        printf("Numero Maximo de Utentes. Devera Eliminar para continuar a usar.");
                    }

                    break;
                case 'D':           //Se quesesse Devolver alguma Bicicleta.

                    DadosUtentesQuantidadeEmprestimosDECRE(Utentes2018,Quantidade_Utente);
            //Apresenta os Dados dos Utentes todos.

                    posicaoPrestamo=devolverBicicleta(Bicicletas2018,Prestamos2018,Quantidade_Bicicletas,cantidadPrestamos,Utentes2018,Quantidade_Utente,&distanciaTotal,&estado,&opcaoAveria,&posicaoBicicletaParaAvaria);
            //A funçao encarga-se de devolver a Bicicleta, e retorna a posição do Emprestimo que foi "terminado"

                    if(posicaoPrestamo!=-1) //Se o Emprestimo existir ...
                    {
                        if (opcaoAveria=='S')   //É preguntado se a Bicleta sufriu alguma averia..
                        {
                                    //No caso que sim, guarda-se numa variavel dinamica os dados
                            Averias=realloc(Averias,(cantidadAverias+1)*sizeof(tipoAveria));
                            if (Averias == NULL)
                            {
                                printf ("\nError - Imposivel inserir os dados da Avaria.\n");
                            }
                            else
                            {   //Se nao houver problemas com a variavel dinamica...

                                Averias[cantidadAverias]=lerDadosAveria(Bicicletas2018[posicaoBicicletaParaAvaria].ID_Bicicleta,Bicicletas2018[posicaoBicicletaParaAvaria].Distancia_Total);
                                //Le os dados referentes a Avaria.

                                cantidadAverias++;
                                //É acrescentado a quantidade da avarias no Programa.
                                escreveFichTextoAverias(Averias,cantidadAverias);
                                //E é escrito a informação num Ficheiro de Texto
                                //Ao final esta informação não vai ser reusada, então só fica como Registro.
                                printf("\nAvaria Registada.\n");
                            }
                        }

                        RegistroPres = realloc(RegistroPres,(historioPres+1)*sizeof(tipoPrestamo));
                        //Agora que o Emprestimo terminou, é preciso adicionar esse Emprestimo que acabou ao Historico de Emprestimos,
                        //e a variavel dinamica RegistroPres vai guardar essa informação...

                        if (RegistroPres == NULL)
                        {
                            printf ("\nError - Impossivel adicionar o Emprestimo ao Historico.\n");
                        }
                        else    //Se não houver problemas...
                        {
                            RegistroPres[historioPres]=Prestamos2018[posicaoPrestamo];  //Sáo copiados os dados de esse Emprestimo já feito, ao
                            //elemento de Historico preciso.
                            historioPres++;
                            //A variavel da Quantidade de Elementos que há no Historico de Emprestimos é acrescentada
                            printf ("\nEmprestimo adicionado ao Historico.\n");
                        }

                        Prestamos2018=eliminaElementoPrestamo(Prestamos2018,&cantidadPrestamos,posicaoPrestamo);
                        //É eliminado o Emprestimo que já terminou da Lista de Emprestimos.

                        if (elementosNaLista>0) //Se houver elementos na Lista de Espera a espera por uma Bicicleta.
                        {
                            switch(opcaoAtribucaoListaEspera)
                            {           //Dependendo da opção que foi inserida na Atrbução da Lista de Espera

                            case 'O':   //Por Ordem de Chegada.

                                posicaoLista=atribucaoBicicletaListaOrdemEntrada(ListaEspera2018,elementosNaLista,Bicicletas2018,Quantidade_Bicicletas);
                //é atribuída uma Bicicleta ao Elemento na Lista de Espera, volta por return a posição do Elemento.

                                if (ListaEspera2018[posicaoLista].ID_Bicicleta_Reserva!=0)  //Comproba-se que aquele Elemento não esta associado a Bicicleta nehuma.
                                {

                                    Prestamos2018 = realloc(Prestamos2018,(cantidadPrestamos+1)*sizeof(tipoPrestamo));
                                    //Acrescenta-se a variavel dinamica da Lista de Emprestimos.
                                    if (Prestamos2018 == NULL)
                                    {
                                        printf ("\nError - Impossivel inserir o funcionario.\n");
                                    }
                                    else    //Se não houver problemas
                                    {
                                        Prestamos2018[cantidadPrestamos]=ListaEspera2018[posicaoLista]; //São copiados os dados ao ultimo elemento da LIsta de Emprestimos.

                                        posicaoUtente=descubrirUtenteDesdeEmprestimo(Prestamos2018[cantidadPrestamos],Utentes2018,Quantidade_Utente);
                                        //Esta funçao descubre a posição do Utente que fez um Pedido de Emprestimo, e agora já tem uma Bicicleta.
                                        //Que sirve para apresentar no monitor o Utente
                                        printf("\nBicicleta %d Emprestada à Utente %d, pedidod de Emprestimo com NR: %d\n",Prestamos2018[cantidadPrestamos].ID_Bicicleta_Reserva,Prestamos2018[cantidadPrestamos].ID_Utente_Reserva,Prestamos2018[cantidadPrestamos].Numero_Registro);
                                        cantidadPrestamos++;
                                        //É acrescentada a variavel com a Quantidade de elementos na Lista de Emprestimos
                                        if (elementosNaLista>0) //Se houver ainda Elementos na Lista de Espera.
                                        {       //Elimina o Elemento que já tem Bicicleta e que esta na Lista de Espera
                                            //Como já tem Bicicleta, então não é preciso que este na Lista de Espera,
                                            //porque já esta na Lista de Emprestimos agora.

                                            ListaEspera2018=eliminaElementoLista(ListaEspera2018,&elementosNaLista,posicaoLista);

                                        }
                                    }
                                }
                                else
                                {
                                    printf("\nNao ha Bicicletas Dispoiveis para o Emprestimo com Numero Registro: %d \n",ListaEspera2018[posicaoLista].Numero_Registro);

                                }

                                break;

                            case 'D':   //Se a opção na Atribução fosse pelas Distancias

                                if (opcaoMenuListaDistancia=='C'){
                                        //Se a prioridade sao os Pedidos de Emprestimos com Distancias Menores

                                    ListarListaPorDistanciaCres(ListaEspera2018,elementosNaLista);
                                    //Troca os Elementos da Lista de Espera para que ao final o primeiro elemento da
                                    //Lista de Espera seja o menor

                                }
                                if (opcaoMenuListaDistancia=='D'){
                                        //Se a prioridade sao os Pedidos de Emprestimos com Distancias Maiores

                                    ListarListaPorDistanciaDecres(ListaEspera2018,elementosNaLista);
                                    //Troca os Elementos da Lista de Espera para que ao final o primeiro elemento da
                                    //Lista de Espera seja o maior.
                                }


                                posicaoLista=atribucaoBicicletaListaOrdemEntrada(ListaEspera2018,elementosNaLista,Bicicletas2018,Quantidade_Bicicletas);
                //é atribuída uma Bicicleta ao Elemento na Lista de Espera, volta por return a posição do Elemento.

                                if (ListaEspera2018[posicaoLista].ID_Bicicleta_Reserva!=0)  //Comproba-se que aquele Elemento não esta associado a Bicicleta nehuma.
                                {

                                    Prestamos2018 = realloc(Prestamos2018,(cantidadPrestamos+1)*sizeof(tipoPrestamo));
                                    //Acrescenta-se a variavel dinamica da Lista de Emprestimos.
                                    if (Prestamos2018 == NULL)
                                    {
                                        printf ("\nError - Impossivel inserir o funcionario.\n");
                                    }
                                    else    //Se não houver problemas
                                    {
                                        Prestamos2018[cantidadPrestamos]=ListaEspera2018[posicaoLista]; //São copiados os dados ao ultimo elemento da LIsta de Emprestimos.

                                        posicaoUtente=descubrirUtenteDesdeEmprestimo(Prestamos2018[cantidadPrestamos],Utentes2018,Quantidade_Utente);
                                        //Esta funçao descubre a posição do Utente que fez um Pedido de Emprestimo, e agora já tem uma Bicicleta.
                                        //Que sirve para apresentar no monitor o Utente
                                        printf("\nBicicleta %d Emprestada à Utente %d, pedidod de Emprestimo com NR: %d\n",Prestamos2018[cantidadPrestamos].ID_Bicicleta_Reserva,Prestamos2018[cantidadPrestamos].ID_Utente_Reserva,Prestamos2018[cantidadPrestamos].Numero_Registro);
                                        cantidadPrestamos++;
                                        //É acrescentada a variavel com a Quantidade de elementos na Lista de Emprestimos
                                        if (elementosNaLista>0) //Se houver ainda Elementos na Lista de Espera.
                                        {       //Elimina o Elemento que já tem Bicicleta e que esta na Lista de Espera
                                            //Como já tem Bicicleta, então não é preciso que este na Lista de Espera,
                                            //porque já esta na Lista de Emprestimos agora.

                                            ListaEspera2018=eliminaElementoLista(ListaEspera2018,&elementosNaLista,posicaoLista);

                                        }
                                    }
                                }
                                else
                                {
                                    printf("\nNao ha Bicicletas Dispoiveis para o Emprestimo com Numero Registro: %d \n",ListaEspera2018[posicaoLista].Numero_Registro);

                                }

                                break;
                            }
                        }
                    }

                    break;
                case 'C':       //Se quesesse Consultar os dados de um Utente só.

                    consultardadosUtente(Utentes2018,Quantidade_Utente);

                    break;

                case 'M':   //Se quesesse mostar os dados dos Utentes, foi pedido que seja feito por Quantidade de Emprestimos Feitos de forma Decerscente.

                    DadosUtentesQuantidadeEmprestimosDECRE(Utentes2018,Quantidade_Utente);

                    break;

                case 'E':   //Editar Utente

                    editarUtente(Utentes2018,Quantidade_Utente);

                    break;

                case 'A':   //Eliminar Utente

                    eliminaUtente(Utentes2018,&Quantidade_Utente);
            //Envia a informaçao toda, e é enviado como parametro por referencia a Quantidade, dentro da função provavelmente seja alterada.

                    break;
                case 'U':   //Determina qual foi a Ultima Bicicleta utilizada pelo algum Utente especifico.

                    UltimaBicicleta(Utentes2018,Quantidade_Utente,Bicicletas2018,Quantidade_Bicicletas,RegistroPres,historioPres);
            //É enviado os parametros precisos para que a função seja feita.

                    break;

                }
            }
            while (opcaoMenuUtentes1!='V'); //Termina o SUB MENU UTENTES


            break;

        case 'E':   //SUB MENU EMPRESTIMOS

            do          //Sai só do SUB MENU EMPRESTIMOS se colocasse a opção Voltar ao Menu Principal.
            {
                opcaoMenuPrestamos1=menuPrestamos1();

                switch (opcaoMenuPrestamos1)
                {

                case 'N':   //Se colocasse Novo Pedido de Emprestimo.

                    if (opcaoAtribucaoListaEspera=='\0')    //Se fosse a primeira vez que é inicializado o programa,
                            //então vai ser pedido ao Utilizador que agregue uma das opções sobre o funcionamento da LIsta de Esper,
                            // ou seja, a Atribução das Bicicletas seja feito de acordo ao que....

                    {
                        printf("\nAntes de que o programa començe trabalhar, devera inserir uma opcao na Funcionalidad da Lista de Espera.\n");
                        opcaoAtribucaoListaEspera=menuAtribucaoListaEspera();
                    //Apresenta o Menu de Atribução de Bicicletas,
                    //Há a opção de que sejam por ordem de chegada ..
                    //E a opção de que seja por Distancia a percorrer entre os Campis.

                        if (opcaoAtribucaoListaEspera=='D'){    //Se fosse pelas Distancias dos Campis.

                            opcaoMenuListaDistancia=menuListaDistancia();
                            //Devera inserir uma opção, deve se aclarar se vai ter prefencia por os Pedidos de Emprestimos
                            //com Distancias maiores ou menores.
                        }
                        printf("\nObrigado. Agora Pode Continuar.\n\n");
                    }

                    numeroProcura=lerInteiro("Insera o ID do Utente: ",1,MAX_ID_UTENTES);           //Le o ID do Utente que vai fazer o pedido de Emprestimo.
                    posicaoUtente=procura_ID_Utente(Utentes2018,Quantidade_Utente,numeroProcura);   //Retorna a posiçao do Utente com esse ID.
                    estado=UtenteOcupado(ListaEspera2018,Prestamos2018,elementosNaLista,cantidadPrestamos,numeroProcura);   //A função determina se o utente
                                    //já tem um Pedido de Emprestimo na Lista de Espera ou na Lista de Emprestimo.  Muda o valor da variavel estado para saber issso.

                    if (posicaoUtente==-1)
                    {
                        printf("\nEsse ID nao existe.\n");
                    }
                    else
                    {
                        if (estado!=1)  //Se o valor retornado por aquela variavel, fosse 1 (ou seja que não esta em nehuma das Listas, da para continuar.
                        {
                            Prestamos2018 = realloc(Prestamos2018,(cantidadPrestamos+1)*sizeof(tipoPrestamo));  //Faz um realloc de um elemento mais.
                            if (Prestamos2018 == NULL)
                            {
                                printf ("\nError - Impossivel inserir o funcionario.\n");
                            }
                            else
                            {
                                numeroRegistro=acrescentarNumeroRegistro(numeroRegistro);   //Acrescenta o numero de Registro.

                                leDadosPedidoEmprestimo(&Prestamos2018[cantidadPrestamos],numeroRegistro,Utentes2018[posicaoUtente].ID_Utente,Utentes2018[posicaoUtente].Profesion);
                                //Le os Dados do Novo Pedido de Emprestimo, a informção toda é pedida e asignada na posição respectiva.

                                BicicletasDisponibles=QuaantidadeBicletasDisponibles(Quantidade_Bicicletas,Prestamos2018[cantidadPrestamos].Campus_Origen_Prestamo,Bicicletas2018);
                                //São Calculadas as Bicicletas dispoiveis no Campus de Origem do Novo Pedido de Emprestimo.

                                if (BicicletasDisponibles>0)    //Se haber Bicicletas...
                                {
                                    Prestamos2018[cantidadPrestamos].ID_Bicicleta_Reserva=asignacaoBicicleta(Quantidade_Bicicletas,Bicicletas2018,Prestamos2018[cantidadPrestamos].Campus_Origen_Prestamo);
                                    //E asignado automaticamente alguma Bicicleta que esteja Disponivel nesse campus.

                                    cantidadPrestamos++;
                                    //É acrescentada a variavel com a quantidade de elementos na Lista de Emprestimos

                                    Utentes2018[posicaoUtente].QuantidadePrestamos_Feitos++;
                                    //Também acrescenta-se a quantidade de emprestimos feitos pelo Utilizador.

                                    printf("\nBicicleta %d Emprestada .\n",Prestamos2018[cantidadPrestamos-1].ID_Bicicleta_Reserva);
                                }
                                else    //Se não haber...
                                {
                                    printf("\nNao existem Bicicletas Disponibles. O seu Pedido de Emprestimo ficara na Lista de Espera.\n");
                                    ListaEspera2018=realloc(ListaEspera2018,(elementosNaLista+1)*sizeof(tipoPrestamo));
                                    //E acrescentado em 1 elemento a variavel dinamica.

                                    if (ListaEspera2018!=NULL)  //Se não houver erro nehum...
                                    {
                                        ListaEspera2018[elementosNaLista]=Prestamos2018[cantidadPrestamos];
                                        //A informação do Pedido Emprestimo e copiada ao elemento da Lista de Espera.
                                        //Não é preciso eliminar os dados da LIsta de Emprestimos, porque a variavel da
                                        //Quantidade de Emprestimos não foi acrescentada, então é como se náo fosse parte
                                        //do vetor, porque é informação que não nos interessa mais.


                                        elementosNaLista++;
                                        //É acrescentada a variavel com a quantidade de elementos que estam na Lista.

                                        printf("\nAdicionado a Lista de Espera.\n");
                                    }
                                    else
                                    {
                                        printf ("\nError - Impossivel adicionar à Lista de Espera.");
                                    }
                                }
                            }
                        }
                    }

                    break;

                case 'M':   //Mostra os Dados dos Pedidos de Emprestimos que estam na Lista de Emprestimos.

                    Mostrar_Dados_Emprestimos(Prestamos2018,cantidadPrestamos);

                    break;

                case 'C':   //Consulta os Dados de um Pedido de Emprestimo que esteja na Lista de Emprestimos.

                    consultarDadosPrestamo(Prestamos2018,cantidadPrestamos);

                    break;
                }
            }
            while (opcaoMenuPrestamos1!='V');

            break;

        case 'L':   //SUM MENU LISTA DE ESPERA (ADICIONAL)

            do
            {
                    //Apresenta o Menu até que o Utilizador coloque Voltar ao Menu Principal.
                opcaoMenuLista1=menuLista1();
                switch(opcaoMenuLista1)
                {

                case 'M':   //Mostra os dados que estejam nesse momento na Lista de Espera.

                    MostrarDadosLista(ListaEspera2018,elementosNaLista);

                    break;

                case 'E':   //Opção para Editar o Campus Destino da Lista de Espera.

                    editarCampusDestinoEmprestimoNaLista(ListaEspera2018,elementosNaLista);

                    break;

                case 'A':   //Opção para Eliminar/Apagar um Pedido de Emprestimo qeu esteja na Lista de Espera.

                    apagarElementoLista(ListaEspera2018,&elementosNaLista);

                    break;

                }
            }
            while(opcaoMenuLista1!='V');    //Só sai do Sub Menu Lista de Espera se coloca a opção Voltar ao Menu Principal.

            break;

        case 'D':

            DadosEstadisticos(Bicicletas2018,Quantidade_Bicicletas,Utentes2018,Quantidade_Utente,RegistroPres,historioPres);

            //Envia a informação toda à função, para que sejam feitos os respectivos calculos.

            break;

        case 'C':

            leFicheiroDadosUtentes(Utentes2018,&Quantidade_Utente);
            leFicheiroDadosBicicleta(Bicicletas2018,&Quantidade_Bicicletas);
            Prestamos2018=leFicheiroDadosPrestamos(Prestamos2018,&cantidadPrestamos);
            ListaEspera2018=leFicheiroDadosLista(ListaEspera2018,&elementosNaLista);
            leFichTextoNumeroRegistro(&numeroRegistro);

            printf("\nOperacao Feita.\n");      //Le os dados dos ficheiros binarios e de texto.

            break;

        case 'G':

            gravarFicheiroDadosBicicleta(Bicicletas2018,Quantidade_Bicicletas);
            gravarFicheiroDadosUtentes(Utentes2018,Quantidade_Utente);
            gravarFicheiroDadosPrestamos(Prestamos2018,cantidadPrestamos);
            gravarFicheiroDadosLista(ListaEspera2018,elementosNaLista);
            escreveFichTextoNumeroRegistro(numeroRegistro);

            printf("\nOperacao Feita.\n");                  //Chama a todas as funções que gravam dados.

            break;

        case 'F':
            printf("\nFim do programa.\n"); //Aviso de Fim de programa.
            break;
        }

    }
    while(opcaoMenuPrincipal!='F');         //O programa termina só se o Utilizador da a opçao de Fim de programa.

    free(RegistroPres);     //LIbertamos la memoria.
    free(ListaEspera2018);  //Libertamos la memoria.
    free(Prestamos2018);    //Libertamos la memoria.

    return 0;
}
