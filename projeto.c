#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

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

    printf("Preco unitario: ");
    scanf("%f", &p.preco);

    fwrite(&p, sizeof(Produto), 1, arquivo);
    fclose(arquivo);

    printf("Produto cadastrado.\n");
}

void registrarEntrada() {
    int codigo, quantidade;
    printf("Digite o codigo do produto para entrada: ");
    scanf("%d", &codigo);
    printf("Quantidade a adicionar: ");
    scanf("%d", &quantidade);

    FILE *arquivo = fopen("estoque.dat", "rb+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Produto p;
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (p.codigo == codigo) {
            p.quantidade += quantidade;
            fseek(arquivo, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, arquivo);
            encontrado = 1;
            printf("Entrada de produto registrada.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }

    fclose(arquivo);
}

void registrarSaida() {
    int codigo, quantidade;
    printf("Digite o codigo do produto para saida: ");
    scanf("%d", &codigo);
    printf("Quantidade a remover: ");
    scanf("%d", &quantidade);

    FILE *arquivo = fopen("estoque.dat", "rb+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Produto p;
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (p.codigo == codigo) {
            if (p.quantidade >= quantidade) {
                p.quantidade -= quantidade;
                fseek(arquivo, -sizeof(Produto), SEEK_CUR);
                fwrite(&p, sizeof(Produto), 1, arquivo);
                printf("Saida de produto registrada.\n");
            } else {
                printf("Quantidade insuficiente no estoque.\n");
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }

    fclose(arquivo);
}

void consultarProdutoCodigo() {
    int codigo;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    FILE *arquivo = fopen("estoque.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Produto p;
    int encontrado = 0;

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (p.codigo == codigo) {
            printf("\nProduto encontrado:\n");
            printf("Nome: %s\n", p.nome);
            printf("Descricao: %s\n", p.descricao);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Preco: R$ %.2f\n", p.preco);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto com codigo %d nao encontrado.\n", codigo);
    }

    fclose(arquivo);
}

void consultarProdutoNome() {
    char nomeBusca[50];
    printf("Digite o nome do produto: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    FILE *arquivo = fopen("estoque.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Produto p;
    int encontrado = 0;

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (strcasecmp(p.nome, nomeBusca) == 0) {
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", p.codigo);
            printf("Descricao: %s\n", p.descricao);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Preco: R$ %.2f\n", p.preco);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto com nome digitado nao encontrado.\n");
    }

    fclose(arquivo);
}

void gerarRelatorio() {
    FILE *arquivo = fopen("estoque.dat", "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de estoque");
        return;
    }

    FILE *relatorio = fopen("relatorio_estoque.txt", "w");
    if (!relatorio) {
        perror("Erro ao criar o arquivo de relatorio");
        fclose(arquivo);
        return;
    }

    Produto p;
    fprintf(relatorio, "Relatorio de Estoque do Supermercado\n\n");
    fprintf(relatorio, "%-10s %-30s %-10s %-15s\n", "Codigo", "Nome", "Quantidade", "Preço Total");
    fprintf(relatorio, "----------------------------------------------------------------\n");

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        float precoTotal = p.quantidade * p.preco;
        fprintf(relatorio, "%-10d %-30s %-10d R$ %-13.2f\n", p.codigo, p.nome, p.quantidade, precoTotal);
    }

    fclose(arquivo);
    fclose(relatorio);

    printf("Relatorio de estoque gerado.\n");
}