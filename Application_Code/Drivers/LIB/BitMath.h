/**
 * \addtogroup Drivers
 * This group contain HAL and MCAL drivers. And necessary libraries
 * @{
 * \addtogroup LIBs
 * This group includes necessary libraries
 * @{
 * \file BitMath.h
 * \brief this file contains macros function for bits operation
 * \author Mustafa M.Montaser
 * \version v1.0.0
 * \date 17-Feb-2023
 * */

/** @} */
/** @} */


#ifndef _BIT_MATH_H
#define _BIT_MATH_H


/* write value for single bit */
#define WRT_BIT(REG, BIT_INDEX, VAL)			REG = ((REG & (~(1 << BIT_INDEX))) | (VAL << BIT_INDEX))

/* write value for 2 bits */
#define WRT_2BITS(REG, LS_BIT_INDEX, VAL)		REG = (REG & (~(0b11 << LS_BIT_INDEX))) | (VAL << LS_BIT_INDEX)

/* write value for 3 bits */
#define WRT_3BITS(REG, LS_BIT_INDEX, VAL)		REG = (REG & (~(0b111 << LS_BIT_INDEX))) | (VAL << LS_BIT_INDEX)

/* write value for 4 bits */
#define WRT_4BITS(REG, LS_BIT_INDEX, VAL)		REG = (REG & (~(0b1111 << LS_BIT_INDEX))) | (VAL << LS_BIT_INDEX)

/* write value for 5 bits */
#define WRT_5BITS(REG, LS_BIT_INDEX, VAL)		REG = (REG & (~(0b11111 << LS_BIT_INDEX))) | (VAL << LS_BIT_INDEX)

/* write value for 16 bits */
#define WRT_16BITS(REG, LS_BIT_INDEX, VAL)		REG = (REG & (~(0xffff << LS_BIT_INDEX))) | (VAL << LS_BIT_INDEX)

/* set single bit */
#define SET_BIT(REG, BIT_INDEX)					REG |= (1 << BIT_INDEX)

/* clear single bit */
#define CLR_BIT(REG, BIT_INDEX)					REG &= (~(1 << BIT_INDEX))

/* toggle single bit */
#define TOG_BIT(REG, BIT_INDEX)					REG ^= (1 << BIT_INDEX)

/* get single bit value */
#define GET_BIT(REG, BIT_INDEX)					((REG >> BIT_INDEX) & 1)

/* get 3 bits value */
#define GET_3BITS(REG, BIT_INDEX)				((REG >> BIT_INDEX) & 0b111)


#endif /* _BIT_MATH_H */

