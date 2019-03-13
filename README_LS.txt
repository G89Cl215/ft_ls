# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README.txt                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 18:29:58 by tgouedar          #+#    #+#              #
#    Updated: 2019/03/13 19:24:48 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

>>> RECHERCHE SUR LES OUTILS DE LS <<<

Sans ordre significatif...

			-=-=-	I. opendir/readdir/closedir		-=-=-

#include <dirent.h>

defines the following
> DIR 		a type representing a directory stream.

> ino_t		a type used for file serial numbers.
typedef ulong_t		ino_t;

dev_t

mode_t 

nlink_t

a)	The dirent struct

#include <sys/types.h>
#include <sys/dir.h>

struct dirent
{
ino_t		d_ino;               /* file number of entry */
__uint16_t	d_reclen;            /* length of this record */
__uint8_t	d_type;              /* file type, see below */
__uint8_t   d_namlen;            /* length of string in d_name */
char    	d_name[255 + 1];     /* name must be no longer than this */
}

d_type can display :
-DT_UNKNOWN
	The type is unknown. Only some filesystems have full support to return the
type of the file, others might always return this value.
-DT_REG
	A regular file.
-DT_DIR
	A directory.
-DT_FIFO
	A named pipe, or FIFO. See FIFO Special Files.
-DT_SOCK
	A local-domain socket.
-DT_CHR
	A character device.
-DT_BLK
	A block device.
-DT_LNK
	A symbolic link.

Tips found on stack overflow :
(d_type is a speed optimization to save on lstat(2) calls, when it's supported.

As the readdir(3) man page points out, not all filesystems return real info
in the d_type field (typically because it would take an extra disk seek to read
the inode. Filesystems that always set DT_UNKNOWN are common in real life, and
not something that you can ignore.

You always need code that will fall back to using lstat(2) if
d_type==DT_UNKNOWN, if the filename alone isn't enough to decide it's
uninteresting. (This is the case for some callers, like find -name or expanding
globs like *.c, which is why readdir doesn't incur the overhead of filling it
in if it would take an extra disk read.)

The Linux getdents(2) man page has an example program that does what you're
trying to do, including a chained-ternary-operator block to decode the d_type
field into text strings. (As the other answers point out, your mistake is
printing it out as an character, rather than comparing it against DT_REG,
DT_DIR, etc.)

To be portable, your code needs to check that struct dirent even HAS a d_type
field, if you use it, or your code won't even compile outside of GNU and BSD
systems. (see readdir(3)))

a)	DIR		*opendir(const char *filename);

	The opendir() function opens the directory named by filename, associates a
directory stream with it and returns a pointer to be used to identify the
directory stream in subsequent operations.  The pointer NULL is returned
if filename cannot be accessed, or if it cannot malloc(3) enough memory
to hold the whole thing, and sets the global variable errno to indicate the
error.

b)	struct dirent	*readdir(DIR *dirp);

	The readdir() function returns a pointer to the next directory entry.
It returns NULL upon reaching the end of the directory or on error.
In the event of an error, errno may be set to any of the values documented for 
the getdirentries(2) system call.

c)	int		closedir(DIR *dirp);

	The closedir() function closes the named directory stream and frees the
structure associated with the dirp pointer, returning 0 on success.
On failure, -1 is returned and the global variable errno is set to indicate the
error.


				-=-=-	II. stat/lstat		-=-=-

#include <sys/stat.h>

a)	The stat struct

	The <sys/stat.h> header dfines a structure of data concerning the file
and into which information is placed when the following fun. The stat struct may
contain more information when the _DARWIN_FEATURE_64_BIT_INODE is defined.
The stat structure is defined as:

