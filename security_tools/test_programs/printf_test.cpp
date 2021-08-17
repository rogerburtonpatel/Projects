/* printf example */
// also prints program to show the printf commands.
// make sure to compile with g++ printf_test.cpp -o printf_test
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <string.h>

int main(int argc, char* argv[])
{
	(void)argc;
	std::string line;
	std::string program_name = argv[0];
        program_name +=	".cpp";
	std::ifstream program_in(program_name);


	while (getline(program_in, line)) {
	printf ("%s \n", line.c_str());
	}

	program_in.close();



	printf ("Characters: %c %c \n", 'a', 65);

	printf ("Decimals: %d %ld\n", 1977, 650000L);

	printf ("Preceding with blanks: %10d \n", 1977);

	printf ("Preceding with zeros: %010d \n", 1977);

	printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);

	printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);

	printf ("Width trick: %*d \n", 5, 10);

	printf ("%s \n", "A string");

	return 0;
}
