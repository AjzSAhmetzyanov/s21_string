#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

int s21_sprintf(char *str_in, const char *format, ...);
struct token {
    char flag1;  // плюс  пробел
    char flag3;  // минус
    int width;
    int toch;
    char lenght;
};

int int_len(long long int n) {
    int len = 0;
    while (n != 0) {
        len++;
        n /= 10;
    }
    return len;
}
int unsign_int_len(unsigned long long int n) {
    int len = 0;
    while (n != 0) {
        len++;
        n /= 10;
    }
    return len;
}
char *int_to_buf(char *buf, int is_int, long int n, char flag, char flag3, int width, int toch) {
    int len = int_len(n);

    int ftoch = 0;  // длина числа
    if ((toch != -1 || toch == 0) && is_int == 0) {
        ftoch = toch + 1;
    }
    int tr_len = len;
    if (toch != -1 && toch > len && is_int == 1)  // если задана точность, то длина числа будет равна точности
        len = toch;
    int full_len = len;
    int i = 0;
    int j = 0;
    int flag_null = 1;
    if (n == 0) {
        flag_null = 0;
    }
    if ((flag == ' ' && n >= 0) || (flag == '+' && n > 0) || n < 0)  // если заданы флаги пробел и + или число отрицательное, то
        // фактическая длина больше на единицу, так как нужно печатать
        // плюс, минус или пробел
        full_len++;
    if (flag3 == -1 && width != -1) {  // если задана ширина и нет флага 0 или -,
        // то печатаем сначала пробелы, затем число
        for (; j < width - full_len - ftoch; ++j) {
            *(buf + j) = ' ';
        }
    }
    if (flag == ' ' && n >= 0) {  // если флаг пробел, то перед числом ставим пробел
        buf += j;
        *(buf++) = ' ';
        buf -= j;
    }
    if (flag == '+' && n >= 0) {  // если если флаг +, то перед положительным числом ставим плюс
        buf += j;
        *(buf++) = '+';
        buf -= j;
       // full_len++;
    }
    if (n < 0) {  // если число отрицательно, то перед ним печатаем минус
        buf += j;
        *(buf++) = '-';
        buf -= j;
        n = (-1) * n;
    }
    if (n == 0) {  // обработка 0
        buf += j;
        *(buf++) = '0';
        buf -= j;
      //  full_len++;
    }
    if (n + 2 == LONG_MIN + 2) {
        n += 2;
        n = (-1) * n;
        *(buf + j + len - i - 1) = '8';
        int flag1 = 1;
        while (n != 0) {
            if (flag1 == 1) {
                flag1 = 0;
                n /= 10;
                i++;
                continue;
            }
            *(buf + j + len - i - 1) = (n % 10) | '0';
            n /= 10;
            i++;
        }

    } else {
        while (n != 0) {  // непосредственно вывод самого числа
            *(buf + j + len - i - 1) = (n % 10) | '0';
            n /= 10;
            i++;
        }
    }
    if (is_int == 1) {
        for (int h = 0; h < toch - tr_len; h++) {  // а это, если задана точность, вывод дополнительных нулей
            *(buf + j + len - i - 1) = '0';
            i++;
        }
    }

    if (flag3 == '-' && width != -1 && is_int == 1) {  // если флаг - и задана ширина, то после числа пробелы печатаем
        if (flag_null == 0 && flag == '+') {
            for (; j < width - full_len - ftoch - 2; ++j) { 
                *(buf + len - 1 + j + 1) = ' ';
            }
        }
        if (flag_null == 0 && flag != '+') {
            for (; j < width - full_len - ftoch - 1; ++j) { 
                *(buf + len - 1 + j + 1) = ' ';
            }
        }
        if (flag_null == 1) {
            for (; j < width - full_len - ftoch; ++j) { 
                *(buf + len - 1 + j + 1) = ' ';
            }
        }
    }

    return (buf);
}

