#include "funcoes_principais.h"
#include <stdio.h>
#include <string.h>

#include "entrada.h"
#include "banco_de_dados.h"

int login(FILE* bancoDeDados, char* cpfDoUsuarioAtual)
{
        printf("Digite seu CPF (sem pontos ou traços) e sua senha.\nCPF: ");
        char cpfDigitado[12];
        scanf(" %11s", cpfDigitado);

        if (checarPorStringDeDigitos(cpfDigitado, 11) == 1)
                return 1;

        printf("Digite sua senha.\nSenha: ");
        char senhaDigitada[9];
        scanf(" %8s", senhaDigitada);

        if (checarPorStringDeDigitos(senhaDigitada, 8) == 1)
                return 2;

        if (checarExistenciaDoUsuario(bancoDeDados, cpfDigitado, senhaDigitada) == 1)
                return 3;
        
        strcpy(cpfDoUsuarioAtual, cpfDigitado);

        return 0;
}

int exibirMenu(void)
{
        printf("Menu");
}