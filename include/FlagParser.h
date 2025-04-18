#include <stdexcept>
#include <string>
#include <typeindex>
#include <vector>

struct Flag {
    std::string name;
    void *value;
    std::type_index type;
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
            auto ret = new T;
            flags.push_back({name, ret, std::type_index(typeid(T))});
            return ret;
        }

        void parse_flags() {
            for (int i = 0; i < argc; ++i) {
                if (argv[i][0] != '-')
                    continue;

                std::string flag_name = argv[i];
                flag_name.erase(0, 1);

                for (auto &flag : flags) {
                    if (flag.name != flag_name)
                        continue;
                    
                    std::string value = argv[++i];
                    auto type = flag.type;

                    if (type == std::type_index(typeid(int))) {
                        *(int*)flag.value = std::stoi(value);
                    } else if (type == std::type_index(typeid(float))) {
                        *(float*)flag.value = std::stof(value);
                    } else if (type == std::type_index(typeid(double))) {
                        *(double*)flag.value = std::stod(value);
                    } else if (type == std::type_index(typeid(std::string))) {
                        *(std::string*)flag.value = value;
                    } else {
                        throw std::invalid_argument("Invalid flag type: " + std::string(type.name()));
                        exit(1);
                    }
                }
            }
        }
};
