// /*
// *getchar
// */
// #include <stdio.h>
// #include <termios.h>
// int main(void)
// {
// 	struct termios term1, term0;
// 	int ch;
// 	tcgetattr(0, &term1); //現在の画面環境の取得
// 	term0 = term1;		  //現在の画面環境の保存
// 	term1.c_lflag &= ~(ICANON | ECHO);
// 	//現在の画面環境をエコーオフおよび非カノニカル・モードに設定
// 	term1.c_cc[VMIN] = 1;		   //そのためのパラメータ
// 	term1.c_cc[VTIME] = 0;		   //そのためのパラメータ
// 	tcsetattr(0, TCSANOW, &term1); //現在の画面環境を更新
// 	ch = getchar();
// 	printf("押下したキーは %c です\n", ch);
// 	tcsetattr(0, TCSANOW, &term0);
// 	//保存しておいた環境で現在の画面環境を更新（元に戻す）
// 	return 0;
// }








// #include <stdio.h>
// #include <string.h>
// #include <termios.h>
// #include <unistd.h>

// #define cursorforward(x) printf("\033[%dC", (x))
// #define cursorbackward(x) printf("\033[%dD", (x))

// #define KEY_ESCAPE  0x001b
// #define KEY_ENTER   0x000a
// #define KEY_UP      0x0105
// #define KEY_DOWN    0x0106
// #define KEY_LEFT    0x0107
// #define KEY_RIGHT   0x0108

// static struct termios term, oterm;

// static int getch(void);
// static int kbhit(void);
// static int kbesc(void);
// static int kbget(void);

// static int getch(void)
// {
//     int c = 0;

//     tcgetattr(0, &oterm);
//     memcpy(&term, &oterm, sizeof(term));
//     term.c_lflag &= ~(ICANON | ECHO);
//     term.c_cc[VMIN] = 1;
//     term.c_cc[VTIME] = 0;
//     tcsetattr(0, TCSANOW, &term);
//     c = getchar();
//     tcsetattr(0, TCSANOW, &oterm);
//     return c;
// }

// static int kbhit(void)
// {
//     int c = 0;

//     tcgetattr(0, &oterm);
//     memcpy(&term, &oterm, sizeof(term));
//     term.c_lflag &= ~(ICANON | ECHO);
//     term.c_cc[VMIN] = 0;
//     term.c_cc[VTIME] = 1;
//     tcsetattr(0, TCSANOW, &term);
//     c = getchar();
//     tcsetattr(0, TCSANOW, &oterm);
//     if (c != -1) ungetc(c, stdin);
//     return ((c != -1) ? 1 : 0);
// }

// static int kbesc(void)
// {
//     int c;

//     if (!kbhit()) return KEY_ESCAPE;
//     c = getch();
//     if (c == '[') {
//         switch (getch()) {
//             case 'A':
//                 c = KEY_UP;
//                 break;
//             case 'B':
//                 c = KEY_DOWN;
//                 break;
//             case 'C':
//                 c = KEY_LEFT;
//                 break;
//             case 'D':
//                 c = KEY_RIGHT;
//                 break;
//             default:
//                 c = 0;
//                 break;
//         }
//     } else {
//         c = 0;
//     }
//     if (c == 0) while (kbhit()) getch();
//     return c;
// }

// static int kbget(void)
// {
//     int c;

//     c = getch();
//     return (c == KEY_ESCAPE) ? kbesc() : c;
// }

// int main(void)
// {
//     int c;
// 	int i = 0;
// 	char	buf[1024];

// 	bzero(buf, 1024);
//     while (1) {
//         c = kbget();
//         if (c == KEY_ENTER || c == KEY_ESCAPE || c == KEY_UP || c == KEY_DOWN) {
//             break;
//         } else
//         if (c == KEY_RIGHT) {
//             cursorbackward(1);
//         } else
//         if (c == KEY_LEFT) {
//             cursorforward(1);
//         } else {
// 			putchar(c);
//            buf[i] = c;
// 		   i++;
//         }
//     }
//     printf("\n%s\n", buf);
//     return 0;
// }














