#ifndef __nuvieDefs_h__
#define __nuvieDefs_h__

#if _MSC_VER < 1300
#include "msvc/msvc_kludges.h"
#elif _MSC_VER >= 1300
#include "visualc7/vc7inc.h"
#endif

#define NUVIE_GAME_NONE  0
#define NUVIE_GAME_U6    1
#define NUVIE_GAME_MD    2
#define NUVIE_GAME_SE    4

#define NUVIE_CONFIG_NAME_U6 "ultima6"
#define NUVIE_CONFIG_NAME_MD "martian"
#define NUVIE_CONFIG_NAME_SE "savage"

/*
#ifndef BOOL
typedef unsigned char BOOL;
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif
*/

#ifndef WIN32
  #define U6PATH_DELIMITER '/'
#else
  #define U6PATH_DELIMITER '\\'
#endif

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

#ifdef MACOSX
#define NUVIE_RAND random
#else
#define NUVIE_RAND rand
#endif

#endif /* __nuvieDefs_h__ */