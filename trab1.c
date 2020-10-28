#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
/*Estruturas*/
typedef struct{
    char nome[50];
} DADOS;
typedef struct {
    char *bolas_branca_e_preta;
    int *senha,*tentativa;
} Vetores;
/**/
/*Prótotipos das Funções*/
void Verifica_bola_pretas(int *tentativa,int *senha,char *preto,int tam);
void Verifica_bola_brancas(int *tentativa,int *senha,char *branco,int tam);
void Verifica_Tentativa(int *senha);
void limpa_nome(char nickname[]); /*tira o enter*/
void validacao_acesso_regras(int num1);
void complexidade_jogo(int *nivel);
int valida_nome(char nickname[]); /*!!!!!! falar com o grupo se compensa fazer isso daqui so que usando funcao recursiva(diminuiria o codigo principal)  !!!!!!*/
void valida_nivel(int *nivel);
void gerador_senha(int *senha,int nivel);
void limpar_ponteiros(int *tentativa,char *preto_branco);
/**/
int main(void) {
    Vetores vetor;
    int i,vidas=10,TAM;
     char nickname[11];
    int acesso_regras = 42; /*falta arrumar a funcao daqui*/
    int teste_de_nome = 42;   /*para nao causar problemas com o retorno*/
    int *nivel_do_jogo; /*eu acho que o nivel do jogo tem que ser ponteiro justamente pq quando eu chamar a funcao que valida o nivel ela tem que alterar o nivel escolhido(caso esse seja errado)*/
     /*interação inicial com o usuário*/
    vetor.bolas_branca_e_preta = (char *)malloc(4 * sizeof(char));
    vetor.tentativa= (int *)malloc(4*sizeof(int));
    vetor.senha = (int *)malloc(4*sizeof(int));
    printf("Seja muito bem vindo ao Mastermind\n");
    printf("\n");

    /*nome do usuario*/
    printf("informe seu nome, max de 10 caracteres, sendo eles números ou letras.\n");/**/
    fgets(nickname,11,stdin);
    limpa_nome(nickname);
    valida_nome(nickname);

    teste_de_nome = valida_nome(nickname);
    while(teste_de_nome == 0) {
        printf("Nome inválido.\n");
        printf("Informe seu nome, max de 10 caracteres, sendo eles números ou letras.\n");
        fgets(nickname,11,stdin);
        limpa_nome(nickname);
        teste_de_nome = valida_nome(nickname);
    }
    
    if(teste_de_nome == 1) {
        printf("Nome aceito com sucesso.\n");
    }

    printf("\n");
    /*saudações*/
    printf("%s, chegou a hora de treinar suas habilidades em quebrar códigos.\n", nickname);
    
    /*decisao de acessar ou nao as regras*/
    printf("Deseja acessar o codigo de regras? (digite 1 para sim, 0 para não)\n");
    scanf("%d", &acesso_regras);
    validacao_acesso_regras(acesso_regras);

    printf("\n");
    printf("Complexidade do código:\n"); /*sobrando tempo incluimos o desafio*/
    printf("Digite 1 para nível fácil.\n");
    printf("Digite 2 para nível intermediário.\n");
    printf("Digite 3 para nível difícil.\n");
    nivel_do_jogo = (int *)calloc(1,sizeof(int));
    scanf("%d", nivel_do_jogo);
    complexidade_jogo(nivel_do_jogo);
    
    printf("\n");
    printf("Dicas:\n");
    printf("Cada 'X' indica a quantidade números digitados por você que estão no codigo e estão na posição correta.\n");
    printf("Cada 'O' indica a quantidade números digitados por você que estão no codigo, mas na posição errada.\n");

    if(*nivel_do_jogo == 1) printf("Código fácil gerado com sucesso.\n");
        
    if(*nivel_do_jogo == 2) printf("Código intermediário gerado com sucesso.\n");
    
    if(*nivel_do_jogo == 3) printf("Código difícil gerado com sucesso.\n Boa sorte %s, vai precisar.", nickname);
    switch (*nivel_do_jogo){

    case 1:
        TAM = 4;
        vidas = 10;
        break;

    case 2:
        TAM = 4;
        vidas = 10;
        break;

    case 3:
        TAM = 6;  
        vidas = 12;
        vetor.bolas_branca_e_preta = (char *) realloc(vetor.bolas_branca_e_preta, 6 * sizeof(char));
        vetor.tentativa = (int *)realloc(vetor.tentativa, 6 * sizeof(int)); 
        break;
        default: /*!!!!!!!!! esse default aqui ta com problema?   !!!!!!!!!!*/
    puts("Error 404");
        break;
    }
    gerador_senha(vetor.senha,*nivel_do_jogo);
    for (i = 0; i < TAM; i++)
    {
      printf("%d",vetor.senha[i]);
    }
    while(vidas!=0) {
    printf("\n");
    printf("Digite uma senha(com espaco entre os digitos e depois tecle enter): ");
    
    for (i = 0; i < TAM; i++) {
        scanf("%d",&vetor.tentativa[i]);
    
    }
    
    printf("\n");
    Verifica_bola_pretas(vetor.tentativa,vetor.senha,vetor.bolas_branca_e_preta,TAM);
    Verifica_bola_brancas(vetor.tentativa,vetor.senha,vetor.bolas_branca_e_preta,TAM);
    puts("Senha:* * * * ");
    puts("Tentativa:");
    for (i = 0; i < TAM; i++) {
      printf("%d",vetor.tentativa[i]);
    }

        printf(" || %s\n",vetor.bolas_branca_e_preta);
        vidas--;
        limpar_ponteiros(vetor.tentativa,vetor.bolas_branca_e_preta);
        printf("Digite uma senha: ");
     }
        free(vetor.bolas_branca_e_preta);
        free(vetor.senha);
        free(vetor.tentativa);
    
    return 0;
}
void valida_nivel(int *nivel) {

}

