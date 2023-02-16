#ifndef MEMBROS_H_INCLUDED
#define MEMBROS_H_INCLUDED

#include "funcoes_aux.h"

#define MAX_MEMBROS 200

typedef struct
{
    int numeroUtente;
    char nome[MAX_STRING + 1];
    char membro[MAX_STRING + 1];
    int ano;
    char confinamento[MAX_STRING + 1];
    char vacinacao[MAX_STRING + 1];
    int tomaVacina;
    tipoData vacina;
    int numTestesAgendados;
    int numTestesRealizados;
    int numTestesPositivos;
} tipoMembro;



tipoMembro lerDadosMembros(int numeroMembro, int vetormembros[MAX_MEMBROS], int *entrada, int *numMembrosVacinados);
int leQuantidadeMembros();
void atualizarEstadoVacinacao(int numeroDeUtente, tipoMembro vetorMembros[MAX_MEMBROS], int numMembros, int *numMembrosVacinados );
void atualizarEstadoConfinamento(int numeroDeUtente, int numMembros,tipoMembro vetorMembros[MAX_MEMBROS], int *entrada);

void gravarFicheiroBinario(tipoMembro vetorMembros[MAX_MEMBROS], int numMembros);
void lerFicheiroBinario(tipoMembro vetorMembros[MAX_MEMBROS], int *numMembros);

#endif // MEMBROS_H_INCLUDED
