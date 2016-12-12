#ifndef CTS_CORE_MATH_H__
#define CTS_CORE_MATH_H__

#include <cts-core/coreapi.h>
#include <Eigen/Dense>

namespace cts
{
	using vec2 = Eigen::Vector2d;

	namespace math
	{
		inline double distance(const vec2& lhs, const vec2 rhs)
		{
			return (lhs - rhs).norm();
		}


		template<typename T>
		T clamp(T value, T min, T max)
		{
			return std::min(max, std::max(min, value));
		}
	}
}

#endif
