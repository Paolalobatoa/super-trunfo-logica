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

void calcularDensidadePopulacional(Carta* c);
void calcularPibPerCapita(Carta* c);
void mostrarMenu(Carta c1, Carta c2);
void comparar(Carta c1, Carta c2, int opcao);

void cadastrarCarta(Carta* c, int numero) {
    char temp[20];
    char estado_str[10];

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

void calcularDensidadePopulacional(Carta* c) {
    c->densidadePopulacional = c->populacao / c->area;
}

void calcularPibPerCapita(Carta* c) {
    c->pibPerCapita = (c->pib * 1e9) / c->populacao;
}

void mostrarMenu(Carta c1, Carta c2) {
    int opcao;

    printf("\n=== MENU DE COMPARAÇÃO ===\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Demográfica\n");
    printf("6. PIB per capita\n");
    printf("Escolha o atributo para comparar (1-6): ");
    scanf("%d", &opcao);
    getchar(); 
    comparar(c1, c2, opcao);
}

void comparar(Carta c1, Carta c2, int opcao) {
    printf("\nComparação de cartas:\n");
    printf("Carta 1 - %s (%c)\n", c1.cidade, c1.estado);
    printf("Carta 2 - %s (%c)\n\n", c2.cidade, c2.estado);

    switch (opcao) {
        case 1:
            printf("População: %d vs %d\n", c1.populacao, c2.populacao);
            if (c1.populacao > c2.populacao)
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
            else if (c2.populacao > c1.populacao)
                printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
            else
                printf("Resultado: Empate!\n");
            break;
        case 2:
            printf("Área: %.2f vs %.2f\n", c1.area, c2.area);
            if (c1.area > c2.area)
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
            else if (c2.area > c1.area)
                printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
            else
                printf("Resultado: Empate!\n");
            break;
        case 3:
            printf("PIB: %.2f bilhões vs %.2f bilhões\n", c1.pib, c2.pib);
            if (c1.pib > c2.pib)
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
            else if (c2.pib > c1.pib)
                printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
            else
                printf("Resultado: Empate!\n");
            break;
        case 4:
            printf("Pontos Turísticos: %d vs %d\n", c1.pontosTuristicos, c2.pontosTuristicos);
            if (c1.pontosTuristicos > c2.pontosTuristicos)
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
            else if (c2.pontosTuristicos > c1.pontosTuristicos)
                printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
            else
                printf("Resultado: Empate!\n");
            break;
        case 5:
            printf("Densidade Demográfica: %.2f vs %.2f\n", c1.densidadePopulacional, c2.densidadePopulacional);
            if (c1.densidadePopulacional < c2.densidadePopulacional)
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
            else if (c2.densidadePopulacional < c1.densidadePopulacional)
                printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
            else
                printf("Resultado: Empate!\n");
            break;
        case 6:
            printf("PIB per capita: %.2f vs %.2f\n", c1.pibPerCapita, c2.pibPerCapita);
            if (c1.pibPerCapita > c2.pibPerCapita)
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
            else if (c2.pibPerCapita > c1.pibPerCapita)
                printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
            else
                printf("Resultado: Empate!\n");
            break;
        default:
            printf("Opção inválida.\n");
    }
}

int main() {
    Carta carta1, carta2;

    cadastrarCarta(&carta1, 1);
    printf("\n");
    cadastrarCarta(&carta2, 2);

    mostrarMenu(carta1, carta2);

    return 0;
}
