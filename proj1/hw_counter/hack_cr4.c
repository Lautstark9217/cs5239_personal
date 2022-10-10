#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>

#define MOD_TAG "haccah: "

/*
 *  print_cr4 - prints the value stored in CR4
 *      @info: passed by on_each_cpu()
 */
static void 
print_cr4(void *info)
{
    unsigned long cr4_val;

    asm volatile (
        ".intel_syntax;"
        "mov    %0, %%cr4;"
        ".att_syntax;"
        : "=r"(cr4_val));
    
    pr_info(MOD_TAG"CR4=%lx on core #%d\n", cr4_val, smp_processor_id());
}

/*
 *  set_pce - sets Performance-monitoring Counter Enable bit in CR4
 *      @info: passed by on_each_cpu()
 */
static void
set_pce(void *info)
{
    pr_info(MOD_TAG"Setting PCE on core #%d\n", smp_processor_id());

    asm volatile (
        ".intel_syntax;"
        "push   %rax;"
        "mov    %rax, %cr4;"
        "or     %rax, 0x100;"
        "mov    %cr4, %rax;"
        "pop    %rax;"
        ".att_syntax;");
}

/*
 *  clear_pce - clears Performance-monitoring Counter Enable bit in CR4
 *      @info: passed by on_each_cpu()
 */
static void
clear_pce(void *info)
{
    pr_info(MOD_TAG"Clearing PCE on core #%d\n", smp_processor_id());

    asm volatile (
        ".intel_syntax;"
        "push   %rax;"
        "push   %rbx;"
        "mov    %rax, %cr4;"
        "mov    %rbx, 0x100;"
        "not    %rbx;"
        "and    %rax, %rbx;"
        "mov    %cr4, %rax;"
        "pop    %rbx;"
        "pop    %rax;"
        ".att_syntax;");
}

/*
 *  mod_init - module entry point
 *      @return: status (if not 0, module not loaded)
 */
static int __init 
mod_init(void)
{
    pr_info(MOD_TAG"=======================\n");

    on_each_cpu(print_cr4, NULL, 0);
    on_each_cpu(set_pce,   NULL, 0);
    on_each_cpu(print_cr4, NULL, 0);

    return 0;
}

/*
 *  mod_exit - module exit point
 */
static void __exit
mod_exit(void)
{
    pr_info(MOD_TAG"=======================\n");

    on_each_cpu(print_cr4, NULL, 0);
    on_each_cpu(clear_pce, NULL, 0);
    on_each_cpu(print_cr4, NULL, 0);
}

module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");