// #include <termios.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// # include <termcap.h>
// # include "includes/minishell.h"

// int	put(int c)
// {
// 	write(1, &c, 1);
// 	return (1);
// }



// int main()
// {
//     int     ret;
//     char    buff;
//     char    *term_name;
//     char    *termcap;
//     struct termios  termios_new;
//     struct termios  termios_backup;

//     /*
//     ** Init termcap library
//     */
//     term_name = getenv("TERM");
//     tgetent(NULL, term_name);

//     /*
//     ** Get the terminal mode to non canonical and shut down echo
//     */
//     bzero(&termios_new, sizeof(struct termios));
//     tcgetattr(STDIN, &termios_backup);
//     termios_new = termios_backup;

//     termios_new.c_lflag &= ~(ICANON);
//     termios_new.c_lflag &= ~(ECHO);
//     termios_new.c_cc[VMIN] = 1;
//     termios_new.c_cc[VTIME] = 0;

//     /*
//     **  Set the change
//     */
//     tcsetattr(STDIN, TCSAFLUSH, &termios_new);

//     /*
//     ** Get the termcap for clearing screen on the particular terminal
//     */
//     termcap = tgetstr("cl", NULL);

//     /*
//     ** Loop read to get user entries and clear screen for 'c', output char for 'b', break for 'q'
//     */
//     while((ret = read(STDIN, &buff, 1)) > 0)
//     {
//         if (buff == 'c')
//             // tputs(termcap, 1, put);
// 			ft_putstr_fd(tgetstr("ti", NULL), STDIN);
//         else if (buff == 'b')
//             put(buff);
//         else if (buff == 'q')
//             break ;
// 		printf("[%c]\n", buff);
//         buff = 0;
//     }

//     /*
//     ** Put back the terminal mode as found before
//     */
//     tcsetattr(STDIN, TCSAFLUSH, &termios_backup);
//     return (0);
// }

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "includes/minishell.h"
#include <sys/ioctl.h>
#include <unistd.h>
# include <termcap.h>
# include <termios.h>
// # include <readline.h>
# include <sys/ioctl.h>

// int main()
// {
// 	// tgetent(NULL, getenv("TERM"));
// 	// tcgetattr(STDIN, &(g_global.terms[0]));
// 	// g_global.terms[1] = g_global.terms[0];
// 	// g_global.terms[1].c_lflag &= ~(ICANON | ECHO);
// 	// g_global.terms[1].c_cc[VMIN] = 1;
// 	// g_global.terms[1].c_cc[VTIME] = 0;
// 	// tcsetattr(STDIN, TCSANOW, &(g_global.terms[1]));
// 	// char *tmp = readline("abc");
// 	// int buf;
// 	// read(0, &buf, 99);
// 	// printf("%d\n", buf);
// 	// read(0, &buf, 99);
// 	// printf("%d\n", buf);
// 	// write(1, "[", 1);
// 	// write(1, s, strlen(s));
// 	// write(1, "]", 1);
// 	// tcsetattr(STDIN, TCSANOW, &(g_global.terms[0]));
	// printf("\x1b[38;5;93maaaaaaaa\033[0m\n");
	// printf("\x1b[38;5;109maaaaaaaa\033[0m\n");
	// printf("\x1b[38;5;106maaaaaaaa\033[0m\n");
	// printf("\x1b[95maaaaaaaa\033[0m");
	// printf("\x1b[4Daaaaa");
	// printf("\tわたしの毎月の小遣いは、\\200です\n");
    // printf("\a");        /* ビープ音がなる */
	// else
// 	printf("\x1b[6n");
// 	char buf[100];
// 	bzero(buf, 100);
// 	read(0, buf, 99);
// 	printf("%s\n", buf);
// 	// printf("\033[49m");
// }

