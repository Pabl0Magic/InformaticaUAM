from game import (
    TwoPlayerGameState,
)
from tournament import (
    StudentHeuristic,
)


class BombaBatista(StudentHeuristic):
    # Informational variables
    name = "La Bomba Batista"
    version = "v1"

    # Configurable variables
    kill_factor = 5
    weight_factor = 1.5

    # Read-only variables: don't change!
    # the ordinal of 'a', precalculated
    ord_a = ord('a')

    # Weights obtained from
    # dhconnelly(dot)com/paip-python/docs/paip/othello.html#section-63
    weights = [
        120, -20,  20,   5,   5,  20, -20, 120,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        20,  -5,  15,   3,   3,  15,  -5,  20,
        5,  -5,   3,   3,   3,   3,  -5,   5,
        5,  -5,   3,   3,   3,   3,  -5,   5,
        20,  -5,  15,   3,   3,  15,  -5,  20,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        120, -20,  20,   5,   5,  20, -20, 120,
    ]

    def get_name(self) -> str:
        """Gets the name of the Heuristic

        Returns:
            str: The name of the heuristic
        """
        return f"{self.name} {self.version}"

    def obtain_proper_pos(self, move_code):
        """Obtains the proper position from a move_code

        Args:
            move_code (str): The weird tuple string
            that represents the move code

        Returns:
            (x, y): A real, numeric tuple of positions
        """
        x = int(move_code[1])
        y = ord(move_code[4]) - self.ord_a + 1
        return (x, y)

    def get_weight(self, state: TwoPlayerGameState) -> int:
        """Obtains the weight of a specific state move_code

        Args:
            state (TwoPlayerGameState): The state to be checked

        Returns:
            int: The weight
        """
        x, y = self.obtain_proper_pos(state.move_code)
        return self.weights[x - 1 + (y - 1) * 7]

    def compute_weights(self, state: TwoPlayerGameState, successors) -> int:
        """Compute the weight for the current state, provided
        the successors of this state (may be precomputed)

        Args:
            state (TwoPlayerGameState): The current state
            successors ([TwoPlayerGameState]): Array of successor states

        Returns:
            int: The computed weight
        """
        # Adapted from
        # dhconnelly(dot)com/paip-python/docs/paip/othello.html#section-65

        # Assume everything is not None.
        # First, start by checking our own weight
        result = self.get_weight(state)
        # Next, substract all the resulting weights that the
        # opponent might get
        # NOTE: this code is never run since
        # we believe our heuristic is
        # getting timed out.
        if successors:
            for successor_state in successors:
                result -= self.get_weight(successor_state)
        return result

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        """Main evaluation function for our main heuristic.
        This is what *we* believe is a good heuristic:

        The whole concept is this heuristic will focus
        on getting the best movements based in weights while
        also heavily considering the moves the opponent has in this
        round

        Args:
            state (TwoPlayerGameState): The current state

        Returns:
            float: The heuristic evaluation result
        """
        # First, check if move_code is not None
        if state.move_code:
            successors = state.game.generate_successors(state)
            opponent_options = len(successors)
            # KILLER MOVE :slash:
            if opponent_options == 0:
                # IT'S OVER 9000!
                return 9000
            # More options for the opponent means less
            # chance of this state for getting picked
            wei = self.compute_weights(state, None) * self.weight_factor
            total = wei - opponent_options * self.kill_factor
            return total
        else:
            return -999.0


class TheJoker(StudentHeuristic):
    # Weights obtained from
    # http://dhconnelly.com/paip-python/docs/paip/othello.html#section-63
    weights = [
        120, -20,  20,   5,   5,  20, -20, 120,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        20,  -5,  15,   3,   3,  15,  -5,  20,
        5,  -5,   3,   3,   3,   3,  -5,   5,
        5,  -5,   3,   3,   3,   3,  -5,   5,
        20,  -5,  15,   3,   3,  15,  -5,  20,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        120, -20,  20,   5,   5,  20, -20, 120,
    ]

    ord_a = ord("a")

    def get_name(self) -> str:
        """Gets the name of the Heuristic

        Returns:
            str: The name of the heuristic
        """
        # search the movie name ye
        return "The_Joker (Jared Leto)"

    def obtain_proper_pos(self, move_code):
        """Obtains the proper position from a move_code

        Args:
            move_code (str): The weird tuple string
            that represents the move code

        Returns:
            (x, y): A real, numeric tuple of positions
        """
        x = int(move_code[1])
        y = ord(move_code[4]) - self.ord_a + 1
        return (x, y)

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        """Main evaluation function for our testing, very bad heuristic

        This heuristic aims to pick the worst possible movements
        based on weights.

        Args:
            state (TwoPlayerGameState): The current state

        Returns:
            float: The heuristic evaluation result
        """
        # Use an auxiliary function.
        if state.move_code:
            x, y = self.obtain_proper_pos(state.move_code)
            idx = int(x) - 1 + (y - 1) * 7
            wei = self.weights[idx]
            return -wei
        else:
            return -999.0


class JokerBabysitter(StudentHeuristic):
    # Weights obtained from
    # http://dhconnelly.com/paip-python/docs/paip/othello.html#section-63
    weights = [
        120, -20,  20,   5,   5,  20, -20, 120,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        20,  -5,  15,   3,   3,  15,  -5,  20,
        5,  -5,   3,   3,   3,   3,  -5,   5,
        5,  -5,   3,   3,   3,   3,  -5,   5,
        20,  -5,  15,   3,   3,  15,  -5,  20,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        120, -20,  20,   5,   5,  20, -20, 120,
    ]

    ord_a = ord("a")

    def get_name(self) -> str:
        """Gets the name of the Heuristic

        Returns:
            str: The name of the heuristic
        """
        # if this wins, the tournament is rigged
        return "Joker_Babysitter"

    def obtain_proper_pos(self, move_code):
        """Obtains the proper position from a move_code

        Args:
            move_code (str): The weird tuple string
            that represents the move code

        Returns:
            (x, y): A real, numeric tuple of positions
        """
        x = int(move_code[1])
        y = ord(move_code[4]) - self.ord_a + 1
        return (x, y)

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        """Main evaluation function for our very bad heuristic

        The whole point of this heuristic is to give the opponent more options.
        We believe that, if this heuristic wins, the tournament is very rigged
        towards the worse heuristics.

        Args:
            state (TwoPlayerGameState): The current state

        Returns:
            float: The heuristic evaluation result
        """
        # Use an auxiliary function.
        if state.move_code:
            x, y = self.obtain_proper_pos(state.move_code)
            idx = int(x) - 1 + (y - 1) * 7
            wei = self.weights[idx]
            # this literally gives the opponents
            # more moves to choose, lol
            oppo_moves = len(state.game.generate_successors(state))
            return -wei + oppo_moves * 10
        else:
            return -999.0
