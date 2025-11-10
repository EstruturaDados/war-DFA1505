#include <stdio.h>
#include <string.h>


struct Territorio {
    char nome[30];   
    char cor[10];     
    int tropas;       
};

int main() {
    struct Territorio territorios[5]; 
    int i;

    printf("=== Cadastro de Territórios ===\n");

    for (i = 0; i < 5; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %29[^\n]", territorios[i].nome); 

        printf("Digite a cor do exército: ");
        scanf(" %9[^\n]", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n=== Territórios Cadastrados ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
