


#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_TUPLE_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_TUPLE_H_

#include <utility>  // For ::std::pair.

#if defined(__SYMBIAN32__) || (defined(__SUNPRO_CC) && __SUNPRO_CC < 0x590)
# define GTEST_DECLARE_TUPLE_AS_FRIEND_ public:
#else
# define GTEST_DECLARE_TUPLE_AS_FRIEND_ \
    template <GTEST_10_TYPENAMES_(U)> friend class tuple; \
   private:
#endif

#define GTEST_0_TUPLE_(T) tuple<>
#define GTEST_1_TUPLE_(T) tuple<T##0, void, void, void, void, void, void, \
    void, void, void>
#define GTEST_2_TUPLE_(T) tuple<T##0, T##1, void, void, void, void, void, \
    void, void, void>
#define GTEST_3_TUPLE_(T) tuple<T##0, T##1, T##2, void, void, void, void, \
    void, void, void>
#define GTEST_4_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, void, void, void, \
    void, void, void>
#define GTEST_5_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, void, void, \
    void, void, void>
#define GTEST_6_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, void, \
    void, void, void>
#define GTEST_7_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    void, void, void>
#define GTEST_8_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    T##7, void, void>
#define GTEST_9_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    T##7, T##8, void>
#define GTEST_10_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    T##7, T##8, T##9>

#define GTEST_0_TYPENAMES_(T)
#define GTEST_1_TYPENAMES_(T) typename T##0
#define GTEST_2_TYPENAMES_(T) typename T##0, typename T##1
#define GTEST_3_TYPENAMES_(T) typename T##0, typename T##1, typename T##2
#define GTEST_4_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3
#define GTEST_5_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4
#define GTEST_6_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5
#define GTEST_7_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6
#define GTEST_8_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6, typename T##7
#define GTEST_9_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6, \
    typename T##7, typename T##8
#define GTEST_10_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6, \
    typename T##7, typename T##8, typename T##9

namespace std {
namespace tr1 {

template <typename T0 = void, typename T1 = void, typename T2 = void,
    typename T3 = void, typename T4 = void, typename T5 = void,
    typename T6 = void, typename T7 = void, typename T8 = void,
    typename T9 = void>
class tuple;

namespace gtest_internal {

template <typename T>
struct ByRef { typedef const T& type; };  // NOLINT
template <typename T>
struct ByRef<T&> { typedef T& type; };  // NOLINT

#define GTEST_BY_REF_(T) typename ::std::tr1::gtest_internal::ByRef<T>::type

template <typename T>
struct AddRef { typedef T& type; };  // NOLINT
template <typename T>
struct AddRef<T&> { typedef T& type; };  // NOLINT

#define GTEST_ADD_REF_(T) typename ::std::tr1::gtest_internal::AddRef<T>::type

template <int k> class Get;

template <bool kIndexValid, int kIndex, class Tuple>
struct TupleElement;

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 0, GTEST_10_TUPLE_(T)> { typedef T0 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 1, GTEST_10_TUPLE_(T)> { typedef T1 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 2, GTEST_10_TUPLE_(T)> { typedef T2 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 3, GTEST_10_TUPLE_(T)> { typedef T3 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 4, GTEST_10_TUPLE_(T)> { typedef T4 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 5, GTEST_10_TUPLE_(T)> { typedef T5 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 6, GTEST_10_TUPLE_(T)> { typedef T6 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 7, GTEST_10_TUPLE_(T)> { typedef T7 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 8, GTEST_10_TUPLE_(T)> { typedef T8 type; };

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 9, GTEST_10_TUPLE_(T)> { typedef T9 type; };

}  // namespace gtest_internal

template <>
class tuple<> {
 public:
  tuple() {}
  tuple(const tuple& /* t */)  {}
  tuple& operator=(const tuple& /* t */) { return *this; }
};

template <GTEST_1_TYPENAMES_(T)>
class GTEST_1_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0) : f0_(f0) {}

  tuple(const tuple& t) : f0_(t.f0_) {}

  template <GTEST_1_TYPENAMES_(U)>
  tuple(const GTEST_1_TUPLE_(U)& t) : f0_(t.f0_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_1_TYPENAMES_(U)>
  tuple& operator=(const GTEST_1_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_1_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_1_TUPLE_(U)& t) {
    f0_ = t.f0_;
    return *this;
  }

  T0 f0_;
};

template <GTEST_2_TYPENAMES_(T)>
class GTEST_2_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1) : f0_(f0),
      f1_(f1) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_) {}

  template <GTEST_2_TYPENAMES_(U)>
  tuple(const GTEST_2_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_) {}
  template <typename U0, typename U1>
  tuple(const ::std::pair<U0, U1>& p) : f0_(p.first), f1_(p.second) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_2_TYPENAMES_(U)>
  tuple& operator=(const GTEST_2_TUPLE_(U)& t) {
    return CopyFrom(t);
  }
  template <typename U0, typename U1>
  tuple& operator=(const ::std::pair<U0, U1>& p) {
    f0_ = p.first;
    f1_ = p.second;
    return *this;
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_2_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_2_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
};

template <GTEST_3_TYPENAMES_(T)>
class GTEST_3_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2) : f0_(f0), f1_(f1), f2_(f2) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_) {}

  template <GTEST_3_TYPENAMES_(U)>
  tuple(const GTEST_3_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_3_TYPENAMES_(U)>
  tuple& operator=(const GTEST_3_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_3_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_3_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
};

template <GTEST_4_TYPENAMES_(T)>
class GTEST_4_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3) : f0_(f0), f1_(f1), f2_(f2),
      f3_(f3) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_) {}

  template <GTEST_4_TYPENAMES_(U)>
  tuple(const GTEST_4_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_4_TYPENAMES_(U)>
  tuple& operator=(const GTEST_4_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_4_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_4_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
};

template <GTEST_5_TYPENAMES_(T)>
class GTEST_5_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3,
      GTEST_BY_REF_(T4) f4) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_) {}

