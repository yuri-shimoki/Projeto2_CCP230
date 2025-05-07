/*
#include <stdio.h>

#include "funcoes_administrador.h"
#include "banco_de_dados.h"

#include "funcoes_principais.h"

int main(void)
{
    int codigoDeRetorno;

    MenusAdministrador menuAtual = LOGIN;

    FILE* arquivoDeUsuarios;
    codigoDeRetorno = abrirArquivo(&arquivoDeUsuarios, "usuarios.bin");

    FILE* arquivoDeExtratos;
    codigoDeRetorno = abrirArquivo(&arquivoDeExtratos, "extratos.bin");

    FILE* arquivoDeCriptomoedas;
    codigoDeRetorno = abrirArquivo(&arquivoDeUsuarios, "criptomoedas.bin");

    ListaDeUsuarios* listaDeUsuarios = (ListaDeUsuarios*) malloc(sizeof(ListaDeUsuarios));

    listaDeUsuarios->quantidadeDeUsuarios = 0;

    Extrato* extrato = (Extrato*) malloc(sizeof(Extrato));
    int usuarioPossuiExtrato = 1;
    
    codigoDeRetorno = carregarListaDeUsuarios(arquivoDeUsuarios, listaDeUsuarios);

    codigoDeRetorno = carregarCotacao(arquivoDeCriptomoedas, &cotacao);

    while (menuAtual != SAIR)
    {
        switch (menuAtual)
        {
        case LOGIN:
            codigoDeRetorno = admLogin();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case MENU:
            codigoDeRetorno = admMenu();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case CADASTRAR_INVESTIDOR:
            codigoDeRetorno = admCadastrarUsuario();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case EXCLUIR_INVESTIDOR:
            codigoDeRetorno = admExcluirUsuario();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case CADASTRAR_CRIPTOMOEDA:
            codigoDeRetorno = admCadastrarCriptomoeda();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case EXCLUIR_CRIPTOMOEDA:
            codigoDeRetorno = admExcluirCriptomoeda();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case CONSULTAR_SALDO:
            codigoDeRetorno = admConsultarSaldo();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case CONSULTAR_EXTRATO:
            codigoDeRetorno = admConsultarExtrato();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        case ATUALIZAR_COTACAO:
            // codigoDeRetorno = atualizarCotacao();
            switch (codigoDeRetorno)
            {
            /*
            case :
                
                break;
            */
            }
            break;
        }
    }

    fclose(arquivoDeCriptomoedas);
    fclose(arquivoDeExtratos);
    fclose(arquivoDeUsuarios);

    return 0;
}
*/