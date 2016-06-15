/*
 * hexdump.c
 *
 *  Created on: Jun 9, 2016
 *      Author: hernan
 */

#include "hexdumpTest.h"

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 21
#endif

void hexdump(void *mem, unsigned int len,FILE*archi)
{
        unsigned int i, j;
        for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
        {
                /* print offset */
                if(i % HEXDUMP_COLS == 0)
                {
                        printf("0x%06x: ", i);
                        fprintf(archi,"0x%06x: ",i);
                }

                /* print hex data */
                if(i < len)
                {
                        printf("%02x ", 0xFF & ((char*)mem)[i]);
                        fprintf(archi,"%02x ",0xFF & ((char*)mem)[i]);
                }
                else /* end of block, just aligning for ASCII dump */
                {
                        printf("   ");
                        fprintf(archi,"   ");
                }

                /* print ASCII dump */
                if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
                {
                        for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
                        {
                                if(j >= len) /* end of block, not really printing */
                                {
                                        putchar(' ');
                                        fputc(' ',archi);
                                }
                                else if(isprint(((char*)mem)[j])) /* printable char */
                                {
                                        putchar(0xFF & ((char*)mem)[j]);
                                        fputc(0xFF & ((char*)mem)[j],archi);
                                }
                                else /* other char */
                                {
                                        putchar('.');
                                        fputc('.',archi);
                                }
                        }
                        putchar('\n');
                        fputc('\n',archi);
                }
        }
}

