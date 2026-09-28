/*
 * Projeto 1 - Implementacao de A.F.D.
 * Linguagens Formais e Automatos - 2026-2
 *
 * Integrantes do grupo:
 *   Mihael Rommel b. Xavier     / RA: 10239617
 *   Gian Lucca Campanha Ribeiro / RA: 10438361
 *   Victor Reis da Silva        / RA: 10420297
 *   KAUA VICTOR OLIVEIRA DE SOUSA / RA: 10444362
 */

#include <stdio.h>

/* Valores de retorno da funcao scanner */
#define ERRO                      0
#define INTEIRO                   1
#define INTEIRO_COM_SINAL         2
#define VALOR_MONETARIO           3
#define PONTO_FLUTUANTE           4
#define PONTO_FLUTUANTE_COM_SINAL 5

int scanner(char *p)
{
q0:
    if (*p == '-') { p++; goto q1; }
    if (*p >= '1' && *p <= '9') { p++; goto q7; }
    if (*p == '0') { p++; goto q10; }
    if (*p == '$') { p++; goto q12; }
    return ERRO;

q1:
    if (*p >= '1' && *p <= '9') { p++; goto q2; }
    if (*p == '0') { p++; goto q5; }
    return ERRO;

q2:
    if (*p >= '0' && *p <= '9') { p++; goto q2; }
    if (*p == ',') { p++; goto q3; } /* Transicao para flutuante com sinal */
    if (*p == '\0') return INTEIRO_COM_SINAL;
    return ERRO;

q3:
    if (*p >= '0' && *p <= '9') { p++; goto q4; }
    return ERRO;

q4:
    if (*p >= '0' && *p <= '9') { p++; goto q4; }
    if (*p == '\0') return PONTO_FLUTUANTE_COM_SINAL;
    return ERRO;

q5:
    if (*p == ',') { p++; goto q6; } /* O "-0" leva obrigatoriamente a virgula */
    return ERRO;

q6:
    /* Apos "-0,", so aceita de 1 a 9, proibindo "-0,0" */
    if (*p >= '1' && *p <= '9') { p++; goto q4; }
    return ERRO;

q7:
    if (*p >= '0' && *p <= '9') { p++; goto q7; }
    if (*p == ',') { p++; goto q8; } /* Transicao para flutuante */
    if (*p == '\0') return INTEIRO;
    return ERRO;

q8:
    if (*p >= '0' && *p <= '9') { p++; goto q9; }
    return ERRO;

q9:
    if (*p >= '0' && *p <= '9') { p++; goto q9; }
    if (*p == '\0') return PONTO_FLUTUANTE;
    return ERRO;

q10:
    if (*p == ',') { p++; goto q11; } /* O "0" vai para flutuante */
    if (*p == '\0') return INTEIRO;
    return ERRO;

q11:
    /* Apos "0,", so aceita de 1 a 9, proibindo "0,0" */
    if (*p >= '1' && *p <= '9') { p++; goto q9; }
    return ERRO;

q12:
    if (*p == '0') { p++; goto q13; }
    if (*p >= '1' && *p <= '9') { p++; goto q14; }
    return ERRO;

q13:
    if (*p == ',') { p++; goto q20; }
    return ERRO;

q14:
    if (*p >= '0' && *p <= '9') { p++; goto q15; }
    if (*p == '.') { p++; goto q17; }
    if (*p == ',') { p++; goto q20; }
    return ERRO;

q15:
    if (*p >= '0' && *p <= '9') { p++; goto q16; }
    if (*p == '.') { p++; goto q17; }
    if (*p == ',') { p++; goto q20; }
    return ERRO;

q16:
    if (*p == '.') { p++; goto q17; }
    if (*p == ',') { p++; goto q20; }
    return ERRO;

q17:
    if (*p >= '0' && *p <= '9') { p++; goto q18; }
    return ERRO;

q18:
    if (*p >= '0' && *p <= '9') { p++; goto q19; }
    return ERRO;

q19:
    if (*p >= '0' && *p <= '9') { p++; goto q16; }
    return ERRO;

q20:
    if (*p >= '0' && *p <= '9') { p++; goto q21; }
    return ERRO;

q21:
    if (*p >= '0' && *p <= '9') { p++; goto q22; }
    return ERRO;

q22:
    if (*p == '\0') return VALOR_MONETARIO;
    return ERRO;
}

void imprime(char *palavra, int resultado)
{
    printf("para \"%s\" e ", palavra);
    switch (resultado) {
    case INTEIRO:
        printf("<INTEIRO>\n");
        break;
    case INTEIRO_COM_SINAL:
        printf("<INTEIRO COM SINAL>\n");
        break;
    case VALOR_MONETARIO:
        printf("<VALOR MONETARIO>\n");
        break;
    case PONTO_FLUTUANTE:
        printf("<P. FLUTUANTE>\n");
        break;
    case PONTO_FLUTUANTE_COM_SINAL:
        printf("<P. FLUTUANTE COM SINAL>\n");
        break;
    default:
        printf("<ERRO>\n");
        break;
    }
}

int main(void)
{
    char w1[] = "21";
    char w2[] = "-21";
    char w3[] = "021";
    char w4[] = "2.1";
    char w5[] = "2,1";
    char w6[] = "-0,34";
    char w7[] = "05,567";
    char w8[] = "$5.567,78";
    /*Obs: Possível erro na documentação do projeto.
    Entao considerei que 2.1 e -2.1 é erro no documento do projeto
    o ponto flutuante eh exclusivamente com virgula*/
    char w9[] = "-2.1"; // 

    imprime(w1, scanner(w1));
    imprime(w2, scanner(w2));
    imprime(w3, scanner(w3));
    imprime(w4, scanner(w4));
    imprime(w5, scanner(w5));
    imprime(w6, scanner(w6));
    imprime(w7, scanner(w7));
    imprime(w8, scanner(w8));
    imprime(w9, scanner(w9));

    return 0;
}
