#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_aux.h"
#include "membros.h"
#include "confinamento.h"

int leQuantidadeMembros() // lê a quantidade de membros
{
    int numMembros;
    numMembros = lerInteiro(" Numero de membros da comunidade: ", 1, MAX_MEMBROS);
    return numMembros;
}

tipoMembro lerDadosMembros(int numeroMembro, int vetormembros[MAX_MEMBROS], int *entrada, int *numMembrosVacinados) // função para registar a informacao dos membros
{

    int op,i,continuar; // variaveis auxiliares
    tipoMembro membro;


    printf("\n\t Inserir dados do %d membro",numeroMembro+1);

    do {
    membro.numeroUtente = lerInteiro("\n\t Numero de utente: ", 100000000, 999999999); // numero de utente provisorio
    vetormembros[numeroMembro] = membro.numeroUtente; // vetor auxiliar que copia o numero de utente provisorio
    for (i = 0; i <= numeroMembro; i++)
    {
        if (vetormembros[i]== membro.numeroUtente && numeroMembro!=i) // verifica se o numero de utente já existe ou nao
        {
            printf("\n\t Este numero de utente ja existe.");
            continuar = 0;
            i = numeroMembro;
        }else{
        continuar =1;
        }
    }
    }while(continuar == 0); //verifica se o numero de utente inserido já existe ou não
    lerString("\t Nome do utente: ",membro.nome,MAX_STRING);


    op = lerInteiro("\n\t Selecione o tipo de membro : \n\t  1- Estudante \n\t  2- Docente \n\t  3- Tecnico \n\t  Opcao: ",1,3); // introduz o tipo de membro
    switch(op)
    {
    case 1 :
        strcpy(membro.membro,"Estudante");
        break;
    case 2 :
        strcpy(membro.membro,"Docente");
        break;
    case 3 :
        strcpy(membro.membro,"Tecnico");
        break;
    }

    membro.ano = lerInteiro("\n\t Ano de nascimento: ",1900,2022);

    op = lerInteiro("\n\t Selecione o estado de confinamento : \n\t  1- Nao confirmado \n\t  2- Quarentena \n\t  3- Isolamento profilatico \n\t  Opcao: ",1,3); // introduz o estado de confinamento
    switch(op)
    {
    case 1 :
        strcpy(membro.confinamento,"Nao confinado");
        break;
    case 2 :
        strcpy(membro.confinamento,"Quarentena");
        *entrada = UTILIZADOR ; // parametro de entrada para a a funcao acrescentar confinamento
        break;
    case 3 :
        strcpy(membro.confinamento,"Isolamento profilatico");
        *entrada = UTILIZADOR ; // parametro de entrada para a a funcao acrescentar confinamento
        break;
    }

    op = lerInteiro("\n\t Selecione o estado de vacinacao : \n\t  1- Sem Vacina \n\t  2- Dose 1  \n\t  3- Dose 2 \n\t  4- Dose 3 \n\t  Opcao: ",1,4);
    switch(op)
    {
    case 1 :
        strcpy(membro.vacinacao,"Sem vacina");
        membro.tomaVacina = 0; // variavel que indica se o membro é ou nao vacinado
        break;
    case 2 :
        strcpy(membro.vacinacao,"Dose 1");
        break;
    case 3 :
        strcpy(membro.vacinacao,"Dose 2");
        break;
    case 4 :
        strcpy(membro.vacinacao,"Dose 3");
        break;
    }

    if (op>1 && op<=4) // verifica se o memmbro tomou alguma das dozes da vacina e introduz a data da ultima doze
    {
        membro.tomaVacina = 1;
        (*numMembrosVacinados)++;
        membro.vacina = lerData("\n\t Insira a data da sua ultima vacina : ");

    }

    membro.numTestesAgendados = 0 ; // inicializa a 0 algumas variáveis auxiliares
    membro.numTestesRealizados = 0 ;
     membro.numTestesPositivos = 0 ;

    system("cls");
    return membro;
}

