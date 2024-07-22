"""Game loop and state design pattern mockup.
"""

from typing import Callable, Any


def functional_while(
        predicate: Callable[[Any], bool],
        function: Callable[[Any], Any],
        accumulator: Any
        ) -> Any:
    """Functional while loop.

    Args:
        predicate (func): function returning boolean
        function (func): function returning
        accumulator (any): inital data to operate on.

    Returns:
        Any: accumulator end state
    """
    while predicate(accumulator):
        function(accumulator)
    return accumulator


def draw(game):
    """Side effects: draw per tick."""
    print("---------------------------")
    print(f"Time: {game['time']}")
    print(f"A pressed {game['a']} times")
    print(f"B pressed {game['b']} times")
    print("---------------------------")


def user_input(game):
    """Side effects: user input per tick."""
    # ---- Mock user input ---
    keypress = True
    key = "a"
    # ------------------------
    if keypress:
        if key == "a":
            game["a"] += 1


def update(game):
    """Per tick game update"""
    user_input(game)
    draw(game)
    game["time"] += 1
    return game


def main():
    game = {
       "a": 0,
       "b": 0,
       "time": 0,
    }
    game_end = {
        "a": 10,
        "b": 0
    }
    print("===========================")
    print("game init")
    print("===========================")
    functional_while(
        lambda game: not all(
            game[key] == game_end[key]
            for key in game
            if key != "time"
        ),
        update,
        game
    )
    print("===========================")
    print("game end")
    print("===========================")


if __name__ == "__main__":
    main()
