#include "../include/args.h"
#include <iostream>



int main(int argc, char** argv)
{
	args::parse_args(argc, argv);

	return 0;
}