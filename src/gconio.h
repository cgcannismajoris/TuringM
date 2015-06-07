/*
 * gconio.h v0.5
 *
 * A replacement library for Borland C-specific conio.h functions for gcc
 * and MSVC.
 *
 * Implemented functions: clrscr, delay, delline, gotoxy, kader,
 *                        lijnh, lijnv, textbackground, textcolor,
 *                        getch, getche, setcursortype.
 *
 * Implemented MSVC-only functions: wherex, wherey.
 *
 * Added functions: get_screen_rows, get_screen_columns
 *
 * Warning: The Linux functions in this library rely on ANSI code sequences 
 *          _ALOT_. Output might look weird on non-ANSI-compliant terminals.
 * 
 * Warning: gotoxy() uses (0, 0) as topleft corner. This is different from
 *          what MSVC users may be used to.
 *
 * An updated version of this file can be requested by sending email
 * to Wence Van der Meersch <wence@wence.be> or 
 * Filip Duyck <filip@factor9.be>.
 *
 * Copyright (C) 2002-2003 Wence Van der Meersch & Filip Duyck
 *
 * The MSVC versions of setcursortype, textcolor and textbackground were
 * kindly donated by Sebastien Boelpaep <sebastien@pi.be>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 * History:
 *
 * v0.5:  - gconio.h should now be compatible with MSVC!
 *        - Rewrote clrscr, lineh, linev functions to evade ANSI codes.
 *        - Added wherex, wherey, setcursortype functions (MSVC only).
 * v0.2:  - Added getch, getche, strlwr, strupr functions.
 *        - Added aliases for stricmp, strnicmp.
 *
 * v0.1:  - First release.
 */

#ifndef __GCONIO_H
#define __GCONIO_H

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

/**** DEFINITIONS **************************/
#define kader(x,y,l,h,t) box(x,y,l,h,t)
#define lijnh(x,y,l,c)   lineh(x,y,l,c)
#define lijnv(x,y,l,c)   linev(x,y,l,c)
#define stricmp          strcasecmp 
#define strnicmp         strncasecmp
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**** PROTOTYPES ***************************/
void delline (void);
void clrscr (void);
void delay (unsigned long milliseconds);
int get_screen_rows (void);
int get_screen_columns (void);
void textbackground (int newcolor);
void textcolor (int newcolor);
void box (int x, int y, int length, int height, int type);
void lineh (int x, int y, int length, int character);
void linev (int x, int y, int length, int character);
void gotoxy (int x, int y);
void flushall (void);
int getch (void);
int getche (void);
char *strlwr (char *text);
char *strupr (char *text);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GCONIO_H */


