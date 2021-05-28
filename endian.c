#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>  // BYTE_ORDER (included in stdio.h)
//----------------------------------------------------------------------------------------------------
#ifndef BYTE_ORDER // Endian type (defined in byteorder.h)
#define LITTLE_ENDIAN  1234
#define BIG_ENDIAN     4321
#endif
//----------------------------------------------------------------------------------------------------
// バイトオーダーの取得
static int  get_endian(void) { int x = 1; return (*(char *)&x == 1) ? LITTLE_ENDIAN : BIG_ENDIAN; }
// 文字列の16進表示: バイナリエディタ等でのダンプ
static void hexdump(char* str, char* xbuf);
static void dump2char(char* hex, char* out, const char* seps);
// 10進 ==> 16進
static int  dec2hex(int decval, char* wbuf);
static void dec2hex1(int decval, int buflen, char* wbuf);
// 10進 <== 16進
static int  hex2dec(char* hexval);
static int  hex2dec1(int n, char* buf);
//----------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char cbuf[] = "Hello World!", xbuf[256];
    int bbuf[] = {123456,789};
    char buf[256];

    printf("Is little endian? %d\n",(get_endian() == LITTLE_ENDIAN));
    //--------------------------------------------------
    // 16進ダンプ → 元に戻す
    //--------------------------------------------------
    printf("\n** Convert String and HEX Dump\n");
    memset(xbuf,0,256); hexdump(cbuf,xbuf);
    printf("[STRING -> HEX] %s -> %s\n",cbuf,xbuf);
    char output[32]; memset(output,0,32);
    dump2char(xbuf,output," ");
    printf("[HEX -> STRING] %s -> %s\n",xbuf,output);

    //--------------------------------------------------
    // 文字列を16進文字列へ [1バイト単位]
    //--------------------------------------------------
    printf("\n** Convert String to HEX ASCII [1BYTE]\n");
    printf(" %s: ",cbuf);
    for ( int i=0; i<strlen(cbuf); i++ ) { dec2hex(cbuf[i],buf); printf("%s ",buf); }
    printf("\n");
    //--------------------------------------------------
    // バイナリデータをアスキーデータへ
    //--------------------------------------------------
    printf("\n** Convert BINARY and 8 BYTE HEX ASCII [int data]\n");
    for ( int i=0; i<2; i++ ) {
        int val = bbuf[i]; memset(buf,0,256); dec2hex1(val,8,buf); printf(" %d [0x%06x]: %s\n",val,val,buf);
        char* p = (char*)&val; printf(" - VALUE CHECK [%d] : %02x,%02x,%02x\n",val,*p,(0xff&*(p+1)),(0xff&*(p+2)));
        // 元に戻す
        printf(" - Reverse to int: \"%s\" -> %d\n",buf,hex2dec1(strlen(buf),buf));
    }
    return 0;
}


int dec2asc (char *str, int dec) {
    int len = 0, len_buf; //桁数
    int buf[10];
    while (1) { //10で割れた回数（つまり桁数）をlenに、各桁をbufに格納
        buf[len++] = dec % 10;
        if (dec < 10) break;
        dec /= 10;
    }
    len_buf = len;
    while (len) {
        *(str++) = buf[--len] + 0x30;
    }
    return len_buf;
}

//16進数からASCIIコードに変換
int hex2asc (char *str, int dec) { //10で割れた回数（つまり桁数）をlenに、各桁をbufに格納
    int len = 0, len_buf; //桁数
    int buf[10];
    while (1) {
        buf[len++] = dec % 16;
        if (dec < 16) break;
        dec /= 16;
    }
    len_buf = len;
    while (len) {
        len --;
        *(str++) = (buf[len]<10)?(buf[len] + 0x30):(buf[len] - 9 + 0x60);
    }
    return len_buf;
}


