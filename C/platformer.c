#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER '*'
#define BLOCK '='
#define EMPTY ' '

enum player_state {GROUND, AIR};

int y_max, x_max;

struct player {
	int x;
	int y;
	int v_x;
	int v_y;
	int a_x;
	int a_y;
	int state;
	void (*jump)(void);
	void (*move_left)(struct player *);
	void (*move_right)(struct player *);
};

/* move_is_okay: check to see if a move is allowable */
static char move_is_okay(int y, int x) {
	chtype testch = mvinch(y, x) & A_CHARTEXT;
	return (testch == EMPTY);
}

/* move_left: move the character left and delete the last position */
static void move_left(struct player *p) {
	if (p->x > 0 && move_is_okay(p->y, p->x-1)) {
		mvaddch(p->y, p->x, EMPTY);
		p->x--;
	}
}

/* move_left: move the character left and delete the last position */
static void move_right(struct player *p) {
	if (p->x < x_max && move_is_okay(p->y, p->x+1)) {
		mvaddch(p->y, p->x, EMPTY);
		p->x++;
	}
}

/* start_ncurses: initialize ncurses library */
void start_ncurses(void) {
	initscr();
	keypad(stdscr, TRUE);
	intrflush(stdscr, FALSE);
	nodelay(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
	curs_set(0);
}

int main(void) {
	int c;
	struct player player;
	clock_t start_time;
	clock_t current_time;
	clock_t interval;

	start_ncurses();

	/* initialize player */
	getmaxyx(stdscr, y_max, x_max);
	player.y = y_max-1;
	player.x = 0;
	player.state = GROUND;
	player.move_left = move_left;
	player.move_right = move_right;
	mvaddch(player.y, player.x, PLAYER);

	do {
		c = getch();
		if (c != ERR) {
			switch (c) {
				case KEY_UP: case 'w': case 'W': case ' ':
					break;
				case KEY_LEFT: case 'a': case 'A':
					player.move_left(&player);
					break;
				case KEY_RIGHT: case 'd': case 'D':
					player.move_right(&player);
					break;
				default:
					break;
			}
			mvaddch(player.y, player.x, PLAYER);
			refresh();
		}
	}
	while (c != 'q' && c != 'Q');

	endwin(); /* tell ncurses to clean up */

	exit(EXIT_SUCCESS);
}
