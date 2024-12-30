#include "vga.h"
int strlen (char str[])
{
        int i = 0;
        do{
                i++;
        } while (str[i] != 0);
        return i;
}

int size_of (int array[])
{
        int i = 0;
        do {
                i++;
        } while (array[i]!=0);
        return i;
}


int int_to_ascii_buff (int nb, char str[])
{
        int i = 0;
        if (nb<0) {
                return 1;
        }

        do {
                str[i] = (nb % 10) + '0';
                nb= nb / 10;
                i++;
        } while (nb != 0);
        //last char not initialized yet
        str[i] = '\0';
        // i contain size of str
        for (int j = 0, k = i - 1; j < k; j++, k--) {
                char tmp = str[j];
                str[j] = str[k];
                str[k] = tmp;
        }
        return 0;
}