  template <GTEST_5_TYPENAMES_(U)>
  tuple(const GTEST_5_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_5_TYPENAMES_(U)>
  tuple& operator=(const GTEST_5_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_5_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_5_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
};

template <GTEST_6_TYPENAMES_(T)>
class GTEST_6_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4),
      f5_(f5) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_) {}

  template <GTEST_6_TYPENAMES_(U)>
  tuple(const GTEST_6_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_6_TYPENAMES_(U)>
  tuple& operator=(const GTEST_6_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_6_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_6_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
};

template <GTEST_7_TYPENAMES_(T)>
class GTEST_7_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6) : f0_(f0), f1_(f1), f2_(f2),
      f3_(f3), f4_(f4), f5_(f5), f6_(f6) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_) {}

  template <GTEST_7_TYPENAMES_(U)>
  tuple(const GTEST_7_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_7_TYPENAMES_(U)>
  tuple& operator=(const GTEST_7_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_7_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_7_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
};

template <GTEST_8_TYPENAMES_(T)>
class GTEST_8_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_(), f7_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6,
      GTEST_BY_REF_(T7) f7) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4),
      f5_(f5), f6_(f6), f7_(f7) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_) {}

  template <GTEST_8_TYPENAMES_(U)>
  tuple(const GTEST_8_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_8_TYPENAMES_(U)>
  tuple& operator=(const GTEST_8_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_8_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_8_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    f7_ = t.f7_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
  T7 f7_;
};

template <GTEST_9_TYPENAMES_(T)>
class GTEST_9_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_(), f7_(), f8_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6, GTEST_BY_REF_(T7) f7,
      GTEST_BY_REF_(T8) f8) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4),
      f5_(f5), f6_(f6), f7_(f7), f8_(f8) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_) {}

  template <GTEST_9_TYPENAMES_(U)>
  tuple(const GTEST_9_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_9_TYPENAMES_(U)>
  tuple& operator=(const GTEST_9_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_9_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_9_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    f7_ = t.f7_;
    f8_ = t.f8_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
  T7 f7_;
  T8 f8_;
};

template <GTEST_10_TYPENAMES_(T)>
class tuple {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_(), f7_(), f8_(),
      f9_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6, GTEST_BY_REF_(T7) f7,
      GTEST_BY_REF_(T8) f8, GTEST_BY_REF_(T9) f9) : f0_(f0), f1_(f1), f2_(f2),
      f3_(f3), f4_(f4), f5_(f5), f6_(f6), f7_(f7), f8_(f8), f9_(f9) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_), f9_(t.f9_) {}

  template <GTEST_10_TYPENAMES_(U)>
  tuple(const GTEST_10_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_),
      f9_(t.f9_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_10_TYPENAMES_(U)>
  tuple& operator=(const GTEST_10_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_10_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_10_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    f7_ = t.f7_;
    f8_ = t.f8_;
    f9_ = t.f9_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
  T7 f7_;
  T8 f8_;
  T9 f9_;
};



inline tuple<> make_tuple() { return tuple<>(); }

template <GTEST_1_TYPENAMES_(T)>
inline GTEST_1_TUPLE_(T) make_tuple(const T0& f0) {
  return GTEST_1_TUPLE_(T)(f0);
}

template <GTEST_2_TYPENAMES_(T)>
inline GTEST_2_TUPLE_(T) make_tuple(const T0& f0, const T1& f1) {
  return GTEST_2_TUPLE_(T)(f0, f1);
}

template <GTEST_3_TYPENAMES_(T)>
inline GTEST_3_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2) {
  return GTEST_3_TUPLE_(T)(f0, f1, f2);
}

