#include "./header/Halma.hpp"
#include "./header/Board.hpp"
#include "./header/FieldType.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

Halma::Halma(IHalmaPlayer *playerOne, IHalmaPlayer *playerTwo,
             vector<string> inputLines)
    : board(inputLines), currentPlayer(PLAYER_ONE), isGameOver(false) {
    if (playerOne == nullptr || playerTwo == nullptr) {
        throw invalid_argument("Canont initialize game with nullptr player");
    }
    setPlayerOne(playerOne);
    setPlayerTwo(playerTwo);
}

void Halma::printBoard() const { board.printBoard(); }

void Halma::switchTurn() {
    currentPlayer = (currentPlayer == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
}

void Halma::makeMove(piece_move move) {
    board.makeMove(move);
    if (checkWinner(currentPlayer)) {
        gameFinished();
    };
    switchTurn();
}
void Halma::setPlayerOne(IHalmaPlayer *player) {
    this->playerOne = player;
    player->setPlayer(PLAYER_ONE);
};
void Halma::setPlayerTwo(IHalmaPlayer *player) {
    this->playerTwo = player;
    player->setPlayer(PLAYER_TWO);
}

void Halma::makeMockMove(piece_move move) {
    board.makeMove(move);
    switchTurn();
}

void Halma::undoMockMove(piece_move move) {
    board.undoMove(move);
    switchTurn();
}

bool Halma::checkWinner(FieldType playerType) const {
    return board.playerPiecesInGoalCamp(playerType) == board.PIECE_COUNT;
}

void Halma::gameFinished() { isGameOver = true; }

int Halma::playGame(bool print) {
    int visitedNodes = 0;

    while (!isGameOver) {
        visitedNodes += playTurn(print);
    }

    return visitedNodes;
}

int Halma::playTurn(bool print) {
    search_result foundMove;
    if (currentPlayer == PLAYER_ONE) {
        foundMove = playerOne->chooseMove(*this);
    } else if (currentPlayer == PLAYER_TWO) {
        foundMove = playerTwo->chooseMove(*this);
    }

    makeMove(foundMove.move);
    if (print) {
        printBoard();
        std::cout << "\n\n";
    }
    return foundMove.visitedNodes;
}

Board &Halma::getBoard() { return board; }
FieldType Halma::getCurrentPlayer() { return currentPlayer; }
