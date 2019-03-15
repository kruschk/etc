#define _POSIX_C_SOURCE 199309L
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#define BALL 'o'
#define PATH ' '
#define MAX_LINE 1024

/* start_ncurses: initializes ncurses */
static void start_ncurses(void) {
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	curs_set(0);
	clear();
	refresh();
}

static void cleanup_ncurses(void) {
	endwin();
}

int main(void) {
	/* initialize ncurses */
	start_ncurses();

	while (TRUE) {
		int x_max;
		int y_max;

		/* put the ball at the initial position */
		struct {
			double x;
			double y;
		} ball;

		/* variables for storing and testing input */
		int valid_input = FALSE;
		char quit = FALSE;
		char input[MAX_LINE];
		char testch;
		char *input_helper;

		/* declare variables for initial velocity and direction */
		double v_0;
		double theta_0;

		/* timespec for sleeping */
		struct timespec ts = {0, 500000000}; /* {s, ns} */

		/* initial position of the ball */
		const double x_0 = 3;    /* m */
		const double y_0 = 3;    /* m */


		/* set the running time to zero, since that's used to compute the
		 * trajectory */
		double t = 0; /* s */

		/* reset y_max and x_max in case window size changes */
		getmaxyx(stdscr, y_max, x_max);

		/* set the initial position of the ball */
		ball.x = x_0;
		ball.y = y_max - 1 - y_0;

		/* draw a stickman */
		mvaddch(y_max - 1, 0, '/');
		mvaddch(y_max - 1, 2, '\\');
		mvaddch(y_max - 2, 0, '/');
		mvaddch(y_max - 2, 1, '|');
		mvaddch(y_max - 2, 2, '\\');
		mvaddch(y_max - 2, 3, 'o');
		mvaddch(y_max - 3, 1, 'o');

		/* gather user input */
		nodelay(stdscr, FALSE);
		echo();
		while (!valid_input) {
			mvaddstr(0, 0, "Enter the initial velocity in m/s and the direction in"
					" degrees, separated by a space. Or use 'q' or 'Q' to quit: ");
			refresh();
			getnstr(input, MAX_LINE);
			valid_input = TRUE;
			for (int i = 0; (testch = input[i]) != '\0'; i++) {
				if (isdigit(testch) || isspace(testch) || testch == '.') {
					;
				}
				else if (testch == 'q' || testch == 'Q') {
					quit = TRUE;
					break;
				}
				else {
					mvhline(0, 0, ' ', x_max);
					mvaddstr(0, 0, "invalid input, try again");
					refresh();
					ts.tv_sec = 1;
					ts.tv_nsec = 0;
					nanosleep(&ts, NULL);
					ts.tv_sec = 0;
					ts.tv_nsec = 500000000;
					valid_input = FALSE;
					break;
				}
			}
		}
		if (quit) {
			break;
		}
		else {
			v_0 = strtod(input, &input_helper);
			theta_0 = strtod(input_helper, NULL);
		}
		nodelay(stdscr, TRUE);
		noecho();

		/* erase the prompt before the action starts */
		mvhline(0, 0, ' ', x_max);

		/* animate the stickman */
		nanosleep(&ts, NULL);
		mvaddch(y_max - 2, 3, ' ');
		mvaddch(y_max - 2, 2, ' ');
		mvaddch(y_max - 3, 2, '/');
		refresh();

		/* draw the trajectory of the ball */
		ts.tv_nsec = 16666666; /* 60 fps, i.e. ~0.016 s per frame */
		while ((0 <= ball.x && ball.x < x_max) && (ball.y < y_max)) {
			int c; /* for getch() */

			/* pi */
			const double pi = acos(-1); /* rad */

			/* gravitational acceleration */
			const double g = -9.805; /* m*s^(-2) */

			/* compute the initial velocity components */
			double v_x_0 = v_0*cos(theta_0*pi/180.0); /* m*s^(-1) */
			double v_y_0 = v_0*sin(theta_0*pi/180.0); /* m*s^(-1) */

			/* check if the user wants to end the simulation early */
			if ((c = getch()) == 'q' || c == 'Q') {
				break;
			}

			/* replace the last position with PATH and draw the new position */
			mvaddch(round(ball.y), round(ball.x), PATH);
			ball.x = x_0 + v_x_0*t; /* compute the new coordinates */
			/* y_max-1-blah because y+ is downward; need to flip coordinate */
			ball.y = y_max - 1 - (y_0 + v_y_0*t + 0.5*g*t*t);
			mvaddch(round(ball.y), round(ball.x), BALL);

			/* refresh the screen */
			refresh();

			/* update the time */
			t += ts.tv_sec + ts.tv_nsec/1e9;

			/* pause so we can watch the action */
			nanosleep(&ts, NULL);
		}
		clear();
		refresh();
	}

	cleanup_ncurses();

	exit(EXIT_SUCCESS);
}
