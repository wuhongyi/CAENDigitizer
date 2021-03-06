// DigitizerUser.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 4月 24 17:55:37 2016 (+0800)
// Last-Updated: Fri Apr 29 19:25:03 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 92
// URL: http://wuhongyi.cn 

#include "DigitizerUser.hh"
#include "DigitizerAdmin.hh"

#include <iostream>

#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <inttypes.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void SaveROOTPicture(char *type,int b, int ch, int size,int16_t *WaveData,TCanvas *c,TGraph *g)
// {
//   g=new TGraph();
//   c->Clear();

//   char filename[32];
//   int i;
//   sprintf(filename, "Picture%sB%dC%d.jpg",type,b,ch);

//   for(i=0; i<size; i++)
//     {
//       g->SetPoint(i,i,WaveData[i]);
//       // printf("%d\n",WaveData[i]);
//     }
//   c->cd();
//   g->Draw("AC");
//   c->SaveAs(filename);
//   delete g;
// }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UpdateFileName(DigitizerRun_t *PKU_DGTZ_RunManager)
{
  char temp[8];
  sprintf(PKU_DGTZ_RunManager->WriteFileName,"%s/run%04d_%d",PKU_DGTZ_RunManager->PathToRawData,PKU_DGTZ_RunManager->RunNumber,PKU_DGTZ_RunManager->FileNo+1);
  PKU_DGTZ_RunManager->FileNo++;
}


void OpenFile(DigitizerRun_t *PKU_DGTZ_RunManager)
{
  PKU_DGTZ_FilePointer = fopen(PKU_DGTZ_RunManager->WriteFileName, "wb");
  if (PKU_DGTZ_FilePointer == NULL)    
    printf("open file fail \n");
}

void CloseFile()
{
  if(PKU_DGTZ_FilePointer != NULL)
    fclose(PKU_DGTZ_FilePointer);
  PKU_DGTZ_FilePointer = NULL; 
}

void OpenRunLog()
{
  PKU_DGTZ_LogFilePointer = fopen("../run.log","aw");
  if(PKU_DGTZ_LogFilePointer == NULL)
    printf("open file ../run.log fail \n");
}

void WriteRunLog(char *log)
{
  fprintf(PKU_DGTZ_LogFilePointer,"%s",log);
}

void CloseRunLog()
{
  if(PKU_DGTZ_LogFilePointer != NULL)
    fclose(PKU_DGTZ_LogFilePointer);
  PKU_DGTZ_LogFilePointer = NULL; 
}

void UpdateWhenFileFillUp(DigitizerRun_t *PKU_DGTZ_RunManager)
{
  if(PKU_DGTZ_RunManager->WriteFlag)
    {
      if(GetFileSize(PKU_DGTZ_RunManager->WriteFileName) > MAXFILEBYTE)
	{
	  CloseFile(); 
	  UpdateFileName(PKU_DGTZ_RunManager);
	  OpenFile(PKU_DGTZ_RunManager);
	}
    }
}

int SaveWaveform(int b, int ch, int size, uint16_t energy,int16_t *WaveData,uint64_t time)
{
  fwrite(&b,sizeof(int),1,PKU_DGTZ_FilePointer);
  fwrite(&ch,sizeof(int),1,PKU_DGTZ_FilePointer);
  fwrite(&size,sizeof(int),1,PKU_DGTZ_FilePointer);
  fwrite(&energy,sizeof(uint16_t),1,PKU_DGTZ_FilePointer);
  fwrite(&time,sizeof(uint64_t),1,PKU_DGTZ_FilePointer);
  fwrite(WaveData,sizeof(int16_t),size,PKU_DGTZ_FilePointer);
  return 0;
}



// 
// DigitizerUser.cc ends here
