/*
** TRISTAN GORY, 2022
** lib-c-av-parser
** File description:
** header of the parser
*/

#ifndef PARSER_H_
#   define PARSER_H_
#   include <stdint.h>
#   include <stdbool.h>
#   include <stdio.h>
#   include <stdlib.h>
#   include <stddef.h>
#   include <string.h>

/**
 *  \struct parser argument entry
 *
 *  \brief Structure that represents an argument entry.
 * \var opt: Option name (such as -h)
 * \var long_opt: Long option name (such as --help)
 * \var help: Help message
 * \var type_info: A string that describes the type of the argument
 * \var args_needed: a boolean that indicates if the argument is mandatory after the option
 */
struct avparser_entry {
    const char *opt;
    const char *opt_long;
    const char *help;
    const char *type_info;
    int (*handler)(void *user_data, char **arg, int argc);
    bool args_needed;
};

/**
 *  \struct avparser, a container for the parser context
 *
 * \brief Structure that represents the parser context.
 * \var program_name: The name of the program
 * \var entries: An array of entries
 * \var entries_size: The size of the entries array
 * \var user_data: A pointer to the user data
 */
struct avparser_context {
    const char *program_name;
    const struct avparser_entry *entries;
    size_t entries_size;
    void *user_data;
};

#define AVPARSER_DEFAULT_HELP_HANDLER ((int (*)(void *user_data, char **arg, int argc))-1)

int avparse(int ac, char **av, const struct avparser_context *context);

#endif /* !PARSER_H_ */
