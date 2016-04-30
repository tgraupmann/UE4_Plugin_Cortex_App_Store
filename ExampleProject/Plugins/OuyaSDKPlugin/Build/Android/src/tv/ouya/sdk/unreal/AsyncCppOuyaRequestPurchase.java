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

package tv.ouya.sdk.unreal;

import tv.ouya.console.api.*;


public class AsyncCppOuyaRequestPurchase {

	public static void invoke(String identifier) {

		CallbacksRequestPurchase callbacks = new CallbacksRequestPurchase();

		callbacks.m_purchasable = identifier;

		// store for access
		IUnrealOuyaActivity.SetCallbacksRequestPurchase(callbacks);

		Product product = new Product(identifier, "", 0, 0, "", 0, 0, "", "", Product.Type.ENTITLEMENT);

		// invoke service
		UnrealOuyaPlugin.requestPurchaseAsync(product);
	}
}