#pragma once

#include <memory>

#ifdef JLHE_DEBUG
	#define JLHE_ENABLE_ASSERTS
#endif

#ifdef JLHE_ENABLE_ASSERTS
	#define JLHE_ASSERT(x, ...) { if(!(x)) {JLHE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JLHE_CORE_ASSERT(x, ...) { if(!(x)) {JLHE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JLHE_ASSERT(x, ...)
	#define JLHE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define JLHE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace JLHE {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}