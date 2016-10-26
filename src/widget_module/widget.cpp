#include <mcurses/widget_module/widget.hpp>
#include <mcurses/system_module/system.hpp>
#include <mcurses/system_module/events/paint_event.hpp>
#include <mcurses/painter_module/color.hpp>
#include <mcurses/painter_module/painter.hpp>
#include <mcurses/system_module/events/key_event.hpp>
#include <mcurses/system_module/events/mouse_event.hpp>
#include <mcurses/system_module/events/resize_event.hpp>
#include <mcurses/system_module/events/move_event.hpp>
#include <mcurses/system_module/events/close_event.hpp>

#include <memory>

namespace mcurses {

Widget::Widget()
{
	this->initialize();
}

void Widget::initialize()
{
	this->close = [this](){ System::post_event(this, std::make_unique<Close_event>()); };
	this->close.track(this->destroyed);

	this->hide = [this](){ this->set_visible(false); };
	this->hide.track(this->destroyed);

	this->show = [this](){ this->set_visible(true); };
	this->show.track(this->destroyed);

	this->repaint = [this](){ Paint_event e; System::send_event(this, e); };
	this->repaint.track(this->destroyed);

	this->give_focus = [this](){ std::bind(&Widget::set_focus, this, true); };
	this->give_focus.track(this->destroyed);

	this->update_me = [this](){ std::bind(&Widget::update, this); };
	this->update_me.track(this->destroyed);

	return;
}

bool
Widget::has_coordinates(unsigned glob_x, unsigned glob_y)
{
	if((glob_x >= this->global_x()) && (glob_x <= (this->global_max_x()))
		&& (glob_y >= this->global_y()) && (glob_y <= (this->global_max_y())))
	{
		return true;
	}
	return false;
}

void Widget::set_geometry(unsigned x, unsigned y, unsigned width, unsigned height)
{
	this->set_x(x);
	this->set_y(y);
	this->set_width(width);
	this->set_height(height);
	return;
}

void Widget::set_fixed_width(unsigned width)
{
	this->set_min_width(width);
	this->set_max_width(width);
	this->Layout_param_changed(); 
	return;
}

void Widget::set_fixed_height(unsigned height)
{
	this->set_min_height(height);
	this->set_max_height(height);
	this->Layout_param_changed(); 
	return;
}

void
Widget::update()
{
	System::post_event(this, std::make_unique<Paint_event>());
	return;
}

bool Widget::event(Event& event)
{
	// Move_event
	if(event.type() == Event::Type::Move) {
		this->move_event(static_cast<Move_event&>(event));
		return event.is_accepted();
	}

	// Resize_event
	if(event.type() == Event::Type::Resize) {
		this->resize_event(static_cast<Resize_event&>(event));
		return event.is_accepted();
	}

	// Paint_event
	if(event.type() == Event::Type::Paint) {
		if(this->visible()) {
			this->paint_event(static_cast<Paint_event&>(event));
		} else {
			this->paint_hidden_widget();
		}
		return event.is_accepted();
	}

	// Mouse_events
	if(event.type() == Event::Type::MouseButtonPress) {
		if(this->focus_policy() == Focus_policy::ClickFocus
			|| this->focus_policy() == Focus_policy::StrongFocus) {
			System::set_focus_widget(this);
		}
		this->mouse_press_event(static_cast<Mouse_event&>(event));
		return event.is_accepted();
	}
	if(event.type() == Event::Type::MouseButtonRelease) {
		this->mouse_release_event(static_cast<Mouse_event&>(event));
		return event.is_accepted();
	}
	if(event.type() == Event::Type::MouseButtonDblClick) {
		this->mouse_double_click_event(static_cast<Mouse_event&>(event));
		return event.is_accepted();
	}
	if(event.type() == Event::Type::Wheel) {
		this->wheel_event(static_cast<Mouse_event&>(event));
		return event.is_accepted();
	}
	if(event.type() == Event::Type::MouseMove && this->has_mouse_tracking()) {
		this->mouse_move_event(static_cast<Mouse_event&>(event));
		return event.is_accepted();
	}

	// KeyEvent
	if(event.type() == Event::Type::KeyPress) {
		this->key_press_event(static_cast<Key_event&>(event));
		return event.is_accepted();
	}
	if(event.type() == Event::Type::KeyRelease) {
		this->key_release_event(static_cast<Key_event&>(event));
		return event.is_accepted();
	}

	// Close Event
	if(event.type() == Event::Type::Close) {
		this->close_event(static_cast<Close_event&>(event));
		return event.is_accepted();
	}

	return Object::event(event);
}

void Widget::move_event(Move_event& event)
{
	this->set_x(event.new_x());
	this->set_y(event.new_y());
	Widget* parent = dynamic_cast<Widget*>(this->parent());
	if (parent) { parent->update(); }
	this->update();
	event.accept();
	return;
}

void Widget::resize_event(Resize_event& event)
{
	this->set_width(event.new_width());
	this->set_height(event.new_height());
	if (event.new_width() < event.old_width() || event.new_height() < event.old_height()) {
		Widget* parent = dynamic_cast<Widget*>(this->parent());
		if (parent) { parent->update(); }
	}
	this->update();
	event.accept();
	return;
}

void Widget::paint_event(Paint_event& event)
{
	// Post paint event to each child
	for(Object* c : this->children()) {
		Widget* child = dynamic_cast<Widget*>(c);
		if(child) {
			child->update();
		}
	}
	event.accept();
	return;
}

void Widget::paint_hidden_widget()
{
	Painter p{this};
	Widget* parent = dynamic_cast<Widget*>(this->parent());
	Color background = Color::Black;
	if(parent) {
		background = parent->palette().background();
	}
	p.fill(0, 0, this->width(), this->height(), background);
}

void Widget::mouse_press_event(Mouse_event& event)
{
	event.ignore();
	return;
}

void Widget::mouse_release_event(Mouse_event& event)
{
	event.ignore();
	return;
}

void Widget::mouse_double_click_event(Mouse_event& event)
{
	event.ignore();
	return;
}

void Widget::wheel_event(Mouse_event& event)
{
	event.ignore();
	return;
}

void Widget::mouse_move_event(Mouse_event& event)
{
	event.ignore();
	return;
}

void Widget::key_press_event(Key_event& event)
{
	event.ignore();
	return;
}

void Widget::key_release_event(Key_event& event)
{
	event.ignore();
	return;
}

void Widget::close_event(Close_event& event)
{
	this->delete_later();
	return;
}


void Widget::set_focus(bool focus)
{
	if(this->focus_policy() == Focus_policy::NoFocus) {
		return;
	}
	focus_ = focus;
	return;
}

void Widget::set_palette_recursively(Palette palette)
{
	this->palette_ = palette;
	this->update();
	for(Object* c : this->children()) {
		Widget* child = dynamic_cast<Widget*>(c);
		if(child) {
			child->set_palette_recursively(palette);
		}
	}
	return;
}

void Widget::set_visible(bool visible)
{
	this->visible_ = visible;
	for(Object* c : this->children()) {
		Widget* child = dynamic_cast<Widget*>(c);
		if(child) {
			child->set_visible(visible);
		}
	}
	return;
}




unsigned Widget::find_global_x() const	// previously get_global_x
{
	Widget* parent_widg = dynamic_cast<Widget*>(this->parent());
	if(!parent_widg) {
		return this->x();
	} else {
		return this->x() + parent_widg->find_global_x();
	}
}

unsigned Widget::find_global_y() const
{
	Widget* parent_widg = dynamic_cast<Widget*>(this->parent());
	if(!parent_widg) {
		return this->y();
	} else {
		return this->y() + parent_widg->find_global_y();
	}
}

Paint_engine& Widget::paint_engine() const
{
	if(paint_engine_) {
		return *paint_engine_;
	} else {
		return *System::paint_engine();
	}
}

} // namespace mcurses