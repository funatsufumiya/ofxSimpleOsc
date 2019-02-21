#pragma once

#include <string>
#include "ofxOsc.h"

namespace ofxSimpleOsc {
	class Sender {
	protected:
		ofxOscSender sender;
		ofxOscMessage temp_message;

		void sendImpl(ofxOscMessage& message);

		template <class Head, class... Tail>
		void sendImpl(ofxOscMessage& message, const Head& head, const Tail&... tail);

		template <typename T>
		void addArg(ofxOscMessage& m, T arg);

	public:
		Sender(){}
		~Sender(){
			sender.clear();
		}

		void setup(const std::string& host, int port);
		void send(ofxOscMessage& message, bool wrap_in_bundle=true);

		template <class... Args>
		void send(const std::string& address, const Args&... args);
	};
};