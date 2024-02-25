#include <iostream>
using namespace std;
#include <vector>

struct piece {
    int deplacement;
    int valeur;
    char couleur;
    char symbole;
    bool empty;
};

struct pion_blanc : public piece {
    pion_blanc() {
        deplacement = 1;
        valeur = 1;
        couleur = 'B';
        symbole = 'P';
        empty = false;
    }
};

struct pion_noir : public piece {
    pion_noir() {
        deplacement = 2;
        valeur = 1;
        couleur = 'N';
        symbole = 'p';
        empty = false;
    }
};

struct cavalier_blanc : public piece {
    cavalier_blanc() {
        deplacement = 3;
        valeur = 3;
        couleur = 'B';
        symbole = 'C';
        empty = false;
    }
};

struct cavalier_noir : public piece {
    cavalier_noir() {
        deplacement = 3;
        valeur = 3;
        couleur = 'N';
        symbole = 'c';
        empty = false;
    }
};

struct fou_blanc : public piece {
    fou_blanc() {
        deplacement = 4;
        valeur = 3;
        couleur = 'B';
        symbole = 'F';
        empty = false;
    }
};

struct fou_noir : public piece {
    fou_noir() {
        deplacement = 4;
        valeur = 3;
        couleur = 'N';
        symbole = 'f';
        empty = false;
    }
};

struct tour_blanche : public piece {
    tour_blanche() {
        deplacement = 5;
        valeur = 5;
        couleur = 'B';
        symbole = 'T';
        empty = false;
    }
};

struct tour_noire : public piece {
    tour_noire() {
        deplacement = 5;
        valeur = 5;
        couleur = 'N';
        symbole = 't';
        empty = false;
    }
};

struct dame_blanche : public piece {
    dame_blanche() {
        deplacement = 6;
        valeur = 9;
        couleur = 'B';
        symbole = 'D';
        empty = false;
    }
};

struct dame_noire : public piece {
    dame_noire() {
        deplacement = 6;
        valeur = 9;
        couleur = 'N';
        symbole = 'd';
        empty = false;
    }
};

struct roi_blanc : public piece {
    roi_blanc() {
        deplacement = 0;
        valeur = 0;
        couleur = 'B';
        symbole = 'R';
        empty = false;
    }
};

struct roi_noir : public piece {
    roi_noir() {
        deplacement = 0;
        valeur = 0;
        couleur = 'N';
        symbole = 'r';
        empty = false;
    }
};

struct case_vide : public piece {
    case_vide () {
        empty = true;
        symbole = ' ';
    }
};

