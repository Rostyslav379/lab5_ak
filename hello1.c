#include <hello1.h>

MODULE_AUTHOR("Karpenko Rostyslav <dfttime@ukr.net>");
MODULE_DESCRIPTION("Lab4 Module hello2.c");
MODULE_LICENSE("Dual BSD/GPL");

struct myStruct {
    struct list_head list;
    ktime_t startTime;
    ktime_t finishTime;
};

static LIST_HEAD(myList);
int counter;

int print_hello(uint paramValue)
{
    if (paramValue > 10) {
   	 pr_err("Error: paramValue cannot be greater than 10\n");
   	 return -EINVAL;
    }

    if (paramValue == 0 || (paramValue <= 10 && paramValue >= 5)) {
   	 pr_emerg("Warning: %u\n", paramValue);
    }

    counter = 0;
    while (counter != paramValue) {
   	 struct myStruct *ptr = kmalloc(sizeof(*ptr), GFP_KERNEL); 
   	 ptr->startTime = ktime_get();
   	 pr_emerg("Hello world!\n");
   	 ptr->finishTime = ktime_get();
   	 list_add_tail(&ptr->list, &myList);
   	 counter += 1;
    }
    return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    return 0;
}

static void __exit hello1_exit(void)
{
    struct myStruct *ptr, *next;

    list_for_each_entry_safe(ptr, next, &myList, list) {
   	 pr_emerg("Time in nanoseconds: %lld\n", ptr-> finishTime - ptr->startTime);
   	 list_del(&ptr->list);
   	 kfree(ptr);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);
