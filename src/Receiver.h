#pragma once

#include <string>
#include <vector>
#include <functional>

#include "ofEvents.h"
#include "ofxOsc.h"

namespace ofxSimpleOsc {

	class Receiver {

	protected:
		bool enable_log = true;
		ofxOscReceiver receiver;
		std::function<void(const ofxOscMessage&)> receive_func;

		void update(ofEventArgs & args);

		bool is_int(const std::string& s);
		bool is_float(const std::string& s);
		bool is_double(const std::string& s);

		template<typename T>
		bool is_type(const std::string& s);

		std::vector<std::string> split(const std::string& s, char delimiter);

		std::string getOscArg(const ofxOscMessage& m, size_t i);

	public:
		void setup(int port, bool enable_osc_log, std::function<void(const ofxOscMessage&)> receive_func);
		void setup(int port, std::function<void(const ofxOscMessage&)> receive_func);

		void showNotHandledWarning();
		void printOscLog(const ofxOscMessage& m, bool print_args=true);

		void setOscLogEnabled(bool b);
		bool getOscLogEnabled();
	};

	static ofEvent<const ofxOscMessage&> OSC_MESSAGE_RECEIVED;
};