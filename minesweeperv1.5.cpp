#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

using namespace std;
//righe-colonne-bombe impostate alla difficoltà esperto ufficiale
#define N 16 //righe
#define M 30 //colonne
#define B 99 //bombe
int i, j;
int br = B; //bombe rimanenti
int campo[N][M]; //matrice campo soluzione
int gioco[N][M]; //matrice campo gioco, -1 = celle da giocare(□), 0 = (-), 1/8 = n° bombe
int checkQueue[N][M]; //controllo per la coda
int partita; //finchè può giocare vale 0, se vince 2, se perde 1
int bp = B; //bombe piazzate dall'utente
int primacasella = 1; //1-è la prima giocata 0-giocate successive

 //Colori
#ifdef __linux__
#define Nero "\u001b[30m"					//CaselleDaGiocare
#define Rosso "\u001b[38;5;196m"				//Bombe
#define Verde "\u001b[38;5;2m"					//1
#define Blu "\u001b[38;5;21m"					//2
#define Fucsia "\u001b[38;5;200m"				//3
#define Azzurro "\u001b[38;5;33m"				//4
#define Arancione "\u001b[38;5;202m"				//5
#define Bordeaux "\u001b[38;5;88m"				//6
#define Violetto "\u001b[38;5;93m"				//7
#define Giallo "\u001b[38;5;226m"				//8
#define Verdino "\u001b[38;5;190m"				//PuntiDomanda
 //Sfondi
#define SfondoGrigio "\u001b[48;5;248m"				//SfondoCampo
//Stili
#define Evidenziato "\u001b[7m"
#define Sottolineato "\u001b[4m"
#define Grassetto "\u001b[1m"
 //Reset
#define Reset "\u001b[0m"
void visualizzaCampo() {

	//stampa numeri sopra
	printf("\n   ");
	for (j = 0;j < M;j++)
		printf(Evidenziato " %2i" Reset, j + 1);
	printf(Evidenziato"  \n" Reset);
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf(Evidenziato "\n%2i" Reset " ", i + 1) : printf(Evidenziato "\n%i" Reset " ", i + 1);
		for (j = 0;j<M;j++) {
			if (campo[i][j] == -1) {
				printf(SfondoGrigio Rosso "  *" Reset);
			}
			else if (campo[i][j] == 0) {
				printf(SfondoGrigio "   " Reset);
			}
			else {
				switch (campo[i][j]) {
				case 1: {
					printf(SfondoGrigio Verde "  %i" Reset, campo[i][j]);
					break;
				}
				case 2: {
					printf(SfondoGrigio Blu "  %i" Reset, campo[i][j]);
					break;
				}
				case 3: {
					printf(SfondoGrigio Fucsia "  %i" Reset, campo[i][j]);
					break;
				}
				case 4: {
					printf(SfondoGrigio Azzurro "  %i" Reset, campo[i][j]);
					break;
				}
				case 5: {
					printf(SfondoGrigio Arancione "  %i" Reset, campo[i][j]);
					break;
				}
				case 6: {
					printf(SfondoGrigio Bordeaux "  %i" Reset, campo[i][j]);
					break;
				}
				case 7: {
					printf(SfondoGrigio Violetto "  %i" Reset, campo[i][j]);
					break;
				}
				default: {
					printf(SfondoGrigio Giallo "  %i" Reset, campo[i][j]);
					break;
				}
				}
			}
		}
		printf(SfondoGrigio "  " Reset);
	}
}
void visualizzaGioco() {

	//stampa numeri sopra
	printf("\t\n   ");
	for (j = 0;j < M;j++)
		printf(Evidenziato " %2i" Reset, j + 1);
	printf(Evidenziato "  " Reset);
	printf(Sottolineato Evidenziato Grassetto Rosso "\t\t\t   Bombe Rimanenti: %i   \n" Reset, bp);
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf(Evidenziato "\t\n%2i" Reset " ", i + 1) : printf(Evidenziato "\t\n%i" Reset " ", i + 1);
		for (j = 0;j<M;j++) {
			if (gioco[i][j] == -1) {
				printf(Nero SfondoGrigio "  □" Reset);
			}
			else if (gioco[i][j] == -2) {
				printf(SfondoGrigio Rosso "  ?" Reset);
			}
			else if (gioco[i][j] == 0) {
				printf(SfondoGrigio "   " Reset);
			}
			else {
				switch (gioco[i][j]) {
				case 1: {
					printf(SfondoGrigio Verde "  %i" Reset, gioco[i][j]);
					break;
				}
				case 2: {
					printf(SfondoGrigio Blu "  %i" Reset, gioco[i][j]);
					break;
				}
				case 3: {
					printf(SfondoGrigio Fucsia "  %i" Reset, gioco[i][j]);
					break;
				}
				case 4: {
					printf(SfondoGrigio Azzurro "  %i" Reset, gioco[i][j]);
					break;
				}
				case 5: {
					printf(SfondoGrigio Arancione "  %i" Reset, gioco[i][j]);
					break;
				}
				case 6: {
					printf(SfondoGrigio Bordeaux "  %i" Reset, gioco[i][j]);
					break;
				}
				case 7: {
					printf(SfondoGrigio Violetto "  %i" Reset, gioco[i][j]);
					break;
				}
				default: {
					printf(SfondoGrigio Giallo "  %i" Reset, gioco[i][j]);
					break;
				}
				}
			}
		}
		printf(SfondoGrigio "  " Reset);
	}
}

