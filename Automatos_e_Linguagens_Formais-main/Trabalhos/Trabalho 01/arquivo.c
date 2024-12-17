#include <stdio.h>
#define MAX_STATES 12
#define DEAD_STATE -1


typedef struct {
    int epsilon[MAX_STATES][2];
    int delta[MAX_STATES][2];
    int initial_state;
    int final_states[5];
} Automato;

Automato automato;
char input[52];
int len_input = 0;

void init_automaton();
void transition(char symbol, int *current_state);
int epsilon_trans(int state, int current_index);
int is_accepted(int state);
int simulate_automaton(int current_index, int current_state);

void init_automaton() {
    automato.initial_state = 0;

    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < 2; j++) {
            automato.delta[i][j] = DEAD_STATE;
        }
    }

    automato.delta[1][1] = 2;
    automato.delta[2][0] = 3;
    automato.delta[3][0] = 4;
    automato.delta[4][1] = 5;
    automato.delta[5][0] = 6;
    automato.delta[7][1] = 8;
    automato.delta[8][0] = 9;
    automato.delta[9][0] = 10;
    automato.delta[10][0] = 11;

    for (int i = 0; i < MAX_STATES; i++) {
        automato.epsilon[i][0] = DEAD_STATE;
        automato.epsilon[i][1] = DEAD_STATE;
    }

    automato.epsilon[0][0] = 1;
    automato.epsilon[0][1] = 7;
    automato.epsilon[4][0] = 1;
    automato.epsilon[4][1] = 7;
    automato.epsilon[6][0] = 1;
    automato.epsilon[6][1] = 7;
    automato.epsilon[9][0] = 7;
    automato.epsilon[11][0] = 7;

    automato.final_states[0] = 0;
    automato.final_states[1] = 4;
    automato.final_states[2] = 6;
    automato.final_states[3] = 9;
    automato.final_states[4] = 11;
}

void transition(char symbol, int *current_state) {
    if(*current_state == DEAD_STATE) return;

    int index = (symbol == '0') ? 0 : 1;
    *current_state = automato.delta[*current_state][index];
}

int epsilon_trans(int state, int current_index) {
    for(int i = 0; i < 2; i++) {
        int next_state = automato.epsilon[state][i];
        if(next_state != DEAD_STATE) {
            if(simulate_automaton(current_index, next_state)) {
                return 1;
            }
        }
    }
    return 0;
}

int is_accepted(int state) {
    for(int i = 0; i < 5; i++) {
        if(state == automato.final_states[i]) {
            return 1;
        }
    }
    return 0;
}

int simulate_automaton(int current_index, int current_state) {
    if(current_index >= len_input) {
        return is_accepted(current_state);
    }

    if(epsilon_trans(current_state, current_index)) {
        return 1;
    }

    transition(input[current_index], &current_state);

    if(current_state == DEAD_STATE) {
        return 0;
    }
    return simulate_automaton(current_index + 1, current_state);
}

int main() {
    init_automaton();

    fgets(input, 52, stdin);

    while(input[len_input] != '\0' && input[len_input] != '\n') {
        len_input++;
    }
    input[len_input] = '\0';

    if(simulate_automaton(0, automato.initial_state)) {
        printf("sim\n");
    }
    else {
        printf("nao\n");
    }
    return 0;
}

