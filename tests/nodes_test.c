#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include "nodes.h"

void int_literal_test(void)
{
    opal_parse_string("1\n");
}


int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/nodes/int_literal", int_literal_test);
    return g_test_run();
}
