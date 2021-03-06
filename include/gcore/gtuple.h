#ifndef _CORE_TUPLE_H_
#define _CORE_TUPLE_H_

#include "gutility.h"

namespace gsystem { // gsystem

// 对组
template<typename T1, typename T2>
class GPair
{
public:
	typedef T1 FirstType;
	typedef T2 SecondType;

public:
	GPair();
	GPair(const T1 &first, const T2 &second);
	GPair(const T1 &first, T2 &&second);
	GPair(T1 &&first, const T2 &second);
	GPair(T1 &&first, T2 &&second);
	GPair(const GPair<T1, T2> &pair);
	GPair(GPair<T1, T2> &&pair);

	const volatile T1& First() const volatile;
	volatile T1 &First() volatile;
	const T1 &First() const;
	T1 &First();
	const volatile T2& First() const volatile;
	volatile T2 &First() volatile;
	const T2 &Second() const;
	T2 &Second();

private:
	T1 m_tFirst;
	T2 m_tSecond;
};

// 根据两个数值，构造一个GPair  
template<typename T1, typename T2> GPair<T1, T2> GMakePair(const T1 &first, const T2 &second);
template<typename T1, typename T2> GPair<T1, T2> GMakePair(const T1 &first, T2 &&second);
template<typename T1, typename T2> GPair<T1, T2> GMakePair(T1 &&first, const T2 &second);
template<typename T1, typename T2> GPair<T1, T2> GMakePair(T1 &&first, T2 &&second);

// 元组
template<typename ...TS> class GTuple;
template<> class GTuple<> {};
typedef GTuple<> GNullTuple;

template<typename T, typename ...TS>
class GTuple<T, TS...> : public GTuple<TS...>
{
public:
	typedef T ValueType;
	typedef GTuple<TS...> BaseType;
	typedef GTuple<T, TS...> ThisType;

	GTuple() {}
	GTuple(const T &v, const TS&... tails) :BaseType(tails...), value_(v) {}
	GTuple(T &&v, TS&&... tails) :BaseType(GForward<TS>(tails)...), value_(GForward<T>(v)) {}
	GTuple(const ThisType &tuple)
		: BaseType(static_cast<const BaseType &>(tuple)), value_(tuple.value_)
	{

	}
	GTuple(ThisType &&tuple)
		: BaseType(static_cast<BaseType &&>(tuple)), value_(GMove(tuple.value_))
	{

	}

	const T &Head() const { return value_; }
	T &Head() { return value_; }
	ThisType &operator=(const ThisType &tuple)
	{
		value_ = tuple.value_;
		BaseType::operator=(static_cast<const BaseType &>(tuple));
		return *this;
	}
	ThisType &operator=(ThisType &&tuple)
	{
		value_ = GMove(tuple.value_);
		BaseType::operator=(static_cast<BaseType &&>(tuple));
		return *this;
	}

	template<typename ValueT>
	ValueT &GetAt(gsize pos)
	{
		if (pos == 0)
		{
			if (!GIsSame<ValueT, T>::value)
			{
				throw ("error type.");
			}
			return (ValueT &)value_;
		}
		return static_cast<BaseType &>(*this).GetAt<ValueT>(--pos);
	}

	template<typename ValueT>
	const ValueT &GetAt(gsize pos) const
	{
		if (pos == 0)
		{
			if (!GIsSame<ValueT, T>::value)
			{
				throw ("error type.");
			}
			return (const ValueT &)value_;
		}
		return static_cast<BaseType &>(*this).GetAt<ValueT>(--pos);
	}

	template<typename ValueT>
	gvoid SetAt(gsize pos, const ValueT &value)
	{
		if (pos == 0)
		{
			if (!GIsSame<ValueT, T>::value)
			{
				throw ("error type.");
			}
			value = static_cast<const T &>(value);
			return;
		}
		return static_cast<BaseType &>(*this).SetAt<ValueT>(--pos, value);
	}

	template<typename ValueT>
	gvoid SetAt(gsize pos, ValueT &&value)
	{
		if (pos == 0)
		{
			if (!GIsSame<ValueT, T>::value)
			{
				throw ("error type.");
			}
			value_ = (T &&)value;
			return;
		}
		return static_cast<BaseType &>(*this).SetAt<ValueT>(--pos, GForward<ValueT>(value));
	}

protected:
	T value_;
};

template<typename T>
class GTuple<T> : public GNullTuple
{
public:
	typedef T ValueType;
	typedef GNullTuple BaseType;
	typedef GTuple<T> ThisType;

