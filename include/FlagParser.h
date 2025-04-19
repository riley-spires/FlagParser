#include <iostream>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <vector>

struct Flag {
    std::string name;
    void *value;
    std::type_index type;
    bool is_set = false;
};

class FlagParser {
    private:
        int argc;
        char **argv;
        std::vector<Flag> flags;

    public:
        FlagParser(int argc, char **argv) {
            this->argc = argc;
            this->argv = argv;
        }

        template <typename T>
        T* add_flag(std::string name) {
            T *ret = new T;
            flags.push_back({.name = name, .value = ret, .type = std::type_index(typeid(T))});
            return ret;
        }

        void parse_flags() {
            for (int i = 0; i < argc; ++i) {
                std::string flag_name = argv[i];
                if (flag_name[0] != '-')
                    continue;

                while (flag_name[0] == '-') {
                    flag_name.erase(0, 1);
                }

                for (auto &flag : flags) {
                    if (flag.name != flag_name)
                        continue;

                    std::string value;
                    
                    if (i + 1 < argc) {
                        value = argv[++i];
                    } else {
                        value = "";
                    }
                    auto type = flag.type;

                    if (type == std::type_index(typeid(int))) {
                        *(int*)flag.value = std::stoi(value);
                    } else if (type == std::type_index(typeid(float))) {
                        *(float*)flag.value = std::stof(value);
                    } else if (type == std::type_index(typeid(double))) {
                        *(double*)flag.value = std::stod(value);
                    } else if (type == std::type_index(typeid(std::string))) {
                        *(std::string*)flag.value = value;
                    } else if (type == std::type_index(typeid(bool))) {
                        if (value == "" || value == "true") {
                            *(bool*)flag.value = true;
                            continue;
                        } else if (value[0] == '-') {
                            *(bool*)flag.value = true;
                            --i;
                            continue;
                        }

                        *(bool*)flag.value = value == "true";
                    } else {
                        throw std::invalid_argument("Invalid flag type: " + std::string(type.name()));
                        exit(1);
                    }
                    
                    flag.is_set = true;
                }
            }
        }

        bool is_flag_set(std::string name) {
            for (auto &flag : flags) {
                if (flag.name == name) {
                    return flag.is_set;
                }
            }

            return false;
        }

        void usage() {
            std::cout << "Usage: " << argv[0] << " [flags]" << std::endl;
            for (auto &flag : flags) {
                std::cout << "    -" << flag.name;
                if (flag.type == std::type_index(typeid(bool))) {
                    std::cout << " [true|false]";
                } else {
                    std::cout << " <value>";
                }
                std::cout << std::endl;
            }
        }
};
