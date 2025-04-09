#include "entrada.h"
#include <ctype.h>
#include <stdio.h>

int checarPorStringDeDigitos(char* string, int comprimento)
{
        for (int i = 0; i < comprimento; ++i)
                if (isdigit(string[i]))
                        continue;
                else
                        return 1;
        return 0;
}

void pressioneEnterParaContinuar()
{
        printf("Pressione ENTER para continuar.\n");
        while (getchar() != '\n');
        getchar();
}