#elif __APPLE__
#define Nero "\x1B[30m"
#define Rosso "\x1B[38;5;196m"					//Bombe
#define Verde "\x1B[38;5;2m"					//1
#define Blu "\x1B[38;5;21m"						//2
#define Fucsia "\x1B[38;5;200m"					//3
#define Azzurro "\x1B[38;5;33m"					//4
#define Arancione "\x1B[38;5;202m"				//5
#define Bordeaux "\x1B[38;5;88m"				//6
#define Violetto "\x1B[38;5;93m"				//7
#define Giallo "\x1B[38;5;226m"					//8
#define Verdino "\x1B[38;5;190m"				//PuntiDomanda
					  //Sfondi
#define SfondoGrigio "\x1B[48;5;248m"			//SfondoCampo
					  //Stili
#define Evidenziato "\x1B[7m"
#define Sottolineato "\x1B[4m"
#define Grassetto "\x1B[1m"
					  //Reset
#define Reset "\x1B[0m"
void visualizzaCampo() {

	//stampa numeri sopra
	printf("\n   ");
	for (j = 0;j < M;j++)
		printf(Evidenziato " %2i" Reset, j + 1);
	printf(Evidenziato"  \n" Reset);
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf(Evidenziato "\n%2i" Reset " ", i + 1) : printf(Evidenziato "\n%i" Reset " ", i + 1);
		for (j = 0;j<M;j++) {
			if (campo[i][j] == -1) {
				printf(SfondoGrigio Rosso "  *" Reset);
			}
			else if (campo[i][j] == 0) {
				printf(SfondoGrigio "   " Reset);
			}
			else {
				switch (campo[i][j]) {
				case 1: {
					printf(SfondoGrigio Verde "  %i" Reset, campo[i][j]);
					break;
				}
				case 2: {
					printf(SfondoGrigio Blu "  %i" Reset, campo[i][j]);
					break;
				}
				case 3: {
					printf(SfondoGrigio Fucsia "  %i" Reset, campo[i][j]);
					break;
				}
				case 4: {
					printf(SfondoGrigio Azzurro "  %i" Reset, campo[i][j]);
					break;
				}
				case 5: {
					printf(SfondoGrigio Arancione "  %i" Reset, campo[i][j]);
					break;
				}
				case 6: {
					printf(SfondoGrigio Bordeaux "  %i" Reset, campo[i][j]);
					break;
				}
				case 7: {
					printf(SfondoGrigio Violetto "  %i" Reset, campo[i][j]);
					break;
				}
				default: {
					printf(SfondoGrigio Giallo "  %i" Reset, campo[i][j]);
					break;
				}
				}
			}
		}
		printf(SfondoGrigio "  " Reset);
	}
}
void visualizzaGioco() {

	//stampa numeri sopra
	printf("\t\n   ");
	for (j = 0;j < M;j++)
		printf(Evidenziato " %2i" Reset, j + 1);
	printf(Evidenziato "  " Reset);
	printf(Sottolineato Evidenziato Grassetto Rosso "\t\t\t   Bombe Rimanenti: %i   \n" Reset, bp);
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf(Evidenziato "\t\n%2i" Reset " ", i + 1) : printf(Evidenziato "\t\n%i" Reset " ", i + 1);
		for (j = 0;j<M;j++) {
			if (gioco[i][j] == -1) {
				printf(Nero SfondoGrigio "  □" Reset);
			}
			else if (gioco[i][j] == -2) {
				printf(SfondoGrigio Rosso "  ?" Reset);
			}
			else if (gioco[i][j] == 0) {
				printf(SfondoGrigio "   " Reset);
			}
			else {
				switch (gioco[i][j]) {
				case 1: {
					printf(SfondoGrigio Verde "  %i" Reset, gioco[i][j]);
					break;
				}
				case 2: {
					printf(SfondoGrigio Blu "  %i" Reset, gioco[i][j]);
					break;
				}
				case 3: {
					printf(SfondoGrigio Fucsia "  %i" Reset, gioco[i][j]);
					break;
				}
				case 4: {
					printf(SfondoGrigio Azzurro "  %i" Reset, gioco[i][j]);
					break;
				}
				case 5: {
					printf(SfondoGrigio Arancione "  %i" Reset, gioco[i][j]);
					break;
				}
				case 6: {
					printf(SfondoGrigio Bordeaux "  %i" Reset, gioco[i][j]);
					break;
				}
				case 7: {
					printf(SfondoGrigio Violetto "  %i" Reset, gioco[i][j]);
					break;
				}
				default: {
					printf(SfondoGrigio Giallo "  %i" Reset, gioco[i][j]);
					break;
				}
				}
			}
		}
		printf(SfondoGrigio "  " Reset);
	}
}

