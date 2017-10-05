/**************************************************************************

   Lunar Compress C Dynamic DLL Access Program
   Created by FuSoYa, Defender of Relm
   http://fusoya.eludevisibility.org

   Check "LunarDLL.h" for documentation on using this file.

**************************************************************************/

//#include "stdafx.h"  //use this if you get errors compiling under VC
#include <windows.h>
#include "..\DLLCode\LunarDLL.h"

#ifdef _WIN64
#define DLLSOURCE "..\\x64\\"
#else
#define DLLSOURCE "..\\"
#endif

LCPROC1 LunarVersion;
LCPROC2 LunarCloseFile;
LCPROC3 LunarOpenFile;
LCPROC4 LunarGetFileSize;
LCPROC5 LunarReadFile;
LCPROC6 LunarWriteFile;
LCPROC7 LunarSNEStoPC;
LCPROC8 LunarPCtoSNES;
LCPROC9 LunarDecompress;
LCPROC10 LunarRecompress;
LCPROC11 LunarEraseArea;
LCPROC12 LunarExpandROM;
LCPROC13 LunarVerifyFreeSpace;
LCPROC14 LunarCreatePixelMap;
LCPROC15 LunarCreateBppMap;
LCPROC16 LunarSNEStoPCRGB;
LCPROC17 LunarPCtoSNESRGB;
LCPROC18 LunarRender8x8;
LCPROC19 LunarWriteRatArea;
LCPROC20 LunarEraseRatArea;
LCPROC21 LunarGetRatAreaSize;
LCPROC22 LunarOpenRAMFile;
LCPROC23 LunarSaveRAMFile;
LCPROC24 LunarIPSCreate;
LCPROC25 LunarIPSApply;
LCPROC26 LunarSetFreeBytes;

HINSTANCE LunarLibInst=NULL;


bool LunarUnloadDLL()  {

   if (!LunarLibInst)
      return true;	//the library is already unloaded
   FreeLibrary(LunarLibInst);
   LunarLibInst=NULL;
   return true;   //library unloaded
}

bool LunarLoadDLL()  {
unsigned int i=0;

   if (LunarLibInst)
      return true;	//the library is already loaded
   LunarLibInst = LoadLibrary("Lunar Compress");
   if (!LunarLibInst) //hmm, try the other file name?
      LunarLibInst = LoadLibrary("Lunar_Compress");
   if (!LunarLibInst)
      return false;	//Couldn't load DLL...

   // If the handle is valid, try to get the function addresses.
   i+=(int)( LunarVersion = (LCPROC1)GetProcAddress(LunarLibInst,"LunarVersion") );
   i+=(int)( LunarCloseFile = (LCPROC2)GetProcAddress(LunarLibInst,"LunarCloseFile") );
   i+=(int)( LunarOpenFile = (LCPROC3)GetProcAddress(LunarLibInst,"LunarOpenFile") );
   i+=(int)( LunarGetFileSize = (LCPROC4)GetProcAddress(LunarLibInst,"LunarGetFileSize") );
   i+=(int)( LunarReadFile = (LCPROC5)GetProcAddress(LunarLibInst,"LunarReadFile") );
   i+=(int)( LunarWriteFile = (LCPROC6)GetProcAddress(LunarLibInst,"LunarWriteFile") );
   i+=(int)( LunarSNEStoPC = (LCPROC7)GetProcAddress(LunarLibInst,"LunarSNEStoPC") );
   i+=(int)( LunarPCtoSNES = (LCPROC8)GetProcAddress(LunarLibInst,"LunarPCtoSNES") );
   i+=(int)( LunarDecompress = (LCPROC9)GetProcAddress(LunarLibInst,"LunarDecompress") );
   i+=(int)( LunarRecompress = (LCPROC10)GetProcAddress(LunarLibInst,"LunarRecompress") );
   i+=(int)( LunarEraseArea = (LCPROC11)GetProcAddress(LunarLibInst,"LunarEraseArea") );
   i+=(int)( LunarExpandROM = (LCPROC12)GetProcAddress(LunarLibInst,"LunarExpandROM") );
   i+=(int)( LunarVerifyFreeSpace = (LCPROC13)GetProcAddress(LunarLibInst,"LunarVerifyFreeSpace") );
   i+=(int)( LunarCreatePixelMap = (LCPROC14)GetProcAddress(LunarLibInst,"LunarCreatePixelMap") );
   i+=(int)( LunarCreateBppMap = (LCPROC15)GetProcAddress(LunarLibInst,"LunarCreateBppMap") );
   i+=(int)( LunarSNEStoPCRGB = (LCPROC16)GetProcAddress(LunarLibInst,"LunarSNEStoPCRGB") );
   i+=(int)( LunarPCtoSNESRGB = (LCPROC17)GetProcAddress(LunarLibInst,"LunarPCtoSNESRGB") );
   i+=(int)( LunarRender8x8 = (LCPROC18)GetProcAddress(LunarLibInst,"LunarRender8x8") );
   i+=(int)( LunarWriteRatArea = (LCPROC19)GetProcAddress(LunarLibInst,"LunarWriteRatArea") );
   i+=(int)( LunarEraseRatArea = (LCPROC20)GetProcAddress(LunarLibInst,"LunarEraseRatArea") );
   i+=(int)( LunarGetRatAreaSize = (LCPROC21)GetProcAddress(LunarLibInst,"LunarGetRatAreaSize") );
   i+=(int)( LunarOpenRAMFile = (LCPROC22)GetProcAddress(LunarLibInst,"LunarOpenRAMFile") );
	i+=(int)( LunarSaveRAMFile = (LCPROC23)GetProcAddress(LunarLibInst,"LunarSaveRAMFile") );
   i+=(int)( LunarIPSCreate = (LCPROC24)GetProcAddress(LunarLibInst,"LunarIPSCreate") );
	i+=(int)( LunarIPSApply = (LCPROC25)GetProcAddress(LunarLibInst,"LunarIPSApply") );
   i+=(int)( LunarSetFreeBytes = (LCPROC26)GetProcAddress(LunarLibInst,"LunarSetFreeBytes") );

   if (i>=26)
       return true;	//load successful!

   LunarUnloadDLL();
   return false;	//we couldn't find all the functions...
}



