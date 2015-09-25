/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#ifndef _NET_COMMON_H_
#define _NET_COMMON_H_

#define BEGIN_NAMESPACE(tag) namespace tag {

#define END_NAMESPACE(tag) }

#define NET_ERR -1
#define NET_OK 0

#define MAX_EVENTS 1024

// socket state
#define NET_READABLE 1
#define NET_WRITABLE 2
#define NET_ERRORBLE 4


// connect state
#define NET_CON_CONNECT 1
#define NET_CON_DISCONN 2
#define NET_CON_ERROR 4

// stream state
#define NET_ORIGIN 0x01
#define NET_READING_HEADER 0x02
#define NET_FINISH_HEADER 0x04
#define NET_FINISH_DATA 0x08

#define NET_WRITE_READY 0x10
#define NET_FINISH_WRITE 0x20

// iocom data state
#define NET_IOCOMM_ERROR 0x1
#define NET_IOCOMM_READ 0x2
#define NET_IOCOMM_WRITE 0x4


#define CHUNKSIZE 4096
#define DEFAULT_WAIT_TIME 100000

#define IsState(target, tr) (target&tr)

#endif
