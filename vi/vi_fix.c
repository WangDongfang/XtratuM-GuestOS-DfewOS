/****************************************Copyright (c)*****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info----------------------------------------------------------------------------------
** File name:               vi_fix.c
** Last modified Date:      2011-6-1 13:47:06
** Last Version:            1.0.0
** Descriptions:            This file implement some funtions that VxWorks is pressed for.
**
**---------------------------------------------------------------------------------------------------------
** Created by:              WangDongfang
** Last modified Date:      2011-6-1 13:47:06
** Version:                 1.0.0
** Descriptions:            This file implement some funtions that VxWorks is pressed for.
**
**********************************************************************************************************/

#include "vi_fix.h"

/*********************************************************************************************************
** 函数名称: get_terminal_width_height
** 功能描述: 获得终端窗口的大小
** 输　入  : fd            终端
**           width         宽度
**           height        高度
** 输　出  : 0: OK
** 全局变量: 
** 调用模块: 
*********************************************************************************************************/
int  get_terminal_width_height (const int  fd, int  *width, int  *height)
{
    if (width) {
        *width = __VI_TERMINAL_WIDTH;
    }
    if (height) {
        *height = __VI_TERMINAL_HEIGHT;
    }
    
    return  (0);
}
/*********************************************************************************************************
** 函数名称: last_char_is
** 功能描述: 判断指定字符是否是字符串的最后一个字符
** 输　入  : s             字符串
**           c             最后一个字符
** 输　出  : 如果与给定相同返回指针, 如果不同返回 NULL
** 全局变量: 
** 调用模块: 
*********************************************************************************************************/
char *last_char_is (const char *s, int c)
{
    if (s && *s) {
        size_t sz = lib_strlen(s) - 1;
        s += sz;
        if ((unsigned char)*s == c) {
            return  (char*)s;
        }
    }
    return  NULL;
}
/*********************************************************************************************************
** 函数名称: lib_xzalloc
** 功能描述: 内存分配(清零)
** 输　入  : s             大小
** 输　出  : 开辟成功返回内存地址, 否则直接退出线程.
** 全局变量: 
** 调用模块: 
*********************************************************************************************************/
void  *lib_xzalloc (size_t s)
{
    return lib_memset(lib_xmalloc(s), 0, s);
}
/*********************************************************************************************************
** 函数名称: full_write
** 功能描述: 将所有缓冲区内的数据写入文件
** 输　入  : fd        文件
**           buf       缓冲区
**           len       长度
** 输　出  : 写入的长度
** 全局变量: 
** 调用模块: 
*********************************************************************************************************/
ssize_t full_write (int fd, const void *buf, size_t len)
{
    ssize_t temp;
    ssize_t total = 0;
    
    while (len) {
        temp = safe_write(fd, (char *)buf, len);
        if (temp < 0) {
            return  (temp);
        }
        total += temp;
        buf    = ((const char *)buf) + temp;
        len   -= (size_t)temp;
    }

	return  (total);
}
/*********************************************************************************************************
** 函数名称: bb_putchar
** 功能描述: 输出一个字符
** 输　入  : c     字符
** 输　出  : 
** 全局变量: 
** 调用模块: 
*********************************************************************************************************/
int  bb_putchar (int ch)
{
    return  (fputc(ch, stdout));
}

/* wdf */
/**********************************************************************************************************
  find a char in string from left, return the char addr if find or the '\0' addr
**********************************************************************************************************/
char *strchrnul(const char *str, char c)
{
    char *p = strchr(str, c);

    if (p == NULL) {
        return (char *)(str + strlen(str));
    } else {
        return p;
    }
}

/**********************************************************************************************************
  count of a string chars, return strlen if it's little than maxlen or maxlen
**********************************************************************************************************/
size_t strnlen (const char *s,
				size_t imaxlen)
{
    const char *save = s + 1;

    while (*s++ != EOS && (s - save) < imaxlen)
        ;

    return (s - save);
}

/**********************************************************************************************************
  copy a string to a new malloc memory, return the new string address
**********************************************************************************************************/
char * xstrdup (const char *string)
{
	return strcpy (xmalloc (strlen (string) + 1), string);
}

/**********************************************************************************************************
  copy a string to a new malloc memory, if source strlen > n, only copy front n chars
**********************************************************************************************************/
char * xstrndup (const char *s, size_t n)  
{  
    char *result;  
    size_t len = strlen (s);  

    if (n < len)  
        len = n;  

    result = malloc(len + 1);   

    result[len] = '\0';  
    return (char *) memcpy (result, s, len);  
}

/**********************************************************************************************************
  alloc memory, if failed warning caller
**********************************************************************************************************/
void * xmalloc (size_t size)
{
    register void *value = malloc(size);
    if (value == 0)
        printf("virtual memory exhausted");

    return value;
}
/* wdf */

/*********************************************************************************************************
  END
*********************************************************************************************************/
