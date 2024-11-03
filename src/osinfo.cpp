#include <osinfo>
#include <fstream>
#include <iostream>
#include <vector>
#include <format>

// This is a helper function to split strings when '=' comes
// Do not use for any other cases
std::vector<std::string> split(std::string &s)
{
    std::vector<std::string> vec{};
    std::string current_string = "";

    for (size_t i = 0; i < s.size(); i++)
    {
        if (s.at(i) == '=')
        {
            vec.push_back(s.substr(0, i));
            vec.push_back(s.substr(i + 1));
        }
    }

    return vec;
}

std::string read_all_bytes(FILE *file)
{
    std::string buff;
    int size = 1024;
    char s[size];

    while (fgets(s, size, file) != NULL)
    {
        buff.append(s);
    }
    return buff;
}

// determine which distro family it belongs
std::string osinfo::get_distro_family()
{
    std::ifstream in("/etc/os-release");
    std::string line;
    std::vector<std::string> vec;
    while (std::getline(in, line))
    {
        vec = split(line);
        if (vec.at(0) == "ID_LIKE")
        {
            return vec.at(1);
        }
    }
    return "";
}

// This function will get all the package count
// from system. This will be count from all package managers
std::string osinfo::get_package_count()
{
    std::string package_info = "Packages: ";

    // getting apt packages
    auto out = popen("apt list --installed 2>/dev/null | wc -l", "r");
    if (out != nullptr)
    {
        int apt_package_cout = atoi(read_all_bytes(out).c_str()) - 1;
        if (apt_package_cout != -1)
        {
            package_info.append(std::format("{}(deb) ", apt_package_cout));
        }
        
        pclose(out);
    }

    // getting snap packages
    out = popen("snap list 2>/dev/null | wc -l", "r");
    if (out != nullptr)
    {
        int snap_package_cout = atoi(read_all_bytes(out).c_str()) - 1;
        if (snap_package_cout != -1)
        {
            package_info.append(std::format("{}(snap) ", snap_package_cout));
        }
        
        pclose(out);
    }
    // getting flatpak
    out = popen("flatpak list 2>/dev/null| wc -l", "r");
    if (out != nullptr)
    {
        int flatpak_package_cout = atoi(read_all_bytes(out).c_str()) - 1;
        if (flatpak_package_cout != -1)
        {
            package_info.append(std::format("{}(flatpak) ", flatpak_package_cout));
        }
        
        
        pclose(out);
    }
    

    return package_info;
}

// This function will get os name
std::string osinfo::get_os_name()
{
    std::string s = "OsName: ";
    bool is_name_fetched = false;
    std::ifstream in("/etc/os-release");
    std::string line;
    std::vector<std::string> vec;
    while (std::getline(in, line))
    {
        vec = split(line);
        if (vec.at(0) == "PRETTY_NAME")
        {
            s.append(vec.at(1));
            is_name_fetched = true;
        }
    }

    if (!is_name_fetched)
    {
        s.append("Unkown");   
    }
    return s;
}


// class osinfo
osinfo::osinfo::osinfo()
{
    this->os_name = get_os_name();
    this->package_count = get_package_count();
}

osinfo::osinfo::~osinfo()
{
}