#include "s21_string.h"
#include "s21_sprintf.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__  // TARGET_OS_X

static char *ErrorNames[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full",
    "Unknown error: 107",
};
#endif
#ifdef __doc__
static char *ErrorNames[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error",
    "Unknown error 134",
};
#endif
#ifdef __linux__
static char *ErrorNames[] = {
    "No error information",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "I/O error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child process",
    "Resource temporarily unavailable",
    "Out of memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "No file descriptors available",
    "Not a tty",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Invalid seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Domain error",
    "Result not representable",
    "Resource deadlock would occur",
    "Filename too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Symbolic link loop",
    "No error information",
    "No message of desired type",
    "Identifier removed",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Device not a stream",
    "No data available",
    "Device timeout",
    "Out of streams resources",
    "No error information",
    "No error information",
    "No error information",
    "Link has been severed",
    "No error information",
    "No error information",
    "No error information",
    "Protocol error",
    "Multihop attempted",
    "No error information",
    "Bad message",
    "Value too large for data type",
    "No error information",
    "File descriptor in bad state",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Illegal byte sequence",
    "No error information",
    "No error information",
    "No error information",
    "Not a socket",
    "Destination address required",
    "Message too large",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address in use",
    "Address not available",
    "Network is down",
    "Network unreachable",
    "Connection reset by network",
    "Connection aborted",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is connected",
    "Socket not connected",
    "Cannot send after socket shutdown",
    "No error information",
    "Operation timed out",
    "Connection refused",
    "Host is down",
    "Host is unreachable",
    "Operation already in progress",
    "Operation in progress",
    "Stale file handle",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Remote I/O error",
    "Quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Previous owner died",
    "State not recoverable",
    "No error information",
};
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
    s21_size_t i = 0;
    for (i = 0; i < n; i++) {
        if (*((char *)str + i) ==  c)
        return (char *)str + i;
    }
    return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int flag;
    if (!n) {
        flag = 0;
      } else {
          while (--n && *(char*)str1 == *(char*)str2) {
               str1 = (char*)str1 + 1;
               str2 = (char*)str2 + 1;
               }
               flag = (*((unsigned char*)str1) - *((unsigned char*)str2));
     }
    return flag;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    s21_size_t i;
    for (i = 0; i < n; i++) ((char *)dest)[i] = ((char *)src)[i];

    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *pDest = (char *)dest;
    char *pSrc = (char *)src;
    if ((pDest > pSrc) && (pDest < pSrc + n)) {
        pSrc += n;
        pDest += n;
        while (n--) *--pDest = *--pSrc;
    } else {
        while (n--) *pDest++ = *pSrc++;
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        *((char *)str + i) = c;
    }
    return str;
}

char *s21_strcat(char *dest, const char *src) {
    s21_size_t len1 = s21_strlen(dest), len2 = s21_strlen(src);
    for (s21_size_t i = s21_strlen(dest); i < len1 + len2; i++) {
        dest[i] = src[i - len1];
    }
    dest[len1 + len2] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    char *result_adrr = S21_NULL;
    s21_size_t i;
    for (i = 0; i <= s21_strlen(str); i++) {
        if (*((char *)str + i) == c) {
            result_adrr = (char *)str + i;
            break;
        } else {
            result_adrr = 0;
        }
    }
    return (result_adrr != 0) ? result_adrr : (char *)S21_NULL;
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return (*str1 - *str2);
}

char *s21_strcpy(char *dest, const char *src) {
    char *r = dest;
    while ((*dest++ = *src++)) {
    }
    return r;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t len1 = s21_strlen(str1);
    s21_size_t len2 = s21_strlen(str2);
    s21_size_t i, j;
    for (i = 0; i < len1; i++)
        for (j = 0; j < len2; j++)
            if (str1[i] == str2[j]) return i;
    return i;
}

char *s21_strerror(int errnum) {
    char *out = (char *)calloc(50, sizeof(char));
    int err_p_max = 107;
#if __APPLE__ == 1
    err_p_max = 107;
#endif
#if __linux__ == 1
    err_p_max = 131;
#endif
    if (errnum < 0 || errnum > err_p_max) {
#if __APPLE__ == 1
        s21_sprintf(out, "Unknown error: %d", errnum);
#endif
#if __linux__ == 1
        s21_sprintf(out, "%s", ErrorNames[132]);
#endif
    } else {
#if __APPLE__ == 1
        s21_sprintf(out, "%s", ErrorNames[errnum]);
#endif
#if __linux__ == 1
        s21_sprintf(out, "%s", ErrorNames[errnum]);
#endif
    }
    out = (char *)realloc(out, s21_strlen(out));
    return (out);
}

