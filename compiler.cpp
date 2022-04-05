#include <iostream>
#include <fstream>

using namespace std;

//declaring command funcs
void bsif(string arg1);
void bootable();
void a20(bool on);
void bsinline(string line);
//declaring tool funcs
bool isin(string str1, string str2);
void open(string in, string out);


//global vars
ifstream rf;
ofstream of;
string iline;
bool com;
int pos;
int temp;

int main(int argc, char const *argv[])
{
    open(argv[1], argv[2]);
    while(true){
        //get next line
        getline(rf, iline);
        //comment
        com = isin(iline, "//");

        if (!com){
            if (isin(iline, "?bootbyte")){
                bootable();
            }
            if (isin(iline, "<?>")){
                break;
            }
            if (isin(iline, " if")){
                bsif(iline);
            }
            if (isin(iline,"inline")){
                bsinline(iline);
            }
        } else {
            of << ';' << iline.substr(0,pos) << iline.substr(pos+2) << endl;
        }
    }
    
}
void open(string in, string out){
    rf.open(in);
    of.open(out);
}

void bsif(string line){
    
}

void a20(bool on){
    //todo add a20 line activation code here

}

void bootable(){
    //write: 
    of << "times 510-($-$$) db 0" << endl << "dw 0xaa55" << endl;
}

bool isin(string str1, string str2){
    if (str1.find(str2) != -1) {
        pos = str1.find(str2);
        return true;
    } else {
        return false;
    }
}

void bsinline(string line){
    string sstr;
    if (isin(line, "inline(")){
        temp = pos;
        isin(line, ")");
        sstr = line.substr(temp+7, pos);
        of << "inline test => " << sstr << endl;
    } else {
        cout << "ERORR: expected ( after inline near:" << pos << endl;
    }
}