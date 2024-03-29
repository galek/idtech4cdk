/**
 * $Id: BLI_blenlib.h,v 1.17 2005/11/05 13:09:43 elubie Exp $
 *
 * ***** BEGIN GPL/BL DUAL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL/BL DUAL LICENSE BLOCK *****
 *
 * @mainpage BLI - Blender LIbrary external interface
 *
 * @section about About the BLI module
 *
 * This is the external interface of the Blender Library. If you find
 * a call to a BLI function that is not prototyped here, please add a
 * prototype here. The library offers mathematical operations (mainly
 * vector and matrix calculus), an abstraction layer for file i/o,
 * functions for calculating Perlin noise, scanfilling services for
 * triangles, and a system for guarded memory
 * allocation/deallocation. There is also a patch to make MS Windows
 * behave more or less Posix-compliant.
 *
 * @section issues Known issues with BLI
 *
 * - blenlib is written in C.
 * - The posix-compliancy may move to a separate lib that deals with 
 *   platform dependencies. (There are other platform-dependent 
 *   fixes as well.)
 * - The file i/o has some redundant code. It should be cleaned.
 * - arithb.c is a very messy matrix library. We need a better 
 *   solution.
 * - vectorops.c is close to superfluous. It may disappear in the 
 *   near future.
 * 
 * @section dependencies Dependencies
 *
 * - The blenlib uses type defines from makesdna/, and functions from
 * standard libraries.
 * 
 * $Id: BLI_blenlib.h,v 1.17 2005/11/05 13:09:43 elubie Exp $ 
*/

#ifndef BLI_BLENLIB_H
#define BLI_BLENLIB_H

/* braindamage for the masses... needed
	because fillfacebase and fillvertbase are used outside */
#include "DNA_listBase.h" 

extern ListBase fillfacebase;
extern ListBase fillvertbase;
/**
 * @attention Defined in scanfill.c
 */
extern ListBase filledgebase;
extern int totblock;

struct chardesc;
struct direntry;
struct rctf;
struct rcti;
struct EditVert;
struct PackedFile;
struct LinkNode;

