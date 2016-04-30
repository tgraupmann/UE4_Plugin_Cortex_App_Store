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

// OUYA handles remapping native input
#include "OuyaSDK_OuyaInputView.h"
#include "OuyaSDK_PluginOuya.h"

// OUYA handles remapping native input
// Include the OUYA namespace
using namespace OuyaSDK;
using namespace tv_ouya_sdk_OuyaInputView;

// function prototypes
int SetupJNI();
int RegisterJavaPluginClasses();
int RegisterFromJavaPluginTestGameActivity();

// Redefine a tag for logging
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "OuyaSDKPlugin"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING true

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
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** StartupModule ***");
#endif

	if (SetupJNI() == JNI_OK)
	{
		UE_LOG(LogOuyaSDKPlugin, Log, TEXT("*** JNI has initialized. ***"));
	}
	else
	{
		UE_LOG(LogOuyaSDKPlugin, Log, TEXT("*** JNI failed to initialize! ***"));
	}
#endif
}

void FOuyaSDKPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if PLATFORM_ANDROID
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** ShutdownModule ***");
#endif
#endif
}

// Android specific code
#if PLATFORM_ANDROID

// Setup the JNI classes, called from StartupModule
int SetupJNI()
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** SetupJNI ***");
#endif

	if (OuyaInputView::InitJNI() == JNI_ERR)
	{
		return JNI_ERR;
	}

	if (RegisterJavaPluginClasses() == JNI_ERR)
	{
		return JNI_ERR;
	}

	if (RegisterFromJavaPluginTestGameActivity() == JNI_ERR)
	{
		return JNI_ERR;
	}	

#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** SetupJNI initialized successfully. ***");
#endif
	return JNI_OK;
}

// register classes from the OUYA SDK
int RegisterJavaPluginClasses()
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Initialize the OuyaInputView classes ***");
#endif

	if (OuyaInputView::InitJNI() == JNI_ERR)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to initialize the OuyaInputView class! ***");
		return JNI_ERR;
	}

#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Initialize the PluginOuya classes!***");
#endif

	if (PluginOuya::InitJNI() == JNI_ERR)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to initialize the PluginOuya class! ***");
		return JNI_ERR;
	}
}

// register classes from the JAVA
int RegisterFromJavaPluginTestGameActivity()
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** FAndroidApplication::GetJavaEnv() ***");
#endif
	JNIEnv* env = FAndroidApplication::GetJavaEnv();

	const char* strPluginJavaClass = "tv/ouya/sdk/PluginTestGameActivity";
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Searching for %s... ***", strPluginJavaClass);
#endif

	jclass jcPluginJavaClass = FAndroidApplication::FindJavaClass(strPluginJavaClass);

	if (jcPluginJavaClass)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Found class %s ***", strPluginJavaClass);
#endif
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
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Found method %s", strPluginJavaMethod);
#endif
	}
	else
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strPluginJavaMethod);
		return JNI_ERR;
	}

#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Invoking method %s...", strPluginJavaMethod);
#endif
	env->CallStaticVoidMethod(jcPluginJavaClass, jmInit);
	return JNI_OK;
}

// Use a global variable to cause the constructor to invoke
AndroidPluginTestSetupCallbackAndroidInput GSetupCallbackAndroidInput;

// define the callback function that will get the android input events
int32_t AndroidPluginTestHandleRegisterCallbackAndroidInput(struct android_app* app, AInputEvent* event)
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** This indicates a successful test. The callback was invoked! ***");
#endif

	return 0;
}

// Use the constructor to register the input callback using the global var: `GSetupCallbackAndroidInput`
AndroidPluginTestSetupCallbackAndroidInput::AndroidPluginTestSetupCallbackAndroidInput()
{
	RegisterCallbackAndroidInput(AndroidPluginTestHandleRegisterCallbackAndroidInput);
}

#endif
