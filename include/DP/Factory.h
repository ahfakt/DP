#ifndef DP_FACTORY_H
#define DP_FACTORY_H

#include "DP/CreateInfo.h"
#include <stdexcept>
#include <unordered_map>

namespace DP {

template <typename T, typename IDType, typename ... Args>
class Factory {
	static inline std::unordered_map<IDType, CreateInfo<T, Args ...>> Registry;

public:
	Factory() noexcept;

	struct TypeID
	{ IDType id; };

	struct Exception : std::runtime_error
	{ using std::runtime_error::runtime_error; };

	template <typename DT, IDType typeID>
	class Registrar {
		static const inline bool IsRegistered = [] {
			return Registry.try_emplace(typeID,
					[] (void* ptr, Args&& ... args) -> T*
					{ return ::new(ptr) DT(std::forward<Args>(args) ...); },
					sizeof(DT)
			).second;
		}();

	protected:
		static constexpr TypeID TypeId {typeID};

		__attribute__((__used__))
		Registrar() noexcept;
	};//class Registrar<DT, IDType>

	static CreateInfo<T, Args ...> const&
	GetCreateInfo(TypeID const& TypeId);

	static T*
	Create(TypeID const& TypeId, Args&& ... args);

	virtual TypeID
	getTypeId() = 0;
};//class Factory<T, IDType, Args ...>

}//namespace DP

#include "../src/Factory.hpp"

#endif //DP_FACTORY_H