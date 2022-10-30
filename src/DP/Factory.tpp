#include "DP/Factory.hpp"

namespace DP {

template <typename Base, typename Type, typename ... Args>
template <typename Derived, Type type>
Factory<Base, Type, Args...>::Registrar<Derived, type>::Registrar()
{ TYPE; }

template <typename Base, typename Type, typename... Args>
std::uint32_t
Factory<Base, Type, Args...>::GetSize()
{ return Factory::Registry.size(); }

template <typename Base, typename Type, typename ... Args>
CreateInfo<Base, Args ...> const&
Factory<Base, Type, Args ...>::GetCreateInfo(Type const& type)
{
	if (auto i = Factory::Registry.find(type); i != Factory::Registry.end())
		return i->second;
	throw Exception("Unregistered Type");
}

template <typename Base, typename Type, typename... Args>
CreateInfo<Base, Args ...> const&
Factory<Base, Type, Args...>::GetCreateInfoNth(std::uint32_t i)
{
	if (i < Factory::Registry.size()) { // TODO more efficient
		auto b = Factory::Registry.begin();
		std::advance(b, i);
		return b->second;
	}
	throw Exception("Unregistered Type");
}

template <typename Base, typename Type, typename ... Args>
std::unique_ptr<Base>
Factory<Base, Type, Args ...>::Create(Type const& type, Args&& ... args)
{
	auto const& createInfo = Factory::GetCreateInfo(type);
	return std::unique_ptr<Base>{createInfo.constructor(::operator new(createInfo.size), std::forward<Args>(args) ...)};
}

template <typename Base, typename Type, typename... Args>
std::unique_ptr<Base>
Factory<Base, Type, Args...>::CreateNth(std::uint32_t i, Args&& ... args)
{
	auto const& createInfo = Factory::GetCreateInfoNth(i);
	return std::unique_ptr<Base>{createInfo.constructor(::operator new(createInfo.size), std::forward<Args>(args) ...)};
}

}//namespace DP