	GTuple() {}
	GTuple(const T &v) :value_(v) {}
	GTuple(T &&v) :value_(GForward<T>(v)) {}
	GTuple(const ThisType &tuple) :value_(tuple.value_) {}
	GTuple(ThisType &&tuple) :value_(GMove(tuple.value_)) {}

	const T &Head() const { return this->value_; }
	T &Head() { return this->value_; }
	ThisType &operator=(const ThisType &tuple)
	{
		value_ = tuple.value_;
		return *this;
	}
	ThisType &operator=(ThisType &&tuple)
	{
		value_ = GMove(tuple.value_);
		return *this;
	}

	template<typename ValueT>
	ValueT &GetAt(gsize pos)
	{
		if (pos > 0)
		{
			throw "out of index.";
		}
		if (!GIsSame<ValueT, T>::value)
		{
			throw ("error type.");
		}
		return (ValueT &)value_;
	}

	template<typename ValueT>
	const ValueT &GetAt(gsize pos) const
	{
		if (pos > 0)
		{
			throw "out of index.";
		}
		if (!GIsSame<ValueT, T>::value)
		{
			throw ("error type.");
		}
		return (const ValueT &)value_;
	}

	template<typename ValueT>
	gvoid SetAt(gsize pos, const ValueT &value)
	{
		if (pos > 0)
		{
			throw "out of index.";
		}
		value_ = static_cast<const T &>(value);
	}

