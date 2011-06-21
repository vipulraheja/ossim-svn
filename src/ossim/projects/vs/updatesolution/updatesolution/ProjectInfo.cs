////////////////////////////////////////////////////////////
// - UpdateSolution -
// A tool for generating project and solution files from
// the OSSIM source tree.
//
// Written By: David A. Horner (http://dave.thehorners.com)
// License: LGPL
// $Id: ProjectInfo.cs 10417 2007-02-02 15:02:32Z dburken $
////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Text;
using System.Data;
using System.IO;

namespace updatesolution
{
    // this class is just a simple data holder for
    // projects we find in the tree.
    class ProjectInfo
    {
        public string theName = "";
        public string theProjPath = "";
        public string theGuid = "";
        public ArrayList theFiles = new ArrayList();

        public ProjectInfo(string appName, string path)
        {
            // set our members
            this.theName = appName;
            this.theGuid = System.Guid.NewGuid().ToString();
            this.theProjPath = path;
            this.theFiles.Clear();
        }

        public void FindFiles(string path, ArrayList extList)
        {
            // move through the directory and add all matching files
            DirectoryInfo dir = new DirectoryInfo(path);
            foreach (FileSystemInfo entry in dir.GetFileSystemInfos())
            {
                if (filterFile(entry.Extension, extList))
                {
                    theFiles.Add(entry);
                }
            }
        }

        // check the incoming extension matches one of the files we'd like to keep.
        private bool filterFile(string strExtension, ArrayList extList)
        {
            for (int j = 0; j < extList.Count; j++)
            {
                if (extList[j].ToString() == strExtension)
                {
                    return true;
                }
            }
            return false;
        }

    }
}
