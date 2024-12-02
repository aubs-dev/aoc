#ifndef GEM_GEM_H
#define GEM_GEM_H

// -------------------------------------------
// System
// -------------------------------------------

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

// -------------------------------------------
// External
// -------------------------------------------

#ifdef GEM_IMPLEMENTATION
// -- STB
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#define STBI_NO_THREAD_LOCALS
#include "../external/stb_image.h"
#include "../external/stb_image_write.h"

#include "../external/dirent.h"

// -------------------------------------------
// GEM
// -------------------------------------------

#include "defines.h"
#include "gem_math.h"
#include "logger.h"

#include "gem_memory.h"
#include "filesystem.h"

#endif // GEM_GEM_H

// -------------------------------------------
// Source
// -------------------------------------------

#ifdef GEM_IMPLEMENTATION

#ifndef GEM_GEM_C
#define GEM_GEM_C

// -- GEM
#include "gem_memory.c"
#include "filesystem.c"

#endif // GEM_GEM_C

#endif // GEM_IMPLEMENTATION
