#include "./header/Halma.hpp"
#include "./header/Board.hpp"
#include "./header/FieldType.hpp"
#include <algorithm>
#include <iostream>

Halma::Halma(IHalmaPlayer *playerOne, IHalmaPlayer *playerTwo,
             vector<string> inputLines)
    : board(inputLines), currentPlayer(PLAYER_ONE), isGameOver(false) {
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
    if (player == nullptr) {
        return;
    }
    this->playerOne = player;
    player->setPlayer(PLAYER_ONE);
};
void Halma::setPlayerTwo(IHalmaPlayer *player) {
    if (player == nullptr) {
        return;
    }
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
    if (playerOne != nullptr && playerTwo != nullptr) {
        while (!isGameOver) {
            visitedNodes += playTurn();
            if (print) {
                printBoard();
                cout << "\n\n\n";
            }
        }
    } else if (playerOne != nullptr) {
        playTurn();
        if (print) {
            printBoard();
            cout << "\n\n\n";
        }
    }

    return visitedNodes;
}

int Halma::playTurn() {
    search_result foundMove;
    if (currentPlayer == PLAYER_ONE && playerOne != nullptr) {
        search_result foundMove = playerOne->chooseMove(*this);
        makeMove(foundMove.move);
    } else if (currentPlayer == PLAYER_TWO && playerTwo != nullptr) {
        search_result foundMove = playerTwo->chooseMove(*this);
        makeMove(foundMove.move);
    }

    return foundMove.visitedNodes;
}

Board &Halma::getBoard() { return board; }
FieldType Halma::getCurrentPlayer() { return currentPlayer; }
