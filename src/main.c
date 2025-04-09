#include <stdio.h>

#include "funcoes_principais.h"
#include "banco_de_dados.h"

int main(void)
{
        Menus menuAtual = LOGIN;
        Usuario usuarioAtual;
        int codigoDeRetorno;

        FILE* bancoDeDados = fopen("database.bin", "rb+");
        if (bancoDeDados == NULL)
        {
                bancoDeDados = fopen("database.bin", "wb+");
                if (bancoDeDados == NULL)
                {
                        printf("[ERRO]: Nao foi possivel criar um banco de dados. Terminando o programa.");
                        return 1;
                }

                rewind(bancoDeDados);
        }

        FILE* arquivoDeExtratos = fopen("extratos.bin", "rb+");
        if (arquivoDeExtratos == NULL)
        {
                arquivoDeExtratos = fopen("extratos.bin", "wb+");
                if (arquivoDeExtratos == NULL)
                {
                        printf("[ERRO]: Nao foi possivel criar um arquivo de extratos. Terminando o programa.\n\n");
                        return 1;
                }

                rewind(arquivoDeExtratos);
        }

        ListaDeUsuarios* listaDeUsuarios;
        Extrato* extrato;
        int usuarioPossuiExtrato = 1;
        
        codigoDeRetorno = carregarListaDeUsuarios(bancoDeDados, listaDeUsuarios);
        switch (codigoDeRetorno)
        {
        case 1:
                printf("[ERRO]: Nao foi possivel alocar espaco na memoria.\n\n");
                return 2;
        case 2:
                printf("[ERRO]: Nao foi possivel ler o banco de dados.\n\n");
                return 3;
        case 3:
                printf("[ERRO]: O banco de dados possui mais que 10 usuarios.\n\n");
                return 4;
        }

        do
        {
                switch (menuAtual)
                {
                case LOGIN:
                        codigoDeRetorno = login(listaDeUsuarios, &usuarioAtual);
                        switch (codigoDeRetorno)
                        {
                        case 0:
                                printf("Bem-vindo, %s.\n\n", usuarioAtual.nome);

                                codigoDeRetorno = carregarExtrato(arquivoDeExtratos, usuarioAtual.cpf, &extrato);

                                switch (codigoDeRetorno)
                                {
                                case 1:
                                        printf("[ERRO]: Nao foi possivel alocar espaco na memoria.\n\n");
                                        break;
                                case 2:
                                        printf("[ERRO]: Nao foi possivel abrir ou criar o arquivo de extratos.\n\n");
                                        break;
                                case 3:
                                        usuarioPossuiExtrato = 0;
                                        break;
                                }

                                menuAtual = MENU;
                                break;
                        case 1:
                                printf("[ERRO]: A entrada digitada nao e um CPF valido.\n\n");
                                break;
                        case 2:
                                printf("[ERRO]: A entrada digitada nao e uma senha valida.\n\n");
                                break;
                        case 3:
                                printf("[ERRO]: O CPF e senha digitados nao correspondem a um usuario existente.\n\n");
                                break;
                        }

                        break;
                case MENU:
                        codigoDeRetorno = exibirMenu();
                        break;
                case SALDO:
                        
                        break;
                case EXTRATO:

                        break;
                case DEPOSITO:

                        break;
                case SAQUE:

                        break;
                case COMPRA:

                        break;
                case VENDA:

                        break;

                case COTACAO:

                        break;
                }
                
        } while (menuAtual != SAIR);

        codigoDeRetorno = salvarExtrato(arquivoDeExtratos, extrato, usuarioPossuiExtrato);

        switch (codigoDeRetorno)
        {
        case 1:
                printf("[ERRO]: Nao foi possivel alocar espaco na memoria.\n\n");
                break;
        case 2:
                printf("[ERRO]: Nao foi possivel ler ou escrever para o arquivo de extratos.\n\n");
                break;
        case 3:
                printf("[ERRO]: Nao foi possivel encontrar o extrato do usuario no banco de dados.\n\n");
                break;
        case 4:
                printf("[ERRO]: Um erro de logica ocorreu ao salvar o extrato.\n\n");
                break;
        }

        free(extrato);
        free(listaDeUsuarios);

        fclose(arquivoDeExtratos);
        fclose(bancoDeDados);

        return 0;
}