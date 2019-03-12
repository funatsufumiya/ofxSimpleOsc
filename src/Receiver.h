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
		bool print_args = true;
		std::string logger_module_name = "ofxSimpleOsc::Receiver";
		ofxOscReceiver receiver;
		std::function<void(const ofxOscMessage&)> receive_func;

		void update(ofEventArgs & args);

	public:
		Receiver() {}
		~Receiver() {
			if (receiver.isListening()) {
				ofRemoveListener(ofEvents().update, this, &Receiver::update);
				receiver.stop();
			}
		}
		void setup(int port, bool enable_osc_log, std::function<void(const ofxOscMessage&)> receive_func);
		void setup(int port, std::function<void(const ofxOscMessage&)> receive_func);
		void showNotHandledWarning(const std::string& module_name="ofxSimpleOsc::Receiver");
		void showNotHandledWarning(const ofxOscMessage& m, const std::string& module_name="ofxSimpleOsc::Receiver");
		void printOsclog(const ofxOscMessage & m, bool print_args=true, const std::string& module_name="ofxSimpleOsc::Receiver");
		void setOscLogEnabled(bool enabled);
		void setOscLogEnabled(bool enabled, bool print_args, const std::string& logger_module_name="ofxSimpleOsc::Receiver");
		bool getOscLogEnabled();
	};

	static ofEvent<const ofxOscMessage&> OSC_MESSAGE_RECEIVED;
};