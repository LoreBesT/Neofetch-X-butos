#include <stdio.h> //non supportata direttamente da butos. I comandi vanno modificati con quelli delle call di butos
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
//Le librerie non sono tutte necessarie. Sono state importate solo le 4 supportate
#include <syscalls.h> //commentare su macchina virtuale con kernel linux

#define RED "\e[0;31m"
#define RESET "\e[0m"

// Funzione per ottenere le informazioni sulla CPU tramite CPUID
void get_cpu_info(char *cpu_info) {
    unsigned int eax, ebx, ecx, edx;

    __asm__ (
        "movl $0, %%eax\n\t"      // Imposta EAX a 0 per ottenere il Vendor ID
        "cpuid\n\t"                // Chiama CPUID
        "movl %%ebx, %1\n\t"      // Salva EBX
        "movl %%edx, %2\n\t"      // Salva EDX
        "movl %%ecx, %3\n\t"      // Salva ECX
        : "=a"(eax), "=r"(ebx), "=r"(edx), "=r"(ecx) // Output
        :                           // Nessun input
        : "ebx", "edx", "ecx"      // Registri modificati
    );

    // Formattiamo il Vendor ID come una stringa
    sprintf(cpu_info, "%c%c%c%c%c%c%c%c%c%c%c%c",
            (ebx & 0xFF), (ebx >> 8 & 0xFF), (ebx >> 16 & 0xFF), (ebx >> 24 & 0xFF),
            (edx & 0xFF), (edx >> 8 & 0xFF), (edx >> 16 & 0xFF), (edx >> 24 & 0xFF),
            (ecx & 0xFF), (ecx >> 8 & 0xFF), (ecx >> 16 & 0xFF), (ecx >> 24 & 0xFF));
}

int main() {
    char os_name[] = "Butos";  // Nome del sistema operativo
    float os_version = 0.0;
    char cpu_info[100];      // Buffer per le informazioni sulla CPU

    // Otteniamo le informazioni sulla CPU
    get_cpu_info(cpu_info);

    // Stampa le informazioni
    printf(RED"OS: "RESET);
    printf("%s ", os_name);
    printf("%.1f\n",os_version);
    printf(RED"CPU: "RESET);
    printf("%s\n", cpu_info);

    return 0;
}