char *unsign_int_to_buf(char *buf, int is_int, unsigned long int n, char flag, char flag3, int width, int toch) {
    int len = unsign_int_len(n);

    int ftoch = 0;  // длина числа
    if ((toch != -1 || toch == 0) && is_int == 0) {
        ftoch = toch + 1;
    }
    int tr_len = len;
    if (toch != -1 && toch > len && is_int == 1)  // если задана точность, то длина числа будет равна точности
        len = toch;
    int full_len = len;
    int i = 0;
    int j = 0;
    int flag_null = 0;
    // if (n == 0) {
    //     flag_null = 1;
    // } else {
    //     flag_null = 0;
    // }
    if ((flag == ' ' && n >= 0) || (flag == '+' && n > 0) || n < 0)  // если заданы флаги пробел и + или число отрицательное, то
        // фактическая длина больше на единицу, так как нужно печатать
        // плюс, минус или пробел
        full_len++;
    if (flag3 == -1 && width != -1) {  // если задана ширина и нет флага 0 или -,
        // то печатаем сначала пробелы, затем число
        if (n == 0) width--;
        for (; j < width - full_len - ftoch; ++j) {
            *(buf + j) = ' ';
        }
    }
    if (flag == ' ' && n >= 0) {  // если флаг пробел, то перед числом ставим пробел
        buf += j;
        *(buf++) = ' ';
        buf -= j;
    }
    if (flag == '+' && n > 0) {  // если если флаг +, то перед положительным числом ставим плюс
        buf += j;
        *(buf++) = '+';
        buf -= j;
    }
    if (n < 0) {  // если число отрицательно, то перед ним печатаем минус
        buf += j;
        *(buf++) = '-';
        buf -= j;
        n = (-1) * n;
    }
    if (n == 0) {  // обработка 0
        buf += j;
        *(buf++) = '0';
        buf -= j;
    }
    if (n + 2 == LONG_MIN + 2) {
        n += 2;
        n = (-1) * n;
        *(buf + j + len - i - 1) = '8';
        int flag1 = 1;
        while (n != 0) {
            if (flag1 == 1) {
                flag1 = 0;
                n /= 10;
                i++;
                continue;
            }
            *(buf + j + len - i - 1) = (n % 10) | '0';
            n /= 10;
            i++;
        }

    } else {
        while (n != 0) {  // непосредственно вывод самого числа
            *(buf + j + len - i - 1) = (n % 10) | '0';
            n /= 10;
            i++;
        }
    }
    if (is_int == 1) {
        for (int h = 0; h < toch - tr_len; h++) {  // а это, если задана точность, вывод дополнительных нулей
            *(buf + j + len - i - 1) = '0';
            i++;
        }
    }

    if (flag3 == '-' && width != -1 && is_int == 1) {  // если флаг - и задана ширина, то после числа пробелы печатаем
        for (; j < width - full_len - ftoch; ++j) 
            *(buf + len - 1 + j + 1) = ' ';
    }

    return (buf);
}

char *dub_to_str(char *buf, long double n, char flag1, char flag2, int width, int toch) {
    int len = int_len((int)n);
    if ((flag1 == ' ' && n >= 0) || (flag1 == '+' && n > 0) ||
        n < 0)  // если заданы флаги пробел и + или число отрицательное, то фактическая длина больше на
        // единицу, так как нужно печатать плюс, минус или пробел
        len++;
    if (toch == -1)  // т к точность по умолчанию
        toch = 6;
    if (flag2 != '-') {
        for (int i = 0; i < width - len - toch; ++i) {
            s21_strcat(buf, " ");
        }
    }

    int_to_buf(buf, 0, (int)n, flag1, flag2, width, toch);

    if (toch != 0) s21_strcat(buf, ".");
    if (n < 0) {
        n = n * (-1);
    }
    n = n - (long int)n;
    int a = s21_strlen(buf);
    //    for (int i = 0; i < toch; i++) {
    //        n *= 10;
    //        buf[a] = (int)n + '0';
    //        n = n - (int)n;
    //        ++a;
    //    }
    for (int i = 0; i < toch; i++) {
        n *= 10;
        if ((n < 1) && (n > 0.9) && toch != 6) {
            n = lround(n);
        }
        if ((width - toch - len > 0) && (len - toch == 1)) {
            n += 0.1;
        }
        buf[a] = (int)n + '0';
        n = n - (int)n;
        ++a;
    }
    if (flag2 == '-') {
        for (int i = 0; i < width - (len + toch + 1); i++) {
            buf[s21_strlen(buf)] = ' ';
        }
    }
    return buf;
}

