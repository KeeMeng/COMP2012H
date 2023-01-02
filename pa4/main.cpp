// Sources: 
// www.geeksforgeeks.org/multiply-large-integers-under-large-modulo
// en.wikipedia.org/wiki/Primality_test
// en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

#include <iostream>
#include <cmath>
using namespace std;

// maximum number is 2^63-1, maximum 62 primes
long long factors[62];
long long stack[62];
int factors_index = 0;
int stack_index = 0;

// convert input string to number
long long chars_to_int(const char chars[]) {
	long long result = chars[0] - '0';
	for (int i = 1; chars[i] != '\0'; i++) {
		result *= 10;
		result += chars[i] - '0';
	}
	return result;
}

// square number and mod without overflow
long long square_mod(unsigned long long x, long long mod) {
	// since x can be 2 times larger than long long after multiplication, use unsigned
	if ((int)log2(x) < 32) {
		return (x * x) % mod;
	} else {
		// https://www.geeksforgeeks.org/multiply-large-integers-under-large-modulo/
		// Basically check each bit, if the bit is 1, add x multiplied by 2^(bit position) to number
		x %= mod;
		unsigned long long y = x;
		long long result = 0;
		while (y) {
			if (y & 1) {
				// first bit is 1
				result = (result + x) % mod;
			}
			// double a
			x = (x << 1) % mod;
			// half b
			y >>= 1;
		}
		return result;
	}
}

// (x^2 + c) mod n
long long g(const long long x, const long long n, const long long c) {
	return (square_mod(x, n) + c - 1) % n;
}

long long gcd(long long x, long long y) {
	return y ? gcd(y, x % y) : x;
}

// https://en.wikipedia.org/wiki/Primality_test
bool is_prime(const long long n) {
	if (n % 2 == 0 || n % 3 == 0) {
		if (n == 2 || n == 3) {
			return true;
		} else {
			return false;
		}
	} else if (n <= 1) {
		return false;
	} else {
		// all primes are 6k±1 
		for (long long i = 5; i * i <= n; i += 6) {
			if (n % i == 0 || n % (i + 2) == 0) {
				return false;
			}
		}
		return true;
	}
}

// https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Algorithm
long long factorize(const long long n, long long c) {
	long long x, y, d, diff;
	do {
		x = c;
		y = c;
		do {
			x = g(x, n, c);
			y = g(g(y, n, c), n, c);
			diff = (x < y) ? (y - x) : (x - y);
			d = gcd(diff, n);
		} while (d == 1);
		c++;
		// lol
	} while (d == n);
	return d;
}

// insert prime number to factors in the right order
void insert_sort(const long long factor) {
	factors_index++;
	if (factors_index == 0) {
		factors[0] = factor;
	} else {
		for (int i = factors_index; i >= 1; i--) {
			if (factor >= factors[i - 1]) {
				factors[i] = factor;
				return;
			} else {
				factors[i] = factors[i - 1];
			}
		}
		// factor was not inserted in loop
		factors[0] = factor;
	}
}

int main(int argc, char *argv[]) {
	long long start, end;
	
	if (argc > 1) {
		start = chars_to_int(argv[1]);
		end = chars_to_int(argv[2]);
	} else {
		// my own input for testing
		cout << "Start: ";
		cin >> start;
		cout << "End: ";
		cin >> end;
	}
	
	// pre calculated primes to 1000
	int small_primes[167] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };
	int small_primes_square[167] = { 9, 25, 49, 121, 169, 289, 361, 529, 841, 961, 1369, 1681, 1849, 2209, 2809, 3481, 3721, 4489, 5041, 5329, 6241, 6889, 7921, 9409, 10201, 10609, 11449, 11881, 12769, 16129, 17161, 18769, 19321, 22201, 22801, 24649, 26569, 27889, 29929, 32041, 32761, 36481, 37249, 38809, 39601, 44521, 49729, 51529, 52441, 54289, 57121, 58081, 63001, 66049, 69169, 72361, 73441, 76729, 78961, 80089, 85849, 94249, 96721, 97969, 100489, 109561, 113569, 120409, 121801, 124609, 128881, 134689, 139129, 143641, 146689, 151321, 157609, 160801, 167281, 175561, 177241, 185761, 187489, 192721, 196249, 201601, 208849, 212521, 214369, 218089, 229441, 237169, 241081, 249001, 253009, 259081, 271441, 273529, 292681, 299209, 310249, 316969, 323761, 326041, 332929, 344569, 351649, 358801, 361201, 368449, 375769, 380689, 383161, 398161, 410881, 413449, 418609, 426409, 434281, 436921, 452929, 458329, 466489, 477481, 491401, 502681, 516961, 528529, 537289, 546121, 552049, 564001, 573049, 579121, 591361, 597529, 619369, 635209, 654481, 657721, 674041, 677329, 683929, 687241, 703921, 727609, 734449, 737881, 744769, 769129, 776161, 779689, 786769, 822649, 829921, 844561, 863041, 877969, 885481, 896809, 908209, 935089, 942841, 954529, 966289, 982081, 994009 };
	
	long long n, factor;
	for (long long number = start; number <= end; number++) {
		n = number;
		cout << n << '=';
		
		// trial division for 2
		while (n % 2 == 0 && n != 2) {
			cout << "2*";
			n >>= 1;
			// bitshift multiply
		}
		
		// trial division for other small prime numbers
		for (int i = 0; i < 167; i++) {
			while (n % small_primes[i] == 0 && n != small_primes[i]) {
				cout << small_primes[i] << '*';
				n /= small_primes[i];
			}
			// optimisation added after submission :(
			if (small_primes_square[i] > n) {
				break;
			}
		}
		
		// all prime factors found
		if (is_prime(n)) {
			cout << n << '\n';
			continue;
		}
		
		// keep factorising composite numbers in stack
		stack[0] = n;
		stack_index = 0;
		factors_index = -1;
		while (true) {
			if (is_prime(stack[stack_index])) {
				insert_sort(stack[stack_index--]);
				if (stack_index == -1) {
					break;
				}
			} else {
				factor = factorize(stack[stack_index], 2);
				if (is_prime(factor)) {
					// found a prime factor, replace stack item
					insert_sort(factor);
					stack[stack_index] = stack[stack_index] / factor;
				} else {
					// need to factorise two composite factors
					stack[stack_index + 1] = stack[stack_index] / factor;
					stack[stack_index++] = factor;
				}
			}
		}
		
		// output all factors
		for (int i = 0; i < factors_index; i++) {
			cout << factors[i] << '*';
		}
		cout << factors[factors_index] << '\n';
	}
	
	// only flush at the end for speed
	cout << flush;
	
	return 0;
}
