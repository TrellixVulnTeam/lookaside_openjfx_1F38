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

#ifndef __G_RAND_H__
#define __G_RAND_H__

#include <glib/gtypes.h>

G_BEGIN_DECLS

typedef struct _GRand           GRand;

/* GRand - a good and fast random number generator: Mersenne Twister
 * see http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html for more info.
 * The range functions return a value in the intervall [begin, end).
 * int          -> [0..2^32-1]
 * int_range    -> [begin..end-1]
 * double       -> [0..1)
 * double_range -> [begin..end)
 */

GRand*  g_rand_new_with_seed  (guint32  seed);
GRand*  g_rand_new_with_seed_array (const guint32 *seed,
                    guint seed_length);
GRand*  g_rand_new            (void);
void    g_rand_free           (GRand   *rand_);
GRand*  g_rand_copy           (GRand   *rand_);
void    g_rand_set_seed       (GRand   *rand_,
                   guint32  seed);
void    g_rand_set_seed_array (GRand   *rand_,
                   const guint32 *seed,
                   guint    seed_length);

#define g_rand_boolean(rand_) ((g_rand_int (rand_) & (1 << 15)) != 0)

guint32 g_rand_int            (GRand   *rand_);
gint32  g_rand_int_range      (GRand   *rand_,
                   gint32   begin,
                   gint32   end);
gdouble g_rand_double         (GRand   *rand_);
gdouble g_rand_double_range   (GRand   *rand_,
                   gdouble  begin,
                   gdouble  end);
void    g_random_set_seed     (guint32  seed);

#define g_random_boolean() ((g_random_int () & (1 << 15)) != 0)

guint32 g_random_int          (void);
gint32  g_random_int_range    (gint32   begin,
                   gint32   end);
gdouble g_random_double       (void);
gdouble g_random_double_range (gdouble  begin,
                   gdouble  end);


G_END_DECLS

#endif /* __G_RAND_H__ */