// ********************************************************************************************************************//
// ********************************************************************************************************************//
int s21_sprintf(char *str_in, const char *format, ...) {
    va_list arg;
    va_start(arg, format);  // Устанавливаю указатель на первый неизвестный аргумент

    struct token tok;
    tok.flag1 = -1;
    tok.flag3 = -1;
    tok.width = -1;
    tok.toch = -1;
    tok.lenght = -1;

    int flag;
    int null_flag;
    int str_len = 0;
    char *str;
    str = calloc(str_len, str_len * sizeof(char));

    // \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//
    for (int form = 0; form < (int)s21_strlen(format); form++) {
        flag = 0;
        null_flag = 0;
        tok.flag1 = -1;
        tok.flag3 = -1;
        tok.width = -1;
        tok.toch = -1;
        tok.lenght = -1;
        if (format[form] != '%') {
            str = (char *)realloc(str, (str_len + 1) * sizeof(char));
            str[str_len] = format[form];
            str_len++;
            continue;
        }  // ................................................OK

        ++form;
        int read = 1;
        while (read) {
            if (format[form] == '-' || format[form] == '+' || format[form] == ' ') {
                if (format[form] == '+' || format[form] == ' ') {
                    if (format[form] == '+')
                        tok.flag1 = format[form];
                    else
                        tok.flag1 = format[form];
                }
                if (format[form] == '-') tok.flag3 = format[form];
                ++form;
            } else {
                read = 0;
            }
        }  //  ............................................................OK

        char tmp[256] = "\0";                            // add dynamic allocate!!
        if (format[form] >= 48 && format[form] <= 57) {  // Ширина
            for (int i = 0; format[form] >= 48 && format[form] <= 57; form++, i++) {
                tmp[i] = format[form];
            }
            tok.width = atoi(tmp);
            for (int i = 0; i < 255; i++) {
                tmp[i] = '\0';
            }
            // ++form;  // Перенос.
        }  // OK

        if (format[form] == '*') {
            tok.width = va_arg(arg, int);
            ++form;
        }

        char tmp2[256] = "\0";
        if (format[form] == '.' && format[form + 1] >= 48 && format[form + 1] <= 57) {  // Точность
            ++form;
            for (int i = 0; format[form] >= 48 && format[form] <= 57; form++, i++) {
                tmp2[i] = format[form];
            }
            tok.toch = atoi(tmp2);
            flag = 1;
            ++form;
            for (int i = 0; i < 256; i++) {
                tmp2[i] = '\0';
            }
        }

        if (format[form] == '.' && format[form + 1] == '*') {
            tok.toch = va_arg(arg, int);
            form += 2;
        }

        if (format[form] == '.' && (format[form + 1] < 48 || format[form + 1] > 57) && format[form + 1] != '*') {
            ++form;
            tok.toch = 0;
            null_flag = 1;
        }

        //        if (format[form] == '.' && (format[form + 1] == 'l' || format[form + 1] == 'h') && format[form + 1] != '*') {
        //            if (format[form + 2] == 'd') {
        //                tok.toch = 0;
        //                ++form;
        //            }
        //        }
        //
        //        if (format[form] == '.' && (format[form + 1] == 'd'))

        if (format[form] == 'h' || format[form] == 'l') {
            tok.lenght = format[form];
            ++form;
        }
        // ***//***//***//***//***//***//***//***//***//***//***//***//***//***//
        if (flag == 1) {
            --form;
        }
        //        if (null_flag == 1) {
        //            continue;
        //        }
        // ***//***//***//***//***//***//***//***//***//***//***//***//***//***//
        // ***//***//***//***//***//***//***//***//***//***//***//***//***//***//
        // ***//***//***//***//***//***//***//***//***//***//***//***//***//***//
        switch (format[form]) {  // Спецификаторы
            case 'c': {
                char new_arg;
                new_arg = (char)va_arg(arg, int);
                if (tok.flag3 != '-' && tok.width != -1) {
                    for (int i = 0; i < tok.width - 1; i++) {  // прописать расширение памяти по str/
                        str = realloc(str, (str_len + 1) * sizeof(char));
                        str[str_len] = ' ';
                        str_len++;
                    }
                    str = realloc(str, (str_len + 1) * sizeof(char));
                }
                str = realloc(str, (str_len + 1) * sizeof(char));
                str[str_len] = new_arg;
                str_len++;
                if (tok.flag3 == '-' && tok.width != -1) {
                    for (int i = 0; i < tok.width - 1; i++) {
                        str = realloc(str, (str_len + 1) * sizeof(char));
                        str[str_len] = ' ';
                        str_len++;
                    }
                }
                break;
            }

            case 'd':  //  Обработка int
            {
                long int par;
                char *buf;
                if (tok.lenght == 'l') {
                    par = (long int)va_arg(arg, long int);
                } else {
                    par = (long int)va_arg(arg, int);
                }
                if (tok.width > (tok.toch + int_len((long long int)par) + 2))
                    buf = calloc(tok.width + 1, sizeof(int));
                else
                    buf = calloc(((size_t)tok.toch + int_len((long long int)par) + 2), sizeof(int));
                int_to_buf(buf, 1, par, tok.flag1, tok.flag3, tok.width, tok.toch);
                str_len += (int)s21_strlen(buf);
                str = realloc(str, (str_len + 1) * sizeof(char));
                str[str_len - s21_strlen(buf)] = '\0';
                s21_strcat(str, buf);
                free(buf);
                //              if (format[])
                break;
            }

            case 'i':  // Обработка десятичного знкового int
            {
                str[str_len] = '\0';
                long int par;
                char *buf;
                if (tok.lenght == 'l') {
                    par = (long int)va_arg(arg, long int);
                } else {
                    par = (long int)va_arg(arg, int);
                }
                if (tok.width > (tok.toch + int_len((long long int)par) + 2))
                    buf = calloc(tok.width, sizeof(int));
                else
                    buf = calloc((tok.toch + int_len((long long int)par) + 2), (tok.toch + int_len((long long int)par) + 2) * sizeof(int));
                int_to_buf(buf, 1, par, tok.flag1, tok.flag3, tok.width, tok.toch);
                str_len += s21_strlen(buf);
                str = realloc(str, (str_len + 1) * sizeof(char));
                str[str_len - s21_strlen(buf)] = '\0';
                s21_strcat(str, buf);
                free(buf);
                break;
            }

            case 'u':  // Беззнаковое десятичное целое число unsigned int
            {
                unsigned long int par = 0;
                char *buf;
                if (tok.lenght == 'l')
                    par = (unsigned long int)va_arg(arg, unsigned long int);
                else if (tok.lenght == 'h')
                    par = (unsigned short int)va_arg(arg, unsigned int);
                else
                    par = (unsigned long int)va_arg(arg, unsigned int);
                if (tok.width > (tok.toch + unsign_int_len(par) + 2))
                    buf = calloc(tok.width + 1, sizeof(char));
                else
                    buf = calloc((tok.toch + unsign_int_len(par) + 2), sizeof(char));
                unsign_int_to_buf(buf, 1, par, tok.flag1, tok.flag3, tok.width, tok.toch);
                str_len += (int)s21_strlen(buf);
                str = realloc(str, (str_len + 1) * sizeof(char));
                str[str_len - s21_strlen(buf)] = '\0';
                s21_strcat(str, buf);
                free(buf);
                break;
            }

            case 'f':  // добавить Динамику
            {
                double par;
                par = va_arg(arg, double);
                char *buf;

                if (tok.flag1 == '+' || par < 0) {
                    if (tok.width > (tok.toch + int_len((int)par) + 2))
                        buf = calloc(tok.width + 1, sizeof(char));
                    else
                        buf = calloc((tok.toch + int_len((int)par) + 2), sizeof(char));
                } else {
                    if (tok.width > (tok.toch + int_len((int)par) + 1)) {
                        buf = calloc(tok.width + 1, sizeof(char));
                    } else {
                        if (tok.toch == -1)
                            buf = calloc(int_len((int)par) + 9, sizeof(char));
                        else
                            buf = calloc((tok.toch + int_len((int)par) + 4), sizeof(char));
                    }
                }

                dub_to_str(buf, par, tok.flag1, tok.flag3, tok.width, tok.toch);
                str_len += (int)s21_strlen(buf);
                str = realloc(str, (str_len + 1) * sizeof(char));
                str[str_len - s21_strlen(buf)] = '\0';
                s21_strcat(str, buf);
                free(buf);
                break;
            }

            case 's': {
                char *arr = (char *)malloc(sizeof(char));
                int k = 0;
                for (char *par = va_arg(arg, char *); *par; par++) {
                    if (tok.toch != 0) {
                        if (tok.toch <= k && tok.toch > 0) continue;
                        k++;
                        arr = realloc(arr, (k + 1) * sizeof(char));
                        *(arr + k - 1) = *par;
                        str_len++;
                    } else {
                        arr = realloc(arr, (k + 1) * sizeof(char));
                        *(arr + k - 1) = '\0';
                    }
                }
                *(arr + k) = '\0';
                int l = s21_strlen(arr);
                if (tok.width > l) {
                    str = realloc(str, (str_len + tok.width + 1) * sizeof(char));
                    str[str_len - l] = '\0';
                } else {
                    str = realloc(str, (str_len + l + 1) * sizeof(char));
                    str[str_len - l] = '\0';
                }
                if (tok.flag3 != '-') {
                    for (int i = 0; i < tok.width - l; ++i) {
                        s21_strcat(str, " ");
                        str_len++;
                    }
                }
                s21_strcat(str, arr);
                free(arr);
                if (tok.flag3 == '-') {
                    for (int i = 0; i < tok.width - l; ++i) {
                        s21_strcat(str, " ");
                        str_len++;
                    }
                }
                break;
            }

            case '%': {
                if (tok.width != -1) {
                    for (int i = 0; i < tok.width - 1; i++) {
                        str = realloc(str, (str_len + 1) * sizeof(char));
                        str[str_len] = '\0';
                        str[i] = ' ';
                        str_len++;
                    }
                }
                str = realloc(str, (str_len + 2) * sizeof(char));
                str[str_len] = '\0';
                s21_strcat(str, "%");
                str_len++;
                break;
            }
            default: {
                str = realloc(str, (str_len + 2) * sizeof(char));
                str[str_len + 1] = '\0';
                str[s21_strlen(str)] = format[form];
                str_len++;
                break;
            }
        }
    }
    va_end(arg);
    str = realloc(str, (str_len + 1) * sizeof(char));
    str[str_len] = '\0';
    //    printf("\n");
    s21_strcpy(str_in, str);
    free(str);
    return str_len;
}

