/*
 * (c) 2015 fullhan.com
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __FH81_H__
#define __FH81_H__

#include <asm/types.h>

typedef char SINT8;
typedef short SINT16;
typedef int SINT32;
typedef long long SINT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef float ieee_single;
typedef double ieee_double;
typedef unsigned long boolean;
#define lift_shift_bit_num(bit_num)			(1<<bit_num)
#define reg_read(addr)                  (*((volatile UINT32 *)(addr)))
#define reg_write(addr,value)           (*(volatile UINT32 *)(addr)=(value))
#define GET_REG(addr)                   reg_read(addr)
#define SET_REG(addr,value)             reg_write(addr,value)
#define SET_REG_M(addr,value,mask)      reg_write(addr,(reg_read(addr)&(~(mask)))|((value)&(mask)))
#define SET_REG_B(addr,element,highbit,lowbit) SET_REG_M((addr),((element)<<(lowbit)),(((1<<((highbit)-(lowbit)+1))-1)<<(lowbit)))
#define GET_REG8(addr)                  (*((volatile UINT8 *)(addr)))
#define SET_REG8(addr,value)            (*(volatile UINT8 *)(addr)=(value))
#define read_reg(addr)                  (*((volatile uint32 *)(addr)))
#define write_reg(addr, reg)            (*((volatile uint32 *)(addr))) = (uint32)(reg)
#define inw(addr)                       (*((volatile uint32 *)(addr)))
#define outw(addr, reg)                 (*((volatile uint32 *)(addr))) = (uint32)(reg)

#define DELAY(times)  do{\
	int i=0;\
	for(i=0;i<times;i++){}\
}while(0)

#endif /*__FH81_H__*/
