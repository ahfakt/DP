#pragma once

#include "CreateInfo.hpp"
#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace DP {

template <typename Base, typename Type, typename ... Args>
class Factory {
	static inline std::unordered_map<Type, CreateInfo<Base, Args ...>> Registry;

public:
	struct Exception : std::runtime_error
	{ using std::runtime_error::runtime_error; };

	template <typename Derived, Type type>
	struct Registrar {
		static inline const Type TYPE = []() {
			if (auto [pair, inserted] = Registry.try_emplace(type,
					[] (void* ptr, Args&& ... args) -> Base*
					{ return ::new(ptr) Derived(std::forward<Args>(args) ...); },
					sizeof(Derived)); inserted)
				return pair->first;
			throw Exception{"Registered Type"};
		}();
	};//struct DP::Factory<Base, Type, Args ...>::Registrar<Derived, type>

	static std::uint32_t
	GetSize();

	static CreateInfo<Base, Args ...> const&
	GetCreateInfo(Type const& type);

	static CreateInfo<Base, Args ...> const&
	GetCreateInfoNth(std::uint32_t i);

	static std::unique_ptr<Base>
	Create(Type const& type, Args&& ... args);

	static std::unique_ptr<Base>
	CreateNth(std::uint32_t i, Args&& ... args);
};//class DP::Factory<Base, Type, Args ...>

}//namespace DP

#include "../../src/DP/Factory.tpp"
