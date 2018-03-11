/**
 * Originally from
 * http://www.jera.com/techinfo/jtns/jtn002.html
 */
 #define mu_assert(message, test) \
 do { \
     if (!(test)) \
        return message; \
 } while (0)

 #define mu_run_test(test) \
 do { \
     string message = test(); \
     tests_run++; \
     if (!message.empty()) \
        return message; \
 } while (0)
 extern int tests_run;
