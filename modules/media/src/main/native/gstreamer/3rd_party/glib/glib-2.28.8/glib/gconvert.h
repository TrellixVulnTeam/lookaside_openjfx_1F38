/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#if defined(G_DISABLE_SINGLE_INCLUDES) && !defined (__GLIB_H_INSIDE__) && !defined (GLIB_COMPILATION)
#error "Only <glib.h> can be included directly."
#endif

#ifndef __G_CONVERT_H__
#define __G_CONVERT_H__

#include <glib/gerror.h>

G_BEGIN_DECLS

/**
 * GConvertError:
 * @G_CONVERT_ERROR_NO_CONVERSION: Conversion between the requested character
 *     sets is not supported.
 * @G_CONVERT_ERROR_ILLEGAL_SEQUENCE: Invalid byte sequence in conversion input.
 * @G_CONVERT_ERROR_FAILED: Conversion failed for some reason.
 * @G_CONVERT_ERROR_PARTIAL_INPUT: Partial character sequence at end of input.
 * @G_CONVERT_ERROR_BAD_URI: URI is invalid.
 * @G_CONVERT_ERROR_NOT_ABSOLUTE_PATH: Pathname is not an absolute path.
 *
 * Error codes returned by character set conversion routines.
 */
typedef enum
{
  G_CONVERT_ERROR_NO_CONVERSION,
  G_CONVERT_ERROR_ILLEGAL_SEQUENCE,
  G_CONVERT_ERROR_FAILED,
  G_CONVERT_ERROR_PARTIAL_INPUT,
  G_CONVERT_ERROR_BAD_URI,
  G_CONVERT_ERROR_NOT_ABSOLUTE_PATH
} GConvertError;

/**
 * G_CONVERT_ERROR:
 *
 * Error domain for character set conversions. Errors in this domain will
 * be from the #GConvertError enumeration. See #GError for information on
 * error domains.
 */
#define G_CONVERT_ERROR g_convert_error_quark()
GQuark g_convert_error_quark (void);

/**
 * GIconv:
 *
 * The <structname>GIConv</structname> struct wraps an
 * iconv() conversion descriptor. It contains private data
 * and should only be accessed using the following functions.
 */
typedef struct _GIConv *GIConv;

GIConv g_iconv_open   (const gchar  *to_codeset,
               const gchar  *from_codeset);
gsize  g_iconv        (GIConv        converter,
               gchar       **inbuf,
               gsize        *inbytes_left,
               gchar       **outbuf,
               gsize        *outbytes_left);
gint   g_iconv_close  (GIConv        converter);


gchar* g_convert               (const gchar  *str,
                gssize        len,
                const gchar  *to_codeset,
                const gchar  *from_codeset,
                gsize        *bytes_read,
                gsize        *bytes_written,
                GError      **error) G_GNUC_MALLOC;
gchar* g_convert_with_iconv    (const gchar  *str,
                gssize        len,
                GIConv        converter,
                gsize        *bytes_read,
                gsize        *bytes_written,
                GError      **error) G_GNUC_MALLOC;
gchar* g_convert_with_fallback (const gchar  *str,
                gssize        len,
                const gchar  *to_codeset,
                const gchar  *from_codeset,
                const gchar  *fallback,
                gsize        *bytes_read,
                gsize        *bytes_written,
                GError      **error) G_GNUC_MALLOC;


/* Convert between libc's idea of strings and UTF-8.
 */
gchar* g_locale_to_utf8   (const gchar  *opsysstring,
               gssize        len,
               gsize        *bytes_read,
               gsize        *bytes_written,
               GError      **error) G_GNUC_MALLOC;
gchar* g_locale_from_utf8 (const gchar  *utf8string,
               gssize        len,
               gsize        *bytes_read,
               gsize        *bytes_written,
               GError      **error) G_GNUC_MALLOC;

/* Convert between the operating system (or C runtime)
 * representation of file names and UTF-8.
 */
#ifndef __GTK_DOC_IGNORE__
#ifdef G_OS_WIN32
#define g_filename_to_utf8 g_filename_to_utf8_utf8
#define g_filename_from_utf8 g_filename_from_utf8_utf8
#define g_filename_from_uri g_filename_from_uri_utf8
#define g_filename_to_uri g_filename_to_uri_utf8
#endif
#endif

gchar* g_filename_to_utf8   (const gchar  *opsysstring,
                 gssize        len,
                 gsize        *bytes_read,
                 gsize        *bytes_written,
                 GError      **error) G_GNUC_MALLOC;
gchar* g_filename_from_utf8 (const gchar  *utf8string,
                 gssize        len,
                 gsize        *bytes_read,
                 gsize        *bytes_written,
                 GError      **error) G_GNUC_MALLOC;

gchar *g_filename_from_uri (const gchar *uri,
                gchar      **hostname,
                GError     **error) G_GNUC_MALLOC;

gchar *g_filename_to_uri   (const gchar *filename,
                const gchar *hostname,
                GError     **error) G_GNUC_MALLOC;
gchar *g_filename_display_name (const gchar *filename) G_GNUC_MALLOC;
gboolean g_get_filename_charsets (G_CONST_RETURN gchar ***charsets);

gchar *g_filename_display_basename (const gchar *filename) G_GNUC_MALLOC;

gchar **g_uri_list_extract_uris (const gchar *uri_list) G_GNUC_MALLOC;

G_END_DECLS

#endif /* __G_CONVERT_H__ */
