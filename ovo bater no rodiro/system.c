#include "bibliotecas.h"
#include "system.h"
#include "variaveis.h"

typedef struct elemento{
    double x, y, largura, altura;
    char id[100], contorno[100], preenchimento[100];
    bool marcadoTP;
}elemento;

void showlist(lista sequence) {
    celula celulaAux = getHead(sequence);
    elemento *aux;
    puts("=================");
    for (int i = 0; i < getSize(sequence); i++) {
        aux = getItem(celulaAux);
        printf("Pos na lista = %d - id = %s x = %lf y = %lf largura = %lf altura = %lf preenchimento = %s contorno = %s\n", i, aux->id, aux->x, aux->y, aux->largura, aux->altura, aux->preenchimento, aux->contorno);
        celulaAux = getNext(celulaAux);
    }
    puts("=================");
}

void getData(listaDupla sequence, void* location) {
    elemento* aux; 
    char* PathArquivoGeoInicial = getPathArquivoGeoInicial(location);
    FILE* arq = fopen(PathArquivoGeoInicial, "r");
    double x;
    double y;
    double largura;
    double altura;
    char id[100];
    char contorno[100];
    char preenchimento[100];
    char comando[20];
    int i = 0;
    while (fscanf(arq, "%s", comando) != -1) {
        if (!strcmp(comando, "cc")) {
            fscanf(arq, "%s", contorno);
        } else if (!strcmp(comando, "cp")) {
            fscanf(arq, "%s", preenchimento);
        } else if (!strcmp(comando, "r")) {
            aux = calloc(1, sizeof(elemento));
            strcpy(aux->contorno, contorno);
            strcpy(aux->preenchimento, preenchimento);
            fscanf(arq, "%s %lf %lf %lf %lf", id, &x, &y, &largura, &altura);
            strcpy(aux->id, id);
            aux->x = x;
            aux->y = y;
            aux->largura = largura;
            aux->altura = altura;
            insert(sequence, aux);
        }
    }
    fclose(arq);
}

