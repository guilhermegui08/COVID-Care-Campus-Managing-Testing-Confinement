#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_aux.h"
#include "testes.h"
#include "confinamento.h"

// esta funcao mostrar dados encontra-se aqui por causa de um conflito de dependencia de dados
void mostrarDados(tipoMembro vetorMembros[], int numMembros, tipoTeste *testesPtr, int *numTestes)
{
    int i, teste;

    if (numMembros == 0)
    {
        printf("\n\n Ainda nao existem estudantes inscritos \n\n");
    }
    else
    {

        for (i = 0; i < numMembros; i++)
        {
            printf("\n\n\t Dados %d membro  ", i+1);
            printf("\n\t Numero de utente : %d",vetorMembros[i].numeroUtente );
            printf("\n\t Nome : ");
            puts(vetorMembros[i].nome);
            printf("\t Tipo de membro : ");
            puts(vetorMembros[i].membro);
            printf("\t Ano de nascimento : %d",vetorMembros[i].ano );
            printf("\n\t Estado de confinamento : ");
            puts(vetorMembros[i].confinamento);
            if (vetorMembros[i].tomaVacina == 0 )
            {
                printf("\t Estado de vacinacao : ");
                puts(vetorMembros[i].vacinacao);
            }
            else
            {
                printf("\t Estado de vacinacao : ");
                puts(vetorMembros[i].vacinacao);
                printf("\t Dia : %d",vetorMembros[i].vacina.dia );
                printf("\n\t Mes : %d",vetorMembros[i].vacina.mes );
                printf("\n\t Ano : %d",vetorMembros[i].vacina.ano );
            }
            printf("n\t Quantidade de testes realizados : %d",vetorMembros[i].numTestesRealizados);
            if (vetorMembros[i].numTestesAgendados > 0) // verifica se o membro já agendou algum teste
            {
                printf("\n\t Testes Agendados ------");
                for (teste = 0; teste < *numTestes; teste++)
                {
                    if (testesPtr[teste].numeroUtente == vetorMembros[i].numeroUtente && testesPtr[teste].realizado == 0)
                    {
                        if (testesPtr[teste].tipo == 1 )
                        {
                            printf("\n\t Tipo de teste : PCR.");
                        }
                        else
                        {
                            printf("\n\t Tipo de teste : Antigenio.");
                        }
                        printf("\n\t Data agendada para a realizacao do teste : \n\t Dia : %d \n\t Mes : %d \n\t Ano : %d ",
                               testesPtr[teste].data.dia,testesPtr[teste].data.mes,testesPtr[teste].data.ano);
                    }
                }
            }

        }
    }
}


tipoTeste lerDadosTeste(void) // função que pede ao utilizador dados para o agendamento de u  teste
{
    tipoTeste teste;

    printf("\n\t Inserir dados do Teste\n");
    teste.data = lerData("\n\t Em que dia pretende realizar o teste :");
    teste.tipo = lerInteiro("\n\t Tipo de teste  1- PCR 2- Antigenio ", PCR, ANTIGENIO);
    teste.realizado = 0;

    return teste;
}

tipoTeste *acrescentarTesteDIN(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *numTestesAgendados)
{

    int membro;
    tipoTeste teste;
    tipoTeste *auxPtr;


    for(membro=0; membro < numMembros; membro++)
    {
        if(numDeUtente == vetorMembros[membro].numeroUtente) // verifica se o numero de utente existe
        {
            auxPtr = testesPtr;
            testesPtr = realloc(testesPtr, (*numTestes + 1) * sizeof(tipoTeste));

            if (testesPtr == NULL)
            {
                printf("Impossivel reservar memoria para o agendar o teste.");
                testesPtr = auxPtr;
            }
            else
            {
                teste = lerDadosTeste();

                teste.numeroUtente = numDeUtente;
                strcpy(teste.nome,vetorMembros[membro].nome);


                if (*numTestes == 0)
                {
                    teste.designacao = 1;
                }
                else
                {
                    teste.designacao = testesPtr[*numTestes - 1].designacao + 1;
                }

                testesPtr[*numTestes] = teste;



                vetorMembros[membro].numTestesAgendados++;
                printf("\n\t O utente numero %d ja agendou %d teste(s).\n",
                       numDeUtente,
                       vetorMembros[membro].numTestesAgendados);
                printf("\n\t O seu teste agendado tem a designacao : %d.\n",teste.designacao);

                (*numTestes)++;
                (*numTestesAgendados)++;
                membro = numMembros;
            }
        }
        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }
    return testesPtr;
}

