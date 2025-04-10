#include "funcoes_principais.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "entrada.h"
#include "banco_de_dados.h"

int login(ListaDeUsuarios* listaDeUsuarios, Usuario* usuarioAtual, int* indice)
{
        printf("Digite seu CPF (sem pontos ou tracos) e sua senha.\nCPF: ");
        char cpfDigitado[12];
        scanf(" %11s", cpfDigitado);

        if (checarPorStringDeDigitos(cpfDigitado, 11) == 1)
                return 1;

        printf("Digite sua senha.\nSenha: ");
        char senhaDigitada[9];
        scanf(" %8s", senhaDigitada);

        if (checarPorStringDeDigitos(senhaDigitada, 8) == 1)
                return 2;

        int indiceDoUsuarioAtual = checarExistenciaDoUsuario(listaDeUsuarios, cpfDigitado, senhaDigitada);

        if (indiceDoUsuarioAtual == -1)
                return 3;
        
        *indice = indiceDoUsuarioAtual;
        *usuarioAtual = listaDeUsuarios->usuarios[indiceDoUsuarioAtual];

        return 0;
}

int exibirMenu(void)
{
        printf("--- [MENU PRINCIPAL] ---\n1. Exibir saldo\n2. Exibir extrato\n3. Depositar\n4. Sacar\n5. Comprar criptomoeda\n6. Vender criptomoeda\n7. Randomizar cotacao\n8. Sair\nDigite um numero de 1 a 8: ");

        int entrada;
        scanf("%i", &entrada);

        printf("\n");

        if (entrada < 1 || entrada > 8)
                return 9;
        
        return entrada;
}

void exibirSaldo(Usuario* usuarioAtual)
{
        printf("Nome: %s\nCPF: %s\nSaldo:\n- R$%.2f\n- %.6f BTC\n- %.6f ETH\n- %.6f XRP\n\n",
                usuarioAtual->nome,
                usuarioAtual->cpf,
                usuarioAtual->saldoReais,
                usuarioAtual->saldoBitcoin,
                usuarioAtual->saldoEthereum,
                usuarioAtual->saldoRipple);
}

int depositarDinheiro(Usuario* usuarioAtual, Extrato* extrato)
{
        printf("Digite quantos reais deseja depositar: R$");
        float valor;
        int retorno = scanf("%f", &valor);

        printf("\n");

        if (retorno != 1)
                return 1;

        if (valor < 0)
                return 2;

        Transacao transacao;

        obterDataEHoraAtuais(transacao.data, transacao.hora);
        transacao.tipo = '+';
        transacao.valorDaTransacao = valor;
        strcpy(transacao.moeda, "REAL");
        transacao.saldoReais = usuarioAtual->saldoReais;
        transacao.saldoBitcoin = usuarioAtual->saldoBitcoin;
        transacao.saldoEthereum = usuarioAtual->saldoEthereum;
        transacao.saldoRipple = usuarioAtual->saldoRipple;

        usuarioAtual->saldoReais += valor;

        registrarTransacao(extrato, &transacao);

        return 0;
}

int sacarDinheiro(Usuario* usuarioAtual, Extrato* extrato)
{
        printf("Digite quantos reais deseja sacar: R$");
        float valor;
        int retorno = scanf("%f", &valor);

        printf("\n");

        if (retorno != 1)
                return 1;

        if (valor < 0)
                return 2;

        if (valor > usuarioAtual->saldoReais)
                return 3;

        Transacao transacao;

        obterDataEHoraAtuais(transacao.data, transacao.hora);
        transacao.tipo = '-';
        transacao.valorDaTransacao = valor;
        strcpy(transacao.moeda, "REAL");
        transacao.saldoReais = usuarioAtual->saldoReais;
        transacao.saldoBitcoin = usuarioAtual->saldoBitcoin;
        transacao.saldoEthereum = usuarioAtual->saldoEthereum;
        transacao.saldoRipple = usuarioAtual->saldoRipple;

        usuarioAtual->saldoReais -= valor;

        registrarTransacao(extrato, &transacao);

        return 0;
}

