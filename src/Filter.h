#pragma once

#include <string>
#include <functional>
#include <tuple>

#include "ofMain.h"
#include "ofxOsc.h"

namespace ofxSimpleOsc {
	namespace detail {
		template <typename type, type ... ns>
		struct integer_sequence {
			using value_type = type;
			static constexpr std::size_t size() noexcept { return sizeof...(ns); }
		};
		
		template <typename integer_type, integer_type n, integer_type ... ns>
		struct make_integer_sequence_impl {
			struct sequence_wrapper { using type = integer_sequence<integer_type, ns ...>; };
			using type = typename conditional<
			0 < n,
			make_integer_sequence_impl<integer_type, n - 1, n - 1, ns ...>,
			sequence_wrapper
			>::type::type;
		};
		
		template <typename type, type n>
		using make_integer_sequence = typename make_integer_sequence_impl<type, n>::type;
		
		template <std::size_t ... ns>
		using index_sequence = integer_sequence<std::size_t, ns ...>;
		
		template <std::size_t n>
		using make_index_sequence = make_integer_sequence<std::size_t, n>;
		
		template <typename... types>
		using index_sequence_for = make_index_sequence<sizeof...(types)>;
	};
	
	class Filter {
	protected:
		const ofxOscMessage& m;

		bool matched = false;

		template<typename R, typename... Args>
		struct function_traits {
			typedef R return_type;
			typedef std::tuple<Args...> arg_types;
			static constexpr size_t arg_num = sizeof...(Args);
		};

		template<typename F, typename R, typename... Args>
		const function_traits<R, Args...> make_function_traits_impl(F, R(F::*f)(Args...) const) {
			return function_traits<R, Args...>();
		}

		template<typename F>
		auto make_function_traits(F f) -> decltype(make_function_traits_impl(f, &F::operator())) {
			return make_function_traits_impl(f, &F::operator());
		}

		template<typename R, typename Head, typename... Tail>
		const function_traits<R, Tail...> tail(function_traits<R, Head, Tail...> ft) {
			return function_traits<R, Tail...>();
		}

		template<typename T>
		T get(const ofxOscMessage& m, size_t i);
		
		template <typename R, typename ... Ts, std::size_t ... indices>
		void exec_fn_impl(std::function<R(Ts ...)> f, ofxSimpleOsc::detail::index_sequence<indices ...>) {
			f(get<typename std::tuple_element<indices, std::tuple<Ts ...>>::type>(m, indices) ...);
		}
		
		
		template <typename R, typename ... Ts>
		void exec_fn(std::function<R(Ts ...)> f) {
			exec_fn_impl(f, ofxSimpleOsc::detail::make_index_sequence<sizeof...(Ts)>{});
		}
		
		template<typename F, typename R, typename... Args>
		bool matchFuncCall(F& f, function_traits<R, Args...> func_traits) {
			constexpr size_t n = sizeof...(Args);
			
			if (m.getNumArgs() < n) {
				return false;
			}
			else {
				exec_fn<R,Args...>(std::function<R(Args ...)>(f));
				return true;
			}
		}

		template<typename F, typename R, typename Arg = const ofxOscMessage&>
		bool matchFuncCall(F& f, function_traits<R, const ofxOscMessage&> func_traits) {
			f(m);
			return true;
		}

		template<typename F, typename R, typename Arg = ofxOscMessage&>
		bool matchFuncCall(F& f, function_traits<R, ofxOscMessage&> func_traits) {
			f(m);
			return true;
		}

		template<typename F, typename R, typename Arg = ofxOscMessage>
		bool matchFuncCall(F& f, function_traits<R, ofxOscMessage> func_traits) {
			f(m);
			return true;
		}

		template<typename... Args>
		bool bindImpl(Args*... params) {
			constexpr size_t n = sizeof...(Args);
			
			if (m.getNumArgs() < n) {
				return false;
			}
			else {
				bind_params<Args...>(params...);
				return true;
			}
		}

		template<typename Arg = ofVec2f>
		bool bindImpl(ofVec2f* p) {
			size_t n = m.getNumArgs();
			
			if (n < 2){
				return false;
			}
			else {
				p->x = get<float>(m, 0);
				p->y = get<float>(m, 1);
				return true;
			}
		}

		template<typename Arg = ofVec3f>
		bool bindImpl(ofVec3f* p) {
			size_t n = m.getNumArgs();
			
			if (n < 2){
				return false;
			}
			else if(n == 2){
				p->x = get<float>(m, 0);
				p->y = get<float>(m, 1);
				return true;
			}
			else{
				p->x = get<float>(m, 0);
				p->y = get<float>(m, 1);
				p->z = get<float>(m, 2);
				return true;
			}
		}

