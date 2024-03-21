#pragma once

#include <string>
#include <string.h>
#include <type_traits>

/*
* Written by shzy.
* Happy for using.
*/

#define _FLASHENUM_BEGIN_ namespace flash_enum{
#define _FLASHENUM_END_ }

_FLASHENUM_BEGIN_

/*
#if defined _WIN32
#  if (_MSC_VER >= 1900)
#    define _CONST_EXPR_ constexpr
#  else
#    define _CONST_EXPR_  
#  endif
#else // GCC / Clang
#  define _CONST_EXPR_ constexpr
#endif
*/

template<typename E>
using EnableOnlyEnum = typename std::enable_if<std::is_enum<E>::value>::type;

/* don't call these */
template<typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
inline std::string __truncate_to_enum_val__(char const *str);
template<typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
inline std::string __truncate_to_enum_type__(char const *str);
template<typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
inline std::string __truncate_to_type_with_val__(char const *str);

/* convert this to std::string, */
/* or use a std::string variable to recv it. */
struct flect_string
{
	flect_string(std::string &&val) : val_(val) {}
	~flect_string() = default;

	operator std::string&&()
	{
		return std::move(val_);
	}

private:
	std::string val_;
};

/* return enum name as string */
template<typename T, T ev>
inline flect_string reflect_enum()
{

#if defined(_WIN32) && defined(_MSC_VER)
	return __truncate_to_enum_val__<T>(__FUNCSIG__);
#else
	return __truncate_to_enum_val__<T>(__PRETTY_FUNCTION__);
#endif

}

/* return enum type as string */
template<typename T, typename NON_USE = void*>
inline flect_string reflect_type(T enum_val)
{
	static_cast<void>(enum_val);
#if defined(_WIN32) && defined(_MSC_VER)
	return __truncate_to_enum_type__<T>(__FUNCSIG__);
#else
	return __truncate_to_enum_type__<T>(__PRETTY_FUNCTION__);
#endif

}

/* return enum type as string */
template<typename T, T ev>
inline flect_string reflect_type()
{

#if defined(_WIN32) && defined(_MSC_VER)
	return __truncate_to_enum_type__<T>(__FUNCSIG__);
#else
	return __truncate_to_enum_type__<T>(__PRETTY_FUNCTION__);
#endif

}

/* return enum type and value as string */
/* like "EnumType::ENUM_VAL" */
template<typename T, T ev>
inline flect_string reflect_type_with_val()
{

#if defined(_WIN32) && defined(_MSC_VER)
	return __truncate_to_type_with_val__<T>(__FUNCSIG__);
#else
	return __truncate_to_type_with_val__<T>(__PRETTY_FUNCTION__);
#endif

}


template<typename T, typename std::enable_if<std::is_enum<T>::value>::type*>
inline std::string __truncate_to_enum_val__(char const *str)
{
	//find '<' and '>'
	int len = strlen(str);
	int type_begin{0}; // '<' 
	int type_end{0}; // '>'
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == '>' || str[i] == ']')
		{
			type_end = i;
			continue;
		}
		if (str[i] == '<' || str[i] == '[')
		{
			type_begin = i;
			break;
		}
	}

	std::string func_name(str + type_begin, type_end - type_begin + 1);

	//find ',' or ';'
	int sepa_index{0};
	for (int i = func_name.size() - 1; i >= 0; i--)
	{
		if (func_name[i] == ',' || func_name[i] == ';')
		{
			sepa_index = i;
			break;
		}
	}

	std::string ev_name(func_name, sepa_index); //left ',' in ev_name, for convenience to reverse find

	int ev_begin_index{0}, ev_end_index{0};
	for (int i = ev_name.size() - 1; i >= 0; i--)
	{
		if (((ev_name[i] >= '0' && ev_name[i] <= '9') ||
			(ev_name[i] >= 'A' && ev_name[i] <= 'Z') ||
			(ev_name[i] >= 'a' && ev_name[i] <= 'z') ||
			(ev_name[i] == '_')))
		{
			ev_end_index = i;
			break;
		}
	}
	for (int i = ev_end_index; i >= 0; i--)
	{
		if (!((ev_name[i] >= '0' && ev_name[i] <= '9') ||
			(ev_name[i] >= 'A' && ev_name[i] <= 'Z') ||
			(ev_name[i] >= 'a' && ev_name[i] <= 'z') ||
			(ev_name[i] == '_')))
		{
			ev_begin_index = i;
			break;
		}
	}

	ev_name.erase(ev_end_index + 1);
	ev_name.erase(0, ev_begin_index + 1);

	return ev_name;
}


