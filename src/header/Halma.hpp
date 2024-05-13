#pragma once

#include "../interface/IHalmaPlayer.hpp"
#include "./Board.hpp"
#include "./FieldType.hpp"
#include <string>

class Halma {
public:
    static const FieldType PLAYER_ONE = FieldType::WHITE;
    static const FieldType PLAYER_TWO = FieldType::BLACK;
    Halma(IHalmaPlayer *playerOne = nullptr, IHalmaPlayer *playerTwo = nullptr,
          vector<string> inputLines = {});
    void printBoard() const;
    void switchTurn();
    void makeMove(piece_move move);
    void makeMockMove(piece_move move);
    void undoMockMove(piece_move move);
    void setPlayerOne(IHalmaPlayer *player);
    void setPlayerTwo(IHalmaPlayer *player);
    bool checkWinner(FieldType playerType) const;
    void gameFinished();
    int playGame(bool printBoard = true);
    int playTurn();
    Board &getBoard();
    FieldType getCurrentPlayer();
    bool isGameOver;

private:
    IHalmaPlayer *playerOne;
    IHalmaPlayer *playerTwo;
    FieldType currentPlayer;
    Board board;
};
