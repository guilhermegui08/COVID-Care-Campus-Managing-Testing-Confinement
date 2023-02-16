#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_aux.h"


void cleanBufferStdin() //funcao para limpar o buffer stdin , desenvolvida em aula
{
    char chr;

    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}


int lerInteiro(char mensagem[MAX_STRING], int min, int max) //função para ler um numero inteiro, desenvolvida em aula
{
    int numero, controlo;
    printf("\n%s (%d a %d): ", mensagem, min, max);

    do
    {
        controlo = scanf("%d", &numero);
        cleanBufferStdin();
        if (controlo == 0)
        {
            printf("\tInsira um numero inteiro: ");
        }
        else
        {
            if(numero < min || numero > max)
            {
                printf("\tValor invalido. Insira novamente: ");
            }
        }
    }
    while(controlo == 0 || numero < min || numero > max);

    return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maxCaracteres) // funcao para ler uma string usada para registar o nome membros ,desenvolvida em aula
{
   int tamanhoString;
    printf("\n%s", mensagem);

    do
    {
        fgets(vetorCaracteres, maxCaracteres, stdin);
        tamanhoString = strlen(vetorCaracteres);
        if(tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres : ");
        }
    }
    while (tamanhoString == 1);

    if (vetorCaracteres[tamanhoString -1] != '\n')
    {
        cleanBufferStdin();
    }
    else
    {
        vetorCaracteres[tamanhoString -1] = '\0';
    }
}
tipoData lerData(char mensagem[MAX_STRING]) // função para ler uma data desenvolvida em aula
    {
        tipoData data;
        int maxDiasMes;

        printf("%s", mensagem);
        data.ano = lerInteiro("\n\t Ano",2015, 2022);
        data.mes = lerInteiro("\n\t Mes", 1, 12);

        switch (data.mes)
        {
        case 2:
            if (data.ano % 400 == 0 || (data.ano % 4 == 0 && data.ano % 100 != 0))
            {
                maxDiasMes = 29;
            }
            else
            {
                maxDiasMes = 28;
            }
            break;
        case 4:
            maxDiasMes = 30;
            break;
        case 6:
            maxDiasMes = 30;
            break;
        case 9:
            maxDiasMes = 30;
            break;
        case 11:
            maxDiasMes = 30;
            break;
        default:
            maxDiasMes = 31;
        }
        data.dia = lerInteiro("\n\t Dia", 1, maxDiasMes);

        return data;
    }


