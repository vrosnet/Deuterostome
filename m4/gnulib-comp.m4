# DO NOT EDIT! GENERATED AUTOMATICALLY!
# Copyright (C) 2002-2011 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects that use version control, this file can be treated like
# other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([gl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  m4_pattern_allow([^gl_LIBOBJS$])dnl a variable
  m4_pattern_allow([^gl_LTLIBOBJS$])dnl a variable
  AC_REQUIRE([AC_PROG_RANLIB])
  AC_REQUIRE([AM_PROG_CC_C_O])
  # Code from module alloca:
  # Code from module alloca-opt:
  # Code from module arg-nonnull:
  # Code from module c++defs:
  # Code from module chdir-long:
  # Code from module chown:
  # Code from module clock-time:
  # Code from module cloexec:
  # Code from module close:
  # Code from module configmake:
  # Code from module d-type:
  # Code from module dirent:
  # Code from module dirfd:
  # Code from module dirname-lgpl:
  # Code from module dosname:
  # Code from module double-slash-root:
  # Code from module dup2:
  # Code from module errno:
  # Code from module error:
  # Code from module exitfail:
  # Code from module extensions:
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
  # Code from module fchdir:
  # Code from module fclose:
  # Code from module fcntl:
  # Code from module fcntl-h:
  # Code from module fd-hook:
  # Code from module fdopendir:
  # Code from module fflush:
  AC_REQUIRE([AC_FUNC_FSEEKO])
  # Code from module filenamecat-lgpl:
  # Code from module fnmatch:
  # Code from module fpurge:
  # Code from module freading:
  # Code from module fseeko:
  AC_REQUIRE([AC_FUNC_FSEEKO])
  # Code from module ftello:
  AC_REQUIRE([AC_FUNC_FSEEKO])
  # Code from module futimens:
  # Code from module getcwd-lgpl:
  # Code from module getdtablesize:
  # Code from module getlogin_r:
  # Code from module gettext-h:
  # Code from module gettime:
  # Code from module gettimeofday:
  # Code from module glob:
  # Code from module havelib:
  # Code from module include_next:
  # Code from module intprops:
  # Code from module lchown:
  # Code from module localcharset:
  # Code from module lock:
  # Code from module lseek:
  # Code from module lstat:
  # Code from module malloc-posix:
  # Code from module mbrtowc:
  # Code from module mbsinit:
  # Code from module mbsrtowcs:
  # Code from module memchr:
  # Code from module mempcpy:
  # Code from module memrchr:
  # Code from module mkdir:
  # Code from module mkdtemp:
  # Code from module multiarch:
  # Code from module open:
  # Code from module openat:
  # Code from module openat-die:
  # Code from module realloc-posix:
  # Code from module rmdir:
  # Code from module save-cwd:
  # Code from module stat:
  # Code from module stat-time:
  # Code from module stdbool:
  # Code from module stddef:
  # Code from module stdint:
  # Code from module stdio:
  # Code from module stdlib:
  # Code from module strdup-posix:
  # Code from module streq:
  # Code from module strerror:
  # Code from module strerror_r-posix:
  # Code from module string:
  # Code from module strnlen1:
  # Code from module sys_stat:
  # Code from module sys_time:
  # Code from module tempname:
  # Code from module threadlib:
  gl_THREADLIB_EARLY
  # Code from module time:
  # Code from module timespec:
  # Code from module unistd:
  # Code from module unistd-safer:
  # Code from module unlink:
  # Code from module utimens:
  # Code from module utimensat:
  # Code from module verify:
  # Code from module warn-on-use:
  # Code from module wchar:
  # Code from module wctype-h:
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([gl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [true])
  gl_cond_libtool=true
  gl_m4_base='m4'
  m4_pushdef([AC_LIBOBJ], m4_defn([gl_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gl_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gl_LIBSOURCES]))
  m4_pushdef([gl_LIBSOURCES_LIST], [])
  m4_pushdef([gl_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='lib'
changequote(,)dnl
LTALLOCA=`echo "$ALLOCA" | sed -e 's/\.[^.]* /.lo /g;s/\.[^.]*$/.lo/'`
changequote([, ])dnl
AC_SUBST([LTALLOCA])
gl_FUNC_ALLOCA
gl_FUNC_CHDIR_LONG
gl_FUNC_CHOWN
gl_UNISTD_MODULE_INDICATOR([chown])
gl_CLOCK_TIME
gl_CLOEXEC
gl_MODULE_INDICATOR_FOR_TESTS([cloexec])
gl_FUNC_CLOSE
gl_UNISTD_MODULE_INDICATOR([close])
gl_CONFIGMAKE_PREP
gl_CHECK_TYPE_STRUCT_DIRENT_D_TYPE
gl_DIRENT_H
gl_FUNC_DIRFD
gl_DIRENT_MODULE_INDICATOR([dirfd])
gl_DIRNAME_LGPL
gl_DOUBLE_SLASH_ROOT
gl_FUNC_DUP2
gl_UNISTD_MODULE_INDICATOR([dup2])
gl_HEADER_ERRNO_H
gl_ERROR
m4_ifdef([AM_XGETTEXT_OPTION],
  [AM_][XGETTEXT_OPTION([--flag=error:3:c-format])
   AM_][XGETTEXT_OPTION([--flag=error_at_line:5:c-format])])
gl_FUNC_FCHDIR
gl_UNISTD_MODULE_INDICATOR([fchdir])
gl_FUNC_FCLOSE
gl_STDIO_MODULE_INDICATOR([fclose])
gl_FUNC_FCNTL
gl_FCNTL_MODULE_INDICATOR([fcntl])
gl_FCNTL_H
gl_FUNC_FDOPENDIR
gl_DIRENT_MODULE_INDICATOR([fdopendir])
gl_MODULE_INDICATOR([fdopendir])
gl_FUNC_FFLUSH
gl_MODULE_INDICATOR([fflush])
gl_STDIO_MODULE_INDICATOR([fflush])
gl_FILE_NAME_CONCAT_LGPL
gl_FUNC_FNMATCH_POSIX
gl_FUNC_FPURGE
gl_STDIO_MODULE_INDICATOR([fpurge])
gl_FUNC_FREADING
gl_FUNC_FSEEKO
gl_STDIO_MODULE_INDICATOR([fseeko])
gl_FUNC_FTELLO
gl_STDIO_MODULE_INDICATOR([ftello])
gl_FUNC_FUTIMENS
gl_SYS_STAT_MODULE_INDICATOR([futimens])
gl_FUNC_GETCWD_LGPL
gl_UNISTD_MODULE_INDICATOR([getcwd])
gl_FUNC_GETDTABLESIZE
gl_UNISTD_MODULE_INDICATOR([getdtablesize])
gl_FUNC_GETLOGIN_R
gl_UNISTD_MODULE_INDICATOR([getlogin_r])
AC_SUBST([LIBINTL])
AC_SUBST([LTLIBINTL])
gl_GETTIME
gl_FUNC_GETTIMEOFDAY
gl_SYS_TIME_MODULE_INDICATOR([gettimeofday])
gl_GLOB
gl_FUNC_LCHOWN
gl_UNISTD_MODULE_INDICATOR([lchown])
gl_LOCALCHARSET
LOCALCHARSET_TESTS_ENVIRONMENT="CHARSETALIASDIR=\"\$(top_builddir)/$gl_source_base\""
AC_SUBST([LOCALCHARSET_TESTS_ENVIRONMENT])
gl_LOCK
gl_FUNC_LSEEK
gl_UNISTD_MODULE_INDICATOR([lseek])
gl_FUNC_LSTAT
gl_SYS_STAT_MODULE_INDICATOR([lstat])
gl_FUNC_MALLOC_POSIX
gl_STDLIB_MODULE_INDICATOR([malloc-posix])
gl_FUNC_MBRTOWC
gl_WCHAR_MODULE_INDICATOR([mbrtowc])
gl_FUNC_MBSINIT
gl_WCHAR_MODULE_INDICATOR([mbsinit])
gl_FUNC_MBSRTOWCS
gl_WCHAR_MODULE_INDICATOR([mbsrtowcs])
gl_FUNC_MEMCHR
gl_STRING_MODULE_INDICATOR([memchr])
gl_FUNC_MEMPCPY
gl_STRING_MODULE_INDICATOR([mempcpy])
gl_FUNC_MEMRCHR
gl_STRING_MODULE_INDICATOR([memrchr])
gl_FUNC_MKDIR
gl_FUNC_MKDTEMP
gl_STDLIB_MODULE_INDICATOR([mkdtemp])
gl_MULTIARCH
gl_FUNC_OPEN
gl_FCNTL_MODULE_INDICATOR([open])
gl_FUNC_OPENAT
gl_FUNC_REALLOC_POSIX
gl_STDLIB_MODULE_INDICATOR([realloc-posix])
gl_FUNC_RMDIR
gl_UNISTD_MODULE_INDICATOR([rmdir])
gl_SAVE_CWD
gl_FUNC_STAT
gl_SYS_STAT_MODULE_INDICATOR([stat])
gl_STAT_TIME
gl_STAT_BIRTHTIME
AM_STDBOOL_H
gl_STDDEF_H
gl_STDINT_H
gl_STDIO_H
gl_STDLIB_H
gl_FUNC_STRDUP_POSIX
gl_STRING_MODULE_INDICATOR([strdup])
gl_FUNC_STRERROR
gl_MODULE_INDICATOR([strerror])
gl_STRING_MODULE_INDICATOR([strerror])
gl_FUNC_STRERROR_R
gl_STRING_MODULE_INDICATOR([strerror_r])
gl_HEADER_STRING_H
gl_HEADER_SYS_STAT_H
AC_PROG_MKDIR_P
gl_HEADER_SYS_TIME_H
AC_PROG_MKDIR_P
gl_FUNC_GEN_TEMPNAME
gl_THREADLIB
gl_HEADER_TIME_H
gl_TIMESPEC
gl_UNISTD_H
gl_UNISTD_SAFER
gl_FUNC_UNLINK
gl_UNISTD_MODULE_INDICATOR([unlink])
gl_UTIMENS
gl_FUNC_UTIMENSAT
gl_SYS_STAT_MODULE_INDICATOR([utimensat])
gl_WCHAR_H
gl_WCTYPE_H
  # End of code from modules
  m4_ifval(gl_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gl_LIBSOURCES_DIR])[ ||
      for gl_file in ]gl_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gl_LIBSOURCES_DIR])
  m4_popdef([gl_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gl_libobjs=
    gl_ltlibobjs=
    if test -n "$gl_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gl_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gl_libobjs="$gl_libobjs $i.$ac_objext"
        gl_ltlibobjs="$gl_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gl_LIBOBJS], [$gl_libobjs])
    AC_SUBST([gl_LTLIBOBJS], [$gl_ltlibobjs])
  ])
  gltests_libdeps=
  gltests_ltlibdeps=
  m4_pushdef([AC_LIBOBJ], m4_defn([gltests_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gltests_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gltests_LIBSOURCES]))
  m4_pushdef([gltests_LIBSOURCES_LIST], [])
  m4_pushdef([gltests_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='tests'
changequote(,)dnl
  gltests_WITNESS=IN_`echo "${PACKAGE-$PACKAGE_TARNAME}" | LC_ALL=C tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ | LC_ALL=C sed -e 's/[^A-Z0-9_]/_/g'`_GNULIB_TESTS
changequote([, ])dnl
  AC_SUBST([gltests_WITNESS])
  gl_module_indicator_condition=$gltests_WITNESS
  m4_pushdef([gl_MODULE_INDICATOR_CONDITION], [$gl_module_indicator_condition])
  m4_popdef([gl_MODULE_INDICATOR_CONDITION])
  m4_ifval(gltests_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gltests_LIBSOURCES_DIR])[ ||
      for gl_file in ]gltests_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gltests_LIBSOURCES_DIR])
  m4_popdef([gltests_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gltests_libobjs=
    gltests_ltlibobjs=
    if test -n "$gltests_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gltests_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gltests_libobjs="$gltests_libobjs $i.$ac_objext"
        gltests_ltlibobjs="$gltests_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gltests_LIBOBJS], [$gltests_libobjs])
    AC_SUBST([gltests_LTLIBOBJS], [$gltests_ltlibobjs])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_LIBOBJ], [
  AS_LITERAL_IF([$1], [gl_LIBSOURCES([$1.c])])dnl
  gl_LIBOBJS="$gl_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gl_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gl_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gl_LIBSOURCES_DIR], [lib])
      m4_append([gl_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_LIBOBJ], [
  AS_LITERAL_IF([$1], [gltests_LIBSOURCES([$1.c])])dnl
  gltests_LIBOBJS="$gltests_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gltests_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gltests_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gltests_LIBSOURCES_DIR], [tests])
      m4_append([gltests_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([gl_FILE_LIST], [
  build-aux/arg-nonnull.h
  build-aux/c++defs.h
  build-aux/config.rpath
  build-aux/warn-on-use.h
  lib/alloca.c
  lib/alloca.in.h
  lib/at-func.c
  lib/basename-lgpl.c
  lib/chdir-long.c
  lib/chdir-long.h
  lib/chown.c
  lib/cloexec.c
  lib/cloexec.h
  lib/close.c
  lib/config.charset
  lib/dirent.in.h
  lib/dirfd.c
  lib/dirname-lgpl.c
  lib/dirname.h
  lib/dosname.h
  lib/dup-safer.c
  lib/dup2.c
  lib/errno.in.h
  lib/error.c
  lib/error.h
  lib/exitfail.c
  lib/exitfail.h
  lib/fchdir.c
  lib/fchmodat.c
  lib/fchown-stub.c
  lib/fchownat.c
  lib/fclose.c
  lib/fcntl.c
  lib/fcntl.in.h
  lib/fd-hook.c
  lib/fd-hook.h
  lib/fd-safer.c
  lib/fdopendir.c
  lib/fflush.c
  lib/filenamecat-lgpl.c
  lib/filenamecat.h
  lib/fnmatch.c
  lib/fnmatch.in.h
  lib/fnmatch_loop.c
  lib/fpurge.c
  lib/freading.c
  lib/freading.h
  lib/fseeko.c
  lib/fstatat.c
  lib/ftello.c
  lib/futimens.c
  lib/getcwd-lgpl.c
  lib/getdtablesize.c
  lib/getlogin_r.c
  lib/gettext.h
  lib/gettime.c
  lib/gettimeofday.c
  lib/glob-libc.h
  lib/glob.c
  lib/glob.in.h
  lib/glthread/lock.c
  lib/glthread/lock.h
  lib/glthread/threadlib.c
  lib/intprops.h
  lib/lchown.c
  lib/localcharset.c
  lib/localcharset.h
  lib/lseek.c
  lib/lstat.c
  lib/malloc.c
  lib/mbrtowc.c
  lib/mbsinit.c
  lib/mbsrtowcs-impl.h
  lib/mbsrtowcs-state.c
  lib/mbsrtowcs.c
  lib/memchr.c
  lib/memchr.valgrind
  lib/mempcpy.c
  lib/memrchr.c
  lib/mkdir.c
  lib/mkdirat.c
  lib/mkdtemp.c
  lib/open.c
  lib/openat-die.c
  lib/openat-priv.h
  lib/openat-proc.c
  lib/openat.c
  lib/openat.h
  lib/pipe-safer.c
  lib/realloc.c
  lib/ref-add.sin
  lib/ref-del.sin
  lib/rmdir.c
  lib/save-cwd.c
  lib/save-cwd.h
  lib/stat-time.h
  lib/stat.c
  lib/stdbool.in.h
  lib/stddef.in.h
  lib/stdint.in.h
  lib/stdio-impl.h
  lib/stdio.in.h
  lib/stdlib.in.h
  lib/strdup.c
  lib/streq.h
  lib/strerror-impl.h
  lib/strerror.c
  lib/strerror_r.c
  lib/string.in.h
  lib/stripslash.c
  lib/strnlen1.c
  lib/strnlen1.h
  lib/sys_stat.in.h
  lib/sys_time.in.h
  lib/tempname.c
  lib/tempname.h
  lib/time.in.h
  lib/timespec.h
  lib/unistd--.h
  lib/unistd-safer.h
  lib/unistd.in.h
  lib/unlink.c
  lib/unlinkat.c
  lib/utimens.c
  lib/utimens.h
  lib/utimensat.c
  lib/verify.h
  lib/wchar.in.h
  lib/wctype.in.h
  m4/00gnulib.m4
  m4/alloca.m4
  m4/chdir-long.m4
  m4/chown.m4
  m4/clock_time.m4
  m4/cloexec.m4
  m4/close.m4
  m4/codeset.m4
  m4/configmake.m4
  m4/d-type.m4
  m4/dirent_h.m4
  m4/dirfd.m4
  m4/dirname.m4
  m4/double-slash-root.m4
  m4/dup2.m4
  m4/errno_h.m4
  m4/error.m4
  m4/extensions.m4
  m4/fchdir.m4
  m4/fclose.m4
  m4/fcntl-o.m4
  m4/fcntl.m4
  m4/fcntl_h.m4
  m4/fdopendir.m4
  m4/fflush.m4
  m4/filenamecat.m4
  m4/fnmatch.m4
  m4/fpurge.m4
  m4/freading.m4
  m4/fseeko.m4
  m4/ftello.m4
  m4/futimens.m4
  m4/getcwd.m4
  m4/getdtablesize.m4
  m4/getlogin_r.m4
  m4/gettime.m4
  m4/gettimeofday.m4
  m4/glibc21.m4
  m4/glob.m4
  m4/gnulib-common.m4
  m4/include_next.m4
  m4/lchown.m4
  m4/lib-ld.m4
  m4/lib-link.m4
  m4/lib-prefix.m4
  m4/localcharset.m4
  m4/locale-fr.m4
  m4/locale-ja.m4
  m4/locale-zh.m4
  m4/lock.m4
  m4/longlong.m4
  m4/lseek.m4
  m4/lstat.m4
  m4/malloc.m4
  m4/mbrtowc.m4
  m4/mbsinit.m4
  m4/mbsrtowcs.m4
  m4/mbstate_t.m4
  m4/memchr.m4
  m4/mempcpy.m4
  m4/memrchr.m4
  m4/mkdir.m4
  m4/mkdtemp.m4
  m4/mmap-anon.m4
  m4/mode_t.m4
  m4/multiarch.m4
  m4/onceonly.m4
  m4/open.m4
  m4/openat.m4
  m4/realloc.m4
  m4/rmdir.m4
  m4/save-cwd.m4
  m4/stat-time.m4
  m4/stat.m4
  m4/stdbool.m4
  m4/stddef_h.m4
  m4/stdint.m4
  m4/stdio_h.m4
  m4/stdlib_h.m4
  m4/strdup.m4
  m4/strerror.m4
  m4/strerror_r.m4
  m4/string_h.m4
  m4/sys_stat_h.m4
  m4/sys_time_h.m4
  m4/tempname.m4
  m4/threadlib.m4
  m4/time_h.m4
  m4/timespec.m4
  m4/unistd-safer.m4
  m4/unistd_h.m4
  m4/unlink.m4
  m4/utimbuf.m4
  m4/utimens.m4
  m4/utimensat.m4
  m4/utimes.m4
  m4/warn-on-use.m4
  m4/wchar_h.m4
  m4/wchar_t.m4
  m4/wctype_h.m4
  m4/wint_t.m4
])
