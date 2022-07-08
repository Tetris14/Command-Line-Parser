/*
** TRISTAN GORY PROJECT, 2022
** lib-c-argv-parser
** File description:
** create
*/

#   include <string.h>
#   include "avparser.h"
#   define ERR_LOG( ... ) fprintf(stderr, __VA_ARGS__)
#   define LOG( ... ) fprintf(stdout, __VA_ARGS__)

static void avparser_display_help(const struct avparser_context *context)
{
    LOG("USAGE: %s [OPTIONS]\n", context->program_name);
    for (size_t i = 0; i < context->entries_size; ++i) {
        LOG("\n %s", context->entries[i].opt);
        if (context->entries[i].opt_long != NULL) {
            LOG(", %s", context->entries[i].opt_long);
        }
        if (context->entries[i].type_info != NULL) {
            LOG(" [%s]\n", context->entries[i].type_info);
        }
        else {
            LOG("\n");
        }
        LOG("\t%s\n", context->entries[i].help);
    }
}

static bool is_opt_valid(const struct avparser_entry *entry, const char *arg)
{
    return (strcmp(arg, entry->opt) == 0 || strcmp(arg, entry->opt_long) == 0);
}

static int handle_arguments_entry(int ac, char **av, const struct avparser_entry *entry, const struct avparser_context *context)
{
    int ret;

    if (entry->args_needed && ac == 1) {
        ERR_LOG("Option: '%s' needs  an argument\n", av[0]);
        return (1);
    } else if (entry->handler == AVPARSER_DEFAULT_HELP_HANDLER) {
        avparser_display_help(context);
        return (1);
    } else if (entry->handler != NULL) {
        ret = entry->handler(context->user_data, av, ac);
        if (ret != 0)
            ERR_LOG("Invalid parameter after '%s' option\n", av[0]);
        return (ret);
    }
    return (0);
}

static int check_opt(int ac, char **av, const struct avparser_context *context)
{
    for (size_t i = 0; i < context->entries_size; ++i) {
        if (is_opt_valid(&context->entries[i], av[0])) {
            return handle_arguments_entry(ac, av, &context->entries[i], context);
        }
    }
    ERR_LOG("Unknown param: '%s'.\n", av[0]);
    return (1);
}

int avparse(int ac, char **av, const struct avparser_context *context)
{
    int ret = 0;
    int check;

    for (int i = 0; i < ac; ++i) {
        if (av[i][0] == '-') {
            check = check_opt(ac - i, &av[i], context);
            if (check < 0) {
                return (check);
            }
            ret += check;
        }
    }
    return (ret);
}