#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char estado;
    char codigo[10];
    char cidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
} Carta;

void calcularDensidadePopulacional(Carta* c) {
    c->densidadePopulacional = c->populacao / c->area;
}

void calcularPibPerCapita(Carta* c) {
    c->pibPerCapita = (c->pib * 1e9) / c->populacao;
}

void cadastrarCarta(Carta* c, int numero) {
    char temp[20], estado_str[10];

    printf("=== Cadastro da Carta %d ===\n", numero);
    printf("Estado (A-H): ");
    fgets(estado_str, sizeof(estado_str), stdin);
    c->estado = estado_str[0];

    printf("Codigo (ex: A01): ");
    fgets(c->codigo, sizeof(c->codigo), stdin);
    c->codigo[strcspn(c->codigo, "\n")] = '\0';

    printf("Cidade: ");
    fgets(c->cidade, sizeof(c->cidade), stdin);
    c->cidade[strcspn(c->cidade, "\n")] = '\0';

    printf("População: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &c->populacao);

    printf("Área (km²): ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%f", &c->area);

    printf("PIB (em bilhões): ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%f", &c->pib);

    printf("Pontos Turísticos: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &c->pontosTuristicos);

    calcularDensidadePopulacional(c);
    calcularPibPerCapita(c);
}

int escolherAtributo(const char* texto, int atributoUsado) {
    int opcao;
    printf("\n%s\n", texto);

    for (int i = 1; i <= 6; i++) {
        if (i == atributoUsado) continue;
        switch (i) {
            case 1: printf("1. População\n"); break;
            case 2: printf("2. Área\n"); break;
            case 3: printf("3. PIB\n"); break;
            case 4: printf("4. Pontos Turísticos\n"); break;
            case 5: printf("5. Densidade Demográfica\n"); break;
            case 6: printf("6. PIB per capita\n"); break;
        }
    }

    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == atributoUsado || opcao < 1 || opcao > 6) {
        printf("Opção inválida. Tente novamente.\n");
        return escolherAtributo(texto, atributoUsado);
    }
    return opcao;
}

float obterValorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.densidadePopulacional;
        case 6: return c.pibPerCapita;
        default: return 0;
    }
}

void nomeAtributo(int atributo, char* nome) {
    switch (atributo) {
        case 1: strcpy(nome, "População"); break;
        case 2: strcpy(nome, "Área"); break;
        case 3: strcpy(nome, "PIB"); break;
        case 4: strcpy(nome, "Pontos Turísticos"); break;
        case 5: strcpy(nome, "Densidade Demográfica"); break;
        case 6: strcpy(nome, "PIB per capita"); break;
    }
}

float pontuar(Carta c1, Carta c2, int atributo) {
    float v1 = obterValorAtributo(c1, atributo);
    float v2 = obterValorAtributo(c2, atributo);

    if (atributo == 5) 
        return (v1 < v2) ? 1 : (v2 < v1) ? -1 : 0;
    else 
        return (v1 > v2) ? 1 : (v2 > v1) ? -1 : 0;
}

void compararAtributos(Carta c1, Carta c2, int a1, int a2) {
    char nome1[30], nome2[30];
    nomeAtributo(a1, nome1);
    nomeAtributo(a2, nome2);

    float v1_c1 = obterValorAtributo(c1, a1);
    float v1_c2 = obterValorAtributo(c2, a1);

    float v2_c1 = obterValorAtributo(c1, a2);
    float v2_c2 = obterValorAtributo(c2, a2);

    float soma1 = (a1 == 5 ? -v1_c1 : v1_c1) + (a2 == 5 ? -v2_c1 : v2_c1);
    float soma2 = (a1 == 5 ? -v1_c2 : v1_c2) + (a2 == 5 ? -v2_c2 : v2_c2);

    printf("\nComparando cartas:\n");
    printf("Carta 1: %s (%c)\n", c1.cidade, c1.estado);
    printf("Carta 2: %s (%c)\n\n", c2.cidade, c2.estado);

    printf("%s:\n -> %s: %.2f\n -> %s: %.2f\n", nome1, c1.cidade, v1_c1, c2.cidade, v1_c2);
    printf("%s:\n -> %s: %.2f\n -> %s: %.2f\n", nome2, c1.cidade, v2_c1, c2.cidade, v2_c2);

    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f\n", c1.cidade, soma1);
    printf("%s: %.2f\n", c2.cidade, soma2);

    if (soma1 > soma2)
        printf("\nResultado: Carta 1 (%s) venceu!\n", c1.cidade);
    else if (soma2 > soma1)
        printf("\nResultado: Carta 2 (%s) venceu!\n", c2.cidade);
    else
        printf("\nResultado: Empate!\n");
}

int main() {
    Carta carta1, carta2;

    cadastrarCarta(&carta1, 1);
    printf("\n");
    cadastrarCarta(&carta2, 2);

    printf("\n=== Comparação de Cartas com Dois Atributos ===\n");
    int atributo1 = escolherAtributo("Escolha o primeiro atributo para comparação:", 0);
    int atributo2 = escolherAtributo("Escolha o segundo atributo (diferente do primeiro):", atributo1);

    compararAtributos(carta1, carta2, atributo1, atributo2);

    return 0;
}
