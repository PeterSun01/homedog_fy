#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#
PROJECT_NAME := HOMEDOG_V0.0.0

EXTRA_COMPONENT_DIRS := $(ESP_ALIYUN_PATH)

SDKCONFIG_DEFAULTS := sdkconfig_$(chip).defaults

include $(IDF_PATH)/make/project.mk