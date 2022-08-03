#ifndef DP_FACTORY_HPP
#define DP_FACTORY_HPP

#include "CreateInfo.hpp"
#include <stdexcept>
#include <unordered_map>

namespace DP {

template <typename Base, typename ID, typename ... Args>
class Factory {
	static inline std::unordered_map<ID, CreateInfo<Base, Args ...>> Registry;

public:
	struct Exception : std::runtime_error
	{ using std::runtime_error::runtime_error; };

	template <typename Derived, ID id>
	struct Registrar {
		static inline const ID TYPE = []() {
			if (auto [pair, inserted] = Factory::Registry.try_emplace(id,
					[] (void* ptr, Args&& ... args) -> Base* { return ::new(ptr) Derived(std::forward<Args>(args) ...); },
					sizeof(Derived)); inserted)
				return pair->first;
			throw Exception("Registered ID");
		}();
	protected:
		__attribute__((__used__))
		Registrar();
	};//struct Registrar<Derived, ID>

	static CreateInfo<Base, Args ...> const&
	GetCreateInfo(ID const& id);

	static Base*
	Create(ID const& id, Args&& ... args);
};//class DP::Factory<Base, ID, Args ...>

}//namespace DP

#include "../../src/Factory.tpp"

#endif //DP_FACTORY_HPP