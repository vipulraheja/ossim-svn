//----------------------------------------------------------------------------
//
// File ossim-batch-test.cpp
// 
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Test code application ossim batch test.
//
//----------------------------------------------------------------------------
// $Id: ossim-batch-test.cpp 19751 2011-06-13 15:13:07Z dburken $

#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimApplicationUsage.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimTimer.h>
#include <ossim/init/ossimInit.h>

#include <cstdlib> /* for system() */
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static void writeTemplate(const ossimFilename& templateFile);
static void getDateString(std::string& date);
static void getLogFilename(ossimFilename& logFile);

static bool processTest(const ossimString& prefix, const ossimKeywordlist& kwl,
                        std::ofstream& logStr);

static bool processCommands(const ossimString& prefix, const ossimKeywordlist& kwl,
                            std::ofstream& logStr, const ossimString& testName, bool logTime);

static bool processCommands(const ossimString& prefix, const ossimKeywordlist& kwl,
                            std::ofstream& logStr, const ossimFilename& tempFile,
                            const ossimString& testName);

int main(int argc, char *argv[])
{
   enum
   {
      PASS  = 0,
      FAIL  = 1,
      ERROR = -1
   };
   
   std::string tempString;
   ossimArgumentParser::ossimParameter stringParam(tempString);
   ossimArgumentParser ap(&argc, argv);
   ossimInit::instance()->addOptions(ap);
   ossimInit::instance()->initialize(ap);

   ap.getApplicationUsage()->setApplicationName(ap.getApplicationName());

   ap.getApplicationUsage()->setDescription(ap.getApplicationName()+" batch test application.");
   
   ap.getApplicationUsage()->setCommandLineUsage(ap.getApplicationName()+" <tests.kwl>");
   
   ap.getApplicationUsage()->addCommandLineOption("-h or --help","Display usage.");
   
   ap.getApplicationUsage()->addCommandLineOption("-w", "<template_file> Writes a template file.  Can be used to start a tests.kwl file.");

   if ( ap.read("-h") || ap.read("--help") || (ap.argc() < 2) )
   {
      ap.getApplicationUsage()->write(ossimNotify(ossimNotifyLevel_NOTICE)); 
      return 0;
   }
   if (ap.read("-w", stringParam))
   {
      ossimFilename geometryTemplateFile = tempString.c_str();
      writeTemplate(geometryTemplateFile);
      return PASS;
   }

   ossimFilename configFile = ap.argv()[1];

   ossimKeywordlist kwl;
   kwl.setExpandEnvVarsFlag(true);
   if ( kwl.addFile(configFile) )
   {
      ossimFilename logDir;
      const char* lookup = 0;
      lookup = kwl.find("log_directory");
      if ( lookup )
      {
         logDir = ossimFilename(lookup).expand();
         if ( logDir.exists() == false )
         {
            if ( logDir.createDirectory() == false )
            {
               cerr << "Could not create: " << logDir << endl;
               return ERROR;
            }
         }
      }
      else
      {
         cerr << "missing config keyword: log_directory" << endl;
      }

      ossimFilename logFile;
      getLogFilename(logFile);
      logFile = logDir.dirCat(logFile);
      ossimSetLogFilename(logFile);
      std::ofstream logStr;
      logStr.open(logFile.c_str());
      if ( logStr.fail() )
      {
         cerr << "Could not open: " << logFile << endl;
         return ERROR;
      }
      else
      {
         cout << "Logging to file: " << logFile << "\n";
      }
      
      std::string date;
      getDateString(date);
      logStr << "// ---\n"
             << "// ossim-batch-test log:\n"
             << "// date format = yyyymmddhhmmss\n"
             << "//---\n"
             << "start_time: " << date << "\n"
             << "config_file: " << configFile << "\n";
      // Start the timer.
      ossimTimer::instance()->setStartTick();
      
      double startTime = ossimTimer::instance()->time_s();

      // Get the number of test:
      ossimString regExpStr = "test[0-9]+\\.";
      const ossim_uint32 COUNT = kwl.getNumberOfSubstringKeys(regExpStr);
      const ossim_uint32 MAX_INDEX = COUNT + 1000;
      ossimString prefixBase = "test";
      ossim_uint32 index = 0;
      ossim_uint32 processedIndexes = 0;

      while ( processedIndexes < COUNT )
      {
         ossimString prefix =  prefixBase + ossimString::toString(index) + ".";
         if ( processTest( prefix, kwl, logStr) )
         {
            ++processedIndexes;
         }
         ++index;
         if ( index >= MAX_INDEX ) break; 
      }

      getDateString(date);
      logStr << "\nstop_time: " << date << "\n";
      double stopTime = ossimTimer::instance()->time_s();
      logStr << "total elapsed time in seconds: "
             << std::setiosflags(ios::fixed) << std::setprecision(4)
             << (stopTime-startTime)
             << endl; // flush
      logStr.close();
      
      cout << "Wrote: " << logFile << endl;
   }
   else
   {
      cerr << "could not open: " << configFile << endl;
      return ERROR;
   }

   return 0;
}

