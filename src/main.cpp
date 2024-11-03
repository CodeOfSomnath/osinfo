#include <iostream>
#include <sys/utsname.h>
#include <memory>
#include <osinfo>


int main(int argc, char const *argv[])
{
    std::cout << osinfo::get_package_count() << std::endl;
    return 0;
}
