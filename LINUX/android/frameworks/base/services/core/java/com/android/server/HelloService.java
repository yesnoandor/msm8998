package com.android.server;

import android.content.Context;

import android.os.IHelloService;
import android.util.Slog;

public class HelloService extends IHelloService.Stub {
	private static final String TAG = "HelloService";
	
	HelloService() {
		Slog.i(TAG, "HelloService::+++++++++++++++");
		
		init_native();

		Slog.i(TAG, "HelloService::---------------");
	}

	public void setVal(int val) {
		Slog.i(TAG, "HelloService::setVal+++++++++++++++");

		setVal_native(val);

		Slog.i(TAG, "HelloService::setVal---------------");
	}

	public int getVal() {
		Slog.i(TAG, "HelloService::getVal+++++++++++++++");

		Slog.i(TAG, "HelloService::getVal---------------");

		return getVal_native();
	}
	
	private static native boolean init_native();
	private static native void setVal_native(int val);
	private static native int getVal_native();
};
