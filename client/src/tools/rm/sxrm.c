/*
 *  Copyright (C) 2012-2014 Skylable Ltd. <info-copyright@skylable.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Special exception for linking this software with OpenSSL:
 *
 *  In addition, as a special exception, Skylable Ltd. gives permission to
 *  link the code of this program with the OpenSSL library and distribute
 *  linked combinations including the two. You must obey the GNU General
 *  Public License in all respects for all of the code used other than
 *  OpenSSL. You may extend this exception to your version of the program,
 *  but you are not obligated to do so. If you do not wish to do so, delete
 *  this exception statement from your version.
 */

#include "default.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "sx.h"
#include "cmdline.h"
#include "version.h"
#include "libsxclient/src/misc.h"
#include "bcrumbs.h"

static sxc_client_t *sx = NULL;

static void sighandler(int signal)
{
    if(sx)
	sxc_shutdown(sx, signal);
    fprintf(stderr, "Process interrupted\n");
    exit(1);
}


int main(int argc, char **argv) {
    sxc_client_t *sx;
    int ret = 0;
    unsigned int i;
    struct gengetopt_args_info args;
    char *filter_dir;
    sxc_logger_t log;
    sxc_cluster_t *cluster = NULL;
    sxc_file_list_t *lst = NULL;

    if(cmdline_parser(argc, argv, &args))
	exit(1);

    if(args.version_given) {
	printf("%s %s\n", CMDLINE_PARSER_PACKAGE, SRC_VERSION);
	cmdline_parser_free(&args);
	exit(0);
    }

    if(!args.inputs_num) {
	cmdline_parser_print_help();
	printf("\n");
	fprintf(stderr, "ERROR: Wrong number of arguments\n");
	cmdline_parser_free(&args);
	exit(1);
    }

    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);

    if(!(sx = sxc_init(SRC_VERSION, sxc_default_logger(&log, argv[0]), sxc_input_fn, NULL))) {
	cmdline_parser_free(&args);
	return 1;
    }

    if(args.config_dir_given && sxc_set_confdir(sx, args.config_dir_arg)) {
        fprintf(stderr, "ERROR: Could not set configuration directory %s: %s\n", args.config_dir_arg, sxc_geterrmsg(sx));
        cmdline_parser_free(&args);
        return 1;
    }
    sxc_set_verbose(sx, args.verbose_flag);
    sxc_set_debug(sx, args.debug_flag);

    if(args.filter_dir_given) {
	filter_dir = strdup(args.filter_dir_arg);
    } else {
	const char *pt = sxi_getenv("SX_FILTER_DIR");
	if(pt)
	    filter_dir = strdup(pt);
	else
	    filter_dir = strdup(SX_FILTER_DIR);
    }
    if(!filter_dir) {
	fprintf(stderr, "ERROR: Failed to set filter dir\n");
	cmdline_parser_free(&args);
        sxc_shutdown(sx, 0);
	return 1;
    }
    if(sxc_filter_loadall(sx, filter_dir)) {
	fprintf(stderr, "WARNING: Failed to load filters: %s\n", sxc_geterrmsg(sx));
	sxc_clearerr(sx);
    }
    free(filter_dir);

    lst = sxc_file_list_new(sx, args.recursive_given);
    for(i = 0; lst && i < args.inputs_num; i++) {
        const char *url = args.inputs[i];
        sxc_file_t *target = sxc_file_from_url(sx, &cluster, url);
        if (!target) {
	    sxc_uri_t *u = NULL;
            fprintf(stderr, "ERROR: Can't process URL '%s': %s\n", url, sxc_geterrmsg(sx));
	    if(strstr(sxc_geterrmsg(sx), SXBC_TOOLS_CFG_ERR)) {
		u = sxc_parse_uri(sx, url);
		if(u)
		    fprintf(stderr, SXBC_TOOLS_CFG_MSG, u->host, u->profile ? u->profile : "", u->profile ? "@" : "", u->host);
	    } else if(strstr(sxc_geterrmsg(sx), SXBC_TOOLS_CONN_ERR)) {
                fprintf(stderr, SXBC_TOOLS_CONN_MSG);
	    } else if(strstr(sxc_geterrmsg(sx), SXBC_TOOLS_CERT_ERR)) {
		u = sxc_parse_uri(sx, url);
		if(u)
		    fprintf(stderr, SXBC_TOOLS_CERT_MSG, u->profile ? u->profile : "", u->profile ? "@" : "", u->host);
	    } else if(strstr(sxc_geterrmsg(sx), SXBC_TOOLS_INVALIDPROF_ERR)) {
		fprintf(stderr, SXBC_TOOLS_INVALIDPROF_MSG);
	    }
	    sxc_free_uri(u);
            ret = 1;
            break;
        }
        if (!sxc_file_is_sx(target)) {
            fprintf(stderr, "WARNING: Will not remove local file '%s'\n", url);
            ret = 1;
        }
        if (sxc_file_list_add(lst, target, 1)) {
            fprintf(stderr, "ERROR: Cannot add file list entry '%s': %s\n", url, sxc_geterrmsg(sx));
            ret = 1;
            sxc_file_free(target);
        }
    }
    if (sxc_rm(lst, args.ignore_errors_flag, args.mass_given)) {
        fprintf(stderr, "ERROR: Failed to remove file(s): %s\n", sxc_geterrmsg(sx));
	if(cluster && strstr(sxc_geterrmsg(sx), SXBC_TOOLS_VOL_ERR))
	    fprintf(stderr, SXBC_TOOLS_VOL_MSG, "", "", sxc_cluster_get_sslname(cluster));
	else if(strstr(sxc_geterrmsg(sx), SXBC_TOOLS_RMVOL_ERR)) {
	    /* only check the first argument */
	    sxc_uri_t *u = sxc_parse_uri(sx, args.inputs[0]);
	    if(u) {
		if(!u->path)
		    fprintf(stderr, SXBC_TOOLS_RMVOL_MSG, u->profile ? u->profile : "", u->profile ? "@" : "", u->host, u->volume);
		sxc_free_uri(u);
	    }
	}
        ret = 1;
    }
    if(args.mass_given)
        printf("Deleted %d batch(es) of files\n", sxc_file_list_get_successful(lst));
    else
        printf("Deleted %d file(s)\n", sxc_file_list_get_successful(lst));

    sxc_file_list_free(lst);
    sxc_cluster_free(cluster);

    cmdline_parser_free(&args);
    sxc_shutdown(sx, 0);
    return ret;
}
