/*
 * mime.h : GeeXboX uShare media file MIME-type association header.
 * Originally developped for the GeeXboX project.
 * Copyright (C) 2005-2007 Benjamin Zores <ben@geexbox.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _MIME_H_
#define _MIME_H_

struct mime_type_t {
  char *extension;
  char *mime_class;
  char *mime_protocol;
};
#ifdef WIN32
extern const struct mime_type_t MIME_Type_List[];
#else
extern const struct mime_type_t MIME_Type_List[];
#endif
char *mime_get_protocol (struct mime_type_t *mime);

#endif /* _MIME_H */
