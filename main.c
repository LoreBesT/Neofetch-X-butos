#include <stdio.h> //non supportata direttamente da butos. I comandi vanno modificati con quelli delle call di butos
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
//Le librerie non sono tutte necessarie. Sono state importate solo le 4 supportate
#include <syscalls.h> //commentare su macchina virtuale con kernel linux

#define RED "\e[0;31m"
#define RESET "\e[0m"

// Funzione per ottenere le informazioni sulla CPU tramite CPUID
void get_processor_version(char *vendor, char *brand) {
    unsigned int eax, ebx, ecx, edx;
    unsigned int vendor_id[3];

    // Ottieni l'ID del fornitore del processore
    eax = 0x00000000; // Funzione 0
    __asm__ (
        "cpuid"
        : "=b" (vendor_id[0]), "=d" (vendor_id[1]), "=c" (vendor_id[2])
        : "a" (eax)
    );

    // Copia l'ID del fornitore del processore
    snprintf(vendor, 13, "%c%c%c%c%c%c%c%c%c%c%c%c",
             (char)(vendor_id[0] & 0xFF), (char)((vendor_id[0] >> 8) & 0xFF),
             (char)((vendor_id[0] >> 16) & 0xFF), (char)((vendor_id[0] >> 24) & 0xFF),
             (char)(vendor_id[1] & 0xFF), (char)((vendor_id[1] >> 8) & 0xFF),
             (char)((vendor_id[1] >> 16) & 0xFF), (char)((vendor_id[1] >> 24) & 0xFF),
             (char)(vendor_id[2] & 0xFF), (char)((vendor_id[2] >> 8) & 0xFF),
             (char)((vendor_id[2] >> 16) & 0xFF), (char)((vendor_id[2] >> 24) & 0xFF));
    vendor[12] = '\0'; // Aggiungi terminatore di stringa

    // Ottieni il nome del processore
    eax = 0x80000002; // Funzione 0x80000002
    __asm__ (
        "cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
        : "a" (eax)
    );
    snprintf(brand, 17, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
             (char)(eax & 0xFF), (char)((eax >> 8) & 0xFF),
             (char)((eax >> 16) & 0xFF), (char)((eax >> 24) & 0xFF),
             (char)(ebx & 0xFF), (char)((ebx >> 8) & 0xFF),
             (char)((ebx >> 16) & 0xFF), (char)((ebx >> 24) & 0xFF),
             (char)(ecx & 0xFF), (char)((ecx >> 8) & 0xFF),
             (char)((ecx >> 16) & 0xFF), (char)((ecx >> 24) & 0xFF),
             (char)(edx & 0xFF), (char)((edx >> 8) & 0xFF),
             (char)((edx >> 16) & 0xFF), (char)((edx >> 24) & 0xFF));

    eax = 0x80000003; // Funzione 0x80000003
    __asm__ (
        "cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
        : "a" (eax)
    );
    snprintf(brand + 16, 17, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
             (char)(eax & 0xFF), (char)((eax >> 8) & 0xFF),
             (char)((eax >> 16) & 0xFF), (char)((eax >> 24) & 0xFF),
             (char)(ebx & 0xFF), (char)((ebx >> 8) & 0xFF),
             (char)((ebx >> 16) & 0xFF), (char)((ebx >> 24) & 0xFF),
             (char)(ecx & 0xFF), (char)((ecx >> 8) & 0xFF),
             (char)((ecx >> 16) & 0xFF), (char)((ecx >> 24) & 0xFF),
             (char)(edx & 0xFF), (char)((edx >> 8) & 0xFF),
             (char)((edx >> 16) & 0xFF), (char)((edx >> 24) & 0xFF));

    eax = 0x80000004; // Funzione 0x80000004
    __asm__ (
        "cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
        : "a" (eax)
    );
    snprintf(brand + 32, 17, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
             (char)(eax & 0xFF), (char)((eax >> 8) & 0xFF),
             (char)((eax >> 16) & 0xFF), (char)((eax >> 24) & 0xFF),
             (char)(ebx & 0xFF), (char)((ebx >> 8) & 0xFF),
             (char)((ebx >> 16) & 0xFF), (char)((ebx >> 24) & 0xFF),
             (char)(ecx & 0xFF), (char)((ecx >> 8) & 0xFF),
             (char)((ecx >> 16) & 0xFF), (char)((ecx >> 24) & 0xFF),
             (char)(edx & 0xFF), (char)((edx >> 8) & 0xFF),
             (char)((edx >> 16) & 0xFF), (char)((edx >> 24) & 0xFF));
}

int main() {
    char os_name[] = "Butos";  // Nome del sistema operativo
    float os_version = 0.0;
    char cpu_info[100];      // Buffer per le informazioni sulla CPU
    char vendor[13];
    char brand[49]; // 3 * 16 + 1 per il terminatore

    get_processor_version(vendor, brand);

    printf(RED"OS: "RESET);
    printf("%s ", os_name);
    printf("%.1f\n",os_version);
    printf(RED"CPU: "RESET);
    printf("%s ", brand);
    printf("%s\n", vendor);

    return 0;
}