void writeTemplate(const ossimFilename& templateFile)
{
   std::ofstream out(templateFile.c_str());
   if ( out.good() )
   {
      out << "// ossim-batch-test config file.\n"
          << "log_directory: $(OSSIM_TEST)/logs\n"
          << "test1.name: test1\n"
          << "test1.description: Test rgb data coming out grey scale.\n"
          << "\n"
          << "// ---\n"
          << "// Control flags:\n"
          << "// Use 0 or 1, true or false to turn on and off sections.\n"
          << "// Typically preprocess and expected results only turned on for first run.\n"
          << "// Clean commands should erase anything created by this test.\n"
          << "// Command order if flag turned on:\n"
          << "// 1) clean, 2) pre-process, 3) expected, 4) test, 5) post-process\n"
          << "// ---\n"
          << "\n"
          << "// Turns on/off whole test:\n"
          << "test1.enabled: 1\n"
          << "\n"
          << "test1.run_clean_commands: 0\n"
          << "test1.run_preprocessing_commands: 1\n"
          << "test1.run_expected_results_commands: 1\n"
          << "test1.run_test_commands: 1\n"
          << "test1.run_postprocessing_commands: 1\n"
          << "\n"
          << "// Temp file to catch diff output.\n"
          << "test1.temp_file: /tmp/tmp.txt\n"
          << "\n"
          << "// Clean up commands.\n"
          << "test1.clean_command0: rm -rf $(OSSIM_TEST)/expected_results/test1\n"
          << "test1.clean_command1: rm -rf $(OSSIM_TEST)/output/test1\n"
          << "\n"
          << "// Pre-process commands:\n"
          << "test1.preprocess_command0: mkdir -p $(OSSIM_TEST)/expected_results/test1\n"
          << "test1.preprocess_command1: mkdir -p $(OSSIM_TEST)/output/test1\n"
          << "\n"
          << "// Commands to generate expected results:\n"
          << "test1.expected_results_command0: ossim-orthoigen -w tiff_tiled_band_separate $(OSSIM_TEST)/test_data/test1/test1.ntf $(OSSIM_TEST)/expected_results/test1/t1.tif\n"
          << "test1.expected_results_command1: ossim-create-histo $(OSSIM_TEST)/expected_results/test1/t1.tif\n"
          << "\n"
          << "// The actual commands to test:\n"
          << "test1.test_command0: ossim-orthoigen -w tiff_tiled_band_separate $(OSSIM_TEST)/test_data/test1/test1.ntf $(OSSIM_TEST)/output/test1/t1.tif\n"
          << "test1.test_command1: ossim-create-histo $(OSSIM_TEST)/output/test1/t1.tif\n"
          << "\n"
          << "// Post process commands for diffs and stuff:\n"
          << "test1.postprocess_command0: diff -w $(OSSIM_TEST)/expected_results/test1/t1.his $(OSSIM_TEST)/output/test1/t1.his\n"
          << "\n"
          << "// test2.name:\n"
          << "// ..."
          << std::endl;
      
      out.close();
      
      ossimNotify(ossimNotifyLevel_NOTICE)
         << "Wrote file: " << templateFile.c_str() << std::endl;
   }
   else
   {
      ossimNotify(ossimNotifyLevel_NOTICE)
         << "Could not open: " << templateFile.c_str() << std::endl;
   }
}

void getDateString(std::string& date)
{
   time_t t;
   time(&t);
   tm* lt;
   lt = localtime(&t);
   std::string frmt = "%Y%m%d%H%M%S";
   // yyyymmddhhmmss
   char s[15];
   size_t count = strftime(s, 15, frmt.c_str(), lt);
   if ( count && (count < 15) )
   {
      date = s;
   }
   else
   {
      date.clear(); // ??? (drb)
   }
}

