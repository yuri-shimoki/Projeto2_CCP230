#pragma once

#include <stdio.h>

typedef enum
{
        LOGIN,
        MENU,
        SALDO,
        EXTRATO,
        DEPOSITO,
        SAQUE,
        COMPRA,
        VENDA,
        COTACAO,
        SAIR
} Menus;

int login(FILE* bancoDeDados, char* cpfDoUsuarioAtual);

int exibirMenu(void);

int exibirSaldo(void);

int exibirExtrato(void);

int depositarDinheiro(void);

int sacarDinheiro(void);

int comprarCriptomoeda(void);

int venderCriptomoeda(void);

int atualizarCotacao(void);