#ifndef DP_CREATE_INFO_H
#define DP_CREATE_INFO_H

#include <cstdint>

namespace DP {

/**
 * @brief	Type alias for the placement new construction function
 * @typedef	Func CreateInfo.h "DP/CreateInfo.h"
 */
template <typename T, typename ... Args>
using CreateFunc = T* (*)(void* ptr, Args&& ...);

/**
 * @brief	Helper struct to be used to create polymorphic objects
 * @struct	Info CreateInfo.h "DP/CreateInfo.h"
 */
template <typename T, typename ... Args>
struct CreateInfo {
	/// Create function to be used to create the T-based object
	CreateFunc<T, Args ...> create;
	/// The size of the T-based object to be created
	std::size_t size;
};//struct CreateInfo<T, Args ...>

}//namespace DP

#endif //DP_CREATE_INFO_H