// funcao que acrescenta apenas um teste pcr ao vetor dos testes *testesPtr usada quando um teste dá inconclusivo ou um antigenio dá positivo
tipoTeste *acrescentarTestePCR(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *numTestesAgendados, tipoTesteDia *testesDiaPtr, int *numTestesPCR)
{

    int membro;
    tipoTeste teste;
    tipoTeste *auxPtr;


    for(membro=0; membro < numMembros; membro++)
    {
        if(numDeUtente == vetorMembros[membro].numeroUtente)
        {
            auxPtr = testesPtr;
            testesPtr = realloc(testesPtr, (*numTestes + 1) * sizeof(tipoTeste));

            if (testesPtr == NULL)
            {
                printf("Impossivel reservar memoria para o agendar o teste.");
                testesPtr = auxPtr;
            }
            else
            {
                teste.tipo = PCR;

                teste.data = lerData("\n\t Em que dia pretende realizar o teste PCR:");
                testesDiaPtr = verificaDia(testesDiaPtr, numTestesPCR, &teste.data, testesPtr, numTestes); // verifica se o dia tem disponibilidade para agendar o pcr
                teste.numeroUtente = numDeUtente;
                strcpy(teste.nome,vetorMembros[membro].nome);

                if (*numTestes == 0)
                {
                    teste.designacao = 1;
                }
                else
                {
                    teste.designacao = testesPtr[*numTestes - 1].designacao + 1;
                }

                testesPtr[*numTestes] = teste;

                logTestes(testesPtr[*numTestes], INSERIR);

                vetorMembros[membro].numTestesAgendados++;
                printf("\n\t O utente numero %d ja agendou %d teste(s).\n",
                       numDeUtente,
                       vetorMembros[membro].numTestesAgendados);
                printf("\n\t O seu teste agendado tem a designacao : %d.\n",teste.designacao);

                (*numTestes)++;
                (*numTestesAgendados)++;
                membro = numMembros;
            }
        }
        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }
    return testesPtr;
}

// funcao que verifica se o dia tem disponibilidade para ser realizado um teste pcr
tipoTesteDia *verificaDia(tipoTesteDia *testesDiaPtr, int *numTestesPcr, tipoData *data, tipoTeste *testesPtr, int *numTestes)
{
    int i = 0;
    tipoTesteDia testedia;
    tipoTesteDia *auxPtr;
    if (*numTestesPcr == 0) // verifica se já existe algum dia para o qual está agendado um teste , a variável numtestesPcr conta o numero de dias diferentes para os quais estao agendados testes pcr
    {
        auxPtr = testesDiaPtr;
        testesDiaPtr = realloc(testesDiaPtr, (*numTestesPcr + 1) * sizeof(tipoTesteDia));

        if (testesDiaPtr == NULL)
        {
            printf("Impossivel reservar memoria para o agendar o teste.");
            testesDiaPtr = auxPtr;
        }
        else
        {

            testedia.data = *data;
            testedia.quanTestes=1;
            testedia.validacao = 1;
            printf("\n\t O seu teste PCR tem possibilidade de ser agendado.");
            testesDiaPtr[*numTestesPcr] = testedia;
            (*numTestesPcr)++;
        }
    }
    else // caso já haja um dia para o qual estao agendados testes pcr vai verificar se há disponibilidade para esse dia ou então cria uma nova posicao no vetor testesDiaPtr com um dia diferente
    {
        do
        {
            for (i = 0; i < *numTestesPcr; i++)
            {

                if ( testesDiaPtr[i].data.dia == data->dia && testesDiaPtr[i].data.mes == data->mes && testesDiaPtr[i].data.ano == data->ano )
                {
                    testesDiaPtr[i].quanTestes =testesDiaPtr[i].quanTestes + 1;
                    if (testesDiaPtr[i].quanTestes > 15)
                    {
                        printf("\n\t O seu teste PCR nao tem possibilidade de ser agendado.");

                         *data = lerData("\n\t Em que dia pretende realizar o teste :");
                        testesDiaPtr[i].validacao= 0;
                        testedia.validacao = 0;
                    }else {
                    printf("\n\t O seu teste PCR tem possibilidade de ser agendado.");
                        i = *numTestesPcr;
                    }
                    }

                else
                {
                    auxPtr = testesDiaPtr;
                    testesDiaPtr = realloc(testesDiaPtr, (*numTestesPcr + 1) * sizeof(tipoTesteDia));

                    if (testesDiaPtr == NULL)
                    {
                        printf("Impossivel reservar memoria para o agendar o teste.");
                        testesDiaPtr = auxPtr;
                    }
                    else
                    {

                        testedia.data = *data;
                        testedia.quanTestes=1;
                        testedia.validacao = 1;
                        printf("\n\t O seu teste PCR tem possibilidade de ser agendado.");

                        i = *numTestesPcr;
                        testesDiaPtr[*numTestesPcr] = testedia;
                        (*numTestesPcr)++;
                    }
                }
            }
        }
        while( testedia.validacao == 0 );

    }
    return testesDiaPtr;
}

