#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <iostream>

int i,j;

using namespace std;
//righe-colonne-bombe impostate alla difficoltà esperto ufficiale
#define N 16 //righe
#define M 30 //colonne
#define B 99 //bombe
int br=B; //bombe rimanenti
int campo[N][M]; //matrice campo soluzione
int gioco[N][M]; //matrice campo gioco, -1 = celle da giocare(□), 0 = (-), 1/8 = n° bombe
int checkQueue[N][M]; //controllo per la coda
int partita; //finchè può giocare vale 0, se vince 2, se perde 1
int bp = B; //bombe piazzate dall'utente
int primacasella = 1; //1-è la prima giocata 0-giocate successive

void sistemaGioco() {

	for (i=0;i<N;i++) {
		for (j=0;j<M;j++) {
			gioco[i][j]--;
		}
	}
}

void piazzaMine() {

	srand(time(NULL));
	int x,y;

	while (br!=0) {
		x=rand()%N;
		y=rand()%M;
		if (campo[x][y]!=-1) {
			campo[x][y]=-1;
			br--;
		}
	}

}

void piazzaNumeri() {

	for (i=0;i<N;i++) {
		for (j=0;j<M;j++) {
			if (i==0 && j==0) { //alto sx
				if (campo[i][j]!=-1) {
					if (campo[i+1][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j]==-1) campo[i][j]++;
					if (campo[i][j+1]==-1) campo[i][j]++;
				}
			} else if (i==0 && j==M-1) { //alto dx
				if (campo[i][j]!=-1) {
					if (campo[i+1][j]==-1) campo[i][j]++;
					if (campo[i][j-1]==-1) campo[i][j]++;
					if (campo[i+1][j-1]==-1) campo[i][j]++;
				}
			} else if (i==N-1 && j==M-1) { //basso dx
				if (campo[i][j]!=-1) {
					if (campo[i-1][j]==-1) campo[i][j]++;
					if (campo[i-1][j-1]==-1) campo[i][j]++;
					if (campo[i][j-1]==-1) campo[i][j]++;
				}
			} else if (i==N-1 && j==0) { //basso sx
				if (campo[i][j]!=-1) {
					if (campo[i-1][j]==-1) campo[i][j]++;
					if (campo[i-1][j+1]==-1) campo[i][j]++;
					if (campo[i][j+1]==-1) campo[i][j]++;
				}
			} else if (i==0) { //prima riga
				if (campo[i][j]!=-1) {
					if (campo[i][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j]==-1) campo[i][j]++;
					if (campo[i+1][j-1]==-1) campo[i][j]++;
					if (campo[i][j-1]==-1) campo[i][j]++;
				}
			} else if (j==M-1) { //ultima colonna
				if (campo[i][j]!=-1) {
					if (campo[i-1][j-1]==-1) campo[i][j]++;
					if (campo[i-1][j]==-1) campo[i][j]++;
					if (campo[i+1][j]==-1) campo[i][j]++;
					if (campo[i+1][j-1]==-1) campo[i][j]++;
					if (campo[i][j-1]==-1) campo[i][j]++;
				}
			} else if (i==N-1) { //ultima riga
				if (campo[i][j]!=-1) {
					if (campo[i-1][j-1]==-1) campo[i][j]++;
					if (campo[i-1][j]==-1) campo[i][j]++;
					if (campo[i-1][j+1]==-1) campo[i][j]++;
					if (campo[i][j+1]==-1) campo[i][j]++;
					if (campo[i][j-1]==-1) campo[i][j]++;
				}
			} else if (j==0) { //prima colonna
				if (campo[i][j]!=-1) {
					if (campo[i-1][j]==-1) campo[i][j]++;
					if (campo[i-1][j+1]==-1) campo[i][j]++;
					if (campo[i][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j]==-1) campo[i][j]++;
				}
			} else {
				if (campo[i][j]!=-1) {
					if (campo[i-1][j-1]==-1) campo[i][j]++;
					if (campo[i-1][j]==-1) campo[i][j]++;
					if (campo[i-1][j+1]==-1) campo[i][j]++;
					if (campo[i][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j+1]==-1) campo[i][j]++;
					if (campo[i+1][j]==-1) campo[i][j]++;
					if (campo[i+1][j-1]==-1) campo[i][j]++;
					if (campo[i][j-1]==-1) campo[i][j]++;
				}
			}
		}
	}
}

