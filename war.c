#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 6
#define TOTAL_MISSOES 5
#define TAM_MISS_STR 100
#define COR_JOGADOR "Azul"

const char* VETOR_MISSOES[TOTAL_MISSOES] = {
    "Conquistar 4 territorios",
    "Eliminar todas as tropas da cor Vermelha",
    "Conquistar o territorio 'Siberia'",
    "Eliminar todas as tropas da cor Verde",
    "Conquistar 2 territorios na America"
};

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
    char continente[20];
} Territorio;


Territorio* alocarMapa(int tamanho);
char* alocarMissao(int tamanhoString);
void inicializarTerritorios(Territorio* mapa);
void liberarMemoria(Territorio* mapa, char* missaoJogador);

void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho);
void faseDeAtaque(Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);

void exibirMenuPrincipal();
void exibirMapa(const Territorio* mapa, int tamanho);
void exibirMissao(const char* missao);

void limparBufferEntrada();


int main() {
    srand(time(NULL));

    Territorio* mapa = alocarMapa(TOTAL_TERRITORIOS);
    char* missaoJogador = alocarMissao(TAM_MISS_STR);

    if (mapa == NULL || missaoJogador == NULL) {
        printf("Erro critico: Falha na alocacao de memoria.\n");
        if (mapa) free(mapa);
        if (missaoJogador) free(missaoJogador);
        return 1;
    }

    inicializarTerritorios(mapa);
    
    atribuirMissao(missaoJogador, VETOR_MISSOES, TOTAL_MISSOES);
    
    exibirMissao(missaoJogador);

    int opcao = -1;
    int vitoria = 0;

    do {
        exibirMapa(mapa, TOTAL_TERRITORIOS);
        exibirMenuPrincipal();
        
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, TOTAL_TERRITORIOS);
                
                vitoria = verificarMissao(missaoJogador, mapa, TOTAL_TERRITORIOS);
                if (vitoria) {
                    printf("\n=========================================\n");
                    printf("  VITORIA! Voce cumpriu sua missao!\n");
                    printf("=========================================\n");
                    opcao = 0;
                }
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
            system("clear || cls");
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);

    return 0;
}


Territorio* alocarMapa(int tamanho) {
    Territorio* mapa = (Territorio*)calloc(tamanho, sizeof(Territorio));
    return mapa;
}

char* alocarMissao(int tamanhoString) {
    char* missao = (char*)malloc(tamanhoString * sizeof(char));
    return missao;
}

void inicializarTerritorios(Territorio* mapa) {
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Azul");
    strcpy(mapa[0].continente, "America");
    mapa[0].tropas = 10;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Azul");
    strcpy(mapa[1].continente, "America");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Mexico");
    strcpy(mapa[2].cor, "Vermelho");
    strcpy(mapa[2].continente, "America");
    mapa[2].tropas = 5;

    strcpy(mapa[3].nome, "Siberia");
    strcpy(mapa[3].cor, "Vermelho");
    strcpy(mapa[3].continente, "Asia");
    mapa[3].tropas = 8;

    strcpy(mapa[4].nome, "Egito");
    strcpy(mapa[4].cor, "Verde");
    strcpy(mapa[4].continente, "Africa");
    mapa[4].tropas = 5;
    
    strcpy(mapa[5].nome, "Congo");
    strcpy(mapa[5].cor, "Verde");
    strcpy(mapa[5].continente, "Africa");
    mapa[5].tropas = 4;
}

void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    printf("\nLiberando memoria alocada...\n");
    if (mapa != NULL) {
        free(mapa);
    }
    if (missaoJogador != NULL) {
        free(missaoJogador);
    }
}

void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

