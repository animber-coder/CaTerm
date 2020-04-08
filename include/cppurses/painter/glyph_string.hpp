#ifndef CPPURSES_PAINTER_GLYPH_STRING_HPP
#define CPPURSES_PAINTER_GLYPH_STRING_HPP
#include <algorithm>
#include <codecvt>
#include <cstddef>
#include <locale>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include <cppurses/painter/attribute.hpp>
#include <cppurses/painter/glyph.hpp>
#include <cppurses/painter/utility/wchar_to_bytes.hpp>

namespace cppurses {

/// Holds a collection of Glyphs with a similar interface to std::string.
class Glyph_string : private std::vector<Glyph> {
   public:
    /// Used to indicate 'Until the end of the string'.
    static auto constexpr npos = static_cast<std::size_t>(-1);

   public:
    /// Default constructs an empty Glyph_string.
    Glyph_string() = default;

    Glyph_string(Glyph_string const&) = default;
    Glyph_string(Glyph_string&&)      = default;
    auto operator=(Glyph_string const&) -> Glyph_string& = default;
    auto operator=(Glyph_string &&) -> Glyph_string& = default;

    /// Construct with \p symbols, each having given Attributes applied to them.
    template <typename... Attributes>
    Glyph_string(std::wstring const& symbols, Attributes... attrs)
    {
        this->append(symbols, attrs...);
    }

    /// Construct with \p symbols, each having given Attributes applied to them.
    template <typename... Attributes>
    Glyph_string(wchar_t const* symbols, Attributes... attrs)
    {
        this->append(symbols, attrs...);
    }

    /// Construct with \p symbols, each having given Attributes applied to them.
    template <typename... Attributes>
    Glyph_string(std::string const& symbols, Attributes... attrs)
    {
        this->append(symbols, attrs...);
    }

    /// Construct with \p symbols, each having given Attributes applied to them.
    template <typename... Attributes>
    Glyph_string(char const* symbols, Attributes... attrs)
    {
        this->append(symbols, attrs...);
    }

    /// Construct with \p count \p glyph's, adding given Attributes to each.
    explicit Glyph_string(Glyph const& glyph, std::size_t count = 1)
    {
        for (; count != 0; --count)
            this->append(glyph);
    }

    /// Construct with iterators from any container providing Input Iterators.
    template <typename InputIterator>
    Glyph_string(InputIterator first, InputIterator last)
        : vector<Glyph>::vector(first, last)
    {}

   public:
    /// Convert to a std::wstring, each Glyph being a wchar_t.
    auto w_str() const -> std::wstring
    {
        auto result = std::wstring{};
        result.reserve(this->length());
        for (auto const& glyph : *this)
            result.push_back(glyph.symbol);
        return result;
    }

    /// Convert to a std::string.
    auto str() const -> std::string
    {
        return utility::wchar_to_bytes(this->w_str());
    }

    /// Return the length in Glyphs of the Glyph_string.
    auto length() const -> size_type { return this->size(); }

   public:
    /// Compound concatenation assignment operator to append a Glyph.
    auto operator+=(Glyph const& glyph) -> Glyph_string&
    {
        return this->append(glyph);
    }

    /// Concatenation operator to append a Glyph_string.
    auto operator+(Glyph_string const& gs) const -> Glyph_string
    {
        return Glyph_string{*this}.append(gs);
    }

    /// Append single Glyph to the end of the Glyph_string w/given Attributes.
    template <typename... Attributes>
    auto append(Glyph const& symbol, Attributes... attrs) -> Glyph_string&
    {
        this->push_back(symbol);
        this->back().brush.add_attributes(attrs...);
        return *this;
    }

    /// Append a c-string with given Attributes to the end of the Glyph_string.
    template <typename... Attributes>
    auto append(char const* symbols, Attributes... attrs) -> Glyph_string&
    {
        auto converter   = std::wstring_convert<std::codecvt_utf8<wchar_t>>{};
        auto wide_string = std::wstring{converter.from_bytes(symbols)};
        this->reserve(this->size() + wide_string.size());
        for (wchar_t sym : wide_string)
            this->append(Glyph{sym, attrs...});
        return *this;
    }

    /// Append std::string with given Attributes to the end of the Glyph_string.
    template <typename... Attributes>
    auto append(std::string const& symbols, Attributes... attrs)
        -> Glyph_string&
    {
        return this->append(symbols.c_str(), attrs...);
    }

    /// Append a wide c-string with given Attributes to the end of Glyph_string.
    template <typename... Attributes>
    auto append(wchar_t const* symbols, Attributes... attrs) -> Glyph_string&
    {
        for (auto i = 0uL; symbols[i] != L'\0'; ++i)
            this->append(Glyph{symbols[i], attrs...});
        return *this;
    }

