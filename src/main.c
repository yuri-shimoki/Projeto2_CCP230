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
        int indiceDoUsuarioAtual;
        int codigoDeRetorno;
        Cotacao cotacao;

        FILE* bancoDeDados;
        codigoDeRetorno = abrirArquivo(&bancoDeDados, "database.bin");

        FILE* arquivoDeExtratos;
        codigoDeRetorno = abrirArquivo(&arquivoDeExtratos, "extratos.bin");

        FILE* arquivoDeCotacao;
        codigoDeRetorno = abrirArquivo(&arquivoDeCotacao, "cotacao.bin");

        if (codigoDeRetorno == 1)
        {
                printf("[ERRO]: Nao foi possivel abrir um ou mais arquivos de dados. Terminando o programa.\n\n");
                return 1;
        }

        ListaDeUsuarios* listaDeUsuarios = (ListaDeUsuarios*) malloc(sizeof(ListaDeUsuarios));

        listaDeUsuarios->quantidadeDeUsuarios = 0;

        Extrato* extrato = (Extrato*) malloc(sizeof(Extrato));
        int usuarioPossuiExtrato = 1;
        
        codigoDeRetorno = carregarListaDeUsuarios(bancoDeDados, listaDeUsuarios);

        switch (codigoDeRetorno)
        {
        case 1:
                printf("[ERRO]: Nao foi possivel alocar espaco na memoria.\n\n");
                pressioneEnterParaContinuar();
                return 2;
                break;
        case 2:
                printf("[ERRO]: Nao foi possivel ler o banco de dados.\nTerminando o programa.\n\n");
                pressioneEnterParaContinuar();
                return 3;
                break;
        case 3:
                printf("--- [AVISO] ---\nO banco de dados esta vazio. No entanto, o programa ira criar um usuario padrao para fins de teste.\nRemova esta funcionalidade quando for possivel registrar novos usuarios.\n\n");
                break;
        case 4:
                printf("[ERRO]: O banco de dados possui mais que 10 usuarios.\nTerminando o programa.\n\n");
                pressioneEnterParaContinuar();
                return 4;
                break;
        }

        codigoDeRetorno = carregarCotacao(arquivoDeCotacao, &cotacao);

        if (codigoDeRetorno == 1)
        {
                printf("[ERRO]: Nao foi possivel ler o arquivo de cotacao.\nTerminando o programa\n\n");
                pressioneEnterParaContinuar();
                return 5;
        }

        do
        {
                switch (menuAtual)
                {
                case LOGIN:
                        codigoDeRetorno = login(listaDeUsuarios, &usuarioAtual, &indiceDoUsuarioAtual);
                        switch (codigoDeRetorno)
                        {
                        case 0:
                                printf("Bem-vindo, %s.\n\n", usuarioAtual.nome);

                                codigoDeRetorno = carregarExtrato(arquivoDeExtratos, usuarioAtual.cpf, extrato); 
                                //extrato->quantidadeDeTransacoes = 0;
                                switch (codigoDeRetorno)
                                {
                                case 1:
                                        printf("[ERRO]: Nao foi possivel alocar espaco na memoria.\n\n");
                                        pressioneEnterParaContinuar();
                                        break;
                                case 2:
                                        printf("[ERRO]: Nao foi possivel abrir ou criar o arquivo de extratos.\n\n");
                                        pressioneEnterParaContinuar();
                                        break;
                                case 3:
                                        usuarioPossuiExtrato = 0;
                                        break;
                                }

                                menuAtual = MENU;
                                break;
                        case 1:
                                printf("[ERRO]: A entrada digitada nao e um CPF valido.\n\n");
                                pressioneEnterParaContinuar();
                                break;
                        case 2:
                                printf("[ERRO]: A entrada digitada nao e uma senha valida.\n\n");
                                pressioneEnterParaContinuar();
                                break;
                        case 3:
                                printf("[ERRO]: O CPF e senha digitados nao correspondem a um usuario existente.\n\n");
                                pressioneEnterParaContinuar();
                                break;
                        }

                        break;
                case MENU:
                        codigoDeRetorno = exibirMenu();

                        if (codigoDeRetorno == 9)
                        {
                                printf("[ERRO]: O numero digitado nao e um numero de 1 a 8.\n\n");
                                pressioneEnterParaContinuar();
                                printf("\n");
                                menuAtual = MENU;
                        }

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
                        codigoDeRetorno = depositarDinheiro(&usuarioAtual, extrato);

                        switch (codigoDeRetorno)
                        {
                        case 0:
                                menuAtual = SALDO;
                                break;
                        case 1:
                                printf("[ERRO]: O valor digitado e invalido.\n\n");
                                menuAtual = MENU;
                                break;
                        case 2:
                                printf("[ERRO]: O valor de deposito nao pode ser negativo.\n\n");
                                menuAtual = MENU;
                                break;
                        }
                        break;
                case SAQUE:
                        codigoDeRetorno = sacarDinheiro(&usuarioAtual, extrato);

                        switch (codigoDeRetorno)
                        {
                        case 0:
                                menuAtual = SALDO;
                                break;
                        case 1:
                                printf("[ERRO]: O valor digitado e invalido.\n\n");
                                pressioneEnterParaContinuar();
                                menuAtual = MENU;
                                break;
                        case 2:
                                printf("[ERRO]: O valor de saque nao pode ser negativo.\n\n");
                                pressioneEnterParaContinuar();
                                menuAtual = MENU;
                                break;
                        case 3:
                                printf("[ERRO]: O valor de saque nao pode exceder seu saldo.\n\n");
                                pressioneEnterParaContinuar();
                                menuAtual = MENU;
                                break;
                        }
                        break;
                case COMPRA:
                        codigoDeRetorno = comprarCriptomoeda(&usuarioAtual, extrato);

                        switch (codigoDeRetorno)
                        {
                        case 0:
                                menuAtual = SALDO;
                                break;
                        case 1:
                                printf("[ERRO]: O valor digitado e invalido.\n\n");
                                pressioneEnterParaContinuar();
                                menuAtual = MENU;
                                break;
                        case 2:
                                printf("[ERRO]: O valor de compra nao pode ser negativo.\n\n");
                                pressioneEnterParaContinuar();
                                menuAtual = MENU;
                                break;
                        case 3:
                                printf("[ERRO]: O valor de compra nao pode exceder seu saldo.\n\n");
                                pressioneEnterParaContinuar();
                                menuAtual = MENU;
                                break;
                        }
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

        codigoDeRetorno = salvarUsuario(bancoDeDados, &usuarioAtual, indiceDoUsuarioAtual, listaDeUsuarios->quantidadeDeUsuarios);

        if (codigoDeRetorno == 1)
                printf("[ERRO]: Nao foi possivel salvar o banco de dados.\n\n");

        codigoDeRetorno = salvarCotacao(arquivoDeCotacao, &cotacao);

        if (codigoDeRetorno == 1)
                printf("[ERRO]: Nao foi possivel salvar a cotacao.\n\n");

        free(extrato);
        free(listaDeUsuarios);

        fclose(arquivoDeCotacao);
        fclose(arquivoDeExtratos);
        fclose(bancoDeDados);

        return 0;
}