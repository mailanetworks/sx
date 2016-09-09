/** @file cmd_node.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.6
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef CMD_NODE_H
#define CMD_NODE_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NODE_CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define NODE_CMDLINE_PARSER_PACKAGE "sxadm"
#endif

#ifndef NODE_CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#define NODE_CMDLINE_PARSER_PACKAGE_NAME "sxadm"
#endif

#ifndef NODE_CMDLINE_PARSER_VERSION
/** @brief the program version */
#define NODE_CMDLINE_PARSER_VERSION VERSION
#endif

/** @brief Where the command line options are stored */
struct node_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *full_help_help; /**< @brief Print help, including hidden options, and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  const char *new_help; /**< @brief Creates a new local SX node in STORAGE_PATH help description.  */
  const char *info_help; /**< @brief Print details about the local node in STORAGE_PATH help description.  */
  const char *check_help; /**< @brief Perform sanity check on the local node in STORAGE_PATH help description.  */
  char * extract_arg;	/**< @brief Extract all files from the local node in STORAGE_PATH to DESTPATH.  */
  char * extract_orig;	/**< @brief Extract all files from the local node in STORAGE_PATH to DESTPATH original value given at command line.  */
  const char *extract_help; /**< @brief Extract all files from the local node in STORAGE_PATH to DESTPATH help description.  */
  char * rename_cluster_arg;	/**< @brief Set a new name for an SX cluster.  */
  char * rename_cluster_orig;	/**< @brief Set a new name for an SX cluster original value given at command line.  */
  const char *rename_cluster_help; /**< @brief Set a new name for an SX cluster help description.  */
  const char *upgrade_help; /**< @brief Upgrade a node to new SX version help description.  */
  const char *upgrade_job_help; /**< @brief Run the upgrade job directly help description.  */
  const char *compact_help; /**< @brief Compact the node data freeing up any allocated but unused storage space help description.  */
  const char *gc_help; /**< @brief Run GC on node immediately help description.  */
  const char *gc_expire_help; /**< @brief Run GC on node and expire its reservations immediately help description.  */
  const char *unbump_wait_help; /**< @brief Wait for active unbumps to complete help description.  */
  const char *warm_cache_help; /**< @brief Warm DB caches help description.  */
  const char *vacuum_help; /**< @brief Vacuum help description.  */
  const char *get_definition_help; /**< @brief Print node definition in 'cluster --mod' format help description.  */
  char * cluster_key_arg;	/**< @brief File containing a pre-generated cluster authentication token or stdin if \"-\" is given (default autogenerate token)..  */
  char * cluster_key_orig;	/**< @brief File containing a pre-generated cluster authentication token or stdin if \"-\" is given (default autogenerate token). original value given at command line.  */
  const char *cluster_key_help; /**< @brief File containing a pre-generated cluster authentication token or stdin if \"-\" is given (default autogenerate token). help description.  */
  char * cluster_uuid_arg;	/**< @brief The SX cluster UUID (default autogenerate UUID)..  */
  char * cluster_uuid_orig;	/**< @brief The SX cluster UUID (default autogenerate UUID). original value given at command line.  */
  const char *cluster_uuid_help; /**< @brief The SX cluster UUID (default autogenerate UUID). help description.  */
  const char *batch_mode_help; /**< @brief Turn off interactive confirmations, progress notifications and assume yes for all questions help description.  */
  int human_readable_flag;	/**< @brief Print human readable sizes (default=off).  */
  const char *human_readable_help; /**< @brief Print human readable sizes help description.  */
  int debug_flag;	/**< @brief Enable debug messages (default=off).  */
  const char *debug_help; /**< @brief Enable debug messages help description.  */
  char * owner_arg;	/**< @brief Set ownership of storage to user[:group].  */
  char * owner_orig;	/**< @brief Set ownership of storage to user[:group] original value given at command line.  */
  const char *owner_help; /**< @brief Set ownership of storage to user[:group] help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int full_help_given ;	/**< @brief Whether full-help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int new_given ;	/**< @brief Whether new was given.  */
  unsigned int info_given ;	/**< @brief Whether info was given.  */
  unsigned int check_given ;	/**< @brief Whether check was given.  */
  unsigned int extract_given ;	/**< @brief Whether extract was given.  */
  unsigned int rename_cluster_given ;	/**< @brief Whether rename-cluster was given.  */
  unsigned int upgrade_given ;	/**< @brief Whether upgrade was given.  */
  unsigned int upgrade_job_given ;	/**< @brief Whether upgrade-job was given.  */
  unsigned int compact_given ;	/**< @brief Whether compact was given.  */
  unsigned int gc_given ;	/**< @brief Whether gc was given.  */
  unsigned int gc_expire_given ;	/**< @brief Whether gc-expire was given.  */
  unsigned int unbump_wait_given ;	/**< @brief Whether unbump-wait was given.  */
  unsigned int warm_cache_given ;	/**< @brief Whether warm-cache was given.  */
  unsigned int vacuum_given ;	/**< @brief Whether vacuum was given.  */
  unsigned int get_definition_given ;	/**< @brief Whether get-definition was given.  */
  unsigned int cluster_key_given ;	/**< @brief Whether cluster-key was given.  */
  unsigned int cluster_uuid_given ;	/**< @brief Whether cluster-uuid was given.  */
  unsigned int batch_mode_given ;	/**< @brief Whether batch-mode was given.  */
  unsigned int human_readable_given ;	/**< @brief Whether human-readable was given.  */
  unsigned int debug_given ;	/**< @brief Whether debug was given.  */
  unsigned int owner_given ;	/**< @brief Whether owner was given.  */

  char **inputs ; /**< @brief unamed options (options without names) */
  unsigned inputs_num ; /**< @brief unamed options number */
  int MODE_group_counter; /**< @brief Counter for group MODE */
} ;

/** @brief The additional parameters to pass to parser functions */
struct node_cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure node_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure node_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *node_args_info_purpose;
/** @brief the usage string of the program */
extern const char *node_args_info_usage;
/** @brief the description string of the program */
extern const char *node_args_info_description;
/** @brief all the lines making the help output */
extern const char *node_args_info_help[];
/** @brief all the lines making the full help output (including hidden options) */
extern const char *node_args_info_full_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int node_cmdline_parser (int argc, char **argv,
  struct node_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use node_cmdline_parser_ext() instead
 */
int node_cmdline_parser2 (int argc, char **argv,
  struct node_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int node_cmdline_parser_ext (int argc, char **argv,
  struct node_args_info *args_info,
  struct node_cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int node_cmdline_parser_dump(FILE *outfile,
  struct node_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int node_cmdline_parser_file_save(const char *filename,
  struct node_args_info *args_info);

/**
 * Print the help
 */
void node_cmdline_parser_print_help(void);
/**
 * Print the full help (including hidden options)
 */
void node_cmdline_parser_print_full_help(void);
/**
 * Print the version
 */
void node_cmdline_parser_print_version(void);

/**
 * Initializes all the fields a node_cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void node_cmdline_parser_params_init(struct node_cmdline_parser_params *params);

/**
 * Allocates dynamically a node_cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized node_cmdline_parser_params structure
 */
struct node_cmdline_parser_params *node_cmdline_parser_params_create(void);

/**
 * Initializes the passed node_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void node_cmdline_parser_init (struct node_args_info *args_info);
/**
 * Deallocates the string fields of the node_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void node_cmdline_parser_free (struct node_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int node_cmdline_parser_required (struct node_args_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CMD_NODE_H */