#elif WIN32
void visualizzaCampo() {

	HANDLE hConsoleColor;

	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

	//stampa numeri sopra
	printf("\n   ");
	for (j = 0;j < M;j++)
		printf(" %2i", j + 1);
	printf("  \n");
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf("\n%2i ", i + 1) : printf("\n%i ", i + 1);
		for (j = 0;j<M;j++) {
			if (campo[i][j] == -1) {
				SetConsoleTextAttribute(hConsoleColor, 12);
				printf("  *");
				SetConsoleTextAttribute(hConsoleColor, 7);
			}
			else if (campo[i][j] == 0) {
				printf("   ");
			}
			else {
				switch (campo[i][j]) {
				case 1: {
					SetConsoleTextAttribute(hConsoleColor, 10);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 2: {
					SetConsoleTextAttribute(hConsoleColor, 9);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 3: {
					SetConsoleTextAttribute(hConsoleColor, 13);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 4: {
					SetConsoleTextAttribute(hConsoleColor, 11);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 5: {
					SetConsoleTextAttribute(hConsoleColor, 14);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 6: {
					SetConsoleTextAttribute(hConsoleColor, 8);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 7: {
					SetConsoleTextAttribute(hConsoleColor, 6);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				default: {
					SetConsoleTextAttribute(hConsoleColor, 15);
					printf("  %i", campo[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				}
			}
		}
	}
}
void visualizzaGioco() {

	HANDLE hConsoleColor;

	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

	//stampa numeri sopra
	printf("\t\n   ");
	for (j = 0;j < M;j++)
		printf(" %2i", j + 1);
	printf("  ");
	SetConsoleTextAttribute(hConsoleColor, 12);
	printf("\t\t\t   Bombe Rimanenti: %i   \n", bp);
	SetConsoleTextAttribute(hConsoleColor, 7);
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf("\t\n%2i ", i + 1) : printf("\t\n%i ", i + 1);
		for (j = 0;j<M;j++) {
			if (gioco[i][j] == -1) {
				printf("  %c", 254);
			}
			else if (gioco[i][j] == -2) {
				SetConsoleTextAttribute(hConsoleColor, 12);
				printf("  ?");
				SetConsoleTextAttribute(hConsoleColor, 7);
			}
			else if (gioco[i][j] == 0) {
				printf("   ");
			}
			else {
				switch (gioco[i][j]) {
				case 1: {
					SetConsoleTextAttribute(hConsoleColor, 10);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 2: {
					SetConsoleTextAttribute(hConsoleColor, 9);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 3: {
					SetConsoleTextAttribute(hConsoleColor, 13);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 4: {
					SetConsoleTextAttribute(hConsoleColor, 11);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 5: {
					SetConsoleTextAttribute(hConsoleColor, 14);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 6: {
					SetConsoleTextAttribute(hConsoleColor, 8);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				case 7: {
					SetConsoleTextAttribute(hConsoleColor, 6);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				default: {
					SetConsoleTextAttribute(hConsoleColor, 15);
					printf("  %i", gioco[i][j]);
					SetConsoleTextAttribute(hConsoleColor, 7);
					break;
				}
				}
			}
		}
	}
}
#endif 

void sistemaGioco() {

	for (i = 0;i<N;i++) {
		for (j = 0;j<M;j++) {
			gioco[i][j]--;
		}
	}
}

void piazzaMine() {

	srand(time(NULL));
	int x, y;

	while (br != 0) {
		x = rand() % N;
		y = rand() % M;
		if (campo[x][y] != -1) {
			campo[x][y] = -1;
			br--;
		}
	}

}

void piazzaNumeri() {

	for (i = 0;i<N;i++) {
		for (j = 0;j<M;j++) {
			if (i == 0 && j == 0) { //alto sx
				if (campo[i][j] != -1) {
					if (campo[i + 1][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j] == -1) campo[i][j]++;
					if (campo[i][j + 1] == -1) campo[i][j]++;
				}
			}
			else if (i == 0 && j == M - 1) { //alto dx
				if (campo[i][j] != -1) {
					if (campo[i + 1][j] == -1) campo[i][j]++;
					if (campo[i][j - 1] == -1) campo[i][j]++;
					if (campo[i + 1][j - 1] == -1) campo[i][j]++;
				}
			}
			else if (i == N - 1 && j == M - 1) { //basso dx
				if (campo[i][j] != -1) {
					if (campo[i - 1][j] == -1) campo[i][j]++;
					if (campo[i - 1][j - 1] == -1) campo[i][j]++;
					if (campo[i][j - 1] == -1) campo[i][j]++;
				}
			}
			else if (i == N - 1 && j == 0) { //basso sx
				if (campo[i][j] != -1) {
					if (campo[i - 1][j] == -1) campo[i][j]++;
					if (campo[i - 1][j + 1] == -1) campo[i][j]++;
					if (campo[i][j + 1] == -1) campo[i][j]++;
				}
			}
			else if (i == 0) { //prima riga
				if (campo[i][j] != -1) {
					if (campo[i][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j] == -1) campo[i][j]++;
					if (campo[i + 1][j - 1] == -1) campo[i][j]++;
					if (campo[i][j - 1] == -1) campo[i][j]++;
				}
			}
			else if (j == M - 1) { //ultima colonna
				if (campo[i][j] != -1) {
					if (campo[i - 1][j - 1] == -1) campo[i][j]++;
					if (campo[i - 1][j] == -1) campo[i][j]++;
					if (campo[i + 1][j] == -1) campo[i][j]++;
					if (campo[i + 1][j - 1] == -1) campo[i][j]++;
					if (campo[i][j - 1] == -1) campo[i][j]++;
				}
			}
			else if (i == N - 1) { //ultima riga
				if (campo[i][j] != -1) {
					if (campo[i - 1][j - 1] == -1) campo[i][j]++;
					if (campo[i - 1][j] == -1) campo[i][j]++;
					if (campo[i - 1][j + 1] == -1) campo[i][j]++;
					if (campo[i][j + 1] == -1) campo[i][j]++;
					if (campo[i][j - 1] == -1) campo[i][j]++;
				}
			}
			else if (j == 0) { //prima colonna
				if (campo[i][j] != -1) {
					if (campo[i - 1][j] == -1) campo[i][j]++;
					if (campo[i - 1][j + 1] == -1) campo[i][j]++;
					if (campo[i][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j] == -1) campo[i][j]++;
				}
			}
			else {
				if (campo[i][j] != -1) {
					if (campo[i - 1][j - 1] == -1) campo[i][j]++;
					if (campo[i - 1][j] == -1) campo[i][j]++;
					if (campo[i - 1][j + 1] == -1) campo[i][j]++;
					if (campo[i][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j + 1] == -1) campo[i][j]++;
					if (campo[i + 1][j] == -1) campo[i][j]++;
					if (campo[i + 1][j - 1] == -1) campo[i][j]++;
					if (campo[i][j - 1] == -1) campo[i][j]++;
				}
			}
		}
	}
}

//debug
void visualizzaCheck() {
	for (i = 0;i<N;i++) {
		printf("\n");
		for (j = 0;j<M;j++) {
			if (checkQueue[i][j] == -1) {
				printf(" *");
			}
			else {
				printf(" %i", checkQueue[i][j]);
			}
		}
	}
}
//debug
void giocoNoStyle() {
	for (i = 0;i<N;i++) {
		printf("\n");
		for (j = 0;j<M;j++) {
			if (gioco[i][j] == -1) {
				printf(" *");
			}
			else {
				printf(" %i", gioco[i][j]);
			}
		}
	}
}

int checkVittoria() {

	int k = 0;

	for (i = 0;i<N;i++) {
		for (j = 0;j<M;j++) {
			if (checkQueue[i][j] == 0) k++;
		}
	}

	if (k == B) {
		printf("\n\nComplimenti!! Hai vinto!!\n\n");
		return(2);
	}
	else {
		return(0);
	}

}

void liberaZeri(int a, int b) { //a=riga, b=colonna
	queue <int> q1; //coda righe
	queue <int> q2; //coda colonne

	q1.push(a);
	q2.push(b);

	while (!q1.empty()) {
		//if!=0&&!=-1 --> visualizza su gioco[][]
		//if==0 --> if not in checkQueue --> metti in queue

		i = q1.front();
		q1.pop();
		j = q2.front();
		q2.pop();
		if (campo[i][j] == 0) {
			checkQueue[i][j]++;
			gioco[i][j] = 0;
		}

		if (i == 0 && j == 0) { //alto sx
			if (campo[i + 1][j + 1] >= 0 && checkQueue[i + 1][j + 1] == 0 && gioco[i + 1][j + 1] != -2) {
				checkQueue[i + 1][j + 1]++;
				gioco[i + 1][j + 1] = campo[i + 1][j + 1];
				if (campo[i + 1][j + 1] == 0) {
					q1.push(i + 1);
					q2.push(j + 1);
				}
			}

			//if (campo[i+1][j]==0) campo[i][j]++;
			if (campo[i + 1][j] >= 0 && checkQueue[i + 1][j] == 0 && gioco[i + 1][j] != -2) {
				checkQueue[i + 1][j]++;
				gioco[i + 1][j] = campo[i + 1][j];
				if (campo[i + 1][j] == 0) {
					q1.push(i + 1);
					q2.push(j);
				}
			}
			//if (campo[i][j+1]==0) campo[i][j]++;
			if (campo[i][j + 1] >= 0 && checkQueue[i][j + 1] == 0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j + 1]++;
				gioco[i][j + 1] = campo[i][j + 1];
				if (campo[i][j + 1] == 0) {
					q1.push(i);
					q2.push(j + 1);
				}
			}
		}
		else if (i == 0 && j == M - 1) { //alto dx
										 //if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i + 1][j] >= 0 && checkQueue[i + 1][j] == 0 && gioco[i + 1][j] != -2) {
				checkQueue[i + 1][j]++;
				gioco[i + 1][j] = campo[i + 1][j];
				if (campo[i + 1][j] == 0) {
					q1.push(i + 1);
					q2.push(j);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j - 1] >= 0 && checkQueue[i][j - 1] == 0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j - 1]++;
				gioco[i][j - 1] = campo[i][j - 1];
				if (campo[i][j - 1] == 0) {
					q1.push(i);
					q2.push(j - 1);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i + 1][j - 1] >= 0 && checkQueue[i + 1][j - 1] == 0 && gioco[i + 1][j - 1] != -2) {
				checkQueue[i + 1][j - 1]++;
				gioco[i + 1][j - 1] = campo[i + 1][j - 1];
				if (campo[i + 1][j - 1] == 0) {
					q1.push(i + 1);
					q2.push(j - 1);
				}
			}
		}
		else if (i == N - 1 && j == M - 1) { //basso dx
											 //if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i - 1][j] >= 0 && checkQueue[i - 1][j] == 0 && gioco[i - 1][j] != -2) {
				checkQueue[i - 1][j]++;
				gioco[i - 1][j] = campo[i - 1][j];
				if (campo[i - 1][j] == 0) {
					q1.push(i - 1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i - 1][j - 1] >= 0 && checkQueue[i - 1][j - 1] == 0 && gioco[i - 1][j - 1] != -2) {
				checkQueue[i - 1][j - 1]++;
				gioco[i - 1][j - 1] = campo[i - 1][j - 1];
				if (campo[i - 1][j - 1] == 0) {
					q1.push(i - 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j - 1] >= 0 && checkQueue[i][j - 1] == 0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j - 1]++;
				gioco[i][j - 1] = campo[i][j - 1];
				if (campo[i][j - 1] == 0) {
					q1.push(i);
					q2.push(j - 1);
				}
			}
		}
		else if (i == N - 1 && j == 0) { //basso sx
										 //if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i - 1][j] >= 0 && checkQueue[i - 1][j] == 0 && gioco[i - 1][j] != -2) {
				checkQueue[i - 1][j]++;
				gioco[i - 1][j] = campo[i - 1][j];
				if (campo[i - 1][j] == 0) {
					q1.push(i - 1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i - 1][j + 1] >= 0 && checkQueue[i - 1][j + 1] == 0 && gioco[i - 1][j + 1] != -2) {
				checkQueue[i - 1][j + 1]++;
				gioco[i - 1][j + 1] = campo[i - 1][j + 1];
				if (campo[i - 1][j + 1] == 0) {
					q1.push(i - 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j + 1] >= 0 && checkQueue[i][j + 1] == 0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j + 1]++;
				gioco[i][j + 1] = campo[i][j + 1];
				if (campo[i][j + 1] == 0) {
					q1.push(i);
					q2.push(j + 1);
				}
			}
		}
		else if (i == 0) { //prima riga
						   //if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j + 1] >= 0 && checkQueue[i][j + 1] == 0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j + 1]++;
				gioco[i][j + 1] = campo[i][j + 1];
				if (campo[i][j + 1] == 0) {
					q1.push(i);
					q2.push(j + 1);
				}
			}
			//if (campo[i+1][j+1]==-1) campo[i][j]++;
			if (campo[i + 1][j + 1] >= 0 && checkQueue[i + 1][j + 1] == 0 && gioco[i + 1][j + 1] != -2) {
				checkQueue[i + 1][j + 1]++;
				gioco[i + 1][j + 1] = campo[i + 1][j + 1];
				if (campo[i + 1][j + 1] == 0) {
					q1.push(i + 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i + 1][j] >= 0 && checkQueue[i + 1][j] == 0 && gioco[i + 1][j] != -2) {
				checkQueue[i + 1][j]++;
				gioco[i + 1][j] = campo[i + 1][j];
				if (campo[i + 1][j] == 0) {
					q1.push(i + 1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i + 1][j - 1] >= 0 && checkQueue[i + 1][j - 1] == 0 && gioco[i + 1][j - 1] != -2) {
				checkQueue[i + 1][j - 1]++;
				gioco[i + 1][j - 1] = campo[i + 1][j - 1];
				if (campo[i + 1][j - 1] == 0) {
					q1.push(i + 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j - 1] >= 0 && checkQueue[i][j - 1] == 0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j - 1]++;
				gioco[i][j - 1] = campo[i][j - 1];
				if (campo[i][j - 1] == 0) {
					q1.push(i);
					q2.push(j - 1);
				}
			}
		}
		else if (j == M - 1) { //ultima colonna
							   //if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i - 1][j - 1] >= 0 && checkQueue[i - 1][j - 1] == 0 && gioco[i - 1][j - 1] != -2) {
				checkQueue[i - 1][j - 1]++;
				gioco[i - 1][j - 1] = campo[i - 1][j - 1];
				if (campo[i - 1][j - 1] == 0) {
					q1.push(i - 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i - 1][j] >= 0 && checkQueue[i - 1][j] == 0 && gioco[i - 1][j] != -2) {
				checkQueue[i - 1][j]++;
				gioco[i - 1][j] = campo[i - 1][j];
				if (campo[i - 1][j] == 0) {
					q1.push(i - 1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i + 1][j] >= 0 && checkQueue[i + 1][j] == 0 && gioco[i + 1][j] != -2) {
				checkQueue[i + 1][j]++;
				gioco[i + 1][j] = campo[i + 1][j];
				if (campo[i + 1][j] == 0) {
					q1.push(i + 1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i + 1][j - 1] >= 0 && checkQueue[i + 1][j - 1] == 0 && gioco[i + 1][j - 1] != -2) {
				checkQueue[i + 1][j - 1]++;
				gioco[i + 1][j - 1] = campo[i + 1][j - 1];
				if (campo[i + 1][j - 1] == 0) {
					q1.push(i + 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j - 1] >= 0 && checkQueue[i][j - 1] == 0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j - 1]++;
				gioco[i][j - 1] = campo[i][j - 1];
				if (campo[i][j - 1] == 0) {
					q1.push(i);
					q2.push(j - 1);
				}
			}
		}
		else if (i == N - 1) { //ultima riga
							   //if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i - 1][j - 1] >= 0 && checkQueue[i - 1][j - 1] == 0 && gioco[i - 1][j - 1] != -2) {
				checkQueue[i - 1][j - 1]++;
				gioco[i - 1][j - 1] = campo[i - 1][j - 1];
				if (campo[i - 1][j - 1] == 0) {
					q1.push(i - 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i - 1][j] >= 0 && checkQueue[i - 1][j] == 0 && gioco[i - 1][j] != -2) {
				checkQueue[i - 1][j]++;
				gioco[i - 1][j] = campo[i - 1][j];
				if (campo[i - 1][j] == 0) {
					q1.push(i - 1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i - 1][j + 1] >= 0 && checkQueue[i - 1][j + 1] == 0 && gioco[i - 1][j + 1] != -2) {
				checkQueue[i - 1][j + 1]++;
				gioco[i - 1][j + 1] = campo[i - 1][j + 1];
				if (campo[i - 1][j + 1] == 0) {
					q1.push(i - 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j + 1] >= 0 && checkQueue[i][j + 1] == 0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j + 1]++;
				gioco[i][j + 1] = campo[i][j + 1];
				if (campo[i][j + 1] == 0) {
					q1.push(i);
					q2.push(j + 1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j - 1] >= 0 && checkQueue[i][j - 1] == 0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j - 1]++;
				gioco[i][j - 1] = campo[i][j - 1];
				if (campo[i][j - 1] == 0) {
					q1.push(i);
					q2.push(j - 1);
				}
			}
		}
		else if (j == 0) { //prima colonna
						   //if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i - 1][j] >= 0 && checkQueue[i - 1][j] == 0 && gioco[i - 1][j] != -2) {
				checkQueue[i - 1][j]++;
				gioco[i - 1][j] = campo[i - 1][j];
				if (campo[i - 1][j] == 0) {
					q1.push(i - 1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i - 1][j + 1] >= 0 && checkQueue[i - 1][j + 1] == 0 && gioco[i - 1][j + 1] != -2) {
				checkQueue[i - 1][j + 1]++;
				gioco[i - 1][j + 1] = campo[i - 1][j + 1];
				if (campo[i - 1][j + 1] == 0) {
					q1.push(i - 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j + 1] >= 0 && checkQueue[i][j + 1] == 0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j + 1]++;
				gioco[i][j + 1] = campo[i][j + 1];
				if (campo[i][j + 1] == 0) {
					q1.push(i);
					q2.push(j + 1);
				}
			}
			//if (campo[i+1][j+1]==-1) campo[i][j]++;
			if (campo[i + 1][j + 1] >= 0 && checkQueue[i + 1][j + 1] == 0 && gioco[i + 1][j + 1] != -2) {
				checkQueue[i + 1][j + 1]++;
				gioco[i + 1][j + 1] = campo[i + 1][j + 1];
				if (campo[i + 1][j + 1] == 0) {
					q1.push(i + 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i + 1][j] >= 0 && checkQueue[i + 1][j] == 0 && gioco[i + 1][j] != -2) {
				checkQueue[i + 1][j]++;
				gioco[i + 1][j] = campo[i + 1][j];
				if (campo[i + 1][j] == 0) {
					q1.push(i + 1);
					q2.push(j);
				}
			}
		}
		else {
			//if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i - 1][j - 1] >= 0 && checkQueue[i - 1][j - 1] == 0 && gioco[i - 1][j - 1] != -2) {
				checkQueue[i - 1][j - 1]++;
				gioco[i - 1][j - 1] = campo[i - 1][j - 1];
				if (campo[i - 1][j - 1] == 0) {
					q1.push(i - 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i - 1][j] >= 0 && checkQueue[i - 1][j] == 0 && gioco[i - 1][j] != -2) {
				checkQueue[i - 1][j]++;
				gioco[i - 1][j] = campo[i - 1][j];
				if (campo[i - 1][j] == 0) {
					q1.push(i - 1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i - 1][j + 1] >= 0 && checkQueue[i - 1][j + 1] == 0 && gioco[i - 1][j + 1] != -2) {
				checkQueue[i - 1][j + 1]++;
				gioco[i - 1][j + 1] = campo[i - 1][j + 1];
				if (campo[i - 1][j + 1] == 0) {
					q1.push(i - 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j + 1] >= 0 && checkQueue[i][j + 1] == 0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j + 1]++;
				gioco[i][j + 1] = campo[i][j + 1];
				if (campo[i][j + 1] == 0) {
					q1.push(i);
					q2.push(j + 1);
				}
			}
			//if (campo[i+1][j+1]==-1) campo[i][j]++;
			if (campo[i + 1][j + 1] >= 0 && checkQueue[i + 1][j + 1] == 0 && gioco[i + 1][j + 1] != -2) {
				checkQueue[i + 1][j + 1]++;
				gioco[i + 1][j + 1] = campo[i + 1][j + 1];
				if (campo[i + 1][j + 1] == 0) {
					q1.push(i + 1);
					q2.push(j + 1);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i + 1][j] >= 0 && checkQueue[i + 1][j] == 0 && gioco[i + 1][j] != -2) {
				checkQueue[i + 1][j]++;
				gioco[i + 1][j] = campo[i + 1][j];
				if (campo[i + 1][j] == 0) {
					q1.push(i + 1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i + 1][j - 1] >= 0 && checkQueue[i + 1][j - 1] == 0 && gioco[i + 1][j - 1] != -2) {
				checkQueue[i + 1][j - 1]++;
				gioco[i + 1][j - 1] = campo[i + 1][j - 1];
				if (campo[i + 1][j - 1] == 0) {
					q1.push(i + 1);
					q2.push(j - 1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j - 1] >= 0 && checkQueue[i][j - 1] == 0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j - 1]++;
				gioco[i][j - 1] = campo[i][j - 1];
				if (campo[i][j - 1] == 0) {
					q1.push(i);
					q2.push(j - 1);
				}
			}

		}

	}

}

void liberaCasella(int r, int c) {

	switch (campo[r - 1][c - 1])
	{
	case 0: {
		//posto vuoto
		liberaZeri(r - 1, c - 1);
		break;
	}
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8: {
		gioco[r - 1][c - 1] = campo[r - 1][c - 1];
		checkQueue[r - 1][c - 1]++;
		break;
	}
	default: {
		printf("\n\n Hai perso! Bomba colpita in posizione [%i,%i]\n", r, c);
		visualizzaCampo();
		partita = 1;
		break;
	}
	}
}

int giocata(int r, int c) {

	liberaCasella(r, c);

	if (campo[r - 1][c - 1] != -1) return(0);
	else return(1);
}

int liberaNumero(int r, int c) {

	//col primo if contollo la posizione
	//col secondo controllo che quella casella non sia stata marcata come bomba dall'utente
	//come parametri passo i valori effettivi dato che poi in liberaCasella ho il -1 di defualt, nel controllo faccio a mano il -1 del valore
	if ((r - 1) == 0 && (c - 1) == 0) { //alto sx
		if (gioco[r - 1][c] == -1) liberaCasella(r, c + 1);
		if (gioco[r][c] == -1) liberaCasella(r + 1, c + 1);
		if (gioco[r][c - 1] == -1) liberaCasella(r + 1, c);
	}
	else if ((r - 1) == 0 && (c - 1) == M - 1) { //alto dx
		if (gioco[r - 1][c - 2] == -1) liberaCasella(r, c - 1);
		if (gioco[r][c - 2] == -1) liberaCasella(r + 1, c - 1);
		if (gioco[r][c - 1] == -1) liberaCasella(r + 1, c);
	}
	else if ((r - 1 == N - 1) && (c - 1) == M - 1) { //basso dx
		if (gioco[r - 2][c - 1] == -1) liberaCasella(r - 1, c);
		if (gioco[r - 2][c - 2] == -1) liberaCasella(r - 1, c - 1);
		if (gioco[r - 1][c - 2] == -1) liberaCasella(r, c - 1);
	}
	else if ((r - 1) == N - 1 && (c - 1) == 0) { //basso sx
		if (gioco[r - 1][c] == -1) liberaCasella(r, c + 1);
		if (gioco[r - 2][c] == -1) liberaCasella(r - 1, c + 1);
		if (gioco[r - 2][c - 1] == -1) liberaCasella(r - 1, c);
	}
	else if (r - 1 == 0) { //prima riga
		if (gioco[r - 1][c - 2] == -1) liberaCasella(r, c - 1);
		if (gioco[r - 1][c] == -1) liberaCasella(r, c + 1);
		if (gioco[r][c - 2] == -1) liberaCasella(r + 1, c - 1);
		if (gioco[r][c - 1] == -1) liberaCasella(r + 1, c);
		if (gioco[r][c] == -1) liberaCasella(r + 1, c + 1);
	}
	else if (c - 1 == M - 1) {//ultima colonna
		if (gioco[r - 2][c - 1] == -1) liberaCasella(r - 1, c);
		if (gioco[r - 2][c - 2] == -1) liberaCasella(r - 1, c - 1);
		if (gioco[r - 1][c - 2] == -1) liberaCasella(r, c - 1);
		if (gioco[r][c - 2] == -1) liberaCasella(r + 1, c - 1);
		if (gioco[r][c - 1] == -1) liberaCasella(r + 1, c);
	}
	else if (r - 1 == N - 1) { //ultima riga
		if (gioco[r - 1][c - 2] == -1) liberaCasella(r, c - 1);
		if (gioco[r - 2][c - 2] == -1) liberaCasella(r - 1, c - 1);
		if (gioco[r - 2][c - 1] == -1) liberaCasella(r - 1, c);
		if (gioco[r - 2][c] == -1) liberaCasella(r - 1, c + 1);
		if (gioco[r - 1][c] == -1) liberaCasella(r, c + 1);
	}
	else if (c - 1 == 0) { //prima colonna
		if (gioco[r - 2][c - 1] == -1) liberaCasella(r - 1, c);
		if (gioco[r - 2][c] == -1) liberaCasella(r - 1, c + 1);
		if (gioco[r - 1][c] == -1) liberaCasella(r, c + 1);
		if (gioco[r][c] == -1) liberaCasella(r + 1, c + 1);
		if (gioco[r][c - 1] == -1) liberaCasella(r + 1, c);
	}
	else { //blocchi centrali
		if (gioco[r - 1][c - 2] == -1) liberaCasella(r, c - 1);
		if (gioco[r - 2][c - 2] == -1) liberaCasella(r - 1, c - 1);
		if (gioco[r - 2][c - 1] == -1) liberaCasella(r - 1, c);
		if (gioco[r - 2][c] == -1) liberaCasella(r - 1, c + 1);
		if (gioco[r - 1][c] == -1) liberaCasella(r, c + 1);
		if (gioco[r][c] == -1) liberaCasella(r + 1, c + 1);
		if (gioco[r][c - 1] == -1) liberaCasella(r + 1, c);
		if (gioco[r][c - 2] == -1) liberaCasella(r + 1, c - 1);
	}

	return(partita);
}

void reset() {

	for (i = 0;i<N;i++) {
		for (j = 0;j<M;j++) {
			gioco[i][j] = 0;
			campo[i][j] = 0;
			checkQueue[i][j] = 0;
		}
	}
	br = B;
	bp = B;
	partita = 0;
	primacasella = 1;
}

void mossa() {
	int r, c;
	int bg = 0; //casella-1	liberanumero-2	piazzabomba-3	rimuovibomba-4
	int numeroreset = 0;	//info

	if (primacasella == 1) {
		do {
			printf("\n\nInserisci Riga,Colonna:\t");
			scanf("%i,%i", &r, &c);
		} while ((((r - 1) < 0) || ((r - 1) >= N)) && ((c - 1) < 0 || (c - 1) >= M));
	}
	else {
		do {
			printf("\n\nInserisci la terna di valori di gioco: Casella(0)\\LiberaNumero(1)\\PiazzaBomba(2)\\RimuoviBomba(3),Riga,Colonna:\t");
			scanf("%i,%i,%i", &bg, &r, &c);
		} while ((bg != 0 || bg != 1 || bg != 2 || bg != 3) && ((r - 1) < 0 || (r - 1) >= N) && ((c - 1) < 0 || (c - 1) >= M));
	}
	while (primacasella == 1 && campo[r - 1][c - 1] != 0) {
		//visualizzaCampo();		//debug
		reset();
		piazzaMine();
		piazzaNumeri();
		sistemaGioco();
		//numeroreset++;		//info
	}
	//printf("\n\nNumero reset:\t%i\n", numeroreset);
	primacasella = 0;

	switch (bg) {
	case 0: {
		//controllo che la casella non sia stata segnata come bomba
		//altrimenti restarto la richiesta della mossa
		if (gioco[r - 1][c - 1] != -2) partita = giocata(r, c);
		else mossa();
		break;
	}
	case 1: {
		//controllo che la casella non sia stata segnata come bomba
		if (gioco[r - 1][c - 1] != -2) partita = liberaNumero(r, c);
		else mossa();
		break;
	}
	case 2: {
		gioco[r - 1][c - 1] = -2;
		bp--;
		break;
	}
	case 3: {
		gioco[r - 1][c - 1] = -1;
		bp++;
		break;
	}
	}
}

int main() {
	char giocare;

	do {

		reset();					//pulisce partita precedente
		piazzaMine();				//piazza mine casualmente
		piazzaNumeri();				//sistema i numeri in base alle mine adiacenti
		sistemaGioco();				//sistemo il campo a -1 per la visualizzazione

		printf("\n\n");

		do {

			//printf("\nCHECK");	//debug
			//visualizzaCheck();	//debug	
			//printf("\nCampo");	//debug
			//visualizzaCampo();	//debug
			//printf("\nGioco");	//debug
			//giocoNoStyle();		//debug
			//printf("\n\n");		//debug

			visualizzaGioco();
			mossa();

			if (partita == 0) {
				partita = checkVittoria();
			}
		} while ((partita != 1) && (partita != 2));

		do {
			printf("\nVuoi fare un'altra partita\nScegli: s/n\t");
			scanf(" %c", &giocare);
		} while (!(giocare == 's' || giocare == 'S' || giocare == 'n' || giocare == 'N'));
	} while (giocare == 's' || giocare == 'S');

	return(0);
}

//► □
