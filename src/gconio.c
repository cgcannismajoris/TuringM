
#include "gconio.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**** GLOBAL VARIABLES *********************/
int __gconio_h_ansi_attr = 0;
int __gconio_h_ansi_fg = 37;
int __gconio_h_ansi_bg = 40;

/**** FUNCTIONS ****************************/

void delay (unsigned long milliseconds)
{
    usleep (milliseconds * 1000);
}

void flushall (void)
{
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
}

int getch (void)
{
    int kbdinput;
    struct termios t_orig, t_new;

    // We need to change terminal settings so getchar() does't
    // require a CR at the end. Also disable local echo.
    tcgetattr(0, &t_orig);
    t_new = t_orig;
    t_new.c_lflag &= ~ICANON; t_new.c_lflag &= ~ECHO;
    t_new.c_lflag &= ~ISIG;   t_new.c_cc[VMIN] = 1;
    t_new.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &t_new);

    // Get actual input
    kbdinput = getchar();

    // Reset terminal settings.
    tcsetattr(0, TCSANOW, &t_orig);

    return (kbdinput);  
}

int getche (void)
{
    int kbdinput;
    kbdinput = getch();
    putchar (kbdinput);
    return (kbdinput);
}

char *strlwr (char *text)
{
    char *origtext = text;
    while (*text != '\0')
    {
      if ((*text > 64) && (*text < 91)) *text += 32;
      text++;
    }
    return (origtext);
}

char *strupr (char *text)
{
    char *origtext = text;
    while (*text != '\0')
    {
      if ((*text > 96) && (*text < 123)) *text -= 32;
      text++;
    }
    return (origtext);
}

int get_win_size (win) struct winsize *win;
{
    int err = ioctl (1, TIOCGWINSZ, (char *) win);
    if (err != 0) err = ioctl (0, TIOCGWINSZ, (char *) win);
    return (err);
}

int get_screen_columns (void)
{
#ifdef TIOCGWINSZ
    struct winsize win;

    /* In older versions of Solaris, ioctl will fail and set errno
       to EINVAL when using it in a telnet session. We are not going to
       support this, as these versions of Solaris (2.1 - 2.3) are barely
       used anymore, and telnet sessions should not be used. -FD */

    if (!get_win_size (&win))
        if (win.ws_col > 0)
            return win.ws_col;
#endif

    if (getenv ("COLUMNS"))
        return ((unsigned int) atoi (getenv ("COLUMNS")));

    return 80; /* return default */
}

int get_screen_rows (void)
{
#ifdef TIOCGWINSZ
    struct winsize win;

    /* In older versions of Solaris, ioctl will fail and set errno
       to EINVAL when using it in a telnet session. We are not going to
       support this, as these versions of Solaris (2.1 - 2.3) are barely
       used anymore, and telnet sessions should not be used. -FD */

    if (!get_win_size (&win))
        if (win.ws_row > 0)
            return win.ws_row;
#endif

    if (getenv ("LINES"))
        return ((unsigned int) atoi(getenv ("LINES")));

    return 25; /* return default */
}

void clrscr (void) 
{
    int count;
    for (count = 0; count < get_screen_rows(); count++)
    {
        gotoxy (0, count);
        delline();
    }
    gotoxy (0,0);
}


void delline () 
{
    printf ("\r\033[K\r");
}

void gotoxy (int x, int y)
{
    if ( (x <= get_screen_columns()) && (y <= get_screen_rows()) )
        printf("\033[%d;%dH", y, x);
    else
        return;
}

void linev (int x, int y, int length, int character)
{
    int count;
    if ((y + length - 1) <= get_screen_rows())
    {
        gotoxy (x,y);
        for (count = 0; count < length; count++)
        {
            gotoxy (x, y + count); 
            putchar (character);
        }
    }
}

void lineh (int x, int y, int length, int character)
{
    int count;
    if ((x + length - 1) <= get_screen_columns())
    {
        gotoxy (x,y);
        for (count = 0; count < length; count++) 
            putchar (character);
    }
}

void box (int x, int y, int length, int height, int type)
{

    char charset[10];

    if ( (x<0) || (y<0) || (length<0) || (height<0) || 
         ((x+length)>get_screen_columns()) || ((y+height)>get_screen_rows()))
        return;
    else {
        switch (type)
        {

            case 1: sprintf (charset, "++++-|"); break;
            case 2: sprintf (charset, "++++=|"); break;
            default: sprintf (charset, "++++-|"); break;
        }

        lineh (x, y, length, charset[4]);
        lineh (x, y + height - 1, length , charset[4]);
        linev (x, y, height, charset[5]);
        linev (x + length - 1, y, height, charset[5]);

        gotoxy (x, y);                           putchar (charset[0]);
        gotoxy (x, y + height - 1);              putchar (charset[1]);
        gotoxy (x + length - 1, y);              putchar (charset[2]);
        gotoxy (x + length - 1, y + height - 1); putchar (charset[3]);

        gotoxy(0, y + height + 2);
    }

}

void textcolor (int newcolor)
{
    if (newcolor > 7) { __gconio_h_ansi_attr = 1; newcolor -= 8; }
    else { __gconio_h_ansi_attr = 0; }
    switch(newcolor)
    {
        case 0:  __gconio_h_ansi_fg = 30; break; // black
        case 1:  __gconio_h_ansi_fg = 34; break; // blue
        case 2:  __gconio_h_ansi_fg = 32; break; // green
        case 3:  __gconio_h_ansi_fg = 36; break; // cyan
        case 4:  __gconio_h_ansi_fg = 31; break; // red
        case 5:  __gconio_h_ansi_fg = 35; break; // magenta
        case 6:  __gconio_h_ansi_fg = 33; break; // brown
        case 7:  __gconio_h_ansi_fg = 37; break; // gray
	default: return;
    }
    printf ("\033[%d;%d;%dm", __gconio_h_ansi_attr, __gconio_h_ansi_fg, __gconio_h_ansi_bg);
}

void textbackground (int newcolor)
{
    switch(newcolor)
    {
        case 0:  __gconio_h_ansi_bg = 40; break;
        case 1:  __gconio_h_ansi_bg = 44; break;
        case 2:  __gconio_h_ansi_bg = 42; break;
        case 3:  __gconio_h_ansi_bg = 46; break;
        case 4:  __gconio_h_ansi_bg = 41; break;
        case 5:  __gconio_h_ansi_bg = 45; break;
        case 6:  __gconio_h_ansi_bg = 43; break;
        case 7:  __gconio_h_ansi_bg = 47; break;
        default: return;
    }
    printf ("\033[%d;%d;%dm", __gconio_h_ansi_attr, __gconio_h_ansi_fg, __gconio_h_ansi_bg);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
