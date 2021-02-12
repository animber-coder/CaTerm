#ifndef CATERM_TERMINAL_INPUT_HPP
#define CATERM_TERMINAL_INPUT_HPP


namespace ox::input {

/// Wait for user input, and return with a corresponding Event.
/** Blocking call, input can be received from the keyboard, mouse, or the
 *  terminal being resized. Will return nullptr if there is an error. */
auto get() -> std::optional<Event>;

}  // namespace ox::input
#endif  // CATERM_TERMINAL_INPUT_HPP
