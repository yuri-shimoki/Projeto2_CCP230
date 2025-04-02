#include <stdio.h>


int login(char* cpfDoUsuarioAtual)
{

}

int exibirMenu(void)
{

}

int exibirSaldo(void)
{

}

int exibirExtrato(void)
{

}

int depositarDinheiro(void)
{

}

int sacarDinheiro(void)
{

}

int comprarCriptomoeda(void)
{
        
}

int venderCriptomoeda(void)
{

}

int atualizarCotacao(void)
{

}

typedef enum
{
        LOGIN,
        MENU,
        SALDO,
        EXTRATO,
        DEPOSITO,
        SAQUE,
        COMPRA,
        VENDA,
        COTACAO,
        SAIR
} Menus;

int main(void)
{
        Menus menuAtual = LOGIN;
        char cpfDoUsuarioAtual[11];
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

                fseek(bancoDeDados, 0, SEEK_SET);
        }

        do
        {
                switch (menuAtual)
                {
                case LOGIN:

                        break;
                case MENU:

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