		template<typename Arg = ofColor>
		bool bindImpl(ofColor* p) {
			size_t n = m.getNumArgs();
			
			if (n < 1){
				return false;
			}
			else if(n == 1){
				*p = ofColor(get<float>(m, 0));
				return true;
			}
			else if(n == 2){
				*p = ofColor(get<float>(m, 0), get<float>(m, 1));
				return true;
			}
			else if(n == 3){
				*p = ofColor(get<float>(m, 0), get<float>(m, 1), get<float>(m, 2));
				return true;
			}
			else if(n == 4){
				*p = ofColor(get<float>(m, 0), get<float>(m, 1), get<float>(m, 2), get<float>(m, 3));
				return true;
			}
		}

		template<typename Arg = ofFloatColor>
		bool bindImpl(ofFloatColor* p) {
			size_t n = m.getNumArgs();
			
			if (n < 1){
				return false;
			}
			else if(n == 1){
				*p = ofFloatColor(get<float>(m, 0));
				return true;
			}
			else if(n == 2){
				*p = ofFloatColor(get<float>(m, 0), get<float>(m, 1));
				return true;
			}
			else if(n == 3){
				*p = ofFloatColor(get<float>(m, 0), get<float>(m, 1), get<float>(m, 2));
				return true;
			}
			else if(n == 4){
				*p = ofFloatColor(get<float>(m, 0), get<float>(m, 1), get<float>(m, 2), get<float>(m, 3));
				return true;
			}
		}

		template<typename Arg = ofShortColor>
		bool bindImpl(ofShortColor* p) {
			size_t n = m.getNumArgs();
			
			if (n < 1){
				return false;
			}
			else if(n == 1){
				*p = ofShortColor(get<int>(m, 0));
				return true;
			}
			else if(n == 2){
				*p = ofShortColor(get<int>(m, 0), get<int>(m, 1));
				return true;
			}
			else if(n == 3){
				*p = ofShortColor(get<int>(m, 0), get<int>(m, 1), get<int>(m, 2));
				return true;
			}
			else if(n == 4){
				*p = ofShortColor(get<int>(m, 0), get<int>(m, 1), get<int>(m, 2), get<int>(m, 3));
				return true;
			}
		}

		template<typename Arg = ofQuaternion>
		bool bindImpl(ofQuaternion* p) {
			size_t n = m.getNumArgs();
			
			if (n < 4){
				return false;
			}
			else {
				*p = ofQuaternion(get<float>(m, 0), get<float>(m, 1), get<float>(m, 2), get<float>(m, 3));
				return true;
			}
		}

		template<typename Arg = ofRectangle>
		bool bindImpl(ofRectangle* p) {
			size_t n = m.getNumArgs();
			
			if (n < 4){
				return false;
			}
			else {
                *p = ofRectangle(get<float>(m, 0), get<float>(m, 1), get<float>(m, 2), get<float>(m, 3));
				return true;
			}
		}
		
		template <typename ... Ts, std::size_t ... indices>
		void bind_params_impl(std::tuple<Ts * ...> t, ofxSimpleOsc::detail::index_sequence<indices ...>) {
			auto trash = {(*std::get<indices>(t) = get<typename std::tuple_element<indices, std::tuple<Ts ...>>::type>(m, indices), 0)...};
		}
		
		template <typename ... Ts>
		void bind_params(Ts * ... vs) {
			bind_params_impl(std::make_tuple(vs ...), ofxSimpleOsc::detail::make_index_sequence<sizeof...(Ts)>{});
		}
		
	public:
		Filter(const ofxOscMessage & msg) : m(msg) {}

		template<typename Func>
		Filter& match(const std::string& address, Func func) {
			if (matched) { return *this; }

			if (m.getAddress() == address) {
				auto t = make_function_traits(func);

				if (matchFuncCall(func, t)) {
					matched = true;
				}
			}

			return *this;
		}

		template<typename Func>
		Filter& bind_fn(const std::string& address, Func func) {
			return match(address, func);
		}

		template<typename Func>
		Filter& when(const std::string& address, Func func) {
			return match(address, func);
		}

		template<typename... Args>
		Filter& bind(const std::string& address, Args*... params) {
			if (matched) { return *this; }

			if (m.getAddress() == address) {
				if (bindImpl(params...)) {
					matched = true;
				}
			}

			return *this;
		}

		void else_(std::function<void()> func)
		{
			if (matched) { return; }

			func();
			matched = true;
		}

		void else_(std::function<void(const ofxOscMessage&)> func){
			if (matched) { return; }

			func(m);
			matched = true;
		}

		void else_show_warning(const string& module_name = "ofxSimpleOsc::Filter"){
			if (matched) { return; }

			ofLogWarning(module_name) << m.getAddress() << " (typetag: " << m.getTypeString() << ") not match. ignored.";
		}
	};

	static inline Filter filter(const ofxOscMessage& msg) {
		return std::move(Filter(msg));
	}
}
