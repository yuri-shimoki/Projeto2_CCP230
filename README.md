# Projeto 2 de CCP230

## Objetivo

O objetivo deste projeto é criar uma exchange de criptomoedas, isto é, uma plataforma onde é possível realizar a compra e venda de criptomoedas.

Criptomoedas são moedas digitais descentralizadas, que não pertencem a governo algum.

## Compilação e Execução

Para compilar o projeto, primeiramente utilize o comando:

```cd <caminho da pasta raiz>```

Para ir até a pasta raiz do projeto, e, em seguida, utilize o comando:

```gcc -Ofast -I headers src/investidor/*.c -o aplicativo```

Para compilar o programa de usuário investidor, e utilize o comando:

```gcc -Ofast -I headers src/administrador/*.c -o aplicativo```

Para compilar o programa de usuário administrador. Em ambos os casos, um executável `aplicativo.exe` será produzido no Windows.

para executar o programa, basta escrever a seguinte linha no terminal:

```.\aplicativo.exe```

## Como Usar o Programa de Usuário Investidor

O programa é dividido em menus. Cada menu irá lhe permitir visualizar uma certa informação ou realizar uma certa ação.

Na tela de login, que aparece no início da execução do programa, você deve digitar o CPF e senha de um usuário existente no banco de dados.

Note que nas especificações deste projeto não foi requisitada uma funcionalidade de registro de usuários. Portanto, para fins de teste, o programa cria um usuário padrão com CPF 00000000000 e senha 00000000. O programa emite um aviso de que esse usuário deve existir apenas para fins de teste, e que deve ser removido caso a funcionalidade de registro de usuários seja implementada.

Note também que nas especificações deste projeto foi requisitado arquivos binários para o armazenamento de dados do programa, o que dificulta o teste do projeto.

Ao inserir o CPF e senha corretamente, você terá acesso ao menu principal do programa, a partir do qual você pode digitar um dos números listados nele para acessar cada uma das funções do programa.

## Participantes do Projeto

Yuri da Silva Shimoki, RA: 24.224.002-6.