int verificarMissao(const char* missao, const Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 4 territorios") == 0) {
        int contagem = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
                contagem++;
            }
        }
        return (contagem >= 4);
    }
    
    if (strcmp(missao, "Eliminar todas as tropas da cor Vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strcmp(missao, "Conquistar o territorio 'Siberia'") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Siberia") == 0 && strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
                return 1;
            }
        }
        return 0;
    }

    if (strcmp(missao, "Eliminar todas as tropas da cor Verde") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) {
                return 0; 
            }
        }
        return 1;
    }

    if (strcmp(missao, "Conquistar 2 territorios na America") == 0) {
        int contagem = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, COR_JOGADOR) == 0 && strcmp(mapa[i].continente, "America") == 0) {
                contagem++;
            }
        }
        return (contagem >= 2);
    }

    return 0;
}


void faseDeAtaque(Territorio* mapa, int tamanho) {
    int idAtacante, idDefensor;
    
    printf("\n--- Fase de Ataque ---\n");
    printf("Digite o numero do territorio ATACANTE (de 1 a %d): ", tamanho);
    scanf("%d", &idAtacante);
    
    printf("Digite o numero do territorio DEFENSOR (de 1 a %d): ", tamanho);
    scanf("%d", &idDefensor);
    limparBufferEntrada();

    idAtacante--; 
    idDefensor--;

    if (idAtacante < 0 || idAtacante >= tamanho || idDefensor < 0 || idDefensor >= tamanho) {
        printf("Indices invalidos. Territorios de 1 a %d.\n", tamanho);
        return;
    }
    
    if (strcmp(mapa[idAtacante].cor, COR_JOGADOR) != 0) {
        printf("Ataque invalido: Voce nao domina o territorio '%s'.\n", mapa[idAtacante].nome);
        return;
    }
    
    if (strcmp(mapa[idDefensor].cor, COR_JOGADOR) == 0) {
        printf("Ataque invalido: Voce nao pode atacar seu proprio territorio ('%s').\n", mapa[idDefensor].nome);
        return;
    }
    
    if (mapa[idAtacante].tropas < 2) {
        printf("Ataque invalido: '%s' precisa ter pelo menos 2 tropas para atacar.\n", mapa[idAtacante].nome);
        return;
    }

    atacar(&mapa[idAtacante], &mapa[idDefensor]);
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nBatalha: %s (%d) vs %s (%d)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("Dado de Ataque: %d\n", dadoAtacante);
    printf("Dado de Defesa: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! %s perdeu 1 tropa.\n", defensor->nome);
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            printf("TERRITORIO CONQUISTADO! '%s' agora e %s.\n", defensor->nome, atacante->cor);
            
            strcpy(defensor->cor, atacante->cor);
            strcpy(defensor->continente, atacante->continente);
            
            int tropasMovidas = (atacante->tropas - 1) / 2;
            if (tropasMovidas < 1 && atacante->tropas > 1) {
                tropasMovidas = 1;
            }

            defensor->tropas = tropasMovidas;
            atacante->tropas -= tropasMovidas;

            printf("%d tropas foram movidas para '%s'.\n", tropasMovidas, defensor->nome);
        }

    } else {
        printf("VITORIA DA DEFESA! %s perdeu 1 tropa.\n", atacante->nome);
        atacante->tropas--;
    }
}


void exibirMenuPrincipal() {
    printf("\n--- Turno do Jogador (%s) ---\n", COR_JOGADOR);
    printf("1. Atacar territorio\n");
    printf("0. Sair do Jogo\n");
    printf("Escolha sua acao: ");
}

void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("\n--- MAPA DO MUNDO ---\n");
    printf("------------------------------------------------------------------\n");
    printf("ID | Territorio     | Continente | Dono (Cor) | Tropas\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%-2d | %-14s | %-10s | %-10s | %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].continente,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("------------------------------------------------------------------\n");
}

void exibirMissao(const char* missao) {
    printf("\n=========================================\n");
    printf("  Sua Missao Secreta:\n");
    printf("  \"%s\"\n", missao);
    printf("=========================================\n");
    printf("\nPressione ENTER para iniciar o jogo...");
    getchar();
    system("clear || cls");
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
