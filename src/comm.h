/*
* Race for the Galaxy AI
*
* Copyright (C) 2009-2015 Keldon Jones
*
* Source file modified by J.-R. Reinhard, November 2016.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>

/*
 * Message buffer length
 */
#define BUF_LEN 1024

/*
 * Message header length
 */
#define HEADER_LEN 8

/*
 * Message types.
 */
#define MSG_LOGIN             1
#define MSG_HELLO             2
#define MSG_DENIED            3
#define MSG_GOODBYE           4
#define MSG_PING              5

#define MSG_PLAYER_NEW        10
#define MSG_PLAYER_LEFT       11

#define MSG_OPENGAME          20
#define MSG_GAME_PLAYER       21
#define MSG_CLOSE_GAME        22
#define MSG_JOIN              23
#define MSG_LEAVE             24
#define MSG_JOINACK           25
#define MSG_JOINNAK           26
#define MSG_CREATE            27
#define MSG_START             28
#define MSG_REMOVE            29
#define MSG_RESIGN            30
#define MSG_ADD_AI            31

#define MSG_STATUS_META       40
#define MSG_STATUS_PLAYER     41
#define MSG_STATUS_CARD       42
#define MSG_STATUS_GOAL       43
#define MSG_STATUS_MISC       44
#define MSG_LOG               45
#define MSG_CHAT              46
#define MSG_WAITING           47
#define MSG_SEAT              48
#define MSG_GAMECHAT          49
#define MSG_LOG_FORMAT        50

#define MSG_CHOOSE            60
#define MSG_PREPARE           61

#define MSG_GAMEOVER          70

/*
 * Connection states.
 */
#define CS_EMPTY              0
#define CS_INIT               1
#define CS_LOBBY              2
#define CS_PLAYING            3
#define CS_DISCONN            4

/*
 * Wait states.
 */
#define WAIT_READY            0
#define WAIT_BLOCKED          1
#define WAIT_OPTION           2


/* External functions */
extern int get_string(char *dest, unsigned int dest_len,
                      char *msg, unsigned int msg_len, char **msg_ptr);
extern int get_integer(int *dest,
                       char *msg, unsigned int msg_len, char **msg_ptr);
extern void put_string(char *ptr, char **msg);
extern void put_integer(int x, char **msg);
extern void start_msg(char **msg, int type);
extern void finish_msg(char *start, char *end);
extern void send_msg(int fd, char *msg);
extern void send_msgf(int fd, int type, char *fmt, ...);
