#include "DP/Factory.hpp"

namespace DP {

template <typename Base, typename ID, typename ... Args>
template <typename Derived, ID id>
Factory<Base, ID, Args...>::Registrar<Derived, id>::Registrar()
{ TYPE; }

template <typename Base, typename ID, typename... Args>
std::uint32_t
Factory<Base, ID, Args...>::GetSize()
{ return Factory::Registry.size(); }

template <typename Base, typename ID, typename ... Args>
CreateInfo<Base, Args ...> const&
Factory<Base, ID, Args ...>::GetCreateInfo(ID const& id)
{
	if (auto i = Factory::Registry.find(id); i != Factory::Registry.end())
		return i->second;
	throw Exception("Unregistered ID");
}

template <typename Base, typename ID, typename... Args>
CreateInfo<Base, Args ...> const&
Factory<Base, ID, Args...>::GetCreateInfoNth(std::uint32_t i)
{
	if (i < Factory::Registry.size()) { // TODO more efficient
		auto b = Factory::Registry.begin();
		std::advance(b, i);
		return b->second;
	}
	throw Exception("Unregistered ID");
}

template <typename Base, typename ID, typename ... Args>
std::unique_ptr<Base>
Factory<Base, ID, Args ...>::Create(ID const& id, Args&& ... args)
{
	auto const& createInfo = Factory::GetCreateInfo(id);
	return createInfo.constructor(::operator new(createInfo.size), std::forward<Args>(args) ...);
}

template <typename Base, typename ID, typename... Args>
std::unique_ptr<Base>
Factory<Base, ID, Args...>::CreateNth(std::uint32_t i, Args&& ... args)
{
	auto const& createInfo = Factory::GetCreateInfoNth(i);
	return createInfo.constructor(::operator new(createInfo.size), std::forward<Args>(args) ...);
}

}//namespace DP
