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

#include "OuyaSDK_CallbacksContentDelete.h"
#include "OuyaSDK_CallbackSingleton.h"

#include <stdio.h>

using namespace tv_ouya_console_api_content_OuyaMod;

void CallbacksContentDelete::OnDeleteFailed(const OuyaMod& ouyaMod, int code, const std::string& reason)
{
}

void CallbacksContentDelete::OnDeleted(const OuyaMod& ouyaMod)
{
}

#endif