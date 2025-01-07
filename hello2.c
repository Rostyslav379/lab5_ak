#include <hello1.h>

MODULE_AUTHOR("Karpenko Rostyslav <dfttime@ukr.net>");
MODULE_DESCRIPTION("Lab4 Module hello2.c");
MODULE_LICENSE("Dual BSD/GPL");

static uint paramValue = 1;
module_param(paramValue, uint, 0444);
MODULE_PARM_DESC(paramValue, "My description");

static int __init hello2_init(void)
{
    pr_emerg("Calling print_hello() from hello2...\n");
    print_hello(paramValue);
    return 0;
}

static void __exit hello2_exit(void)
{
}

module_init(hello2_init);
module_exit(hello2_exit);
