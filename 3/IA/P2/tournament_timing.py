"""Illustration of tournament.

Authors:
    Alejandro Bellogin <alejandro.bellogin@uam.es>

"""


from __future__ import annotations  # For Python 3.7

import time
import numpy as np
from game import Player, TwoPlayerGameState, TwoPlayerMatch
from heuristic import simple_evaluation_function
from reversi import Reversi
from tournament import StudentHeuristic, Tournament


class Heuristic1(StudentHeuristic):

    def get_name(self) -> str:
        return "dummy"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        # Use an auxiliary function.
        return self.dummy(123)

    def dummy(self, n: int) -> int:
        return n + 4


class Heuristic2(StudentHeuristic):

    def get_name(self) -> str:
        return "random"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
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

    """
    game = TicTacToe(
        player1=player1,
        player2=player2,
        dim_board=dim_board
    )
    """
    game = Reversi(
        player1=player1,
        player2=player2,
        height=dim_board,
        width=dim_board,
    )

    game_state = TwoPlayerGameState(
        game=game,
        board=initial_board,
        initial_player=initial_player,
    )

    return TwoPlayerMatch(game_state, max_sec_per_move=1000, gui=False)


# Change with Heuristic1 to run Heuristic1
# instead of our heuristic
use_student = True  # change to use student instead of the basic heuristic
strats = {}
if not use_student:
    strats = {'opt1': [Heuristic1], 'opt2': [Heuristic1]}
alphabeta = False  # change based on tournament.py
for depth in [3, 4]:
    # The tours will run twice, one for max_depth 3 and
    # another one for max_depth 4
    tour = Tournament(max_depth=depth, init_match=create_match)
    if use_student:
        our_strat = tour.load_strategies_from_folder(
                folder=".\\heuristic_tournaments\\", max_strat=3
            )['2391_p2_10_almarza_gonzalez.py'][0]
        strats = {'opt1': [our_strat], 'opt2': [our_strat]}
    print(f"Depth: {depth}")

    if alphabeta:
        print("Starting tournament with MinimaxAlphaBetaStrategy...")
    else:
        print("Starting tournament with MinimaxStrategy...")

    # Variables to compute the best, worst and total times
    best = np.inf
    worst = -np.inf
    total = 0

    # How many times should this be repeated
    n_times = 1
    print(f"Running {n_times} times")
    for i in range(n_times):
        # Equivalent to "starting the timer" in timeit
        start = time.time()
        tour.run(
            student_strategies=strats,
            increasing_depth=False,
            n_pairs=1,
            allow_selfmatch=False,
        )
        time_to_run = time.time() - start
        total += time_to_run
        if time_to_run < best:
            best = time_to_run
        if time_to_run > worst:
            worst = time_to_run

    print(f"Total time taken: {total}\nAverage : {total/n_times}\n" +
          f"Best: {best}\nWorst: {worst}")
