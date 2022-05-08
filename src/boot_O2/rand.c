#include "global.h"

//! The latest generated random number, used to generate the next number in the sequence.
static u32 sRandInt = 1;

//! Space to store a value to be re-interpreted as a float.
//! This can't be static because it is used in z_kankyo
u32 sRandFloat;

//! These values are recommended by the algorithms book *Numerical Recipes in C. The Art of Scientific Computing*, 2nd
//! Edition, 1992, ISBN 0-521-43108-5. (p. 284):
//! > This is about as good as any 32-bit linear congruential generator, entirely adequate for many uses.
#define RAND_MULTIPLIER 1664525
#define RAND_INCREMENT 1013904223

/**
 * Gets the next integer in the sequence of pseudo-random numbers.
 */
u32 Rand_Next(void) {
    return sRandInt = (sRandInt * RAND_MULTIPLIER) + RAND_INCREMENT;
}

/**
 * Seeds the pseudo-random number generator by providing a starting value.
 */
void Rand_Seed(u32 seed) {
    sRandInt = seed;
}

/**
 * Returns a pseudo-random floating-point number between 0.0f and 1.0f, by generating
 * the next integer and masking it to an IEEE-754 compliant floating-point number
 * between 1.0f and 2.0f, returning the result subtract 1.0f.
 */
f32 Rand_ZeroOne(void) {
    sRandInt = (sRandInt * RAND_MULTIPLIER) + RAND_INCREMENT;
    sRandFloat = ((sRandInt >> 9) | 0x3F800000);
    return *((f32*)&sRandFloat) - 1.0f;
}

/**
 * Returns a pseudo-random floating-point number between -0.5f and 0.5f by the same
 * manner in which Rand_ZeroOne generates its result.
 */
f32 Rand_Centered(void) {
    sRandInt = (sRandInt * RAND_MULTIPLIER) + RAND_INCREMENT;
    sRandFloat = ((sRandInt >> 9) | 0x3F800000);
    return *((f32*)&sRandFloat) - 1.5f;
}

/**
 * Seeds a pseudo-random number at rndNum with a provided seed.
 */
void Rand_Seed_Variable(u32* rndNum, u32 seed) {
    *rndNum = seed;
}

/**
 * Generates the next pseudo-random integer from the provided rndNum.
 */
u32 Rand_Next_Variable(u32* rndNum) {
    return *rndNum = (*rndNum * RAND_MULTIPLIER) + RAND_INCREMENT;
}

/**
 * Generates the next pseudo-random floating-point number between 0.0f and
 * 1.0f from the provided rndNum.
 *
 * @remark This is also recommended by Numerical Recipes, pp. 284-5:
 * > If you need floating-point values instead of 32-bit integers, and want to avoid a divide by floating-point 2^{32},
 * > a dirty trick is to mask in an exponent that makes the value lie between 1 and 2, then subtract 1.0.
 * > [...]
 * > Your authors have tried very hard to make almost all of the material in this book machine and compiler independent
 * > — indeed, even programming language independent. This subsection is a rare aberration. Forgive us. Once in a great
 * > while the temptation to be really dirty is just irresistible."
 */
f32 Rand_ZeroOne_Variable(u32* rndNum) {
    u32 next = (*rndNum * RAND_MULTIPLIER) + RAND_INCREMENT;

    sRandFloat = ((*rndNum = next) >> 9) | 0x3F800000;
    return *((f32*)&sRandFloat) - 1.0f;
}

/**
 * Generates the next pseudo-random floating-point number between -0.5f and
 * 0.5f from the provided rndNum.
 */
f32 Rand_Centered_Variable(u32* rndNum) {
    u32 next = (*rndNum * RAND_MULTIPLIER) + RAND_INCREMENT;

    *rndNum = next;
    sRandFloat = (next >> 9) | 0x3F800000;
    return *((f32*)&sRandFloat) - 1.5f;
}
