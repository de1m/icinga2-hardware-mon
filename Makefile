#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := app-template
COMPONENT_EMBED_TXTFILES := server_root_cert.pem

include $(IDF_PATH)/make/project.mk

