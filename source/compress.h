#include "suffixtree.h"
#include <ctime>

#pragma once

#ifndef __COMPRESS_H__
#define __COMPRESS_H__

int Decompress(BYTE* dest, const int dlen, const BYTE *src, const int slen);
int LZ2Compress(BYTE *dest, const 
    int dlen, const BYTE *src, const int slen);

inline void CompressTest(const char path[MAX_PATH])
{
    long start, stop;

    FILE *file = fopen(path, "rb");
    if (!file)
    {
        printf("Could not open file: \"%s\"\n", path);
        return;
    }

    if (fseek(file, 0, SEEK_END))
    {
        printf("File could not be accessed: \"%s\"\n", path);
        return;
    }
    int size = ftell(file);
    if (size == -1)
    {
        printf("Could not get size of file: \"%s\"\n", path);
        return;
    }

    BYTE* data = (BYTE*)malloc(size);
    rewind(file);
    if (fread(data, 1, size, file) != size)
    {
        printf("Could not read file data: \"%s\"\n", path);
        return;
    }
    /*
    start = clock();
    suffixtree *tree = new suffixtree();
    for (int i = 0; i < 1000; i++)
    {
        tree->createtree(data, 0x1000);
    }
        delete tree;

    stop = clock();
    printf("Tree building (1000 interations): %d ms\n", stop - start);
    */
    if (fclose(file))
        printf("Could not close file: \"%s\"\n", path);

    int len = LunarRecompress(data, 0, size, 0, LC_LZ2, 0);
    if (!len)
    {
        printf("Error while getting LC compress size\n");
        return;
    }

    int xlen = LZ2Compress(0, 0, data, 10);
    if (!xlen)
    {
        printf("Error while getting custom compress size\n");
        return;
    }

    BYTE* lc_lz2 = (BYTE*)malloc(len);
    BYTE* xlz2 = (BYTE*)malloc(xlen);

    for (int i = 0; i < 1; i++)
    {
        memset(lc_lz2, 0, len);
        memset(xlz2, 0, xlen);

        if (len != LunarRecompress(data, lc_lz2, size, 0x1000, LC_LZ2, 0))
        {
            printf("Error while compressing LC data\n");
            return;
        }
        if (xlen != LZ2Compress(xlz2, xlen, data, size))
        {
            printf("Error while compressing custom data\n");
            return;
        }
    }
    /*
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        if (len != LunarRecompress(data, lc_lz2, size, 0x1000, LC_LZ2, 0))
        {
            printf("Error while compressing LC data\n");
            return;
        }
    }
    stop = clock();
    printf("Lunar Recompress time (1000 iterations): %d ms\n", stop - start);

    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        if (xlen != LZ2Compress(xlz2, xlen, data, size))
        {
            printf("Error while compressing custom data\n");
            return;
        }
    }
    stop = clock();
    printf("Custom Recompress time (1000 iterations): %d ms\n", stop - start);

    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        if (!LunarOpenRAMFile(lc_lz2, LC_READONLY, len))
        {
            printf("Could not access RAM file\n");
            return;
        }
        if (size != LunarDecompress(data, 0, size, LC_LZ2, 0, 0))
        {
            printf("Error while decompressing data\n");
            return;
        }
    }
    stop = clock();
    printf("Lunar Decompress time (1000 iterations): %d ms\n", stop - start);
    */
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        if (size != Decompress(data, size, lc_lz2, len))
        {
            printf("Custom decompression error\n");
            return;
        }
    }
    stop = clock();
    printf("Custom decompress time (1000 iterations): %d ms\n", stop - start);
}

#endif