    /// Append std::wstring with given Attributes to the end of Glyph_string.
    template <typename... Attributes>
    auto append(std::wstring const& symbols, Attributes... attrs)
        -> Glyph_string&
    {
        for (wchar_t sym : symbols)
            this->append(Glyph{sym, attrs...});
        return *this;
    }

    /// Append another Glyph_string with Attributes to the end of Glyph_string.
    template <typename... Attributes>
    auto append(Glyph_string const& gs, Attributes... attrs) -> Glyph_string&
    {
        for (Glyph const& glyph : gs)
            this->append(glyph, attrs...);
        return *this;
    }

    /// Add a list of Attributes to every Glyph within the Glyph_string.
    template <typename... Attributes>
    void add_attributes(Attributes... attrs)
    {
        for (auto& glyph : *this)
            glyph.brush.add_attributes(attrs...);
    }

    /// Remove a single Attribute from every Glyph within the Glyph_string.
    void remove_attribute(Attribute attr)
    {
        for (Glyph& glyph : *this)
            glyph.brush.remove_attributes(attr);
    }

   public:
    using std::vector<Glyph>::value_type;
    using std::vector<Glyph>::allocator_type;
    using std::vector<Glyph>::size_type;
    using std::vector<Glyph>::difference_type;
    using std::vector<Glyph>::reference;
    using std::vector<Glyph>::const_reference;
    using std::vector<Glyph>::pointer;
    using std::vector<Glyph>::const_pointer;
    using std::vector<Glyph>::iterator;
    using std::vector<Glyph>::const_iterator;
    using std::vector<Glyph>::reverse_iterator;
    using std::vector<Glyph>::const_reverse_iterator;

    using std::vector<Glyph>::operator[];
    using std::vector<Glyph>::size;
    using std::vector<Glyph>::assign;
    using std::vector<Glyph>::get_allocator;
    using std::vector<Glyph>::at;
    using std::vector<Glyph>::front;
    using std::vector<Glyph>::back;
    using std::vector<Glyph>::data;
    using std::vector<Glyph>::begin;
    using std::vector<Glyph>::cbegin;
    using std::vector<Glyph>::end;
    using std::vector<Glyph>::cend;
    using std::vector<Glyph>::rbegin;
    using std::vector<Glyph>::crbegin;
    using std::vector<Glyph>::rend;
    using std::vector<Glyph>::crend;
    using std::vector<Glyph>::empty;
    using std::vector<Glyph>::max_size;
    using std::vector<Glyph>::reserve;
    using std::vector<Glyph>::capacity;
    using std::vector<Glyph>::shrink_to_fit;
    using std::vector<Glyph>::clear;
    using std::vector<Glyph>::insert;
    using std::vector<Glyph>::erase;
    using std::vector<Glyph>::push_back;
    using std::vector<Glyph>::pop_back;
    using std::vector<Glyph>::resize;
    using std::vector<Glyph>::swap;
};

inline auto operator""_gs(char const* x, std::size_t) -> Glyph_string
{
    return {x};
}

inline auto operator""_gs(wchar_t const* x, std::size_t) -> Glyph_string
{
    return {x};
}

// Attribute -------------------------------------------------------------------
inline auto operator|(Glyph_string& gs, Attribute attr) -> Glyph_string&
{
    gs.add_attributes(attr);
    return gs;
}

inline auto operator|(Glyph_string&& gs, Attribute attr) -> Glyph_string
{
    return gs | attr;
}

inline auto operator|(wchar_t const* gs, Attribute attr) -> Glyph_string
{
    return Glyph_string{gs} | attr;
}

// BackgroundColor -------------------------------------------------------------
inline auto operator|(Glyph_string& gs, BackgroundColor c) -> Glyph_string&
{
    gs.add_attributes(c);
    return gs;
}

inline auto operator|(Glyph_string&& gs, BackgroundColor c) -> Glyph_string
{
    return gs | c;
}

inline auto operator|(wchar_t const* gs, BackgroundColor c) -> Glyph_string
{
    return Glyph_string{gs} | c;
}

// ForegroundColor -------------------------------------------------------------
inline auto operator|(Glyph_string& gs, ForegroundColor c) -> Glyph_string&
{
    gs.add_attributes(c);
    return gs;
}

inline auto operator|(Glyph_string&& gs, ForegroundColor c) -> Glyph_string
{
    return gs | c;
}

inline auto operator|(wchar_t const* gs, ForegroundColor c) -> Glyph_string
{
    return Glyph_string{gs} | c;
}

/// Equality comparison on each Glyph in the Glyph_strings.
inline auto operator==(Glyph_string const& x, Glyph_string const& y) -> bool
{
    return std::equal(std::begin(x), std::end(x), std::begin(y), std::end(y));
}

/// Inequality comparison on each Glyph in the Glyph_strings.
inline auto operator!=(Glyph_string const& x, Glyph_string const& y) -> bool
{
    return not(x == y);
}

}  // namespace cppurses
#endif  // CPPURSES_PAINTER_GLYPH_STRING_HPP
