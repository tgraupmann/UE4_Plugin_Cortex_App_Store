// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "OuyaSDKPluginPrivatePCH.h"

#include "OuyaSDKPlugin.h"

// this test is Android specific
#if PLATFORM_ANDROID

// Get access to Android logging
#include <android/log.h>

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

// OUYA handles remapping native input
#include "OuyaSDK_OuyaInputView.h"
#include "OuyaSDK_PluginOuya.h"

// OUYA handles remapping native input
// Include the OUYA namespace
using namespace OuyaSDK;
using namespace tv_ouya_sdk_OuyaInputView;

// function prototypes
int32_t AndroidPluginHandleInput(struct android_app* app, AInputEvent* event);
int RegisterJavaPluginClasses();
int SetupJNI();

// Redefine a tag for logging
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "OuyaSDKPlugin"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING true

extern struct android_app* GNativeAndroidApp;

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

	// reassign android input callback
	GNativeAndroidApp->onInputEvent = AndroidPluginHandleInput;
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
	return JNI_OK;
}

// define the callback function that will get the android input events
int32_t AndroidPluginHandleInput(struct android_app* app, AInputEvent* event)
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** AndroidPluginHandleInput: The callback was invoked! ***");
#endif

	return 0;
}

#endif
