#pragma once

#include <stdio.h>

typedef struct
{
        char cpf[12], senha[9], nome[65];
        float saldoReais, saldoBitcoin, saldoEthereum, saldoRipple;
} Usuario;

typedef struct
{
        unsigned int quantidadeDeUsuarios;
        Usuario usuarios[10];
} ListaDeUsuarios;

typedef struct
{
        char data[11], hora[9], tipo, moeda[9];
        float valorDaTransacao, saldoReais, saldoBitcoin, saldoEthereum, saldoRipple;
} Transacao;

typedef struct
{
        char cpf[12];
        unsigned int quantidadeDeTransacoes;
        Transacao transacoes[100];
} Extrato;

typedef struct
{
        float cotacaoBitcoin, cotacaoEthereum, cotacaoRipple;
} Cotacao;

int carregarListaDeUsuarios(FILE* bancoDeDados, ListaDeUsuarios* listaDeUsuarios);
int salvarUsuario(FILE* bancoDeDados, Usuario* usuarioAtual, int indiceDoUsuarioAtual, int quantidadeDeUsuarios);

int carregarExtrato(FILE* arquivoDeExtratos, char* cpf, Extrato* extrato);
int salvarExtrato(FILE* arquivoDeExtratos, Extrato* extrato, int usuarioPossuiExtrato);

int registrarTransacao(Extrato* extrato, Transacao* transacao);
void imprimirExtrato(Extrato* extrato);

int carregarCotacao(FILE* arquivoDeCotacao, Cotacao* cotacao);
int salvarCotacao(FILE* arquivoDeCotacao, Cotacao* cotacao);

int checarExistenciaDoUsuario(ListaDeUsuarios* listaDeUsuarios, char* cpf, char* senha);

int abrirArquivo(FILE** arquivo, const char* nome);

void obterDataEHoraAtuais(char* data, char* hora);