	template<typename ValueT>
	gvoid SetAt(gsize pos, ValueT &&value)
	{
		if (pos > 0)
		{
			throw "out of index.";
		}
		value_ = (T &&)value;
	}

protected:
	T value_;
};

template<typename... TS> GTuple<TS...> GMakeTuple(const TS&... args);
template<typename... TS> GTuple<TS...> GMakeTuple(TS&&... args);

template<>
GINLINE GTuple<> GMakeTuple()
{
	return GNullTuple();
}

template<typename T, typename...TS>
GINLINE GTuple<T, TS...> GMakeTuple(const T &value, const TS&... tails)
{
	return GTuple<T, TS...>(value, tails...);
}

template<typename T>
GINLINE GTuple<T> GMakeTuple(const T &value)
{
	return GTuple<T>(value);
}

template<typename T, typename...TS>
GINLINE GTuple<T, TS...> GMakeTuple(T &&value, TS&&... tails)
{
	return GTuple<T, TS...>(GForward<T>(value), GForward<TS>(tails)...);
}

template<typename T>
GINLINE GTuple<T> GMakeTuple(T &&value)
{
	return GTuple<T>(GForward<T>(value));
}

template<gsize N, typename... TS> struct GTupleAt;

template<gsize N, typename T, typename... TS>
struct GTupleAt< N, GTuple<T, TS...> >
{
	typedef typename GTupleAt<N - 1, GTuple<TS...>>::ValueType ValueType;
	typedef typename GTupleAt<N - 1, GTuple<TS...>>::TupleType TupleType;
};

template<typename T, typename... TS>
struct GTupleAt< 0, GTuple<T, TS...> >
{
	typedef T ValueType;
	typedef GTuple<T, TS...> TupleType;
};

template<>
struct GTupleAt<0, GNullTuple>
{
	typedef GNullTuple ValueType;
	typedef GNullTuple TupleType;
};

template<gsize N, typename... TS> GINLINE
constexpr const typename GTupleAt<N, GTuple<TS...> >::ValueType &
GTupleConstGet(const GTuple<TS...> &tuple_)
{
	typedef GTuple<TS...> TupleType;
	typedef typename GTupleAt<N, TupleType>::TupleType BaseTupleType;

	return static_cast<const BaseTupleType &>(tuple_).Head();
}

template<gsize N, typename... TS> GINLINE
constexpr const typename GTupleAt<N, GTuple<TS...> >::ValueType &
GTupleGet(const GTuple<TS...> &tuple_)
{
	typedef GTuple<TS...> TupleType;
	typedef typename GTupleAt<N, TupleType>::TupleType BaseTupleType;

	return static_cast<const BaseTupleType &>(tuple_).Head();
}

template<gsize N, typename... TS> GINLINE
typename GTupleAt<N, GTuple<TS...> >::ValueType &
GTupleGet(GTuple<TS...> &tuple_)
{
	typedef GTuple<TS...> TupleType;
	typedef typename GTupleAt<N, TupleType>::TupleType BaseTupleType;

	return static_cast<BaseTupleType &>(tuple_).Head();
}

template<gsize N, typename... TS> GINLINE
gvoid GTupleSet(GTuple<TS...> &tuple_, const typename GTupleAt<N, GTuple<TS...> >::ValueType &val)
{
	typedef GTuple<TS...> TupleType;
	typedef typename GTupleAt<N, TupleType>::TupleType BaseTupleType;

	typename GTupleAt<N, GTuple<TS...> >::ValueType &cur_val
		= static_cast<BaseTupleType &>(tuple_).Head();
	cur_val = val;
}

template<gsize N, typename... TS> GINLINE
gvoid GTupleSet(GTuple<TS...> &tuple_, typename GTupleAt<N, GTuple<TS...> >::ValueType &&val)
{
	typedef GTuple<TS...> TupleType;
	typedef typename GTupleAt<N, TupleType>::TupleType BaseTupleType;

	typename GTupleAt<N, GTuple<TS...> >::ValueType empty;

	typename GTupleAt<N, GTuple<TS...> >::ValueType &cur_val
		= static_cast<BaseTupleType &>(tuple_).Head();
	cur_val = GMove(val);
}

struct GZeroThenVariadicArgs {};
struct GOneThenVariadicArgs {};

template<typename T1, typename T2,
	gbool = GIsEmpty<T1>::value && !GIsFinal<T1>::value>
class GCompressedPair final
	: private T1
{
private:
	T2 m_tValue2;
	typedef T1 BaseType;

public:
	template<typename... Arg2Ts>
	constexpr explicit GCompressedPair(GZeroThenVariadicArgs, Arg2Ts&&... arg2s)
		: T1(), m_tValue2(GForward<Arg2Ts>(arg2s)...)
	{
	}

	template<typename Arg1T, typename... Arg2Ts>
	GCompressedPair(GOneThenVariadicArgs,
		Arg1T&& arg1, Arg2Ts&&... arg2s)
		: T1(GForward<Arg1T>(arg1)),
		m_tValue2(GForward<Arg2Ts>(arg2s)...)
	{
	}


	T1 &First() GNOEXCEPT
	{
		return *this;
	}

	const T1 &First() const GNOEXCEPT
	{
		return *this;
	}

	volatile T1 &First() volatile GNOEXCEPT
	{
		return *this;
	}

	const volatile T1& First() const volatile GNOEXCEPT
	{
		return *this;
	}

	T2 &Second() GNOEXCEPT
	{
		return m_tValue2;
	}

	const T2 &Second() const GNOEXCEPT
	{
		return m_tValue2;
	}

	volatile T2 &Second() volatile GNOEXCEPT
	{
		return m_tValue2;
	}

	const volatile T2 &Second() const volatile GNOEXCEPT
	{
		return m_tValue2;
	}
};

template<typename T1, typename T2>
class GCompressedPair<T1, T2, false> final
	: private GPair<T1, T2>
{
private:
	typedef GPair<T1, T2> BaseType;

public:
	template<typename... Arg2Ts>
	constexpr explicit GCompressedPair(GZeroThenVariadicArgs, Arg2Ts&&... arg2s)
		: GPair<T1, T2>(T1(), T2(GForward<Arg2Ts>(arg2s)...))
	{

	}

	template<typename Arg1T, typename... Arg2Ts>
	GCompressedPair(GOneThenVariadicArgs,
		Arg1T&& arg1, Arg2Ts&&... arg2s)
		: GPair(T1(GForward<Arg1T>(arg1)),
			T2(GForward<Arg2Ts>(arg2s)...))
	{
	}

	T1 &First() GNOEXCEPT
	{
		return BaseType::First();
	}

	const T1 &First() const GNOEXCEPT
	{
		return BaseType::First();
	}

	volatile T1 &First() volatile GNOEXCEPT
	{
		return BaseType::First();
	}

	const volatile T1& First() const volatile GNOEXCEPT
	{
		return BaseType::First();
	}

	T2 &Second() GNOEXCEPT
	{
		return BaseType::Second();
	}

	const T2 &Second() const GNOEXCEPT
	{
		return BaseType::Second();
	}

	volatile T2 &Second() volatile GNOEXCEPT
	{
		return BaseType::Second();
	}

	const volatile T2 &Second() const volatile GNOEXCEPT
	{
		return BaseType::Second();
	}
};

} // namespace gsystem

#include "inline/gtuple.inl"

#endif // _CORE_TUPLE_H_
