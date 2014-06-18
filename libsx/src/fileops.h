/*
 *  Copyright (C) 2012-2014 Skylable Ltd. <info-copyright@skylable.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef __FILEOPS_H
#define __FILEOPS_H

#include "default.h"
#include <sys/types.h>

#include "sx.h"

struct file_upload_ctx;
struct host_upload_ctx;
struct file_download_ctx;

/* Set information about current transfer download value */
int sxi_file_download_set_xfer_stat(struct file_download_ctx* ctx, int64_t downloaded, int64_t to_download);
/* Get numner of bytes to be downloaded */
int64_t sxi_file_download_get_xfer_to_send(const struct file_download_ctx *ctx);
/* Get number of bytes already downloaded */
int64_t sxi_file_download_get_xfer_sent(const struct file_download_ctx *ctx);

/* Set information about current transfer upload value */
int sxi_host_upload_set_xfer_stat(struct host_upload_ctx* ctx, int64_t uploaded, int64_t to_upload);
/* Get numner of bytes to be downloaded */
int64_t sxi_host_upload_get_xfer_to_send(const struct host_upload_ctx *ctx);
/* Get number of bytes already downloaded */
int64_t sxi_host_upload_get_xfer_sent(const struct host_upload_ctx *ctx);

#endif