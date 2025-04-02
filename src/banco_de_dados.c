#include "banco_de_dados.h"

#include <stdio.h>
#include <stdlib.h>

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

int carregarExtrato(FILE* arquivoDeExtratos, Extrato* extrato)
{
        extrato = (Extrato*) malloc(sizeof(Extrato));

        if (extrato == NULL)
                return 1;

        fread(extrato, sizeof(Extrato), 1, arquivoDeExtratos);
        
        if (ferror(arquivoDeExtratos) != 0)
                return 2;

        if (feof(arquivoDeExtratos) != 0)
                return 3;

        return 0;
}