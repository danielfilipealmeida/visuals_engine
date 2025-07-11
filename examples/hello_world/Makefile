# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
	OF_ROOT=$(realpath ../../..)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

all: release post

post:
	echo "copying files"
	mkdir -p bin/data
	cp ../../Resources/001.mov bin/data
	cp ../../Resources/002.mov bin/data
	cp ../../Resources/003.mov bin/data
	cp ../../Resources/004.mov bin/data
	cp ../../Resources/Base.vert bin/data
	cp ../../Resources/ContrastBrightnessSaturation.frag bin/data
	cp ../../Resources/FastBlur.frag bin/data
	cp ../../Resources/layerShader.frag bin/data
	cp ../../Resources/RGBTint.frag bin/data

