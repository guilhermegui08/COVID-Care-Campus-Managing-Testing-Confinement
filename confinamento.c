
#define NULL 0
#include "membros.h"
#include "confinamento.h"

// o grupo considerou que a quarentena dura 7 dias e o isolamento profilatico dura 10 dias
tipoConfinamento  *acrescentarConfinamento(tipoConfinamento *casosConfinamento, int *numTotalConfinados, tipoMembro vetorMembros[], int numDeUtente, int numMembros, int *entrada)
{
    int membro;
    tipoConfinamento confinamento;
    tipoConfinamento *auxConfinamento;

    if (*entrada != 0) // se a entrada for 0 significa que o utente não está infetado nem se encontra em quarentena ou isolamento
    {
        for(membro=0; membro < numMembros; membro++) // nesta função como em muitas outras este for serve para verificar se o numero de utente como parametro de entrada existe
        {
            if(numDeUtente == vetorMembros[membro].numeroUtente)
            {
                auxConfinamento = casosConfinamento;
                casosConfinamento = realloc(casosConfinamento, (*numTotalConfinados + 1) * sizeof(tipoConfinamento));

                if (casosConfinamento == NULL)
                {
                    printf("Impossivel reservar memoria para registar o caso de confinamento.");
                    casosConfinamento = auxConfinamento;
                }
                else
                {
                    if (*entrada == TESTEPOSITIVO) // significa que o utente testou positivo
                    {
                        printf("\n\t Inserir dados do isolamento profilatico");
                        confinamento.data = lerData("\n\t Em que dia o seu teste deu positivo :");
                        confinamento.duracao = 10 ;
                        strcpy(confinamento.confinamento,"Isolamento Profilatico");

                    }
                    else if (*entrada == TESTEINCONCLUSIVO) // significa que o utente testou inconclusivo e terá de fazer quarentena
                    {
                        printf("\n\t Inserir dados do confinamento");
                        confinamento.data = lerData("\n\t Em que dia o seu teste deu inconclusivo :");
                        confinamento.duracao = 7 ;
                        strcpy(confinamento.confinamento,"Quarentena");
                    }
                    else if (*entrada == CONTACTOPROXIMO)
                    {
                        confinamento.duracao = 10 ;
                        confinamento.data = lerData("\n\t Em que dia esteve em contacto com a pessoa : ");
                        strcpy(confinamento.confinamento,"Isolamento Profilatico");
                    }
                    else if (*entrada == UTILIZADOR) // significa que o utente declarou que já estava em quarentena ou isolamento no momento em que se registou ou alterou o estado de confinamento
                    {
                        if (vetorMembros[membro].confinamento[0] == 'Q')
                        {
                            confinamento.duracao = 7 ;
                            confinamento.data = lerData("\n\t Em que dia comecou a quarentena :");
                            strcpy(confinamento.confinamento,vetorMembros[membro].confinamento);
                        }
                        if (vetorMembros[membro].confinamento[0] == 'I')
                        {
                            confinamento.duracao = 10 ;
                            confinamento.data = lerData("\n\t Em que dia comecou o isolamento profilatico : ");
                            strcpy(confinamento.confinamento,vetorMembros[membro].confinamento);
                        }
                    }


                    strcpy(confinamento.membro,vetorMembros[membro].membro);
                    confinamento.numUtente = numDeUtente;
                    strcpy(confinamento.nome,vetorMembros[membro].nome);

                    casosConfinamento[*numTotalConfinados] = confinamento;

                    printf("\n\t O seu caso de confinamento foi registado");

                    (*numTotalConfinados)++;

                    membro = numMembros;
                }
            }
            else if (membro == numMembros-1)
            {
                printf("\n\t Erro, membro nao encontrado. Por favor insira outro numero de utente.");
            }
        }
    }
    return casosConfinamento;
}

void listarCasosConfinamento(tipoConfinamento *casosConfinamento, int *numTotalConfinados)
{
    int i = 0;
    printf("\n\t Lista dos casos de confinamento.");
    for (i=0; i< *numTotalConfinados; i++)
    {
        printf("\n\n\t Numero de utente : %d", casosConfinamento[i].numUtente);
        printf("\n\t Nome : ");
        puts(casosConfinamento[i].nome);
        printf("\t Tipo de membro : ");
        puts(casosConfinamento[i].membro);
        printf("\t Tipo de Confinamento : ");
        puts(casosConfinamento[i].confinamento);
        printf("\t Data de confinamento : %d / %d / %d", casosConfinamento[i].data.dia,casosConfinamento[i].data.mes,casosConfinamento[i].data.ano);
        printf("\n\t Tempo de confinamento : %d ", casosConfinamento[i].duracao);
    }
}
