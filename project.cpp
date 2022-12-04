#include<bits/stdc++.h>
#include<conio.h>
#include<dirent.h>
#include<algorithm>

using namespace std;

int total_deleted_lines = 0;

int nr_of_files;

void return_all_files_from_directory() {
   DIR *dr;
   struct dirent *en;
   dr = opendir("./initial_data"); //open all directory
   ofstream file_names("allapp.txt");
   if (dr) {
      while ((en = readdir(dr)) != NULL) {
         if(en->d_name[0] != '.')
            file_names<<en->d_name << endl; //print all directory name
      }
      closedir(dr); //close all directory
   }
}

struct file {
   vector<string> lines;
   string name;
   int nr_lines;
};


int main() {

   ifstream readnr("allapp.txt");
   string files_names;
   string a[62];
   while(readnr >> files_names){
     a[nr_of_files++] = files_names;
   }
    // intre cele 2 comm eu am citit tot din allapp.txt
   // si am salvat fiecare nume de fisier intr un vector

   vector<file> all_files;

   for(int i = 0; i < nr_of_files; ++i) {
      ifstream read_each("./initial_data/" + a[i]);
      string in;
      file current_file;
      current_file.name = a[i];
      while(getline(read_each, in)) {
         current_file.lines.push_back(in);

      }
      current_file.nr_lines = current_file.lines.size();
      all_files.push_back(current_file);
   }


   for(int i = 0; i < all_files[0].nr_lines; i++) {
      for(int j = 1; j < nr_of_files; ++j)
         for(int t = 0; t < all_files[j].nr_lines; ++t) {
            if(all_files[j].lines[t][0] == '#') 
               continue;
            if(all_files[0].lines[i] == all_files[j].lines[t] && all_files[0].lines[i] != "") {
               all_files[j].lines.erase(all_files[j].lines.begin() + t);
               all_files[j].nr_lines--, --t, ++total_deleted_lines;
            }
         }
   }


   for(int j = 1; j < nr_of_files; ++j) {
      for(int t = 0; t < all_files[j].nr_lines; ++t) {
         if(all_files[j].lines[t] == "" && all_files[j].lines[t - 1][0] == '#' && t >= 0) {
            for(int poz = t - 1; all_files[j].lines[poz][0] == '#' ; poz--) {
               all_files[j].lines.erase(all_files[j].lines.begin() + poz);
               all_files[j].nr_lines--, --t, ++total_deleted_lines;
               if(all_files[j].lines[poz - 1][0] == '#' && poz - 1 == 0) {
                  poz--;
                  all_files[j].lines.erase(all_files[j].lines.begin() + poz);
                  all_files[j].nr_lines--, --t, ++total_deleted_lines;
                  break;
               }
            }
         }
      }
   }

   

   return 0;
}