﻿/*
* Copyright (C) 2012-2016 OUYA, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

// this test is Android specific
#if PLATFORM_ANDROID

#include <jni.h>

#include <string>

namespace tv_ouya_console_api_OuyaController
{
	class OuyaController
	{
	public:
		static int InitJNI(JNIEnv* env);
		void Dispose();

		static const int BUTTON_O = 96;
		static const int BUTTON_U = 99;
		static const int BUTTON_Y = 100;
		static const int BUTTON_A = 97;
		static const int BUTTON_L1 = 102;
		static const int BUTTON_R1 = 103;
		static const int BUTTON_MENU = 82;
		static const int AXIS_LS_X = 0;
		static const int AXIS_LS_Y = 1;
		static const int AXIS_RS_X = 11;
		static const int AXIS_RS_Y = 14;
		static const int AXIS_L2 = 17;
		static const int AXIS_R2 = 18;
		static const int BUTTON_DPAD_UP = 19;
		static const int BUTTON_DPAD_RIGHT = 22;
		static const int BUTTON_DPAD_DOWN = 20;
		static const int BUTTON_DPAD_LEFT = 21;
		static const int BUTTON_R3 = 107;
		static const int BUTTON_L3 = 106;

		static OuyaController* getControllerByPlayer(int playerNum);
		static void showCursor(bool visible);

		const std::string& getDeviceName();

	private:
		static JNIEnv* _env;
		static jclass _jcOuyaController;
		static jmethodID _jmGetButtonData;
		static jmethodID _jmGetControllerByPlayer;
		static jmethodID _jmGetDeviceName;
		static jmethodID _jmShowCursor;
		jobject _instance;
		std::string _deviceName;

		static void FindJNI();

		void SetInstance(jobject instance);
	};
}

#endif
