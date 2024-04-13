#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct state {
    vector<vector<int>> grade = {{0,0,0},{0,0,0},{0,0,0}};
    vector<state*> filhos;

    void show_grid(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                cout << grade[i][j]  << "|";
            }
            cout << endl;
        }
    }

    void getfilhos(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (grade[i][j] == 0){
                    state * novo_state = new state();
                    novo_state->grade = grade;
                    novo_state->grade[i][j] = 2;
                    filhos.push_back(novo_state);
                }
            }
        }
    }
};

void entrada_j1(state* jogo){
    int idx = 0;
    cout << "Digite a posicao:" ;
    cin >> idx;
    idx += -1;
    int coluna = idx%3;
    int linha = (int) floorf(idx/(float)3);

    jogo->grade[linha][coluna] = 1;
}

bool check_vitoria(state *no){
    vector<vector<int>> grade = no->grade;

    for (int i = 0; i < 3; ++i) {
        if (grade[i][0] == grade[i][1] && grade[i][0] == grade[i][2] && grade[i][0] != 0)
            return true;
        if (grade[0][i] == grade[1][i] && grade[0][i] == grade[2][i] && grade[0][i] != 0)
            return true;
    }

    if (grade[0][0] == grade[1][1] && grade[0][0] == grade[2][2] && grade[0][0] != 0)
        return true;
    if (grade[0][2] == grade[1][1] && grade[0][2] == grade[2][0] && grade[0][2] != 0)
        return true;

    return false;
}

bool tabuleiro_cheio(state *no) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (no->grade[i][j] == 0)
                return false;
        }
    }
    return true;
}

int minimax(state *no, int depth, bool is_max) {
    if (check_vitoria(no))
        return is_max ? -1 : 1;
    if (tabuleiro_cheio(no))
        return 0;

    if (is_max) {
        int best_score = -1000;
        for (state* filho : no->filhos) {
            int score = minimax(filho, depth - 1, false);
            best_score = max(best_score, score);
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (state* filho : no->filhos) {
            int score = minimax(filho, depth - 1, true);
            best_score = min(best_score, score);
        }
        return best_score;
    }
}

int main() {
    state *jogo = new state();
    jogo->show_grid();

    while (true) {
        entrada_j1(jogo);
        jogo->show_grid();

        if (check_vitoria(jogo)) {
            cout << "Jogador humano ganhou!" << endl;
            break;
        }

        if (tabuleiro_cheio(jogo)) {
            cout << "O jogo acabou empatado!" << endl;
            break;
        }

        jogo->getfilhos();
        int best_score = -1000;
        state* melhor_jogada = nullptr;
        for (state* filho : jogo->filhos) {
            int score = minimax(filho, 10, false);
            if (score > best_score) {
                best_score = score;
                melhor_jogada = filho;
            }
        }

        if (melhor_jogada) {
            cout << "Próxima jogada do computador: " << endl;
            melhor_jogada->show_grid();
            jogo = melhor_jogada;
        } else {
            cout << "Erro: Nenhuma jogada disponível para o computador!" << endl;
            break;
        }

        if (check_vitoria(jogo)) {
            cout << "Computador ganhou!" << endl;
            break;
        }

        if (tabuleiro_cheio(jogo)) {
            cout << "O jogo acabou empatado!" << endl;
            break;
        }
    }

    return 0;
}
