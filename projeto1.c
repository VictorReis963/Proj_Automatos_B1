/*
 * Projeto 1 - Implementacao de A.F.D.
 * Linguagens Formais e Automatos - 2026-2
 *
 * Integrantes do grupo:
 *   Mihael Rommel b. Xavier / RA: 10239617
 *
 */

#include <stdio.h>

/* Valores de retorno da funcao scanner */
#define ERRO              0
#define INTEIRO           1
#define INTEIRO_COM_SINAL 2

int scanner(char *p)
{
q0:
    if (*p == '-') {
        p++;
        goto q1;
    }
    if (*p >= '1' && *p <= '9') {
        p++;
        goto q7;
    }
    if (*p == '0') {
        p++;
        goto q10;
    }
    return ERRO;

q1:
    if (*p >= '1' && *p <= '9') {
        p++;
        goto q2;
    }
    if (*p == '0') {
        p++;
        goto q5;
    }
    return ERRO;

q2:
    if (*p >= '0' && *p <= '9') {
        p++;
        goto q2;
    }
    if (*p == '\0')
        return INTEIRO_COM_SINAL;
    return ERRO;

q5:
    /* "-0" nao e aceito como inteiro; a continuacao ",x" pertence
       a secao de ponto flutuante, ainda nao implementada aqui. */
    return ERRO;

q7:
    if (*p >= '0' && *p <= '9') {
        p++;
        goto q7;
    }
    if (*p == '\0')
        return INTEIRO;
    return ERRO;

q10:
    /* "0" sozinho e inteiro; qualquer digito depois seria zero a esquerda. */
    if (*p == '\0')
        return INTEIRO;
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
    char w4[] = "0";
    char w5[] = "-0";
    char w6[] = "-";

    imprime(w1, scanner(w1));
    imprime(w2, scanner(w2));
    imprime(w3, scanner(w3));
    imprime(w4, scanner(w4));
    imprime(w5, scanner(w5));
    imprime(w6, scanner(w6));

    return 0;
}
