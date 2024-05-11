#include "./header/AlphaBetaPlayer.hpp"
#include "interface/BoardEvaluator.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

AlphaBetaPlayer::AlphaBetaPlayer(const BoardEvaluator &boardEvaluator,
                                 int depth, FieldType maximizingPlayer)
    : boardEvaluator(boardEvaluator), depth(depth),
      maximizingPlayer(maximizingPlayer){};

void AlphaBetaPlayer::makeMove(Halma &game) {
    pair<float, piece_move> minmaxResult = alphabeta(
        game, depth, maximizingPlayer, boardEvaluator,
        -numeric_limits<float>::infinity(), numeric_limits<float>::infinity());

    piece_move chosenMove = minmaxResult.second;
    cout << "Player " << this->maximizingPlayer
         << " has chose move with evaluation: " << minmaxResult.first << "\n\n";
    game.makeMove(chosenMove);
};

pair<float, piece_move>
AlphaBetaPlayer::alphabeta(Halma &game, int depth, FieldType maximizingPlayer,
                           const BoardEvaluator &boardEvaluator,
                           float alpha = -numeric_limits<float>::infinity(),
                           float beta = numeric_limits<float>::infinity()) {

    Board &board = game.getBoard();
    if (depth == 0 || game.checkWinner(maximizingPlayer)) {
        return {boardEvaluator.evaluateBoard(board, maximizingPlayer),
                piece_move(-1, -1, -1, -1)};
    }

    FieldType currentPlayer = game.getCurrentPlayer();
    bool maximize = currentPlayer == maximizingPlayer;
    float bestEvaluation = maximize ? -numeric_limits<float>::infinity()
                                    : numeric_limits<float>::infinity();
    piece_move bestMove = {-1, -1, -1, -1};

    vector<piece_move> allMoves = board.getPlayerMoves(currentPlayer);

    for (piece_move move : allMoves) {
        game.makeMockMove(move);
        float evaluation = alphabeta(game, depth - 1, maximizingPlayer,
                                     boardEvaluator, alpha, beta)
                               .first;
        game.undoMockMove(move);

        if (maximize) {
            if (evaluation > bestEvaluation) {
                bestEvaluation = evaluation;
                bestMove = move;
            }
            alpha = max(alpha, evaluation);
            if (beta <= alpha) {
                break;
            }
        } else {
            if (evaluation < bestEvaluation) {
                bestEvaluation = evaluation;
                bestMove = move;
            }
            beta = min(beta, evaluation);
            if (beta <= alpha) {
                break;
            }
        }
    }

    return {bestEvaluation, bestMove};
};
