#include <stdio.h>

// Índice para controlar a posição atual na string de entrada
int i = 0;
// Array de caracteres: armazena a string de entrada com até 1000 caracteres + o caractere nulo '\0'
char input[1001];

// Funções para cada símbolo não terminal
int S();
int A();
int B();
int C();
int D();

// Função para verificar se o caractere atual é 'a'
int match(char c) {
    if (input[i] == c) {
        i++;
        return 1;
    }
    return 0;
}

int S() {
    int pos = i;
    if (A()) return 1;  // S → A
    i = pos;
    if (B()) return 1;  // S → B
    i = pos;
    if (match('a') && B() && match('b')) return 1;  // S → aBb
    i = pos;
    return 0;
}

int A() {
    int pos = i;
    if (match('a') && D()) return 1;  // A → aD
    i = pos;
    if (match('b') && C()) return 1;  // A → bC
    i = pos;
    return 1;  // A → ε (epsilon)
}

int B() {
    int pos = i;
    if (match('a') && C()) return 1;  // B → aC
    i = pos;
    if (match('b') && D()) return 1;  // B → bD
    i = pos;
    return 0;
}

int C() {
    int pos = i;
    if (match('a') && B()) return 1;  // C → aB
    i = pos;
    if (match('b') && A()) return 1;  // C → bA
    i = pos;
    return 0;
}

int D() {
    int pos = i;
    if (match('a') && A()) return 1;  // D → aA
    i = pos;
    if (match('b') && B()) return 1;  // D → bB
    i = pos;
    return 0;
}

int main() {
    // Lê a entrada do usuário
    fgets(input, 1001, stdin);

    // Verifica se a string pertence à linguagem
    if (S() && input[i] == '\n') {
        printf("sim\n");
    } else {
        printf("nao\n");
    }

    return 0;
}
