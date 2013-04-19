#include "mystdio.h"
#ifndef DISABLE_DEBUG
/*
Copyright (C) 1993 Free Software Foundation
 
This file is part of the GNU IO Library.  This library is free
software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option)
any later version.
 
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this library; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 
As a special exception, if you link this library with files
compiled with a GNU compiler to produce an executable, this does not cause
the resulting executable to be covered by the GNU General Public License.
This exception does not however invalidate any other reasons why
the executable file might be covered by the GNU General Public License. */

/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. [rescinded 22 July 1999]
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Sprintf is taken from dip122 project.
 * I just adopted it that msp430-gcc can handle it
 * The code is about 1500 bytes (depends on -O options)
 *
 * (c) msp gcc team http://mspgcc.sourceforge.net
 */



/******************************************************************************
 This file is a patched version of printf called _printf_P
 It is made to work with avr-gcc for Atmel AVR MCUs.
 There are some differences from standard printf:
 	1. There is no floating point support (with fp the code is about 8K!)
 	2. Return type is void
 	3. Format string must be in program memory (by using macro printf this is
 	   done automaticaly)
 	4. %n is not implemented (just remove the comment around it if you need it)
 	5. If LIGHTPRINTF is defined, the code is about 550 bytes smaller and the
 	   folowing specifiers are disabled :
 		space # * . - + p s o O
	6. A function void uart_sendchar(char c) is used for output. The UART must
		be initialized before using printf.
 
 Alexander Popov
 sasho@vip.orbitel.bg
 
 small modifications to make it work with liblcd_dip122.a
 replaced uart_sendchar with (*write_char)(char)
 2001 Michael Schaenzler                                                  
*******************************************************************************/

#define NO_VAR_WIDTH
#define NO_SHORT
#define NO_POINTER
#define NO_HEX
#define NO_OCT
#define SHORT_NULLPOINTER
#define NO_NULLPOINTER

/*
 * Actual printf innards.
 *
 * This code is large and complicated...
 */

#include <string.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif


/*
static char *mem;
static void mem_putchar(char c)
{
	*mem++ = c;
}


int sprintf(char *dest, const char *string, ...)
{
	mem = dest;
    va_list args;
    va_start(args, string);
    vuprintf(mem_putchar, string, args);
    va_end(args);
	*mem = 0;
    return 0;
}
*/

extern void debug_putc(char c);
void debug_printf(const char *string, ...)
{
    va_list args;
    va_start(args, string);
    vuprintf(debug_putc, string, args);
    va_end(args);
}

static void (*__write_char) (char);

#define PRINTP PRINT

static inline void PRINT(const char * ptr, unsigned int len)
{
    for(;len;len--)
    {
        __write_char(*ptr++);
    }
}

#define PAD_SP(x) __write_pad(' ',x)
#define PAD_0(x) __write_pad('0',x)

static inline void __write_pad(char c, signed char howmany)
{
    for(;howmany>0;howmany--)
    {
        __write_char(c);
    }
}


#define	BUF		40

#define PRG_RDB(x)	*x


/*
 * Macros for converting digits to letters and vice versa
 */
#define to_digit(c)	((c) - '0')
#define is_digit(c)	((c)<='9' && (c)>='0')
#define to_char(n)	((n) + '0')

/*
 * Flags used during conversion.
 */
#define	LONGINT		0x01		/* long integer */
#define	LONGDBL		0x02		/* long double; unimplemented */
#define	SHORTINT		0x04		/* short integer */
#define	ALT			0x08		/* alternate form */
#define	LADJUST		0x10		/* left adjustment */
#define	ZEROPAD		0x20		/* zero (as opposed to blank) pad */
#define	HEXPREFIX	0x40		/* add 0x or 0X prefix */
#ifdef NO_HEX
    #ifndef NO_POINTER
        #warning NO_HEX implies NO_POINTER!
        #define NO_POINTER
    #endif
#endif

