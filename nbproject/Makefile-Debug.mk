#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/270dbb15/AppWindow.o \
	${OBJECTDIR}/_ext/270dbb15/FaceRecognitionQueue.o \
	${OBJECTDIR}/_ext/270dbb15/FaceRecognizer.o \
	${OBJECTDIR}/_ext/270dbb15/ObjectDetector.o \
	${OBJECTDIR}/_ext/270dbb15/VideoArea.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs opencv` -lpthread  `pkg-config --libs gtkmm-3.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/facerecognition

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/facerecognition: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/facerecognition ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/270dbb15/AppWindow.o: /home/viniciusas/Programacao/FaceRecognition/AppWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/270dbb15
	${RM} "$@.d"
	$(COMPILE.cc) -g -s `pkg-config --cflags opencv` `pkg-config --cflags gtkmm-3.0` -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/270dbb15/AppWindow.o /home/viniciusas/Programacao/FaceRecognition/AppWindow.cpp

${OBJECTDIR}/_ext/270dbb15/FaceRecognitionQueue.o: /home/viniciusas/Programacao/FaceRecognition/FaceRecognitionQueue.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/270dbb15
	${RM} "$@.d"
	$(COMPILE.cc) -g -s `pkg-config --cflags opencv` `pkg-config --cflags gtkmm-3.0` -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/270dbb15/FaceRecognitionQueue.o /home/viniciusas/Programacao/FaceRecognition/FaceRecognitionQueue.cpp

${OBJECTDIR}/_ext/270dbb15/FaceRecognizer.o: /home/viniciusas/Programacao/FaceRecognition/FaceRecognizer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/270dbb15
	${RM} "$@.d"
	$(COMPILE.cc) -g -s `pkg-config --cflags opencv` `pkg-config --cflags gtkmm-3.0` -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/270dbb15/FaceRecognizer.o /home/viniciusas/Programacao/FaceRecognition/FaceRecognizer.cpp

${OBJECTDIR}/_ext/270dbb15/ObjectDetector.o: /home/viniciusas/Programacao/FaceRecognition/ObjectDetector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/270dbb15
	${RM} "$@.d"
	$(COMPILE.cc) -g -s `pkg-config --cflags opencv` `pkg-config --cflags gtkmm-3.0` -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/270dbb15/ObjectDetector.o /home/viniciusas/Programacao/FaceRecognition/ObjectDetector.cpp

${OBJECTDIR}/_ext/270dbb15/VideoArea.o: /home/viniciusas/Programacao/FaceRecognition/VideoArea.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/270dbb15
	${RM} "$@.d"
	$(COMPILE.cc) -g -s `pkg-config --cflags opencv` `pkg-config --cflags gtkmm-3.0` -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/270dbb15/VideoArea.o /home/viniciusas/Programacao/FaceRecognition/VideoArea.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s `pkg-config --cflags opencv` `pkg-config --cflags gtkmm-3.0` -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
