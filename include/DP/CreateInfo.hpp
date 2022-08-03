#ifndef DP_CREATE_INFO_HPP
#define DP_CREATE_INFO_HPP

#include <cstdint>

namespace DP {

/**
 * @brief	Type alias for the placement new construction function
 * @typedef	Constructor CreateInfo.hpp "DP/CreateInfo.hpp"
 */
template <typename T, typename ... Args>
using Constructor = T* (*)(void*, Args&& ...);

/**
 * @brief	Helper struct to be used to create polymorphic objects
 * @struct	CreateInfo CreateInfo.hpp "DP/CreateInfo.hpp"
 */
template <typename T, typename ... Args>
struct CreateInfo {
	/// Create function to be used to create the T-based object
	Constructor<T, Args ...> constructor;
	/// The size of the T-based object to be created
	std::size_t size;
};//struct DP::CreateInfo<T, Args ...>

}//namespace DP

#endif //DP_CREATE_INFO_HPP