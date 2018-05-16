#include "NEURAL_NET_HEADER.h"

// Takes in FEN notation board state, converts it to something the neural net can process (but first, something that I can glance at).

int bdarr[73]; // 64 for each board position, the extra nine for other FEN information (integers greater than nine take up one spac, right?? RIGHT???)
int onecount = 0;

int main (int argc, char *argv[]) { // printer/converter
  char cget;
  int arrpos = 0;
  //printf("%d ", arrpos); // DEBUG STMT
  while ((cget = getchar()) != ' ') {
    int rowpos = 0;
    if (cget != '/') {
      if (isdigit(cget) == 0) {
	printf("%c ", cget);
	bdarr[arrpos] = pcconv(cget);
	arrpos++;
      }
      else if (isdigit(cget) != 0) {
	int empty1 = cget;
	int empty2 = empty1 - 48;
	for (int i = 0; i < empty2; i++) {
	  printf("_ ");
	  bdarr[arrpos] = 0;
	  arrpos++;
	}
      }
    }
    else if (cget == '/') {
      printf("\n");
    }
  }

  printf("\n");
  int field = 0;
  while ((cget = getchar()) != '\n') {
    if (cget != ' ') {
      if (field == 0) {
	if (cget == 'w') {
	  printf("White's move.");
	  bdarr[arrpos] = 1;
	  arrpos++;
	}
	else if (cget == 'b') {
	  printf("Black's move.");
	  bdarr[arrpos] = 0;
	  arrpos++;
	}
      }
      else if (field == 1) {
	if (cget == '-') {
	  printf("No castling.");
	  for (int i = 0; i < 4; i++) {
	    bdarr[arrpos] = 0;
	    arrpos++;
	    //printf("just added, arrpos is %d\n", arrpos); // DEBUG STMT
	  }
	  onecount = 3;
	}
	else if ((cget == 'K' || cget == 'k') || (cget == 'Q' || cget == 'q')) {
	  printf("%c castling; ", cget);
	  bdarr[arrpos] = 1;
	  arrpos++;
	  onecount++;
	  //printf("Onecount is %d\n", onecount); // DEBUG STMT
	}
      }
      else if (field == 2) {
	if (onecount < 3) {
	  //printf("Onecount is %d\n", onecount); // DEBUG STMT
	  while (onecount < 4) {
	    bdarr[arrpos] = 0;
	    arrpos++;
	    onecount++;
	  }
	  onecount = 0;
	}
	if (cget == '-') {
	  printf("No en passant.");
	  for (int i = 0; i < 2; i++) {
	    bdarr[arrpos] = 0;
	    arrpos++;
	  }
	}
	else if (cget != '-') {
	  printf("%c", cget);
	  if (isdigit(cget) != 0) {
	    bdarr[arrpos] = cget;
	    arrpos++;
	  }
	  else if (isdigit(cget) == 0) {
	    if (cget == 'a') {
	      bdarr[arrpos] = 1;
	      arrpos++;
	    }
	    else if (cget == 'b') {
	      bdarr[arrpos] = 2;
	      arrpos++;
	    }
	    else if (cget == 'c') {
	      bdarr[arrpos] = 3;
	      arrpos++;
	    }
	    else if (cget == 'd') {
	      bdarr[arrpos] = 4;
	      arrpos++;
	    }
	    else if (cget == 'e') {
	      bdarr[arrpos] = 5;
	      arrpos++;
	    }
	    else if (cget == 'f') {
	      bdarr[arrpos] = 6;
	      arrpos++;
	    }
	    else if (cget == 'g') {
	      bdarr[arrpos] = 7;
	      arrpos++;
	    }
	    else if (cget == 'h') {
	      bdarr[arrpos] = 8;
	      arrpos++;
	    }
	  }
	}
      }
      else if (field == 3) { 
	printf("Halfmoves: %c.", cget);
	bdarr[arrpos] = cget - 48;
	arrpos++;
      }
      else if (field == 4) {
	printf("Move %c.", cget);
	bdarr[arrpos] = cget - 48;
	arrpos++; // YES OR NO?
      }
    }
    else if (cget == ' ') {
      printf("\n");
      field++;
    }
  }
  
  printf("\n");
  for (int i = 0; i < arrpos; i++) {
    printf("%d ", bdarr[i]);
  }
  printf("\n");
  printf("Length is %d.\n", arrpos);
  arrpos = 0;
  onecount = 0;
  printf("\n");
  
}

int pcconv (char pc) {
  if (isdigit(pc) == 0) {
    if (pc == 'K' || pc == 'k') {
      if (pc == 'K') {
	return 6;
      }
      return -6;
    }
    else if (pc == 'Q' || pc == 'q') {
      if (pc == 'Q') {
	return 5;
      }
      return -5;
    }
    else if (pc == 'R' || pc == 'r') {
      if (pc == 'R') {
	return 4;
      }
      return -4;
    }
    else if (pc == 'B' || pc == 'b') {
      if (pc == 'B') {
	return 3;
      }
      return -3;
    }
    else if (pc == 'N' || pc == 'n') {
      if (pc == 'N') {
	return 2;
      }
      return -2;
    }
    else if (pc == 'P' || pc == 'p') {
      if (pc == 'P') {
	return 1;
      }
      return -1;
    }
  }
}

