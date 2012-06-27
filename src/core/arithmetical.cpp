#include <libmary.h>
#include <arithmetical.h>

unsigned int random_seed;

void randomSeed(unsigned int seed)
{
	random_seed = seed;
	return;
}


// random algorithm using Fibonacci-LFSR
unsigned int random(void)
{
    unsigned int shift_bit;
	shift_bit = (random_seed & 0x0001) ^
			((random_seed & 0x0004) >> 2) ^
			((random_seed & 0x0008) >> 3) ^
			((random_seed & 0x0020) >> 5);
	random_seed = (random_seed >> 1) | (shift_bit << 15);
	return random_seed;
}

long random(long max_num)
{
	if(max_num ==0) return 0;
	return random() % max_num;
}

long random(long min_num, long max_num)
{
	if(min_num >= max_num)return 0;
	if(max_num == 0) return 0;

	return random( max_num - min_num ) + min_num;
}
