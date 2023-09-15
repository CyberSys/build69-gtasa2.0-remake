//
// Created by Weikton 15.09.23
//
#pragma once

#include <jni.h>
#include <string>

#define EXCEPTION_CHECK(env) \
	if ((env)->ExceptionCheck()) \ 
	{ \
		(env)->ExceptionDescribe(); \
		(env)->ExceptionClear(); \
		return; \
	}

class CJava
{
	jobject activity;

	jmethodID s_GetClipboardText;
	jmethodID s_CallLauncherActivity;
	jmethodID s_ShowInputLayout;
	jmethodID s_HideInputLayout;
	jmethodID s_ShowClientSettings;
	jmethodID s_SetUseFullScreen;

	jmethodID s_MakeDialog;

	jmethodID s_showHud;
                  jmethodID s_hideHud;
	jmethodID s_updateHudInfo;

                  // не нужно чинить все что работает
                  // скоро поймешь это на своем опыте
	jmethodID s_updateLoading;
	jmethodID s_showTabWindow;
	jmethodID s_setTabStat;

	jmethodID s_showSpeed;
                  jmethodID s_hideSpeed;
	jmethodID s_updateSpeedInfo;

	jmethodID s_showHudButtonG;
	jmethodID s_hideHudButtonG;

	jmethodID s_setPauseState;
public:
	JNIEnv* GetEnv();

	std::string GetClipboardString();
	void CallLauncherActivity(int type);
	void ShowInputLayout();
	void HideInputLayout();
	void ShowClientSettings();
	void SetUseFullScreen(int b);
	void UpdateHudInfo(int health, int armour, int hunger, int weaponid, int ammo, int ammoinclip, int money, int wanted);
	void ShowHud();
                  void HideHud();
                  void UpdateLoading(int status);
	void UpdateSpeedInfo(int speed, int fuel, int hp, int mileage, int engine, int light, int belt, int lock);
	void ShowSpeed();
                  void HideSpeed();
	void MakeDialog(int dialogId, int dialogTypeId, char* caption, char* content, char* leftBtnText, char* rightBtnText);
	void ShowTabWindow();
	void SetTabStat(int id, char* name, int score, int ping);
                  void ShowG();
                  void HideG();
	void SetPauseState(bool a1);

	CJava(JNIEnv* env, jobject activity);
	~CJava();
};

extern CJava* pJava;