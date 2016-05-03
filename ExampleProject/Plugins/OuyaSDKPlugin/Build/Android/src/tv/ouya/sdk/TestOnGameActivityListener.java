package tv.ouya.sdk;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import com.epicgames.ue4.GameActivity;
import tv.ouya.sdk.OuyaInputView;
import tv.ouya.sdk.unreal.IUnrealOuyaActivity;

public class TestOnGameActivityListener implements GameActivity.OnGameActivityListener {

	private static final String TAG = TestOnGameActivityListener.class.getSimpleName();

	private static GameActivity _sActivity = null;

	// OUYA handles remapping native input
	private OuyaInputView mInputView = null;

	public boolean dispatchGenericMotionEvent(MotionEvent motionEvent) {
		Log.i(TAG, "*** dispatchGenericMotionEvent ***");

		if (null != mInputView) {
			// OUYA handles remapping native input
			// Pass the native input that's been remapped to the view
			mInputView.remappedDispatchGenericMotionEvent(motionEvent);
		}
		return true;
	}

	public boolean dispatchKeyEvent(KeyEvent keyEvent) {
		Log.i(TAG, "*** dispatchKeyEvent ***");

		if (null != mInputView) {
			// OUYA handles remapping native input
			// Pass the native input that's been remapped to the view
			mInputView.remappedDispatchKeyEvent(keyEvent);
		}
		return true;
	}
		
	public boolean onActivityResult(int requestCode, int resultCode, Intent data) {
		Log.i(TAG, "*** onActivityResult ***");
		return false;
	}

	public void onCreate(Bundle savedInstanceState) {
		Log.i(TAG, "*** onCreate ***");

		// Get the GameActivity static reference
		_sActivity = GameActivity.Get();

		// Save a reference to the activity for the OUYA Plugin
		IUnrealOuyaActivity.SetActivity(_sActivity);

		// OUYA handles native input remapping
		// Construct the view
		mInputView = new OuyaInputView(_sActivity);
	}

	public void onDestroy() {
		Log.i(TAG, "*** onDestroy ***");

		if (null != mInputView) {
			// OUYA handles remapping native input
			// shutdown the input remapping
			mInputView.shutdown();
		}
	}

	public void onPause() {
		Log.i(TAG, "*** onPause ***");
	}

	public void onResume() {
		Log.i(TAG, "*** onResume ***");
	}

	public void onStart() {
		Log.i(TAG, "*** onStart ***");
	}

	public void onStop() {
		Log.i(TAG, "*** onStop ***");
	}
}