int comprarCriptomoeda(Usuario* usuarioAtual, Extrato* extrato, Cotacao* cotacao)
{
        printf("Digite qual criptomoeda deseja comprar (Bitcoin, Ethereum ou Ripple): ");
        char criptomoeda[9];
        int retorno = scanf("%8s", criptomoeda);

        printf("\n");

        for (int i = 0; criptomoeda[i] != '\0'; ++i)
                criptomoeda[i] = tolower(criptomoeda[i]); 

        int comparacaoBitcoin = strcmp(criptomoeda, "bitcoin");
        int comparacaoEthereum = strcmp(criptomoeda, "ethereum");
        int comparacaoRipple = strcmp(criptomoeda, "ripple");

        if (comparacaoBitcoin != 0 &&
            comparacaoEthereum != 0 &&
            comparacaoRipple != 0)
        {
                return 1;
        }

        printf("Digite quantos reais deseja gastar na compra da criptomoeda: ");
        float valorDaCompra;
        retorno = scanf("%f", &valorDaCompra);

        if (valorDaCompra < 0.0f)
                return 2;

        if (valorDaCompra > usuarioAtual->saldoReais)
                return 3;

        Transacao transacao;

        obterDataEHoraAtuais(transacao.data, transacao.hora);
        transacao.tipo = '+';
        transacao.valorDaTransacao = valorDaCompra;
        transacao.saldoReais = usuarioAtual->saldoReais;
        transacao.saldoBitcoin = usuarioAtual->saldoBitcoin;
        transacao.saldoEthereum = usuarioAtual->saldoEthereum;
        transacao.saldoRipple = usuarioAtual->saldoRipple;

        char moedaDaTransacao[4];

        if (comparacaoBitcoin == 0)
        {
                strcpy(moedaDaTransacao, "BTC");
                usuarioAtual->saldoBitcoin += (valorDaCompra/cotacao->cotacaoBitcoin) * 0.98f;
        }
        else if (comparacaoEthereum == 0)
        {
                strcpy(moedaDaTransacao, "ETH");
                usuarioAtual->saldoEthereum += (valorDaCompra/cotacao->cotacaoEthereum) * 0.99f;
        }
        else if (comparacaoRipple == 0)
        {
                strcpy(moedaDaTransacao, "XRP");
                usuarioAtual->saldoRipple += (valorDaCompra/cotacao->cotacaoRipple) * 0.99f;
        }

        strcpy(transacao.moeda, moedaDaTransacao);

        usuarioAtual->saldoReais -= valorDaCompra;

        registrarTransacao(extrato, &transacao);

        return 0;
}

int venderCriptomoeda(Usuario* usuarioAtual, Extrato* extrato, Cotacao* cotacao)
{
        printf("Digite qual criptomoeda deseja vender (Bitcoin, Ethereum ou Ripple): ");
        char criptomoeda[9];
        int retorno = scanf("%8s", criptomoeda);

        printf("\n");

        for (int i = 0; criptomoeda[i] != '\0'; ++i)
                criptomoeda[i] = tolower(criptomoeda[i]); 

        int comparacaoBitcoin = strcmp(criptomoeda, "bitcoin");
        int comparacaoEthereum = strcmp(criptomoeda, "ethereum");
        int comparacaoRipple = strcmp(criptomoeda, "ripple");

        if (comparacaoBitcoin != 0 &&
            comparacaoEthereum != 0 &&
            comparacaoRipple != 0)
        {
                return 1;
        }

        printf("Digite quantas unidades da criptomoeda voce deseja vender: ");
        float valorDaCompra;
        retorno = scanf("%f", &valorDaCompra);

        if (valorDaCompra < 0.0f)
                return 2;

        Transacao transacao;

        obterDataEHoraAtuais(transacao.data, transacao.hora);
        transacao.tipo = '-';
        transacao.valorDaTransacao = valorDaCompra;
        transacao.saldoReais = usuarioAtual->saldoReais;
        transacao.saldoBitcoin = usuarioAtual->saldoBitcoin;
        transacao.saldoEthereum = usuarioAtual->saldoEthereum;
        transacao.saldoRipple = usuarioAtual->saldoRipple;

        char moedaDaTransacao[4];

        if (comparacaoBitcoin == 0)
        {
                if (valorDaCompra > usuarioAtual->saldoBitcoin)
                        return 3;

                strcpy(moedaDaTransacao, "BTC");
                usuarioAtual->saldoBitcoin -= valorDaCompra;
                usuarioAtual->saldoReais += (valorDaCompra * cotacao->cotacaoBitcoin) * 0.97f;
        }
        else if (comparacaoEthereum == 0)
        {
                if (valorDaCompra > usuarioAtual->saldoEthereum)
                        return 3;

                strcpy(moedaDaTransacao, "ETH");
                usuarioAtual->saldoEthereum -= valorDaCompra;
                usuarioAtual->saldoReais += (valorDaCompra * cotacao->cotacaoEthereum) * 0.98f;
        }
        else if (comparacaoRipple == 0)
        {
                if (valorDaCompra > usuarioAtual->saldoRipple)
                        return 3;

                strcpy(moedaDaTransacao, "XRP");
                usuarioAtual->saldoRipple -= valorDaCompra;
                usuarioAtual->saldoReais += (valorDaCompra * cotacao->cotacaoRipple) * 0.99f;
        }

        strcpy(transacao.moeda, moedaDaTransacao);

        registrarTransacao(extrato, &transacao);

        return 0;
}

void atualizarCotacao(Cotacao* cotacao)
{
        float porcentagemDeMudanca;

        printf("Cotacoes anteriores:\nBTC: %f\nETH: %f\nXRP: %f\n",
                cotacao->cotacaoBitcoin,
                cotacao->cotacaoEthereum,
                cotacao->cotacaoRipple);

        porcentagemDeMudanca = ((float)((rand() % 11) - 5))/100.0f;
        cotacao->cotacaoBitcoin *= 1 + porcentagemDeMudanca;

        porcentagemDeMudanca = ((float)((rand() % 11) - 5))/100.0f;
        cotacao->cotacaoEthereum *= 1 + porcentagemDeMudanca;

        porcentagemDeMudanca = ((float)((rand() % 11) - 5))/100.0f;
        cotacao->cotacaoRipple *= 1 + porcentagemDeMudanca;

        printf("-------------\nCotacoes novas:\nBTC: %f\nETH: %f\nXRP: %f\n\n",
                cotacao->cotacaoBitcoin,
                cotacao->cotacaoEthereum,
                cotacao->cotacaoRipple);

        pressioneEnterParaContinuar();
}