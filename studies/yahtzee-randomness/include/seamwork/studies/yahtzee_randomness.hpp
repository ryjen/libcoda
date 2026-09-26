#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>

namespace seamwork::studies::yahtzee {

inline constexpr std::size_t dice_per_hand = 5;
inline constexpr unsigned sides_per_die = 6;

enum class face : std::uint8_t {
    one = 1,
    two,
    three,
    four,
    five,
    six,
};

[[nodiscard]] constexpr auto value(face side) noexcept -> unsigned
{
    return static_cast<unsigned>(std::to_underlying(side));
}

using face_values = std::array<face, dice_per_hand>;
using hold_mask = std::array<bool, dice_per_hand>;

class hand
{
public:
    constexpr explicit hand(face_values values, hold_mask held = {})
        : values_(values), held_(held)
    {
    }

    [[nodiscard]] constexpr auto values() const noexcept -> const face_values&
    {
        return values_;
    }

    [[nodiscard]] constexpr auto held() const noexcept -> const hold_mask&
    {
        return held_;
    }

    [[nodiscard]] constexpr auto operator[](std::size_t index) const -> face
    {
        return values_.at(index);
    }

    [[nodiscard]] constexpr auto is_held(std::size_t index) const -> bool
    {
        return held_.at(index);
    }

    [[nodiscard]] auto with_hold(std::size_t index, bool should_hold = true) const -> hand
    {
        if (index >= dice_per_hand) {
            throw std::out_of_range{"Yahtzee die index is outside the hand"};
        }

        auto next_held = held_;
        next_held[index] = should_hold;
        return hand{values_, next_held};
    }

private:
    face_values values_;
    hold_mask held_;
};

template <class Source>
concept face_source = requires(Source& source) {
    { std::invoke(source) } -> std::same_as<face>;
};

template <face_source Source>
[[nodiscard]] auto initial_roll(Source& source) -> hand
{
    face_values values{};
    for (auto& die : values) {
        die = std::invoke(source);
    }
    return hand{values};
}

template <face_source Source>
[[nodiscard]] auto reroll(const hand& current, Source& source) -> hand
{
    auto values = current.values();

    for (std::size_t index = 0; index < values.size(); ++index) {
        if (!current.is_held(index)) {
            values[index] = std::invoke(source);
        }
    }

    return hand{values, current.held()};
}

template <std::uniform_random_bit_generator Engine>
class uniform_face_source
{
public:
    explicit uniform_face_source(Engine engine)
        : engine_(std::move(engine))
    {
    }

    [[nodiscard]] auto operator()() -> face
    {
        std::uniform_int_distribution<unsigned> distribution{1, sides_per_die};
        return static_cast<face>(distribution(engine_));
    }

private:
    Engine engine_;
};

namespace alternatives {

class virtual_face_source
{
public:
    virtual ~virtual_face_source() = default;
    [[nodiscard]] virtual auto next() -> face = 0;
};

[[nodiscard]] inline auto initial_roll(virtual_face_source& source) -> hand
{
    face_values values{};
    for (auto& die : values) {
        die = source.next();
    }
    return hand{values};
}

[[nodiscard]] inline auto reroll(const hand& current, virtual_face_source& source) -> hand
{
    auto values = current.values();

    for (std::size_t index = 0; index < values.size(); ++index) {
        if (!current.is_held(index)) {
            values[index] = source.next();
        }
    }

    return hand{values, current.held()};
}

using erased_face_source = std::function<face()>;

[[nodiscard]] inline auto initial_roll(erased_face_source& source) -> hand
{
    face_values values{};
    for (auto& die : values) {
        die = source();
    }
    return hand{values};
}

[[nodiscard]] inline auto reroll(const hand& current, erased_face_source& source) -> hand
{
    auto values = current.values();

    for (std::size_t index = 0; index < values.size(); ++index) {
        if (!current.is_held(index)) {
            values[index] = source();
        }
    }

    return hand{values, current.held()};
}

template <std::uniform_random_bit_generator Engine>
[[nodiscard]] auto initial_roll_urbg(Engine& engine) -> hand
{
    std::uniform_int_distribution<unsigned> distribution{1, sides_per_die};
    face_values values{};

    for (auto& die : values) {
        die = static_cast<face>(distribution(engine));
    }

    return hand{values};
}

template <std::uniform_random_bit_generator Engine>
[[nodiscard]] auto reroll_urbg(const hand& current, Engine& engine) -> hand
{
    std::uniform_int_distribution<unsigned> distribution{1, sides_per_die};
    auto values = current.values();

    for (std::size_t index = 0; index < values.size(); ++index) {
        if (!current.is_held(index)) {
            values[index] = static_cast<face>(distribution(engine));
        }
    }

    return hand{values, current.held()};
}

} // namespace alternatives

} // namespace seamwork::studies::yahtzee
