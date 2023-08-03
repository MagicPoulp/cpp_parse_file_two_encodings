#pragma once

// https://gist.github.com/khvorov/cd626ea3685fd5e8bf14

namespace detail
{
  template <typename F>
  struct function_traits : public function_traits<decltype(&F::operator())> {};

  template <typename R, typename C, typename... Args>
  struct function_traits<R (C::*)(Args...) const>
  {
    using function_type = std::function<R (Args...)>;
  };
}

template <typename F>
using function_type_t = typename detail::function_traits<F>::function_type;

class LambdaUtilities {
public:
  template <typename F>
  static function_type_t<F> to_function(F & lambda)
  {
    return static_cast<function_type_t<F>>(lambda);
  }
};