//----------------------------------------------------------------------------------------------------
// 文字列の16進変換: バイナリエディタ等でのダンプ
//----------------------------------------------------------------------------------------------------
static void hexdump(char* str, char* xbuf)
{
    int n = strlen(str);
    char xstr[32];
    for ( int i=0; i<n; i++ ) {
        // sprintf(xstr,"%02x",str[i]);
		hex2asc(xstr, str[i]);
		strcat(xbuf,xstr);
        if ( i != n-1 ) strcat(xbuf," ");
    }
}
static void dump2char(char* hex, char* out, const char* seps)
{
    int c, count = 0;
    char *s = strdup(hex), *p = (char*)strtok(s,seps);
    while ( p != NULL ) {
        sscanf(p,"%x",&c); out[count++] = (char)c;
        p = (char*)strtok(NULL,seps);
    }
    free(s);
    out[count] = 0;
}
//----------------------------------------------------------------------------------------------------
// Decimal ==> Hexadicimal
//----------------------------------------------------------------------------------------------------
// 10進数字を16進文字列に変換し文字数を返す
static int dec2hex(int decval, char* wbuf)
{
    int k = 1, n = 1;
    char c;
    while ( (k<<=4) <= decval ) n++;
    if ( get_endian() == LITTLE_ENDIAN ) { // リトルエンディアン[最下位のバイト順](Intel)
        int m = (n/2)*2;
        for ( int i=m-1; i>0; i-=2 ) {
            c = 0xf & (decval>>((i-1)*4)); wbuf[i] = (c > 9) ? (c+'A'-10) : (c+'0');
            c = 0xf & (decval>>(i*4)); wbuf[i-1] = (c > 9) ? (c+'A'-10) : (c+'0');
        }
        if ( m != n ) {
            wbuf[n-1] = '0';
            c = 0xf & (decval>>((n-1)*4)); wbuf[n] = (c > 9) ? (c+'A'-10) : (c+'0'); wbuf[n+1] = '\0';
            n = n+1;
        } else {
            wbuf[n] = '\0';
        }
    } else { // ビッグエンディアン[最上位のバイト順](Motorola)
        int is = 0, m = (n/2)*2;
        if ( m != n ) { wbuf[0] = '0'; is = 1; }
        for ( int i=0; i<n; i++ ) {
            c = 0xf & (decval>>(i*4)); wbuf[is + (n-i-1)] = (c > 9) ? (c+'A'-10) : (c+'0');
        }
        wbuf[is+n] = '\0';
        n = is+n;
    }
    return n;
}
// バイト数を指定して配列へ格納: [ex 000AAA : 6byte] -> 0字詰め
static void dec2hex1(int decval, int buflen, char* wbuf)
{
    if ( (buflen%2) != 0 ) { printf("Illegal byte length\n"); return; }

    memset(wbuf,'0',buflen);

    char buf[256]; memset(buf,0,256);
    int declen = dec2hex(decval,buf);
    if ( declen <= buflen ) {
        int clen = buflen-strlen(buf); if ( clen < 0 ) clen = 0;
        strncpy(wbuf+clen,buf,declen);
    } else { // 準備されたサイズよりデータが大きい..
        printf("Illegal data size (%d < %d)\n", buflen, declen);
    }
}
//----------------------------------------------------------------------------------------------------
// Hexadicimal ==> Decimal
//----------------------------------------------------------------------------------------------------
// 16進文字列を10進数字に変換
static int hex2dec(char* hexval)
{
    return hex2dec1(strlen(hexval),hexval);
}
// 16進文字列を10進数字に変換
static int hex2dec1(int n, char* buf)
{
    int d = 0, shift;
    unsigned char x, x1, x2;
    if ( get_endian() == LITTLE_ENDIAN ) { // リトルエンディアン[最下位のバイト順](Intel)
        int is = 0; // if 00 is top of byte, skip
        for ( int i=0; i<n; i+=2 ) {
            x1 = tolower(buf[i]); if ( isdigit(x1) ) x1 -= '0'; else x1 -= ('a'-10);
            x2 = tolower(buf[i+1]); if ( isdigit(x2) ) x2 -= '0'; else x2 -= ('a'-10);
            x = (x1<<4) + x2; if ( x == 0 ) is ++;
            shift = i/2 - is; d += (x << (shift*8));
        }
    } else { // ビッグエンディアン[最上位のバイト順](Motorola)
        int i = 0, m = (n/2)*2;
        if ( m != n ) {
            i = 1;
            x = tolower(buf[0]); if ( isdigit(x) ) x -= '0'; else x -= ('a'-10);
            shift = m/2; d += (x<<(shift*8));
        }
        for ( ; i<n; i+=2 ) {
            x1 = tolower(buf[i]); if ( isdigit(x1) ) x1 -= '0'; else x1 -= ('a'-10);
            x2 = tolower(buf[i+1]); if ( isdigit(x2) ) x2 -= '0'; else x2 -= ('a'-10);
            x = (x1<<4) + x2;
            shift = ( n != m ) ? ((m-i)/2) : ((n-i)/2 - 1); d += (x << (shift*8));
        }
    }
    return d;
}


