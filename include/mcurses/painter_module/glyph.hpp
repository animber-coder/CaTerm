#ifndef GLYPH_HPP
#define GLYPH_HPP

#include "color.hpp"
#include "brush.hpp"

#include <stdexcept>
#include <string>
#include <utility>

namespace mcurses {

class Glyph_error : public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};

class Glyph {
public:
	Glyph() = default;

	template <typename Symbol, typename ... Attributes>
	Glyph(Symbol symbol, Attributes... attrs)
	:brush_{std::forward<Attributes>(attrs)...} {
		this->set_symbol(std::forward<Symbol>(symbol));
	}

	template <typename Symbol>
	void set_symbol(Symbol symbol) {
		if(verify_length_(std::string{symbol})) {
			symbol_ = std::string{symbol};
		} else {
			throw Glyph_error("Print size is greater than one character.");
		}
	}
	void set_brush(const Brush& brush) { brush_ = brush; }

	std::string symbol() const { return symbol_; }
	Brush& brush() { return brush_; }
	const Brush& brush() const { return brush_; }

private:
	static bool verify_length_(const std::string& s);

	std::string symbol_ = " ";
	Brush brush_;
};

} // namespace mcurses
#endif // GLYPH_HPP