void getLogFilename(ossimFilename& logFile)
{
   logFile = "ossim-batch-test-log-";
   std::string date;
   getDateString(date);
   logFile += date;
   logFile += ".txt";
}

bool processTest(const ossimString& prefix, const ossimKeywordlist& kwl, std::ofstream& logStr)
{
   bool result = false;
   
   const char* lookup = kwl.find( prefix, "name" );
   if (lookup)
   {
      result = true;
      ossimString testName = lookup;
      
      logStr << "\n----------------------------------------------------------------------\n";
      
      // See if test is disabled/enabled:
      bool enabled = true;
      lookup = kwl.find( prefix, "enabled" );
      if ( lookup )
      {
         enabled = ossimString(lookup).toBool();
      }

      if ( enabled )
      {
         logStr << "processing_test: " << testName << "\n";

         lookup = kwl.find( prefix, "description" );
         if ( lookup )
         {
            logStr << "description: " << lookup << "\n";
         }
         
         bool preProcessFlag  = false;
         bool expectedFlag    = false;
         bool testFlag        = false;
         bool postProcessFlag = false;
         bool cleanFlag       = false;

         const char* lookup;
         std::string date; 

         lookup = kwl.find(prefix.c_str(), "run_clean_commands");
         if ( lookup )
         {
            cleanFlag = ossimString(lookup).toBool();
         }
         else
         {
            logStr << "missing_keyword: " << prefix << "run_clean_commands\n"
                   << "defaulting to false...\n";
         }
         
         lookup = kwl.find(prefix.c_str(), "run_preprocessing_commands");
         if ( lookup )
         {
            preProcessFlag = ossimString(lookup).toBool();
         }
         else
         {
            logStr << "missing_keyword: " << prefix << "run_preprocessing_commands\n"
                   << "defaulting to false...\n";
         }

         lookup = kwl.find(prefix.c_str(), "run_expected_results_commands");
         if ( lookup )
         {
            expectedFlag = ossimString(lookup).toBool();
         }
         else
         {
            logStr << "missing_keyword: " << prefix << "run_expected_results_commands\n"
                   << "defaulting to false...\n";
         }

         lookup = kwl.find(prefix.c_str(), "run_test_commands");
         if ( lookup )
         {
            testFlag = ossimString(lookup).toBool();
         }
         else
         {
            logStr << "missing_keyword: " << prefix << "run_test_commands\n"
                   << "defaulting to false...\n";
         }

         lookup = kwl.find(prefix.c_str(), "run_postprocessing_commands");
         if ( lookup )
         {
            postProcessFlag = ossimString(lookup).toBool();
         }
         else
         {
            logStr << "missing_keyword: " << prefix << "run_postprocessing_commands\n"
                   << "defaulting to false...\n";
         }


         logStr << "preProcessFlag:  " << preProcessFlag
                << "\nexpectedFlag:    " <<expectedFlag
                << "\ntestFlag:        " <<testFlag
                << "\npostProcessFlag: " <<postProcessFlag
                << "\ncleanFlag:       " <<cleanFlag
                << "\n";

         // Run the clean first if set...
         if ( cleanFlag )
         {
            ossimString prefixBase = prefix + "clean_command";
            processCommands( prefixBase, kwl, logStr, testName, false );
         }

         if ( preProcessFlag )
         {
            ossimString prefixBase = prefix + "preprocess_command";
            processCommands( prefixBase, kwl, logStr, testName, false );
         }
         if ( expectedFlag )
         {
            ossimString prefixBase = prefix + "expected_results_command";
            processCommands( prefixBase, kwl, logStr, testName, true );
         }
         if ( testFlag )
         {
            ossimString prefixBase = prefix + "test_command";
            processCommands( prefixBase, kwl, logStr, testName, true );
         }
         if ( postProcessFlag )
         {
            ossimFilename tempFile;
            lookup = kwl.find(prefix.c_str(), "temp_file");
            if ( lookup )
            {
               tempFile = lookup;
            }
            else
            {
               logStr << "missing_keyword: " << prefix << "temp_file\n";
            }
            ossimString prefixBase = prefix + "postprocess_command";
            processCommands( prefixBase, kwl, logStr, tempFile, testName );
         }
         logStr << "end_test: " << testName << "\n";
      }
      else
      {
         cout << testName << ": disabled\n";
         logStr << testName << ": disabled\n";
      }
      
      logStr << "----------------------------------------------------------------------\n"; 

   } // if kwl.find( prefix, "name" );
      
   return result; 
}

