#pragma once

#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __attribute__((visibility("default")))
#else
#define LIBRARY_API
#endif
