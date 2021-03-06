/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef ARCH_MIPS_EMU_FILE_H
#define ARCH_MIPS_EMU_FILE_H

#include <stdio.h>


enum mips_file_desc_kind_t
{
	mips_file_desc_invalid = 0,
	mips_file_desc_regular,  /* Regular mips_file */
	mips_file_desc_std,  /* Standard input or output */
	mips_file_desc_pipe,  /* A pipe */
	mips_file_desc_virtual,  /* A virtual mips_file with artificial contents */
	mips_file_desc_gpu,  /* GPU device */
	mips_file_desc_socket  /* Network socket */
};

struct mips_file_desc_t
{
	enum mips_file_desc_kind_t kind;  /* File type */
	int guest_fd;  /* Guest mips_file descriptor id */
	int host_fd;  /* Equivalent open host mips_file */
	int flags;  /* O_xxx flags */
	char *path;  /* Associated path if applicable */
};


/* File descriptor table */
struct mips_file_desc_table_t
{
	/* Number of extra contexts sharing table */
	int num_links;

	/* List of descriptors */
	struct list_t *mips_file_desc_list;
};


struct mips_file_desc_table_t *mips_file_desc_table_create(void);
void mips_file_desc_table_free(struct mips_file_desc_table_t *table);

struct mips_file_desc_table_t *mips_file_desc_table_link(struct mips_file_desc_table_t *table);
void mips_file_desc_table_unlink(struct mips_file_desc_table_t *table);

void mips_file_desc_table_dump(struct mips_file_desc_table_t *table, FILE *f);

struct mips_file_desc_t *mips_file_desc_table_entry_get(struct mips_file_desc_table_t *table, int index);
struct mips_file_desc_t *mips_file_desc_table_entry_new(struct mips_file_desc_table_t *table,
	enum mips_file_desc_kind_t kind, int host_fd, char *path, int flags);
struct mips_file_desc_t *mips_file_desc_table_entry_new_guest_fd(struct mips_file_desc_table_t *table,
        enum mips_file_desc_kind_t kind, int guest_fd, int host_fd, char *path, int flags);
void mips_file_desc_table_entry_free(struct mips_file_desc_table_t *table, int index);
void mips_file_desc_table_entry_dump(struct mips_file_desc_table_t *table, int index, FILE *f);

int mips_file_desc_table_get_host_fd(struct mips_file_desc_table_t *table, int guest_fd);
int mips_file_desc_table_get_guest_fd(struct mips_file_desc_table_t *table, int host_fd);


#endif