struct stat
{
dev_t    			st_dev;			/* device inode resides on */
ino_t    			st_ino;			/* inode's number */
mode_t   			st_mode;		/* inode protection mode */
nlink_t  			st_nlink;		/* number of hard links to the file */
uid_t    			st_uid;			/* user-id of owner */
gid_t    			st_gid;			/* group-id of owner */
dev_t    			st_rdev;		/* device type, for special file inode */
struct timespec 	st_atimespec;	/* time of last access */
struct timespec 	st_mtimespec;	/* time of last data modification */
struct timespec 	st_ctimespec;	/* time of last file status change */
off_t    			st_size;		/* file size, in bytes */
quad_t   			st_blocks;		/* blocks allocated for file */
u_long   			st_blksize;		/* optimal file sys I/O ops blocksize */
u_long   			st_flags;		/* user defined flags for file */
u_long   			st_gen;			/* file generation number */
};


b)	int		stat(const char *restrict path, struct stat *restrict buf);

	The stat() function obtains information about the file pointed to by path.
Read, write or execute permission of the named file is not required, but all
directories listed in the path name leading to the file must be searchable.

c)	int		lstat(const char *restrict path, struct stat *restrict buf);

	The lstat() function is like stat() except in the case where the named file
is a symbolic link; lstat() returns information about the link, while stat()
returns information about the file the link references.  For symbolic links,
the st_mode member contains meaningful information when used with the file type
macros, and the st_size member contains the length of the pathname contained in
the symbolic link. File mode bits and the contents of the remaining members
of the stat structure are unspecified. The value returned in the st_size member
is the length of the contents of the symbolic link, and does not count any
trailing null.



			-=-=-	III. getpwuid/getgrgid		-=-=-


#include <uuid/uuid.h>

	User and group IDs of a process, both real and effective. To use these
facilities, you must include the header files sys/types.h and unistd.h.

Data Type: uid_t
	This is an integer data type used to represent user IDs.
In the GNU C Library, this is an alias for unsigned int.

Data Type: gid_t
	This is an integer data type used to represent group IDs.
In the GNU C Library, this is an alias for unsigned int.

Function: uid_t getuid (void)
	Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

The getuid function returns the real user ID of the process.

Function: gid_t getgid (void)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

The getgid function returns the real group ID of the process.

The geteuid function returns the effective user ID of the process.

Function: gid_t getegid (void)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

The getegid function returns the effective group ID of the process.


Here’s how to use getgroups to read all the supplementary group IDs:

gid_t 	*read_all_groups (void)
{
	int		ngroups = getgroups (0, NULL);
	gid_t	*groups = (gid_t *) xmalloc (ngroups * sizeof (gid_t));
	int 	val = getgroups (ngroups, groups);
	
	if (val < 0)
	{
	    free (groups);
		return NULL;
	}
	return groups;
}

a)	The passwd struct

	The <pwd.h> header defines a structure of information from opendirectoryd,
including records in /etc/master.passwd which is described in master.passwd :

struct passwd
{
char    *pw_name;       /* user name */
char    *pw_passwd;     /* encrypted password */
uid_t   pw_uid;         /* user uid */
gid_t   pw_gid;         /* user gid */
time_t  pw_change;      /* password change time */
char    *pw_class;      /* user access class */
char    *pw_gecos;      /* Honeywell login info */
char    *pw_dir;        /* home directory */
char    *pw_shell;      /* default shell */
time_t  pw_expire;      /* account expiration */
int     pw_fields;      /* internal: fields filled in */
};


b)	struct passwd	*getpwuid(uid_t uid);

#include <sys/types.h>

	getpwuid(), searches the password database for the given login name, user
uid, or user uuid respectively, always returning the first one encountered.

	Note that the password file /etc/master.passwd does not contain user UUIDs.
The UUID for a user may be found using mbr_uid_to_uuid().

	On OS X, these routines are thread-safe and return a pointer to a
thread-specific data structure. The contents of this data structure are
automatically released by subsequent calls to any of these routines on the same
thread, or when the thread exits.  These routines are therefore unsuitable for
use in libraries or frameworks, from where they may overwrite the per-thread
data that the calling application expects to find as a result of its own calls
to these routines. Library and framework code should use the alternative
reentrant variants detailed below.