template <GTEST_4_TYPENAMES_(T)>
inline GTEST_4_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3) {
  return GTEST_4_TUPLE_(T)(f0, f1, f2, f3);
}

template <GTEST_5_TYPENAMES_(T)>
inline GTEST_5_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4) {
  return GTEST_5_TUPLE_(T)(f0, f1, f2, f3, f4);
}

template <GTEST_6_TYPENAMES_(T)>
inline GTEST_6_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5) {
  return GTEST_6_TUPLE_(T)(f0, f1, f2, f3, f4, f5);
}

template <GTEST_7_TYPENAMES_(T)>
inline GTEST_7_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6) {
  return GTEST_7_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6);
}

template <GTEST_8_TYPENAMES_(T)>
inline GTEST_8_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6, const T7& f7) {
  return GTEST_8_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6, f7);
}

template <GTEST_9_TYPENAMES_(T)>
inline GTEST_9_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6, const T7& f7,
    const T8& f8) {
  return GTEST_9_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6, f7, f8);
}

template <GTEST_10_TYPENAMES_(T)>
inline GTEST_10_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6, const T7& f7,
    const T8& f8, const T9& f9) {
  return GTEST_10_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9);
}


template <typename Tuple> struct tuple_size;

template <GTEST_0_TYPENAMES_(T)>
struct tuple_size<GTEST_0_TUPLE_(T)> { static const int value = 0; };

template <GTEST_1_TYPENAMES_(T)>
struct tuple_size<GTEST_1_TUPLE_(T)> { static const int value = 1; };

template <GTEST_2_TYPENAMES_(T)>
struct tuple_size<GTEST_2_TUPLE_(T)> { static const int value = 2; };

template <GTEST_3_TYPENAMES_(T)>
struct tuple_size<GTEST_3_TUPLE_(T)> { static const int value = 3; };

template <GTEST_4_TYPENAMES_(T)>
struct tuple_size<GTEST_4_TUPLE_(T)> { static const int value = 4; };

template <GTEST_5_TYPENAMES_(T)>
struct tuple_size<GTEST_5_TUPLE_(T)> { static const int value = 5; };

template <GTEST_6_TYPENAMES_(T)>
struct tuple_size<GTEST_6_TUPLE_(T)> { static const int value = 6; };

template <GTEST_7_TYPENAMES_(T)>
struct tuple_size<GTEST_7_TUPLE_(T)> { static const int value = 7; };

template <GTEST_8_TYPENAMES_(T)>
struct tuple_size<GTEST_8_TUPLE_(T)> { static const int value = 8; };

template <GTEST_9_TYPENAMES_(T)>
struct tuple_size<GTEST_9_TUPLE_(T)> { static const int value = 9; };

template <GTEST_10_TYPENAMES_(T)>
struct tuple_size<GTEST_10_TUPLE_(T)> { static const int value = 10; };

template <int k, class Tuple>
struct tuple_element {
  typedef typename gtest_internal::TupleElement<
      k < (tuple_size<Tuple>::value), k, Tuple>::type type;
};

#define GTEST_TUPLE_ELEMENT_(k, Tuple) typename tuple_element<k, Tuple >::type


namespace gtest_internal {

template <>
class Get<0> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(0, Tuple))
  Field(Tuple& t) { return t.f0_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(0, Tuple))
  ConstField(const Tuple& t) { return t.f0_; }
};

template <>
class Get<1> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(1, Tuple))
  Field(Tuple& t) { return t.f1_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(1, Tuple))
  ConstField(const Tuple& t) { return t.f1_; }
};

template <>
class Get<2> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(2, Tuple))
  Field(Tuple& t) { return t.f2_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(2, Tuple))
  ConstField(const Tuple& t) { return t.f2_; }
};

template <>
class Get<3> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(3, Tuple))
  Field(Tuple& t) { return t.f3_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(3, Tuple))
  ConstField(const Tuple& t) { return t.f3_; }
};

