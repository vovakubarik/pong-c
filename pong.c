#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define START_POS_X 39
#define START_POS_Y 10
#define START_POS_RACKET_Y 12
#define LEFT_CAR_POS 5
#define RIGHT_CAR_POS 75
#define SCORE 21

void drawborder();
void drawline(int bx, int check);
void drawscreen(int bx, int by, int car_1_y, int car_2_y, int points1, int points2);
void draw_score(int points1, int points2);
void draw_winner(int player);
int check_goal(int bx);
int check_winner(int points1, int points2);
int check_borders(int by);
int check_racket(int bx, int by, int car_1_y, int car_2_y);

int main(void) {
    int bx = START_POS_X, by = START_POS_Y;
    int car_1_y = START_POS_RACKET_Y, car_2_y = START_POS_RACKET_Y;
    int ball_direction_x = 1, ball_direction_y = 1;
    int points1 = 0, points2 = 0;
    int c;
    drawscreen(bx, by, car_1_y, car_2_y, points1, points2);
    while (1) {
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == 'z' && car_1_y <= HEIGHT - 3) {
                car_1_y += 1;
            } else if (c == 'a' && car_1_y > 1) {
                car_1_y -= 1;
            } else if (c == 'm' && car_2_y <= HEIGHT - 3) {
                car_2_y += 1;
            } else if (c == 'k' && car_2_y > 1) {
                car_2_y -= 1;
            } else if (c != 132) {
                printf("Wrong key!");
            }
            while (c == 'z' || c == 'a' || c == 'm' || c == 'k' || c == ' ') {
                printf("\e[1;1H\e[2J");
                bx += ball_direction_x;
                by += ball_direction_y;
                drawscreen(bx, by, car_1_y, car_2_y, points1, points2);
                c = 132;
            }
            if (check_racket(bx, by, car_1_y, car_2_y)) {
                ball_direction_x *= -1;
            }
            if (check_borders(by)) {
                ball_direction_y *= -1;
            }
            if (check_goal(bx) == 2) {
                points1 += 1;
                bx = START_POS_X;
                by = START_POS_Y;
            }
            if (check_goal(bx) == 1) {
                points2 += 1;
                bx = START_POS_X;
                by = START_POS_Y;
            }
            if (check_winner(points1, points2)) {
                printf("\e[1;1H\e[2J");
                draw_winner(check_winner(points1, points2));
                return 0;
            }
        }
    }
    return 0;
}

void drawborder() {
    for (int x = 1; x <= WIDTH + 2; x++) {
        printf("#");
    }
    printf("\n");
}

void drawline(int bx, int check) {
    int car = 124;
    int ball = 42;
    printf("|");
    for (int x = 1; x <= WIDTH; x++) {
        if (x == bx && check / 10 % 10 == 1) {
            printf("%c", (char)ball);
        } else if (x == WIDTH / 2) {
            printf(":");
        } else if (x == LEFT_CAR_POS && check / 100 == 1) {
            printf("%c", (char)car);
        } else if (x == RIGHT_CAR_POS && check % 10 == 1) {
            printf("%c", (char)car);
        } else {
            printf(" ");
        }
    }
    printf("|\n");
}

void drawscreen(int bx, int by, int car_1_y, int car_2_y, int points1, int points2) {
    int check = 0;
    drawborder();
    for (int y = 1; y <= HEIGHT; y++) {
        if (y == by) {
            check += 10;
        }
        if (y == car_1_y || y == car_1_y + 1 || y == car_1_y + 2) {
            check += 100;
        }
        if (y == car_2_y || y == car_2_y + 1 || y == car_2_y + 2) {
            check += 1;
        }
        drawline(bx, check);
        check = 0;
    }
    drawborder();
    draw_score(points1, points2);
}

void draw_score(int points1, int points2) {
    for (int i = 1; i <= WIDTH; i++) {
        if (i == 3) {
            printf("Player 1: %02d", points1);
            i += 12;
        } else if (i == WIDTH - 11) {
            printf("Player 2: %02d", points2);
            i += 12;
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

void draw_winner(int player) {
    if (player == 1) {
        printf("Player 1 won!\n");
    }
    if (player == 2) {
        printf("Player 2 won!\n");
        }
}

int check_goal(int bx) {
    if (bx == 1) {
        return 1;
    }
    if (bx == WIDTH) {
        return 2;
    }
    return 0;
}

int check_winner(int points1, int points2) {
    if (points1 == SCORE) {
        return 1;
    }
    if (points2 == SCORE) {
        return 2;
    }
    return 0;
}

int check_borders(int by) {
    if (by == 1 || by == HEIGHT) {
        return 1;
    }
    return 0;
}

int check_racket(int bx, int by, int car_1_y, int car_2_y) {
    for (int i = car_1_y; i < car_1_y + 2; i++) {
        if (by == i && bx == LEFT_CAR_POS + 1) {
            return 1;
        }
    }
    for (int i = car_2_y; i < car_2_y + 2; i++) {
        if (by == i && bx == RIGHT_CAR_POS - 1) {
            return 1;
        }
    }
    return 0;
}