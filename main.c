#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "funcoes_aux.h"
#include "membros.h"
#include "testes.h"
#include "confinamento.h"


char menu(int numMembros, int membrosVacinados,int quanTestesRealizados, int quanTestesAgendados);
void apresentarDadosEstatisticos(tipoMembro vetorMembros[],tipoTeste *testesPtr,int numMembros, int numTotaTestes, int testesRealizados,int ultimoTeste);

int main()
{

    tipoMembro vetorMembros[MAX_MEMBROS];

    char op;
    int numMembros, membro, numMembrosVacinados = 0, quanTestesRealizados = 0, numTestesAgendados = 0;// variaveis para apresentar no menu alguns dados

    numMembros = leQuantidadeMembros();
    int numerosDeUtente[numMembros]; //vetor auxiliar para verificar se o numero de utente é único
    int numeroDeUtente, opcao, dadosInseridos = 0;   // variáveis auxiliares que servem de parâmetros de entrada para as funções

    int numTotalTestes = 0, ultimoTeste = 0, numTestesPCR = 0;
    tipoTesteDia *testesDiaPtr; // vetor dinamico que verifica o limite de 15 testes pcr por dia
    testesDiaPtr = NULL;
    tipoTeste *testesPtr; // vetor para armazenar os testes agendados e posteriormente realizados
    testesPtr = NULL;

    int numTotalConfinados = 0, entrada = 0; // variáveis auxiliares que servem de parametro de entrada para o vetor confinados
    tipoConfinamento *casosConfinamento; // vetor que guarda os casos de confinamento
    casosConfinamento = NULL;


    do
    {
        op = menu(numMembros, numMembrosVacinados, quanTestesRealizados, numTestesAgendados);
        switch(op)
        {
        case '1':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Registar membros da comunidade. \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                    if (dadosInseridos == 1) // verifica se já foram introduzidos os dados sobre os membros da comunidade
                    {
                        printf("\n\t Ja inseriu os dados dos membros da comunidade");
                    }
                    else
                    {
                        for(membro=0; membro < numMembros; membro++)
                        {
                            vetorMembros[membro]= lerDadosMembros(membro,  numerosDeUtente, &entrada, &numMembrosVacinados);
                            casosConfinamento = acrescentarConfinamento(casosConfinamento, &numTotalConfinados, vetorMembros, vetorMembros[membro].numeroUtente, numMembros, &entrada);
                            entrada = 0 ; // reset ao valor de entrada
                        }
                        dadosInseridos = 1;
                    }
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;
        case '2':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Atualizar estado de vacinacao de um membro. \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :

                    numeroDeUtente = lerInteiro("\n\t Insira o número de utente do Membro: ", 1, 1000000000); // o numero de utente serve de parametro de entrada para a função seguinte
                    atualizarEstadoVacinacao( numeroDeUtente, vetorMembros,numMembros,  (&numMembrosVacinados));
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case '3':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Atualizar estado de confinamento de um membro. \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :

                    numeroDeUtente = lerInteiro("\n\t Insira o número de utente do Membro: ", 100000000, 999999999);
                    atualizarEstadoConfinamento( numeroDeUtente,  numMembros, vetorMembros, &entrada);
                    casosConfinamento = acrescentarConfinamento(casosConfinamento, &numTotalConfinados, vetorMembros, numeroDeUtente, numMembros, &entrada);
                    if (entrada != 0) // entrada é um parametro de entrada para a função acrescentarConfinamento
                    {
                        do
                        {
                            opcao = lerInteiro("\n\t Esteve em contacto com alguem: \n\t 1- Sim. \n\t 2- Nao \n\t Opcao: ",1,2);// verifica se o membro infetado esteve em contacto com alguem
                            switch(opcao)
                            {
                            case 1 :
                                entrada = CONTACTOPROXIMO;
                                numeroDeUtente = lerInteiro("\n\t Insira o numero de utente do Membro que esteve em contacto: ", 100000000, 999999999);
                                casosConfinamento = acrescentarConfinamento(casosConfinamento, &numTotalConfinados, vetorMembros, numeroDeUtente, numMembros, &entrada);
                                break;
                            }
                        }
                        while(opcao == 1);
                    }
                    opcao=1;
                    entrada = 0; //reset ao valor de entrada
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case '4':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Agendar a realizacao de um teste  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :

                    numeroDeUtente = lerInteiro("\n\t Insira o número de utente do Membro: ", 100000000, 999999999);
                    testesPtr = acrescentarTesteDIN(testesPtr, &numTotalTestes, vetorMembros,numeroDeUtente, numMembros, &numTestesAgendados);
                    if (numTotalTestes > 0 && testesPtr[numTotalTestes-1].tipo == PCR)  // verifica se foi agendado algum teste e se é um pcr para verificar se o dia tem disponibilidade
                    {
                        testesDiaPtr = verificaDia(testesDiaPtr, &numTestesPCR, &testesPtr[numTotalTestes-1].data, testesPtr, &numTotalTestes);
                    }

                    break;
                }

            }
            while(opcao == 1);
            system("cls");
            break;

        case '5':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Listar os dados de todos os testes  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                    listarDadostestes(testesPtr, &numTotalTestes);
                    break;
                }

            }
            while(opcao == 1);
            system("cls");

            break;

        case '6':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Alterar a data agendada para a realizacao de um teste  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :

                    numeroDeUtente = lerInteiro("\n\t Insira o número de utente do Membro: ", 100000000, 999999999);
                    testesPtr = alterarDataTeste(testesPtr, &numTotalTestes, vetorMembros,numeroDeUtente, numMembros, testesDiaPtr, &numTestesPCR);

                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case '7':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Registar o resultado de um teste previamente agendado  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :

                    numeroDeUtente = lerInteiro("\n\t Insira o número de utente do Membro: ", 100000000, 999999999);
                    testesPtr = registarResultadoTeste(testesPtr, &numTotalTestes, vetorMembros,numeroDeUtente, numMembros, &quanTestesRealizados, &numTestesAgendados, &ultimoTeste, &entrada,
                                                       testesDiaPtr, &numTestesPCR );
                    casosConfinamento = acrescentarConfinamento(casosConfinamento, &numTotalConfinados, vetorMembros, numeroDeUtente, numMembros, &entrada);
                    if (entrada != 0) // verifica se o utente infetado esteve em contacto com alguem
                    {
                        do
                        {
                            opcao = lerInteiro("\n\t Esteve em contacto com alguem: \n\t 1- Sim. \n\t 2- Nao \n\t Opcao: ",1,2);
                            switch(opcao)
                            {
                            case 1 :
                                entrada = CONTACTOPROXIMO;
                                numeroDeUtente = lerInteiro("\n\t Insira o numero de utente do Membro que esteve em contacto: ", 100000000, 999999999);
                                casosConfinamento = acrescentarConfinamento(casosConfinamento, &numTotalConfinados, vetorMembros, numeroDeUtente, numMembros, &entrada);
                                break;
                            }
                        }
                        while(opcao == 1);
                    }
                    opcao=1;
                    entrada = 0;
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case '8':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Gravar  informacao em ficheiro Binario  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                     gravarFicheiroBinario(vetorMembros, numMembros);
                     gravarFicheiroBinarioTestes(testesPtr, numTotalTestes);
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case '9':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Ler em ficheiro Binario  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                        testesPtr = lerFicheiroBinarioTestesDIN(testesPtr, &numTotalTestes);
                        lerFicheiroBinario(vetorMembros, &numMembros);
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case 'A':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Apresentar a informacao de um teste (PCR ou Antigenio)  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                    numeroDeUtente = lerInteiro("\n\t Insira o número de utente do Membro: ", 100000000, 999999999);
                    apresentarTeste(testesPtr, &numTotalTestes, vetorMembros,numeroDeUtente, numMembros);
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case 'B':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Apresentar dados estatisticos.  \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :

                    apresentarDadosEstatisticos(vetorMembros, testesPtr, numMembros, numTotalTestes, quanTestesRealizados, ultimoTeste);
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case 'C':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Listar casos de confinamento. \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                    if (numTotalConfinados == 0 ) // verifica se existem casos de confinamento para serem listados
                    {
                        printf("\n\t Ainda nao foram registados casos de confinamento:");
                    }
                    else
                    {
                        listarCasosConfinamento( casosConfinamento, &numTotalConfinados);
                    }
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;

        case 'D':
            do
            {
                opcao = lerInteiro("\n\t O que pretende fazer: \n\t 1- Listar informacao dos membros da comunidade. \n\t 2- Sair para o menu \n\t Opcao: ",1,2);
                switch(opcao)
                {
                case 1 :
                    if (dadosInseridos == 0 ) // verifica se os membros já estão registados
                    {
                        printf("\n\t Ainda nao foram inseridos os dados sobre os membros:");
                    }
                    else
                    {
                        mostrarDados(vetorMembros, numMembros, testesPtr, &numTotalTestes);
                    }
                    break;
                }
            }
            while(opcao == 1);
            system("cls");
            break;
        }

    }
    while (op!='S');
    free(testesPtr);
    free(casosConfinamento);
    free(testesDiaPtr);
    return 0;
}


