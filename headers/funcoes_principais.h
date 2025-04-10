#pragma once

#include <stdio.h>

#include "banco_de_dados.h"

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

int login(ListaDeUsuarios* listaDeUsuarios, Usuario* usuarioAtual);

int exibirMenu(void);

void exibirSaldo(Usuario* usuarioAtual);

int exibirExtrato(void);

int depositarDinheiro(Usuario* usuarioAtual, Extrato* extrato);

int sacarDinheiro(void);

int comprarCriptomoeda(void);

int venderCriptomoeda(void);

int atualizarCotacao(void);