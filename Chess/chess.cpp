#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;
const int height = 8;
const int width = 8;

class Figure {
public:

	virtual void Vars(int startY, int startX, vector<string> & Memory, const vector<vector<Figure*>>& Field) = 0;
	void VarOnField(vector<string>& Memory) {
		system("cls");
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << Memory[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	bool isWhite;
	char symbol;
	char curSymbol;
};

class Pawn : public Figure {
public:
	Pawn(bool isWhite) {
		this->isWhite = isWhite;
		symbol = isWhite ? 'п' : 'p';
		curSymbol = isWhite ? 'П' : 'P';
	}
	void Vars(int startY, int startX, vector<string> & Memory, const vector<vector<Figure*>>& Field) override {
		Memory[startY][startX] = curSymbol;
		if (isWhite) {
			if (startY == 6 && Field[startY - 2][startX] == nullptr) Memory[startY - 2][startX] = '+';
			if (startY > 0 && Field[startY - 1][startX] == nullptr) Memory[startY - 1][startX] = '+';
			if (startX > 0 && Field[startY - 1][startX - 1] != nullptr && !Field[startY - 1][startX - 1]->isWhite)
				Memory[startY - 1][startX - 1] = '+';
			if (startX < 7 && Field[startY - 1][startX + 1] != nullptr && !Field[startY - 1][startX + 1]->isWhite)
				Memory[startY - 1][startX + 1] = '+';
		}
		else {
			if (startY == 1 && Field[startY + 2][startX] == nullptr) Memory[startY + 2][startX] = '+';
			if (startY < 7 && Field[startY + 1][startX] == nullptr) Memory[startY + 1][startX] = '+';
			if (startX > 0 && Field[startY + 1][startX - 1] != nullptr && Field[startY + 1][startX - 1]->isWhite)
				Memory[startY + 1][startX - 1] = '+';
			if (startX < 7 && Field[startY + 1][startX + 1] != nullptr && Field[startY + 1][startX + 1]->isWhite)
				Memory[startY + 1][startX + 1] = '+';
		}

		VarOnField(Memory);
	}
};

class Rook : public Figure {
public:
	Rook(bool isWhite) {
		this->isWhite = isWhite;
		symbol = isWhite ? 'т' : 'r';
		curSymbol = isWhite ? 'Т' : 'R';
	}
	void Vars(int startY, int startX, vector<string>& Memory, const vector<vector<Figure*>>& Field) override {
		Memory[startY][startX] = curSymbol;
		for (int i = startY - 1; i >= 0; i--) {
			if (Field[i][startX] == nullptr) {
				Memory[i][startX] = '+';
			}
			else {
				if (Field[i][startX]->isWhite != this->isWhite)
					Memory[i][startX] = '+';
				break;
			}
		}
		for (int i = startY + 1; i <= 7; i++) {
			if (Field[i][startX] == nullptr) {
				Memory[i][startX] = '+';
			}
			else {
				if (Field[i][startX]->isWhite != this->isWhite)
					Memory[i][startX] = '+';
				break;
			}
		}
		for (int i = startX + 1; i <= 7; i++) {
			if (Field[startY][i] == nullptr) {
				Memory[startY][i] = '+';
			}
			else {
				if (Field[startY][i]->isWhite != this->isWhite)
					Memory[startY][i] = '+';
				break;
			}
		}
		for (int i = startX - 1; i >= 0; i--) {
			if (Field[startY][i] == nullptr) {
				Memory[startY][i] = '+';
			}
			else {
				if (Field[startY][i]->isWhite != this->isWhite)
					Memory[startY][i] = '+';
				break;
			}
		}

		VarOnField(Memory);
	}
};

class Bishop : public Figure {
public:
	Bishop(bool isWhite) {
		this->isWhite = isWhite;
		symbol = isWhite ? 'с' : 'b';
		curSymbol = isWhite ? 'С' : 'B';
	}
	void Vars(int startY, int startX, vector<string>& Memory, const vector<vector<Figure*>>& Field) override {
		Memory[startY][startX] = curSymbol;
		for (int i = 1; i >= 0; i++) {
			if (startY + i <= 7 && startX + i <= 7) {
				if (Field[startY + i][startX + i] == nullptr) {
					Memory[startY + i][startX + i] = '+';
				}
				else {
					if (Field[startY + i][startX + i]->isWhite != this->isWhite)
						Memory[startY + i][startX + i] = '+';
					break;
				}
			}
			else break;
		}
		for (int i = 1; i >= 0; i++) {
			if (startY - i >= 0 && startX + i <= 7) {
				if (Field[startY - i][startX + i] == nullptr) {
					Memory[startY - i][startX + i] = '+';
				}
				else {
					if (Field[startY - i][startX + i]->isWhite != this->isWhite)
						Memory[startY - i][startX + i] = '+';
					break;
				}
			}
			else break;
		}
		for (int i = 1; i >= 0; i++) {
			if (startY + i <= 7 && startX - i >= 0) {
				if (Field[startY + i][startX - i] == nullptr) {
					Memory[startY + i][startX - i] = '+';
				}
				else {
					if (Field[startY + i][startX - i]->isWhite != this->isWhite)
						Memory[startY + i][startX - i] = '+';
					break;
				}
			}
			else break;
		}
		for (int i = 1; i >= 0; i++) {
			if (startY - i >= 0 && startX - i >= 0) {
				if (Field[startY - i][startX - i] == nullptr) {
					Memory[startY - i][startX - i] = '+';
				}
				else {
					if (Field[startY - i][startX - i]->isWhite != this->isWhite)
						Memory[startY - i][startX - i] = '+';
					break;
				}
			}
			else break;
		}

		VarOnField(Memory);
	}
};

class Queen : public Figure {
public:
	Queen(bool isWhite) {
		this->isWhite = isWhite;
		symbol = isWhite ? 'ф' : 'q';
		curSymbol = isWhite ? 'Ф' : 'Q';
	}
	void Vars(int startY, int startX, vector<string>& Memory, const vector<vector<Figure*>>& Field) override {
		Memory[startY][startX] = curSymbol;
		for (int i = startY - 1; i >= 0; i--) {//ходы ладьи
			if (Field[i][startX] == nullptr) {
				Memory[i][startX] = '+';
			}
			else {
				if (Field[i][startX]->isWhite != this->isWhite)
					Memory[i][startX] = '+';
				break;
			}
		}
		for (int i = startY + 1; i <= 7; i++) {
			if (Field[i][startX] == nullptr) {
				Memory[i][startX] = '+';
			}
			else {
				if (Field[i][startX]->isWhite != this->isWhite)
					Memory[i][startX] = '+';
				break;
			}
		}
		for (int i = startX + 1; i <= 7; i++) {
			if (Field[startY][i] == nullptr) {
				Memory[startY][i] = '+';
			}
			else {
				if (Field[startY][i]->isWhite != this->isWhite)
					Memory[startY][i] = '+';
				break;
			}
		}
		for (int i = startX - 1; i >= 0; i--) {
			if (Field[startY][i] == nullptr) {
				Memory[startY][i] = '+';
			}
			else {
				if (Field[startY][i]->isWhite != this->isWhite)
					Memory[startY][i] = '+';
				break;
			}
		}
		for (int i = 1; i >= 0; i++) {//ходы слона
			if (startY + i <= 7 && startX + i <= 7) {
				if (Field[startY + i][startX + i] == nullptr) {
					Memory[startY + i][startX + i] = '+';
				}
				else {
					if (Field[startY + i][startX + i]->isWhite != this->isWhite)
						Memory[startY + i][startX + i] = '+';
					break;
				}
			}
			else break;
		}
		for (int i = 1; i >= 0; i++) {
			if (startY - i >= 0 && startX + i <= 7) {
				if (Field[startY - i][startX + i] == nullptr) {
					Memory[startY - i][startX + i] = '+';
				}
				else {
					if (Field[startY - i][startX + i]->isWhite != this->isWhite)
						Memory[startY - i][startX + i] = '+';
					break;
				}
			}
			else break;
		}
		for (int i = 1; i >= 0; i++) {
			if (startY + i <= 7 && startX - i >= 0) {
				if (Field[startY + i][startX - i] == nullptr) {
					Memory[startY + i][startX - i] = '+';
				}
				else {
					if (Field[startY + i][startX - i]->isWhite != this->isWhite)
						Memory[startY + i][startX - i] = '+';
					break;
				}
			}
			else break;
		}
		for (int i = 1; i >= 0; i++) {
			if (startY - i >= 0 && startX - i >= 0) {
				if (Field[startY - i][startX - i] == nullptr) {
					Memory[startY - i][startX - i] = '+';
				}
				else {
					if (Field[startY - i][startX - i]->isWhite != this->isWhite)
						Memory[startY - i][startX - i] = '+';
					break;
				}
			}
			else break;
		}

		VarOnField(Memory);
	}
};

class Horse : public Figure {
public:
	Horse(bool isWhite) {
		this->isWhite = isWhite;
		symbol = isWhite ? 'л' : 'h';
		curSymbol = isWhite ? 'Л' : 'H';
	}
	void Vars(int startY, int startX, vector<string>& Memory, const vector<vector<Figure*>>& Field) override {
		Memory[startY][startX] = curSymbol;
		int moves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},{1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
		for (auto& move : moves) {
			if (startY + move[0] <= 7 && startX + move[1] <= 7 && startY + move[0] >= 0 && startX + move[1] >= 0)
				if (Field[startY + move[0]][startX + move[1]] == nullptr || Field[startY + move[0]][startX + move[1]]->isWhite != this->isWhite)
					Memory[startY + move[0]][startX + move[1]] = '+';
		}

		VarOnField(Memory);
	}
};

class King : public Figure {
public:
	King(bool isWhite) {
		this->isWhite = isWhite;
		symbol = isWhite ? 'ц' : 'k';
		curSymbol = isWhite ? 'Ц' : 'K';
	}
	void Vars(int startY, int startX, vector<string>& Memory, const vector<vector<Figure*>>& Field) override {
		Memory[startY][startX] = curSymbol;
		int moves[8][2] = { {1, 0}, {1, 1}, {0, 1}, {-1, 1},{-1, 0}, {-1, -1}, {0, -1}, {1, -1} };
		for (auto& move : moves) {
			if (startY + move[0] <= 7 && startX + move[1] <= 7 && startY + move[0] >= 0 && startX + move[1] >= 0)
				if (Field[startY + move[0]][startX + move[1]] == nullptr || Field[startY + move[0]][startX + move[1]]->isWhite != this->isWhite)
					Memory[startY + move[0]][startX + move[1]] = '+';
		}

		VarOnField(Memory);
	}
};

class Deck {
public:
	Deck() : Field(height, vector<Figure*>(width, nullptr)),Memory(height, string(width, '·')) {}
	vector<vector<Figure*>> Field;
	void StartPos() {
		Horse* lwHorse = new Horse(true); Field[7][1] = lwHorse;
		Horse* rwHorse = new Horse(true); Field[7][6] = rwHorse;
		Rook* lWhiteRook = new Rook(true); Field[7][0] = lWhiteRook;
		Rook* rWhiteRook = new Rook(true); Field[7][7] = rWhiteRook;
		Bishop* lWhiteBishop = new Bishop(true); Field[7][2] = lWhiteBishop;
		Bishop* rWhiteBishop = new Bishop(true); Field[7][5] = rWhiteBishop;
		Queen* WhiteQueen = new Queen(true); Field[7][3] = WhiteQueen;
		King* wKing = new King(true); Field[7][4] = wKing;

		Horse* lbHorse = new Horse(false); Field[0][1] = lbHorse;
		Horse* rbHorse = new Horse(false); Field[0][6] = rbHorse;
		Rook* lBlackRook = new Rook(false); Field[0][0] = lBlackRook;
		Rook* rBlackRook = new Rook(false); Field[0][7] = rBlackRook;
		Bishop* lBlackBishop = new Bishop(false); Field[0][2] = lBlackBishop;
		Bishop* rBlackBishop = new Bishop(false); Field[0][5] = rBlackBishop;
		Queen* BlackQueen = new Queen(false); Field[0][3] = BlackQueen;
		King* bKing = new King(false); Field[0][4] = bKing;
		for (int i = 0; i < width; i++) {
			Pawn* whitePawn = new Pawn(true);
			Field[6][i] = whitePawn;
			Pawn* blackPawn = new Pawn(false);
			Field[1][i] = blackPawn;
		}
	}
	vector<string> Memory;
	void Draw() {
		system("cls");
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (Field[i][j] == nullptr) { cout << "· "; Memory[i][j] = '·'; }
				else { cout << Field[i][j]->symbol << " "; Memory[i][j] = Field[i][j]->symbol; }
			}
			cout << endl;
		}
	}

