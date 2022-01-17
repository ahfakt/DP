#include "DP/Factory.h"

namespace DP {

template <typename T, typename IDType, typename ... Args>
Factory<T, IDType, Args ...>::Factory() noexcept
{ Factory::Registry; }

template <typename T, typename IDType, typename ... Args>
CreateInfo<T, Args ...> const&
Factory<T, IDType, Args ...>::GetCreateInfo(TypeID const& TypeId)
{
	if (auto i = Factory::Registry.find(TypeId.id); i != Factory::Registry.end())
		return i->second;
	throw Exception("Unregistered Class ID");
}

template <typename T, typename IDType, typename ... Args>
T*
Factory<T, IDType, Args ...>::Create(TypeID const& TypeId, Args&& ... args)
{
	CreateInfo<T, Args ...> const& createInfo = Factory::GetCreateInfo(TypeId);
	return createInfo.create(::operator new(createInfo.size), std::forward<Args>(args) ...);
}

template <typename T, typename IDType, typename ... Args>
template <typename DT, IDType typeID>
Factory<T, IDType, Args ...>::Registrar<DT, typeID>::Registrar()
{ Registrar::IsRegistered; }

}//namespace DP
