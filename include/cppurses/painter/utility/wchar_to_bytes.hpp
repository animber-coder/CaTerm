#ifndef CPPURSES_PAINTER_UTILITY_WCHAR_TO_BYTES_HPP
#define CPPURSES_PAINTER_UTILITY_WCHAR_TO_BYTES_HPP
#include <codecvt>
#include <locale>
#include <string>

namespace cppurses {
namespace utility {

/// Return a string of char/bytes representing the wchar_t \p ch.
inline auto wchar_to_bytes(wchar_t ch) -> std::string
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(ch);
}

/// Return a string of char/bytes representing the wstring \p w_str.
inline auto wchar_to_bytes(std::wstring w_str) -> std::string
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(w_str);
}

}  // namespace utility
}  // namespace cppurses
#endif  // CPPURSES_PAINTER_UTILITY_WCHAR_TO_BYTES_HPP