struct chessboard {
    piece* board[8][8];
    bool* echec = new bool(false);
    bool* petit_rock_blanc_possible = new bool(true);
    bool* grand_rock_blanc_possible = new bool(true);
    bool* petit_rock_noir_possible = new bool(true);
    bool* grand_rock_noir_possible = new bool(true);
    chessboard() {
        for (int i = 0; i < 8; ++i) {
            board[i][1] = new pion_blanc();
            board[i][6] = new pion_noir();
            for (int j = 2; j < 6; ++j) {
                board[i][j] = new case_vide();
            }
        }
        board[0][0] = new tour_blanche();
        board[1][0] = new cavalier_blanc();
        board[2][0] = new fou_blanc();
        board[3][0] = new dame_blanche();
        board[4][0] = new roi_blanc();
        board[5][0] = new fou_blanc();
        board[6][0] = new cavalier_blanc();
        board[7][0] = new tour_blanche();
        board[0][7] = new tour_noire();
        board[1][7] = new cavalier_noir();
        board[2][7] = new fou_noir();
        board[3][7] = new dame_noire();
        board[4][7] = new roi_noir();
        board[5][7] = new fou_noir();
        board[6][7] = new cavalier_noir();
        board[7][7] = new tour_noire();
    }
    ~chessboard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
            }
        }
    }
    void echec_ou_pas(char tour) {
        if (tour == 'B') {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (!board[i][j]->empty && board[i][j]->couleur == 'N' && board[i][j]->symbole != 'r') {
                        coups_possibles(i,j);
                        if (*echec) {
                            break;
                        }
                    }
                }
            }
        }
        else {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (!board[i][j]->empty && board[i][j]->couleur == 'B' && board[i][j]->symbole != 'R') {
                        coups_possibles(i,j);
                        if (*echec) {
                            break;
                        }
                    }
                }
            }
        }
    }
    void changement(int i1, int j1, int i2, int j2) {
        delete board[i2][j2];
        switch (board[i1][j1]->symbole) {
            case 'P':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                if (j2 == 7) {
                    cout << "Choisis une pièce pour la promotion (D = dame, T = tour, C = cavalier, F = fou) : ";
                    char nouvelle_piece;
                    cin >> nouvelle_piece;
                    cout << endl;
                    switch (nouvelle_piece) {
                        case 'D':
                            board[i2][j2] = new dame_blanche();
                            break;
                        case 'T':
                            board[i2][j2] = new tour_blanche();
                            break;
                        case 'C':
                            board[i2][j2] = new cavalier_blanc();
                            break;
                        case 'F':
                            board[i2][j2] = new fou_blanc();
                            break;
                    }
                    break;
                }
                else {
                    board[i2][j2] = new pion_blanc();
                    break;
                }
            case 'p':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                if (j2 == 0) {
                    cout << "Choisis une pièce pour la promotion (D = dame, T = tour, C = cavalier, F = fou) : ";
                    char nouvelle_piece;
                    cin >> nouvelle_piece;
                    cout << endl;
                    switch (nouvelle_piece) {
                        case 'D':
                            board[i2][j2] = new dame_noire();
                            break;
                        case 'T':
                            board[i2][j2] = new tour_noire();
                            break;
                        case 'C':
                            board[i2][j2] = new cavalier_noir();
                            break;
                        case 'F':
                            board[i2][j2] = new fou_noir();
                            break;
                    }
                }
                else {
                    board[i2][j2] = new pion_noir();
                }
                break;
            case 'C':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new cavalier_blanc();
                break;
            case 'c':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new cavalier_noir();
                break;
            case 'F':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new fou_blanc();
                break;
            case 'f':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new fou_noir();
                break;
            case 'T':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new tour_blanche();
                break;
            case 't':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new tour_noire();
                break;
            case 'D':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new dame_blanche();
                break;
            case 'd':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new dame_noire();
                break;
            case 'R':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new roi_blanc();
                break;
            case 'r':
                delete board[i1][j1];
                board[i1][j1] = new case_vide();
                board[i2][j2] = new roi_noir();
                break;
        }
    }
    void retour(char symbole1, int i1, int j1, char symbole2, int i2, int j2) {
        delete board[i1][j1];
        delete board[i2][j2];
        switch (symbole1) {
            case 'P':
                board[i1][j1] = new pion_blanc();
                break;
            case 'p':
                board[i1][j1] = new pion_noir();
                break;
            case 'C':
                board[i1][j1] = new cavalier_blanc();
                break;
            case 'c':
                board[i1][j1] = new cavalier_noir();
                break;
            case 'F':
                board[i1][j1] = new fou_blanc();
                break;
            case 'f':
                board[i1][j1] = new fou_noir();
                break;
            case 'T':
                board[i1][j1] = new tour_blanche();
                break;
            case 't':
                board[i1][j1] = new tour_noire();
                break;
            case 'D':
                board[i1][j1] = new dame_blanche();
                break;
            case 'd':
                board[i1][j1] = new dame_noire();
                break;
            case 'R':
                board[i1][j1] = new roi_blanc();
                break;
            case 'r':
                board[i1][j1] = new roi_noir();
                break;
        }
        switch (symbole2) {
            case ' ':
                board[i2][j2] = new case_vide();
                break;
            case 'P':
                board[i2][j2] = new pion_blanc();
                break;
            case 'p':
                board[i2][j2] = new pion_noir();
                break;
            case 'C':
                board[i2][j2] = new cavalier_blanc();
                break;
            case 'c':
                board[i2][j2] = new cavalier_noir();
                break;
            case 'F':
                board[i2][j2] = new fou_blanc();
                break;
            case 'f':
                board[i2][j2] = new fou_noir();
                break;
            case 'T':
                board[i2][j2] = new tour_blanche();
                break;
            case 't':
                board[i2][j2] = new tour_noire();
                break;
            case 'D':
                board[i2][j2] = new dame_blanche();
                break;
            case 'd':
                board[i2][j2] = new dame_noire();
                break;
            case 'R':
                board[i2][j2] = new roi_blanc();
                break;
            case 'r':
                board[i2][j2] = new roi_noir();
                break;
        }
    }
    void affichage() {
        for (int j = 0; j < 8; ++j) {
            cout << " | ";
            for (int i = 0; i < 8; ++i) {
                cout << board[i][7-j]->symbole << " | ";
            }
            cout << endl << endl;
        }
    }
    int valeur_totale() {
        int sum = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!board[i][j]->empty) {
                    sum += board[i][j]->valeur;
                }
            }
        }
        return sum;
    }
    vector<pair<int,int>> coups_possibles(int i, int j) {
        vector<pair<int,int>> coups;
        if (board[i][j]->deplacement == 1) {
            if (board[i][j+1]->empty) {
                coups.push_back({i,j+1});
                if (j == 1 && board[i][j+2]->empty) {
                    coups.push_back({i,j+2});
                }
            }
            if (i != 7 && !board[i+1][j+1]->empty && board[i+1][j+1]->couleur == 'N') {
                coups.push_back({i+1,j+1});
                if (board[i+1][j+1]->symbole == 'r') {
                    *echec = true;
                }
            }
            if (i != 0 && !board[i-1][j+1]->empty && board[i-1][j+1]->couleur == 'N') {
                coups.push_back({i-1,j+1});
                if (board[i-1][j+1]->symbole == 'r') {
                    *echec = true;
                }
            }
            //prise en passant à gérer
        }
        if (board[i][j]->deplacement == 2) {
            if (board[i][j-1]->empty) {
                coups.push_back({i,j-1});
                if (j == 6 && board[i][j-2]->empty) {
                    coups.push_back({i,j-2});
                }
            }
            if (i != 7 && !board[i+1][j-1]->empty && board[i+1][j-1]->couleur == 'B') {
                coups.push_back({i+1,j-1});
                if (board[i+1][j-1]->symbole == 'R') {
                    *echec = true;
                }
            }
            if (i != 0 && !board[i-1][j-1]->empty && board[i-1][j-1]->couleur == 'B') {
                coups.push_back({i-1,j-1});
                if (board[i-1][j-1]->symbole == 'R') {
                    *echec = true;
                }
            }
            //prise en passant à gérer
        }
        if (board[i][j]->deplacement == 0) {
            int deplacements[8][2] = {{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
            for (int k = 0; k < 8; ++k) {
                if (0 < i+deplacements[k][0] && i+deplacements[k][0] < 8 && 0 < j+deplacements[k][1] && j+deplacements[k][1] < 8 && board[i+deplacements[k][0]][j+deplacements[k][1]]->empty) {
                    int nouveau_i = i + deplacements[k][0];
                    int nouveau_j = j + deplacements[k][1];
                    bool ok = true;
                    if (board[i][j]->couleur == 'B') {
                        for (int l = 0; l < 8; ++l) {
                            if (board[nouveau_i+deplacements[l][0]][nouveau_j+deplacements[l][1]]->symbole == 'r') {
                                ok = false;
                                break;
                            }
                        }
                    }
                    if (board[i][j]->couleur == 'N') {
                        for (int l = 0; l < 8; ++l) {
                            if (board[nouveau_i+deplacements[l][0]][nouveau_j+deplacements[l][1]]->symbole == 'R') {
                                ok = false;
                                break;
                            }
                        }
                    }
                    if (ok) {
                        coups.push_back({i+deplacements[k][0],j+deplacements[k][1]});
                    }
                }
            }
            if (board[i][j]->couleur == 'B') {
                if (*petit_rock_blanc_possible) {
                    echec_ou_pas('B');
                    if (!*echec && board[5][0]->empty && board[6][0]->empty) {
                        *echec = false;
                        changement(i,j,i+1,j);
                        echec_ou_pas('B');
                        if (!*echec) {
                            coups.push_back({i+2,j});
                        }
                        *echec = false;
                        retour('R',i,j,' ',i+1,j);
                    }
                }
                if (*grand_rock_blanc_possible) {
                    echec_ou_pas('B');
                    if (!*echec && board[3][0]->empty && board[2][0]->empty && board[1][0]->empty) {
                        *echec = false;
                        changement(i,j,i-1,j);
                        echec_ou_pas('B');
                        if (!*echec) {
                            coups.push_back({i-2,j});
                        }
                        *echec = false;
                        retour('R',i,j,' ',i-1,j);
                    }
                }
            }
            if (board[i][j]->couleur == 'N') {
                if (*petit_rock_noir_possible) {
                    echec_ou_pas('N');
                    if (!*echec && board[5][7]->empty && board[6][7]->empty) {
                        *echec = false;
                        changement(i,j,i+1,j);
                        echec_ou_pas('N');
                        if (!*echec) {
                            coups.push_back({i+2,j});
                        }
                        *echec = false;
                        retour('r',i,j,' ',i+1,j);
                    }
                }
                if (*grand_rock_noir_possible) {
                    echec_ou_pas('N');
                    if (!*echec && board[3][7]->empty && board[2][7]->empty && board[1][7]->empty) {
                        *echec = false;
                        changement(i,j,i-1,j);
                        echec_ou_pas('N');
                        if (!*echec) {
                            coups.push_back({i-2,j});
                        }
                        *echec = false;
                        retour('r',i,j,' ',i-1,j);
                    }
                }
            }
        }
        if (board[i][j]->deplacement == 3) {
            int deplacements[8][2] = {{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};
            for (int k = 0; k < 8; ++k) {
                if (0 < i+deplacements[k][0] && i+deplacements[k][0] < 8 && 0 < j+deplacements[k][1] && j+deplacements[k][1] < 8) {
                    if (board[i+deplacements[k][0]][j+deplacements[k][1]]->empty) {
                        coups.push_back({i+deplacements[k][0],j+deplacements[k][1]});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+deplacements[k][0]][j+deplacements[k][1]]->couleur == 'N') {
                        coups.push_back({i+deplacements[k][0],j+deplacements[k][1]});
                        if (board[i+deplacements[k][0]][j+deplacements[k][1]]->symbole == 'r') {
                            *echec = true;
                        }
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+deplacements[k][0]][j+deplacements[k][1]]->couleur == 'B') {
                        coups.push_back({i+deplacements[k][0],j+deplacements[k][1]});
                        if (board[i+deplacements[k][0]][j+deplacements[k][1]]->symbole == 'R') {
                            *echec = true;
                        }
                    }
                }
            }
        }
        if (board[i][j]->deplacement == 4) {
            for (int k = 1; k < 8; ++k) {
                if (i+k < 8 && j+k < 8) {
                    if (board[i+k][j+k]->empty) {
                        coups.push_back({i+k,j+k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+k][j+k]->couleur == 'N') {
                        coups.push_back({i+k,j+k});
                        if (board[i+k][j+k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+k][j+k]->couleur == 'B') {
                        coups.push_back({i+k,j+k});
                        if (board[i+k][j+k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i+k < 8 && j-k >= 0) {
                    if (board[i+k][j-k]->empty) {
                        coups.push_back({i+k,j-k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+k][j-k]->couleur == 'N') {
                        coups.push_back({i+k,j-k});
                        if (board[i+k][j-k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+k][j-k]->couleur == 'B') {
                        coups.push_back({i+k,j-k});
                        if (board[i+k][j-k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i-k >= 0 && j+k < 8) {
                    if (board[i-k][j+k]->empty) {
                        coups.push_back({i-k,j+k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i-k][j+k]->couleur == 'N') {
                        coups.push_back({i-k,j+k});
                        if (board[i-k][j+k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i-k][j+k]->couleur == 'B') {
                        coups.push_back({i-k,j+k});
                        if (board[i-k][j+k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i-k >= 0 && j-k >= 0) {
                    if (board[i-k][j-k]->empty) {
                        coups.push_back({i-k,j-k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i-k][j-k]->couleur == 'N') {
                        coups.push_back({i-k,j-k});
                        if (board[i-k][j-k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i-k][j-k]->couleur == 'B') {
                        coups.push_back({i-k,j-k});
                        if (board[i-k][j-k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        if (board[i][j]->deplacement == 5) {
            for (int k = 1; k < 8; ++k) {
                if (i+k < 8) {
                    if (board[i+k][j]->empty) {
                        coups.push_back({i+k,j});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+k][j]->couleur == 'N') {
                        coups.push_back({i+k,j});
                        if (board[i+k][j]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+k][j]->couleur == 'B') {
                        coups.push_back({i+k,j});
                        if (board[i+k][j]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (j+k < 8) {
                    if (board[i][j+k]->empty) {
                        coups.push_back({i,j+k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i][j+k]->couleur == 'N') {
                        coups.push_back({i,j+k});
                        if (board[i][j+k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i][j+k]->couleur == 'B') {
                        coups.push_back({i,j+k});
                        if (board[i][j+k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i-k >= 0) {
                    if (board[i-k][j]->empty) {
                        coups.push_back({i-k,j});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i-k][j]->couleur == 'N') {
                        coups.push_back({i-k,j});
                        if (board[i-k][j]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i-k][j]->couleur == 'B') {
                        coups.push_back({i-k,j});
                        if (board[i-k][j]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (j-k >= 0) {
                    if (board[i][j-k]->empty) {
                        coups.push_back({i,j-k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i][j-k]->couleur == 'N') {
                        coups.push_back({i,j-k});
                        if (board[i][j-k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i][j-k]->couleur == 'B') {
                        coups.push_back({i,j-k});
                        if (board[i][j-k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        if (board[i][j]->deplacement == 6) {
            for (int k = 1; k < 8; ++k) {
                if (i+k < 8 && j+k < 8) {
                    if (board[i+k][j+k]->empty) {
                        coups.push_back({i+k,j+k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+k][j+k]->couleur == 'N') {
                        coups.push_back({i+k,j+k});
                        if (board[i+k][j+k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+k][j+k]->couleur == 'B') {
                        coups.push_back({i+k,j+k});
                        if (board[i+k][j+k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i+k < 8 && j-k >= 0) {
                    if (board[i+k][j-k]->empty) {
                        coups.push_back({i+k,j-k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+k][j-k]->couleur == 'N') {
                        coups.push_back({i+k,j-k});
                        if (board[i+k][j-k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+k][j-k]->couleur == 'B') {
                        coups.push_back({i+k,j-k});
                        if (board[i+k][j-k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i-k >= 0 && j+k < 8) {
                    if (board[i-k][j+k]->empty) {
                        coups.push_back({i-k,j+k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i-k][j+k]->couleur == 'N') {
                        coups.push_back({i-k,j+k});
                        if (board[i-k][j+k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i-k][j+k]->couleur == 'B') {
                        coups.push_back({i-k,j+k});
                        if (board[i-k][j+k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i-k >= 0 && j-k >= 0) {
                    if (board[i-k][j-k]->empty) {
                        coups.push_back({i-k,j-k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i-k][j-k]->couleur == 'N') {
                        coups.push_back({i-k,j-k});
                        if (board[i-k][j-k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i-k][j-k]->couleur == 'B') {
                        coups.push_back({i-k,j-k});
                        if (board[i-k][j-k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i+k < 8) {
                    if (board[i+k][j]->empty) {
                        coups.push_back({i+k,j});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i+k][j]->couleur == 'N') {
                        coups.push_back({i+k,j});
                        if (board[i+k][j]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i+k][j]->couleur == 'B') {
                        coups.push_back({i+k,j});
                        if (board[i+k][j]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (j+k < 8) {
                    if (board[i][j+k]->empty) {
                        coups.push_back({i,j+k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i][j+k]->couleur == 'N') {
                        coups.push_back({i,j+k});
                        if (board[i][j+k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i][j+k]->couleur == 'B') {
                        coups.push_back({i,j+k});
                        if (board[i][j+k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (i-k >= 0) {
                    if (board[i-k][j]->empty) {
                        coups.push_back({i-k,j});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i-k][j]->couleur == 'N') {
                        coups.push_back({i-k,j});
                        if (board[i-k][j]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i-k][j]->couleur == 'B') {
                        coups.push_back({i-k,j});
                        if (board[i-k][j]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            for (int k = 1; k < 8; ++k) {
                if (j-k >= 0) {
                    if (board[i][j-k]->empty) {
                        coups.push_back({i,j-k});
                    }
                    else if (board[i][j]->couleur == 'B' && board[i][j-k]->couleur == 'N') {
                        coups.push_back({i,j-k});
                        if (board[i][j-k]->symbole == 'r') {
                            *echec = true;
                        }
                        break;
                    }
                    else if (board[i][j]->couleur == 'N' && board[i][j-k]->couleur == 'B') {
                        coups.push_back({i,j-k});
                        if (board[i][j-k]->symbole == 'R') {
                            *echec = true;
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        return coups;
    }
};

int ligne(char lettre) {
    return lettre - 'a';
};

int main() {
    chessboard partie;
    partie.affichage();
    char tour = 'B';
    for (int k = 0; k < 10; ++k) {
        *partie.echec = false;
        cout << "Entre ton coup (case de départ-case d'arrivée) : ";
        string coup;
        cin >> coup;
        int i1 = ligne(coup[0]);
        int j1 = coup[1] - '1';
        if (partie.board[i1][j1]->couleur != tour || partie.board[i1][j1]->empty) {
            cout << "Coup invalide, réessaye" << endl;
            continue;
        }
        int i2 = ligne(coup[3]);
        int j2 = coup[4] - '1';
        vector<pair<int,int>> coups = partie.coups_possibles(i1,j1);
        bool coupValide = false;
        for (const auto& p : coups) {
            if (p.first == i2 && p.second == j2) {
                coupValide = true;
                break;
            }
        }
        if (coupValide) {
            char symbole1 = partie.board[i1][j1]->symbole;
            char symbole2 = partie.board[i2][j2]->symbole;
            partie.changement(i1,j1,i2,j2);
            partie.echec_ou_pas(tour);
            if (*partie.echec) {
                cout << "Coup invalide, réessaye" << endl;
                partie.retour(symbole1,i1,j1,symbole2,i2,j2);
                continue;
            }
            else {
                if (i1 == 0 && j1 == 0) {
                    *partie.grand_rock_blanc_possible = false;
                }
                else if (i1 == 7 && j1 == 0) {
                    *partie.petit_rock_blanc_possible = false;
                }
                else if (i1 == 0 && j1 == 7) {
                    *partie.grand_rock_noir_possible = false;
                }
                else if (i1 == 7 && j1 == 7) {
                    *partie.petit_rock_noir_possible = false;
                }
                if (symbole1 == 'R') {
                    *partie.petit_rock_blanc_possible = false;
                    *partie.grand_rock_blanc_possible = false;
                    if (i2 == i1 + 2) {
                        partie.changement(7,0,5,0);
                    }
                    else if (i2 == i1 - 2) {
                        partie.changement(0,0,3,0);
                    }
                }
                if (symbole1 == 'r') {
                    *partie.petit_rock_noir_possible = false;
                    *partie.grand_rock_noir_possible = false;
                    if (i2 == i1 + 2) {
                        partie.changement(7,7,5,7);
                    }
                    else if (i2 == i1 - 2) {
                        partie.changement(0,7,3,7);
                    }
                }
                partie.affichage();
                if (tour == 'B') {
                    tour = 'N';
                }
                else {
                    tour = 'B';
                }
            }
        }
        else {
            cout << "Coup invalide, réessaye" << endl;
            continue;
        }
    }
    return 0;
};