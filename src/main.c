#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "funcoes_principais.h"
#include "banco_de_dados.h"
#include "entrada.h"

int main(void)
{
        setlocale(LC_TIME, "pt_BR.UTF-8");

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

        Usuario usuarioPadrao = { "00000000000\0", "00000000\0", "Usuario Temporario\0", 0.0f, 0.0f, 0.0f, 0.0f };
        listaDeUsuarios->usuarios[0] = usuarioPadrao;
        ++(listaDeUsuarios->quantidadeDeUsuarios);

        switch (codigoDeRetorno)
        {
        case 1:
                printf("[ERRO]: Nao foi possivel alocar espaco na memoria.\n\n");
                return 2;
        case 2:
                printf("[ERRO]: Nao foi possivel ler o banco de dados.\n\n");
                return 3;
        case 3:
                printf("--- [AVISO] ---\nO banco de dados esta vazio. No entanto, o programa ira criar um usuario padrao para fins de teste.\nRemova esta funcionalidade quando for possivel registrar novos usuarios.\n\n");
                break;
        case 4:
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

                                codigoDeRetorno = carregarExtrato(arquivoDeExtratos, usuarioAtual.cpf, extrato);

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

                        if (codigoDeRetorno == 9)
                        {
                                printf("[ERRO]: O numero digitado nao e um numero de 1 a 8. Pressione ENTER para continuar.\n\n");
                                char c;
                                scanf("%*c%c", &c);
                        }
                        printf("\n");

                        menuAtual = codigoDeRetorno + 1;
                        break;
                case SALDO:
                        exibirSaldo(&usuarioAtual);
                        pressioneEnterParaContinuar();
                        menuAtual = MENU;
                        break;
                case EXTRATO:
                        imprimirExtrato(extrato);
                        pressioneEnterParaContinuar();
                        menuAtual = MENU;
                        break;
                case DEPOSITO:

                        menuAtual = MENU;
                        break;
                case SAQUE:
                        menuAtual = MENU;
                        break;
                case COMPRA:
                        menuAtual = MENU;
                        break;
                case VENDA:
                        menuAtual = MENU;
                        break;

                case COTACAO:
                
                        menuAtual = MENU;
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

        codigoDeRetorno = salvarListaDeUsuarios(bancoDeDados, listaDeUsuarios);

        if (codigoDeRetorno == 1)
                printf("[ERRO]: Nao foi possivel salvar o banco de dados.\n\n");

        free(extrato);
        free(listaDeUsuarios);

        fclose(arquivoDeExtratos);
        fclose(bancoDeDados);

        return 0;
}