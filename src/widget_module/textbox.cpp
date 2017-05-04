#include <widget_module/widgets/textbox.hpp>

#include <painter_module/painter.hpp>
#include <system_module/key.hpp>
#include <system_module/events/paint_event.hpp>
#include <system_module/events/key_event.hpp>
#include <system_module/system.hpp>

#include <cstddef>

namespace twf {

bool Textbox::key_press_event(const Key_event& event) {
    Painter p{this};
    // Backspace
    if (event.key_code() == Key::Backspace) {
        if (this->cursor_x() == 0 && this->cursor_y() != 0) {
            if (contents_.at(cursor_index_ - 1).str() == "\n") {
                --cursor_index_;
                contents_.erase(std::begin(contents_) + cursor_index_);
                auto pos = this->position_from_index(cursor_index_);
                p.move(pos.x, pos.y);
                this->update();
                return true;
            } else {
                p.move(this->width() - 1, this->cursor_y() - 1);
                p.put(" ", false);
            }
        } else if (cursor_index_ == 0) {
            return true;
        } else if (this->cursor_x() == 0 && this->cursor_y() == 0) {
            this->scroll_up();
            // this->set_cursor_index(
            // this->index_from_position(this->width() - 1, 0));
            // return true;
        } else {
            p.move(this->cursor_x() - 1, this->cursor_y());
            p.put(" ", false);
        }
        --cursor_index_;
        contents_.erase(std::begin(contents_) + cursor_index_);
        this->erase_widget_screen();
        this->update();  // Only need this for backspace when cursor_index_ is
        // different than the index size(); you can optimize this.
        // Enter
    } else if (event.key_code() == Key::Enter) {
        if (cursor_index_ == contents_.size()) {
            contents_.append("\n");
        } else {
            contents_.insert(std::begin(contents_) + cursor_index_, "\n");
        }
        if (this->cursor_y() == this->height() - 1) {
            this->scroll_down();
        } else {
            this->set_cursor_index(cursor_index_ + 1);
        }
        this->update();
        // Character
    } else if (event.text().size() != 0) {
        if (cursor_index_ == contents_.size()) {
            contents_.append(event.text());
        } else {
            contents_.insert(std::begin(contents_) + cursor_index_,
                             event.text());
        }
        if (this->cursor_y() == this->height() - 1 &&
            this->cursor_x() == this->width() - 1) {
            this->scroll_down();
        } else {
            this->set_cursor_index(cursor_index_ + 1);
        }
        this->update();
    } else if (event.key_code() == Key::Arrow_right) {
        if (cursor_index_ == contents_.size()) {
            return true;
        }
        if (this->cursor_y() == this->height() - 1) {
            if (this->contents_.at(cursor_index_) == '\n' ||
                this->cursor_x() == this->width() - 1) {
                this->scroll_down();
            }
        }
        this->set_cursor_index(cursor_index_ + 1);
        auto pos = position_from_index(cursor_index_);
        p.move(pos.x, pos.y);
    } else if (event.key_code() == Key::Arrow_left) {
        if (cursor_index_ != 0) {
            if (this->cursor_y() == 0 && this->cursor_x() == 0) {
                this->scroll_up();
            }
            this->set_cursor_index(cursor_index_ - 1);
            auto pos = position_from_index(cursor_index_);
            p.move(pos.x, pos.y);
        }
    } else if (event.key_code() == Key::Arrow_up) {
        if (this->cursor_y() == 0) {
            this->scroll_up();
        }
        this->cursor_up();
    } else if (event.key_code() == Key::Arrow_down) {
        if (this->cursor_y() == this->height() - 1 &&
            this->position_from_index(lower_bound_).y != this->height() - 1) {
            this->scroll_down();
        }
        this->cursor_down();
    }
    return true;
}

bool Textbox::mouse_press_event(const Mouse_event& event) {
    if (event.button() == Mouse_event::Button::LeftButton) {
        cursor_index_ = index_from_position(event.local_x(), event.local_y());
        auto pos = position_from_index(cursor_index_);
        Painter p{this};
        p.move(pos.x, pos.y);
    } else if (event.button() == Mouse_event::Button::ScrollUp) {
        this->scroll_up();
    } else if (event.button() == Mouse_event::Button::ScrollDown) {
        this->scroll_down();
    }
    return true;
}

}  // namespace twf