//     int main() {
    
// // //      char data[100];
// // //      char data1[100];
//     //int a, b;
//     char data[100];
//     char data1[100];
//     s21_memset(data, '\0', 100);
//     s21_memset(data1, '\0', 100);
//     int c = s21_sprintf(data,   " %+-5d %+-5i", -7, 0);
//     int d = sprintf(data1,  " %+-5d %+-5i", -7, 0);
// //     char data[100];
// //     char data1[100];
// //     s21_memset(data, '\0', 100);
// //     s21_memset(data1, '\0', 100);

// //     a = s21_sprintf(data, "|%20.2f| ", 324.345);
// //     b = sprintf(data1, "|%20.2f| ", 324.345);
// //     // s21_memset(data, '\0', 100);
// //     // s21_memset(data1, '\0', 100);

// //     // a = s21_sprintf(data, "|%20.2f| ", 324.345);
// //     // b = sprintf(data1, "|%20.2f| ", 324.345);
// //     s21_memset(data, '\0', 200);
// //     s21_memset(data1, '\0', 200);
// //     a = s21_sprintf(data, "%lu", 100000000000000000);
// //     b = sprintf(data1, "%lu", 100000000000000000);
//     printf("%d %s\n", c, data);
//     printf("%d %s\n", d, data1);
//     return 0;
//  }
//     char data[200];
//     char data1[200];
//     int a, b;
//     s21_memset(data, '\0', 200);
//     s21_memset(data1, '\0', 200);
//     short int i = -30000;
//     a = s21_sprintf(data, "%hu", i);
//     b = sprintf(data1, "%hu", i);
//      printf("%d %s\n", a, data);
//      printf("%d %s\n", b, data1);
//     return 0;
// }
//     char str[400] = "\0";
//     char str2[400] = "\0";
//     int a = 0, b = 0;
//     char c[255] = {}, d[255] = {}, x1 = 't';
//     int n = 2100, n1 = 0, n2 = -21;
//     short sh = 123, sh1 = -123;
//     float f = 21.21, f1 = -21.21;
//     long int lg = 12345678912345, lg1 = -12345678912345;

