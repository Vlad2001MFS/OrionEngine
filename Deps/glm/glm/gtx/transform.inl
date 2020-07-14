/// @ref gtx_transform
/// @file glm/gtx/transform.inl

namespace glm
{
	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tmat4x4<T, P> translate(tvec3<T, P> const & v)
	{
		return translate(tmat4x4<T, P>(static_cast<T>(1)), v);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tmat4x4<T, P> rotate(T angle, tvec3<T, P> const & v)
	{
		return rotate(tmat4x4<T, P>(static_cast<T>(1)), angle, v);
	}

    template<typename T>
    GLM_FUNC_QUALIFIER tmat4x4<T> rotate(const tvec3<T> &angles)
    {
        return rotate(angles.x, tvec3<T>(1, 0, 0)) * rotate(angles.y, tvec3<T>(0, 1, 0)) * rotate(angles.z, tvec3<T>(0, 0, 1));
    }

    template<typename T>
    GLM_FUNC_QUALIFIER tmat4x4<T> rotateX(T angle)
    {
        return rotate(angle, tvec3<T>(1, 0, 0));
    }

    template<typename T>
    GLM_FUNC_QUALIFIER tmat4x4<T> rotateY(T angle)
    {
        return rotate(angle, tvec3<T>(0, 1, 0));
    }

    template<typename T>
    GLM_FUNC_QUALIFIER tmat4x4<T> rotateZ(T angle)
    {
        return rotate(angle, tvec3<T>(0, 0, 1));
    }

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tmat4x4<T, P> scale(tvec3<T, P> const & v)
	{
		return scale(tmat4x4<T, P>(static_cast<T>(1)), v);
	}

}//namespace glm
