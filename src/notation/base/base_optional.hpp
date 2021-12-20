#pragma once

#ifdef __CXX17
#include <optional>

namespace hautbois {

template<class T>
class BaseOptional : public std::optional<T> {
public:
    constexpr BaseOptional() noexcept : std::optional<T>::optional( {} )
    {
    }
    void emplaceValue(T val) {
        std::optional<T>::emplace(val);
    }
    T& getValue() {
        return std::optional<T>::value();
    }
    bool hasValue() noexcept {
        return std::optional<T>::has_value();
    }
    void resetValue() noexcept {
        std::optional<T>::reset();
    }
};

} // namespace hautbois
#else
#include <boost/optional.hpp>

namespace hautbois {

template<class T>
class BaseOptional : public boost::optional<T> {
public:
    constexpr BaseOptional() BOOST_NOEXCEPT : boost::optional<T>(boost::none)
    {
    }
    void emplaceValue(T val) {
        boost::optional<T>::emplace(val);
    }
    T& getValue() {
        return boost::optional<T>::get();
    }
    bool hasValue() BOOST_NOEXCEPT {
        return boost::optional<T>::is_initialized();
    }
    void resetValue() BOOST_NOEXCEPT {
        boost::optional<T>::reset();
    }
};

} // namespace hautbois

#endif

