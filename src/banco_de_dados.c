#include "banco_de_dados.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int checarExistenciaDoUsuario(ListaDeUsuarios* listaDeUsuarios, char* cpf, char* senha)
{
        for (int i = 0; i < 10; ++i)
        {
                if (strcmp(listaDeUsuarios->usuarios[i].cpf, cpf) == 0 &&
                    strcmp(listaDeUsuarios->usuarios[i].senha, senha) == 0)
                        return i;
        }

        return -1;
}

int carregarListaDeUsuarios(FILE* bancoDeDados, ListaDeUsuarios* listaDeUsuarios)
{
        listaDeUsuarios = (ListaDeUsuarios*) malloc(sizeof(ListaDeUsuarios));

        if (listaDeUsuarios == NULL)
                return 1;

        int elementosLidos = fread(listaDeUsuarios, sizeof(ListaDeUsuarios), 1, bancoDeDados);
        
        if (ferror(bancoDeDados) != 0)
                return 2;

        if (listaDeUsuarios->quantidadeDeUsuarios > 10)
                return 3;

        return 0;
}

int carregarExtrato(FILE* arquivoDeExtratos, char* cpf, Extrato* extrato)
{
        Extrato* extratos = (Extrato*) malloc(10 * sizeof(Extrato));

        extrato = (Extrato*) malloc(sizeof(Extrato));

        if (extrato == NULL || extratos == NULL)
                return 1;

        rewind(arquivoDeExtratos);

        int elementosLidos = fread(extratos, sizeof(Extrato), 10, arquivoDeExtratos);

        if (ferror(arquivoDeExtratos) != 0)
                return 2;

        for (int i = 0; i < elementosLidos; ++i)
        {
                if (strcmp(extratos[i].cpf, cpf) == 0)
                {
                        *extrato = extratos[i];

                        free(extratos);

                        return 0;
                }
        }

        free(extratos);

        strcpy(extrato->cpf, cpf);
        extrato->quantidadeDeTransacoes = 0;

        return 3;
}

int salvarExtrato(FILE* arquivoDeExtratos, Extrato* extrato, int usuarioPossuiExtrato)
{        
        if (usuarioPossuiExtrato == 0)
        {
                fseek(arquivoDeExtratos, 0, SEEK_END);

                fwrite(extrato, sizeof(Extrato), 1, arquivoDeExtratos);

                if (ferror(arquivoDeExtratos) != 0)
                        return 2;

                return 0;
        }

        Extrato* extratoTemporario = (Extrato*) malloc(sizeof(Extrato));

        if (extratoTemporario == NULL)
                return 1;

        rewind(arquivoDeExtratos);

        for (int i = 0; i < 10; ++i)
        {
                fread(extratoTemporario, sizeof(Extrato), 1, arquivoDeExtratos);

                if (ferror(arquivoDeExtratos) != 0)
                {
                        free(extratoTemporario);
                        return 2;
                }

                if (strcmp(extratoTemporario->cpf, extrato->cpf) == 0)
                {
                        fseek(arquivoDeExtratos, -sizeof(Extrato), SEEK_CUR);

                        fwrite(extrato, sizeof(Extrato), 1, arquivoDeExtratos);

                        if (ferror(arquivoDeExtratos) != 0)
                        {
                                free(extratoTemporario);
                                return 2;
                        }

                        free(extratoTemporario);
                        return 0;
                }

                if (feof(arquivoDeExtratos) != 0)
                {
                        free(extratoTemporario);
                        return 3;
                }
        }

        return 4;
}

int salvarListaDeUsuarios(FILE* bancoDeDados, ListaDeUsuarios* listaDeUsuarios)
{
        rewind(bancoDeDados);

        fwrite(listaDeUsuarios, sizeof(ListaDeUsuarios), 1, bancoDeDados);

        if (ferror(bancoDeDados) != 0)
                return 1;
                
        return 0;
}

int registrarTransacao(Extrato* extrato, Transacao* transacao)
{
        if (extrato->quantidadeDeTransacoes < 100)
        {
                extrato->transacoes[extrato->quantidadeDeTransacoes] = *transacao;

                ++(extrato->quantidadeDeTransacoes);
                return 0;
        }

        if (extrato->quantidadeDeTransacoes > 100)
                return 1;

        for (int i = 0; i < 99; ++i)
                extrato->transacoes[i] = extrato->transacoes[i+1];

        extrato->transacoes[99] = *transacao;

        return 0;
}

int imprimirExtrato(Extrato* extrato)
{
        Transacao transacaoAtual;

        for (int i = extrato->quantidadeDeTransacoes - 1; i >= 0; --i)
        {
                transacaoAtual = extrato->transacoes[i];
                printf("%s %s %c %-13.6f %-8s R$%9.2f %13.6fBTC %13.6fETH %13.6fXRP\n",
                        transacaoAtual.data,
                        transacaoAtual.hora,
                        transacaoAtual.tipo,
                        transacaoAtual.valorDaTransacao,
                        transacaoAtual.moeda,
                        transacaoAtual.saldoReais,
                        transacaoAtual.saldoBitcoin,
                        transacaoAtual.saldoEthereum,
                        transacaoAtual.saldoRipple
                );
        }

        printf("\n");

        return 0;
}

void obterDataEHoraAtuais(char* data, char* hora)
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(data, "%02i-%02i-%04i", tm.tm_mday, tm.tm_mon, tm.tm_year);
        sprintf(hora, "%02i:%02i:%02i", tm.tm_hour, tm.tm_min, tm.tm_sec);
        
        return 0;
}