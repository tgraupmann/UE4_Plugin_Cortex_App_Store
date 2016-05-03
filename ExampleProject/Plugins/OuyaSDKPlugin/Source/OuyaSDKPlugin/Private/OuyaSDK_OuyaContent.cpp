/*
* Copyright (C) 2012-2015 OUYA, Inc.
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

// this test is Android specific
#if PLATFORM_ANDROID

#include "OuyaSDK_OuyaContent.h"
#include "OuyaSDK_OuyaMod.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

using namespace tv_ouya_console_api_content_OuyaMod;

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "tv_ouya_console_api_content_OuyaContent"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace tv_ouya_console_api_content_OuyaContent
{
	jclass OuyaContent::_jcOuyaContent = 0;
	jmethodID OuyaContent::_jmCreate = 0;
	jmethodID OuyaContent::_jmGetInstance = 0;
	jmethodID OuyaContent::_jmIsInitialized = 0;

	int OuyaContent::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "tv/ouya/console/api/content/OuyaContent";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcOuyaContent = (jclass)env->NewGlobalRef(localRef);
				env->DeleteLocalRef(localRef);
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strClass);
				return JNI_ERR;
			}
		}

		return FindJNI();
	}

	int OuyaContent::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strMethod = "create";
			_jmCreate = env->GetMethodID(_jcOuyaContent, strMethod, "()Ltv/ouya/console/api/content/OuyaMod;");
			if (_jmCreate)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return JNI_ERR;
			}
		}

		{
			const char* strMethod = "getInstance";
			_jmGetInstance = env->GetStaticMethodID(_jcOuyaContent, strMethod, "()Ltv/ouya/console/api/content/OuyaContent;");
			if (_jmGetInstance)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return JNI_ERR;
			}
		}

		{
			const char* strMethod = "isInitialized";
			_jmIsInitialized = env->GetMethodID(_jcOuyaContent, strMethod, "()Z");
			if (_jmIsInitialized)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return JNI_ERR;
			}
		}

		return JNI_OK;
	}

	OuyaContent OuyaContent::CreateObject(jobject instance)
	{
		OuyaContent ouyaContent;
		ouyaContent._instance = instance;
		return ouyaContent;
	}

	jobject OuyaContent::GetInstance() const
	{
		return _instance;
	}

	void OuyaContent::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	OuyaContent OuyaContent::getInstance()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_jcOuyaContent)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcOuyaContent is not initialized");
			return OuyaContent::CreateObject(0);
		}

		if (!_jmGetInstance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetInstance is not initialized");
			return OuyaContent::CreateObject(0);
		}

		jobject localRef = (jobject)env->CallStaticObjectMethod(_jcOuyaContent, _jmGetInstance);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getInstance returned null");
			return OuyaContent::CreateObject(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return OuyaContent::CreateObject(globalRef);
	}

	OuyaMod OuyaContent::create()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return OuyaMod::CreateObject(0);
		}

		if (!_jmCreate)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmCreate is not initialized");
			return OuyaMod::CreateObject(0);
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmCreate);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "create returned null");
			return OuyaMod::CreateObject(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return OuyaMod::CreateObject(globalRef);
	}

	bool OuyaContent::isInitialized() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return false;
		}

		if (!_jmIsInitialized)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmIsInitialized is not initialized");
			return false;
		}

		bool result = env->CallBooleanMethod(_instance, _jmIsInitialized);
		return result;
	}
}

#endif
