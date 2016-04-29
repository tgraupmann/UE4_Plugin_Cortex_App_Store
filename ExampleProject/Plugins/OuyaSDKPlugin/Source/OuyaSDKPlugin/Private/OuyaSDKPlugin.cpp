// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "OuyaSDKPluginPrivatePCH.h"

#include "OuyaSDKPlugin.h"

// this test is Android specific
#if PLATFORM_ANDROID

// Get access to Android logging
#include <android/log.h>

// Get a reference to the JNI environment
#include "../../../Core/Public/Android/AndroidApplication.h"

// The JNI_OnLoad callback is defined in the JNI code
#include "../../../Launch/Public/Android/AndroidJNI.h"

// The Android Input callback is defined in the launcher code
#include "../../../Launch/Public/Android/LaunchAndroid.h"

// Find a class within the JAR
#include "OuyaSDK_OuyaController.h"

using namespace tv_ouya_console_api_OuyaController;

// function prototypes
int SetupJNI(JNIEnv* env);
int RegisterFromJarOuyaController(JNIEnv* env);
int RegisterFromJavaPluginTestGameActivity(JNIEnv* env);

// Redefine a tag for logging
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "OuyaSDKPlugin"

#endif

class FOuyaSDKPlugin : public IOuyaSDKPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FOuyaSDKPlugin, OuyaSDKPlugin)

DEFINE_LOG_CATEGORY(LogOuyaSDKPlugin);

void FOuyaSDKPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	if (IOuyaSDKPlugin::IsAvailable())
	{
		UE_LOG(LogOuyaSDKPlugin, Log, TEXT("*** OuyaSDKPlugin has loaded. ***"));
	}
	else
	{
		UE_LOG(LogOuyaSDKPlugin, Log, TEXT("*** OuyaSDKPlugin has not loaded! ***"));
	}

	// Android specific code
#if PLATFORM_ANDROID
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** StartupModule ***");

	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** FAndroidApplication::GetJavaEnv() ***");
	JNIEnv* env = FAndroidApplication::GetJavaEnv();

	SetupJNI(env);
#endif
}

void FOuyaSDKPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if PLATFORM_ANDROID
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** ShutdownModule ***");
#endif
}

// Android specific code
#if PLATFORM_ANDROID

// Setup the JNI classes, called from StartupModule
int SetupJNI(JNIEnv* env)
{
	// check the adb logcat
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** SetupJNI ***");

	if (RegisterFromJarOuyaController(env) == JNI_ERR)
	{
		return JNI_ERR;
	}

	if (RegisterFromJavaPluginTestGameActivity(env) == JNI_ERR)
	{
		return JNI_ERR;
	}	

	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** SetupJNI initialized successfully. ***");
	return JNI_OK;
}

// register classes from the JAR
int RegisterFromJarOuyaController(JNIEnv* env)
{
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Initialize the OuyaController classes... ***");
	if (OuyaController::InitJNI(env) == JNI_ERR)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Failed to initialize the OuyaController class! ***");
		return JNI_ERR;
	}
	else
	{
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Registered the OuyaController class. ***");
		return JNI_OK;
	}
}

// register classes from the JAVA
int RegisterFromJavaPluginTestGameActivity(JNIEnv* env)
{
	const char* strPluginJavaClass = "tv/ouya/sdk/PluginTestGameActivity";
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Searching for %s... ***", strPluginJavaClass);

	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** FAndroidApplication::FindJavaClass() ***");
	jclass jcPluginJavaClass = FAndroidApplication::FindJavaClass(strPluginJavaClass);

	if (jcPluginJavaClass)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Found class %s ***", strPluginJavaClass);
	}
	else
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", strPluginJavaClass);
		return JNI_ERR;
	}

	const char* strPluginJavaMethod = "initialize";
	jmethodID jmInit = env->GetStaticMethodID(jcPluginJavaClass, strPluginJavaMethod, "()V");
	if (jmInit)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Found method %s", strPluginJavaMethod);
	}
	else
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strPluginJavaMethod);
		return JNI_ERR;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Invoking method %s...", strPluginJavaMethod);
	env->CallStaticVoidMethod(jcPluginJavaClass, jmInit);
	return JNI_OK;
}

// Use a global variable to cause the constructor to invoke
AndroidPluginTestSetupCallbackAndroidInput GSetupCallbackAndroidInput;

// define the callback function that will get the android input events
int32_t AndroidPluginTestHandleRegisterCallbackAndroidInput(struct android_app* app, AInputEvent* event)
{
	// check the adb logcat
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** This indicates a successful test. The callback was invoked! ***");

	return 0;
}

// Use the constructor to register the input callback using the global var: `GSetupCallbackAndroidInput`
AndroidPluginTestSetupCallbackAndroidInput::AndroidPluginTestSetupCallbackAndroidInput()
{
	RegisterCallbackAndroidInput(AndroidPluginTestHandleRegisterCallbackAndroidInput);
}

#endif
