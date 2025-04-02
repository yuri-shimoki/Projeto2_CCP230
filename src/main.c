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
                        printf("[ERRO]: Nao foi possivel criar um arquivo de extratos. Terminando o programa.");
                        return 1;
                }

                rewind(arquivoDeExtratos);
        }

        ListaDeUsuarios* listaDeUsuarios;
        carregarListaDeUsuarios(bancoDeDados, listaDeUsuarios);

        do
        {
                switch (menuAtual)
                {
                case LOGIN:
                        codigoDeRetorno = login(bancoDeDados, listaDeUsuarios, &usuarioAtual);
                        switch (codigoDeRetorno)
                        {
                        case 0:
                                printf("Bem-vindo, %s.", usuarioAtual.nome);
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

        fclose(bancoDeDados);

        return 0;
}