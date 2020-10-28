#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpa_nome(char nickname[]); /*tira o enter*/
void validacao_acesso_regras(int num1);

void complexidade_jogo(int *nivel);
int valida_nome(char nickname[]); /*!!!!!! falar com o grupo se compensa fazer isso daqui so que usando funcao recursiva(diminuiria o codigo principal)  !!!!!!*/



int main(void) {
    char nickname[11];
    int acesso_regras = 42; /*falta arrumar a funcao daqui*/
    int teste_de_nome = 42;   /*para nao causar problemas com o retorno*/
    int *nivel_do_jogo; /*eu acho que o nivel do jogo tem que ser ponteiro justamente pq quando eu chamar a funcao que valida o nivel ela tem que alterar o nivel escolhido(caso esse seja errado)*/

    /*interação inicial com o usuário*/
    printf("Seja muito bem vindo ao Mastermind\n");
    printf("\n");

    /*nome do usuario*/
    printf("informe seu nome, max de 10 caracteres, sendo eles números ou letras(sem acento).\n");/**/
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
    printf("Deseja acessar o codigo de regras? (digite 1 para sim, zero para não)\n");
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
    

    return 0;
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
        printf("Decisão inválida.\n");
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