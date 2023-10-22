/*
 * Module: common macros
 * file name: common_macros.h
 * description: contains common macros like SET_BIT,CLEAR_BIT
 * Author: Aya Ahmed
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_
/* to set a certain bit to 1*/
#define SET_BIT(REG,BIT_NUM)        ( REG= REG | (1<<BIT_NUM) )

/* to set a certain bit to 0*/
#define CLEAR_BIT(REG,BIT_NUM)      ( REG= REG & (~(1<<BIT_NUM)) )

/* to check if a certain bit is set to 1*/
#define BIT_IS_SET(REG,BIT_NUM)     (REG & (1<<BIT_NUM) )

/* to check if a certain bit is set to 0*/
#define BIT_IS_CLEAR(REG,BIT_NUM)     (!(REG & (1<<BIT_NUM)) )





#endif /* COMMON_MACROS_H_ */
