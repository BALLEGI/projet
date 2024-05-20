#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
// JEUX D'ECHECK

char board[8][8];
int i,j;
void init_board() {
    // INITILSATION DE LA BOARD
    
    char board0[8][8] = {// LA BORAD0 AVANT DE FAIRE UNE MOUVEMENT
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},// LES LETTRES MAJUSCULE EST LE BLANC ET LES LETTRES MINUSCULE EST LE NOIRE
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    
    for ( i = 0; i < 8; i++) {
        for ( j = 0; j < 8; j++) {
            board[i][j] =board0[i][j];
        }// LA BOARD EST REMPLIR PAR LA BORAD0 A LA PREMIER FOIS PUIS REMPLIR CE DEPEND DE LA MOUVEMENT
    }
}

void print_board() {// AFFICHAGE DE LA BOARD 
    printf("  a b c d e f g h\n");
    printf("  ----------------\n");
    
    for ( i = 0; i <8; i++) {
        printf("%d|", 8 - i);
        for (j = 0; j <8; j++) {
            printf("%c|", board[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  ----------------\n");
    printf("  a b c d e f g h\n");
}

bool is_valid_move(char move[4],int nomove) {
    // VERIFIER SI LE MOVEMENT EST DANS LA BOARD OU NON
    if (move[0] < 'a' || move[0] > 'h' || move[1] < '1' || move[1] > '8' ||
        move[2] < 'a' || move[2] > 'h' || move[3] < '1' || move[3] > '8') {
        return false;
    }
    // VERIFIER SI LA PIECE EST VALIDE OU NON
    bool test;
    int stat1,stat;
    int start_row = '8' - move[1];
    int start_col = move[0] - 'a';
    int end_row = '8' - move[3];
    int end_col = move[2] - 'a';
    char piece = board[start_row][start_col];
    char piecex = board[end_row][end_col];
    if (islower(piece) && nomove%2==0){
    	printf("le blanc qui joue \n");//VERIFIER SI LES JOUEUR SI SON TOURE OU NON
    	return false;
	}
	if(isupper(piece) && nomove%2!=0){
		printf("le noire qui joue \n");
		return false;
	}
    if (board[start_row][start_col] == ' ') {
        return false;
    }//VERIFIER SI LA POSITION IL Y'A UNE PIECE OU NON DE MEME JOUEUR
    if (islower(piece)) { 
    	if(islower(piecex)){
    		printf("1");
    		return false;	
		}

    	if (piece=='p'){
    		// VERIFIER SI LA P PEUT JOUER OU NON
    		if(start_row>=end_row){
    		
				return false;
			}
			if(start_row==1 && end_row-start_row>2){
			
				return false;
			}
			if ( start_row!=1 && end_row-start_row !=1){
				
				return false;
			}
			if (start_col==end_col && piecex!=' '){
				
				return false;
			}
			if (start_col!=end_col && piecex==' '){
				printf("11");
				return false;
			}
		}
		// VERIFIER SI LE ROCK PEUT JOUER OU NON
    	if (piece=='r'){
    		stat=start_row;
    		stat1=start_col;
    		if (start_col==end_col){
				test=true;
    			while ( test==true){
    				stat1=stat1+1;
    				char piecex1 = board[stat][stat1];
    				if ( piecex1!=' '){
    				;
    					test=false;
					}
    				
			}
			return test;
			}
		}
	}
	if (isupper(piece) ){
		if (isupper(piecex)){
		
			return false;
		}

		if (piece=='P'){ // VERIFIER LES CONDITION DE P N'EST PAS VALIDE DONC ON NE PEUT PAS JOUER
			if(start_row<=end_row){
				
				return false;	
			}
			if(start_row==6 && start_row-end_row>2){
			
				return false;
			}
			if (start_row!=6 && start_row-end_row!=1){
				
				return false;
			}
			if (start_col==end_col && piecex!=' '){
				
				return false;
			}
			if (start_col!=end_col && piecex==' '){
				
				return false;
			}}}
	if (piece == 'k' || piece == 'K') {
        // Calcul des déplacements possibles du roi
        int row_diff = abs(end_row - start_row);
        if (row_diff>1){
        	return false;
		}
        int col_diff = abs(end_col - start_col);
        if (col_diff>1){
        	return false;
		}
        
        
    }
	if (piece == 'q' || piece == 'Q') {
        // Calcul des déplacements possibles de la reine
        int row_diff = abs(end_row - start_row);
        int col_diff = abs(end_col - start_col);
        
        int row_step = (start_row < end_row) ? 1 : (start_row > end_row) ? -1 : 0;
    	int col_step = (start_col < end_col) ? 1 : (start_col > end_col) ? -1 : 0;
		int row = start_row + row_step, col = start_col + col_step;
    // Parcours des cases intermédiaires
    	for (row, col; row != end_row || col != end_col;row += row_step, col += col_step) {
        	if (board[row][col] != ' ') {
            	return false; // Il y a une pièce sur le chemin
        }
    }
    }
	if (piece == 'n' || piece == 'N') {
        // Calcul des déplacements possibles du cavalier
        int row_diff = abs(end_row - start_row);
        int col_diff = abs(end_col - start_col);
        
        // Vérification si le mouvement est en L
        if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
            return true; // Le déplacement est valide
        }else{
        	return false;
		}
    }
	// VERIFIER ON PEUT JOUER LE BISHOP OU NON
	if (piece == 'b' || piece == 'B') {
        
        int row_diff = end_row - start_row;
        int col_diff = end_col - start_col;
        if (row_diff != 0 && col_diff != 0 && abs(row_diff) == abs(col_diff)) {
           
            int row_step = (row_diff > 0) ? 1 : -1;
            int col_step = (col_diff > 0) ? 1 : -1;
            int row = start_row + row_step;
            int col = start_col + col_step;
            while (row != end_row && col != end_col) {// VERIFIER IL YA UNE PIECE DANS LE CHEMIN
                if (board[row][col] != ' ') {
                    return false; 
                }
                row += row_step;
                col += col_step;
            }}}
	if (piece == 'r' || piece == 'R') {

        if (start_row == end_row) {
           	int step = (start_col < end_col) ? 1 : -1;
            	int col = start_col + step;
            	for (col; col != end_col; col += step) {
                	if (board[start_row][col] != ' ') {
                    	// VERIFIER IL YA UNE PIECE DANS LE CHEMIN OU  NON
                    	return false;
                }
            }
            
        }

        	else if (start_col == end_col) {
            	int step = (start_row < end_row) ? 1 : -1;
            	int row = start_row + step;
            	for (row; row != end_row; row += step) {
                	if (board[row][start_col] != ' ') {
                    	// VERIFIER IL YA UNE PIECE DANS LE CHEMIN OU NON
                    	return false;
                }
            }

        }
    }
		

	
	

	
    return true;
}

void make_move(char move[4]) {// FAIRE LE MOUVEMENT SI VALIDE
    int start_row = '8' - move[1];
    int start_col = move[0] - 'a';
    int end_row = '8' - move[3];
    int end_col = move[2] - 'a';

    char piece = board[start_row][start_col];
    board[start_row][start_col] = ' ';
    board[end_row][end_col] = piece;
}

int main() {// PROGRAMME PRINCIPALE
    init_board();// INITIATION DE LA BOARD
    int nomove=0;
    while (true) {
        print_board();
        char move[5];
        printf("Enter your move (e.g., e2e4): ");
        scanf("%s", move);
        if (move[0] == 'e' && move[1] == 'x' && move[2] == 'i' && move[3] == 't') {// METHODE POUR TERMINER LE JEUX
            break;
        }

        if (is_valid_move(move,nomove)) {// SI LA MOUVEMENT EST VALIDE DONC ON PEUT JOUER
            make_move(move);
            printf("MOVEMENT EST REUSSIT!\n");
            nomove=nomove+1;
        } else {
            printf("MOUVEMENT EST NON VALIDE!\n");// SI LA MOUVEMENT EST NON VALIDE DOC AFFICHE UN MESSAGE D'ERREURE
        }
    }
    return 0;
}
// FIN DE PROGRAMME 
// CE TRAVAIL EST PAR BALLEGI ALA , OKAZI KOSSAY ET SAID ACHREF
