#include "entrada.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "banco_de_dados.h"

int checarPorStringDeDigitos(char* string, int comprimento)
{
        for (int i = 0; i < comprimento; ++i)
                if (isdigit(string[i]))
                        continue;
                else
                        return 1;
        return 0;
}

void pressioneEnterParaContinuar(void)
{
        printf("Pressione ENTER para continuar.\n");
        while (getchar() != '\n');
        getchar();
}

int requisitarEVerificarSenha(Usuario* usuarioAtual)
{
        printf("Digite sua senha: ");
        char senha[9];
        scanf(" %8s", senha);

        printf("\n");

        if (strcmp(senha, usuarioAtual->senha) != 0)
                return 1;
        
        return 0;
}