void vuprintf(void (*func)(char), const char *fmt0, va_list ap)
{
    register const char *fmt; /* format string */
    register char ch;	/* character from fmt */
    register int n;		/* handy integer (short term usage) */
    register char *cp;	/* handy char pointer (short term usage) */
    const char *fmark;	/* for remembering a place in fmt */
    register unsigned char flags;	/* flags as above */
    signed char width;		/* width from format (%8d), or 0 */
    signed char prec;		/* precision from format (%.3d), or -1 */
    char sign;				/* sign prefix (' ', '+', '-', or \0) */
    unsigned long _ulong=0;	/* integer arguments %[diouxX] */
#define OCT 8
#define DEC 10
#define HEX 16
    unsigned char base;		/* base for [diouxX] conversion */
    signed char dprec;		/* a copy of prec if [diouxX], 0 otherwise */
    signed char dpad;			/* extra 0 padding needed for integers */
    signed char fieldsz;		/* field size expanded by sign, dpad etc */
    /* The initialization of 'size' is to suppress a warning that
       'size' might be used unitialized.  It seems gcc can't
       quite grok this spaghetti code ... */
    signed char size;		/* size of converted field or string */
    char buf[BUF];		/* space for %c, %[diouxX], %[eEfgG] */
    #ifndef NO_HEX
    char ox[2];			/* space for 0x hex-prefix */
    #endif
    
    __write_char = func;

    fmt = fmt0;

    /*
     * Scan the format for conversions (`%' character).
     */
    for (;;)
    {
        for (fmark = fmt; (ch = PRG_RDB(fmt)) != '\0' && ch != '%'; fmt++)
            /* void */;
        if ((n = fmt - fmark) != 0)
        {
            PRINTP(fmark, n);
        }
        if (ch == '\0')
            return;
        fmt++;		/* skip over '%' */

        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

rflag:
        ch = PRG_RDB(fmt++);
reswitch:
        if (ch=='u' || (ch|0x20)=='x')
        {
            if (flags&LONGINT)
            {
                _ulong=va_arg(ap, unsigned long);
            }
            else
            {
                register unsigned int _d;
                _d=va_arg(ap, unsigned int);
                #ifdef NO_SHORT
                _ulong = (long) _d;
                #else
                _ulong = flags&SHORTINT ? (unsigned long)(unsigned short)_d : (unsigned long)_d;
                #endif
            }
        }

        if(ch==' ')
        {
            /*
             * ``If the space and + flags both appear, the space
             * flag will be ignored.''
             *	-- ANSI X3J11
             * NOTE: Removed!
             */
            sign = ' ';
            goto rflag;
        }
        else if (ch=='#')
        {
            flags |= ALT;
            goto rflag;
        }
        else if (
            #ifndef NO_VAR_WIDTH
            ch=='*'||
            #endif
            ch=='-')
        {
            #ifndef NO_VAR_WIDTH
            if (ch=='*')
            {
                /*
                 * ``A negative field width argument is taken as a
                 * - flag followed by a positive field width.''
                 *	-- ANSI X3J11
                 * They don't exclude field widths read from args.
                 */
                if ((width = va_arg(ap, int)) >= 0)
                    goto rflag;
                width = -width;
            }
            #endif
            flags |= LADJUST;
            //NOTE: removed! flags &= ~ZEROPAD; /* '-' disables '0' */
            goto rflag;
        }
        else if (ch=='+')
        {
            sign = '+';
            goto rflag;
        }
        else if (ch=='.')
        {
        #ifndef NO_VAR_WIDTH
            if ((ch = PRG_RDB(fmt++)) == '*')
            {
                n = va_arg(ap, int);
                prec = n < 0 ? -1 : n;
                goto rflag;
            }
        #endif
            n = 0;
            while (is_digit(ch))
            {
                n = n*10 + to_digit(ch);
                ch = PRG_RDB(fmt++);
            }
            prec = n;
            goto reswitch;
        }
        else if (ch=='0')
        {
            /*
             * ``Note that 0 is taken as a flag, not as the
             * beginning of a field width.''
             *	-- ANSI X3J11
             * NOTE: WTF? Removing this adds 20bytes!
             */
            if (!(flags & LADJUST))
                flags |= ZEROPAD; /* '-' disables '0' */
            goto rflag;
        }
        else if (ch>='1' && ch<='9')
        {
            n = 0;
            do
            {
                n = 10 * n + to_digit(ch);
                ch = PRG_RDB(fmt++);
            }
            while (is_digit(ch));
            width = n;
            goto reswitch;
        }
    #ifndef NO_SHORT
        else if (ch=='h')
        {
            flags |= SHORTINT;
            goto rflag;
        }
    #endif
        else if (ch=='l')
        {
            flags |= LONGINT;
            goto rflag;
        }
        else if (ch=='c')
        {
            *(cp = buf) = va_arg(ap, int);
            size = 1;
            sign = '\0';
        }
        else if (ch=='d'||ch=='i')
        {
            if (flags&LONGINT)
            {
                _ulong=va_arg(ap, long);
            }
            else
            {
                register int _d;
                _d=va_arg(ap, int);
                #ifdef NO_SHORT
                _ulong = _d;
                #else
                _ulong = flags&SHORTINT ? (long)(short)_d : (long)_d;
                #endif
            }

            if ((long)_ulong < 0)
            {
                _ulong = -_ulong;
                sign = '-';
            }
            base = DEC;
            goto number;
        }
        #ifndef NO_OCT
        else if (ch=='o')
        {
            base = OCT;
            goto nosign;
        }
        #endif
        #ifndef NO_POINTER
        else if (ch=='p')
        {
            /*
             * ``The argument shall be a pointer to void.  The
             * value of the pointer is converted to a sequence
             * of printable characters, in an implementation-
             * defined manner.''
             *	-- ANSI X3J11
             */
            /* NOSTRICT */
            _ulong = (unsigned int)va_arg(ap, void *);
            base = HEX;
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        }
        #endif
        else if (ch=='s')
        {  // print a string from RAM
            #ifdef NO_NULLPOINTER
            cp = va_arg(ap, char *);
            #else
            if ((cp = va_arg(ap, char *)) == NULL)
            {
                cp=buf;
                #ifdef SHORT_NULLPOINTER
                cp[0] = '\0';
                #else
                cp[0] = '(';
                cp[1] = 'n';
                cp[2] = 'u';
                cp[4] = cp[3] = 'l';
                cp[5] = ')';
                cp[6] = '\0';
                #endif
            }
            #endif
            if (prec >= 0)
            {
                /*
                 * can't use strlen; can only look for the
                 * NUL in the first `prec' characters, and
                 * strlen() will go further.
                 */
                char *p = (char*)memchr(cp, 0, prec);

                if (p != NULL)
                {
                    size = p - cp;
                    if (size > prec)
                        size = prec;
                }
                else
                    size = prec;
            }
            else
                size = strlen(cp);
            sign = '\0';
        }
        else if(ch=='U'||ch=='u')
        {
            base = DEC;
            goto nosign;
        }
        else 
        #ifndef NO_HEX
        if (ch=='X'||ch=='x')
        #else
        if (0)
        #endif
        {
            #ifndef NO_HEX
            base = HEX;
            /* leading 0x/X only if non-zero */
            if (flags & ALT && _ulong != 0)
                flags |= HEXPREFIX;
            #endif
            /* unsigned conversions */
nosign:
            sign = '\0';
            /*
             * ``... diouXx conversions ... if a precision is
             * specified, the 0 flag will be ignored.''
             *	-- ANSI X3J11
             */
number:
            if ((dprec = prec) >= 0)
                flags &= ~ZEROPAD;

            /*
             * ``The result of converting a zero value with an
             * explicit precision of zero is no characters.''
             *	-- ANSI X3J11
             */
            cp = buf + BUF;
            if (_ulong != 0 || prec != 0)
            {
                register unsigned char _d, notlastdigit;
                do
                {
                    notlastdigit=(_ulong>=base);
                    _d = _ulong % base;

                    if (_d<10)
                    {
                        _d+='0';
                    }
                    else
                    {
                        _d+='a'-10;
                        #ifndef NO_HEX
                        if (ch=='X') _d&=~0x20;
                        #endif
                    }
                    *--cp=_d;
                    _ulong /= base;
                }
                while (notlastdigit);

                #ifndef NO_OCT
                // handle octal leading 0
                if (base==OCT && flags & ALT && *cp != '0')
                    *--cp = '0';
                #endif
            }

            size = buf + BUF - cp;
        }
        else
        {  //default
            /* "%?" prints ?, unless ? is NUL */
            /*TODO:if (ch == '\0')
                return;*/
            /* pretend it was %c with argument ch */
            cp = buf;
            *cp = ch;
            size = 1;
            sign = '\0';
        }

        /*
         * All reasonable formats wind up here.  At this point,
         * `cp' points to a string which (if not flags&LADJUST)
         * should be padded out to `width' places.  If
         * flags&ZEROPAD, it should first be prefixed by any
         * sign or other prefix; otherwise, it should be blank
         * padded before the prefix is emitted.  After any
         * left-hand padding and prefixing, emit zeroes
         * required by a decimal [diouxX] precision, then print
         * the string proper, then emit zeroes required by any
         * leftover floating precision; finally, if LADJUST,
         * pad with blanks.
         */

        /*
         * compute actual size, so we know how much to pad.
         */
        fieldsz = size;

        dpad = dprec - size;
        if (dpad < 0)
        {
            dpad = 0;
        }

        if (sign)
        {
            fieldsz++;
        }
        #ifndef NO_HEX
        else if (flags & HEXPREFIX)
        {
            fieldsz += 2;
        }
        #endif
        fieldsz += dpad;

        /* right-adjusting blank padding */
        if ((flags & (LADJUST|ZEROPAD)) == 0)
        {
            n = width - fieldsz;
            if (n > 0)
            {
                PAD_SP(n);
            }
        }

        /* prefix */
        if (sign)
        {
            PRINT(&sign, 1);
        }
        #ifndef NO_HEX
        else if (flags & HEXPREFIX)
        {
            ox[0] = '0';
            ox[1] = ch;
            PRINT(ox, 2);
        }
        #endif

        /* right-adjusting zero padding */
        if ((flags & (LADJUST|ZEROPAD)) == ZEROPAD)
        {
            n = width - fieldsz;
            if (n > 0)
            {
                PAD_0(n);
            }
        }

        /* leading zeroes from decimal precision */
        PAD_0(dpad);

        /* the string or number proper */
        PRINT(cp, size);

        /* left-adjusting padding (always blank) */
        if (flags & LADJUST)
        {
            n = width - fieldsz;
            if (n > 0)
            {
                PAD_SP(n);
            }
        }
    }
}
#endif
