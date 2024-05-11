#include "Halma.hpp"
#include "Board.hpp"
#include "FieldType.hpp"

Halma::Halma() : board(), currentPlayer(PLAYER_ONE), isGameOver(false) {}

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

void Halma::makeMockMove(piece_move move) {
    board.makeMove(move);
    switchTurn();
}

void Halma::undoMockMove(piece_move move) {
    board.undoMove(move);
    switchTurn();
}

bool Halma::checkWinner(FieldType playerType) {
    return board.playerPiecesInGoalCamp(playerType) == board.PIECE_COUNT;
}

void Halma::gameFinished() { isGameOver = true; }

Board &Halma::getBoard() { return board; }
FieldType Halma::getCurrentPlayer() { return currentPlayer; }