//     //*******************************************************************************************//
//     // INT TEST //

//     // a = s21_sprintf(str, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX,  //  По
//     //                 SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
//     // b = sprintf(str2, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN, USHRT_MAX, LONG_MAX,
//     //             LONG_MIN);
// //    a = s21_sprintf(str, "%.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d", 42, 21, 10, n, n2, -21, x1, 21, -42);
// //    b = sprintf(str2, "%.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d", 42, 21, 10, n, n2, -21, x1, 21, -42);
//     //******************************************************************************************//
//     // CHAR* TEST //

//     // a = s21_sprintf(str, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello",  // Починил
//     //                 "hello", "hello", "hello", "hello", "hello");
//     // b = sprintf(str2, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello", "hello", "hello", "hello", "hello", "hello");
// //     a = s21_sprintf(str, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello1", "hello2", "hello3", "hello4", "5hello5", "6hello6",
// "7hello7");
// //     b = sprintf(str2, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello1", "hello2", "hello3", "hello4", "5hello5", "6hello6", "7hello7");

// //    //******************************************************************************************//
//      a = s21_sprintf(str, "% 10f % 10f %f %.0f %.0f %.0f %.0f %f %10f", f, f1, 21., 21.21, 0.0, 21.21, 21.,
//                     0.0, 21.21);
//      b = sprintf(str2, "% 10f % 10f %f %.0f %.0f %.0f %.0f %f %10f", f, f1, 21., 21.21, 0.0, 21.21, 21.,
//      0.0, 21.21);
// //     a = s21_sprintf(str, "%lu", 18446744073709551615); // вылезает ошибка преобразованрия или что-то типо того
// //     b = sprintf(str2, "%lu", 18446744073709551615);
// //     a = s21_sprintf(str, "%*.*d %d % f %+-*d %% %*.*s %.*i %*c %-*lu\n", 9, 6, 2888, -286, 4.0, 6, 100, 8, 3, "Hello", 7, 45674, 8,
// 'Q',
// //     7,
// //                     5555555555);
// //     b = sprintf(str2, "%*.*d %d % f %+-*d %% %*.*s %.*i %*c %-*lu\n", 9, 6, 2888, -286, 4.0, 6, 100, 8, 3, "Hello", 7, 45674, 8, 'Q',
// 7,
// //                 5555555555);
//     // a = s21_sprintf(str, "%c %10c %-10c", '!', 'a', 'b');
//     // b = sprintf(str2, "%c %10c %-10c", '!', 'a', 'b');
// //     a = s21_sprintf(str, "%u %lu", UINT_MAX, ULONG_MAX);
// //     b = sprintf(str2, "%u %lu", UINT_MAX, ULONG_MAX);
// //    a = s21_sprintf(str, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
// //                    21.21, -21.21, 42.42, -42.42, f, f1);
// //    b = sprintf(str2, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
// //                21.21, -21.21, 42.42, -42.42, f, f1);

//     printf("|%s|\n%d\n", str, a);
//     printf("ORIGIN\n|%s|\n%d", str2, b);
//     return 0;
// }
