#include "DP/Factory.hpp"

namespace DP {

template <typename Base, typename ID, typename ... Args>
template <typename Derived, ID id>
Factory<Base, ID, Args...>::Registrar<Derived, id>::Registrar()
{ TYPE; }

template <typename Base, typename ID, typename ... Args>
CreateInfo<Base, Args ...> const&
Factory<Base, ID, Args ...>::GetCreateInfo(ID const& id)
{
	if (auto i = Factory::Registry.find(id); i != Factory::Registry.end())
		return i->second;
	throw Exception("Unregistered ID");
}

template <typename Base, typename ID, typename ... Args>
Base*
Factory<Base, ID, Args ...>::Create(ID const& id, Args&& ... args)
{
	auto const& createInfo = Factory::GetCreateInfo(id);
	return createInfo.constructor(::operator new(createInfo.size), std::forward<Args>(args) ...);
}

}//namespace DP
