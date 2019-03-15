#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <curses.h>
#include <stdlib.h>

#define ALIVE 'o'
#define DEAD ' '

/* initialize_map: initialize the map to contain only DEAD cells */
void initialize_map(void) {
	int y;
	for (y = 0; y < LINES; y++) {
		mvhline(y, 0, DEAD, COLS);
	}
}

/* add_glider: adds a glider at x, y, where x and y are the leftmost and
 * uppermost corner of the object */
void add_glider(int y, const int x) {
	/* make sure there's enough space */
	if (y > LINES - 3 || x > COLS - 3) {
		endwin();
		perror("add_glider: insufficient screen space");
		exit(EXIT_FAILURE);
	}

	/* top row */
	mvaddch(y,   x, DEAD);
	mvaddch(y, x+1, ALIVE);
	mvaddch(y, x+2, DEAD);

	/* middle row */
	y++;
	mvaddch(y,   x, DEAD);
	mvaddch(y, x+1, DEAD);
	mvaddch(y, x+2, ALIVE);

	/* bottom row */
	y++;
	mvaddch(y,   x, ALIVE);
	mvaddch(y, x+1, ALIVE);
	mvaddch(y, x+2, ALIVE);

	refresh();
}

/* add_small_exploder: adds a small exploder at x, y, where x and y are the
 * leftmost and uppermost corner of the object */
void add_small_exploder(int y, const int x) {
	if (y > LINES - 4 || x > COLS - 3) {
		endwin();
		perror("add_small_exploder: insufficient screen space");
		exit(EXIT_FAILURE);
	}

	/* top row */
	mvaddch(y,   x, DEAD);
	mvaddch(y, x+1, ALIVE);
	mvaddch(y, x+2, DEAD);

	/* mid-top row */
	y++;
	mvaddch(y,   x, ALIVE);
	mvaddch(y, x+1, ALIVE);
	mvaddch(y, x+2, ALIVE);

	/* mid-bottom row */
	y++;
	mvaddch(y,   x, ALIVE);
	mvaddch(y, x+1, DEAD);
	mvaddch(y, x+2, ALIVE);

	/* bottom row */
	y++;
	mvaddch(y,   x, DEAD);
	mvaddch(y, x+1, ALIVE);
	mvaddch(y, x+2, DEAD);

	refresh();
}

void make_being(int y, int x, bool being[]);

#define CHECK_AND_INC(y, x)\
	if (mvinch((y), (x)) == ALIVE) {\
		count++;\
	}

