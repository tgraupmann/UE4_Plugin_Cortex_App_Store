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

#pragma once

// this code is Android specific
#if PLATFORM_ANDROID

#include "OuyaSDK_Bitmap.h"
#include "OuyaSDK_OutputStream.h"
#include "OuyaSDK_OuyaModScreenshot.h"

#include <jni.h>
#include <string>

namespace tv_ouya_console_api_content_OuyaModEditor
{
	class OuyaModEditor
	{
	public:
		static int InitJNI();
		static int FindJNI();
		static const OuyaModEditor CreateObject(jobject instance);
		jobject GetInstance() const;
		void Dispose() const;
		tv_ouya_console_api_content_OuyaModScreenshot::OuyaModScreenshot addScreenshot(const android_graphics_Bitmap::Bitmap& bitmap) const;
		void addTag(const std::string& tag) const;
		void deleteFile(const std::string& filename) const;
		java_io_OutputStream::OutputStream newFile(const std::string& filename) const;
		void removeScreenshot(const tv_ouya_console_api_content_OuyaModScreenshot::OuyaModScreenshot& ouyaModScreenshot) const;
		void removeTag(const std::string& tag) const;
		void setCategory(const std::string& category) const;
		void setDescription(const std::string& description) const;
		void setMetadata(const std::string& metadata) const;
		void setTitle(const std::string& title) const;
	private:
		static jclass _jcOuyaModEditor;
		static jmethodID _jmAddScreenshot;
		static jmethodID _jmAddTag;
		static jmethodID _jmDeleteFile;
		static jmethodID _jmNewFile;
		static jmethodID _jmRemoveScreenshot;
		static jmethodID _jmRemoveTag;
		static jmethodID _jmSetCategory;
		static jmethodID _jmSetDescription;
		static jmethodID _jmSetMetadata;
		static jmethodID _jmSetTitle;
		jobject _instance;
	};
}

#endif
