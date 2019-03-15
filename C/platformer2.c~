#define _POSIX_C_SOURCE 199309L
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER '*'
#define BLOCK '='
#define EMPTY ' '

enum player_state {GROUND, AIR};

int y_max, x_max;

const double g = -9.805; /* m*s^(-2) */
const double dt = 0.5;  /* s */

struct player {
	double y;
	double x;
	double v_y;
	double v_x;
	double a_y;
	double a_x;
	int state;
	void (*move_player)(struct player *);
};

/* move_is_okay: check to see if a move is allowable */
static char move_is_okay(int y, int x) {
	chtype testch = mvinch(y, x) & A_CHARTEXT;
	return (testch == EMPTY || testch == PLAYER);
}

/* move_left: move the character left and delete the last position */
static void move_player(struct player *p) {
	/* compute new coordinates */
	double y_new = (double)LINES - 1.0 - (p->y + p->v_y*dt + 0.5*(p->a_y+g)*dt*dt);
	double x_new = p->x + p->v_x*dt + 0.5*(p->a_x)*dt*dt;

	if (move_is_okay(y_new, x_new)) {
		/* erase */
		mvaddch(p->y, p->x, EMPTY);

		/* coordinates */
		p->y = y_new;
		p->x = x_new;

		/* compute new velocities */
		p->v_y = p->a_y*dt;
		p->v_x = p->a_x*dt;

		/* all accelerations will be constants, only changed through collision or
		 * player input */

		/* make the player move */
		mvaddch(p->y, p->x, PLAYER);
		refresh();
	}
	/* if new coordinates will cause a collision, player stops moving */
	else {
		p->v_y = 0;
		p->v_x = 0;
		p->a_y = 0;
		p->a_x = 0;
	}

	/*
	   if (p->x > 0 && move_is_okay(p->y, p->x-1)) {
	   mvaddch(p->y, p->x, EMPTY);
	   p->x--;
	   }
	   */
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
	const struct timespec ts = {0, 16666666};

	/* divide by CLOCKS_PER_SEC to get time in seconds */
	/*clock_t start_time;*/

	start_ncurses();

	/* initialize player */
	getmaxyx(stdscr, y_max, x_max);
	player.y = y_max/2;
	player.x = x_max/2;
	player.state = GROUND;
	player.move_player = move_player;
	mvaddch(player.y, player.x, PLAYER);
	refresh();

	while ((c = getch()) != 'q' && c != 'Q') {
		switch (c) {
			case KEY_UP: case 'w': case 'W': case ' ':
				player.a_y = +15.0;
				break;
			case KEY_LEFT: case 'a': case 'A':
				player.a_x = -5.0;
				break;
			case KEY_RIGHT: case 'd': case 'D':
				player.a_x = +5.0;
				break;
			case ERR:
				player.v_y = 0;
				player.v_x = 0;
				player.a_y = 0;
				player.a_x = 0;
				break;
			default:
				break;
		}
		player.move_player(&player);
		refresh();
		nanosleep(&ts, NULL);
	}

	endwin(); /* tell ncurses to clean up */

	exit(EXIT_SUCCESS);
}