#include <stdio.h>

int getCursorPosition(int ifd, int ofd, int *rows, int *cols)
{
	char buf[32];
	unsigned int i = 0;

	/* Report cursor location */
	if (write(1, "\x1b[6n", 4) != 4)
		return -1;

	/* Read the response: ESC [ rows ; cols R */
	while (i < sizeof(buf) - 1)
	{
		if (read(0, buf + i, 1) != 1)
			break;
		if (buf[i] == 'R')
			break;
		i++;
	}
	buf[i] = '\0';

	/* Parse it. */
	if (buf[0] != '\x1b' || buf[1] != '[')
		return -1;
	if (sscanf(buf + 2, "%d;%d", rows, cols) != 2)
		return -1;
	return 0;
}

int getWindowSize(int ifd, int ofd, int *rows, int *cols) {
    struct winsize ws;

if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0 || 1) {
    /* ioctl() failed. Try to query the terminal itself. */
    int orig_row, orig_col, retval;

    /* Get the initial position so we can restore it later. */
    retval = getCursorPosition(ifd,ofd,&orig_row,&orig_col);
    if (retval == -1) goto failed;

    /* Go to right/bottom margin and get position. */
    if (write(ofd,"\x1b[999C\x1b[999B",12) != 12) goto failed;
    retval = getCursorPosition(ifd,ofd,rows,cols);
    if (retval == -1) goto failed;

    /* Restore position. */
    char seq[32];
    snprintf(seq,32,"\x1b[%d;%dH",orig_row,orig_col);
    if (write(ofd,seq,strlen(seq)) == -1) {
        /* Can't recover... */
    }
    return 0;
} else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
}

failed:
    return -1;
}

int main()
{
		tgetent(NULL, getenv("TERM"));
	tcgetattr(STDIN, &(g_global.terms[0]));
	g_global.terms[1] = g_global.terms[0];
	g_global.terms[1].c_lflag &= ~(ICANON | ECHO);
	g_global.terms[1].c_cc[VMIN] = 1;
	g_global.terms[1].c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSANOW, &(g_global.terms[1]));
	int row = 0;
	int col = 0;
	getWindowSize(0, 1, &row, &col);
	printf("%d\n", col);
	printf("%d\n", row);
	tcsetattr(STDIN, TCSANOW, &(g_global.terms[0]));
}

// int main(void)
// {
//  int cursor_x, cursor_y;

// //  tgetent(NULL, getenv("TERM"));
// //  tcgetattr(STDIN, &(g_global.terms[0]));
// //  g_global.terms[1] = g_global.terms[0];
// //  g_global.terms[1].c_lflag &= ~(ICANON | ECHO);
// //  g_global.terms[1].c_cc[VMIN] = 1;
// //  g_global.terms[1].c_cc[VTIME] = 0;
// //  tcsetattr(STDIN, TCSANOW, &(g_global.terms[1]));
//  printf("1");
//  printf("%s", "\x1B[6n");
//  scanf("\x1B[%d;%dR", &cursor_y, &cursor_x);

//  printf("x = %d, y = %d\n", cursor_x, cursor_y);

// //  tcsetattr(STDIN, TCSANOW, &(g_global.terms[0]));
// }

// static size_t line_length = 80;
// int main( int argc, char *argv[] )
// {
//     struct winsize ws;
//     // get terminal size
//     if( ioctl( STDOUT, TIOCGWINSZ, &ws ) != -1 ) {
//         printf("terminal_width  =%d\n", ws.ws_col);
//         printf("terminal_height =%d\n", ws.ws_row);
//         if( 0 < ws.ws_col && ws.ws_col == (size_t)ws.ws_col ) {
//             line_length = ws.ws_col;
//         }
//     }
// 	printf("line %d\n", line_length);
//     return 0;
// }
