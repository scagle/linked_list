#include <stdio.h>
/* file: minunit.h */
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_assert_format(message, test, ...) do { if (!(test)) { size_t needed = snprintf(NULL, 0, message, __VA_ARGS__); char* buffer = malloc(needed); sprintf(buffer, message, __VA_ARGS__); return buffer; } } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
extern int tests_run;
