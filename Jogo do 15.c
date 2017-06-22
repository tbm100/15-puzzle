/*		ELE103: JOGO DOS 15

	Gabriel Rogerio Ferraz Albino	2017010300
	Rafael Seije Okamoto			2017012234
	Thais Rezende da Silva			2017009524
	Thiago Batista de Mira			2017017670

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estrutura para salvar a pontuação dos jogadores;
	typedef struct player{
		char name[50];
		int moves;
	}Player;

//Protótipo das Funções:
void newGame();//Cria uma Matriz para jogar;
int *create(void);//Aloca memória para o array que será a matriz do jogo e atribui os valores de 0 a 15 à ela;
void random(int *array);//Embaralha os elementos da matriz criada;
int puzzleBoss(int *array);//Confere se a Matriz tem Solução;
void loadGame();//Carrega uma Matriz já salva para jogar;
void game(int *array, int count_move);//Roda o jogo;
int move(int *array, int x);//Troca de posição o 0 com o inteiro escolhido pelo usuário na matriz se o movimento for válido;
void print(int *array);//Imprime a matriz;
void saveGame (int *array, int count_move);//Salva o jogo para continuar mais tarde;
void saveScore(int count_move);//Salva o placar do jogador quando ele vence;
void help(void);//Passa as instruções;
void showScore(void);//Mostra a pontuação dos jogadores que já venceram o jogo;
void solveGame(int *array);// Mostra uma dica para ajudar o úsuario resolver o jogo;

//Funções:
int main(void){
	int op;
//Menu:
	do{
		puts("============= M E N U =============");
		printf("\t(1) Novo Jogo\n\t(2) Carregar Jogo\n\t(3) Instrucoes\n\t(4) Mostrar Pontuacoes\n\t(0) Sair\nOpcao: ");
		scanf("%d", &op);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

		switch (op){
			case 1:
				newGame();
				break;
			case 2:
				loadGame();
				break;
			case 3:
				help();
				break;
			case 4:
				showScore();
		}
	} while (op != 0);

	puts("\n\n\n\n\nAperte qualquer tecla para encerrar...");
	getch();
	return 0;
}

void newGame(){
	int *array = create();//Cria a matriz;
	random(array);//Embaralha a matriz;

	return game(array, 0);//Começa o jogo;
}

int *create(void){
	int *a = (int *) malloc (16 * sizeof(int)), i;
	for(i = 0; i < 16; i++){
		a[i] = i;
	}
	return a;
}

void random(int *array){
	int i, temp, r;

	srand(time(NULL));
	do{
		for (i = 0; i < 16; i++){
			r = rand() % 16;

			temp = array[i];
			array[i] = array[r];
			array[r] = temp;
		}
	}while(puzzleBoss(array) == 0);
}

int puzzleBoss(int *array){
	int countInvertions(int *array);

	int invCount = countInvertions(array);
	int line0 = (search(array, 0) / 4);

	if(invCount % 2 == 0 && line0 % 2 != 0 || invCount % 2 != 0 && line0 % 2 == 0){
		return 1;
	}else {
		return 0;
	}
}

int countInvertions(int *array){
	int inv_count = 0, i, j;
    for (i = 0; i < 4 * 4 - 1; i++){
        for (j = i + 1; j < 4 * 4; j++){
            // count pairs(i, j) such that i appears
            // before j, but i > j.
            if (array[j] && array[i] && array[i] > array[j])
                inv_count++;
        }
    }
    return inv_count;
}

void loadGame(){
	FILE *load = fopen("Gameof15.txt", "r");

	if(load != NULL && feof(load) == 0){
		int count_move;
		int array[16];

		fscanf(load, "%d", &count_move);

		int i;
		for(i = 0; i < 16; i++){
				fscanf(load, "%d", &array[i]);
		}

		game (array, count_move);
	}else {
		printf("\tERRO!\n\n\n\n\n\n\n\n\n");
	}
	fclose(load); free(load);
}

void game(int *array, int count_move){
	int mov = -1;

	while ( array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 || array[5] != 6 || array[6] != 7 || array[7] != 8 || array[8] != 9 || array[9] != 10 || array[10] != 11 || array[11] != 12 || array[12] != 13 || array[13] != 14 || array[14] != 15 || array[15] != 0 ){
		printf("Jogadas = %d  Ajuda: 77  Salvar: 88  Sair: 99", count_move);
		print(array);//Mostra a matriz;
		printf("Mover: ");
		scanf("%d", &mov);//Qual peça o jogador quer mover;
		//99 salva o jogo;
		if(mov == 88){
			saveGame(array, count_move);
			continue;
		}
		//999 sai do jogo;
		if(mov == 99){
			break;
		}

		//111 da dica para o usuário;
		if(mov == 77){
			count_move += 30;
			solveGame(array);
			continue;
		}

		//Números inválidos;
		if( mov < 1 || mov > 15){
			printf("\aMovimento Invalido! ");
			continue;
		}
		//Chama a funçõo para mover, se ela retornar -1, o movimento é inválido;
		if (move (array, mov) == -1){
			printf("\aMovimento Invalido! ");
			continue;
		}else{//Se não, a pessa é movida e o contador de jogadas aumenta;
			count_move++;
		}
	}

	if(array[0] == 1 && array[1] == 2 && array[2] == 3 && array[3] == 4 && array[4] == 5 && array[5] == 6 && array[6] == 7 && array[7] == 8 && array[8] == 9 && array[9] == 10 && array[10] == 11 && array[11] == 12 && array[12] == 13 && array[13] == 14 && array[14] == 15 && array[15] == 0 ){
		puts("\n========================== ! ! ! P A R A B E N S ! ! ! =========================\n\n\t\t\t\t VOCE GANHOU!!!\n");
		saveScore(count_move);
	}

	puts("\nAperte qualquer tecla para continuar...");
	getch();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	free(array);
}

void saveGame (int *array, int count_move){
	FILE *save = fopen("GameOf15.txt", "wt");

	if(save != NULL){
		fprintf(save, "%d ", count_move);

		int i;
		for( i = 0; i < 16; i++){
			fprintf(save, "%d ", array[i]);
		}
		printf("Salvo! ");
	}else{
		printf("Falha ao Salvar! ");
	}

	fclose(save);	free(save);
}

void print(int *array){
	int i;
	puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n===== J O G O =====");
	for(i = 0; i < 16; i++){
		if (array[i] < 10) {//Se o número tiver um dígito;
			if(array[i] != 0){
				printf("  %d  ", array[i]);
			}else {
					printf("     ", array[i]);
			}
		} else {//Se o número tiver 2 dígitos;
			printf(" %d  ", array[i]);
		}

		if ( (i + 1) % 4 == 0 ){//Final de linha;
			printf("\n");
		}
	}
	puts("===================\n");
}

int search(int *array, int x){
	int i;
	for(i = 0; i < 16; i++){
		if(array[i] == x){
			break;
		}
	}
	return i;
}

int relativePosition(int a, int b){
	if( a / 4 == b / 4 ){//Pertencem a mesma linha;
		if ( a - b == 1 || b - a == 1 ){//Estão a distancia de 1;
			return 1;
		}else {
			return 0;
		}
	} else if ( a % 4 == b % 4 ){//Pertencem a mesma coluna;
		if ( a - 4  == b || a + 4 == b ){//Estão a distãncia de 1;
			return 1;
		} else{
			return 0;
		}
	}else {//Não estão na mesma linha nem na mesma coluna;
		return 0;
	}
}

int move(int*array, int x){
	int loc0 = search(array, 0), locx = search(array, x), rel = relativePosition(loc0, locx);
		if( rel == 0 ){
		return -1;
	} else {
		int aux = array[loc0];
		array[loc0] = array[locx];
		array[locx] = aux;
		return 0;
	}
}

void saveScore(int count_move){
	int num;
	FILE *scoreR = fopen("Gameof15Score.txt", "rt");

	if(scoreR != NULL){
		Player winner;
		//Leitura dos dados do jogador que acabou de ganhar;
		printf("Nome: ");
		scanf("\n%[^\n]", winner.name);
		winner.moves = count_move;

		fscanf(scoreR, "%d", &num);//Quantas pessoas já tem na lista;
		if(num > 0 && feof(scoreR) == 0){
			int i, j;
			Player *scoreList = (Player *)malloc((num + 1) * sizeof(Player));//Cria um vetor para os vencedores;
			//Leitura do arquivo para o vetor;
			for(i = 0; i < num || feof(scoreR) == 0; i++){
				fscanf(scoreR, "\n%d", &scoreList[i].moves);
				fscanf(scoreR, "\n%[^\n]", scoreList[i].name);
			}
			strcpy(scoreList[num].name, winner.name);
			scoreList[num].moves = winner.moves;

			//Ordenação do vetor;
			for(i = 0; i < num ; i++){
				for(j = i + 1; j <= num; j++){
					Player aux;
					if(scoreList[j].moves < scoreList[i].moves){
						aux.moves = scoreList[i].moves;
						strcpy(aux.name, scoreList[i].name);

						scoreList[i].moves = scoreList[j].moves;
						strcpy(scoreList[i].name, scoreList[j].name);

						scoreList[j].moves = aux.moves;
						strcpy(scoreList[j].name, aux.name);
					}
				}
			}

			//Escreve o Score já organizado, com o novo player no arquivo;
			FILE *scoreW = fopen("Gameof15Score.txt", "wt");
			if(scoreW != NULL){
				if(num >= 10) num = 9;
				fprintf(scoreW, "%d", (num + 1));
				for(i = 0; i <= num; i++){//Para salvar os 10 melhores
					fprintf(scoreW, "\n%d\n%s", scoreList[i].moves, scoreList[i].name);
				}
			}

			fclose(scoreW);	free(scoreW);
			free(scoreList);

		}else if(num == 0 || feof(scoreR) != 0){
			FILE *scoreW = fopen("Gameof15Score.txt", "wt");

			if(scoreW != NULL){
				fprintf(scoreW, "%d\n%d\n%s", 1, winner.moves, winner.name);
			}
			fclose(scoreW);	free(scoreR);
		}

	}else {
		printf("\tERRO!\n\n\n\n\n\n\n\n\n");
	}
	fclose(scoreR);
}

void help(){
	puts("============================= I N S T R U C O E S  =============================");
	printf("1 => Esse jogo consiste basicamente em organizar uma matriz 4x4 que possui os\nalgarismos de 1 a 15 e um espaco vazio. Um exemplo de matriz:\n\n  2    3    1    4  \n  8   10    5    7  \n  6    9   11   12  \n      13    14   15  \n");
	getch();
	printf("\n2 => Para organizar a matriz, deve-se trocar o 0 com algum algarismo vizinho\nseu da matriz na direcao vertical ou horizontal. Na matriz dada de exemplo, o 0 poderia ser trocado com o 6, ou 13 por exemplo.\n");
	printf("\nA Matriz organizada:\n\n  1    2    3    4  \n  5    6    7    8  \n  9   10   11   12  \n 13   14   15       \n");
	getch();
	printf("\n3 => No jogo aparecera a matriz e embaixo dela a opcao Mover. Nesse campo, deve-se digitar o numero que se deseja trocar de posicao com o 0. Lembramos que:\n\t-> Nao pode escolher 0 e nem numeros menores que ele ou maiores que 15;\n\t-> Caso o suario digite um caracter diferente de um numero, o programa\npodera parar de responder;\n");
	getch();
	printf("\n4 => Para receber uma ajuda durante o jogo, digite 77.\nPara salvar um jogo, digite 88.\nPara sair de um jogo, digite 99.\n");
	puts("\nAperte qualquer tecla para continuar...");
	getch();

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void showScore(void){
	FILE *score = fopen("Gameof15Score.txt", "rt");

	if(score != NULL){
	puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n================= P L A C A R =================\n");
		rewind(score);
		int i, n, points;
		char name[50];

		fscanf(score, "%d", &n);
		for(i = 0; i < n; i++){
			fscanf(score,"\n%d", &points);
			fscanf(score,"\n%[^\n]", name);
			printf("%d\nJogador: %s\nJogadas: %d\n\n", i + 1, name, points);
		}
	puts("===============================================");

		puts("\nAperte qualquer tecla para continuar...");
		getch();

		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	}else {
		printf("\tERRO!\n\n\n\n\n\n\n\n\n");
	}
	fclose(score);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------P U Z Z L E  S O L V E R-----------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------------//
void pos(int *array, int *p, int *l,int *c, int n);
void up(int *array, int *p0, int *l0, int *c0);
void down(int *array, int *p0, int *l0, int *c0);
void left(int *array, int *p0, int *l0, int *c0);
void right(int *array, int *p0, int *l0, int *c0);

void solveGame(int *array){
	void solve1(int *array);
	void solve2(int *array);
	void solve3e4(int *array);
	void solve5(int *array);
	void solve6(int *array);
	void solve7e8(int *array);
	void solve9e13(int *array);
	void solve10e14(int *array);
	void solveFinal(int *array);

	if(array[0] != 1)	return solve1(array);

	if(array[1] != 2)	return solve2(array);
	
	if(array[2] != 3 || array[3] != 4)	return solve3e4(array);
		
	if(array[4] != 5)	return solve5(array);

	if(array[8] != 9 || array[12] != 13)	return solve9e13(array);
	
	if(array[5] != 6)	return solve6(array);

	if(array[6] != 7 || array[7] != 8)	return solve7e8(array);

	if(array[9] != 10 || array[13] != 14)	return solve10e14(array);
	
	return solveFinal(array);
}

void solve1(int *array){
	while(array[0] != 1){//Arruma a posição do 1;
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;//Acha as coordenadas do 0;
		int p1 = search(array, 1), l1 = p1 / 4, c1 = p1 % 4;//Acha as coordenadas do 1;
//----------------------------------------------------------------------------//Arruma 1 na coluna;
		while(c1 > 0){//Enquanto o 1 não estiver na Primeira Coluna (0);
			//Joga o 0 na primeira coluna;
			while(c0 > 0){
				left(array, &p0, &l0, &c0);
				pos(array, &p1, &l1, &c1, 1);
			}

			if (l0 < l1){//Quando 0 tiver em linhas a cima do 1;
				while(l0 < l1) down(array, &p0, &l0, &c0);//Joga o 0 pra baixo até ficar na linha do 1;

			}else if (l0 == l1){//Se eles estiverm na mesma linha;
				while(c0 < c1){//Traz o 1 para esquerda uma posição;
					right(array, &p0, &l0, &c0);
					pos(array, &p1, &l1, &c1, 1);
				}
				(l1 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 1;

			}else if(l0 > l1){//Se o 0 estiver abaixo do 1, joga o 0 pra cima até ficar na mesma linha do 1;
				while(l0 > l1) up(array, &p0, &l0, &c0);//Joga o 0 pra cima;
			}
			pos(array, &p1, &l1, &c1, 1);
		}
//--------------------------------------------------------------------//Arruma o 1 na primeira Linha;
		while(l1 > 0){//Enquanto o 1 não estiver na Primeira linha;
			//Joga o 0 na primeira linha;
			while(l0 > 0){
				up(array, &p0, &l0, &c0);
				pos(array, &p1, &l1, &c1, 1);
			}

			while(c0 > 0) left(array, &p0, &l0, &c0);//Joga ele na coluna a cima do 1;

			while(l0 < l1){//Traz o 1 para cima uma posição;
				down(array, &p0, &l0, &c0);
				pos(array, &p1, &l1, &c1, 1);
			}
			right(array, &p0, &l0, &c0);//e joga o 0 pra direita;
		}
	}
}

void solve2(int *array){
	while(array[1] != 2){//Arruma a posição do 2;
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;//Acha as coordenadas do 0;
		int p2 = search(array, 2), l2 = p2 / 4, c2 = p2 % 4;//Acha as coordenadas do 2;
//----------------------------------------------------------------------------//Colocando 2 na coluna certa;
		while(c2 != 1){//Enquanto o 2 não estiver na Segunda Coluna;
			if(c2 == 0){//Se ele estiver na primeira coluna:
				while(c0 < 3) right(array, &p0, &l0, &c0);//Joga o 0 na última coluna;

				//Deixa o 0 na mesma linha que o 2;
				if (l0 < l2){
					while(l0 < l2) down(array, &p0, &l0, &c0);
				}else if(l0 > l2){
					while(l0 > l2) up(array, &p0, &l0, &c0);
				}

				while(c0 > c2){//Traz o 2 para direita uma posição;
					left(array, &p0, &l0, &c0);
					pos(array, &p2, &l2, &c2, 2);
				}

				(l2 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 2

			}else {
				while(c2 > 1){
					//Joga o 0 na coluna 1, e vai com ele até a linha do 2. Depois vai para direita para até fazer o 2 mexer uma posição;
					if(c0 > 1){
						while(c0 > 1) left(array, &p0, &l0, &c0);
					}else right(array, &p0, &l0, &c0);

					//Deixa o 0 na mesma linha que o 2;
					if (l0 < l2){
						while(l0 < l2) down(array, &p0, &l0, &c0);
					}else if(l0 > l2){
						while(l0 > l2) up(array, &p0, &l0, &c0);
					}

					while(c0 < c2){//Traz o 2 para esquerda uma posição;
						right(array, &p0, &l0, &c0);
						pos(array, &p2, &l2, &c2, 2);
					}

					(l2 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 2
					pos(array, &p2, &l2, &c2, 2);
				}
			}
			pos(array, &p2, &l2, &c2, 2);
		}
//--------------------------------------------------------------------//Arrumando 2 na linha certa
		while(l2 > 0){//Enquanto o 2 não estiver na Primeira linha;
			//Joga o 0 na última coluna;
			while(c0 < 3){
				right(array, &p0, &l0, &c0);
				pos(array, &p2, &l2, &c2, 2);
			}

			while(l0 > 0) up(array, &p0, &l0, &c0);//Quando 0 tiver na coluna 3, joga ele pra linha 0;

			while(c0 > c2) left(array, &p0, &l0, &c0);//Quando 0 tiver na linha 0, joga ele pra mesma coluna que o 2;

			while(l0 < l2){//Quando 0 tiver na mesma coluna que o 2, joga ele pra baixo até o 2 subir;
				down(array, &p0, &l0, &c0);
				pos(array, &p2, &l2, &c2, 2);
			}
			pos(array, &p2, &l2, &c2, 2);
		}
	}
}

void solve3e4(int *array){
	while(array[2] != 3 || array[3] != 4){
//------------------------------------------------------------//Arrumando o 4 no lugar do 3;
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;
		int p4 = search(array, 4), l4 = p4 / 4, c4 = p4 % 4;

//---------------------------------------------------//Arrumando o 4 na coluna certa;
		//Deixa o 0 na coluna 2;
		while(c4 != 2){
			if(c0 < 2){
				while(c0 < 2){
					right(array, &p0, &l0, &c0);
					pos(array, &p4, &l4, &c4, 4);
				}
			}else if(c0 > 2){
				left(array, &p0, &l0, &c0);
				pos(array, &p4, &l4, &c4, 4);
			}
			//Deixa o 0 na mesma linha que o 4;
			if (l0 < l4){
				while(l0 < l4) down(array, &p0, &l0, &c0);
			}else if(l0 > l4){
				while(l0 > l4) up(array, &p0, &l0, &c0);
			}
			//Traz o 4 uma posição;
			if(c0 > c4){
				while(c0 > c4){
					left(array, &p0, &l0, &c0);
					pos(array, &p4, &l4, &c4, 4);
				}
			}else{
				right(array, &p0, &l0, &c0);
				pos(array, &p4, &l4, &c4, 4);
			}
			(l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 4;
			pos(array, &p4, &l4, &c4, 4);
		}
//---------------------------------------------------------------------------------//Arruma 4 na linha;
		while(l4 > 0){//Enquanto o 4 não estiver na Primeira linha;
			//Tira o 0 da linha do 4;
			if(l0 == l4) (l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);
			//Joga o 0 na última coluna;
			while(c0 < 3) right(array, &p0, &l0, &c0);

			while(l0 > 0) up(array, &p0, &l0, &c0);//Quando 0 tiver na coluna 3, joga ele pra linha 0;

			while(c0 > c4){//Quando 0 tiver na linha 0, joga ele pra mesma coluna que o 4;
				left(array, &p0, &l0, &c0);
				pos(array, &p4, &l4, &c4, 4);
			}

			while(l0 < l4){//Quando 0 tiver na mesma coluna que o 2, joga ele pra baixo até o 2 subir;
				down(array, &p0, &l0, &c0);
				pos(array, &p4, &l4, &c4, 4);
			}
			pos(array, &p4, &l4, &c4, 4);
		}
//------------------------------------------------------------------------------------------//Arruma o 3 embaixo do 4;
		int p3 = search(array, 3), l3 = p3 / 4, c3 = p3 % 4;
//---------------------------------------------------//Arrumando o 3 na coluna certa;
		if(l3 != 0){
			//Tira o zero da Linha 0;
			if(l0 == 0){
				down(array, &p0, &l0, &c0);
				pos(array, &p3, &l3, &c3, 3);
			}
			//Deixa o 0 na coluna 2;
			while(c3 != 2){
				if(c0 < 2){
					while(c0 < 2){
						right(array, &p0, &l0, &c0);
						pos(array, &p3, &l3, &c3, 3);
					}
				}else if(c0 > 2){
					left(array, &p0, &l0, &c0);
					pos(array, &p3, &l3, &c3, 3);
				}

				//Deixa o 0 na mesma linha que o 3;
				if (l0 < l3){
					while(l0 < l3) down(array, &p0, &l0, &c0);
				}else if(l0 > l3){
					while(l0 > l3) up(array, &p0, &l0, &c0);
				}
				//Traz o 3 uma posição;
				if(c0 > c3){
					while(c0 > c3){
						left(array, &p0, &l0, &c0);
						pos(array, &p3, &l3, &c3, 3);
					}
				}else{
					right(array, &p0, &l0, &c0);
					pos(array, &p3, &l3, &c3, 3);
				}
				(l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 3;
				pos(array, &p3, &l3, &c3, 3);
			}
		}else {
			//Joga o 0 embaixo do 3;
			while(c0 < 3) right(array, &p0, &l0, &c0);
			while(l0 > 1) up(array, &p0, &l0, &c0);
			//Da 2 voltas ;
			up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);
			up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);
			//Tira o 3 do círculo;
			up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);
			//Deixa o 3 em baixo do 4;
			right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
			//Deixa o 4 e o 3 na posição desejada para continuar;
			while(l0 < 3) down(array, &p0, &l0, &c0);
			while(c0 < 3) right(array, &p0, &l0, &c0);
			while(l0 > 0) up(array, &p0, &l0, &c0);
			left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);
			pos(array, &p3, &l3, &c3, 3);
			pos(array, &p4, &l4, &c4, 4);
		}
//----------------------------------------------------------------------------------//Arruma 3 na linha certa;
		while(l3 > 1){//Enquanto o 3 não estiver na Segunda linha;
			//Tira o 0 da linha do 3;
			if(l0 == l3) (l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);
			//Joga o 0 na última coluna;
			while(c0 < 3) right(array, &p0, &l0, &c0);

			while(l0 > 1) up(array, &p0, &l0, &c0);//Quando 0 tiver na coluna 3, joga ele pra linha 1;

			while(c0 > c3) left(array, &p0, &l0, &c0);//Quando 0 tiver na linha 1, joga ele pra mesma coluna que o 3;

			while(l0 < l3){//Quando 0 tiver na mesma coluna que o 2, joga ele pra baixo até o 2 subir;
				down(array, &p0, &l0, &c0);
				pos(array, &p3, &l3, &c3, 3);
			}
		}
//-------------------------------------------------------------------------------//Arruma tudo
		//Joga o zero na -ultima linha e depois naúltima coluna. Depois sobe ele até a primeira linha;
		while(l0 < 3) down(array, &p0, &l0, &c0);
		while(c0 < 3) right(array, &p0, &l0, &c0);
		while(l0 > 0) up(array, &p0, &l0, &c0);
		left(array, &p0, &l0, &c0);
		down(array, &p0, &l0, &c0);
	}
}

void solve5(int *array){
	while(array[4] != 5){//Arruma a posição do 5;
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;//Acha as coordenadas do 0;
		int p5 = search(array, 5), l5 = p5 / 4, c5 = p5 % 4;//Acha as coordenadas do 1;
//----------------------------------------------------------------------------//Arruma 1 na coluna;
		while(c5 > 0){//Enquanto o 5 não estiver na Primeira Coluna (0);
			//Joga o 0 na primeira coluna;
			while(c0 > 0){
				left(array, &p0, &l0, &c0);
				pos(array, &p5, &l5, &c5, 5);
			}

			if (l0 < l5){
				while(l0 < l5) down(array, &p0, &l0, &c0);

			}else if (l0 == l5){//Se eles estiverm na mesma linha;
				while(c0 < c5){//Traz o 5 para esquerda uma posição;
					right(array, &p0, &l0, &c0);
					pos(array, &p5, &l5, &c5, 5);
				}
				(l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);

			}else if(l0 > l5){//Se o 0 estiver abaixo do 5, joga o 0 pra cima até ficar na mesma linha do 5;
				while(l0 > l5) up(array, &p0, &l0, &c0);//Joga o 0 pra cima;
			}
		}
//--------------------------------------------------------------------//Arruma o 1 na primeira Linha;
		while(l5 > 1){//Enquanto o 5 não estiver na Segunda linha;
			//Joga o 0 na Segunda linha;
			while(l0 > 1){
				up(array, &p0, &l0, &c0);
				pos(array, &p5, &l5, &c5, 5);
			}

			while(c0 > 0) left(array, &p0, &l0, &c0);//Joga ele na coluna a cima do 1;

			while(l0 < l5){//Traz o 1 para cima uma posição;
				down(array, &p0, &l0, &c0);
				pos(array, &p5, &l5, &c5, 5);
			}
			right(array, &p0, &l0, &c0);//e joga o 0 pra direita;
		}
	}
}

void solve9e13(int *array){
	while(array[8] != 9 || array[12] != 13){
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;
		int p13 = search(array, 13), l13 = p13 / 4, c13 = p13 % 4;

		if(l13 != 2){//Coloca o 13 na linha 2;
			if(l0 == 1){//0 na linha 2 para mover o 13;
				down(array, &p0, &l0, &c0);
				pos(array, &p13, &l13, &c13, 13);
			} else if(l0 == 3){
				up(array, &p0, &l0, &c0);
				pos(array, &p13, &l13, &c13, 13);
			}

			if(c0 != c13){//Joga o 0 na coluna do 13;
				if(c0 < c13){
					while(c0 < c13){
						right(array, &p0, &l0, &c0);
						pos(array, &p13, &l13, &c13, 13);
					}
				}else if(c0 > c13){
					while(c0 > c13){
						left(array, &p0, &l0, &c0);
						pos(array, &p13, &l13, &c13, 13);
					}
				}
			}
			//Deixa o 13 na linha do dele;
			(l0 > l13) ? up(array, &p0, &l0, &c0) : down(array, &p0, &l0, &c0);//Tira o 0 da linha do 13;
		}
//---------------------------------------------------------Arruma 13 na coluna;
		while(c13 > 0){
            if(c0 == c13) (c0 < 3)? right(array, &p0, &l0, &c0) : left(array, &p0, &l0, &c0);//Tira o zero da coluna do 13;

			while(l0 < 3) down(array, &p0, &l0, &c0);//Tira o zero da linha do 13;

			while(c0 > 0) left(array, &p0, &l0, &c0);//0 na primeira coluna;

			up(array, &p0, &l0, &c0);//Se o 0 estiver abaixo do 13, joga o 0 pra cima até ficar na mesma linha do 13;

			while(c0 < c13){
				right(array, &p0, &l0, &c0);
				pos(array, &p13, &l13, &c13, 13);
			}
		}
//-----------------------------------------------------------------Arruma 9 na linha
		int p9 = search(array, 9), l9 = p9 / 4, c9 = p9 % 4;
		if(c9 > 0){
			if(l9 != 2){//Coloca o 9 na linha 2;
				if(c0 != 1){//Coloca o 0 da coluna 1;
				 	if(c0 == 0) right(array, &p0, &l0, &c0);
					else while(c0 > 1) left(array, &p0, &l0, &c0);
				}

				if(l0 == 1){//0 na linha 2 para mover o 9;
					down(array, &p0, &l0, &c0);
					pos(array, &p9, &l9, &c9, 9);
				} else if(l0 == 3){
					up(array, &p0, &l0, &c0);
					pos(array, &p9, &l9, &c9, 9);
				}

				if(c0 != c9){//Joga o 0 na coluna do 9;
					if(c0 < c9){
						while(c0 < c9){
							right(array, &p0, &l0, &c0);
							pos(array, &p9, &l9, &c9, 9);
						}
					}else if(c0 > c9){
						while(c0 > c9){
							left(array, &p0, &l0, &c0);
							pos(array, &p9, &l9, &c9, 9);
						}
					}
				}
				//Deixa o 9 na linha do dele;
				(l0 > l9) ? up(array, &p0, &l0, &c0) : down(array, &p0, &l0, &c0);//Tira o 0 da linha do 13;
			}
		}else{
			//Deixa o 0 a direita do 9
			while(l0 < 3) down(array, &p0, &l0, &c0);
			while(c0 > 1) left(array, &p0, &l0, &c0);
			//Da duas voltas;
			left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
			left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
			//Tira o 9 do círculo
			left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);
			//Deixa 9 a direita do 13;
			down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);
			//Coloca o 13 na primeira coluna de novo
			right(array, &p0, &l0, &c0);
			while(l0 < 3) down(array, &p0, &l0, &c0);
			while(c0 > 0) left(array, &p0, &l0, &c0);
			up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
		}
//--------------------------------------Arruma coluna do 9
		while(c9 > 1){
			while(c0 > 1){//Chega o 0 na coluna 1;
				left(array, &p0, &l0, &c0);
				pos(array, &p9, &l9, &c9, 9);
			}
			//Deixa ele na mesma linha que o 9;
			if (l0 < l9) down(array, &p0, &l0, &c0);//Quando 0 tiver em linhas a cima do 13, Joga o 0 pra baixo até ficar na linha do 13;
			else if(l0 > l9) up(array, &p0, &l0, &c0);//Se o 0 estiver abaixo do 1, joga o 0 pra cima até ficar na mesma linha do 1;
			// Tras o 9 uma posição;
			while(c0 < c9) right(array, &p0, &l0, &c0);
			down(array, &p0, &l0, &c0);
		}
//---------------------------------------Arruma tuto
		if(c0 == c9) right(array, &p0, &l0, &c0);
		while(l0 < 3) down(array, &p0, &l0, &c0);
		while(c0 > 0) left(array, &p0, &l0, &c0);
		up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);
	}
}

void solve6(int *array){
	while(array[5] != 6){//Arruma a posição do 1;
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;//Acha as coordenadas do 0;
		int p6 = search(array, 6), l6 = p6 / 4, c6 = p6 % 4;//Acha as coordenadas do 1;
//----------------------------------------------------------------------------//Arruma 1 na coluna;
		while(c6 > 1){//Enquanto o 1 não estiver na Segunda Coluna (1);
			//Joga o 0 na segunda coluna;
			while(c0 > 1){
				left(array, &p0, &l0, &c0);
				pos(array, &p6, &l6, &c6, 6);
			}

			if (l0 < l6){//Quando 0 tiver em linhas a cima do 6;
				while(l0 < l6) down(array, &p0, &l0, &c0);//Joga o 0 pra baixo até ficar na linha do 1;

			}else if (l0 == l6){//Se eles estiverm na mesma linha;
				while(c0 < c6){//Traz o 1 para esquerda uma posição;
					right(array, &p0, &l0, &c0);
					pos(array, &p6, &l6, &c6, 6);
				}
				(l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 1;

			}else if(l0 > l6){//Se o 0 estiver abaixo do 6, joga o 0 pra cima até ficar na mesma linha do 1;
				while(l0 > l6) up(array, &p0, &l0, &c0);//Joga o 0 pra cima;
			}
		}
//--------------------------------------------------------------------//Arruma o 1 na primeira Linha;
		while(l6 > 1){//Enquanto o 6 não estiver na Segunda linha;
			//Joga o 0 na Segunda linha;
			while(l0 > 1){
				up(array, &p0, &l0, &c0);
				pos(array, &p6, &l6, &c6, 6);
			}

			while(c0 > 1) left(array, &p0, &l0, &c0);//Joga ele na coluna a cima do 1;

			while(l0 < l6){//Traz o 1 para cima uma posição;
				down(array, &p0, &l0, &c0);
				pos(array, &p6, &l6, &c6, 6);
			}
			right(array, &p0, &l0, &c0);//e joga o 0 pra direita;
		}
	}
}

void solve7e8(int *array){
	while(array[6] != 7 || array[7] != 8){
//------------------------------------------------------------//Arrumando o 8 no lugar do 7;
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;
		int p8 = search(array, 8), l8 = p8 / 4, c8 = p8 % 4;

//---------------------------------------------------//Arrumando o 8 na coluna certa;
		while(c8 != 2){
			if(c0 < 2){
				while(c0 < 2){//Deixa o 0 na coluna 2;
					right(array, &p0, &l0, &c0);
					pos(array, &p8, &l8, &c8, 8);
				}
			}else if(c0 > 2){
				left(array, &p0, &l0, &c0);
				pos(array, &p8, &l8, &c8, 8);
			}
			//Deixa o 0 na mesma linha que o 8;
			if (l0 < l8){
				while(l0 < l8) down(array, &p0, &l0, &c0);
			}else if(l0 > l8){
				while(l0 > l8) up(array, &p0, &l0, &c0);
			}
			//Traz o 8 uma posição;
			if(c0 > c8){
				while(c0 > c8){
					left(array, &p0, &l0, &c0);
					pos(array, &p8, &l8, &c8, 8);
				}
			}else{
				right(array, &p0, &l0, &c0);
				pos(array, &p8, &l8, &c8, 8);
			}
			(l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);//Tira o 0 da linha do 8;
		}
//---------------------------------------------------------------------------------//Arruma 8 na linha;
		while(l8 > 1){//Enquanto o 8 não estiver na segunda linha;
			//Tira o 0 da linha do 8;
			if(l0 == l8) (l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);
			//Joga o 0 na última coluna;
			while(c0 < 3) right(array, &p0, &l0, &c0);

			while(l0 > 1) up(array, &p0, &l0, &c0);//Quando 0 tiver na coluna 3, joga ele pra linha 1;

			while(c0 > c8){//Quando 0 tiver na linha 0, joga ele pra mesma coluna que o 8;
				left(array, &p0, &l0, &c0);
			}

			while(l0 < l8){//Quando 0 tiver na mesma coluna que o 8, joga ele pra baixo até o 8 subir;
				down(array, &p0, &l0, &c0);
				pos(array, &p8, &l8, &c8, 8);
			}
		}
//------------------------------------------------------------------------------------------//Arruma o 7 embaixo do 8;
		int p7 = search(array, 7), l7 = p7 / 4, c7 = p7 % 4;
//---------------------------------------------------//Arrumando o 7 na coluna certa;
        while(c7 != 2){
            if((l7 != 1) && !(l0 == 1 && l7 == 2 && c7 == 3)){
                if(l0 == 1) down(array, &p0, &l0, &c0);
                if(c0 != 2) (c0 == 1) ? right(array, &p0, &l0, &c0) : left(array, &p0, &l0, &c0);
                if(l0 != l7) (l0 < l7) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);
                (c0 < c7) ? right(array, &p0, &l0, &c0) : left(array, &p0, &l0, &c0);
                pos(array, &p7, &l7, &c7, 7);
            }else {
                if(l0 == 1 && l7 == 2 && c7 == 3) down(array, &p0, &l0, &c0);
                //Joga o 0 embaixo do 7;
                while(c0 < 3) right(array, &p0, &l0, &c0);
                while(l0 > 2) up(array, &p0, &l0, &c0);
                //Da 2 voltas ;
                up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);
                up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);
                //Tira o 7 do círculo;
                up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);
                //Deixa o 8 em seu lugar e o 7 na coluna certa;
                right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);
                right(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
	 			pos(array, &p7, &l7, &c7, 7);
            }
        }
//----------------------------------------------------------------------------------//Arruma 7 na linha certa;
        while(l7 != 2){
            if(l0 == l7) (l0 < 3 ) ? down(array, &p0, &l0, &c0) : up(array, &p0, &l0, &c0);
            while(c0 < 3) right(array, &p0, &l0, &c0);
            while(l0 > 2) up(array, &p0, &l0, &c0);
            left(array, &p0, &l0, &c0);
            while(l0 < l7) down(array, &p0, &l0, &c0);
            pos(array, &p7, &l7, &c7, 7);
        }

//-------------------------------------------------------------------------------//Arruma tudo
		//Joga o zero na ultima linha e depois naúltima coluna. Depois sobe ele até a Segunda linha;
		while(l0 < 3) down(array, &p0, &l0, &c0);
		while(c0 < 3) right(array, &p0, &l0, &c0);
		while(l0 > 1) up(array, &p0, &l0, &c0);
		left(array, &p0, &l0, &c0); down(array, &p0, &l0, &c0);
	}
}

void solve10e14(int *array){
	while(array[9] != 10 || array[13] != 14){
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;
		int p14 = search(array, 14), l14 = p14 / 4, c14 = p14 % 4;
//------------------------------------------------------------------Arruma 14 na linha;
		if(l14 != 2){//Coloca o 14 na linha 2;
			if(l0 == 3) up(array, &p0, &l0, &c0);//0 na linha 2 para mover o 14;

			if(c0 != c14){//Joga o 0 na coluna do 14;
				if(c0 < c14){
					while(c0 < c14) right(array, &p0, &l0, &c0);
				}else if(c0 > c14){
					while(c0 > c14) left(array, &p0, &l0, &c0);
				}
			}
			//Deixa o 14 na linha do dele;
			(l0 > l14) ? up(array, &p0, &l0, &c0) : down(array, &p0, &l0, &c0);//Tira o 0 da linha do 13;
		}
//---------------------------------------------------------Arruma 14 na coluna;
		while(c14 > 1){
			while(l0 < 3) down(array, &p0, &l0, &c0);//Tira o zero da linha do 14;
			while(c0 > 1) left(array, &p0, &l0, &c0);//0 na Segunda coluna;
			up(array, &p0, &l0, &c0);//Joga o 0 pra cima até ficar na mesma linha do 14;
			while(c0 < c14){
				right(array, &p0, &l0, &c0);
				pos(array, &p14, &l14, &c14, 14);
			}
		}
//-----------------------------------------------------------------Arruma 10 na linha
		int p10 = search(array, 10), l10 = p10 / 4, c10 = p10 % 4;
        while(l10 != 2){
            if(c10 == 3){
                if(c0 != 2) (c0 == 1) ? right(array, &p0, &l0, &c0) : left(array, &p0, &l0, &c0);//Arruma 0 na coluna 2;
                if(l0 == 3) up(array, &p0, &l0, &c0);//Joga pra cima
                right(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);//Arruma o 10
            }else if(c10 == 2 && c0 > 1){
                if(l0 == 3) up(array, &p0, &l0, &c0);
                if(c0 > c10) left(array, &p0, &l0, &c0);
                down(array, &p0, &l0, &c0);
            }else{
                if(l0 == l10 && c10 == c0 + 1) right(array, &p0, &l0, &c0);
                //Deixa o 0 a direita do 9
                if(l0 < 3) down(array, &p0, &l0, &c0);
                if(c0 > 2) left(array, &p0, &l0, &c0);
                //Da uma volta e meia;
                left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
                left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);down(array, &p0, &l0, &c0);
                //Volta o 14 para sua posição
                left(array, &p0, &l0, &c0);up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);
            }
            pos(array, &p10, &l10, &c10, 10);
        }
//--------------------------------------Arruma coluna do 10
        if(c10 == 3){
            if(c0 != 2) (c0 == 1) ? right(array, &p0, &l0, &c0) : left(array, &p0, &l0, &c0);//Arruma 0 na coluna 2;
            if(l0 == 3) up(array, &p0, &l0, &c0);//Joga pra cima
            right(array, &p0, &l0, &c0);
            pos(array, &p10, &l10, &c10, 10);
        }
//---------------------------------------Arruma tuto
		while(l0 < 3) down(array, &p0, &l0, &c0);
		while(c0 > 1) left(array, &p0, &l0, &c0);
		up(array, &p0, &l0, &c0);right(array, &p0, &l0, &c0);
	}
}

void solveFinal(int *array){
    while(array[10] != 11 || array[11] != 12 || array[14] != 15){
		int p0 = search(array, 0), l0 = p0 / 4, c0 = p0 % 4;
		int p11 = search(array, 11), l11 = p11 / 4, c11 = p11 % 4;
//-----------------------------------Arruma 11
        if(c11 == 3){//Arruma 11 na coluna;
            if(c0 == c11) left(array, &p0, &l0, &c0);
            if (l0 < l11) down(array, &p0, &l0, &c0);
            if (l0 > l11) up(array, &p0, &l0, &c0);
            right(array, &p0, &l0, &c0);
            pos(array, &p11, &l11, &c11, 11);
        }
//-----------------------------Arruma 11 na linha;
        if(l11 == 3){
            if(l0 == 3){
                up(array, &p0, &l0, &c0);left(array, &p0, &l0, &c0);
            }
            down(array, &p0, &l0, &c0);
        }
//-------------------------------------------------------Arruma 12 e 15;
		int p12 = search(array, 12), l12 = p12 / 4, c12 = p12 % 4;
        int p15 = search(array, 11), l15 = p15 / 4, c15 = p15 % 4;
        (l12 == 3) ? down(array, &p0, &l0, &c0) : right(array, &p0, &l0, &c0);;
    }
}

void pos(int *array, int *p, int *l,int *c, int n){//Acha as coordenadas do 1;
	*p = search(array, n);
	*l = *p / 4;
	*c = *p % 4;
	return;
}

void up(int *array, int *p0, int *l0, int *c0){
	int aux = array[*p0 - 4];
	array[*p0 - 4] = array[*p0];
	array[*p0] = aux;

	*p0 -= 4;
	*l0 -= 1;
}

void down(int *array, int *p0, int *l0, int *c0){
	int aux = array[*p0 + 4];
	array[*p0 + 4] = array[*p0];
	array[*p0] = aux;

	*p0 += 4;
	*l0 += 1;
}

void left(int *array, int *p0, int *l0, int *c0){
	int aux = array[*p0 - 1];
	array[*p0 - 1] = array[*p0];
	array[*p0] = aux;

	*p0 -= 1;
	*c0 -= 1;
}

void right(int *array, int *p0, int *l0, int *c0){
	int aux = array[*p0 + 1];
	array[*p0 + 1] = array[*p0];
	array[*p0] = aux;

	*p0 += 1;
	*c0 += 1;
}
