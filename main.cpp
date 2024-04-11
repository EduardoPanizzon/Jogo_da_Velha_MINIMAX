#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct state
{
    vector<vector<int>> grade = {{0,0,0},{0,0,0},{0,0,0}};
    vector<state*> filhos;

    state(){

    }
    state(int lin, int col){
        this->ult_coluna = col;
        this->ult_linha = lin;
    }
    void show_grid(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << grade[i][j]  << "|";
        }
        cout << endl;
        }
    }
    void getfilhos(bool is_max){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (grade[i][j] == 0){
                    state * novo_state = new state(i,j);
                    novo_state->grade = grade;
                    if(is_max) novo_state->grade[i][j] = 2;
                    else novo_state->grade[i][j] = 1;
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

bool check_horizontal(state *no){
    vector<vector<int>> grade = no->grade;
    if (grade[0][0] == grade[0][1] && grade[0][0] == grade[0][2] && grade[0][0] != 0) return true;
    if (grade[1][0] == grade[1][1] && grade[1][0] == grade[1][2] && grade[1][0] != 0) return true;
    if (grade[2][0] == grade[2][1] && grade[2][0] == grade[2][2] && grade[2][0] != 0) return true;
return false;
}

bool check_vertical(state *no){
    vector<vector<int>> grade = no->grade;
    if (grade[0][0] == grade[1][0] && grade[0][0] == grade[2][0] && grade[0][0] != 0) return true;
    if (grade[0][1] == grade[1][1] && grade[0][1] == grade[2][1] && grade[0][1] != 0) return true;
    if (grade[0][2] == grade[1][2] && grade[0][2] == grade[2][2] && grade[0][2] != 0) return true;
return false;
}

bool check_diagonal(state *no){
    vector<vector<int>> grade = no->grade;
    if (grade[0][0] == grade[1][1] && grade[0][0] == grade[2][2] && grade[0][0] != 0) return true;
    if (grade[0][2] == grade[1][1] && grade[0][2] == grade[2][0] && grade[0][2] != 0) return true;
return false;
}

bool vitoria(state *no){
    if (check_horizontal(no)) return true;
    else if (check_vertical(no)) return true;
    else if (check_diagonal(no)) return true;
    else return false;
}

int minimax(state *no, int depth, bool is_max){
    if(no != nullptr) no->getfilhos(is_max);
    if(no->filhos.size() == 0 || depth == 0){
        if (vitoria(no)) return 1;
        else return 0;
    }
    else if(!is_max){
        int a = 1000;
        for(int i = 0; i < no->filhos.size(); i++){
            a = min(a,minimax(no->filhos[i],depth -1, true));
        }
        return a;
    }
    else{
        int a = -1000;
        for(int i = 0; i < no->filhos.size(); i++){
            a = max(a,minimax(no->filhos[i],depth -1, false));
        }
        return a;
    }
}


int main(int argc, char const *argv[])
{
    state *jogo = new state();
    jogo->show_grid();
    entrada_j1(jogo);    
    jogo->show_grid();
    minimax(jogo,10,true);
    cout << endl;
    jogo->show_grid();


    return 0;
}
