#include <stdio.h>   // Biblioteca padrão de entrada e saída. 
                     // Permite usar funções como printf(), scanf(), getchar(), etc.

#include <stdlib.h>  // Biblioteca padrão de utilidades gerais. 
                     // Oferece funções como malloc(), free(), rand(), atoi(), system(), entre outras.

#include <ctype.h>   // Biblioteca para manipulação de caracteres. 
                     // Fornece funções como toupper(), tolower(), isdigit(), isalpha(), etc. 
                     // Útil para validar e converter letras e números.

#include <time.h>    // Biblioteca para manipulação de tempo e data. 
                     // Contém funções como time(), srand(), rand(), localtime(), que servem, por exemplo, 
                     // para gerar números aleatórios baseados no relógio do sistema.

#include <string.h>  // Biblioteca para manipulação de strings (cadeias de caracteres). 
                     // Funções como strlen(), strcpy(), strcat(), strcmp(), strtok(), etc.

#include <locale.h>  // Biblioteca usada para definir configurações regionais. 
                     // Por exemplo, setlocale(LC_ALL, "Portuguese"); permite que acentos e símbolos 
                     // sejam exibidos corretamente em programas que usam a língua portuguesa.



//Constantes Globais 
#define max_nome 50     // Define um tamanho máximo de 50 caracteres para nomes
#define max_cor 30      // Define um tamanho máximo de 30 caracteres para cores
#define max_equipes 5   // Define o número máximo de equipes permitidas no programa


//Definição da struct Territorio
typedef struct Territorio
{
    char nome[max_nome];   // Array de caracteres para armazenar o nome do território. 
                           // O tamanho máximo é definido pela constante global 'max_nome'.

    char cor[max_cor];     // Array de caracteres para armazenar a cor associada ao território.
                           // Útil, por exemplo, para diferenciar equipes ou regiões no jogo.
                           // O tamanho máximo é definido por 'max_cor'.

    int tropas;            // Número inteiro que representa a quantidade de tropas presentes no território.
} Territorio;              // 'typedef' permite que você use 'Territorio' como um tipo de dado, sem precisar escrever 'struct Territorio' toda vez.



//Funções utilitarias
void limpar_buffer() 
{
    int c;  // Variável para armazenar temporariamente o caractere lido do buffer

    // Enquanto o próximo caractere lido não for '\n' (enter) e não for EOF (fim de arquivo):
    while ((c = getchar()) != '\n' && c != EOF)
        ;   // o ponto-e-vírgula sozinho indica "não fazer nada" dentro do loop
            // Apenas consome e descarta os caracteres do buffer
}

void linha(char caracter, int quantidade)
{
    // Loop que se repete 'quantidade' vezes
    for (int i = 0; i < quantidade; i++)
    {
        printf("%c", caracter);  // Imprime o caractere passado como parâmetro
    }

    printf("\n");  // Após imprimir todos os caracteres, pula para a próxima linha
}

int sortear_num(int max, int min)
{ 
    // rand() gera um número aleatório inteiro entre 0 e RAND_MAX
    // (max - min + 1) define o tamanho do intervalo desejado
    // '+ min' desloca o número para começar no valor mínimo
    return rand() % (max - min + 1) + min;
}



//Funções de alocação e liberação de memória
void* alocar_memoria(int tamanho)
{
    // Aloca memória para 'tamanho' elementos do tipo Territorio, inicializando todos com 0
    Territorio* aux = (Territorio*) calloc(tamanho, sizeof(Territorio));

    // Verifica se a alocação falhou
    if (aux == NULL)
    {
        printf("Erro ao alocar memória!"); // Mensagem de erro
        exit(1);                            // Encerra o programa imediatamente
    }

    return aux;  // Retorna o ponteiro para a memória alocada
}


void liberar_memoria(Territorio *aux)
{
    // Verifica se o ponteiro não é NULL antes de liberar
    if(aux != NULL)
    {
        free(aux);  // Libera a memória previamente alocada com calloc/malloc
    }
}



