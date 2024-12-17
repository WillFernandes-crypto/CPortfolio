#ifndef RELATORIO_H
#define RELATORIO_H

#include <stdio.h>
#include "paciente.h"
#include "medico.h"
#include "hospital.h"
#include "heap.h"

typedef struct {
    char nome[MAX_NOME];
    int horas;
    int especialidade_id;
} MedicoRelatorio;

// Prot�tipos das fun��es de relat�rio
void gerarRelatorioFinal(const char* arquivo_saida, HeapPrioridade* heap, HeapRetorno* heapRetorno, int num_salas, int num_medicos);
void gerarRelatorioHorasTrabalhadas(FILE* fp, Medico* medicos, int num_medicos);

#endif // RELATORIO_H