/* count_neighbours: counts the number of neighbours that are alive */
unsigned int count_neighbours(int y, int x) {
	unsigned int count = 0;
	/* normal case, need to check all 8 neighbors */
	if (y != 0 && y != LINES - 1 && x != 0 && x != COLS - 1) {
		CHECK_AND_INC(y-1, x-1) /* up-left */
		CHECK_AND_INC(y-1,   x) /* up */
		CHECK_AND_INC(y-1, x+1) /* up-right */
		CHECK_AND_INC(  y, x-1) /* left */
		CHECK_AND_INC(  y, x+1) /* right */
		CHECK_AND_INC(y+1, x-1)	/* down-left */
		CHECK_AND_INC(y+1,   x) /* down */
		CHECK_AND_INC(y+1, x+1) /* down-right */
	}
	/* want edges to wrap so that the top connects to the bottom, left to
	 * right, etc. */
	/* top edge */
	else if (y == 0 && x != 0 && x != COLS - 1) {
		CHECK_AND_INC(LINES-1, x-1) /* up-left becomes bottom edge-left */
		CHECK_AND_INC(LINES-1,   x) /* up becomes bottom */
		CHECK_AND_INC(LINES-1, x+1) /* up-right becomes bottom-right */
		CHECK_AND_INC(      y, x-1) /* left */
		CHECK_AND_INC(      y, x+1) /* right */
		CHECK_AND_INC(    y+1, x-1) /* down-left */
		CHECK_AND_INC(    y+1,   x) /* down */
		CHECK_AND_INC(    y+1, x+1) /* down-right */
	}
	/* left edge */
	else if (x == 0 && y != 0 && y != LINES - 1) {
		CHECK_AND_INC(y-1, COLS-1) /* up-left becomes up-right edge */
		CHECK_AND_INC(y-1,      x) /* up */
		CHECK_AND_INC(y-1,    x+1) /* up-right */
		CHECK_AND_INC(  y, COLS-1) /* left becomes right edge */
		CHECK_AND_INC(  y,    x+1) /* right */
		CHECK_AND_INC(y+1, COLS-1) /* down-left becomes down-right edge */
		CHECK_AND_INC(y+1,      x) /* down */
		CHECK_AND_INC(y+1,    x+1) /* down-right */
	}
	/* right edge */
	else if (x == COLS - 1 && y != 0 && y != LINES - 1) {
		CHECK_AND_INC(y-1, x-1) /* etc. */
		CHECK_AND_INC(y-1,   x)
		CHECK_AND_INC(y-1,   0)
		CHECK_AND_INC(  y, x-1)
		CHECK_AND_INC(  y,   0)
		CHECK_AND_INC(y+1, x-1)
		CHECK_AND_INC(y+1,   x)
		CHECK_AND_INC(y+1,   0)
	}
	/* bottom edge */
	else if (y == LINES - 1 && x != 0 && x != COLS - 1) {
		CHECK_AND_INC(y-1, x-1)
		CHECK_AND_INC(y-1,   x)
		CHECK_AND_INC(y-1, x+1)
		CHECK_AND_INC(  y, x-1)
		CHECK_AND_INC(  y, x+1)
		CHECK_AND_INC(  0, x-1)
		CHECK_AND_INC(  0,   x)
		CHECK_AND_INC(  0, x+1)
	}
	/* top-left corner */
	else if (y == 0 && x == 0) {
		CHECK_AND_INC(LINES-1, COLS-1) /* up-left becomes bottom edge-right
										  edge */
		CHECK_AND_INC(LINES-1,      x) /* up becomes bottom-edge */
		CHECK_AND_INC(LINES-1,    x+1) /* up-right becomes bottom edge-right */
		CHECK_AND_INC(      y, COLS-1) /* left becomes right edge */
		CHECK_AND_INC(      y,    x+1) /* right */
		CHECK_AND_INC(    y+1, COLS-1) /* down-left becomes down-right edge */
		CHECK_AND_INC(    y+1,      x) /* down */
		CHECK_AND_INC(    y+1,    x+1) /* down-right */
	}
	/* top-right corner */
	else if (y == 0 && x == COLS - 1) {
		CHECK_AND_INC(LINES-1, x-1) /* etc. */
		CHECK_AND_INC(LINES-1,   x)
		CHECK_AND_INC(LINES-1,   0)
		CHECK_AND_INC(      y, x-1)
		CHECK_AND_INC(      y,   0)
		CHECK_AND_INC(    y+1, x-1)
		CHECK_AND_INC(    y+1,   x)
		CHECK_AND_INC(    y+1,   0)
	}
	/* bottom-left corner */
	else if (y == LINES - 1 && x == 0) {
		CHECK_AND_INC(y-1, COLS-1)
		CHECK_AND_INC(y-1,      x)
		CHECK_AND_INC(y-1,    x+1)
		CHECK_AND_INC(  y, COLS-1)
		CHECK_AND_INC(  y,    x+1)
		CHECK_AND_INC(  0, COLS-1)
		CHECK_AND_INC(  0,      x)
		CHECK_AND_INC(  0,    x+1)
	}
	/* bottom-right corner */
	else if (y == LINES - 1 && x == COLS - 1) {
		CHECK_AND_INC(y-1, x-1)
		CHECK_AND_INC(y-1,   x)
		CHECK_AND_INC(y-1,   0)
		CHECK_AND_INC(  y, x-1)
		CHECK_AND_INC(  y,   0)
		CHECK_AND_INC(  0, x-1)
		CHECK_AND_INC(  0,   x)
		CHECK_AND_INC(  0,   0)
	}

	return count;
}

void update_cell(chtype testch, unsigned int count, int y, int x) {
	if (testch == ALIVE) {
		if (count <= 1) { 
			mvaddch(y, x, DEAD); /* cell dies if it has 0 or 1 neighbour */
		}
		else if (count >= 4) {
	 		mvaddch(y, x, DEAD); /* cell dies if it has 4 or more neighbours */
		}
		else {
			; /* cell survives if it has 2 or 3 neighbours */
		}
	}
	else if (testch == DEAD) {
		if (count == 3) {
			mvaddch(y, x, ALIVE); /* cell becomes populated */
		}
		else {
			; /* cell stays dead */
		}
	}
}

int main(void) {
	const struct timespec ts = {0, 5000000};
	int *neighbour_count;

	/* initialize curses */
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	clear();

	printw("LINES: %d, COLS: %d\n", LINES, COLS);
	refresh();

	/* initialize the game of life */
	initialize_map();
	add_glider(0, 80);
	add_glider(0, 70);
	add_glider(0, 60);
	add_small_exploder(25, 105);
	add_small_exploder(40, 15);
	refresh();

	/* main loop to update the screen */
	while (true) {
		int x, y;
		neighbour_count = malloc(LINES*COLS*(sizeof *neighbour_count));

		/* generate the neighbour_count array */
		for (y = 0; y < LINES; y++) {
			for (x = 0; x < COLS; x++) {
				/* equivalent to neighbour_count[y][x], alternate form:
				 *neighbour_count[y*COLS+x] = count_neighbours(y, x); */
				*(neighbour_count + y*COLS + x) = count_neighbours(y, x);
			}
		}

		/* revive or kill each cell based on its neighbour count */
		for (y = 0; y < LINES; y++) {
			for (x = 0; x < COLS; x++) {
				chtype testch = mvinch(y, x) & A_CHARTEXT;
				int count = *(neighbour_count + y*COLS + x);
				update_cell(testch, count, y, x);
			}
		}
		nanosleep(&ts, NULL);
		refresh();
	}

	/* release malloc'd memory */
	free(neighbour_count);

	/* make ncurses clean up */
	endwin();

	exit(EXIT_SUCCESS);
}