void getArguments(int argc, char** argv, void* locations) {
    if (argc < 2) {
        puts("Argumentos faltando.");
        return;
    }

    bool* IbExecutado = getIbExecutado(locations);
    bool* FbExecutado = getFbExecutado(locations);
    bool* FileGeo  = getFileGeo(locations);
    bool* PathSaida = getPathSaida(locations);
    bool* estatica = getestatica(locations);
    bool* dinamica = getdinamica(locations);
    bool* Consultafeita = getConsultafeita(locations);
    bool* CbExecutado = getCbExecutado(locations);
    bool* Fail = getFail(locations);

    bool pathEntrada = false;

    *IbExecutado = false;

    *FbExecutado = false;

    *FileGeo = false;

    *PathSaida = false;

    *estatica = false;

    *dinamica = true;

    char* DirBaseDeEntrada = getDirBaseDeEntrada(locations);
    char* DirBaseDeSaida = getDirBaseDeSaida(locations);
    char* GeoInicial = getGeoInicial(locations);
    char* NomeGEO = getNomeGEO(locations);
    char* QryConsultas = getQryConsultas(locations);
    char* NomeQRY = getNomeQRY(locations);
    char* NomeArqSVGFinal = getNomeArqSVGFinal(locations);
    char* TituloGrafFinal = getTituloGrafFinal(locations);
    char* PathDoSvgDoGeoSemMudanca = getPathDoSvgDoGeoSemMudanca(locations);
    char* PathArquivoGeoInicial = getPathArquivoGeoInicial(locations);
    char* PathArquivoQryAtual = getPathArquivoQryAtual(locations);
    char* PathDoSvgComOQryExecutado = getPathDoSvgComOQryExecutado(locations);
    char* PathDoTXTComOQryExecutado = getPathDoTXTComOQryExecutado(locations);
    char* PathSVGFinalGrafico = getPathSVGFinalGrafico(locations);

    // printf("%d %d %d %d %d %d %d\n", *IbExecutado, *FbExecutado, *FileGeo, *PathSaida, *estatica, *dinamica, pathEntrada);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {  //Diretório-base de entrada (BED)
            DirBaseDeEntrada = realloc(DirBaseDeEntrada , strlen(argv[i + 1]) + 1);
            strcpy(DirBaseDeEntrada, argv[i + 1]);
            if (DirBaseDeEntrada[strlen(DirBaseDeEntrada) - 1] != '/') {  //Adicionar mais um caractere + o '\0'
                DirBaseDeEntrada = realloc(DirBaseDeEntrada, strlen(DirBaseDeEntrada) + 2);
                strcat(DirBaseDeEntrada, "/");
            }
            pathEntrada = true;
        } else if (!strcmp(argv[i], "-f")) {  //Arquivo .geo inicial. Este arquivo deve estar sob o diretório BED.
            char* temp = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            GeoInicial = realloc(GeoInicial, strlen(argv[i + 1]) + 1);
            NomeGEO = realloc(NomeGEO,strlen(argv[i + 1]) + 1);
            int index;
            int posNome = 0;
            bool found = false;
            strcpy(temp, argv[i + 1]);
            strcpy(GeoInicial, argv[i + 1]);

            for (int i = 0; i < strlen(GeoInicial); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
                if (temp[i] == '/') {
                    index = i;
                    found = true;
                }
            }
            if (found) {
                for (int i = index + 1; i < strlen(GeoInicial); i++) {
                    if (temp[i] == '.') {
                        NomeGEO[posNome] = '\0';
                        break;
                    } else {
                        NomeGEO[posNome] = temp[i];
                        posNome++;
                    }
                }
            } else {
                strcpy(NomeGEO, argv[i + 1]);
                for (int i = 0; i < strlen(NomeGEO); i++) {
                    if (NomeGEO[i] == '.') {
                        NomeGEO[i] = '\0';
                    }
                }
            }
            *FileGeo = true;
            free(temp);
        } else if (!strcmp(argv[i], "-o")) {  //Diretório-base de saída (BSD)
            DirBaseDeSaida = realloc(DirBaseDeSaida, strlen(argv[i + 1]) + 1);
            strcpy(DirBaseDeSaida, argv[i + 1]);
            if (DirBaseDeSaida[strlen(DirBaseDeSaida) - 1] != '/') {  //Adicionar mais um caractere + o '\0'
                DirBaseDeSaida = realloc(DirBaseDeSaida, strlen(DirBaseDeSaida) + 2);
                strcat(DirBaseDeSaida, "/");
            }
            *PathSaida = true;

        } else if (!strcmp(argv[i], "-q")) {  //Arquivo com consultas. Este arquivo deve estar sob o diretório BED.
            char* temp = calloc(strlen(argv[i + 1]) + 1, sizeof(char));
            QryConsultas = realloc(QryConsultas, strlen(argv[i + 1]) + 1);
            NomeQRY = realloc(NomeQRY, strlen(argv[i + 1]) + 1);
            strcpy(QryConsultas, argv[i + 1]);
            strcpy(temp, argv[i + 1]);
            int index;
            int posNome = 0;
            bool found = false;
            for (int i = 0; i < strlen(QryConsultas); i++) {  //Se for passado um caminho relativo na localizacao do .geo inicial
                if (temp[i] == '/') {
                    index = i;
                    found = true;
                }
            }
            if (found) {
                for (int i = index + 1; i < strlen(QryConsultas); i++) {
                    if (temp[i] == '.') {
                        NomeQRY[posNome] = '\0';
                        break;
                    } else {
                        NomeQRY[posNome] = temp[i];
                        posNome++;
                    }
                }
            } else {
                strcpy(NomeQRY, argv[i + 1]);
                for (int i = 0; i < strlen(NomeQRY); i++) {
                    if (NomeQRY[i] == '.') {
                        NomeQRY[i] = '\0';
                    }
                }
            }
            *Consultafeita = true;
            free(temp);
        } else if (!strcmp(argv[i], "-ib")) {  //Inicia coleta de dados de desempenho
            *IbExecutado = true;
        } else if (!strcmp(argv[i], "-cb")) {  //Continua a coletar dados
            *CbExecutado = true;
            //Dar append depois de um -ib executado
        } else if (!strcmp(argv[i], "-fb")) {  //Finaliza a coleta, produz no diretório BED o arquivo arq.svg contendo o gráfico com o título especificado
            FILE* hasStart = fopen("visitasDoQryAtual.txt", "r");
            if (!hasStart) {  //Checar se a coleta foi inicializada
                *Fail = true;
                continue;
            }
            NomeArqSVGFinal = realloc(NomeArqSVGFinal ,strlen(argv[i + 1]) + 1);
            TituloGrafFinal = realloc(TituloGrafFinal ,strlen(argv[i + 2]) + 1);
            strcpy(NomeArqSVGFinal, argv[i + 1]);
            strcpy(TituloGrafFinal, argv[i + 2]);
            *FbExecutado = true;
            fclose(hasStart);
        } else if (!strcmp(argv[i], "-lse")) {  //Setar flags para tipo de lista a ser usado
            *estatica = true;
            *dinamica = false;
        } else if (!strcmp(argv[i], "-ldd")) {  //Setar flags para tipo de lista a ser usado
            *estatica = false;
            *dinamica = true;
        }
    }
    if (*Fail || !*FileGeo || !*PathSaida) {
        if (!*FileGeo) {
            puts("Arquivo geo inexistente.");
        }
        if (!*PathSaida) {
            puts("Path de saida nao inserido.");
        }
        if (*Fail) {
            puts("Coleta nao iniciada!");
        }
        puts("Erro!");
        liberarVariaveisDaStruct(locations);
        exit(1);
    }
    //Apos coletar todas as informacoes, esta na hora de arrumar e organizar todos os dados reunidos, nomes autoexplicativos
    PathDoSvgDoGeoSemMudanca = realloc(PathDoSvgDoGeoSemMudanca ,strlen(DirBaseDeSaida) + strlen(NomeGEO) + 5);
    sprintf(PathDoSvgDoGeoSemMudanca, "%s%s.svg", DirBaseDeSaida, NomeGEO);
    if (pathEntrada) {
        PathArquivoGeoInicial = realloc(PathArquivoGeoInicial, strlen(DirBaseDeEntrada) + strlen(GeoInicial) + 2);
        strcpy(PathArquivoGeoInicial, DirBaseDeEntrada);
        strcat(PathArquivoGeoInicial, GeoInicial);
    } else {
        DirBaseDeEntrada = realloc(DirBaseDeEntrada , 3);
        strcpy(DirBaseDeEntrada, "./");
        PathArquivoGeoInicial = realloc(PathArquivoGeoInicial , strlen(DirBaseDeEntrada) + strlen(GeoInicial) + 1);
        strcpy(PathArquivoGeoInicial, DirBaseDeEntrada);
        strcat(PathArquivoGeoInicial, GeoInicial);
    }
    if (*Consultafeita) {
        PathArquivoQryAtual = realloc(PathArquivoQryAtual, strlen(DirBaseDeEntrada) + strlen(QryConsultas) + 2);
        sprintf(PathArquivoQryAtual, "%s%s", DirBaseDeEntrada, QryConsultas);
        PathDoSvgComOQryExecutado = realloc(PathDoSvgComOQryExecutado, strlen(DirBaseDeSaida) + strlen(NomeGEO) + strlen(NomeQRY) + 9);
        PathDoTXTComOQryExecutado = realloc(PathDoTXTComOQryExecutado , strlen(DirBaseDeSaida) + strlen(NomeGEO) + strlen(NomeQRY) + 9);
        sprintf(PathDoTXTComOQryExecutado, "%s%s-%s.txt", DirBaseDeSaida, NomeGEO, NomeQRY);
        sprintf(PathDoSvgComOQryExecutado, "%s%s-%s.svg", DirBaseDeSaida, NomeGEO, NomeQRY);
    }
    if (*FbExecutado) {
        PathSVGFinalGrafico = realloc(PathSVGFinalGrafico, strlen(DirBaseDeSaida) + strlen(NomeArqSVGFinal) + 10);
        sprintf(PathSVGFinalGrafico, "%s%s.svg", DirBaseDeSaida, NomeArqSVGFinal);
    }
}

