#pragma once

#include <string>
#include <functional>
#include <tuple>

#include "ofMain.h"
#include "ofxOsc.h"

namespace ofxSimpleOsc {
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
        
        template<typename R>
        void exec_fn_impl(std::function<R()> f){
            f();
        }
        
        template<typename R, typename T1>
        void exec_fn_impl(std::function<R(T1)> f){
            f(get<T1>(m, 0));
        }
        
        template<typename R, typename T1, typename T2>
        void exec_fn_impl(std::function<R(T1, T2)> f){
            f(get<T1>(m, 0), get<T2>(m, 1));
        }
        
        template<typename R, typename T1, typename T2, typename T3>
        void exec_fn_impl(std::function<R(T1, T2, T3)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5, T6)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4), get<T6>(m, 5));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5, T6, T7)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4), get<T6>(m, 5), get<T7>(m, 6));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5, T6, T7, T8)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4), get<T6>(m, 5), get<T7>(m, 6), get<T8>(m, 7));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5, T6, T7, T8, T9)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4), get<T6>(m, 5), get<T7>(m, 6), get<T8>(m, 7), get<T9>(m, 8));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5, T6, T7, T8, T10)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4), get<T6>(m, 5), get<T7>(m, 6), get<T8>(m, 7), get<T9>(m, 8), get<T10>(m, 9));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
        void exec_fn_impl(std::function<R(T1, T2, T3, T4, T5, T6, T7, T8, T10, T11)> f){
            f(get<T1>(m, 0), get<T2>(m, 1), get<T3>(m, 2), get<T4>(m, 3), get<T5>(m, 4), get<T6>(m, 5), get<T7>(m, 6), get<T8>(m, 7), get<T9>(m, 8), get<T10>(m, 9), get<T11>(m, 10));
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5,T6,T7,T8,T9)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5,T6,T7,T8,T9>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5,T6,T7,T8)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5,T6,T7,T8>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5,T6,T7)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5,T6,T7>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5,T6)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5,T6>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
        void exec_fn(std::function<R(T1,T2,T3,T4,T5)> f) {
            exec_fn_impl<R,T1,T2,T3,T4,T5>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3, typename T4>
        void exec_fn(std::function<R(T1,T2,T3,T4)> f) {
            exec_fn_impl<R,T1,T2,T3,T4>(f);
        }
        
        template<typename R, typename T1, typename T2, typename T3>
        void exec_fn(std::function<R(T1,T2,T3)> f) {
            exec_fn_impl<R,T1,T2,T3>(f);
        }
        
        template<typename R, typename T1, typename T2>
        void exec_fn(std::function<R(T1,T2)> f) {
            exec_fn_impl<R,T1,T2>(f);
        }
        
        template<typename R, typename Arg>
        void exec_fn(std::function<R(Arg)> f) {
            exec_fn_impl<R,Arg>(f);
        }
        
        template<typename R, typename Arg = void>
        void exec_fn(std::function<R()> f) {
            exec_fn_impl<R>(f);
        }

		template<typename F, typename R, typename... Args>
		bool matchFuncCall(F& f, function_traits<R, Args...> func_traits) {
			constexpr size_t n = sizeof...(Args);
			
			if (m.getNumArgs() < n) {
				return false;
			}
			else {
				exec_fn<R,Args...>(f);
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

		template<typename T1>
		void bind_params(T1* _1){
			*_1 = get<T1>(m, 0);
		}

		template<typename T1, typename T2>
		void bind_params(T1* _1, T2* _2){
			*_1 = get<T1>(m, 0);
			*_2 = get<T2>(m, 1);
		}

		template<typename T1, typename T2, typename T3>
		void bind_params(T1* _1, T2* _2, T3* _3){
			*_1 = get<T1>(m, 0);
			*_2 = get<T2>(m, 1);
			*_3 = get<T3>(m, 2);
		}

		template<typename T1, typename T2, typename T3, typename T4>
		void bind_params(T1* _1, T2* _2, T3* _3, T4* _4){
			*_1 = get<T1>(m, 0);
			*_2 = get<T2>(m, 1);
			*_3 = get<T3>(m, 2);
			*_4 = get<T4>(m, 3);
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		void bind_params(T1* _1, T2* _2, T3* _3, T4* _4, T5* _5){
			*_1 = get<T1>(m, 0);
			*_2 = get<T2>(m, 1);
			*_3 = get<T3>(m, 2);
			*_4 = get<T4>(m, 3);
			*_5 = get<T5>(m, 4);
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		void bind_params(T1* _1, T2* _2, T3* _3, T4* _4, T5* _5, T6* _6){
			*_1 = get<T1>(m, 0);
			*_2 = get<T2>(m, 1);
			*_3 = get<T3>(m, 2);
			*_4 = get<T4>(m, 3);
			*_5 = get<T5>(m, 4);
			*_6 = get<T6>(m, 5);
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		void bind_params(T1* _1, T2* _2, T3* _3, T4* _4, T5* _5, T6* _6, T7* _7){
			*_1 = get<T1>(m, 0);
			*_2 = get<T2>(m, 1);
			*_3 = get<T3>(m, 2);
			*_4 = get<T4>(m, 3);
			*_5 = get<T5>(m, 4);
			*_6 = get<T6>(m, 5);
			*_7 = get<T7>(m, 6);
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

		void else_show_warning(){
			if (matched) { return; }

			ofLogWarning("ofxSimpleOsc::Filter") << m.getAddress() << " (typetag: " << m.getTypeString() << ") not match. ignored.";
		}
	};

	static inline Filter filter(const ofxOscMessage& msg) {
		return std::move(Filter(msg));
	}
}
