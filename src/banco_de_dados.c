#include "banco_de_dados.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checarExistenciaDoUsuario(ListaDeUsuarios* listaDeUsuarios, char* cpf, char* senha)
{
        // char buffer[255];
        return 0;
}

int carregarListaDeUsuarios(FILE* bancoDeDados, ListaDeUsuarios* listaDeUsuarios)
{
        listaDeUsuarios = (ListaDeUsuarios*) malloc(sizeof(ListaDeUsuarios));

        if (listaDeUsuarios == NULL)
                return 1;

        fread(listaDeUsuarios, sizeof(ListaDeUsuarios), 1, bancoDeDados);
        
        if (ferror(bancoDeDados) != 0)
                return 2;

        if (feof(bancoDeDados) != 0)
                return 3;

        return 0;
}

int carregarExtrato(FILE* arquivoDeExtratos, char* cpf, Extrato* extrato)
{
        extrato = (Extrato*) malloc(sizeof(Extrato));

        if (extrato == NULL)
                return 1;

        rewind(arquivoDeExtratos);

        for (int i = 0; i < 10; ++i)
        {
                fread(extrato, sizeof(Extrato), 1, arquivoDeExtratos);

                if (ferror(arquivoDeExtratos) != 0)
                        return 2;

                if (strcmp(extrato->cpf, cpf) == 0)
                        break;

                if (feof(arquivoDeExtratos) != 0)
                        return 3;
        }

        return 0;
}