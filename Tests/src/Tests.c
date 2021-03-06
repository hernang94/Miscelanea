/*
 ============================================================================
 Name        : Tests.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <estructuras.h>
#include "CUnit/Basic.h"

#include "estructurasUMCTest.h"
#include "funcionesTest.h"
#include "hexdumpTest.h"
#include "variablesGlobalesUMCTest.h"

void inicializar(){
		pthread_mutex_init(&mutexMarcos, NULL);
		pthread_mutex_init(&mutexAccesoMem, NULL);
		pthread_mutex_init(&mutexProcs, NULL);
		pthread_mutex_init(&mutexRetardo,NULL);
		pthread_mutex_init(&mutexMP,NULL);
		pthread_mutex_init(&mutexSwap, NULL);
		pthread_mutex_init(&mutexTLB, NULL);
		pthread_mutex_init(&mutexNucleo, NULL);
		logger=log_create("logsUMC","UMC",0,1);
		listaDeProcesos = list_create();
		listaDeFrames=list_create();
		tlb=list_create();
		cantidadDeFrames = 10;
		accesosAMemoria=0;
		marcos_x_proc=2;
		tamanioFrame = 21;
			tamanioTotalmemoria = (tamanioFrame)
					* 10;
			memoriaprincipal = malloc(tamanioTotalmemoria);
			entradasTLB=2;
			retardoUMC=0;
			algoritmo="CLOCK-M";
			int i,j;
			//cantidaddeFrames
		for(i=0;i<10;i++){
			t_nodo_lista_frames * nodoAux=malloc(sizeof(t_nodo_lista_frames));
			nodoAux->pid=0;
			nodoAux->id_frame=(uint32_t)i;
			nodoAux->bitModificado=0;
			nodoAux->bitReferencia=0;
			list_add(listaDeFrames,nodoAux);
		}
		for(j=0;j<entradasTLB;j++){
			t_entrada_TLB*nodoTLBAux=malloc(sizeof(t_entrada_TLB));
			nodoTLBAux->id_frame=0;
			nodoTLBAux->pid=0;
			nodoTLBAux->nro_pagina=0;
			nodoTLBAux->ultimo_acceso=accesosAMemoria;
			list_add(tlb,nodoTLBAux);
		}
}
void testDeEscrituraEnMemoria(){
	//inicializar();
	char*codigofalopa=malloc(strlen("Hello i'm the code")*3);
			strcpy(codigofalopa,"Hello i'm the codeHello i'm the codeHello i'm the code");
	escrituraMemoria(0,0,strlen(codigofalopa)+1,(void*)codigofalopa);
	//char*codigofalopa2=(char*)lecturaMemoria(0,0,strlen(codigofalopa)+1);
	//printf("%s\n",codigofalopa2);
	//CU_ASSERT_NSTRING_EQUAL(codigofalopa2, "Hello the code", 14);
}

int main() {
  inicializar();
  //testDeEscrituraEnMemoria();
  FILE*archi=fopen("test.txt","w+");
  int tamanio=(15*21);
  //hexdump(memoriaprincipal,tamanio,archi);
  uint32_t pid=2021;
  uint32_t pid2=2022;
  uint32_t pid3=2033;
  char*codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  codigo[10]='\0';
  /*char*codigo2=malloc(5);
    strcpy(codigo2,"Holis");
    codigo[5]='\0';*/
    //int tamaniocad= strlen(codigo2);
  inicializarPrograma(pid,4,codigo);
  inicializarPrograma(pid2,7,codigo);
  inicializarPrograma(pid3,7,codigo);
  cargarPaginaenMemoria(pid,2,(void*)codigo);
  //cargarenTLB(pid,2,0);
  //almacenarBytesPagina(5,0,tamaniocad,(void*)codigo2,pid2,0);
  codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid,1,(void*)codigo);
  actualizarBitModificado(0);
  codigo=malloc(10);
  //cargarenTLB(pid,1,1);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid,0,(void*)codigo);
  //cargarenTLB(pid,0,2);
  int frame=buscarenTLB(pid,0);
  uint32_t pid4=1234;
  cambioProceso(4325,&pid4);
  printf("%d\n",pid4);
  printf("%d\n",frame);
  //flushTLB();
  //flushMemoria();
  //actualizarBitModificado(0);
  //actualizarBitReferencia(0);
  //finalizarPrograma(pid);
  //liberarMarcos(pid); OK
  //int indice=encontrarPosicionEnProcesos(456); OK
  //liberarPaginas(indice); OK

  /*codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid,3,(void*)codigo);
  codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid2,6,(void*)codigo);
  codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid2,5,(void*)codigo);

  codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid2,4,(void*)codigo);
  codigo=malloc(10);
  strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid2,3,(void*)codigo);
  codigo=malloc(10);
    strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid2,2,(void*)codigo);
  codigo=malloc(10);
    strcpy(codigo,"Holaperro");
  cargarPaginaenMemoria(pid2,1,(void*)codigo);
  codigo=malloc(10);
    strcpy(codigo,"Holaperro");
  int respuesta=cargarPaginaenMemoria(pid3,3,(void*)codigo);*/
  int a= cantidadFramesDisponibles();
  //printf("Respuesta: %d\n",respuesta);
  printf("%d\n",a);
  //printf("%s\n",mensajito);
  usleep(2000*1000);
  dumpTotal();
  fclose(archi);
 free(memoriaprincipal);
  return 0;
}
