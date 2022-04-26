struct Tile {
  int state;
  char piece;
  int x;
  int y;
};

struct Tile prevBoard[3][3];
struct Tile board[3][3];
struct Tile lightBoard[3][3];

void printBoard(struct Tile b[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (b[j][i].state == 1) {
        Serial.print(b[j][i].piece);
        Serial.print(" ");
      } else {
        Serial.print(b[j][i].state);
        Serial.print(" ");
      }
    }
    Serial.println();
  }
}

void checkPawn(struct Tile p) {
  board[p.x][p.y].state = -1;
  if (p.y - 1 >= 0 && prevBoard[p.x][p.y - 1].state == 0) {
    board[p.x][p.y - 1].state = 2;
  }
  printBoard(board);
}

void checkRook(struct Tile p) {
  Serial.print("Tile: ");
      Serial.print("X: ");
      Serial.print(p.x);
      Serial.print(" Y: ");
      Serial.println(p.y);
  for (int y = p.y; y < 3; y++) {
    if (y == p.y) {
      continue;
    }
    if (board[p.x][y].state == 0) {
      board[p.x][y].state = 2;
    } else {
      break;
    }
  }

  for (int y = p.y; y >= 0; y--) {
    if (y == p.y) {
      continue;
    }
    if (board[p.x][y].state == 0) {
      board[p.x][y].state = 2;
    } else {
      break;
    }
  }

  for (int x = p.x; x < 3; x++) {
    if (x == p.x) {
      continue;
    }
    if (board[x][p.y].state == 0) {
      board[x][p.y].state = 2;
    } else {
      break;
    }
  }

  for (int x = p.x; x >= 0; x--) {
    if (x == p.x) {
      continue;
    }
    if (board[x][p.y].state == 0) {
      board[x][p.y].state = 2;
    } else {
      break;
    }
  }

  board[p.x][p.y].state = -1;
  
  printBoard(board);
}

struct Tile findPickedUpPiece(struct Tile prev[3][3], struct Tile b[3][3]) {
  struct Tile t;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      t = prev[j][i];
      if (prev[j][i].state != b[j][i].state) {
        if (t.piece == 'p') {
          checkPawn(t);
        } else if (t.piece == 'r') {
          checkRook(t);
        }
        return t;
      }
    }
  }
  t.state = -2;
  return t;
}

struct Tile findPlacedPiece(char piece, struct Tile prev[3][3], struct Tile b[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if ((prev[j][i].state == 2 && b[j][i].state == 1) || (prev[j][i].state == -1 && b[j][i].state == 1)) {
        // turn lights off
        board[j][i].piece = piece;
        board[j][i].state = 1;
        Serial.print("Placed Board: \n");
        printBoard(board);
        return board[j][i];
      }
    }
  }
  struct Tile t;
  t.state = -2;
  return t;
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      struct Tile t;
      t.state = 0;
      t.piece = 'x';
      t.x = j;
      t.y = i;
      prevBoard[j][i] = t;
      board[j][i] = t;
    }
  }

  // Testing pawn in center
  prevBoard[1][0].state = 1;
  prevBoard[1][0].piece = 'p';
  board[1][0].state = 1;
  board[1][0].piece = 'p';
  
  prevBoard[2][0].state = 1;
  prevBoard[2][0].piece = 'r';
}

void copyBoard() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      prevBoard[j][i] = board[j][i];
    }
  }
}

bool f = false;

void loop() {
  // put your main code here, to run repeatedly:
    if (!f) {
      Serial.print("Previous Board: \n");
      printBoard(prevBoard);
      Serial.print("Current Board: \n");
      printBoard(board);
      Serial.println();
      struct Tile t = findPickedUpPiece(prevBoard, board);
      Serial.print("Tile: ");
      Serial.print("X: ");
      Serial.print(t.x);
      Serial.print(" Y: ");
      Serial.println(t.y);
      delay(20);

      if (t.state != -2) {
        copyBoard();
      }
      // hardcode sensor
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          struct Tile t;
          board[j][i].state = 0;
        }
      }
      board[1][0].state = 1;
      board[2][2].state = 1;

      Serial.print("New Previous Board: \n");
      printBoard(prevBoard);
      Serial.print("New Current Board: \n");
      printBoard(board);
      Serial.println();

      struct Tile p = findPlacedPiece('r', prevBoard, board);
      
      f = true;
    }
}
