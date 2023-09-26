"""Illustration of tournament.

Authors:
    Alejandro Bellogin <alejandro.bellogin@uam.es>

"""

from __future__ import annotations  # For Python 3.7

import numpy as np

from game import Player, TwoPlayerGameState, TwoPlayerMatch
from heuristic import simple_evaluation_function
from reversi import Reversi
from tournament import StudentHeuristic, Tournament


class Heuristic1(StudentHeuristic):
    def get_name(self) -> str:
        return "solution1"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        # Use an auxiliary function.
        print(state)
        return self.dummy(123)

    def dummy(self, n: int) -> int:
        return n + 4


class Heuristic2(StudentHeuristic):

    def get_name(self) -> str:
        return "random"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        print(state)
        return float(np.random.rand())


class Heuristic3(StudentHeuristic):

    def get_name(self) -> str:
        return "heuristic"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        return simple_evaluation_function(state)


def create_match(player1: Player, player2: Player) -> TwoPlayerMatch:

    dim_board = 8

    initial_board = None
    initial_player = player1

    game = Reversi(
        player1=player1,
        player2=player2,
        width=dim_board,
        height=dim_board,
    )

    game_state = TwoPlayerGameState(
        game=game,
        board=initial_board,
        initial_player=initial_player,
    )

    return TwoPlayerMatch(game_state, max_sec_per_move=1000, gui=False)


tour = Tournament(max_depth=3, init_match=create_match)
strats = tour.load_strategies_from_folder(
        folder=".\\heuristic_tournaments\\", max_strat=3
    )

n = 1

scores, totals, names = tour.run(
    student_strategies=strats,
    increasing_depth=False,
    n_pairs=n,
    allow_selfmatch=True,
)

print(
    'Results for tournament where each game is repeated '
    + '%d=%dx2 times, alternating colors for each player' % (2 * n, n),
)

# print(totals)
# print(scores)

print('\ttotal:', end='')
for name1 in names:
    print('\t%s' % (name1), end='')
print()
for name1 in names:
    print('%s\t%d:' % (name1, totals[name1]), end='')
    for name2 in names:
        if name1 == name2:
            print('\t---', end='')
        else:
            print('\t%d' % (scores[name1][name2]), end='')
    print()
