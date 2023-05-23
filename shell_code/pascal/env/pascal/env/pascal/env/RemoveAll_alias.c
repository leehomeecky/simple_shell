#include "shell.h"

void __attribute__((constructor)) Removeall_alias() {
    const char* filename = "/root/aliases.txt";
    int fileDescriptor = open(filename, O_WRONLY | O_TRUNC);
    
    if (fileDescriptor == -1) {
    /*    _puts("Failed to open the file.\n");*/
        return;
    }
    
    if (close(fileDescriptor) == -1)
    {
     /*   _puts("Failed to close the file.\n");*/
        return;
    }
    
  /*  _puts("File truncated successfully.\n");*/
}