void gerador_senha(int *senha,int nivel) {/*De acordo com o nivel do jogo ele gera uma senha diferente*/
    int i,pos;
    int sorteados[6]={1,2,3,4,5,6};
    srand( (unsigned)time(NULL));
    if(nivel == 1) {/*Nivel 1 gera uma senha de 4 digitos de 1 a 6 sem repetição*/
      for (i=0; i < 4; i++){
        pos = rand() % 5;
        if(sorteados[pos] != 0){
            senha[i] = sorteados[pos];
            sorteados[pos] = 0;
        }
        else i--;
        }
    }
    else if(nivel == 2){/*Nivel 2 gera uma senha de 4 digitos de 1 a 6 com repetição */
    for (i=0; i < 4; i++){
        senha[i] = 1 + rand() % 6;
        }
    }
    else if(nivel == 3){/*Nivel 3 gera uma senha de 6 digitos com repetição*/
        senha = (int *) realloc(senha, 6 * sizeof(int));
        for (i=0; i < 6; i++){
            senha[i] = 1 + rand() % 7;
        }
    }
}

void limpar_ponteiros(int *tentativa,char *preto_branco) {
    *tentativa = 0;
    *preto_branco = 0;
}

void Verifica_bola_pretas(int *tentativa,int *senha,char *branco, int tam) {
   int i;
   /*Esse for verifica se a tentativa esta na posicao certa e preenche o resto com traços*/
    for (i = 0; i < tam; i++){
        if(tentativa[i]==senha[i]) branco[i] = 'X';
    }
}

void Verifica_bola_brancas(int *tentativa,int *senha,char *preto,int tam) {
    int i,j;
    int *aux;
    aux = (int *)malloc(tam * sizeof(int));
    /*Criei um auxiliar para remover os elementos que ja foram checados e nao gerar erro no codigo*/
    for (i = 0; i < tam; i++) {
        aux[i] = senha[i];
    }
    /*esse for verifica se o resto dos elementos do vetor que nao foram verificados aparecem em alguma posicao*/
    for (i = 0; i < tam; i++) {  
        for ( j = 0; j < tam; j++) {
         if(tentativa[i] == aux[j] && preto[i]!='X'&& preto[j]!='X') { 
             preto[i] = 'O';
             aux[j] = 0;
            }
        }
    }
    /*Se a posição do vetor não for 'x' ou 'o' vai receber um traço '-'*/
    for (i = 0; i < tam; i++) {
        if(preto[i]!='X' && preto[i]!='O') preto[i]='-';
    }
}

void limpa_nome(char nickname[]) {
    int tam = strlen(nickname);
    int i;
    
    for(i = 0; i < tam; i++) {
        
        if(nickname[i]=='\n') {
            nickname[i] = '\0';
        }

    }

}

int valida_nome(char nickname[]) {
    int i,tam;
    
    tam = strlen(nickname);

    /*aplicação das restrições do nome*/
    for(i = 0; i < tam; i++) {
        if( !( (nickname[i] >= 'A' && nickname[i] <= 'Z') || (nickname[i] >= 'a' && nickname[i] <= 'z') || (nickname[i] >= '0' && nickname[i] <= '9') || nickname[i]==' ') ) {
    
            return 0;
        } 
    }

    return 1;
}

void complexidade_jogo(int *nivel) {
    
    while(*nivel <1 || *nivel > 3) {

        printf("Complexidade de código inválida.\n");
        printf("Digite 1 para nível fácil\n");
        printf("Digite 2 para nível intermediário\n");
        printf("Digite 3 para nível difícil\n");
        scanf("%d", nivel);
    
    } /*precisa mudar aqui se colocar mais um modo de jogo*/

}

void validacao_acesso_regras(int num1) {
    FILE *ponteiro_para_regras;
    char c;

    while(num1 > 1 || num1 < 0) {
        printf("Desição inválida.\n");
        printf("Digite 1 para ler as regras, digite 0 para pular as regras.\n");
        scanf("%d", &num1);
    }

    if(num1 == 1) {
        
        ponteiro_para_regras = fopen("regras.txt","r");

        if(ponteiro_para_regras == NULL) {
            /*!!!!!!!!!!!! remover esse print !!!!!!!!!!!!!!*/
            printf("o arquivo nao quer abrir, corrijam isso\n");
            exit(5);
        }

        /*printando as regras no console*/
        c = fgetc(ponteiro_para_regras);
        while(!feof(ponteiro_para_regras)) {
            putchar(c);
            c = fgetc(ponteiro_para_regras);  
        }
        fclose(ponteiro_para_regras);
    
    }

    else {
        printf("Nesse caso, vamos ao codigo.\n");
    }

}
