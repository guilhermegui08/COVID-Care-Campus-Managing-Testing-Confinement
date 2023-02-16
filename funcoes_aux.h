#ifndef FUNCOES_AUX_H_INCLUDED
#define FUNCOES_AUX_H_INCLUDED

#define MAX_STRING 100

typedef struct
{
    int dia;
    int mes;
    int ano;
} tipoData;

typedef struct
{
    int hora;
    int minutos;
} tipoHora;



void cleanBufferStdin();
int lerInteiro(char mensagem[MAX_STRING], int min, int max);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maxCaracteres);
tipoData lerData(char mensagem[MAX_STRING]);

#endif // FUNCOES_AUX_H_INCLUDED
