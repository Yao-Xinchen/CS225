#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "./switch number" << std::endl;
        return 0;
    }


    int input = std::atoi(argv[1]);
    int processed = 0;
    switch (input)
    {
        case 1:
            std::cout << "only print one line" << std::endl;
            processed++;
            break;
        case 2:
            std::cout << "Helloooo" << std::endl;
            processed++;
            break;
        default:
            std::cout << "Your number wasn't one or two." << std::endl;
            processed++;
            break;
    }

    std::cout << "The input was processed " << processed << " time(s)" << std::endl;
    if (processed > 1)
        std::cout << "It should have been processed once!" << std::endl;
}