void logTestes(tipoTeste teste, int operacao)   // operacao = 1 agenda
{
    FILE *ficheiro;

    ficheiro = fopen("logTestes.txt", "a");
    if (ficheiro == NULL)
    {
        perror("\n\t Erro na abertura do ficheiro. \n");
    }
    else
    {
        if (operacao == INSERIR)
        {
            fprintf(ficheiro,"\n\t Teste %d  %02d/%02d/%04d  ",
                    teste.designacao,
                    teste.data.dia,
                    teste.data.mes,
                    teste.data.ano);
            if (teste.tipo == 1){
                fprintf(ficheiro, "\n\t PCR");
            }
            else{
               fprintf(ficheiro, "\n\t Antigenio");
            }

            fprintf(ficheiro, "\n\t Numero de utente: %d ", teste.numeroUtente);
            fprintf(ficheiro, "\n\t Nome: ");
            fputs(teste.nome, ficheiro);
            fprintf(ficheiro, "\n\t Estado de vacinacao: ");
            fputs( teste.vacinacao, ficheiro);
            fprintf(ficheiro, "\n\t Resultado: ");
            fputs( teste.resultado, ficheiro);
        }

        fclose(ficheiro);
    }
}

// funcao que alera a data de um teste agendado
tipoTeste *alterarDataTeste(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, tipoTesteDia *testesDiaPtr, int *numTestesPCR)
{
    int membro, i;

    for(membro=0; membro < numMembros; membro++)
    {
        if(numDeUtente == vetorMembros[membro].numeroUtente) // verifica se o numero de utente existe
        {
            if (*numTestes == 0)
            {
                printf("\n\t Ainda nao foram agendados testes.");
            }
            else
            {
                i = lerInteiro("Insira a designacao do teste", 1, *numTestes); // verifica se o teste agendado pertence ao numero de utente de quem o agendou e se já foi realizado
                if (testesPtr[i-1].numeroUtente == numDeUtente)
                {
                    if (testesPtr[i-1].realizado == 1)
                    {
                        printf("\n\t Este teste ja foi realizado.");
                    }
                    testesPtr[i-1].data= lerData("\n\t Insira a nova data para a realizacao do teste: ");
                    if (testesPtr[i-1].tipo == PCR){
                       testesDiaPtr = verificaDia(testesDiaPtr, numTestesPCR, &testesPtr[i-1].data, testesPtr, numTestes);
                    }

                }
                else
                {
                    printf("\n\t Este teste nao lhe pertence.");
                }
            }

            membro = numMembros;
        }
        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }
    return testesPtr;
}


