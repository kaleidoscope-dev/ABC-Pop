#pragma once

// NOTE: this is a very old code. Like 20+ years. So you can't judge me.
// It's here because I was too lazy to learn a proper logging lib

#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdarg.h>

using namespace std;


#define FILE_MODE 0x01
#define CONSOLE_MODE 0x02
#define SILENT_MODE 0x03

class I_cLog
{
 public:
	 I_cLog();
       ~I_cLog();
       
    
    bool FileExists(string path);   
	string AppendLog(const char *format, ...);
	void StartAppend(int indent, string title);
	void StopAppend(int indent,string title);
	void ResetLog(void);
    //int GetMessageParam(int *param);
	void SetDebugFile(string path);
    void IncInd();
    void IncInd(int i);
    void DecInd();
    void DecInd(int i);
    void SetDebugMode(unsigned char mode);
    void AppendBuffer(uint8_t *buffer, int len);


    string currentDirectory;
 private:           
	string path_;


	private:
	FILE *logfile;
	unsigned long LogCounter;

	int indent_;              //  NI
	string indent_string_;    //  NI
    unsigned char debug_mode;           
    
    


};

extern I_cLog *gLog;