void atualizarEstadoVacinacao(int numeroDeUtente, tipoMembro vetorMembros[MAX_MEMBROS], int numMembros, int *numMembrosVacinados )
{
    int membro,op ;

    for(membro=0; membro < numMembros; membro++) // este for verifica se o membro existe ou n
    {
        if(numeroDeUtente == vetorMembros[membro].numeroUtente)
        {
            op = lerInteiro("\n\t Selecione o estado de vacinacao : \n\t  1- Sem Vacina \n\t  2- Dose 1  \n\t  3- Dose 2 \n\t  4- Dose 3 \n\t  Opcao: ",1,4);
            switch(op)
            {
            case 1 :
                strcpy(vetorMembros[membro].vacinacao,"Sem vacina");
                if (vetorMembros[membro].tomaVacina == 1)
                {
                    (*numMembrosVacinados)--;
                }
                vetorMembros[membro].tomaVacina = 0;
                break;
            case 2 :
                strcpy(vetorMembros[membro].vacinacao,"Dose 1");
                break;
            case 3 :
                strcpy(vetorMembros[membro].vacinacao,"Dose 2");
                break;
            case 4 :
                strcpy(vetorMembros[membro].vacinacao,"Dose 3");
                break;
            }

            if (op>1 && op<=4)
            {
                if (vetorMembros[membro].tomaVacina == 1)
                {
                    vetorMembros[membro].tomaVacina = 1;
                }
                else
                {
                    vetorMembros[membro].tomaVacina = 1;
                    (*numMembrosVacinados)++;
                }
                vetorMembros[membro].vacina = lerData("\n\t Insira a data da sua ultima vacina : ");
            }
         membro = numMembros;
        }
        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }
}

void atualizarEstadoConfinamento(int numeroDeUtente, int numMembros,tipoMembro vetorMembros[MAX_MEMBROS], int *entrada)
{
    int membro, op;
    for(membro=0; membro < numMembros; membro++) // este for verifica se o membro existe ou n
    {
        if(numeroDeUtente == vetorMembros[membro].numeroUtente)
        {
            op = lerInteiro("\n\t Selecione o estado de confinamento : \n\t  1- Nao confirmado \n\t  2- Quarentena \n\t  3- Isolamento profilatico \n\t  Opcao: ",1,3);
            switch(op)
            {
            case 1 :
                strcpy( vetorMembros[membro].confinamento,"Nao confinado");
                (*entrada) = 0;
                break;
            case 2 :
                strcpy(vetorMembros[membro].confinamento,"Quarentena");
                (*entrada) = UTILIZADOR;
                break;
            case 3 :
                strcpy(vetorMembros[membro].confinamento,"Isolamento profilatico");
                (*entrada) = UTILIZADOR;
                break;
            }
        membro = numMembros;
        }

        else if (membro == numMembros-1)
        {
            printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
        }
    }
}

void gravarFicheiroBinario(tipoMembro vetorMembros[MAX_MEMBROS], int numMembros){
    FILE *ficheiro;
    int numEscritos;

    ficheiro = fopen("membros.dat", "wb");
    if (ficheiro == NULL){
        printf("Impossivel abrir ficheiro. \n");
    }else{
        numEscritos = fwrite(&numMembros, sizeof(int), 1, ficheiro);
        if (numEscritos != 1){
            printf ("Erro ao escrever o numero de Membros. \n");
        }else{
            numEscritos = fwrite(vetorMembros, sizeof(tipoMembro), numMembros, ficheiro);
            if (numEscritos != numMembros){
                printf ("Erro ao escrever dados dos Membros. \n");
            }
        }
        fclose(ficheiro);
    }
}


void lerFicheiroBinario(tipoMembro vetorMembros[MAX_MEMBROS], int *numMembros){
    FILE *ficheiro;
    int numLidos;

    ficheiro = fopen("membros.dat", "rb");
    if (ficheiro == NULL){
        printf("Impossivel abrir ficheiro. \n");
    } else{
        numLidos = fread(&(*numMembros), sizeof(int), 1, ficheiro);
        if (numLidos != 1){
            printf ("Erro ao obter informacao da quantidade de membros. \n");
            *numMembros = 0;
        } else{
            numLidos = fread(vetorMembros, sizeof(tipoMembro), *numMembros, ficheiro);
            if (numLidos != *numMembros){
                printf ("Erro ao obter informacao dos membros. \n");
                *numMembros = 0;
            }
        }
        fclose(ficheiro);
    }
}
