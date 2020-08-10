#include "notepad.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/trait.hpp>
#include <cppurses/system/system.hpp>
#include <cppurses/widget/border.hpp>
#include <cppurses/widget/widget_slots.hpp>
#include "cppurses/widget/pipe.hpp"

namespace {

void write_file(std::string const& filename, std::string const& output)
{
    auto ofs = std::ofstream{filename};
    if (ofs.fail())
        throw std::runtime_error{"Cannot open " + filename + " for writing."};
    ofs << output;
    if (!ofs)
        throw std::runtime_error{"Write to " + filename + " failed."};
}

auto read_file(std::string const& filename) -> std::string
{
    auto ifs = std::ifstream{filename};
    if (ifs.fail())
        throw std::runtime_error{filename + " Could Not Be Opened"};
    auto oss = std::ostringstream{};
    ifs >> oss.rdbuf();
    if (ifs.fail() and !ifs.eof())
        throw std::runtime_error{"Read From " + filename + " Failed"};
    return oss.str();
}

}  // namespace

using namespace cppurses;

namespace demos {

// Save Area
void Notepad::initialize()
{
    // Signals
    save_area.load_request.connect([this](std::string filename) {
        try {
            txt_trait.textbox.set_contents(::read_file(filename));
            status_bar.success(filename + " Loaded");
        }
        catch (std::runtime_error const& e) {
            status_bar.fail(e.what());
        }
    });

    save_area.save_request.connect([this](std::string filename) {
        try {
            ::write_file(filename, txt_trait.textbox.contents().str());
            status_bar.success("Saved to " + filename);
        }
        catch (std::runtime_error const& e) {
            status_bar.fail(e.what());
        }
    });
}
}  // namespace demos
