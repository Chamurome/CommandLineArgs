#include "dictionary.hpp"
#include "CommandLineArgs.hpp"
#include <iostream>
#include <fstream>

using namespace mmo;



CommanLineArgs cmdline(
    "Application",
{
    CommandLineOption("f", true),
    CommandLineOption("r"),
    CommandLineOption("p", "80")
}, 1);


int main(int argc, const char* argv[])
{
    cmdline.arguments(argc, argv);

    for(auto it=cmdline.optionBegin(); it!=cmdline.optionEnd(); ++it) {
        std::cout << it->name << ": ";
        if(it->value==nullptr) {
            std::cout << "#OMITED";
        } else {
            std::cout << it->value;
        }
        if(it->required) {
            std::cout << "[Required]";
        }
        std::cout << '\n';
    }
    for(auto it=cmdline.argumentBegin(); it!=cmdline.argumentEnd(); ++it) {
        std::cout << *it << "\n";
    }

    return 0;
}