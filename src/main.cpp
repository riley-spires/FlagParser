#include <iostream>
#include "FlagParser.h"


int main(int argc, char **argv) {
    FlagParser parser(argc, argv);

    int *num = parser.add_flag<int>("amount");
    double *price = parser.add_flag<double>("price");
    float *tax = parser.add_flag<float>("tax");
    std::string *str = parser.add_flag<std::string>("msg");
    bool *flag = parser.add_flag<bool>("flag");

    parser.parse_flags();

    if (!parser.is_flag_set("amount") || !parser.is_flag_set("price") || !parser.is_flag_set("tax") || !parser.is_flag_set("msg")) {
        parser.usage();
        return 1;
    }

    for (int i = 0; i < *num; ++i) {
        std::cout << i+1 << ": " << *str << std::endl;
    }

    std::cout << "Price: " << *price << std::endl;
    std::cout << "Tax: " << *tax << std::endl;

    std::cout << "Flag: " << *flag << std::endl;

    return 0;
}
