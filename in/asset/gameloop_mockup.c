#include <cstdio>

typedef struct {
    int a;
    int b;
    int time;
} Game;

int predicate_game_end(Game* game) {
    if (game->a == 10 && game->b == 0) {
        return 0;
    }
    return 1;
}


void draw(Game* game) {
    printf("---------------------------\n");
    printf("Time: %d\n", game->time);
    printf("A pressed %d times\n", game->a);
    printf("B pressed %d times\n", game->b);
    printf("---------------------------\n");
}

void user_input(Game* game) {
    // ---- Mock user input ---
    int keypress = 1;
    char key = 'a';
    // ------------------------
    if (keypress == 1) {
        if (key == 'a') {
            game->a += 1;
        }
    }
}

void function(Game* game) {
    user_input(game);
    draw(game);
    game->time += 1;
}

void functional_while(int (*predicate_game_end)(Game*), void (*function)(Game*), Game* accumulator) {
    while (predicate_game_end(accumulator) == 1) {
        function(accumulator);
    }
}

int main() {
    Game game = {
        .a = 0,
        .b = 0,
        .time = 0
    };
    Game game_end = {
        .a = 10,
        .b = 0
    };

    printf("===========================\n");
    printf("game init\n");
    printf("===========================\n");

    functional_while(predicate_game_end, function, &game);

    printf("===========================\n");
    printf("game end\n");
    printf("===========================\n");

    return 0;
}
