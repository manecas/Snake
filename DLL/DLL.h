#include <windows.h>
#include <tchar.h>
#include <io.h> 
#include <fcntl.h> 

#ifdef DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else 
#define DLL_IMP_API __declspec(dllimport) 
#endif

//variaveis globais
#define LARGURA 60
#define ALTURA  30
#define TAM_CORPO_SNAKE_MAX 10

#define CIMA 1
#define DIREITA 2
#define BAIXO 3
#define ESQUERDA 4

#define NUM_JOGADORES 2
#define SNAKE1 0
#define SNAKE2 1

#define TAM_CORPO_SNAKES_JOGADORES 2
#define TAM_CORPO_SNAKE_AUTOMATICA 2

DLL_IMP_API TCHAR NomeMemoriaPartilhada[];
DLL_IMP_API TCHAR EventoTecla[];
DLL_IMP_API TCHAR EventoMapa[];
DLL_IMP_API TCHAR *MutexInstanciaServidor;
DLL_IMP_API HANDLE hMuteInstanciaServidor;
DLL_IMP_API BOOL encerraThreads;

//estruturas globais
typedef struct Memoria {
	TCHAR matriz[ALTURA][LARGURA];
	TCHAR tecla;
	int pontos1, pontos2;
} memoria;

typedef struct CorpoSnake {
	int x, y;
} corpo_snake;

typedef struct Snake {
	int tamanho;
	int pontos;
	int direcao;
	corpo_snake corpo[TAM_CORPO_SNAKE_MAX];
} snake;

typedef struct Jogador {
	int threadId;
	int num_jogadores;
	snake snakes[2];
} jogador;

//fun��es mem�ria partilhada
DLL_IMP_API HANDLE criaFileMapping();
DLL_IMP_API memoria * criaMapView(HANDLE hMemoria);
DLL_IMP_API void fechaZonaMemoria(HANDLE hMemoria, memoria *mem);