bool processCommands(const ossimString& prefixBase, const ossimKeywordlist& kwl,
                     std::ofstream& logStr, const ossimString& testName, bool logTime)
{
   bool result = true;

   //---
   // We must do these in order so we will use the
   // ossimKeywordlist::getNumberOfSubstringKeys
   // instead of: ossimKeywordlist::getSubstringKeyList
   //
   // MAX_INDEX is just so people can skip numbers in their config file like:
   // test1.command
   // test3.command oops...
   //---
   ossimString regExpStr = prefixBase + "[0-9]+";
   const ossim_uint32 COUNT = kwl.getNumberOfSubstringKeys(regExpStr);
   const ossim_uint32 MAX_INDEX = COUNT + 1000;

   std::string date;
   double startTime;
   double stopTime;
   
   ossimString command;
   ossim_uint32 index = 0;
   ossim_uint32 processedIndexes = 0;
   const char* lookup = 0;
   
   while (  processedIndexes < COUNT )
   {
      ossimString prefix =  prefixBase + ossimString::toString(index);
      lookup = kwl.find( prefix );
      if ( lookup )
      {
         logStr << "executing command: " << lookup << "\n";

         if ( logTime )
         {
            getDateString(date);
            logStr << "begin: " << date << "\n";

            // Start the clock:
            startTime = ossimTimer::instance()->time_s();
         }
            
         // Launch the command:
         int status = system(lookup);

         if ( logTime )
         {
            // Log the time and status:
            stopTime = ossimTimer::instance()->time_s();
            getDateString(date);
            logStr << "end: " << date << "\n"
                   << testName << "[" << index << "]: elapsed time in seconds: "
                   << std::setiosflags(ios::fixed)
                   << std::setprecision(4)
                   << (stopTime-startTime) << "\n";
         }
         
         logStr << "return status: " << status << "\n";
         
         ++processedIndexes;
      }
      ++index;
      
      if ( index >= MAX_INDEX ) break; // Config file has bad numbering...
   }
   return result;
}

bool processCommands(const ossimString& prefixBase,
                     const ossimKeywordlist& kwl,
                     std::ofstream& logStr,
                     const ossimFilename& tempFile,
                     const ossimString& testName)
{
   bool result = true;

   //---
   // We must do these in order so we will use the
   // ossimKeywordlist::getNumberOfSubstringKeys
   // instead of: ossimKeywordlist::getSubstringKeyList
   //
   // MAX_INDEX is just so people can skip numbers in their config file like:
   // test1.command
   // test3.command oops...
   //---
   ossimString regExpStr = prefixBase + "[0-9]+";
   const ossim_uint32 COUNT = kwl.getNumberOfSubstringKeys(regExpStr);
   const ossim_uint32 MAX_INDEX = COUNT + 1000;

   ossimString command;
   ossim_uint32 index = 0;
   ossim_uint32 processedIndexes = 0;
   const char* lookup = 0;
   
   while (  processedIndexes < COUNT )
   {
      ossimString prefix =  prefixBase + ossimString::toString(index);
      lookup = kwl.find( prefix );
      if ( lookup )
      {
         ossimString command = lookup;
         if ( tempFile.size() )
         {
            ossimString s = command;
            s += " > " + tempFile;
            command = s;
         }
         
         logStr << "executing command: " << command << "\n";
         
         // Launch the command:
         int status = system(command.c_str());

         logStr << "return status: " << status << "\n";

         //---
         // Output the status.
         // If failed write the temp file to the log.  This should have the diffs in it.
         //---
         if ( status != 0 )
         {
            cerr << testName << "[" << index << "]: FAILED" << endl;
            logStr << testName << "[" << index << "]: FAILED" << endl;
            logStr << command << "\noutput follows:\n";
            std::ifstream in;
            in.open(tempFile.c_str(), ios::in | ios::binary);
            if ( in.is_open() )
            {
               char ch;
               while ( in.get(ch) ) logStr.put(ch);
               logStr << "\n";
               in.close();
            }
         }
         else
         {
            cout << testName << "[" << index << "]: PASSED" << endl;
            logStr << testName << "[" << index << "]: PASSED" << endl;
         }
         
         ++processedIndexes;
      }
      ++index;
      
      if ( index >= MAX_INDEX ) break; // Config file has bad numbering...
   }
   return result;
}
