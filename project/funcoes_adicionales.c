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

char menuCampus1(char texto[MAX_STRING])
{
    char opcao;
    do
    {
        printf("\n%s\n",texto);

        printf("(1) Campus 1 ESECS\n");
        printf("(2) Campus 2 ESTG\n");
        printf("(5) Campus 5\n");
        printf("(R) esidencias\n");

        printf("Opcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);

        limpaBufferStdin();

        if (opcao!= '1' && opcao!= '2'&& opcao!= '5' && opcao!='R')
        {
            printf("Insera uma opcao valida.\n");
        }
    }
    while(opcao!= '1' && opcao!= '2' && opcao!= '5' && opcao!='R');

    return opcao;
}

char menuPrincipal(int quantidadeBicicletas,int quantidadeUtentes,int quantidadeEmprestimos, int elementosNaLista, int distanciaTotal)
{

    char opcao;
    do
    {
        printf("\n----------Menu Principal----------\n");

        printf("(B)icicletas.");
        printf("\t\t\tQuantidade Bicicletas: %d\n",quantidadeBicicletas);

        printf("(U)tentes.");
        printf("\t\t\tQuantidade Utentes: %d\n",quantidadeUtentes);

        printf("(E)mprestimos.");
        printf("\t\t\tQuantidade Emprestimos Registados: %d\n",quantidadeEmprestimos);

        printf("(L)ista de Espera.");
        printf("\t\tElementos Na Lista de Espera: %d",elementosNaLista);
        printf("\t\tDistancia Total Percorrida: %d km\n",distanciaTotal);

        printf("\n(D)ados Estadisticos.\n");
        printf("(C)argar Imformacao Toda.\n");
        printf("(G)ravar Imformacao Toda.\n");


        printf("\n(F)im do programa.\n");
        printf("Opcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);

        limpaBufferStdin();

        if (opcao!='B' && opcao!='U' && opcao!='E' &&opcao!='L' && opcao!='C' && opcao!='G' && opcao!='D' && opcao!='F')
        {
            printf("Insera uma opcao valida.\n");   // Si no ingresan una opcion valida sale el mensaje de que lo vuelvan a ingresar.
        }
    }
    while (opcao!='B' && opcao!='U' && opcao!='E' &&opcao!='L' && opcao!='C' && opcao!='G' && opcao!='D' && opcao!='F');

    return opcao;
    //Estrutura Menu Principal
}

void distanciaMedia(tipoBicicleta Bicicletas[],int cantidadBicicletas)
{

    float media[cantidadBicicletas];    //Cria-se um vetor Auxiliar, que vai estar associado ao Vetor de Bicicletas, os elementos vam ter as mesmas posiçoes.
    int conta;


if (cantidadBicicletas>0){

    for (conta=0; conta<cantidadBicicletas; conta++)    //Calcula-se a Distância de Cada Bicicleta.
    {
        media[conta]=(float)Bicicletas[conta].Distancia_Total/Bicicletas[conta].Prestamos_Bicicleta;

    }


        for (conta=0; conta<cantidadBicicletas; conta++)
        {
            if(media[conta]>0)  //Se a media calculada, é maior que 0 ...
            {

                printf("ID Bicicleta: %d\n",Bicicletas[conta].ID_Bicicleta);    //O ID da Bicicleta
                printf("Distancia Media Percorrida: %2.f km\n",media[conta]);   //A media calculada, os elementos têm as mesmas posições, pelo que,
                                                                                //a informação esta conectada.
            }
            else    //Se não os dados são apresentados como 0.
            {
                printf("ID Bicicleta: %d\n",Bicicletas[conta].ID_Bicicleta);    //O ID da Bicicleta
                printf("Distancia Media Percorrida: 0 km\n");               //Como a sua media não é mais alta que 0, então evitam-se problemas, se so
            }                                                               // imprime-se o caracter 0.
        }
    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    //Funçao que calcula as ditâncias medias de cada Bicicleta.
}

void percentagemEmprestimosTipoUtente(tipoPrestamo Historico[],int historioPres)
{
    int estudiante=0,docente=0,tecnico=0,convidado=0;
    float perEstudiante;
    float perDocente;
    float perTecnico;
    float perConvidado;
    int cantidadPrestamos=historioPres;

    int conta;

    if(historioPres>0)  //Se  há dados ...
    {
        for (conta=0; conta<historioPres; conta++)  //Percorre o vetor de Emprestimos já terminados.
        {
            switch(Historico[conta].Tipo_Utente_Reserva)    //Dependendo do Tipo/Profesion do Utente qeu fez esse Emprestimo, contam-se em variaveis independentes.
            {
            case 'E':   //Se fosse Estudante...
                estudiante++;
                break;
            case 'D':   //Se fosse Docente...
                docente++;
                break;
            case 'T':   //Se fosse Tecnico...
                tecnico++;
                break;
            case 'C':   //Se fosse Convidado...
                convidado++;
                break;
            }
        }

        //Agora que temos os dados respectivos, é preciso calcular o seu percetagem, a tomar em conta todos os emprestimos que for feitos.

        perEstudiante=(float)estudiante/cantidadPrestamos*100;  //Se fosse Estudante.

        perDocente=(float)docente/cantidadPrestamos*100;    //Se fosse Docente.

        perTecnico=(float)tecnico/cantidadPrestamos*100;    //Se fosse Tecnico.

        perConvidado=(float)convidado/cantidadPrestamos*100;    //Se fosse Convidado.

        printf("Estudantes: %.2f %%\n",perEstudiante);
        printf("Docentes: %.2f %%\n",perDocente);
        printf("Tecnicos Administrativos: %.2f %%\n",perTecnico);   //Imprime os Valores Todos.
        printf("Convidados: %.2f %%\n",perConvidado);

    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    //Funçao que calcula as percetagens dos prestamos feitos por Tipo de Utente.
}

void campusOrigenMaisEmprestimos(tipoPrestamo Historico[],int historioPres)
{

    int conta;
    int campus1=0,campus2=0,campus5=0,campusR=0;
    int empres[4]= {0};                     //Cria-se um vetor auxiliar associado aos campus.
    char maior;

    if (historioPres>0) //Se  há dados ...
    {
        for (conta=0; conta<historioPres; conta++) //Percorre o vetor Todo..
        {
            switch (Historico[conta].Campus_Origen_Prestamo)    //Dependendo do Campus Origem do Emprestimo já terminado ...
            {
            case '1':
                empres[0]++;        //Acrescenta-se com a quantiade de Emprestimos, referente ao Campus 1, o vector com a posiçao 0.
                campus1++;          //Acrescenta-se a variavel com a quantiade de emprestimos com Campus Origem 1.

                //Faz-se assim, para ao final, ordenar o vetor auxiliar, e o primeiro elemento tera os dados do Campus com mais Emprestimos,
                //mas, como probablemente mudou de posições os elementos do vetor Axiliar, então a maneira de saber a que campus refere-se
                // os dados, compara-se com as variaveis locais, e assi, saber o campus de Origem.

                break;
            case '2':
                empres[1]++;        //Acrescenta-se com a quantiade de Emprestimos, referente ao Campus 2, o vector com a posiçao 1.
                campus2++;          //Acrescenta-se a variavel com a quantiade de emprestimos com Campus Origem 2.
                break;
            case '5':
                empres[2]++;        //Acrescenta-se com a quantiade de Emprestimos, referente ao Campus 5, o vector com a posiçao 2.
                campus5++;          //Acrescenta-se a variavel com a quantiade de emprestimos com Campus Origem 5.
                break;
            case 'R':
                empres[3]++;        //Acrescenta-se com a quantiade de Emprestimos, referente a Residencias, o vector com a posiçao 3.
                campusR++;          //Acrescenta-se a variavel com a quantiade de emprestimos com Campus Origem Residencias.
                break;
            }
        }

        int conta2, conta3, aux, posmenor;
        for(conta2=0; conta2 < 4-1; conta2++)  // Percorre vetor
        {
            posmenor=conta2;
            for (conta3=conta2+1; conta3 < 4; conta3++)
            {
                if (empres[conta3] > empres[posmenor])  // Ordena-se o vector Auxiliar de forma Crescente, assim, a primeira posiçao vai ter os Dados do Campus com mais Emprestimos.
                {
                    posmenor = conta3;
                }
            }
            if (posmenor!=conta2)  // se existir elemento inferior
            {
                aux=empres[posmenor]; // troca elemento corrente com o menor
                empres[posmenor]=empres[conta2];
                empres[conta2]=aux;
            }
        }

        //Como o Primeiro elemento do vetor auxiliar tem os dados do campus com maior quantiade de emprestimos, mas posivelmente, aquela informaçao
        //já não e igual com as posiçoes que tinhamos num inicio, compara-se com os dodos dos campus das variaveis locais que não foram alteradas,
        //e se foram iguais, então já sabemos qual é o campus maior, e a quantidade de emprestimos que foram feitos.

        if(empres[0]==campus1)
        {
            maior='1';      //Se fosse maior o Campus 1
        }
        else
        {
            if (empres[0]==campus2)
            {
                maior='2';      //Se fosse maior o Campus 2
            }
            if (empres[0]==campus5)
            {
                maior='5';  //Se fosse maior o Campus 5
            }
            if (empres[0]==campusR)
            {
                maior='R';  //Se fosse maior Residencias
            }
        }

        //E imprime-se a informaçao.

        imprimirCampus("\nO Campus Origem com mais Emprestimos foi ",maior);
        printf(" Com %d Emprestimos.\n",empres[0]);

    }
    else
    {
        printf("\nNao tem dados.\n");
    }

    //Funçao que calcula e apresenta o Campus de Origem com mais Emprestimos.
}

void QuemUtilizoAquelaBicicleta(tipoBicicleta Bicicletas[],int Quantidade_Bicicletas,tipoUtente Utentes[],int Quantidade_Utente,tipoPrestamo Historico[],int historioPres)
{

    int numeroProcura,posicao,conta,conta2;
    int numPrestamos=0;
    int IDrepetidos=-1;
    int numeroFinal;

    if (Quantidade_Bicicletas>0 && historioPres>0)      //Se haber Bicicletas e Emprestimos já terminados
    {

        numeroProcura=lerInteiro("Insere o ID da Bicicleta que precisa Informacao: ",1,MAX_BICICLETAS);
        posicao=procura_ID_Bicicleta(Bicicletas,Quantidade_Bicicletas,numeroProcura);

        if (posicao==-1)    //Se o ID da Bicicelta existir...
        {
            printf("\nNao existem dados com esse numero. Tente novamente.\n");
        }
        else
        {
            for (conta=0; conta<historioPres; conta++)  //Percorre o vetor de Emprestimos já terminados
            {
                if (Bicicletas[posicao].ID_Bicicleta==Historico[conta].ID_Bicicleta_Reserva)   //Se O ID da Bicicleta for igual que o ID da Bicicleta.
                {
                    numPrestamos++;             //A quantidade de Emprestimos que foram feitos com essa Bicicleta.

                    for (conta2=0; conta2<Quantidade_Utente; conta2++)  //Percorre o vetor de Utentes.
                    {
                        if (Historico[conta].ID_Utente_Reserva==Utentes[conta2].ID_Utente)  //Se o ID dos Emprestimos é igual ao ID do Utente.
                        {
                            IDrepetidos++;  //Esto tem que pasar pelo menos uma vez, mas, quando passa mais vezes, significa que foram feitos 2 emprestimos
                                            //com o mesmo Utente, então a variavel permite-nos contar isso.

                        }
                    }

                }

            }

            numeroFinal=(numPrestamos-IDrepetidos); //Dividimos os Emprestimos feitos com esse ID da Bicicleta, e as vezes que o mesmo Utente fez varios Emprestimos.

            if (numPrestamos>0) //Se a resta é maior que 0, apresentam-se os valores.
            {
                printf("\n%d Utentes utilizarom a Bicicleta %d.\n",numeroFinal,Bicicletas[posicao].ID_Bicicleta);

            }
            else    //Se a resta foi menor, para evitar erros, apresentam-se só como o caracter 0.
            {
                printf("\nNao existem Emprestimos com esa Bicicleta.\n");
                printf(" 0 Utentes utilizarom a Bicicleta %d.\n",Bicicletas[posicao].ID_Bicicleta);
            }

        }


    }
    else
    {
        printf("\nNao tem dados.\n");

    }

        //Funçao que calcual e apresenta a Bicicleta mais utilizada por determiando Utente.
}

void emprestimosEntreDuasDatas(tipoPrestamo Historico[],int historioPres)
{

    int conta;
    tipoDataHora dataInicial;
    tipoDataHora dataFinal;
    int prestamosFeitos=0;

    if (historioPres>0) //Se haber Emprestimos já feitos.
    {

        lerDataHora(&dataInicial,"Insere a data Inicial: ");    //Data Inicial Inserida pelo Utilizador.
        lerDataHora(&dataFinal,"Insere a data Final: ");        //Data Final Inserida pelo Utilizador.


        for (conta=0; conta<historioPres; conta++)
        {
                //Percorre o Vetor de Emprestimos já terminados.
            if (Historico[conta].Data_Hora_Prestamo.ano>=dataInicial.ano && Historico[conta].Data_Hora_Prestamo.ano<=dataFinal.ano)
            {       //Se o ano de um Emprestimo é maior que o inserido pelo UTilizador e menor que o inserido pelo Utilizador...

                if (Historico[conta].Data_Hora_Prestamo.mes>=dataInicial.mes && Historico[conta].Data_Hora_Prestamo.mes<=dataFinal.mes)
                {       //Se o mes de um Emprestimo é maior que o inserido pelo UTilizador e menor que o inserido pelo Utilizador...

                    if (Historico[conta].Data_Hora_Prestamo.dia>=dataInicial.dia && Historico[conta].Data_Hora_Prestamo.dia<=dataFinal.dia)
                    {       //Se o dia de um Emprestimo é maior que o inserido pelo UTilizador e menor que o inserido pelo Utilizador...

                        if (Historico[conta].Data_Hora_Prestamo.hora>=dataInicial.hora && Historico[conta].Data_Hora_Prestamo.hora<=dataFinal.hora)
                        {       //Se a hora de um Emprestimo é maior que o inserido pelo UTilizador e menor que o inserido pelo Utilizador...


                            prestamosFeitos++;  //Acrescenta-se a variavel que conta os Emprestimos feitos, entre aquelas duas datas.
                            printf("\n----------------------------------------\n");
                            //Apresenta os dados de aquele Emprestimo.
                            printf("\nNumero de Registro : %d",Historico[conta].Numero_Registro);
                            printf("\n\n ID Utente: %d",Historico[conta].ID_Utente_Reserva);
                            imprimirCampus("\t\t\t\tCampus Origen: ",Historico[conta].Campus_Origen_Prestamo);
                            printf("\n Designacao da Bicicleta: %d",Historico[conta].ID_Bicicleta_Reserva);
                            imprimirCampus("\t\tCampus Destino: ",Historico[conta].Campus_Destino_Prestamo);
                            imprimirData("\n\n Data e Hora de Emprestimo: ",Historico[conta].Data_Hora_Prestamo);
                        }
                    }
                }
            }
        }

        printf("\nForam feitos %d Emprestimos.",prestamosFeitos);   //Ao final da o dado só sobre a quantidade de Emprestimo feitos entre aquelas duas datas.

    }
    else
    {
        printf("\nNao ha Dados.\n");
    }

    //Funçao que apresenta os Emprestimos feitos entre duas datas, inseridas pelo Utilizador.
}


char menuDadosEST()
{
    char opcao;

    do
    {
        printf("\n----------Menu Dados Estadisticos----------\n");
        printf("\n(T)odos os Dados.\n");
        printf("(D)istancias Medias Percorridas por Cada Bicicleta.\n\n");
        printf("(P)ercentagem de empréstimos efetuados por cada tipo de utente.\n");
        printf("(C)ampus Origen com mais Emprestimos.\n");
        printf("(Q)uantidade de Utentes que Utilizaram uma determinada Bicicleta.\n");
        printf("(E)mprestimos Feitos entre duas datas\n");

        printf("\n(V)oltar ao Menu Principal.\n");
        printf("**Toma-se em conta os Emprestimos feitos, com Devolucoes de Bicicletas Feitas.\n\n");

        printf("Opcao-> ");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
        limpaBufferStdin();

        if (opcao!='T' && opcao!='D' && opcao!='P' && opcao!='C' && opcao!='Q'&& opcao!='E' && opcao!='V')
        {
            printf("Insera uma opcao valida.\n");   // Si no ingresan una opcion valida sale el mensaje de que lo vuelvan a ingresar.
        }
    }
    while (opcao!='T' && opcao!='D' && opcao!='P' && opcao!='C' && opcao!='Q'&& opcao!='E' && opcao!='V');   // Vuelve a aparecer el menu

    //Menu que apresenta as varias opções sobre os dados estadisticos que podem ser calculados e apresentados.

    return opcao;
}

void DadosEstadisticos(tipoBicicleta Bicicletas[],int cantidadBicicletas,tipoUtente Utentes[],int cantidadUtentes,tipoPrestamo Historico[],int historioPres)
{

    char opcaoMenuDadosEST;

    opcaoMenuDadosEST=menuDadosEST();

    switch(opcaoMenuDadosEST)
    {

    case 'T':   //Se a opção for calcular e apresentar os dados Todos.

        printf("\n----------Dados Estadisticos----------\n");
        printf("**Toma-se em conta os Emprestimos feitos, com Devolucoes de Bicicletas Feitas.\n");
        printf("\n-------------------------------------------------------------------------------------\n");

        printf("\nDistancias Medias Percorridas por Cada Bicicleta: \n");
        distanciaMedia(Bicicletas,cantidadBicicletas);

        printf("\nPercentagem de empréstimos efetuados por cada tipo de utente: \n");
        percentagemEmprestimosTipoUtente(Historico,historioPres);

        printf("\nCampus Origen com mais Emprestimos: \n");
        campusOrigenMaisEmprestimos(Historico,historioPres);

        printf("\nQuantidade de Utentes que Utilizaram uma determinada Bicicleta: \n");
        QuemUtilizoAquelaBicicleta(Bicicletas,cantidadBicicletas,Utentes,cantidadUtentes,Historico,historioPres);

        printf("\nEmprestimos Feitos entre duas datas: \n");
        emprestimosEntreDuasDatas(Historico,historioPres);

        break;
    case 'D':   //Se a opção for calcular e apresentar só as distancias medias.

        printf("\nDistancias Medias Percorridas por Cada Bicicleta: \n");
        distanciaMedia(Bicicletas,cantidadBicicletas);

        break;
    case 'P':   //Se a opção for calcular e apresentar só os percentagens.
        printf("\nPercentagem de empréstimos efetuados por cada tipo de utente: \n");
        percentagemEmprestimosTipoUtente(Historico,historioPres);

        break;
    case 'C':   //Se a opção for calcular e apresentar só o Campus com mais Emprestimos.
        printf("\nCampus Origen com mais Emprestimos: \n");
        campusOrigenMaisEmprestimos(Historico,historioPres);

        break;
    case 'Q':   //Se a opção for calcular e apresentar só Ultimo Utente que usou uma Bicicleta especifica.
        printf("\nQuantidade de Utentes que Utilizaram uma determinada Bicicleta: \n");
        QuemUtilizoAquelaBicicleta(Bicicletas,cantidadBicicletas,Utentes,cantidadUtentes,Historico,historioPres);

        break;
    case 'E':   //Se a opção for calcular e apresentar só os Emprestimos feitos entre duas datas.
        printf("\nEmprestimos Feitos entre duas datas: \n");
        emprestimosEntreDuasDatas(Historico,historioPres);

        break;

    }
}

int UtenteOcupado(tipoPrestamo Lista[],tipoPrestamo Prestamos[],int elementosNaLista,int cantidadPrestamos,int IDpreciso)
{

    int estado=0;
    int conta;

    if (elementosNaLista>0) //Se houver Elementos Na Lista...
    {
        for(conta=0; conta<elementosNaLista; conta++)   //Percorre o vetor de Lista de Espera.
        {
            if (IDpreciso==Lista[conta].ID_Utente_Reserva)
            {
                estado=1;       //Se encontrar, muda o valor da variavel que vai dar o aviso.
                printf("\nO Utente tem um Pedido de Emprestimo na Lista de Espera. Operacao Invalida.\n");
            }
        }
    }

    if (cantidadPrestamos>0)    //Se houver Elementos na Lista de Emprestimos...
    {
        for(conta=0; conta<cantidadPrestamos; conta++)  //Percorre o vetor de Lista de Emprestimos...
        {
            if (IDpreciso==Prestamos[conta].ID_Utente_Reserva)
            {
                estado=1;   //Se encontar, muda o valor da variavel que vai dar o aviso.
                printf("\nO Utente esta num Emprestimo. Operacao Invalida.\n");
            }
        }

    }

    return estado;
    //Se a variavel devolver 0, não permite fazer um novo Pedido de Emprestimo.

    //Função auxiliar que avisa se um ID de Utente já tem um Pedido de Empresitmo na Lista de Espera ou na Lista de Emprestimos.
}