// void S_getData(listaEstatica sequence, char* PathArquivoGeoInicial) {
//     FILE* data = fopen(PathArquivoGeoInicial, "r");
//     double x;
//     double y;
//     double largura;
//     double altura;
//     char id[100];
//     char contorno[100];
//     char preenchimento[100];
//     char comando[20];
//     while (fscanf(data, "%s", comando) != -1) {
//         if (!strcmp(comando, "cc")) {
//             fscanf(data, "%s", contorno);
//         } else if (!strcmp(comando, "cp")) {
//             fscanf(data, "%s", preenchimento);
//         } else if (!strcmp(comando, "r")) {
//             fscanf(data, "%s %lf %lf %lf %lf", id, &x, &y, &largura, &altura);
//             S_addElement(sequence, x, y, largura, altura, id, preenchimento, contorno);
//         }
//     }
//     fclose(data);
// }

// void getFunctions(listaDupla sequence, char* ArquivoQry) {  //Leitura do .qry
//     FILE* resultstxt = fopen(PathDoTXTComOQryExecutado, "w+");
//     FILE* Svg_Modificado = fopen(PathDoSvgComOQryExecutado, "w+");
//     FILE* comandos = fopen(PathArquivoQryAtual, "r");
//     double x;
//     double y;
//     double largura;
//     double altura;
//     char id[100];
//     int k;
//     char comando[5];
//     int cont = 0;
//     bool naoPrintar = false;
//     while (fscanf(comandos, "%s", comando) != -1) {
//         if (!strcmp(comando, "tp")) {
//             tp(sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "tpr")) {
//             fscanf(comandos, "%lf %lf %lf %lf", &x, &y, &largura, &altura);
//             tpr(x, y, largura, altura, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "dpi")) {
//             fscanf(comandos, "%lf %lf", &x, &y);
//             dpi(x, y, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "dr")) {
//             fscanf(comandos, "%s", id);
//             dr(id, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "bbi")) {
//             fscanf(comandos, "%lf %lf", &x, &y);
//             bbi(x, y, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "bbid")) {
//             fscanf(comandos, "%s", id);
//             bbid(id, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "iid")) {
//             fscanf(comandos, "%s %d", id, &k);
//             iid(id, k, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "diid")) {
//             fscanf(comandos, "%s %d", id, &k);
//             diid(id, k, sequence, resultstxt);
//             cont++;
//         }
//     }
//     if (cont == 1 && iidExecutado) {
//         naoPrintar = true;
//         remove(PathDoSvgComOQryExecutado);
//     } else {
//         writeOnSvg(Svg_Modificado, sequence);
//     }
//     fclose(comandos);
//     fclose(resultstxt);
//     if (!naoPrintar) {
//         fclose(Svg_Modificado);
//     }
// }