//Função de inserção de valores
void inserir_valores(Territorio* aux, char nome[max_nome], char cor[max_cor], int tropas)
{
    // Copia o nome passado como parâmetro para o campo 'nome' do território
    strcpy(aux->nome, nome);

    // Copia a cor passada como parâmetro para o campo 'cor' do território
    strcpy(aux->cor, cor);

    // Atribui o número de tropas ao campo correspondente
    aux->tropas = tropas;
}



//Função para exibir o mapa
void imprimir_mapa(Territorio* equipes, Territorio* player) {
    linha('=', 55);  // Imprime uma linha de '=' com 55 caracteres
    printf("| %-10s | %-15s | %-7s |\n", "Nome", "Cor da Equipe", "Tropas"); // Cabeçalho da tabela
    linha('=', 55);  // Outra linha para separar o cabeçalho dos dados

    // Loop para imprimir todas as equipes
    for (int i = 0; i < max_equipes; i++)
    {
        // %-10s => string alinhada à esquerda com largura 10
        // %-15s => string alinhada à esquerda com largura 15
        // %-7d => inteiro alinhado à esquerda com largura 7
        printf("| %-10s | %-15s | %-7d |\n", equipes[i].nome, equipes[i].cor, equipes[i].tropas);
    }

    linha('=', 55); // Linha separadora após todas as equipes

    // Exibe os dados do jogador
    printf("Sua equipe: \n");
    printf("| %-10s | %-15s | %-7d |\n", player->nome, player->cor, player->tropas);

    linha('=', 55); // Linha final
}



//Função de ataque
void atacar(Territorio* atacante, Territorio* defensor)
{
    // Verifica se os ponteiros são válidos
    if (atacante == NULL || defensor == NULL) return; 

    // Verifica se o atacante tem tropas suficientes
    if(atacante->tropas < 1)
    {
        printf("%s não tem tropas suficientes para atacar (tropas = %d).\n", atacante->nome, atacante->tropas);
        return;  // Sai da função sem realizar ataque
    }

    int num_atacante, num_defensor;

    // Sorteia números aleatórios de 1 a 10 para simular combate
    num_atacante = sortear_num(10, 1);
    num_defensor  = sortear_num(10, 1);

    // Se o atacante ganha ou empata
    if (num_atacante > num_defensor || num_atacante == num_defensor)
    {
        atacante->tropas += 1;   // Recompensa por vitória: +1 tropa
        defensor->tropas -= 1;   // Defensor perde 1 tropa
        if (defensor->tropas < 0) defensor->tropas = 0; // Evita tropas negativas
        printf("%s vence! (+1 tropa). %s perde 1 tropa.\n", atacante->nome, defensor->nome);
    }
    // Se o defensor ganha
    else if(num_atacante < num_defensor)
    {
        atacante->tropas -= 1;   // Atacante perde 1 tropa
        defensor->tropas += 1;   // Defensor ganha 1 tropa
        if (atacante->tropas < 0) atacante->tropas = 0; // Evita tropas negativas
        printf("%s defende com sucesso! %s perde 1 tropa.\n", defensor->nome, atacante->nome);
    }
}