// # include <stdio.h>
// # include <string.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include "includes/minishell.h"

// int main()
// {
// 	struct termios		terminal[2];

// 	tcgetattr(STDIN, &(terminal[ORIGINAL]));
// 	terminal[REPLICA] = terminal[ORIGINAL];
// 	terminal[REPLICA].c_lflag &= ~(ICANON | ECHO);
// 	terminal[REPLICA].c_cc[VMIN] = 1;
// 	terminal[REPLICA].c_cc[VTIME] = 0;
// 	tcsetattr(STDIN, TCSAFLUSH, &(terminal[REPLICA]));

// 	unsigned long buf;
// 	char	*str;
// 	char	chr;

// 	buf = 0;
// 	while (1)
// 	{
// 		buf = 0;
// 		int ret = read(STDIN, &buf, 8);
// 		// buf = (unsigned long long)'\033[B';

// 		printf("lu [%lu]\n", buf);
// 		printf("p  [%p]\n", buf);
// 		printf("x  [%lx]\n", buf);
// 		// printf("[%s]\n", (char *)buf);
// 		// printf("d  [%d]\n", ret);

// 		// char *p = calloc(sizeof(*p), 100); // \e[1;5D
// 		// p = (char*)&buf;
// 		char *p = (char *)&buf;
// 		printf("lu [%lu]\n", *p);
// 		printf("p  [%p]\n", *p);
// 		printf("x  [%lx]\n", *p);
// 		// p[ret] = '\0';
// 		// *p = 0xff & *((p + 1));
// 		printf(" - bufUE CHECK [%d] : %02x,%02x,%02x\n", buf, 0xff & *p, (0xff & *(p + 1)), (0xff & *(p + 2)));
// 		printf(" - bufUE CHECK [%d] : %02x,%02x,%02x\n", buf, (0xff & *(p + 3)), (0xff & *(p + 4)), (0xff & *(p + 5)));
// 		printf(" - bufUE CHECK [%d] : %02x,%02x\n", buf, (0xff & *(p + 6)), (0xff & *(p + 7)));
// 		printf(" - bufUE CHECK [%d] : [%c],[%d],[%c]\n", 0, 0xff & *p, (0xff & *(p + 1)), (0xff & *(p + 2)));
// 		printf(" - bufUE CHECK [%d] : [%c],[%c],[%c]\n", 0, (0xff & *(p + 3)), (0xff & *(p + 4)), (0xff & *(p + 5)));
// 		printf(" - bufUE CHECK [%d] : [%c],[%c]\n", 0, (0xff & *(p + 6)), (0xff & *(p + 7)));
// 		// printf(" - bufUE CHECK [%d] : [%c],[%d],[%c]\n",buf,*p,(0xff&*(p+1)),(0xff&*(p+2)));
// 		// printf(" - bufUE CHECK [%d] : %x,%02x,%02x\n",buf,*p,(0xff&*(p+1)),(0xff&*(p+2)));
// 		// printf("p  [%s]\n", p);
// 		//  printf(" - bufUE CHECK [%d] : %c,%c,%c\n",buf,(0xff&*(p+3)),(0xff&*(p+4)), (0xff&*(p+5)));
// 		//  printf(" - bufUE CHECK [%d] : %c,%c\n",buf,(0xff&*(p+6)),(0xff&*(p+7)));
// 	}

// 	int x = 1; // 0x00000001
// 	if (*(char *)&x == 1)
// 	{
// 		puts("little");
// 		/* little endian. memory image 01 00 00 00 */
// 	}
// 	else
// 	{
// 		puts("big");
// 		/* big endian. memory image 00 00 00 01 */
// 	}
// }