// void S_getFunctions(listaEstatica sequence, char* ArquivoQry) {
//     FILE* resultstxt = fopen(PathDoTXTComOQryExecutado, "w+");
//     FILE* Svg_Modificado = fopen(PathDoSvgComOQryExecutado, "w+");
//     FILE* comandos = fopen(PathArquivoQryAtual, "r");
//     double x;
//     double y;
//     double largura;
//     double altura;
//     char id[100];
//     int k;
//     char comando[5];
//     int cont = 0;
//     bool naoPrintar = false;
//     while (fscanf(comandos, "%s", comando) != -1) {
//         if (!strcmp(comando, "tp")) {
//             S_tp(sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "tpr")) {
//             fscanf(comandos, "%lf %lf %lf %lf", &x, &y, &largura, &altura);
//             S_tpr(x, y, largura, altura, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "dpi")) {
//             fscanf(comandos, "%lf %lf", &x, &y);
//             S_dpi(x, y, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "dr")) {
//             fscanf(comandos, "%s", id);
//             S_dr(id, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "bbi")) {
//             fscanf(comandos, "%lf %lf", &x, &y);
//             S_bbi(x, y, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "bbid")) {
//             fscanf(comandos, "%s", id);
//             S_bbid(id, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "iid")) {
//             fscanf(comandos, "%s %d", id, &k);
//             S_iid(id, k, sequence, resultstxt);
//             cont++;
//         } else if (!strcmp(comando, "diid")) {
//             fscanf(comandos, "%s %d", id, &k);
//             S_diid(id, k, sequence, resultstxt);
//             cont++;
//         }
//     }
//     if (cont == 1 && iidExecutado) {
//         naoPrintar = true;
//         remove(PathDoSvgComOQryExecutado);
//     } else {
//         S_writeOnSvg(Svg_Modificado, sequence);
//     }
//     fclose(comandos);
//     fclose(resultstxt);
//     if (!naoPrintar) {
//         fclose(Svg_Modificado);
//     }
// }