char menu(int numMembros, int membrosVacinados,int quanTestesRealizados, int quanTestesAgendados)
{
    char op;
    do
    {
        printf("\n \t\t*\t*\t*\tMenu\t*\t*\t*\t\n\n ");
        printf("\n\t\t  Quantidade de membros             :\t %d ",numMembros);
        printf("\n\t\t  Quantidade de testes agendados    :\t %d ", quanTestesAgendados);
        printf("\n\t\t  Quantidade de testes realizados   :\t %d ", quanTestesRealizados);
        printf("\n\t\t  Quantidade de membros vacinados   :\t %d \n",membrosVacinados);
        printf("\n   Insira uma operacao a realizar: \n");
        printf("\n     1- Registar membros da comunidade.");
        printf("\n     2- Registar/atualizar o estado de vacinacao de um membro.");
        printf("\n     3- Registar/atualizar o estado de confinamento de um membro.");
        printf("\n     4- Agendar a realizacao de um teste (Maximo 15 PCR por dia).");
        printf("\n     5- Listar dados de todos os testes.");
        printf("\n     6- Alterar a data agendada para a realizacao de um teste.");
        printf("\n     7- Registar o resultado de um teste previamente agendado.");
        printf("\n     8- Armazenar em Ficheiro binario a informacao referente aos membros e aos testes agendados.");
        printf("\n     9- Ler em Ficheiro binario.");
        printf("\n     A- Apresentar a informacao de um teste (PCR ou Antigenio)");
        printf("\n     B- Mostrar dados estatisticos.");
        printf("\n     C- Listagem dos casos de confinamento.");
        printf("\n     D- Listar informacao dos membros da comunidade.");
        printf("\n     S- Sair.");
        printf("\n   Opcao: ");
        scanf("%c", &op);
        op = toupper(op);
        cleanBufferStdin();
        system("cls");
    }
    while(op != '1'&& op != '2' && op != '3' && op != '4' && op != '5' && op != '6' && op != '7' && op != '8' && op != '9' && op!= 'A' && op!= 'B' && op!= 'C' && op!= 'S' && op!= 'D');
    return op;
}
void apresentarDadosEstatisticos(tipoMembro vetorMembros[],tipoTeste *testesPtr,int numMembros, int numTotaTestes, int testesRealizados, int ultimoTeste)
{
    int i = 0, estudante = 0, docente = 0, tecnico = 0, tempoTeste = 0, contador = 0, testesInconclusivos = 0;
    float tempoMedio = 0, percentagemInconclusivos = 0, menorQuantidadeTestes = testesRealizados;

    for (i = 0; i < numMembros; i++)
    {
        if (vetorMembros[i].membro[0] == 'E')
        {
            estudante++;
        }
        if (vetorMembros[i].membro[0] == 'D')
        {
            docente++;
        }
        if (vetorMembros[i].membro[0] == 'T')
        {
            tecnico++;
        }
        if (menorQuantidadeTestes > vetorMembros[i].numTestesRealizados)
        {
            menorQuantidadeTestes = vetorMembros[i].numTestesRealizados;
        }
    }
    i = 0;
    printf("\n\t Dados estatisticos ");
    printf("\n\t Quantidade de membro(s) estudante(s) : %d", estudante);
    printf("\n\t Quantidade de docente(s) : %d", docente);
    printf("\n\t Quantidade de tecnico(s) : %d",tecnico);
    for (i = 0; i < numTotaTestes; i++)
    {
        if(testesPtr[i].realizado == 1)
        {
            tempoTeste = testesPtr[i].tempo + tempoTeste;
            contador++;
        }
        if(testesPtr[i].resultado[0] == 'I')
        {
            testesInconclusivos++;
        }
    }
    if (contador == 0 )
    {
        printf("\n\t Ainda nao foram realizados testes.");
    }
    else
    {
        tempoMedio = tempoTeste / contador;
        printf("\n\t Tempo medio de duracao de cada teste realizado : %0.2f",tempoMedio);
        percentagemInconclusivos = (testesInconclusivos / testesRealizados) * 100;
        printf("\n\t Percentagem de testes realizados : %0.2f %%",percentagemInconclusivos);
        printf("\n\t Membros da comunidade academica com a menor quantidade de testes realizados ");
        i = 0;
        for (i = 0; i < numMembros; i++)
        {
            if (menorQuantidadeTestes == vetorMembros[i].numTestesRealizados)
            {
                printf("\n\t Numero de utente : %d",vetorMembros[i].numeroUtente );
                printf("\n\t Nome : ");
                puts(vetorMembros[i].nome);
                printf("\t Quantidade de testes realizados : %d",vetorMembros[i].numTestesRealizados);
            }
        }
        if (ultimoTeste == 0 )
        {
            printf("\n\t Ainda nao foram realizados testes.");
        }
        else
        {

            printf("\n\t Teste realizado mais recentemente  ");
            i=0;
            for (i = 0; i < testesRealizados; i++)
            {
                if (testesPtr[i].designacao == ultimoTeste)
                {
                    printf("\n\t Designacao : %d",testesPtr[i].designacao);
                    printf("\n\t Nome : ");
                    puts(testesPtr[i].nome);
                    printf("\t Numero de utente : %d",testesPtr[i].numeroUtente);
                    printf("\n\t Resultado : ");
                    puts(testesPtr[i].resultado);
                }
            }
        }
    }
}
