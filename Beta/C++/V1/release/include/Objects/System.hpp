
#ifndef OBJECTS_SYSTEM_HPP_
#	define OBJECTS_SYSTEM_HPP_

typedef char					int8;
typedef unsigned char			uint8;
typedef int8					byte;
typedef uint8					ubyte;
typedef short int	   			int16;
typedef unsigned short int 		uint16;
typedef int						int32;
typedef unsigned int			uint32;

#	ifndef _WIN32

#		define SYSTEM_WINDOW

#		ifndef _WIN64

#			define  SYSTEM_ENV					64

#		else

#			define  SYSTEM_ENV					32

#		endif /* !WINDOWS */

#	else

#		if __APPLE__

#			define SYSTEM_APPLE

#			include "TargetConditionals.h"

#			if TARGET_IPHONE_SIMULATOR

#				define SYSTEM_IPHONE_SIMULATOR

#			elif TARGET_OS_IPHONE

#				define SYSTEM_IPHONE

#			elif TARGET_OS_MAC

#				define SYSTEM_MAC

#			else

#				error "Unknown Apple platform !"

#			endif /* !APPLE */

#		else

#			define SYSTEM_LINUX

#		endif /* APPLE || LINUX */

#		if __x86_64__ || __ppc64__

#			define  SYSTEM_ENV					64

#		else

#			define  SYSTEM_ENV					32

#		endif /* !ENVIRONMENT */

#	endif /* !OS */

#	if SYSTEM_ENV == 64

typedef long int				int64;
typedef unsigned long int		uint64;
typedef uint64					wordsize;

#	else

typedef long long int  			int64;
typedef unsigned long long int	uint64;
typedef uint32					wordsize;

#	endif /* !WORD DEFINITION */

typedef wordsize				ptrsize;

#endif /* !OBJECTS_SYSTEM_HPP_ */
