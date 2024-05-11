#include "./header/Board.hpp"
#include "./header/FieldType.hpp"

#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// clang-format off
const unordered_map<FieldType, vector<pair<int, int>>>
    Board::PLAYER_CAMPS = {
	{FieldType::BLACK, {
		{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4},
		{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4},
		{2, 0}, {2, 1}, {2, 2}, {2, 3},
		{3, 0}, {3, 1}, {3, 2},
		{4, 0}, {4, 1}
    }},
	{FieldType::WHITE, {
		{15, 15}, {15, 14}, {15, 13}, {15, 12}, {15, 11},
		{14, 15}, {14, 14}, {14, 13}, {14, 12}, {14, 11},
		{13, 15}, {13, 14}, {13, 13}, {13, 12},
		{12, 15}, {12, 14}, {12, 13},
		{11, 15}, {11, 14}
	}}
};

const vector<pair<int, int>> Board::DIRECTIONS = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};
// clang-format on

Board::Board() { initializeDefaultBoard(); };

vector<piece_move> Board::getPlayerMoves(FieldType playerType) const {
    vector<pair<int, int>> playerPositions = getPlayerPositions(playerType);
    vector<piece_move> allMoves;

    for (const pair<int, int> &position : playerPositions) {
        int row = position.first;
        int col = position.second;

        vector<piece_move> moves = getPieceMoves(row, col);
        allMoves.insert(allMoves.end(), moves.begin(), moves.end());
    }
    return allMoves;
}

vector<pair<int, int>> Board::getPlayerPositions(FieldType playerType) const {
    vector<pair<int, int>> positions;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (state[row][col] == playerType) {
                positions.push_back({row, col});
            }
        }
    }
    return positions;
};

vector<pair<int, int>> Board::getPlayerGoalCamp(FieldType playerType) const {
    FieldType opponent =
        playerType == FieldType::BLACK ? FieldType::WHITE : FieldType::BLACK;
    return PLAYER_CAMPS.at(opponent);
}

int Board::playerPiecesInGoalCamp(FieldType playerType) const {
    int count = 0;
    vector<pair<int, int>> goalCamp = getPlayerGoalCamp(playerType);
    for (const pair<int, int> &position : goalCamp) {
        if (state[position.first][position.second] == playerType) {
            count++;
        }
    }

    return count;
};

pair<int, int>
Board::getEmptyGoal(vector<pair<int, int>> playerGoalCamp) const {
    for (const pair<int, int> &position : playerGoalCamp) {
        int row = position.first;
        int col = position.second;
        if (state[row][col] == FieldType::EMPTY) {
            return {row, col};
        }
    }
    return playerGoalCamp[0];
};

void Board::makeMove(piece_move move) {
    state[move.toRow][move.toCol] = state[move.fromRow][move.fromCol];
    state[move.fromRow][move.fromCol] = FieldType::EMPTY;
}

void Board::undoMove(piece_move move) {
    state[move.fromRow][move.fromCol] = state[move.toRow][move.toCol];
    state[move.toRow][move.toCol] = FieldType::EMPTY;
}

void Board::printBoard() const {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            FieldType type = state[row][col];
            if (type == FieldType::EMPTY) {
                cout << "."
                     << " ";
            } else {
                cout << state[row][col] << " ";
            }
        }
        cout << "\n";
    }
}

vector<piece_move> Board::getPieceMoves(int row, int col) const {
    vector<piece_move> moves = getDirectMoves(row, col);
    vector<piece_move> jumpMoves = getJumpMoves(row, col);
    for (piece_move move : jumpMoves) {
        moves.push_back(move);
    }
    return moves;
};

vector<piece_move> Board::getDirectMoves(int row, int col) const {
    vector<piece_move> directMoves;
    for (pair<int, int> direction : DIRECTIONS) {
        int adjRow = row + direction.first;
        int adjCol = col + direction.second;
        if (isWithinBounds(adjRow, adjCol) &&
            state[adjRow][adjCol] == FieldType::EMPTY) {
            piece_move move = {row, col, adjRow, adjCol};
            directMoves.push_back(move);
        }
    }
    return directMoves;
};

vector<piece_move> Board::getJumpMoves(int row, int col) const {
    vector<piece_move> jumpMoves;

    queue<pair<int, int>> toVisit;
    set<pair<int, int>> visited;

    toVisit.push({row, col});
    visited.insert({row, col});

    while (!toVisit.empty()) {
        pair<int, int> currPos = toVisit.front();
        toVisit.pop();

        for (pair<int, int> direction : DIRECTIONS) {
            int adjRow = currPos.first + direction.first;
            int adjCol = currPos.second + direction.second;
            if (!isWithinBounds(adjRow, adjCol) ||
                state[adjRow][adjCol] == FieldType::EMPTY) {
                continue;
            }
            int jumpRow = adjRow + direction.first;
            int jumpCol = adjCol + direction.second;

            if (!isWithinBounds(jumpRow, jumpCol) ||
                state[jumpRow][jumpCol] != FieldType::EMPTY) {
                continue;
            }

            if (!visited.contains({jumpRow, jumpCol})) {
                visited.insert({jumpRow, jumpCol});
                toVisit.push({jumpRow, jumpCol});
                piece_move move = {row, col, jumpRow, jumpCol};
                jumpMoves.push_back(move);
            }
        }
    }
    return jumpMoves;
};

bool Board::isWithinBounds(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

void Board::initializeDefaultBoard() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            state[row][col] = FieldType::EMPTY;
        }
    }

    for (const pair<int, int> &pos : PLAYER_CAMPS.at(FieldType::BLACK)) {
        int row = pos.first;
        int col = pos.second;
        state[row][col] = FieldType::BLACK;
    }

    for (const pair<int, int> &pos : PLAYER_CAMPS.at(FieldType::WHITE)) {
        int row = pos.first;
        int col = pos.second;
        state[row][col] = FieldType::WHITE;
    }
};
