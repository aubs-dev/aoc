// -------------------------------------------
// Files
// -------------------------------------------

// Utility
GAPI const char* file_get_extension(const char* path) {
    const char* dot = strrchr(path, '.');
    return (dot || dot != path) ? dot : NULL;
}

GAPI bool file_has_extension(const char* filePath, const char* extension) {
    return strcmp(file_get_extension(filePath), extension) == 0;
}

// Status
GAPI bool file_exists(const char* path) {
    struct stat sb;
    return stat(path, &sb) == 0;
}

GAPI i64 file_get_timestamp(const char* path) {
    struct stat sb;
    stat(path, &sb);
    return sb.st_mtime;
}

// Operation
GAPI file_t file_open(const char* path, file_mode_t mode, bool binary) {
    file_t output = {0};
    output.path = path;

    const char* modeStr;
    switch (mode) {
        case IO_FILE_READ:
            modeStr = binary ? "rb" : "r";
            break;
        case IO_FILE_WRITE:
            modeStr = binary ? "wb" : "w";
            break;
        case IO_FILE_APPEND:
            modeStr = binary ? "ab" : "a";
            break;
        case IO_FILE_READ_WRITE:
            modeStr = binary ? "w+b" : "w+";
            break;
        case IO_FILE_READ_APPEND:
            modeStr = binary ? "a+b" : "a+";
            break;
        default:
            log_error("Invalid file mode: %i", mode);
            break;
    }

    output.handle = fopen(path, modeStr);
    if (!output.handle) log_error("Failed to open file: '%s'", path);
    return output;
}

GAPI bool file_close(file_t* file) {
    if (!file->handle) return false;

    fclose(file->handle);
    file->handle = NULL;

    return true;
}

GAPI i32 file_get_offset(file_t* file) {
    if (!file->handle) return -1;
    return ftell(file->handle);
}

GAPI bool file_set_offset(file_t* file, i32 offset, file_offset_t offsetMethod) {
    if (!file->handle) return false;
    i32 status = fseek(file->handle, offset, offsetMethod);
    return status == 0; // 0 upon success, nonzero value otherwise
}

GAPI bool file_set_offset_start(file_t* file) {
    if (!file->handle) return false;
    i32 status = fseek(file->handle, 0, SEEK_SET);
    return status == 0; // 0 upon success, nonzero value otherwise
}

GAPI bool file_set_offset_end(file_t* file) {
    if (!file->handle) return false;
    i32 status = fseek(file->handle, 0, SEEK_END);
    return status == 0; // 0 upon success, nonzero value otherwise
}

GAPI i32 file_get_size(file_t* file) {
    if (!file->handle) return 0;

    i32 curOffset = ftell(file->handle);
    fseek(file->handle, 0, SEEK_END);
    i32 size = ftell(file->handle); // can only return a maximum size of 2GB :/
    fseek(file->handle, curOffset, SEEK_SET);

    return size;
}

GAPI bool file_read_line(file_t* file, char* buffer, i32 bufferSize, i32* outLineLength) {
    if (file->handle && buffer && bufferSize > 0) {
        if (fgets(buffer, bufferSize, file->handle) != 0) {
            i32 lineLength = (i32)strlen(buffer);
            if (outLineLength != NULL) *outLineLength = lineLength;
            return true;
        }
    }

    return false;
}

GAPI bool file_read(file_t* file, void* buffer, i32 bufferSize, i32* outBytesRead) {
    if (file->handle && buffer && bufferSize > 0) {
        i32 bytesRead = (i32)fread(buffer, 1, bufferSize, file->handle);
        if (outBytesRead != NULL) *outBytesRead = bytesRead;
        return bytesRead == bufferSize;
    }

    return false;
}

GAPI bool file_write_line(file_t* file, const char* text) {
    if (!file->handle) return false;

    // Write the data on a new line
    i32 curOffset = ftell(file->handle);
    
    fseek(file->handle, 0, SEEK_END);
    if (ftell(file->handle) > 0) fputc('\n', file->handle);
    fputs(text, file->handle);

    fseek(file->handle, curOffset, SEEK_SET);

    // Flush the stream to immediately write the data.
    return fflush(file->handle) == 0;
}

GAPI bool file_write(file_t* file, const void* buffer, i32 bufferSize, i32* outBytesWritten) {
    if (file->handle && buffer && bufferSize > 0) {
        i32 bytesWritten = (i32)fwrite(buffer, 1, bufferSize, file->handle);
        if (outBytesWritten != NULL) *outBytesWritten = bytesWritten;

        if (bytesWritten != bufferSize) return false;
        return fflush(file->handle) == 0;
    }

    return false;
}

// Utility
GAPI bool file_move(const char* fromPath, const char* toPath) {
    i32 status = 0;

    // Remove the "to" file incase it exists
    status = remove(toPath);
    if (status != 0 && errno != ENOENT) {
        log_error("Failed to remove file before moving: '%s'", toPath);
        return false;
    }

    // Move the file
    status = rename(fromPath, toPath);
    if (status != 0) {
        if (errno == EEXIST) {
            log_warn("Tried to move file into another: '%s' to '%s'", fromPath, toPath);
            return false;
        } else {
            log_error("Failed to move file: '%s' to '%s'", fromPath, toPath);
            return false;
        }
    }

    return true;
}

GAPI bool file_remove(const char* path) {
    i32 status = remove(path);
    if (status != 0) {
        log_error("Failed to remove file: '%s'", path);
        return false;
    }

    return true;
}

GAPI bool file_copy(const char* srcPath, const char* destPath) {
    // Check if source exists
    struct stat statSrc;
    if (stat(srcPath, &statSrc) != 0) {
        log_error("Source file does not exist: %s", srcPath);
        return false;
    }

    // Copy the source file into memory
    file_t srcFile = file_open(srcPath, IO_FILE_READ, true);
    i32 srcSize = file_get_size(&srcFile);
    if (srcSize == 0) return false;

    char* srcData = memory_alloc(srcSize);
    file_read(&srcFile, srcData, srcSize, NULL);
    file_close(&srcFile);

    // Write data into the destination file
    file_t destFile = file_open(destPath, IO_FILE_WRITE, true);
    file_write(&destFile, srcData, srcSize, NULL);
    file_close(&destFile);

    // Free data
    memory_free(srcData);

    return true;
}
