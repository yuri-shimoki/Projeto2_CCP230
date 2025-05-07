#pragma once

typedef enum
{
        LOGIN,
        MENU,
        CADASTRAR_INVESTIDOR,
        EXCLUIR_INVESTIDOR,
        CADASTRAR_CRIPTOMOEDA,
        EXCLUIR_CRIPTOMOEDA,
        CONSULTAR_SALDO,
        CONSULTAR_EXTRATO,
        ATUALIZAR_COTACAO,
        SAIR
} MenusAdministrador;

int admLogin(void);
int admMenu(void);

int admConsultarSaldo(void);
int admConsultarExtrato(void);