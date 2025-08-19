#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "elim-dup.h"

uint64_t elimDup(uint64_t x) {
    // Caso especial: si x es 0, retornar 0
    if (x == 0) return 0;
    
    uint64_t resultado = 0;
    int shift_resultado = 0;  // Posición donde insertar el siguiente dígito (en bits)
    int hex_anterior = -1;    // Dígito hexadecimal anterior (-1 indica que no hay)
    
    // Procesar cada dígito hexadecimal desde el menos significativo
    while (x != 0) {
        // Extraer el dígito hexadecimal menos significativo usando AND bit a bit
        // 0xF = 0b1111 extrae exactamente 4 bits (un dígito hexadecimal)
        int hex_actual = x & 0xF;
        
        // Solo agregar el dígito si es diferente al anterior (eliminar duplicados)
        if (hex_actual != hex_anterior) {
            // Insertar el dígito en su posición usando OR bit a bit
            // El cast a uint64_t asegura que no haya problemas con el desplazamiento
            // shift_resultado nunca será >= 64 porque uint64_t tiene máximo 16 dígitos hex
            resultado |= ((uint64_t)hex_actual << shift_resultado);
            shift_resultado += 4;  // Siguiente posición: 4 bits a la izquierda
            hex_anterior = hex_actual;  // Actualizar el dígito anterior
        }
        
        // Desplazar x 4 bits a la derecha para procesar el siguiente dígito hex
        // Equivale a eliminar el dígito que acabamos de procesar
        x >>= 4;
    }
    
    return resultado;
}
