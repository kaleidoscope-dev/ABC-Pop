#include "I_cLog.h"



#include <time.h>





I_cLog *gLog = NULL;


I_cLog::I_cLog()
{
 path_ = "debug.txt";
}


I_cLog::~I_cLog()
{
}


bool I_cLog::FileExists(string path)
{
 FILE *f = NULL;
 f = fopen(path.c_str(),"r");
 if (f == NULL)
    {
     return false;
    }else {
           fclose(f);
           return true;
          }
}




const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


 string I_cLog::AppendLog(const char *format, ...)
{
    return "";
 if (debug_mode != SILENT_MODE)
	{
	 char out[256];
	 va_list arglist;

	 va_start( arglist, format );
	 vsprintf(out, format, arglist );
	 va_end( arglist );

     LogCounter++;

     string s = out;

     time_t  timev;
      time(&timev);
     string b = currentDateTime();


  switch (debug_mode)
     {
	  case  FILE_MODE :
			{
             char out_text[512];

			 logfile = fopen(path_.c_str(),"a");


			 sprintf(out_text,"#%d [%s] %s\n",LogCounter,b.c_str(),s.c_str());
			 string str_out_text = out_text;
			 for (int c=0;c<this->indent_;c++)
			      str_out_text.insert(str_out_text.begin(),' ');

			 fprintf(logfile,"%s",str_out_text.c_str());
			 fclose(logfile);

			 break;
			}

		 case CONSOLE_MODE :
			{
			 char out_text[512];
			 sprintf(out_text,"#%d [%s] %s\n",LogCounter,b.c_str(),s.c_str());
			 string str_out_text = out_text;
			 for (int c=0;c<this->indent_;c++)
			      str_out_text.insert(str_out_text.begin(),' ');


			 printf("%s",out_text);

			 break;
			}
     }
    return s;
   }
return "";
}



void I_cLog::AppendBuffer(uint8_t *buffer, int len)
{
 logfile = fopen(path_.c_str(),"a");
 for (int c=0;c<len;c++)
     {
      fprintf(logfile,"%2X ",buffer[c]);
     }
 fprintf(logfile,"\n");
 fclose(logfile);
}


void I_cLog::StartAppend(int indent, string title)
{
 this->IncInd(indent);

  string b = "NON";


  string s;
  for (int c=0;c<indent;c++) s+=" ";

            switch (debug_mode)
               {
            case  FILE_MODE :
                  {


                  logfile = fopen(path_.c_str(),"a");
  		           fprintf(this->logfile,"\n#%d [%s]%s---------------------[ START: %s ]------------------------------\n",LogCounter,b.c_str(),s.c_str(),title.c_str());
			        fclose(logfile);
                   break;
                  }

               case CONSOLE_MODE :
                  {
  		            AppendLog("\n#%d [%s]%s---------------------[ START: %s ]------------------------------\n",LogCounter,b.c_str(),s.c_str(),title.c_str());
                   break;
                  }


               }
}

void I_cLog::StopAppend(int indent,string title)
{
    /*
  _datetime_t tim = _datetime_t::now();
  string b = string(tim.fmt("%d/%m - %H:%M:%S"));
  // fak kaj koji su ovo hakovi :)
  string s;
  for (int c=0;c<indent;c++) s+=" ";

            switch (debug_mode)
               {
            case  FILE_MODE :
                  {

                  logfile = fopen(path_.c_str(),"a");
  		           fprintf(this->logfile,"\n#%d [%s]%s---------------[ STOP: %s ]------------------------------------------\n",LogCounter,b.c_str(),s.c_str(),title.c_str());
			        fclose(logfile);
                   break;
                  }

               case CONSOLE_MODE :
                  {
  		            gLog->AppendLog("\n#%d [%s]%s---------------[ STOP: %s ]------------------------------------------\n",LogCounter,b.c_str(),s.c_str(),title.c_str());
                   break;
                  }

               }

   this->DecInd(indent);
   */
}



void I_cLog::ResetLog(void)
{/*
	if (path_.empty())
	   {
	    path_ = "debug.txt";
	   }

	logfile = fopen(path_.c_str(),"w");
	if (logfile == NULL)
	   {
	    path_ = "debug.txt";
	   }

	fclose(logfile);
	LogCounter = 0;
    this->indent_ = 0;
    */
}



void I_cLog::SetDebugFile(string path)
{
	path_ = path;

}

void I_cLog::IncInd()
{
    this->indent_+=3;
}

void I_cLog::IncInd(int i)
{
    this->indent_+=i;
}


void I_cLog::DecInd(int i)
{
    this->indent_-= i;
    if (this->indent_ <0)
    indent_ = 0;
}

void I_cLog::DecInd()
{
    this->indent_-=3;
    if (this->indent_ <0)
    indent_ = 0;
}

void I_cLog::SetDebugMode(unsigned char mode)
{
    this->debug_mode = mode;
}










