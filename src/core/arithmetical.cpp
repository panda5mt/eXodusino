#include <libmary.h>
#include <arithmetical.h>

unsigned int random_seed;


int atoi(char *str) {
    int num = 0;
    int type = 0;

    // 先頭に+付いてたら無視する
    if ( *str == '+' ) {
        str++;
    }
    // 先頭に-付いてたらtypeフラグを立てておく
    else if ( *str == '-' ) {
        type = 1;
        str++;
    }

    while(*str != '\0'){
        // 0～9以外の文字列ならそこで終了
        if ( *str < 48 || *str > 57 ) {
            break;
        }
        num += *str - 48;
        num *= 10;
        str++;
    }

    num /= 10;

    // -符号が付いていたら0から引くことで負の値に変換する
    if ( type ) {
        num = 0 - num;
    }

    return num;
}
void randomSeed(unsigned int seed)
{
	random_seed = seed;
	return;
}

// random algorithm using linear congruential method
unsigned int random(void)
{
	int hi,lo,x;

	x = random_seed;

	if(x == 0)x = 123459876L;

	hi = x / 127773L;
	lo = x % 127773L;
	x = 16807L * lo - 2836L * hi;

	if(x < 0)x += 0x7FFFFFFFL;
	random_seed = x;

	return (x % ((unsigned long int)0x7FFFFFFFL + 1));

}

// random algorithm using Fibonacci-LFSR
unsigned int random_LFSR(void)
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