	~Deck() {
		for (auto& row : Field) {
			for (auto& fig : row) {
				delete fig;
			}
		}
	}
};

void Step(bool white,Deck & deck);


int main() {
	SetConsoleCP(1251);
	setlocale(LC_ALL, "rus");

	Deck deck;
	deck.StartPos();
	deck.Draw();
	bool whitePlayer = true;

	while (true) {
		Step(whitePlayer, deck);
		Step(!whitePlayer, deck);
	}
	return 0;
}

void Step(bool white, Deck & deck) {
	if (white) cout << "Ходят белые" << endl;
	else cout << "Ходят черные" << endl;
	while (true) {
		cout << "\nВыберите фигуру для хода\n";
		int y;
		int x;
		cin >> y;
		cin >> x;
		if (y < 0 || y >= height || x < 0 || x >= width || deck.Field[y][x] == nullptr || deck.Field[y][x]->isWhite != white) {
			cout << "Некорректный выбор клетки." << endl;
			continue;
		}
		deck.Field[y][x]->Vars(y, x, deck.Memory, deck.Field);
		cout << "\nВыберите куда сходить\n";
		int endy;
		int endx;
		cin >> endy;
		cin >> endx;
		if (deck.Memory[endy][endx] == '+') {
			delete deck.Field[endy][endx];
			deck.Field[endy][endx] = deck.Field[y][x];
			deck.Field[y][x] = nullptr;
			deck.Draw();
			break;
		}
		else {
			cout << "Некорректный ход\n";
			deck.Draw();
		}
	}
}