// void freeAllandClose(FILE* geo, FILE* svg_source) {
//     fclose(svg_source);
//     fclose(geo);
// }

// void checarColetas() {
//     if (IbExecutado) {
//         FILE* visitasDoQryAtual = fopen("visitasDoQryAtual.txt", "w+");
//         fprintf(visitasDoQryAtual, "%ld %d\n", visitas, tamanhoOriginal);
//         fclose(visitasDoQryAtual);
//     } else if (CbExecutado) {
//         FILE* visitasDoQryAtual = fopen("visitasDoQryAtual.txt", "a+");
//         fprintf(visitasDoQryAtual, "%ld %d\n", visitas, tamanhoOriginal);
//         fclose(visitasDoQryAtual);
//     } else if (FbExecutado) {
//         FILE* visitasDoQryAtual = fopen("visitasDoQryAtual.txt", "a+");
//         fprintf(visitasDoQryAtual, "%ld %d\n", visitas, tamanhoOriginal);
//         fclose(visitasDoQryAtual);
//         buildGraphic();
//     }
// }

// void createTempFiles() {
//     FILE* tempTPWrite = fopen("testeTP.txt", "w+");
//     FILE* tempTPR = fopen("tempTPR.txt", "w+");
//     FILE* tempDPI = fopen("tempDPI.txt", "w+");
//     FILE* tempDR = fopen("tempDR.txt", "w+");
//     FILE* tempBBICoordenadas = fopen("tempBBICoordinates.txt", "w+");
//     FILE* tempBBIPontos = fopen("tempBBIPoints.txt", "w+");
//     FILE* tempBBIDCoordenadas = fopen("tempBBIDCoordinates.txt", "w+");
//     FILE* tempDIID = fopen("tempDIID.txt", "w+");
//     FILE* tempDIIDRemove = fopen("tempDIIDRemove.txt", "w+");

//     fclose(tempTPWrite);
//     fclose(tempTPR);
//     fclose(tempDPI);
//     fclose(tempDR);
//     fclose(tempBBICoordenadas);
//     fclose(tempBBIPontos);
//     fclose(tempBBIDCoordenadas);
//     fclose(tempDIID);
//     fclose(tempDIIDRemove);
// }

// void removeTempFiles() {
//     remove("testeTP.txt");
//     remove("tempTPR.txt");
//     remove("tempDPI.txt");
//     remove("tempDR.txt");
//     remove("tempBBICoordinates.txt");
//     remove("tempBBIPoints.txt");
//     remove("tempBBIDCoordinates.txt");
//     remove("tempDIID.txt");
//     remove("tempDIIDRemove.txt");
// }

