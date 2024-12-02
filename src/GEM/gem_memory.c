// -------------------------------------------
// Memory
// -------------------------------------------

GAPI void* memory_alloc(u64 size) {
    void* block = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    gem_assert_msg(block, "Failed to allocate memory!");
    return block;
}

GAPI void memory_free(void* block) {
    VirtualFree(block, 0, MEM_RELEASE);
}

GAPI void* memory_zero(void* block, u64 size) {
    return memset(block, 0, size);
}

GAPI void* memory_copy(void* src, void* dest, u64 size) {
    return memcpy(dest, src, size);
}

GAPI void* memory_set(void* block, u64 size, i32 value) {
    return memset(block, value, size);
}
