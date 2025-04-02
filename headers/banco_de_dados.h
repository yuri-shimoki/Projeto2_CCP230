#pragma once

#include <stdio.h>

typedef struct
{
        char cpf[12], senha[9], nome[65];
        float saldoReais, saldoBitcoin, saldoEthereum, saldoRipple;
} Usuario;

typedef struct
{
        Usuario usuarios[10];
} ListaDeUsuarios;

typedef struct
{
        char data[9], hora[9], tipo, moeda[9];
        float valorDaTransacao, saldoReais, saldoBitcoin, saldoEthereum, saldoRipple;
} Transacao;

typedef struct
{
        Transacao transacoes[100];
} Extrato;

int carregarListaDeUsuarios(FILE* bancoDeDados, ListaDeUsuarios* listaDeUsuarios);
int carregarExtrato(FILE* arquivoDeExtratos, Extrato* extrato);

int checarExistenciaDoUsuario(ListaDeUsuarios* listaDeUsuarios, char* cpf, char* senha);