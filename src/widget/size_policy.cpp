#include <caterm/widget/size_policy.hpp>

#include <utility>

namespace ox {

void Size_policy::hint(int value)
{
    data_.hint = value;
    policy_updated.emit();
}

auto Size_policy::hint() const -> int { return data_.hint; }

void Size_policy::min(int value)
{
    data_.min = value;
    if (data_.max < data_.min)
        data_.max = data_.min;
    policy_updated.emit();
}

auto Size_policy::min() const -> int { return data_.min; }

void Size_policy::max(int value)
{
    data_.max = value;
    if (data_.min > data_.max)
        data_.min = data_.max;
    policy_updated.emit();
}

auto Size_policy::max() const -> int { return data_.max; }

void Size_policy::stretch(double value)
{
    if (value <= 0.)
        return;
    data_.stretch = value;
    policy_updated.emit();
}

auto Size_policy::stretch() const -> double { return data_.stretch; }

void Size_policy::can_ignore_min(bool enable) { data_.can_ignore_min = enable; }

auto Size_policy::can_ignore_min() const -> bool
{
    return data_.can_ignore_min;
}

void Size_policy::fixed(int hint)
{
    data_.hint    = hint;
    data_.min     = hint;
    data_.max     = hint;
    data_.stretch = 1.;
    policy_updated.emit();
}

void Size_policy::minimum(int hint)
{
    data_.hint = hint;
    this->min(hint);
}

void Size_policy::maximum(int hint)
{
    data_.hint = hint;
    this->max(hint);
}

void Size_policy::preferred(int hint)
{
    data_.hint = hint;
    if (hint < data_.min)
        data_.min = hint;
    if (hint > data_.max)
        data_.max = hint;
    policy_updated.emit();
}

void Size_policy::expanding(int hint)
{
    data_.stretch = 100'000.;
    data_.hint    = hint;
    if (hint < data_.min)
        data_.min = hint;
    if (hint > data_.max)
        data_.max = hint;
    policy_updated.emit();
}

void Size_policy::minimum_expanding(int hint)
{
    data_.stretch = 100'000.;
    data_.hint    = hint;
    this->min(hint);
}

void Size_policy::ignored()
{
    data_.hint = 0;
    data_.min  = 0;
    data_.max  = maximum_max;
    policy_updated.emit();
}

Size_policy::Size_policy(Size_policy const& x) : data_{x.data_} {}

Size_policy::Size_policy(Size_policy&& x) : data_{std::move(x.data_)} {}

auto Size_policy::operator=(Size_policy const& x) -> Size_policy&
{
    data_ = x.data_;
    policy_updated.emit();
    return *this;
}

auto Size_policy::operator=(Size_policy&& x) -> Size_policy&
{
    data_ = std::move(x.data_);
    policy_updated.emit();
    return *this;
}

}  // namespace ox
