#ifndef TESTES_H_INCLUDED
#define TESTES_H_INCLUDED

#define INSERIR 1
#define PCR 1
#define ANTIGENIO 2

#include "membros.h"

typedef struct
{
    int designacao;
    int  tipo;
    tipoData data;
    int numeroUtente;
    char resultado[MAX_STRING + 1];
    char nome[MAX_STRING + 1];
    char vacinacao[MAX_STRING + 1];
    tipoHora hora;
    int tempo;
    int realizado;
} tipoTeste;

typedef struct
{
    tipoData data;
    int quanTestes;
    int validacao;
} tipoTesteDia;

 tipoTesteDia *verificaDia(tipoTesteDia *testesDiaPtr, int *numTestesPcr, tipoData *data, tipoTeste *testesPtr, int *numTestes);

tipoTeste lerDadosTeste(void);

tipoTeste *acrescentarTesteDIN(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *numTestesAgendados);
tipoTeste *acrescentarTestePCR(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *numTestesAgendados, tipoTesteDia *testesDiaPtr, int *numTestesPCR);
tipoTeste *alterarDataTeste(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, tipoTesteDia *testesDiaPtr, int *numTestesPCR);
tipoTeste *registarResultadoTeste(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *testesRealizados, int *testesAgendados, int *ultimoTeste, int *entrada,
                                  tipoTesteDia *testesDiaPtr, int *numTestesPCR);

void listarDadostestes(tipoTeste *testesPtr, int *numTestes);
void  apresentarTeste(tipoTeste *testesPtr, int *numTestes, tipoMembro vetorMembros[], int numDeUtente, int numMembros);

void gravarFicheiroBinarioTestes(tipoTeste *testesPtr, int numTotalTestes);
tipoTeste *lerFicheiroBinarioTestesDIN(tipoTeste *testesPtr, int *numTotalTestes);
void logTestes(tipoTeste teste, int operacao);

// a funcao que mostra dados dos membros e os testes agendados de cada membro encontra-se aqui devido a um conflito de dependencia de dados
void mostrarDados(tipoMembro vetorMembros[], int numMembros, tipoTeste *testesPtr, int *numTestes);

#endif // TESTES_H_INCLUDED
