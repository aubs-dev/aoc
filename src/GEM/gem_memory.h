#ifndef GEM_MEMORY_H
#define GEM_MEMORY_H

// -------------------------------------------
// Functions
// -------------------------------------------

GAPI void* memory_alloc(u64 size);
GAPI void  memory_free(void* block);

GAPI void* memory_zero(void* block, u64 size);
GAPI void* memory_copy(void* src, void* dest, u64 size);
GAPI void* memory_set(void* block, u64 size, i32 value);

#endif // GEM_MEMORY_H