tipoTeste *registarResultadoTeste(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *testesRealizados, int *testesAgendados, int *ultimoTeste, int *entrada,
                                  tipoTesteDia *testesDiaPtr, int *numTestesPCR)
{
    *entrada = 0;
    int membro, i, op;
    for(membro=0; membro < numMembros; membro++)
    {
        if(numDeUtente == vetorMembros[membro].numeroUtente) // verifica se o numero de utente existe
        {
            if (*numTestes == 0)
            {
                printf("\n\t Ainda nao foram agendados testes."); // verifica se há testes agendados
            }
            else
            {
                i = lerInteiro("\n\t Insira a designacao do teste", 1, *numTestes); // caso hajam testes agendados verifica se pertencem ao numero de utente que os agendou
                if (testesPtr[i-1].numeroUtente == numDeUtente)
                {
                    if (testesPtr[i-1].realizado == 1)
                    {
                        printf("\n\t Este teste ja foi realizado.");
                    }
                    else
                    {
                        testesPtr[i-1].hora.hora = lerInteiro("\n\t A que horas realizou o teste : \n\t  Hora : ",0,23);
                        testesPtr[i-1].hora.minutos = lerInteiro("\n\t Minuto : ",0,59);
                        testesPtr[i-1].tempo = lerInteiro("\n\t Quantos minutos demorou o teste a ser realizado:  ",0,60);

                        strcpy(testesPtr[i-1].nome,vetorMembros[membro].nome);
                        strcpy(testesPtr[i-1].vacinacao,vetorMembros[membro].vacinacao);

                        testesPtr[i-1].realizado = 1;
                        vetorMembros[membro].numTestesAgendados--;
                        vetorMembros[membro].numTestesRealizados++;
                        (*testesAgendados)--;
                        (*testesRealizados)++;
                        (*ultimoTeste) =  testesPtr[i-1].designacao;

                        op = lerInteiro("\n\t Selecione o resultado do teste realizado : \n\t  1- Positivo \n\t  2- Negativo  \n\t  3- Inconclusivo \n\t  Opcao: ",1,3);
                        switch(op)
                        {
                        case 1 :
                            strcpy(testesPtr[i-1].resultado,"Positivo");
                            vetorMembros[membro].numTestesPositivos++;
                            strcpy(vetorMembros[membro].confinamento,"Isolamento profilatico");
                            if (testesPtr[i-1].tipo == ANTIGENIO)
                            {
                                printf("\n\t O seu teste antigenio foi positivo tera de agendar outro teste PCR.");
                                testesPtr = acrescentarTestePCR(testesPtr, numTestes, vetorMembros, numDeUtente, numMembros, testesAgendados, testesDiaPtr, numTestesPCR);
                                *entrada = TESTEPOSITIVO;
                            }
                            break;
                        case 2 :
                            strcpy(testesPtr[i-1].resultado,"Negativo");
                            *entrada = 0;
                            break;
                        case 3 :
                            strcpy(testesPtr[i-1].resultado,"Inconclusivo");
                            strcpy(vetorMembros[membro].confinamento,"Quarentena");
                            printf("\n\t O seu teste foi inconclusivo tera de agendar outro teste PCR.");
                            testesPtr = acrescentarTestePCR(testesPtr, numTestes, vetorMembros, numDeUtente, numMembros, testesAgendados, testesDiaPtr, numTestesPCR);
                            *entrada = TESTEINCONCLUSIVO;
                            break;
                        }

                        logTestes(testesPtr[i-1], INSERIR);
                    }
                }
                else
                {
                    printf("\n\t Este teste nao lhe pertence.");
                }
            }

            membro = numMembros;
        }
        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }
    return testesPtr;
}

void listarDadostestes(tipoTeste *testesPtr, int *numTestes)
{
    if (*numTestes == 0)
    {
        printf("\n\t Ainda nao foram realizados ou agendados tetes.");
    }
    else
    {
        int i;
        for(i = 0; i < *numTestes ; i++)
        {
            printf("\n\n\t Designacao : %d",testesPtr[i].designacao );
            if (testesPtr[i].tipo == 1)
            {
                printf("\n\t Tipo : PCR");
            }
            else
            {
                printf("\n\t Tipo : Antigenio");
            }
            printf("\n\t Data agendada : \n\t Dia: %d \n\t Mes: %d \n\t Ano: %d ", testesPtr[i].data.dia,testesPtr[i].data.mes,testesPtr[i].data.ano);
            printf("\n\t Numero de utente : %d",testesPtr[i].numeroUtente);
            printf("\n\t Nome : ");
            puts(testesPtr[i].nome);

            if (testesPtr[i].realizado == 1)
            {
                printf("\t Resultado : ");
                puts(testesPtr[i].resultado);
                printf("\t Hora de realizacao -> %d:%d",testesPtr[i].hora.hora,testesPtr[i].hora.minutos);
                printf("\n\t Tempo de realizacao -> %d minutos",testesPtr[i].tempo);


            }
            else
            {
                printf("\n\t O teste ainda nao foi realizado");
            }
        }

    }
}

