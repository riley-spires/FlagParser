#include <iostream>
#include "FlagParser.h"


int main(int argc, char **argv) {
    FlagParser parser(argc, argv);

    int *num = parser.add_flag<int>("amount");
    double *price = parser.add_flag<double>("price");
    float *tax = parser.add_flag<float>("tax");
    std::string *str = parser.add_flag<std::string>("msg");

    parser.parse_flags();

    for (int i = 0; i < *num; ++i) {
        std::cout << i+1 << ": " << *str << std::endl;
    }

    std::cout << "Price: " << *price << std::endl;
    std::cout << "Tax: " << *tax << std::endl;

    return 0;
}
