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
void compararPorPopulacao(Carta c1, Carta c2);

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

void compararPorPopulacao(Carta c1, Carta c2) {
    printf("\nComparação de cartas (Atributo: População):\n\n");

    printf("Carta 1 - %s (%c): %d\n", c1.cidade, c1.estado, c1.populacao);
    printf("Carta 2 - %s (%c): %d\n", c2.cidade, c2.estado, c2.populacao);

    if (c1.populacao > c2.populacao) {
        printf("\nResultado: Carta 1 (%s) venceu!\n", c1.cidade);
    } else if (c2.populacao > c1.populacao) {
        printf("\nResultado: Carta 2 (%s) venceu!\n", c2.cidade);
    } else {
        printf("\nResultado: Empate!\n");
    }
}

int main() {
    Carta carta1, carta2;

    cadastrarCarta(&carta1, 1);
    printf("\n");
    cadastrarCarta(&carta2, 2);

    compararPorPopulacao(carta1, carta2);

    return 0;
}
