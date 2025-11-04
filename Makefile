.PHONY: all clean


export PLATFORM              = PLATFORM_WEB

export PROJECT_NAME          = raylib-concertina
export PROJECT_VERSION       = 1.0
export PROJECT_BUILD_PATH    = build
export PROJECT_SOURCE_FILES  = \
    $(wildcard src/*.cpp)

export RAYLIB_SRC_PATH       = ../lib/raylib/src
export RAYLIB_INCLUDE_PATH   = $(RAYLIB_SRC_PATH)
export RAYLIB_LIB_PATH       = $(RAYLIB_SRC_PATH)

export EMSDK_PATH			 = D:/Misc/emsdk
export BUILD_WEB_SHELL       = src/minshell.html
export BUILD_WEB_RESOURCES   = TRUE
export BUILD_WEB_RESOURCES_PATH = assets

export BUILD_MODE            = RELEASE

export INCLUDE_PATHS		+= -I../lib/TinySoundFont

include Makefile.Template

OBJS = $(patsubst %.cpp, %.o, $(PROJECT_SOURCE_FILES))

CFLAGS = -Wall -Wextra $(PROJECT_CUSTOM_FLAGS) -std=c++20
CC = g++
ifeq ($(PLATFORM),PLATFORM_WEB)
    CC = em++
	CFLAGS += -Os
else
	CFLAGS += -O2
endif

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_BUILD_PATH)/$(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)