getpwuid() returnes a valid pointer to a passwd structure on success or NULL if
the entry is not found or if an error occurs. If an error does occur, errno will
be set. Note that programs must explicitly set errno to zero before calling any
of these functions if they need to distinguish between a non-existent entry and
an error.

c)	The group struct

	The <grp.h> header defines a structure of information from opendirectoryd,
including records in /etc/master.passwd which is described in master.passwd :

struct group
{
char    *gr_name;       /* group name */
char    *gr_passwd;     /* group password */
gid_t   gr_gid;         /* group id */
char    **gr_mem;       /* group members */
};


d)	struct group	*getgrgid(gid_t gid);

	The function getgrgid() searches the group database for the given group name
pointed to by name, the group id given by gid, or the UUID given by uuid
respectively, returning the first one encountered. Identical group names, group
gids, or uuids may result in undefined behavior.

	Note that the groups file /etc/group does not contain group UUIDs.
The UUID for a group may be found using mbr_gid_to_uuid().

	On OS X, these routines are thread-safe and return a pointer to a
thread-specific data structure. The contents of this data structure are
automatically released by subsequent calls to any of these routines on the same
thread, or when the thread exits. These routines are therefore unsuitable for
use in libraries or frameworks, from where they may overwrite the per-thread
data that the calling application expects to find as a result of its own calls
to these routines. Library and framework code should use the alternative
reentrant variants detailed below.

getgrgid(), returns a pointer to a group structure on success or NULL if the
entry is not found or if an error occurs. If an error does occur, errno will be
set.  Note that programs must explicitly set errno to zero before calling any
of these functions if they need to distinguish between a non-existent entry and
an error.



					-=-=-	IV. time/ctime		-=-=-

#include <time.h>

a)	The time_t type



b)	time_t	time(time_t *tloc);

	returns the value of time in seconds since
0 hours, 0 minutes, 0 seconds, January 1, 1970, Coordinated Universal Time,
without including leap seconds. If an error occurs, time() returns the value
(time_t)-1. The return value is also stored in *tloc, provided that tloc is
non-null.

c)	char	*ctime(const time_t *clock);


	ctime() takes as an argument a time value representing the time in seconds
since the Epoch (00:00:00 UTC, January 1, 1970; see time(3)). When encountering
an error, these functions return NULL and set errno to an appropriate value and
djusts this time value for the current time zone. It returns a pointer to a
26-character string of the form:

		Thu Nov 24 18:22:48 1986\n\0

All of the fields have constant width.



						-=-=-	V. readlink		-=-=-

#include <unistd.h>

ssize_t
		readlink(const char *restrict path, char *restrict buf, size_t bufsize);

	readlink() places the contents of the symbolic link path in the buffer buf,
which has size bufsize. Readlink does not append a NUL character to buf.


				-=-=-	VI. perror/sterror		-=-=-


	The strerror(), and perror() functions look up the error message string
corresponding to an error number.
If the error number is not recognized, these functions return an error message
string containing "Unknown error: " followed by the error number in decimal.


a)	void	perror(const char *s);

#include <stdio.h>

	The perror() function finds the error message corresponding to the current
value of the global variable errno (intro(2)) and writes it, followed by a new-
line, to the standard error file descriptor. If the argument s is non-NULL and
does not point to the null character, this string is prepended to the message
string and separated from it by a colon and space (``: ''); otherwise, only the
error message string is printed.


b)	char	*strerror(int errnum);

#include <string.h>

extern const char *const	sys_errlist[];
extern const int			sys_nerr;

	strerror() returns EINVAL as a warning. Error numbers recognized by this
implementation fall in the range 0 <= errnum < sys_nerr.


-=-=-	VII. errno		-=-=-
