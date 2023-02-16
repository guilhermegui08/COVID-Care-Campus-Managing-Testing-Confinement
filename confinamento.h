#ifndef CONFINAMENTO_H_INCLUDED
#define CONFINAMENTO_H_INCLUDED

#include "funcoes_aux.h"
#include "membros.h"

#define TESTEPOSITIVO 1
#define TESTEINCONCLUSIVO 2
#define CONTACTOPROXIMO 3
#define UTILIZADOR 4

typedef struct
{
    int numUtente;
    char membro[MAX_STRING+1];
    char confinamento[MAX_STRING + 1];
    char nome[MAX_STRING + 1];
    tipoData data;
    int duracao;
} tipoConfinamento;

tipoConfinamento  *acrescentarConfinamento(tipoConfinamento *casosConfinamento, int *numTotalConfinados, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *entrada);
void listarCasosConfinamento(tipoConfinamento *casosConfinamento, int *numTotalConfinados);
#endif // CONFINAMENTO_H_INCLUDED