#ifdef __cplusplus
extern "C" {
#endif

/* BLI_util.h */
char *BLI_gethome(void);
void BLI_make_file_string(const char *relabase, char *string,  const char *dir, const char *file);
void BLI_make_exist(char *dir);
void BLI_split_dirfile(char *string, char *dir, char *file);
int BLI_testextensie(char *str, char *ext);
void addlisttolist(ListBase *list1, ListBase *list2);
void BLI_insertlink(struct ListBase *listbase, void *vprevlink, void *vnewlink);
void * BLI_findlink(struct ListBase *listbase, int number);
void BLI_freelistN(struct ListBase *listbase);
void BLI_addtail(struct ListBase *listbase, void *vlink);
void BLI_remlink(struct ListBase *listbase, void *vlink);
void BLI_newname(char * name, int add);
int BLI_stringdec(char *string, char *kop, char *staart, unsigned short *numlen);
void BLI_stringenc(char *string, char *kop, char *staart, unsigned short numlen, int pic);
void BLI_addhead(struct ListBase *listbase, void *vlink);
void BLI_insertlinkbefore(struct ListBase *listbase, void *vnextlink, void *vnewlink);
void BLI_freelist(struct ListBase *listbase);
int BLI_countlist(struct ListBase *listbase);
void BLI_freelinkN(ListBase *listbase, void* vlink);
void BLI_splitdirstring(char *di,char *fi);

	/**
	 * Blender's path code replacement function.
	 * Bases @a path strings leading with "//" by the
	 * directory @a basepath, and replaces instances of
	 * '#' with the @a framenum. Results are written
	 * back into @a path.
	 * 
	 * @a path The path to convert
	 * @a basepath The directory to base relative paths with.
	 * @a framenum The framenumber to replace the frame code with.
	 * @retval Returns true if the path was relative (started with "//").
	 */
int BLI_convertstringcode(char *path, char *basepath, int framenum);

void BLI_makestringcode(const char *relfile, char *file);

	/**
	 * Change every @a from in @a string into @a to. The
	 * result will be in @a string
	 *
	 * @a string The string to work on
	 * @a from The character to replace
	 * @a to The character to replace with
	 */
void BLI_char_switch(char *string, char from, char to);

	/**
	 * Makes sure @a path has platform-specific slashes.
	 * 
	 * @a path The path to 'clean'
	 */
void BLI_clean(char *path);
	/**
	 * Duplicates the cstring @a str into a newly mallocN'd
	 * string and returns it.
	 * 
	 * @param str The string to be duplicated
	 * @retval Returns the duplicated string
	 */
char* BLI_strdup(char *str);

	/**
	 * Duplicates the first @a len bytes of cstring @a str 
	 * into a newly mallocN'd string and returns it. @a str
	 * is assumed to be at least len bytes long.
	 * 
	 * @param str The string to be duplicated
	 * @param len The number of bytes to duplicate
	 * @retval Returns the duplicated string
	 */
char* BLI_strdupn(char *str, int len);

	/**
	 * Like strncpy but ensures dst is always
	 * '\0' terminated.
	 * 
	 * @param dst Destination for copy
	 * @param src Source string to copy
	 * @param maxncpy Maximum number of characters to copy (generally
	 *   the size of dst)
	 * @retval Returns dst
	 */
char* BLI_strncpy(char *dst, char *src, int maxncpy);

	/**
	 * Compare two strings
	 * 
	 * @retval True if the strings are equal, false otherwise.
	 */
int BLI_streq(char *a, char *b);

	/**
	 * Compare two strings without regard to case.
	 * 
	 * @retval True if the strings are equal, false otherwise.
	 */
int BLI_strcaseeq(char *a, char *b);

	/**
	 * Read a file as ASCII lines. An empty list is
	 * returned if the file cannot be opened or read.
	 * 
	 * @attention The returned list should be free'd with
	 * BLI_free_file_lines.
	 * 
	 * @param name The name of the file to read.
	 * @retval A list of strings representing the file lines.
	 */
struct LinkNode *BLI_read_file_as_lines(char *name);

	/**
	 * Free the list returned by BLI_read_file_as_lines.
	 */
void BLI_free_file_lines(struct LinkNode *lines);

	/**
	 * Checks if name is a fully qualified filename to an executable.
	 * If not it searches $PATH for the file. On Windows it also
	 * adds the correct extension (.com .exe etc) from
	 * $PATHEXT if necessary. Also on Windows it translates
	 * the name to its 8.3 version to prevent problems with
	 * spaces and stuff. Final result is returned in fullname.
	 *
	 * @param fullname The full path and full name of the executable
	 * @param name The name of the executable (usually argv[0]) to be checked
	 */
void BLI_where_am_i(char *fullname, char *name);

	/**
	 * determines the full path to the application bundle on OS X
	 *
	 * @return path to application bundle
	 */
#ifdef __APPLE__
char* BLI_getbundle(void);
#endif

#ifdef WIN32
int BLI_getInstallationDir( char * str );
#endif
		
/* BLI_storage.h */
int    BLI_filesize(int file);
double BLI_diskfree(char *dir);
char * BLI_getwdN(char * dir);
void BLI_hide_dot_files(int set);
unsigned int BLI_getdir(char *dirname,  struct direntry **filelist);

/**
 * @attention Do not confuse with BLI_exists
 */
int    BLI_exist(char *name);

/* BLI_fileops.h */
void  BLI_recurdir_fileops(char *dirname);
int BLI_link(char *file, char *to);
int BLI_backup(char *file, char *from, char *to);


/**
 * @attention Do not confuse with BLI_exist
 */
int   BLI_exists(char *file);
int   BLI_copy_fileops(char *file, char *to);
int   BLI_rename(char *from, char *to);
int   BLI_gzip(char *from, char *to);
int   BLI_delete(char *file, int dir, int recursive);
int   BLI_move(char *file, char *to);
int   BLI_touch(char *file);
char *BLI_last_slash(char *string);

/* BLI_rct.c */
/**
 * Determine if a rect is empty. An empty
 * rect is one with a zero (or negative)
 * width or height.
 *
 * @return True if @a rect is empty.
 */
int BLI_rcti_is_empty(struct rcti * rect);
void BLI_init_rctf(struct rctf *rect, float xmin, float xmax, float ymin, float ymax);
int  BLI_in_rcti(struct rcti * rect, int x, int y);
int  BLI_in_rctf(struct rctf *rect, float x, float y);
int  BLI_isect_rctf(struct rctf *src1, struct rctf *src2, struct rctf *dest);
/* why oh why doesn't this work? */
//void BLI_union_rctf(struct rctf *rct1, struct rctf *rct2);
void BLI_union_rctf(struct rctf *rcta, struct rctf *rctb);

/* scanfill.c: used in displist only... */
struct EditVert *BLI_addfillvert(float *vec);
struct EditEdge *BLI_addfilledge(struct EditVert *v1, struct EditVert *v2);
int BLI_edgefill(int mode, int mat_nr);
void BLI_end_edgefill(void);

/* noise.h: */
float BLI_hnoise(float noisesize, float x, float y, float z);
float BLI_hnoisep(float noisesize, float x, float y, float z);
float BLI_turbulence(float noisesize, float x, float y, float z, int nr);
float BLI_turbulence1(float noisesize, float x, float y, float z, int nr);
/* newnoise: generic noise & turbulence functions to replace the above BLI_hnoise/p & BLI_turbulence/1.
 * This is done so different noise basis functions can be used */
float BLI_gNoise(float noisesize, float x, float y, float z, int hard, int noisebasis);
float BLI_gTurbulence(float noisesize, float x, float y, float z, int oct, int hard, int noisebasis);
/* newnoise: musgrave functions */
float mg_fBm(float x, float y, float z, float H, float lacunarity, float octaves, int noisebasis);
float mg_MultiFractal(float x, float y, float z, float H, float lacunarity, float octaves, int noisebasis);
float mg_VLNoise(float x, float y, float z, float distortion, int nbas1, int nbas2);
float mg_HeteroTerrain(float x, float y, float z, float H, float lacunarity, float octaves, float offset, int noisebasis);
float mg_HybridMultiFractal(float x, float y, float z, float H, float lacunarity, float octaves, float offset, float gain, int noisebasis);
float mg_RidgedMultiFractal(float x, float y, float z, float H, float lacunarity, float octaves, float offset, float gain, int noisebasis);
/* newnoise: voronoi */
void voronoi(float x, float y, float z, float* da, float* pa, float me, int dtype);
/* newnoise: cellNoise & cellNoiseV (for vector/point/color) */
float cellNoise(float x, float y, float z);
void cellNoiseV(float x, float y, float z, float *ca);

/* These callbacks are needed to make the lib finction properly */

/**
 * Set a function taking a char* as argument to flag errors. If the
 * callback is not set, the error is discarded.
 * @param f The function to use as callback
 * @attention used in creator.c
 */
void BLI_setErrorCallBack(void (*f)(char*));

/**
 * Set a function to be able to interrupt the execution of processing
 * in this module. If the function returns true, the execution will
 * terminate gracefully. If the callback is not set, interruption is
 * not possible.
 * @param f The function to use as callback
 * @attention used in creator.c
 */
void BLI_setInterruptCallBack(int (*f)(void));

int BLI_strcasecmp(const char *s1, const char *s2);
int BLI_strncasecmp(const char *s1, const char *s2, int n);

#define PRNTSUB(type,arg)			printf(#arg ": %" #type " ", arg)

#ifndef PRINT
#define PRINT(t,v)					{PRNTSUB(t,v); printf("\n");}
#define PRINT2(t1,v1,t2,v2)			{PRNTSUB(t1,v1); PRNTSUB(t2,v2); printf("\n");}
#define PRINT3(t1,v1,t2,v2,t3,v3)	{PRNTSUB(t1,v1); PRNTSUB(t2,v2); PRNTSUB(t3,v3); printf("\n");}
#define PRINT4(t1,v1,t2,v2,t3,v3,t4,v4)	{PRNTSUB(t1,v1); PRNTSUB(t2,v2); PRNTSUB(t3,v3); PRNTSUB(t4,v4); printf("\n");}
#endif

/**
 * @param array The array in question
 * @retval The number of elements in the array.
 */
#define BLI_ARRAY_NELEMS(array)		(sizeof((array))/sizeof((array)[0]))

/**
 * @param strct The structure of interest
 * @param member The name of a member field of @a strct
 * @retval The offset in bytes of @a member within @a strct
 */
#define BLI_STRUCT_OFFSET(strct, member)	((int) &((strct*) 0)->member)

#ifdef __cplusplus
}
#endif

#endif

