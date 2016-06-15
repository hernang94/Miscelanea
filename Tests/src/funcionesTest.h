/*
 * funciones.h
 *
 *  Created on: 27/5/2016
 *      Author: utnso
 */

#ifndef FUNCIONESTEST_H_
#define FUNCIONESTEST_H_

#include<stdint.h>
#include<stdlib.h>
#include<commons/collections/list.h>
#include<commons/txt.h>
#include<estructuras.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <commons/config.h>
#include "estructurasUMCTest.h"
#include "hexdumpTest.h"
#include "variablesGlobalesUMCTest.h"
void inicializarPrograma(uint32_t pid,int cantPaginas,char* codPrograma);
void solicitarBytes(int numPagina,int offset,int tamaniooPag,uint32_t pid,int clienteCPU);
void almacenarBytesPagina(int numPagina,int offset,int tamaniooPag,void*buffer,uint32_t pid,int clienteCPU);
void finalizarPrograma(uint32_t pid);
void proc_Destroy(t_nodo_lista_procesos *self);
void pagina_Destroy(t_nodo_lista_paginas*self);
void frame_Destroy(t_nodo_lista_frames *self);
void entrada_TLB_Destroy(t_entrada_TLB *self);
int encontrarPosicionEnProcesos(uint32_t pid) ;
int moverPunteroProximaPosibleVictima(int indice, uint32_t pid);
int buscarVictimaClockModificado(uint32_t pid) ;
void actualizarBitReferencia(uint32_t id_frame) ;
void actualizarBitModificado(uint32_t id_frame) ;
void * lecturaMemoria(uint32_t frame, uint32_t offset, uint32_t tamanio);
void escrituraMemoria(uint32_t frame, uint32_t offset, uint32_t tamanio,
		void * buffer) ;
void actualizarBitUltimoAccesoTLB(uint32_t pid, int nroFrame) ;
void cambiarRetardo(int nuevoRetardo) ;
void flushMemoria();
void flushTLB();
void limpiarEntradasTLB(uint32_t pid) ;
void liberarMarcos(uint32_t pid);
int buscarEnListaProcesos(uint32_t pid, int numPagina);
int buscarenTLB(uint32_t pid, int numPag) ;
int buscarEntradaMasAntigua() ;
void LRU(uint32_t paginaNueva, uint32_t pid, uint32_t frameNuevo) ;
int cantidadFramesDisponibles() ;
void inicializarPuntero(uint32_t pid, int indice) ;
int buscarVictimaClock(uint32_t pid) ;
void realizarCambiosEnPagina(uint32_t pagNueva, uint32_t frame, int indiceproc) ;
void indicarPaginaQueVaAlSwap(uint32_t id_frame, int indiceproc) ;
void algoritmoDeReemplazo(uint32_t pid, uint32_t pagNueva, void *codigo);
void cargarenTLB(uint32_t pid, int numPagina, uint32_t nroFrame) ;
int cargarPaginaenMemoria(uint32_t pid, int numPag, void*buffer);
int inicializarEnSwap(int socketSwap, int cantidadPaginasCodigo, uint32_t pid) ;
//void*pedirAlSwap(int numPagina, uint32_t pid) ;
void liberarPaginas(int indice) ;
void dumpearEstructuraPaginas(t_nodo_lista_procesos*nodoAux, FILE*archivo) ;
void dumpPIDparaDumpTotal(t_nodo_lista_procesos*nodoAux, FILE*archivo) ;
void dumpTotal() ;
void dumpMemoriaPID(t_nodo_lista_procesos*nodoAux, FILE*archivo);
void dumpPID(uint32_t pid);
void enviarCodigoAlSwap(uint32_t pid, int cantPaginas, char*codPrograma);
//void inicializarPrograma(uint32_t pid, int cantPaginas, void* codPrograma);
void avisarSwapFinPrograma(uint32_t pid) ;
void avisarNucleoFinProgramaPorOverFlow(uint32_t pid) ;
void avisarNucleoFinPrograma(uint32_t pid) ;
//void * solicitarBytes(int numPagina, int offset, int tamanioPag, uint32_t pid,
		//int clienteCPU);
//void almacenarBytesPagina(int numPagina, int offset, int tamanioPag,
	//	void*buffer, uint32_t pid) ;
//void finalizarPrograma(uint32_t pid) ;
void cambioProceso(uint32_t idNuevoPrograma, uint32_t * idProcesoActivo) ;
#endif /* FUNCIONESTEST_H_ */
