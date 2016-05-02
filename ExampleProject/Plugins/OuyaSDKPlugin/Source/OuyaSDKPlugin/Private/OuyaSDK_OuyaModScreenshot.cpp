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

#include "OuyaSDK_OuyaModScreenshot.h"

// Get a reference to the JNI environment
#include "../../../Core/Public/Android/AndroidApplication.h"

// Get a reference to the JVM
#include "../../../Launch/Public/Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "tv_ouya_console_api_content_OuyaModScreenshot"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING true

using namespace android_graphics_Bitmap;

namespace tv_ouya_console_api_content_OuyaModScreenshot
{
	jclass OuyaModScreenshot::_jcOuyaModScreenshot = 0;

	int OuyaModScreenshot::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "tv/ouya/console/api/content/OuyaModScreenshot";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = env->FindClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcOuyaModScreenshot = (jclass)env->NewGlobalRef(localRef);
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

	int OuyaModScreenshot::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		return JNI_OK;
	}

	const OuyaModScreenshot OuyaModScreenshot::CreateObject(jobject instance)
	{
		OuyaModScreenshot ouyaModScreenshot;
		ouyaModScreenshot._instance = instance;
		return ouyaModScreenshot;
	}

	jobject OuyaModScreenshot::GetInstance() const
	{
		return _instance;
	}

	void OuyaModScreenshot::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	Bitmap OuyaModScreenshot::getImage() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is null!");
			return Bitmap(0);
		}

		jmethodID method;
		{
			const char* strMethod = "getImage";
			method = env->GetMethodID(_jcOuyaModScreenshot, strMethod, "()Landroid/graphics/Bitmap;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return Bitmap(0);
			}
		}

		jobject localRef = env->CallObjectMethod(_instance, method);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getImage returned null");
			return Bitmap(0);
		}
		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getImage returned Bitmap");
#endif
		return Bitmap(globalRef);
	}

	Bitmap OuyaModScreenshot::getThumbnail() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is null!");
			return Bitmap(0);
		}

		jmethodID method;
		{
			const char* strMethod = "getThumbnail";
			method = env->GetMethodID(_jcOuyaModScreenshot, strMethod, "()Landroid/graphics/Bitmap;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return Bitmap(0);
			}
		}

		jobject localRef = env->CallObjectMethod(_instance, method);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getThumbnail returned null");
			return Bitmap(0);
		}
		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getThumbnail returned Bitmap");
#endif
		return Bitmap(globalRef);
	}
}

#endif