template <>
class Get<4> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(4, Tuple))
  Field(Tuple& t) { return t.f4_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(4, Tuple))
  ConstField(const Tuple& t) { return t.f4_; }
};

template <>
class Get<5> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(5, Tuple))
  Field(Tuple& t) { return t.f5_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(5, Tuple))
  ConstField(const Tuple& t) { return t.f5_; }
};

template <>
class Get<6> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(6, Tuple))
  Field(Tuple& t) { return t.f6_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(6, Tuple))
  ConstField(const Tuple& t) { return t.f6_; }
};

template <>
class Get<7> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(7, Tuple))
  Field(Tuple& t) { return t.f7_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(7, Tuple))
  ConstField(const Tuple& t) { return t.f7_; }
};

template <>
class Get<8> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(8, Tuple))
  Field(Tuple& t) { return t.f8_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(8, Tuple))
  ConstField(const Tuple& t) { return t.f8_; }
};

template <>
class Get<9> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(9, Tuple))
  Field(Tuple& t) { return t.f9_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(9, Tuple))
  ConstField(const Tuple& t) { return t.f9_; }
};

}  // namespace gtest_internal

template <int k, GTEST_10_TYPENAMES_(T)>
GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(k, GTEST_10_TUPLE_(T)))
get(GTEST_10_TUPLE_(T)& t) {
  return gtest_internal::Get<k>::Field(t);
}

template <int k, GTEST_10_TYPENAMES_(T)>
GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(k,  GTEST_10_TUPLE_(T)))
get(const GTEST_10_TUPLE_(T)& t) {
  return gtest_internal::Get<k>::ConstField(t);
}



namespace gtest_internal {

template <int kSize1, int kSize2>
struct SameSizeTuplePrefixComparator;

template <>
struct SameSizeTuplePrefixComparator<0, 0> {
  template <class Tuple1, class Tuple2>
  static bool Eq(const Tuple1& /* t1 */, const Tuple2& /* t2 */) {
    return true;
  }
};

template <int k>
struct SameSizeTuplePrefixComparator<k, k> {
  template <class Tuple1, class Tuple2>
  static bool Eq(const Tuple1& t1, const Tuple2& t2) {
    return SameSizeTuplePrefixComparator<k - 1, k - 1>::Eq(t1, t2) &&
        ::std::tr1::get<k - 1>(t1) == ::std::tr1::get<k - 1>(t2);
  }
};

}  // namespace gtest_internal

template <GTEST_10_TYPENAMES_(T), GTEST_10_TYPENAMES_(U)>
inline bool operator==(const GTEST_10_TUPLE_(T)& t,
                       const GTEST_10_TUPLE_(U)& u) {
  return gtest_internal::SameSizeTuplePrefixComparator<
      tuple_size<GTEST_10_TUPLE_(T)>::value,
      tuple_size<GTEST_10_TUPLE_(U)>::value>::Eq(t, u);
}

template <GTEST_10_TYPENAMES_(T), GTEST_10_TYPENAMES_(U)>
inline bool operator!=(const GTEST_10_TUPLE_(T)& t,
                       const GTEST_10_TUPLE_(U)& u) { return !(t == u); }


}  // namespace tr1
}  // namespace std

#undef GTEST_0_TUPLE_
#undef GTEST_1_TUPLE_
#undef GTEST_2_TUPLE_
#undef GTEST_3_TUPLE_
#undef GTEST_4_TUPLE_
#undef GTEST_5_TUPLE_
#undef GTEST_6_TUPLE_
#undef GTEST_7_TUPLE_
#undef GTEST_8_TUPLE_
#undef GTEST_9_TUPLE_
#undef GTEST_10_TUPLE_

#undef GTEST_0_TYPENAMES_
#undef GTEST_1_TYPENAMES_
#undef GTEST_2_TYPENAMES_
#undef GTEST_3_TYPENAMES_
#undef GTEST_4_TYPENAMES_
#undef GTEST_5_TYPENAMES_
#undef GTEST_6_TYPENAMES_
#undef GTEST_7_TYPENAMES_
#undef GTEST_8_TYPENAMES_
#undef GTEST_9_TYPENAMES_
#undef GTEST_10_TYPENAMES_

#undef GTEST_DECLARE_TUPLE_AS_FRIEND_
#undef GTEST_BY_REF_
#undef GTEST_ADD_REF_
#undef GTEST_TUPLE_ELEMENT_

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_TUPLE_H_
