"tic-tac-toe"
" MEHON Samuel BCS1"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
 
#define N 3
#define TIME_LIMIT 5
 
char grille[N][N];
 
void initialiser() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grille[i][j] = ' ';
}
 
void afficher() {
    clear();
    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            mvprintw(l * 2, c * 4, "[%c]", grille[l][c]);
        }
    }
    refresh();
}
 
int victoire(char s) {
    for (int i = 0; i < N; i++) {
        if ((grille[i][0] == s && grille[i][1] == s && grille[i][2] == s) ||
            (grille[0][i] == s && grille[1][i] == s && grille[2][i] == s))
            return 1;
    }
    if ((grille[0][0] == s && grille[1][1] == s && grille[2][2] == s) ||
        (grille[0][2] == s && grille[1][1] == s && grille[2][0] == s))
        return 1;
    return 0;
}
 
int est_plein() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (grille[i][j] == ' ') return 0;
    return 1;
}
 
int coup_temps(char joueur) {
    int touche = -1;
    time_t debut = time(NULL);
 
    while (time(NULL) - debut < TIME_LIMIT) {
        afficher();
        usleep(500000);
        timeout(0);
        touche = getch();
        if (touche != ERR) return touche;
    }
 
    return -1;
}
 
int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    srand(time(NULL));
 
    initialiser();
    char joueur = 'X';
 
    while (1) {
        int input = coup_temps(joueur);
 
        if (input == -1) break;
 
        if (input >= '1' && input <= '9') {
            int pos = input - '1';
            int l = pos / N;
            int c = pos % N;
 
            if (grille[l][c] == ' ') {
                grille[l][c] = joueur;
 
                if (victoire(joueur)) {
                    afficher();
                    getch();
                    break;
                }
 
                if (est_plein()) {
                    afficher();
                    getch();
                    break;
                }
 
                joueur = (joueur == 'X') ? 'O' : 'X';
            }
        }
    }
 
    endwin();
    return 0;
}
