package com.epicgames.ue4;

import tv.ouya.examples.unreal.exampleproject.OBBDownloaderService;
import tv.ouya.examples.unreal.exampleproject.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

