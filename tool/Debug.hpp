#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
using namespace std;

#define DEBUG true

#if(DEBUG)
	#define dout(N) cout << "DEBUG " << __FILE__ << " (" << __LINE__ << "): "\
		<< N << '\n'
#else
	#define dout(N)
#endif

#endif