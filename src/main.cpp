#include "include/siff.h"

void usage()
{
    std::cout << "usage: ./siff file1 file2\n";
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        usage();
    }

    Siff siff(argv[1], argv[2]);

    return 0;
}
