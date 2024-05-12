#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "./FieldType.hpp"

using namespace std;

struct piece_move {
    int fromRow, fromCol;
    int toRow, toCol;
};

class Board {
public:
    static const int BOARD_SIZE = 16;
    static const int PIECE_COUNT = 19;
    static const vector<pair<int, int>> DIRECTIONS;
    static const unordered_map<FieldType, vector<pair<int, int>>> PLAYER_CAMPS;

    Board(vector<string> inputLines);
    vector<piece_move> getPlayerMoves(FieldType playerType) const;
    vector<pair<int, int>> getPlayerPositions(FieldType playerType) const;
    vector<pair<int, int>> getPlayerGoalCamp(FieldType playerType) const;
    int playerPiecesInGoalCamp(FieldType playerType) const;
    pair<int, int> getEmptyGoal(vector<pair<int, int>> playerGoalCamp) const;
    void makeMove(piece_move move);
    void undoMove(piece_move move);
    void printBoard() const;

private:
    FieldType state[BOARD_SIZE][BOARD_SIZE];
    vector<piece_move> getPieceMoves(int row, int col) const;
    vector<piece_move> getDirectMoves(int row, int col) const;
    vector<piece_move> getJumpMoves(int row, int col) const;
    bool isWithinBounds(int row, int col) const;
    void initializeBoard(vector<string> inputLines);
    void initializeFromStdInput(vector<string> inputLines);
    void initializeDefault();
};
