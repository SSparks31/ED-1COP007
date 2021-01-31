#ifndef LIB_DATASTORE_H
#define LIB_DATASTORE_H

typedef struct dataStore dataStoreT;
typedef struct dataFile dataFileT;

dataStoreT *createDataStore(char *defaultDir, int *parameters);
void destroyDataStore(dataStoreT **dataStore);

dataFileT *createDataFile(int id, char *path, char *mode);
void destroyDataFile(dataFileT **dataFile);

#endif