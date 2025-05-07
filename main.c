#include <stdio.h>
#include "projeto.h"

int main() {
    int opcao;
    do {
        printf("\nEstoque de supermercado\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Registrar Entrada / Compra\n");
        printf("3 - Registrar Saida / Venda\n");
        printf("4 - Consultar por Codigo\n");
        printf("5 - Consultar por Nome\n");
        printf("6 - Gerar Relatorio de Estoque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                registrarEntrada();
                break;
            case 3:
                registrarSaida();
                break;
            case 4:
                consultarProdutoCodigo();
                break;
            case 5:
                consultarProdutoNome();
                break;
            case 6:
                gerarRelatorio();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
