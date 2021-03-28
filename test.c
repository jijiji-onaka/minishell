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
//     tcgetattr(STDIN_FILENO, &termios_backup);
//     termios_new = termios_backup;

//     termios_new.c_lflag &= ~(ICANON);
//     termios_new.c_lflag &= ~(ECHO);
//     termios_new.c_cc[VMIN] = 1;
//     termios_new.c_cc[VTIME] = 0;

//     /*
//     **  Set the change
//     */
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);

//     /*
//     ** Get the termcap for clearing screen on the particular terminal
//     */
//     termcap = tgetstr("cl", NULL);

//     /*
//     ** Loop read to get user entries and clear screen for 'c', output char for 'b', break for 'q'
//     */
//     while((ret = read(STDIN_FILENO, &buff, 1)) > 0)
//     {
//         if (buff == 'c')
//             // tputs(termcap, 1, put);
// 			ft_putstr_fd(tgetstr("ti", NULL), STDIN_FILENO);
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
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_backup);
//     return (0);
// }

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "includes/minishell.h"
int main()
{
	ft_putnbr_fd(INT_MIN, 1);
	puts("");
	ft_putnbr_fd(INT_MAX, 1);
	puts("");
	ft_putnbr_fd(0, 1);
	puts("");
	ft_putnbr_fd(123, 1);
	puts("");
	ft_putnbr_fd(+123, 1);
	puts("");
	ft_putnbr_fd(-123, 1);
	printf("\033[D");
	printf("\033[D");
}
