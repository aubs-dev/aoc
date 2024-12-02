#ifndef GEM_LOGGER_H
#define GEM_LOGGER_H

// -------------------------------------------
// Constants
// -------------------------------------------

// -- ANSI Escape Sequences
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_STRIKE "\033[9m"

#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"

#define ANSI_BOLD_BLACK "\033[1m\033[30m"
#define ANSI_BOLD_RED "\033[1m\033[31m"
#define ANSI_BOLD_GREEN "\033[1m\033[32m"
#define ANSI_BOLD_YELLOW "\033[1m\033[33m"
#define ANSI_BOLD_BLUE "\033[1m\033[34m"
#define ANSI_BOLD_MAGENTA "\033[1m\033[35m"
#define ANSI_BOLD_CYAN "\033[1m\033[36m"
#define ANSI_BOLD_WHITE "\033[1m\033[37m"

#define ANSI_BG_BLACK "\033[40m"
#define ANSI_BG_RED "\033[41m"
#define ANSI_BG_GREEN "\033[42m"
#define ANSI_BG_YELLOW "\033[43m"
#define ANSI_BG_BLUE "\033[44m"
#define ANSI_BG_MAGENTA "\033[45m"
#define ANSI_BG_CYAN "\033[46m"
#define ANSI_BG_WHITE "\033[47m"

// -------------------------------------------
// Logging
// -------------------------------------------

// TODO: Add an optional flag to enable timestamps. E.g. [INFO][20:03:05] Some information message!
// TODO: All forms of logging don't support wide characters
// TODO: Add logging for vectors and matrices (maybe other types as well)

#if defined(GEM_DEBUG) && !defined(GEM_DISABLE_LOGGING)
    #define log_format(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
    #define log_bool(msg, b) fprintf(stderr, ANSI_WHITE "[BOOL] " msg ": %s" ANSI_RESET "\n", b ? "true" : "false")

    #define log_info(format, ...) fprintf(stderr, ANSI_WHITE "[INFO] " ANSI_RESET format "\n", ##__VA_ARGS__)
    #define log_warn(format, ...) fprintf(stderr, ANSI_YELLOW "[WARN] " ANSI_RESET format "\n", ##__VA_ARGS__)
    #define log_error(format, ...) fprintf(stderr, ANSI_RED "[ERROR] " ANSI_RESET format "\n", ##__VA_ARGS__)
#else
    #define log_format(format, ...) ((void)0)
    #define log_bool(msg, b) ((void)0)

    #define log_info(format, ...) ((void)0)
    #define log_warn(format, ...) ((void)0)
    #define log_error(format, ...) ((void)0)
#endif // GEM_RELEASE || !GEM_DISABLE_ASSERTIONS

// -------------------------------------------
// Assertions
// -------------------------------------------

#if !defined(GEM_DISABLE_ASSERTIONS)
    #define exec_debug_trap() __builtin_trap()

    #define gem_assert(expr)                                                     \
        if (!(expr)) {                                                           \
            fprintf(stderr, ANSI_BG_RED ANSI_BOLD_WHITE "[ASSERT]" ANSI_RESET    \
                            " in " ANSI_YELLOW "%s " ANSI_RESET                  \
                            "on " ANSI_GREEN "line %d" ANSI_RESET                \
                            " : " ANSI_BOLD_WHITE "gem_assert(%s)\n" ANSI_RESET, \
                           __FILE__, __LINE__, #expr);                           \
            exec_debug_trap();                                                   \
        }

    #define gem_assert_msg(expr, msg)                                                        \
        if (!(expr)) {                                                                       \
            fprintf(stderr, ANSI_BG_RED ANSI_BOLD_WHITE "[ASSERT]" ANSI_RESET                \
                            " in " ANSI_YELLOW "%s " ANSI_RESET                              \
                            "on " ANSI_GREEN "line %d" ANSI_RESET                            \
                            " : " ANSI_BOLD_WHITE "gem_assert_msg(%s, \"%s\")\n" ANSI_RESET, \
                            __FILE__, __LINE__, #expr, msg);                                 \
            exec_debug_trap();                                                               \
       }
#else
    #define exec_debug_trap() ((void)0)

    #define gem_assert(expr) ((void)0)
    #define gem_assert_msg(expr, msg) ((void)0)
#endif // !GEM_DISABLE_ASSERTIONS

#endif // GEM_LOGGER_H