//Função para verificar missões
int verificar_missao(Territorio* aux, Territorio* player, int missao)
{
    int contador = 0;  // Conta quantos territórios pertencem ao player (para missão 1)

    // Missão 1: possuir pelo menos 3 territórios
    if(missao == 1)
    {
        for(int i = 0; i < max_equipes; i++)
        {
            if (strcmp(aux[i].nome, player->nome) == 0) 
                contador++;  // Incrementa contador se o território pertence ao player
        }
        
        if(contador >= 3)
        {
            linha('\n', 2);   // Duas linhas em branco
            linha('=', 55);   // Linha decorativa
            printf("\nParabéns!");  // Mensagem de vitória
            linha('=', 55);
            return 1;  // Missão concluída
        }
        else
        {
            linha('\n', 2);
            linha('=', 55);
            printf("Sua missão ainda não foi concluída\n");
            linha('=', 55);
        }
    }
    
    // Missão 2: possuir pelo menos 10 tropas
    if(missao == 2)
    {
        if(player->tropas >= 10)
        {
            linha('\n', 2);
            linha('=', 55);
            printf("\nParabéns!");
            linha('=', 55);
            return 1;  // Missão concluída
        }
        else
        {
            linha('\n', 2);
            linha('=', 55);
            printf("Sua missão ainda não foi concluída\n");
            linha('=', 55);
        }
    }

    return 0; // Missão não concluída
}
    

int main()
{
    srand(time(NULL));                 // Inicializa a semente para rand(), garantindo números pseudoaleatórios diferentes a cada execução
    setlocale(LC_ALL, "pt_br");        // Configura o idioma/locale para Português, permitindo exibir acentos corretamente

    Territorio* equipes = alocar_memoria(max_equipes);  // Aloca memória para 5 equipes

    // Inicializa os territórios com nomes, cores e tropas aleatórias
    inserir_valores(&equipes[0], "Norte", "Vermelho", sortear_num(10, 2));
    inserir_valores(&equipes[1], "Sul", "Azul", sortear_num(5, 2));
    inserir_valores(&equipes[2], "Leste", "Verde", sortear_num(10, 2));
    inserir_valores(&equipes[3], "Oeste", "Amarelo", sortear_num(10, 2));
    inserir_valores(&equipes[4], "Centro", "Roxo", sortear_num(10, 2));

    // Escolhe aleatoriamente o território do jogador
    Territorio* jogador = &equipes[sortear_num(max_equipes, 0)];

    int controlador = 1; // Variável de controle do loop principal
    int defensor = 0;    // Índice da equipe defensora
    int opc_menu = 0;    // Opção escolhida no menu

    do
    {
        imprimir_mapa(equipes, jogador);  // Mostra o mapa atualizado

        linha('\n',2);
        linha('=', 55);

        // Menu de opções
        printf("Selecione uma opção: ");
        printf("\n|1- Atacar!| \t |2- Verificar Missao| \t |3- Sair|\n");

        scanf("%d", &opc_menu);           // Lê opção do usuário
        limpar_buffer();                  // Limpa buffer para evitar problemas de leitura
        linha('=', 55);

        // Validação da opção
        if(opc_menu > 3 || opc_menu < 1)
        {
            linha('\n', 10);
            linha('=', 55);
            printf("Selecione uma opção válida\n");
            linha('=', 55);
            continue;  // Volta para o início do loop
        }

        switch(opc_menu)
        {
            case 1: // Ataque
            do
            {
                printf("\nSelecione a equipe defensora(1 a 5): ");
                scanf("%d", &defensor);
                limpar_buffer();

                if(defensor > 5 || defensor < 1)
                {
                    printf("\nSelecione um valor válido!"); 
                    continue;
                }

                if(strcmp(jogador->nome,equipes[defensor - 1].nome) == 0)
                {
                    printf("\nNão pode atacar a si mesmo!");
                    defensor = 0;
                }

            }while(defensor > 5 || defensor < 1 );

            linha('=', 55);
            atacar(jogador, &equipes[defensor - 1]); // Executa o ataque
            break;

            case 2: // Verificar missão
            verificar_missao(equipes, jogador, 1); // Missão 1 hardcoded
            break;

            case 3: // Sair
            printf("Saindo...");
            controlador = 0; // Encerra o loop
            break;

            default:
            printf("Erro!"); // Nunca deve ocorrer devido à validação anterior
            break;
        }

    }while(controlador); // Loop principal do jogo

    // Libera memória alocada
    liberar_memoria(equipes);
    liberar_memoria(jogador);

    return 0;
}
