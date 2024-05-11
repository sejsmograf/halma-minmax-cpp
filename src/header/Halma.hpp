#pragma once

#include "./Board.hpp"
#include "./FieldType.hpp"

class Halma {
public:
    static const FieldType PLAYER_ONE = FieldType::WHITE;
    static const FieldType PLAYER_TWO = FieldType::BLACK;
    Halma();
    void printBoard() const;
    void switchTurn();
    void makeMove(piece_move move);
    void makeMockMove(piece_move move);
    void undoMockMove(piece_move move);
    bool checkWinner(FieldType playerType);
    void gameFinished();
    Board &getBoard();
    FieldType getCurrentPlayer();

    bool isGameOver;

private:
    FieldType currentPlayer;
    Board board;
};