void  apresentarTeste(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros)
{
    int membro, i;
    for(membro=0; membro < numMembros; membro++)
    {
        if(numDeUtente == vetorMembros[membro].numeroUtente)
        {
            if (*numTestes == 0)
            {
                printf("\n\t Ainda nao foram agendados testes.");
            }
            else
            {
                i = lerInteiro("\n\t Insira a designacao do teste", 1, *numTestes);
                if (testesPtr[i-1].numeroUtente == numDeUtente)
                {
                    printf("\n\n\t Designacao : %d",testesPtr[i-1].designacao );
                    if (testesPtr[i-1].tipo == 1)
                    {
                        printf("\n\t Tipo : PCR");
                    }
                    else
                    {
                        printf("\n\t Tipo : Antigenio");
                    }
                    printf("\n\t Numero de utente : %d",testesPtr[i-1].numeroUtente);
                    printf("\n\t Nome : ");
                    puts(testesPtr[i-1].nome);
                    printf("\t Tipo de membro : ");
                    puts(vetorMembros[membro].membro);
                    printf("\t Quantidade de testes poditivos : %d",vetorMembros[membro].numTestesPositivos);
                    if (testesPtr[i-1].realizado == 1)
                    {
                        printf("\n\t Resultado : ");
                        puts(testesPtr[i-1].resultado);
                        printf("\t Hora de realizacao -> %d:%d",testesPtr[i-1].hora.hora,testesPtr[i-1].hora.minutos);
                        printf("\n\t Tempo de realizacao -> %d minutos",testesPtr[i-1].tempo);

                    }
                    else
                    {
                        printf("\n\t O teste ainda nao foi realizado");
                    }
                }
                else
                {
                    printf("\n\t Este teste nao lhe pertence.");
                }
            }

            membro = numMembros;
        }
        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }

}

void gravarFicheiroBinarioTestes(tipoTeste *testesPtr, int numTotalTestes)
{
    FILE *ficheiro;
    int numEscritos;

    ficheiro = fopen("testes.dat", "wb");
    if (ficheiro == NULL)
    {
        printf("Impossivel abrir ficheiro.\n");
    }
    else
    {
        numEscritos = fwrite(&numTotalTestes, sizeof(int), 1, ficheiro);
        if (numEscritos != 1)
        {
            printf ("Erro ao escrever a quantidade de aulas. \n");
        }
        numEscritos = fwrite(testesPtr, sizeof(tipoTeste), numTotalTestes, ficheiro);
        if (numEscritos != numTotalTestes)
        {
            printf ("Erro ao escrever dados dos testes");
        }
        fclose(ficheiro);
    }
}

tipoTeste *lerFicheiroBinarioTestesDIN(tipoTeste *testesPtr, int *numTotalTestes)
{
    FILE *ficheiro;
    int numLidos;

    ficheiro = fopen("testes.dat", "rb");
    if (ficheiro == NULL)
    {
        printf("Impossivel abrir ficheiro. \n");
    }
    else
    {
        numLidos = fread(&(*numTotalTestes), sizeof(int), 1, ficheiro);
        if (numLidos != 1)
        {
            printf ("Erro obter informacao da quantidade de testes. \n");
            *numTotalTestes = 0;
        }
        else
        {
            testesPtr = realloc(testesPtr, (*numTotalTestes) * sizeof(tipoTeste));
            if(testesPtr == NULL && *numTotalTestes != 0)
            {
                printf("Erro ao reservar memoria.\n");
                *numTotalTestes = 0;
            }
            else
            {
                numLidos = fread(testesPtr, sizeof(tipoTeste), *numTotalTestes, ficheiro);
                if (numLidos != *numTotalTestes)
                {
                    printf ("Erro obter informacao sobre os testes agendados. \n");
                    free(testesPtr);
                    testesPtr = NULL;
                    *numTotalTestes = 0;
                }
            }
        }
        fclose(ficheiro);
    }
    return testesPtr;
}
