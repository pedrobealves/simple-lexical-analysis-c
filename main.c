#include <stdio.h>
#include <string.h>
#include <malloc.h>

FILE *arq;
char proxCarater;
char *lexema;
int classeCarater;
int tamanhoLex;

//Constantes
#define LETRA 10
#define DIGITO 20
#define EOF 30
#define LIT_INT 40
#define PAR 50
#define OP 60
#define IDENT 80
#define PNTS 90
#define OUTRO 100

// Escopo de funções
void abrirArquivo();
int obtemCarater();
void acrescentaCarater();
int lex();
int pesquisa(char);
void printTokenAndLexema(int);
void espacos();
int naoespaco(char);
int eAlfabeto();
int eDigito();

int main() {
    abrirArquivo();
    return 0;
}

void abrirArquivo(){
    int prox;
    if ((arq = fopen("codigo.txt", "r")) == NULL)
        printf("Erro \n");
    else {
        printf("\tToken \t\tLexeme\n");
        classeCarater = obtemCarater();
        do {
            prox = lex(classeCarater);
            printTokenAndLexema(prox);
        } while (prox != EOF);
    }
}

void printTokenAndLexema(int token){
    char tokenText[50];
    switch (token) {
        case IDENT:
            strcpy(tokenText, "identificador");
        break;
        case LIT_INT:
            strcpy(tokenText, "int_literal");
            break;
        case OP:
            strcpy(tokenText, "operador");
            break;
        case PAR:
            strcpy(tokenText, "parenteses");
            break;
        case PNTS:
            strcpy(tokenText, "pontos");
            break;
        case EOF:
            strcpy(tokenText, "EOF");
            break;
    }
    printf("%s\t\t%s\n",
           tokenText, lexema);
}

int lex() {
    int ant;
    tamanhoLex = 0;
    espacos();
    lexema = (char *) malloc(sizeof(char));
    switch (classeCarater) {
        case LETRA:
            acrescentaCarater();
            classeCarater = obtemCarater();
            while (classeCarater == LETRA || classeCarater == DIGITO) {
                acrescentaCarater();
                classeCarater = obtemCarater();
            }
            return IDENT;
            break;
        case DIGITO:
            acrescentaCarater();
            classeCarater = obtemCarater();
            while (classeCarater == DIGITO) {
                acrescentaCarater();
                classeCarater = obtemCarater();
            }
            return LIT_INT;
            break;
        case OUTRO:
            ant = pesquisa(proxCarater);
            classeCarater = obtemCarater();
            return ant;
            break;
    }
    return 0;
}

int obtemCarater() {
    if ((proxCarater = getc(arq)) != EOF) {
        if (eAlfabeto())
            return LETRA;
        else if (eDigito())
            return DIGITO;
        else return OUTRO;
    }
    return EOF;
}

int eAlfabeto(){
    return ( (proxCarater >= 'a' && proxCarater <= 'z') || (proxCarater >= 'A' && proxCarater <= 'Z') );
}

int eDigito(){
    return ( proxCarater >= '0' && proxCarater <= '9' );
}

void acrescentaCarater() {
    lexema = (char *) realloc(lexema, sizeof(char));
    lexema[tamanhoLex++] = proxCarater;
    lexema[tamanhoLex] = 0;
}

int pesquisa(char ch) {
    if (ch == '(' || ch == ')'){
        acrescentaCarater();
        return PAR;
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>') {
        acrescentaCarater();
        return OP;
    } else if (ch == ';' || ch == ':'){
        acrescentaCarater();
        return PNTS;
    }
    else {
        return EOF;
    }
}

void espacos() {
    while (naoespaco(proxCarater))
        classeCarater = obtemCarater();
}

int naoespaco(char ch) {
    return ch == ' ' || ch == '\t' ||  ch == '\v' ||  ch == '\f' ||  ch == '\r';
}