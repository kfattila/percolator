# Find the Pthreads library
# This module searches for the Pthreads library (including the
# pthreads-win32 port).
#
# This module defines these variables:
#
#  PTHREADS_FOUND       - True if the Pthreads library was found
#  PTHREADS_LIBRARY     - The location of the Pthreads library
#  PTHREADS_INCLUDE_DIR - The include directory of the Pthreads library
#  PTHREADS_DEFINITIONS - Preprocessor definitions to define (HAVE_PTHREAD_H is a fairly common one)
#
# This module responds to the PTHREADS_EXCEPTION_SCHEME
# variable on Win32 to allow the user to control the
# library linked against.  The Pthreads-win32 port
# provides the ability to link against a version of the
# library with exception handling.	IT IS NOT RECOMMENDED
# THAT YOU CHANGE PTHREADS_EXCEPTION_SCHEME TO ANYTHING OTHER THAN
# "C" because most POSIX thread implementations do not support stack
# unwinding.
#
#  PTHREADS_EXCEPTION_SCHEME
#	   C  = no exceptions (default)
#		  (NOTE: This is the default scheme on most POSIX thread
#		   implementations and what you should probably be using)
#	   CE = C++ Exception Handling
#	   SE = Structure Exception Handling (MSVC only)
#

#
# Define a default exception scheme to link against
# and validate user choice.
#
IF(NOT DEFINED PTHREADS_EXCEPTION_SCHEME)
	# Assign default if needed
	SET(PTHREADS_EXCEPTION_SCHEME "C")
ELSE(NOT DEFINED PTHREADS_EXCEPTION_SCHEME)
	# Validate
	IF(NOT PTHREADS_EXCEPTION_SCHEME STREQUAL "C" AND
	   NOT PTHREADS_EXCEPTION_SCHEME STREQUAL "CE" AND
	   NOT PTHREADS_EXCEPTION_SCHEME STREQUAL "SE")

	MESSAGE(FATAL_ERROR "See documentation for FindPthreads.cmake, only C, CE, and SE modes are allowed")

	ENDIF(NOT PTHREADS_EXCEPTION_SCHEME STREQUAL "C" AND
		  NOT PTHREADS_EXCEPTION_SCHEME STREQUAL "CE" AND
		  NOT PTHREADS_EXCEPTION_SCHEME STREQUAL "SE")

	 IF(NOT MSVC AND PTHREADS_EXCEPTION_SCHEME STREQUAL "SE")
		 MESSAGE(FATAL_ERROR "Structured Exception Handling is only allowed for MSVC")
	 ENDIF(NOT MSVC AND PTHREADS_EXCEPTION_SCHEME STREQUAL "SE")

ENDIF(NOT DEFINED PTHREADS_EXCEPTION_SCHEME)

#
# Find the header file
#
FIND_PATH(PTHREADS_INCLUDE_DIR
          NAMES pthread.h
	  HINTS
	  /usr/include
	  /usr/local/include
	  $ENV{PTHREAD_INCLUDE_PATH}
	  )

message(STATUS "${PTHREADS_INCLUDE_DIR}")
#
# Find the library
#
SET(names)
IF(MSVC)
	SET(names
			pthreadV${PTHREADS_EXCEPTION_SCHEME}2
			pthread
			libpthread.a libpthread.dll.a libpthread.la libpthreadGC2.a
	)
ELSEIF(MINGW)
	SET(names
			pthreadG${PTHREADS_EXCEPTION_SCHEME}2
			pthread
			libpthread.a libpthread.dll.a libpthread.la libpthreadGC2.a
	)
ELSE(MSVC) # Unix / Cygwin / Apple / Etc.
	SET(names pthread)
ENDIF(MSVC)
	
FIND_LIBRARY(PTHREADS_LIBRARY NAMES ${names}
	DOC "The Portable Threads Library"
	PATHS
	${CMAKE_SOURCE_DIR}/lib
	/usr/lib
	/usr/local/lib
	/lib
	/lib64
        /usr/lib64
        /usr/local/lib64
	$ENV{PTHREAD_LIBRARY_PATH}
	/usr/i686-pc-mingw32/sys-root/mingw/lib/
	/usr/i586-mingw32msvc/sys-root/mingw/lib/
	/usr/i586-mingw32msvc/lib/
	/usr/i686-pc-mingw32/lib/
	C:/MinGW/lib/
	/mingw/lib  )
message(STATUS "${PTHREADS_LIBRARY}")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pthreads DEFAULT_MSG
	PTHREADS_LIBRARY PTHREADS_INCLUDE_DIR)

IF(PTHREADS_INCLUDE_DIR AND PTHREADS_LIBRARY)
	SET(PTHREADS_DEFINITIONS -DHAVE_PTHREAD_H)
	SET(PTHREADS_INCLUDE_DIRS ${PTHREADS_INCLUDE_DIR})
	SET(PTHREADS_LIBRARIES	  ${PTHREADS_LIBRARY})
ENDIF(PTHREADS_INCLUDE_DIR AND PTHREADS_LIBRARY)

MARK_AS_ADVANCED(PTHREADS_INCLUDE_DIR)
MARK_AS_ADVANCED(PTHREADS_LIBRARY)