template<typename T, typename std::enable_if<std::is_enum<T>::value>::type*>
inline std::string __truncate_to_enum_type__(char const *str)
{
	//find '<' and '>'
	int len = strlen(str);
	int type_begin{0}; // '<' 
	int type_end{0}; // '>'
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == '>' || str[i] == ']')
		{
			type_end = i;
			continue;
		}
		if (str[i] == '<' || str[i] == '[')
		{
			type_begin = i;
			break;
		}
	}

	std::string func_name(str + type_begin, type_end - type_begin + 1);

	//find ',' or ';'
	int sepa_index{0};
	for (int i = func_name.size() - 1; i >= 0; i--)
	{
		if (func_name[i] == ',' || func_name[i] == ';')
		{
			sepa_index = i;
			break;
		}
	}

	std::string et_name(func_name, 0, sepa_index);

	int et_begin_index{0}, et_end_index{0};
	for (int i = et_name.size() - 1; i >= 0; i--)
	{
		if (((et_name[i] >= '0' && et_name[i] <= '9') ||
			(et_name[i] >= 'A' && et_name[i] <= 'Z') ||
			(et_name[i] >= 'a' && et_name[i] <= 'z') ||
			(et_name[i] == '_')))
		{
			et_end_index = i;
			break;
		}
	}
	for (int i = et_end_index; i >= 0; i--)
	{
		if (!((et_name[i] >= '0' && et_name[i] <= '9') ||
			(et_name[i] >= 'A' && et_name[i] <= 'Z') ||
			(et_name[i] >= 'a' && et_name[i] <= 'z') ||
			(et_name[i] == '_')))
		{
			et_begin_index = i;
			break;
		}
	}
	et_name.erase(et_end_index + 1);
	et_name.erase(0, et_begin_index + 1);

	return et_name;
}

template<typename T, typename std::enable_if<std::is_enum<T>::value>::type*>
inline std::string __truncate_to_type_with_val__(char const *str)
{
	//find '<' and '>'
	int len = strlen(str);
	int type_begin{0}; // '<' 
	int type_end{0}; // '>'
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == '>' || str[i] == ']')
		{
			type_end = i;
			continue;
		}
		if (str[i] == '<' || str[i] == '[')
		{
			type_begin = i;
			break;
		}
	}

	std::string func_name(str + type_begin, type_end - type_begin + 1);

	//find ',' or ';'
	int sepa_index{0};
	for (int i = func_name.size() - 1; i >= 0; i--)
	{
		if (func_name[i] == ',' || func_name[i] == ';')
		{
			sepa_index = i;
			break;
		}
	}

	std::string et_name(func_name, 0, sepa_index);
	std::string ev_name(func_name, sepa_index); //left ',' in ev_name, for convenience to reverse find

	int et_begin_index{0}, et_end_index{0};
	for (int i = et_name.size() - 1; i >= 0; i--)
	{
		if (((et_name[i] >= '0' && et_name[i] <= '9') ||
			(et_name[i] >= 'A' && et_name[i] <= 'Z') ||
			(et_name[i] >= 'a' && et_name[i] <= 'z') ||
			(et_name[i] == '_')))
		{
			et_end_index = i;
			break;
		}
	}
	for (int i = et_end_index; i >= 0; i--)
	{
		if (!((et_name[i] >= '0' && et_name[i] <= '9') ||
			(et_name[i] >= 'A' && et_name[i] <= 'Z') ||
			(et_name[i] >= 'a' && et_name[i] <= 'z') ||
			(et_name[i] == '_')))
		{
			et_begin_index = i;
			break;
		}
	}
	et_name.erase(et_end_index + 1);
	et_name.erase(0, et_begin_index + 1);

	int ev_begin_index{0}, ev_end_index{0};
	for (int i = ev_name.size() - 1; i >= 0; i--)
	{
		if (((ev_name[i] >= '0' && ev_name[i] <= '9') ||
			(ev_name[i] >= 'A' && ev_name[i] <= 'Z') ||
			(ev_name[i] >= 'a' && ev_name[i] <= 'z') ||
			(ev_name[i] == '_')))
		{
			ev_end_index = i;
			break;
		}
	}
	for (int i = ev_end_index; i >= 0; i--)
	{
		if (!((ev_name[i] >= '0' && ev_name[i] <= '9') ||
			(ev_name[i] >= 'A' && ev_name[i] <= 'Z') ||
			(ev_name[i] >= 'a' && ev_name[i] <= 'z') ||
			(ev_name[i] == '_')))
		{
			ev_begin_index = i;
			break;
		}
	}

	ev_name.erase(ev_end_index + 1);
	ev_name.erase(0, ev_begin_index + 1);

	return (et_name + "::" + ev_name);
}





_FLASHENUM_END_