void visualizzaCampo() {
	
	//stampa numeri sopra
	printf("\n   ");
	for (j = 0;j < M;j++)
		printf(" %2i", j + 1);
	printf("\n");
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf("\n%i  ", i + 1) : printf("\n%i ", i + 1);
		for (j = 0;j<M;j++) {
			if (campo[i][j] == -1) {
				printf("  *");
			}
			else if (campo[i][j] == 0) {
				printf("   ");
			}
			else {
				printf("  %i", campo[i][j]);
			}
		}
	}
}
//debug
void visualizzaCheck() {
	for (i=0;i<N;i++) {
		printf("\n");
		for (j=0;j<M;j++) {
			if (checkQueue[i][j]==-1) {
				printf(" *");
			} else {
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

void visualizzaGioco() {
	
	//stampa numeri sopra
	printf("\t\n   ");
	for (j = 0;j < M;j++)
		printf(" %2i", j + 1);
	printf("\t\t\t\tBombe Rimanenti: %i\n", bp);
	//stampa numero riga-campo
	for (i = 0;i<N;i++) {
		((i + 1) < 10) ? printf("\t\n%i  ", i + 1) : printf("\t\n%i ", i + 1);
		for (j = 0;j<M;j++) {
			if (gioco[i][j] == -1) {
				printf("  □");
			}
			else if (gioco[i][j] == -2) {
				printf("  ?");
			}
			else if (gioco[i][j] == 0) {
				printf("   ");
			}
			else {
				printf("  %i", gioco[i][j]);
			}
		}
	}
}

int checkVittoria() {

	int k=0;

	for (i=0;i<N;i++) {
		for (j=0;j<M;j++) {
			if (checkQueue[i][j]==0) k++;
		}
	}

	if (k==B) {
		printf("\n\nComplimenti!! Hai vinto!!\n\n");
		return(2);
	} else {
		return(0);
	}

}

void liberaZeri(int a, int b) { //a=riga, b=colonna
	queue <int> q1; //coda righe
	queue <int> q2; //coda colonne

	q1.push(a);
	q2.push(b);

	while(!q1.empty()) {
		//if!=0&&!=-1 --> visualizza su gioco[][]
		//if==0 --> if not in checkQueue --> metti in queue

		i=q1.front();
		q1.pop();
		j=q2.front();
		q2.pop();
		if (campo[i][j] == 0) {
			checkQueue[i][j]++;
			gioco[i][j] = 0;
		}

		if (i==0 && j==0) { //alto sx
			if (campo[i+1][j+1]>=0 && checkQueue[i+1][j+1]==0 && gioco[i+1][j+1] != -2) {
				checkQueue[i+1][j+1]++;
				gioco[i+1][j+1]=campo[i+1][j+1];
				if (campo[i+1][j+1]==0) {
					q1.push(i+1);
					q2.push(j+1);
				}
			}
			
			//if (campo[i+1][j]==0) campo[i][j]++;
			if (campo[i+1][j]>=0 && checkQueue[i+1][j]==0 && gioco[i+1][j] != -2) {
				checkQueue[i+1][j]++;
				gioco[i+1][j]=campo[i+1][j];
				if (campo[i+1][j]==0) {
					q1.push(i+1);
					q2.push(j);
				}
			}
			//if (campo[i][j+1]==0) campo[i][j]++;
			if (campo[i][j+1]>=0 && checkQueue[i][j+1]==0 && gioco[i][j+1] != -2) {
				checkQueue[i][j+1]++;
				gioco[i][j+1]=campo[i][j+1];
				if (campo[i][j+1]==0) {
					q1.push(i);
					q2.push(j+1);
				}
			}
		} else if (i==0 && j==M-1) { //alto dx
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i+1][j]>=0 && checkQueue[i+1][j]==0 && gioco[i+1][j] != -2) {
				checkQueue[i+1][j]++;
				gioco[i+1][j]=campo[i+1][j];
				if (campo[i+1][j]==0) {
					q1.push(i+1);
					q2.push(j);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j-1]>=0 && checkQueue[i][j-1]==0 && gioco[i][j-1] != -2) {
				checkQueue[i][j-1]++;
				gioco[i][j-1]=campo[i][j-1];
				if (campo[i][j-1]==0) {
					q1.push(i);
					q2.push(j-1);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i+1][j-1]>=0 && checkQueue[i+1][j-1]==0 && gioco[i+1][j-1] != -2) {
				checkQueue[i+1][j-1]++;
				gioco[i+1][j-1]=campo[i+1][j-1];
				if (campo[i+1][j-1]==0) {
					q1.push(i+1);
					q2.push(j-1);
				}
			}
		} else if (i==N-1 && j==M-1) { //basso dx
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i-1][j]>=0 && checkQueue[i-1][j]==0 && gioco[i-1][j] != -2) {
				checkQueue[i-1][j]++;
				gioco[i-1][j]=campo[i-1][j];
				if (campo[i-1][j]==0) {
					q1.push(i-1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i-1][j-1]>=0 && checkQueue[i-1][j-1]==0 && gioco[i-1][j-1] != -2) {
				checkQueue[i-1][j-1]++;
				gioco[i-1][j-1]=campo[i-1][j-1];
				if (campo[i-1][j-1]==0) {
					q1.push(i-1);
					q2.push(j-1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j-1]>=0 && checkQueue[i][j-1]==0 && gioco[i][j-1] != -2) {
				checkQueue[i][j-1]++;
				gioco[i][j-1]=campo[i][j-1];
				if (campo[i][j-1]==0) {
					q1.push(i);
					q2.push(j-1);
				}
			}
		} else if (i==N-1 && j==0) { //basso sx
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i-1][j]>=0 && checkQueue[i-1][j]==0 && gioco[i-1][j] != -2) {
				checkQueue[i-1][j]++;
				gioco[i-1][j]=campo[i-1][j];
				if (campo[i-1][j]==0) {
					q1.push(i-1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i-1][j+1]>=0 && checkQueue[i-1][j+1]==0 && gioco[i-1][j+1] != -2) {
				checkQueue[i-1][j+1]++;
				gioco[i-1][j+1]=campo[i-1][j+1];
				if (campo[i-1][j+1]==0) {
					q1.push(i-1);
					q2.push(j+1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j+1]>=0 && checkQueue[i][j+1]==0 && gioco[i][j+1] != -2) {
				checkQueue[i][j+1]++;
				gioco[i][j+1]=campo[i][j+1];
				if (campo[i][j+1]==0) {
					q1.push(i);
					q2.push(j+1);
				}
			}
		} else if (i==0) { //prima riga
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j+1]>=0 && checkQueue[i][j+1]==0 && gioco[i][j+1] != -2) {
				checkQueue[i][j+1]++;
				gioco[i][j+1]=campo[i][j+1];
				if (campo[i][j+1]==0) {
					q1.push(i);
					q2.push(j+1);
				}
			}
			//if (campo[i+1][j+1]==-1) campo[i][j]++;
			if (campo[i+1][j+1]>=0 && checkQueue[i+1][j+1]==0 && gioco[i+1][j+1] != -2) {
				checkQueue[i+1][j+1]++;
				gioco[i+1][j+1]=campo[i+1][j+1];
				if (campo[i+1][j+1]==0) {
					q1.push(i+1);
					q2.push(j+1);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i+1][j]>=0 && checkQueue[i+1][j]==0 && gioco[i+1][j] != -2) {
				checkQueue[i+1][j]++;
				gioco[i+1][j]=campo[i+1][j];
				if (campo[i+1][j]==0) {
					q1.push(i+1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i+1][j-1]>=0 && checkQueue[i+1][j-1]==0 && gioco[i+1][j-1] != -2) {
				checkQueue[i+1][j-1]++;
				gioco[i+1][j-1]=campo[i+1][j-1];
				if (campo[i+1][j-1]==0) {
					q1.push(i+1);
					q2.push(j-1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j-1]>=0 && checkQueue[i][j-1]==0 && gioco[i][j-1] != -2) {
				checkQueue[i][j-1]++;
				gioco[i][j-1]=campo[i][j-1];
				if (campo[i][j-1]==0) {
					q1.push(i);
					q2.push(j-1);
				}
			}
		} else if (j==M-1) { //ultima colonna
			//if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i-1][j-1]>=0 && checkQueue[i-1][j-1]==0 && gioco[i-1][j-1] != -2) {
				checkQueue[i-1][j-1]++;
				gioco[i-1][j-1]=campo[i-1][j-1];
				if (campo[i-1][j-1]==0) {
					q1.push(i-1);
					q2.push(j-1);
				}
			}
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i-1][j]>=0 && checkQueue[i-1][j]==0 && gioco[i-1][j] != -2) {
				checkQueue[i-1][j]++;
				gioco[i-1][j]=campo[i-1][j];
				if (campo[i-1][j]==0) {
					q1.push(i-1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i+1][j]>=0 && checkQueue[i+1][j]==0 && gioco[i+1][j] != -2) {
				checkQueue[i+1][j]++;
				gioco[i+1][j]=campo[i+1][j];
				if (campo[i+1][j]==0) {
					q1.push(i+1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i+1][j-1]>=0 && checkQueue[i+1][j-1]==0 && gioco[i+1][j-1] != -2) {
				checkQueue[i+1][j-1]++;
				gioco[i+1][j-1]=campo[i+1][j-1];
				if (campo[i+1][j-1]==0) {
					q1.push(i+1);
					q2.push(j-1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j-1]>=0 && checkQueue[i][j-1]==0 && gioco[i][j-1] != -2) {
				checkQueue[i][j-1]++;
				gioco[i][j-1]=campo[i][j-1];
				if (campo[i][j-1]==0) {
					q1.push(i);
					q2.push(j-1);
				}
			}
		} else if (i==N-1) { //ultima riga
			//if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i-1][j-1]>=0 && checkQueue[i-1][j-1]==0 && gioco[i-1][j-1] != -2) {
				checkQueue[i-1][j-1]++;
				gioco[i-1][j-1]=campo[i-1][j-1];
				if (campo[i-1][j-1]==0) {
					q1.push(i-1);
					q2.push(j-1);
				}
			}
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i-1][j]>=0 && checkQueue[i-1][j]==0 && gioco[i-1][j] != -2) {
				checkQueue[i-1][j]++;
				gioco[i-1][j]=campo[i-1][j];
				if (campo[i-1][j]==0) {
					q1.push(i-1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i-1][j+1]>=0 && checkQueue[i-1][j+1]==0 && gioco[i-1][j+1] != -2) {
				checkQueue[i-1][j+1]++;
				gioco[i-1][j+1]=campo[i-1][j+1];
				if (campo[i-1][j+1]==0) {
					q1.push(i-1);
					q2.push(j+1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j+1]>=0 && checkQueue[i][j+1]==0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j+1]++;
				gioco[i][j+1]=campo[i][j+1];
				if (campo[i][j+1]==0) {
					q1.push(i);
					q2.push(j+1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j-1]>=0 && checkQueue[i][j-1]==0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j-1]++;
				gioco[i][j-1]=campo[i][j-1];
				if (campo[i][j-1]==0) {
					q1.push(i);
					q2.push(j-1);
				}
			}
		} else if (j==0) { //prima colonna
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i-1][j]>=0 && checkQueue[i-1][j]==0 && gioco[i - 1][j] != -2) {
				checkQueue[i-1][j]++;
				gioco[i-1][j]=campo[i-1][j];
				if (campo[i-1][j]==0) {
					q1.push(i-1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i-1][j+1]>=0 && checkQueue[i-1][j+1]==0 && gioco[i - 1][j + 1] != -2) {
				checkQueue[i-1][j+1]++;
				gioco[i-1][j+1]=campo[i-1][j+1];
				if (campo[i-1][j+1]==0) {
					q1.push(i-1);
					q2.push(j+1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j+1]>=0 && checkQueue[i][j+1]==0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j+1]++;
				gioco[i][j+1]=campo[i][j+1];
				if (campo[i][j+1]==0) {
					q1.push(i);
					q2.push(j+1);
				}
			}
			//if (campo[i+1][j+1]==-1) campo[i][j]++;
			if (campo[i+1][j+1]>=0 && checkQueue[i+1][j+1]==0 && gioco[i + 1][j + 1] != -2) {
				checkQueue[i+1][j+1]++;
				gioco[i+1][j+1]=campo[i+1][j+1];
				if (campo[i+1][j+1]==0) {
					q1.push(i+1);
					q2.push(j+1);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i+1][j]>=0 && checkQueue[i+1][j]==0 && gioco[i + 1][j] != -2) {
				checkQueue[i+1][j]++;
				gioco[i+1][j]=campo[i+1][j];
				if (campo[i+1][j]==0) {
					q1.push(i+1);
					q2.push(j);
				}
			}
		} else {
			//if (campo[i-1][j-1]==-1) campo[i][j]++;
			if (campo[i-1][j-1]>=0 && checkQueue[i-1][j-1]==0 && gioco[i - 1][j - 1] != -2) {
				checkQueue[i-1][j-1]++;
				gioco[i-1][j-1]=campo[i-1][j-1];
				if (campo[i-1][j-1]==0) {
					q1.push(i-1);
					q2.push(j-1);
				}
			}
			//if (campo[i-1][j]==-1) campo[i][j]++;
			if (campo[i-1][j]>=0 && checkQueue[i-1][j]==0 && gioco[i - 1][j] != -2) {
				checkQueue[i-1][j]++;
				gioco[i-1][j]=campo[i-1][j];
				if (campo[i-1][j]==0) {
					q1.push(i-1);
					q2.push(j);
				}
			}
			//if (campo[i-1][j+1]==-1) campo[i][j]++;
			if (campo[i-1][j+1]>=0 && checkQueue[i-1][j+1]==0 && gioco[i - 1][j + 1] != -2) {
				checkQueue[i-1][j+1]++;
				gioco[i-1][j+1]=campo[i-1][j+1];
				if (campo[i-1][j+1]==0) {
					q1.push(i-1);
					q2.push(j+1);
				}
			}
			//if (campo[i][j+1]==-1) campo[i][j]++;
			if (campo[i][j+1]>=0 && checkQueue[i][j+1]==0 && gioco[i][j + 1] != -2) {
				checkQueue[i][j+1]++;
				gioco[i][j+1]=campo[i][j+1];
				if (campo[i][j+1]==0) {
					q1.push(i);
					q2.push(j+1);
				}
			}
			//if (campo[i+1][j+1]==-1) campo[i][j]++;
			if (campo[i+1][j+1]>=0 && checkQueue[i+1][j+1]==0 && gioco[i + 1][j + 1] != -2) {
				checkQueue[i+1][j+1]++;
				gioco[i+1][j+1]=campo[i+1][j+1];
				if (campo[i+1][j+1]==0) {
					q1.push(i+1);
					q2.push(j+1);
				}
			}
			//if (campo[i+1][j]==-1) campo[i][j]++;
			if (campo[i+1][j]>=0 && checkQueue[i+1][j]==0 && gioco[i + 1][j] != -2) {
				checkQueue[i+1][j]++;
				gioco[i+1][j]=campo[i+1][j];
				if (campo[i+1][j]==0) {
					q1.push(i+1);
					q2.push(j);
				}
			}
			//if (campo[i+1][j-1]==-1) campo[i][j]++;
			if (campo[i+1][j-1]>=0 && checkQueue[i+1][j-1]==0 && gioco[i + 1][j - 1] != -2) {
				checkQueue[i+1][j-1]++;
				gioco[i+1][j-1]=campo[i+1][j-1];
				if (campo[i+1][j-1]==0) {
					q1.push(i+1);
					q2.push(j-1);
				}
			}
			//if (campo[i][j-1]==-1) campo[i][j]++;
			if (campo[i][j-1]>=0 && checkQueue[i][j-1]==0 && gioco[i][j - 1] != -2) {
				checkQueue[i][j-1]++;
				gioco[i][j-1]=campo[i][j-1];
				if (campo[i][j-1]==0) {
					q1.push(i);
					q2.push(j-1);
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
			printf("\n Hai perso! Bomba colpita in posizione [%i,%i]", r, c);
			visualizzaCampo();
			partita = 1;
			break;
		}
	}
}

int giocata(int r, int c) {

	liberaCasella(r, c);

	if (campo[r-1][c-1] != -1) return(0);
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
		} while (((r - 1) < 0 || (r - 1) >= N) && ((c - 1) < 0 || (c - 1) >= M));
	}
	else {
		do {
			printf("\n\nInserisci la terna di valori di gioco: Casella(0)\\LiberaNumero(1)\\PiazzaBomba(2)\\RimuoviBomba(3),Riga,Colonna:\t");
			scanf("%i,%i,%i", &bg, &r, &c);
		} while ((bg != 0 || bg != 1 || bg != 2 || bg != 3) && ((r - 1) < 0 || (r - 1) >= N) && ((c - 1) < 0 || (c - 1) >= M));
	}
	while(primacasella == 1 && campo[r-1][c-1] != 0) {
		//visualizzaCampo();		//debug
		reset();
		piazzaMine();
		piazzaNumeri();
		sistemaGioco();
		//numeroreset++;		//info
	}
	//printf("\n%i\n", numeroreset);
	primacasella = 0;
	
	switch (bg) {
	case 0: {
		//controllo che la casella non sia stata segnata come bomba
		//altrimenti restarto la richiesta della mossa
		if (gioco[r-1][c-1] != -2) partita = giocata(r, c);
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

			if (partita==0) {
				partita=checkVittoria();
			}
		} while ((partita != 1) && (partita!= 2));

		do {
			printf("\nVuoi fare un'altra partita\nScegli: s/n\t");
			scanf(" %c", &giocare);
		} while (!(giocare == 's' || giocare == 'S' || giocare == 'n' || giocare == 'N'));
	} while (giocare == 's' || giocare == 'S');

	return(0);
}

//► □