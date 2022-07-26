#include "DP/Factory.h"

namespace DP {

template <typename T, typename IdType, typename ... Args>
CreateInfo<T, Args ...> const&
Factory<T, IdType, Args ...>::GetCreateInfo(IdType const& typeId)
{
	if (auto i = Factory::Registry.find(typeId); i != Factory::Registry.end())
		return i->second;
	throw Exception("Unregistered Id");
}

template <typename T, typename IdType, typename ... Args>
T*
Factory<T, IdType, Args ...>::Create(IdType const& typeId, Args&& ... args)
{
	CreateInfo<T, Args ...> const& createInfo = Factory::GetCreateInfo(typeId);
	return createInfo.create(::operator new(createInfo.size), std::forward<Args>(args) ...);
}

template <typename T, typename IdType, typename... Args>
template <typename DT, IdType id>
Factory<T, IdType, Args...>::Registrar<DT, id>::Registrar()
{ TYPE; }

}//namespace DP
