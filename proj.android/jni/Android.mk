LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/MainMenuScene.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/Item.cpp \
				   ../../Classes/SmallItem.cpp \
				   ../../Classes/FruitsPage.cpp \
				   ../../Classes/PageViewWIndicator.cpp \
				   ../../Classes/PageIndicator.cpp \
				   ../../Classes/PageIndicatorItem.cpp \
				   ../../Classes/Board.cpp \
				   ../../Classes/libs/pugixml/pugixml.cpp \
				   ../../Classes/helpers/wordsXMLHelper.cpp \
				   ../../Classes/helpers/arLettersUtils.cpp \
				   ../../Classes/helpers/lettersSoundUtils.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
