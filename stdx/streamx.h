#include <istream>
#include <ostream>
#include <type_traits>

namespace stdx {
    template<class T>
    void binary_write(std::ostream& stream, T val) {
        static_assert(std::is_pod<T>(), "Type is not POD");
        stream.write(reinterpret_cast<char*>(&val), sizeof(T));
    }

    template<class T>
    T binary_read(std::istream& stream) {
        static_assert(std::is_pod<T>(), "Type is not POD");
        T val;
        stream.read(reinterpret_cast<char*>(&val), sizeof(T));
        return val;
    }
}