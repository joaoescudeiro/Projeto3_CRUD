#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

void cadastrarProduto() {
    Produto p;
    FILE *arquivo = fopen("estoque.dat", "ab");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &p.codigo);
    getchar();

    printf("Nome: ");
    fgets(p.nome, 50, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Descricao: ");
    fgets(p.descricao, 100, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Preço unitario: ");
    scanf("%f", &p.preco);

    fwrite(&p, sizeof(Produto), 1, arquivo);
    fclose(arquivo);

    printf("Produto cadastrado.\n");
}
