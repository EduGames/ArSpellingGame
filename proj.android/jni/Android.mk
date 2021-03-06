LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/scenes/MainMenuScene.cpp \
				   ../../Classes/scenes/GameScene.cpp \
				   ../../Classes/objects/Item.cpp \
				   ../../Classes/objects/SmallItem.cpp \
				   ../../Classes/ui/FruitsPage.cpp \
				   ../../Classes/ui/PageViewWIndicator.cpp \
				   ../../Classes/objects/PageIndicator.cpp \
				   ../../Classes/objects/PageIndicatorItem.cpp \
				   ../../Classes/objects/Board.cpp \
				   ../../Classes/libs/pugixml/pugixml.cpp \
				   ../../Classes/helpers/wordsXMLHelper.cpp \
				   ../../Classes/helpers/arLettersUtils.cpp \
				   ../../Classes/helpers/soundUtils.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
