#include <vector>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{ 
    auto core_id = [&] () -> std::string {
        if (argc > 1) {
            return argv[1];
        }

        return "???";
    }();

    std::vector<uint8_t> b1;

    b1.resize(1024 * 1024 * 1024);
    ::read(::open("/dev/random", O_RDONLY), b1.data(), b1.size());

    for (std::size_t i = 0; i < 100000; ++i) {
        std::vector<uint8_t> b2;

        b2.resize(b1.size());
        std::memcpy(b2.data(), b1.data(), b1.size());

        if (b1 != b2) {
            std::cout << " Iteration " << i << ": MISMATCH ON CORE " << core_id << std::endl;
        }
    }

    return 0;
}
