#include "./include/avparser.h"

struct params {
    unsigned int fps;
    char *name;
};

static int fps_handler(void *userdata, char **av, int ac)
{
    struct params *p = userdata;
    int fps;
    int ret = sscanf(av[1], "%u", &fps);

    return ret == 1 ? 0 : 1;
}

static int name_handler(void *userdata, char **av, int ac)
{
    struct params *p = userdata;
    char *s = strdup(av[1]);

    if (s == NULL) {
        return (-1);
    }
    p->name = s;
    return (0);
}

static const struct avparser_entry MAIN_OPTIONS[] = {
    {
        .opt = "-h",
        .opt_long = "--help",
        .help = "Display toto",
        .type_info = NULL,
        .args_needed = false,
        .handler = AVPARSER_DEFAULT_HELP_HANDLER,
    },
    {
        .opt = "-f",
        .opt_long = "--fps",
        .help = "Set the def framerate zozo",
        .type_info = "INTEGER",
        .args_needed = true,
        .handler = &fps_handler,
    },
    {
        .opt = "-n",
        .opt_long = "--name",
        .help = "Set zozo",
        .type_info = "STRING",
        .args_needed = true,
        .handler = &name_handler,
    }
};

int main(int ac, char **av)
{
    struct params p = {
        .fps = 30,
        .name = strdup("Tristan")
    };
    const struct avparser_context parser = {
        .entries = MAIN_OPTIONS,
        .entries_size = sizeof(MAIN_OPTIONS) / sizeof(*MAIN_OPTIONS),
        .program_name = av[0],
        .user_data = &p,
    };
    int ret = avparse(ac - 1, av + 1, &parser);
    printf("ret: %d\n", ret);
    printf("fps: %u, name: %s\n", p.fps, p.name);
    free(p.name);
    return (0);
}