#ifndef DP_FACTORY_H
#define DP_FACTORY_H

#include "CreateInfo.h"
#include <stdexcept>
#include <unordered_map>

namespace DP {

template <typename T, typename IdType, typename ... Args>
class Factory {
	static inline std::unordered_map<IdType, CreateInfo<T, Args ...>> Registry;

public:
	struct Exception : std::runtime_error
	{ using std::runtime_error::runtime_error; };

	template <typename DT, IdType id>
	struct Registrar {
		static inline const IdType TYPE = []() {
			if (auto [pair, inserted] = Factory::Registry.try_emplace(id,
				[] (void* ptr, Args&& ... args) -> T* { return ::new(ptr) DT(std::forward<Args>(args) ...); }, sizeof(DT)); inserted)
				return pair->first;
			throw Exception("Registered Id");
		}();
	protected:
		__attribute__((__used__))
		Registrar();
	};//struct Registrar<DT, IdType>

	static CreateInfo<T, Args ...> const&
	GetCreateInfo(IdType const& typeId);

	static T*
	Create(IdType const& typeId, Args&& ... args);
};
//class Factory<T, IdType, Args ...>

}//namespace DP

#include "../../src/Factory.hpp"

#endif //DP_FACTORY_H