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

#pragma once

//General Log
DECLARE_LOG_CATEGORY_EXTERN(LogOuyaSDKPlugin, Log, All);

/**
* Pending PR: https://github.com/EpicGames/UnrealEngine/pull/2313
*/

/**
* This is a unit test to verify that the JNI_OnLoad callback is properly
* invoked on Android.
* A successful test will display a message in the Android logcat.
*/
#if PLATFORM_ANDROID

/*
* In this case `Unit Test` is meant as a
* test created by the developer to make sure
* a particular feature works.
* This test uses the class constructor
* to register the callback by
* constructing a global variable
* which happens long before the
* JNI_OnLoad event.
*/
class AndroidPluginTestSetupCallbackJNIOnload
{
public:
	// The constructor will register the JNI_OnLoad callback
	AndroidPluginTestSetupCallbackJNIOnload();
};

#endif
