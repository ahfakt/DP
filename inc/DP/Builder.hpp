#ifndef DP_BUILDER_HPP
#define DP_BUILDER_HPP

#include <cstdint>

namespace DP {

template <std::size_t t, typename T, typename ... U>
struct TypeImpl
{ using type = typename TypeImpl<t - 1, U ...>::type; };

template <typename T, typename ... U>
struct TypeImpl<0, T, U ...>
{ using type = T; };

template <std::size_t t, typename ... T>
using Type = typename TypeImpl<t, T ...>::type;


template <std::size_t v, auto t, auto ... u>
struct ValueImpl
{ static inline constexpr Type<v - 1, decltype(u) ...> value = ValueImpl<v - 1, u ...>::value; };

template <auto t, auto ... u>
struct ValueImpl<0, t, u ...>
{ static inline constexpr decltype(t) value = t; };

template <std::size_t v, auto ... t>
inline constexpr Type<v, decltype(t) ...> Value = ValueImpl<v, t ...>::value;


template <typename T>
struct MemberTypeImpl
{ using type = void; };

template <typename T, typename M>
struct MemberTypeImpl<M T::*>
{ using type = M; };

template <std::size_t m, auto ... M>
using MemberType = typename MemberTypeImpl<Type<m, decltype(M) ...>>::type;


template <typename P, auto ... M>
struct MemberAccess {
	template <std::size_t m>
	static MemberType<m, M ...>&
	Get(void* p) noexcept
	{ return reinterpret_cast<P*>(p)->*Value<m, M ...>; }

	template <std::size_t m>
	static MemberType<m, M ...> const&
	Get(void const* p) noexcept
	{ return reinterpret_cast<P const*>(p)->*Value<m, M ...>; }

	template <std::size_t m>
	static MemberType<m, M ...>&
	Get(P& p) noexcept
	{ return p.*Value<m, M ...>; }

	template <std::size_t m>
	static MemberType<m, M ...> const&
	Get(P const& p) noexcept
	{ return p.*Value<m, M ...>; }
};//struct DP::MemberAccess<P, M ...>


template <typename T>
class Builder {
protected:
	virtual T
	build() const = 0;

public:
	T*
	operator()(void* p) const
	{ return ::new(p) T{build()}; }

	T
	operator()() const
	{ return build(); }
};//class DP::Builder<T>

}//namespace DP

#endif //DP_BUILDER_HPP