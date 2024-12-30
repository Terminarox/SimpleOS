int busy_wait(unsigned int sec)
{
        unsigned int i;
        unsigned int j;
        for (i = 0; i < sec; i++) {
                for (j = 0; j < 100000000; j++) {
                        __asm__ __volatile__("nop");
                }
        }
        return 0;
}
/* busy_wait is not accurate and seems to be take a little more time than asked */
