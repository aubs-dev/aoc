#ifndef GEM_FILESYSTEM_H
#define GEM_FILESYSTEM_H

// -------------------------------------------
// Data Types
// -------------------------------------------

typedef struct {
    const char* path;
    void* handle;
} file_t;

typedef enum {
    IO_FILE_READ        = 1 << 0,
    IO_FILE_WRITE       = 1 << 1,
    IO_FILE_APPEND      = 1 << 2,
    IO_FILE_READ_WRITE  = IO_FILE_READ | IO_FILE_WRITE,
    IO_FILE_READ_APPEND = IO_FILE_READ | IO_FILE_APPEND,
} file_mode_t;

typedef enum {
    IO_FILE_SET = 0, // set the offset relative to the start of file
    IO_FILE_CUR = 1, // get the current offset
    IO_FILE_END = 2, // set the offset relative to the end of file (works backwards)
} file_offset_t;

// -------------------------------------------
// Functions
// -------------------------------------------

// -- Files
// TODO: Better error handling for all file functions

// Utility
GAPI const char* file_get_extension(const char* filePath);
GAPI bool        file_has_extension(const char* filePath, const char* extension);

// Status
GAPI bool file_exists(const char* path);
GAPI i64  file_get_timestamp(const char* path);

// Operation
GAPI file_t file_open(const char* path, file_mode_t mode, bool binary);
GAPI bool   file_close(file_t* file);

GAPI i32  file_get_offset(file_t* file);
GAPI bool file_set_offset(file_t* file, i32 offset, file_offset_t offsetMethod);
GAPI bool file_set_offset_start(file_t* file);
GAPI bool file_set_offset_end(file_t* file);

GAPI i32 file_get_size(file_t* file);

GAPI bool file_read_line(file_t* file, char* buffer, i32 bufferSize, i32* outLineLength);
GAPI bool file_read(file_t* file, void* buffer, i32 bufferSize, i32* outBytesRead);

GAPI bool file_write_line(file_t* file, const char* text);
GAPI bool file_write(file_t* file, const void* buffer, i32 bufferSize, i32* outBytesWritten);

// Utility
GAPI bool file_move(const char* fromPath, const char* toPath);
GAPI bool file_remove(const char* path);

GAPI bool file_copy(const char* srcPath, const char* destPath);

// -- Directories
// TODO: Implement

// Status
// GAPI bool directory_exists(const char* path);
// GAPI bool directory_get_timestamp(const char* path);

// Utility
// GAPI bool directory_create(const char* path);
// GAPI bool directory_remove(const char* path);

#endif // GEM_FILESYSTEM_H
