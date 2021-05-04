# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "includes/minishell.h"

int main()
{
	struct termios		terminal[2];

	tcgetattr(STDIN, &(terminal[ORIGINAL]));
	terminal[REPLICA] = terminal[ORIGINAL];
	terminal[REPLICA].c_lflag &= ~(ICANON | ECHO);
	terminal[REPLICA].c_cc[VMIN] = 1;
	terminal[REPLICA].c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSAFLUSH, &(terminal[REPLICA]));

	unsigned long buf;
	char	*str;
	char	chr;

	buf = 0;
	while (1)
	{
		buf = 0;
		int ret = read(STDIN, &buf, 8);
		// buf = (unsigned long long)'\033[B';

		printf("lu [%lu]\n", buf);
		printf("p  [%p]\n", buf);
		printf("x  [%lx]\n", buf);
		// printf("[%s]\n", (char *)buf);
		// printf("d  [%d]\n", ret);

		// char *p = calloc(sizeof(*p), 100); // \e[1;5D
		// p = (char*)&buf;
		char *p = (char *)&buf;
		printf("lu [%lu]\n", *p);
		printf("p  [%p]\n", *p);
		printf("x  [%lx]\n", *p);
		// p[ret] = '\0';
		// *p = 0xff & *((p + 1));
		printf(" - bufUE CHECK [%d] : %02x,%02x,%02x\n", buf, 0xff & *p, (0xff & *(p + 1)), (0xff & *(p + 2)));
		printf(" - bufUE CHECK [%d] : %02x,%02x,%02x\n", buf, (0xff & *(p + 3)), (0xff & *(p + 4)), (0xff & *(p + 5)));
		printf(" - bufUE CHECK [%d] : %02x,%02x\n", buf, (0xff & *(p + 6)), (0xff & *(p + 7)));
		printf(" - bufUE CHECK [%d] : [%c],[%d],[%c]\n", 0, 0xff & *p, (0xff & *(p + 1)), (0xff & *(p + 2)));
		printf(" - bufUE CHECK [%d] : [%c],[%c],[%c]\n", 0, (0xff & *(p + 3)), (0xff & *(p + 4)), (0xff & *(p + 5)));
		printf(" - bufUE CHECK [%d] : [%c],[%c]\n", 0, (0xff & *(p + 6)), (0xff & *(p + 7)));
		// printf(" - bufUE CHECK [%d] : [%c],[%d],[%c]\n",buf,*p,(0xff&*(p+1)),(0xff&*(p+2)));
		// printf(" - bufUE CHECK [%d] : %x,%02x,%02x\n",buf,*p,(0xff&*(p+1)),(0xff&*(p+2)));
		// printf("p  [%s]\n", p);
		//  printf(" - bufUE CHECK [%d] : %c,%c,%c\n",buf,(0xff&*(p+3)),(0xff&*(p+4)), (0xff&*(p+5)));
		//  printf(" - bufUE CHECK [%d] : %c,%c\n",buf,(0xff&*(p+6)),(0xff&*(p+7)));
	}

	int x = 1; // 0x00000001
	if (*(char *)&x == 1)
	{
		puts("little");
		/* little endian. memory image 01 00 00 00 */
	}
	else
	{
		puts("big");
		/* big endian. memory image 00 00 00 01 */
	}
}
