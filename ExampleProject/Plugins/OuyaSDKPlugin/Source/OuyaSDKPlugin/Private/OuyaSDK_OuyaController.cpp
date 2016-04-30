/*
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

#include "OuyaSDKPluginPrivatePCH.h"
#include "OuyaSDK_OuyaController.h"

// this test is Android specific
#if PLATFORM_ANDROID

// Get a reference to the JNI environment
#include "../../../Core/Public/Android/AndroidApplication.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "tv_ouya_console_api_OuyaController"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define VERBOSE_LOGGING true

namespace tv_ouya_console_api_OuyaController
{
	jclass OuyaController::_jcOuyaController = 0;
	jmethodID OuyaController::_jmGetButtonData = 0;
	jmethodID OuyaController::_jmGetControllerByPlayer = 0;
	jmethodID OuyaController::_jmGetDeviceName = 0;
	jmethodID OuyaController::_jmShowCursor = 0;

	int OuyaController::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strOuyaControllerClass = "tv/ouya/console/api/OuyaController";
			if (VERBOSE_LOGGING)
			{
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for %s", strOuyaControllerClass);
			}
			_jcOuyaController = FAndroidApplication::FindJavaClass(strOuyaControllerClass);
			if (_jcOuyaController)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strOuyaControllerClass);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strOuyaControllerClass);
				return JNI_ERR;
			}
		}

		return JNI_OK;
	}

	void OuyaController::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		GJavaVM->AttachCurrentThread(&env, 0);

		{
			const char* strMethod = "getButtonData";
			_jmGetButtonData = env->GetStaticMethodID(_jcOuyaController, strMethod, "(I)Ltv/ouya/console/api/OuyaController$ButtonData;");
			if (_jmGetButtonData)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		{
			const char* strMethod = "getControllerByPlayer";
			_jmGetControllerByPlayer = env->GetStaticMethodID(_jcOuyaController, strMethod, "(I)Ltv/ouya/console/api/OuyaController;");
			if (_jmGetControllerByPlayer)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		{
			const char* strMethod = "getDeviceName";
			_jmGetDeviceName = env->GetMethodID(_jcOuyaController, strMethod, "()Ljava/lang/String;");
			if (_jmGetDeviceName)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		{
			const char* strMethod = "showCursor";
			_jmShowCursor = env->GetStaticMethodID(_jcOuyaController, strMethod, "(Z)V");
			if (_jmShowCursor)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}
	}

	void OuyaController::SetInstance(jobject instance)
	{
		_instance = instance;
	}

	void OuyaController::Dispose()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteLocalRef(_instance);
			_instance = 0;
		}
	}

	OuyaController* OuyaController::getControllerByPlayer(int playerNum)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		FindJNI();

		if (!_jcOuyaController)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcOuyaController is not initialized");
			return 0;
		}

		if (!_jmGetControllerByPlayer)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetControllerByPlayer is not initialized");
			return 0;
		}

		jint arg1 = playerNum;
		jobject retVal = env->CallStaticObjectMethod(_jcOuyaController, _jmGetControllerByPlayer, arg1);
		if (!retVal)
		{
			// May return null if controller isn't connected
			//__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getControllerByPlayer returned null");
			return 0;
		}

		OuyaController* result = new OuyaController();
		result->SetInstance(retVal);
		return result;
	}

	void OuyaController::showCursor(bool visible)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		FindJNI();

		if (!_jcOuyaController)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcOuyaController is not initialized");
			return;
		}

		if (!_jmShowCursor)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmShowCursor is not initialized");
			return;
		}

		env->CallStaticVoidMethod(_jcOuyaController, _jmShowCursor, visible);
	}

	const std::string& OuyaController::getDeviceName()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		FindJNI();

		_deviceName = "Unavailable";

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return _deviceName;
		}

		if (!_jmGetDeviceName)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetDeviceName is not initialized");
			return _deviceName;
		}

		jstring retVal = (jstring)env->CallObjectMethod(_instance, _jmGetDeviceName);
		if (!retVal)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getDeviceName returned null");
			return _deviceName;
		}

		const char* nativeString = env->GetStringUTFChars(retVal, 0);
		_deviceName = nativeString;
		env->ReleaseStringUTFChars(retVal, nativeString);
		env->DeleteLocalRef(retVal);

		return _deviceName;
	}
}

#endif