s21_size_t s21_strlen(const char *str) {
    const char *tmp = str;
    while (*tmp != '\0') tmp++;
    return tmp - str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t dest_len = s21_strlen(dest);
    s21_size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    const char *end = str1 + n;
    int result = 0;
    for (; result == 0 && str1 != end && (*str1 || *str2); result = *(str1++) - *(str2++)) {
    }
    return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
    for (; i < n; i++) dest[i] = '\0';
    return dest;
}

char *s21_strrchr(const char *str, int c) {
    char *ch = S21_NULL;
    for (int i = s21_strlen(str); i >= 0; i--)
        if (str[i] == c) {
            ch = (char *)str + i;
            break;
        }
    return ch;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    s21_size_t i = 0;
    char *ch;
    while (*(str1 + i) && s21_strchr(str2, *(str1 + i)) == S21_NULL) i++;
    ch = *(str1 + i) ? (char *)(str1 + i) : S21_NULL;
    return (ch);
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t i, j;
    for (i = 0; str1[i] != '\0'; i++) {
        for (j = 0; str2[j] != str1[i]; j++) {
            if (str2[j] == '\0') return i;
        }
    }
    return i;
}

char *s21_strstr(const char *haystack, const char *needle) {
    int flag;
    char *ch = S21_NULL;
    if (needle[0] != '\0') {
        for (int i = 0; haystack[i] != '\0'; i++) {
            if (haystack[i] == needle[0]) flag = 0;
            for (int j = 0; needle[j] != '\0'; j++) {
                if (haystack[i + j] != needle[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                ch = (char *)haystack + i;
                break;
            }
        }
    } else {
        ch = (char *)haystack;
    }
    return ch;
}

char *s21_strtok(char *str1, const char *sep) {
    static unsigned char *last;
    unsigned char *str;
    const unsigned char *ctrl = (const unsigned char *)sep;
    unsigned char map[32];
    int count;
    for (count = 0; count < 32; count++) {
        map[count] = 0;
    }
    do {
        map[*ctrl >> 3] |= (1 << (*ctrl & 7));
    } while (*ctrl++);
    if (str1) {
        str = (unsigned char *)str1;
    } else {
        str = last;
    }
    while ((map[*str >> 3] & (1 << (*str & 7))) && *str) {
        str++;
    }
    str1 = (char *)str;
    for (; *str; str++) {
        if (map[*str >> 3] & (1 << (*str & 7))) {
            *str++ = '\0';
            break;
        }
    }
    last = str;
    char *ch = S21_NULL;
    if (str1 == (char *)str) {
        ch = S21_NULL;
    } else {
        ch = str1;
    }
    return ch;
}
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *new_string = S21_NULL;
    char *ch = S21_NULL;
    if (!src) ch = S21_NULL;
    if (src && str && s21_strlen(src) >= start_index) {
        new_string = (char *)calloc((s21_strlen(src) + s21_strlen(str)), sizeof(char));
        s21_strncpy(new_string, src, start_index);
        new_string[start_index] = '\0';
        s21_strcat(new_string, str);
        s21_strcat(new_string, src + start_index);
    }
    ch = new_string;
    return ch;
}
void *s21_to_lower(const char *str) {
    char *new_str = S21_NULL;
    if (str != S21_NULL) {
        new_str = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
        s21_strcpy(new_str, str);
        s21_size_t i = 0;
        for (; i < s21_strlen(new_str); i++) {
            if (new_str[i] >= 65 && new_str[i] <= 90) {
                new_str[i] = new_str[i] + 32;
            }
        }
    }
    return new_str;
}
void *s21_to_upper(const char *str) {
    char *new_str = S21_NULL;
    if (str != S21_NULL) {
        new_str = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
        s21_strcpy(new_str, str);
        s21_size_t i = 0;
        for (; i < s21_strlen(new_str); i++) {
            if (new_str[i] >= 97 && new_str[i] <= 122) {
                new_str[i] = new_str[i] - 32;
            }
        }
    }
    return new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
    int i;
    static char *str;
    void *ptr = S21_NULL;
    if ((src != S21_NULL) && (trim_chars != S21_NULL)) {
        str = malloc(s21_strlen(src));

        s21_strcpy(str, src);

        for (i = s21_strlen(str) - 1; i >= 0 && s21_strchr(trim_chars, str[i]) != S21_NULL; i--) {
            str[i] = '\0';
        }
        while (str[0] != '\0' && s21_strchr(trim_chars, str[0]) != S21_NULL) {
            s21_memmove(&str[0], &str[1], s21_strlen(str));
        }
        ptr = str;
    } else {
        ptr = S21_NULL;
    }
    return ptr;
}
