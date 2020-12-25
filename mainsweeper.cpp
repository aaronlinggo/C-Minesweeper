#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

void PapanArena(string Arena[10][10], int Jmine, int xmine[100], int ymine[100], int x[100], int y[100], int jumlahpagar, bool cheat){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            Arena[i][j] = ".";
        }
    }
    for(int i=0; i<Jmine; i++){
        Arena[ymine[i]][xmine[i]] = ".";
    }
    int bombbawah[100]; int bombkiri[100]; int bombkanan[100]; int bombatas[100];
    for(int i=0; i<jumlahpagar; i++){
        bombbawah[i] = 0; bombkiri[i] = 0; bombkanan[i] = 0; bombatas[i] = 0;
        if(y[i] < 9){
            for(int j=0; j<Jmine; j++){
                if(x[i]-1 == xmine[j] && y[i]+1 == ymine[j]){
                    bombbawah[i]++;
                }
                if(x[i]+1 == xmine[j] && y[i]+1 == ymine[j]){
                    bombbawah[i]++;
                }
                if(x[i] == xmine[j] && y[i]+2 == ymine[j]){
                    bombbawah[i]++;
                }
            }
            Arena[y[i]+1][x[i]] = bombbawah[i]+48;
        }
        if(x[i] > 0){
            for(int j=0; j<Jmine; j++){
                if(x[i]-2 == xmine[j] && y[i] == ymine[j]){
                    bombkiri[i]++;
                }
                if(x[i]-1 == xmine[j] && y[i]+1 == ymine[j]){
                    bombkiri[i]++;
                }
                if(x[i]-1 == xmine[j] && y[i]-1 == ymine[j]){
                    bombkiri[i]++;
                }
            }
            Arena[y[i]][x[i]-1] = bombkiri[i]+48;
        }
        if(x[i] < 9){
            for(int j=0; j<Jmine; j++){
                if(x[i]+2 == xmine[j] && y[i] == ymine[j]){
                    bombkanan[i]++;
                }
                if(x[i]+1 == xmine[j] && y[i]+1 == ymine[j]){
                    bombkanan[i]++;
                }
                if(x[i]+1 == xmine[j] && y[i]-1 == ymine[j]){
                    bombkanan[i]++;
                }
            }
            Arena[y[i]][x[i]+1] = bombkanan[i]+48;
        }
        if(y[i] > 0){
            for(int j=0; j<Jmine; j++){
                if(x[i]-1 == xmine[j] && y[i]-1 == ymine[j]){
                    bombatas[i]++;
                }
                if(x[i]+1 == xmine[j] && y[i]-1 == ymine[j]){
                    bombatas[i]++;
                }
                if(x[i] == xmine[j] && y[i]-2 == ymine[j]){
                    bombatas[i]++;
                }
            }
            Arena[y[i]-1][x[i]] = bombatas[i]+48;
        }
    }
    for(int i=0; i<jumlahpagar; i++){
        Arena[y[i]][x[i]] = "#";
    }
    if(cheat == true){
        for(int i=0; i<Jmine; i++){
            Arena[ymine[i]][xmine[i]] = "B";
        }
    }
}
void CetakPapan(string Arena[10][10]){
    cout<<"___| ";
    for(int i=0; i<10; i++){
        cout<<i<<" | ";
    }
    cout<<endl;
    for(int i=0; i<10; i++){
        cout<<" "<<i<<" | ";
        for(int j=0; j<10; j++){
            cout<<Arena[i][j]<<" | ";
        }
        cout<<endl;
    }
}
void PosisiBom(string Arena[10][10], int jumlahmine, int &Jmine, int xmine[100], int ymine[100]){
    Jmine = 0;
    do{
        bool salah = false;
        int x = rand()%10; int y = rand()%10;
        for(int i=0; i<Jmine; i++){
            if(y == ymine[i] && x == xmine[i]){
                salah = true;
                i = Jmine;
            }
        }
        if(salah == false){
            if(Arena[y][x] == "."){
                xmine[Jmine] = x; ymine[Jmine] = y;
                Jmine++;
            }
        }
    } while(Jmine<jumlahmine);
}
void menang(string Arena[10][10], int Jmine, int &WINGAME, bool &win){
    int pagartotal = 100-Jmine;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(Arena[i][j] == "#"){
                WINGAME++;
            }
        }
    }
    if(WINGAME == pagartotal){
        win = true;
    }
}
void tulisfile(string Arena[10][10]){
    ofstream ft("Screenshot.txt");
    if(ft.is_open()){
        cout<<"Screenshot Berhasil!"<<endl<<endl;
        ft<<"___| ";
        for(int i=0; i<10; i++){
            ft<<i<<" | ";
        }
        ft<<endl;
        for(int i=0; i<10; i++){
            ft<<" "<<i<<" | ";
            for(int j=0; j<10; j++){
                ft<<Arena[i][j]<<" | ";
            }
            ft<<endl;
        }
        ft.close();
    } else{
        cout<<"File screenshot Tidak ada"<<endl;
    }
}
void replayGame(string Arena[10][10], int jumlahpagar, int Jmine, int xmine[100], int ymine[100], int x[100], int y[100], bool cheat){
    ofstream ft("Replay.txt");
    if(ft.is_open()){
        int Replay=0;
        jumlahpagar++;
        while(Replay != jumlahpagar){
            PapanArena(Arena, Jmine, xmine, ymine, x, y, Replay, cheat);
            ft<<endl<<"REPLAY GAME"<<endl;
            ft<<"Step "<<Replay+1<<endl<<endl;
            ft<<"___| ";
            for(int i=0; i<10; i++){
                ft<<i<<" | ";
            }
            ft<<endl;
            for(int i=0; i<10; i++){
                ft<<" "<<i<<" | ";
                for(int j=0; j<10; j++){
                    ft<<Arena[i][j]<<" | ";
                }
                ft<<endl;
            }
            Replay++;
        }
        ft.close();
    } else{
        cout<<endl<<"File Replay Tidak ada"<<endl;
    }
}
void save(int x[100], int y[100], int jumlahpagar, int Jmine, int xmine[100], int ymine[100]){
    ofstream save("Save.txt");
    if(save.is_open()){
        cout<<"Save Berhasil!"<<endl<<endl;
        for(int i=0; i<Jmine; i++){
            save<<xmine[i]<<","<<ymine[i]<<" ";
        }
        save<<endl;
        for(int i=0; i<jumlahpagar; i++){
            save<<x[i]<<","<<y[i]<<" ";
        }
        save.close();
    } else{
        cout<<endl<<"File save tidak ada!"<<endl<<endl;
    }
}
void load(string &koordinatMine, string &koordinatPagar){
    ifstream load("Save.txt");
    string baris;
    bool cekbarisawal = true;
    if(load.is_open()){
        cout<<endl<<"Load Berhasil!"<<endl<<endl;
        while(getline(load,baris)){
            if(cekbarisawal == true){
                koordinatMine = baris;
                cekbarisawal = false;
            } else{
                koordinatPagar = baris;
            }
        }
        load.close();
    } else{
        cout<<endl<<"TIdak ada save-save an!"<<endl<<endl;
    }
}
int main(){
    srand(time(0));
    //Mine
    int jumlahmine, Jmine = 0, xmine[100], ymine[100];
    //Default Arena & Menu
    string Arena[10][10];
    char menu, submenu, menureplay;
    //Game
    int inputx, inputy, x[100], y[100], jumlahpagar = 0;
    int WINGAME = 0;
    bool cekX = false, cekY = false;
    bool game = true, win = false;
    bool bukanbom = false, cheat = false;
    //Save & Load
    string koordinatMine, koordinatPagar;
    do{
        WINGAME = 0; game = true; win = false; Jmine = 0;
        cout<<"=== MINESWEEPER ==="<<endl;
        cout<<"1. Play"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<">>> "; menu = getch();
        if(menu == '1'){
            system("cls"); jumlahmine = rand()%41+20;
            PapanArena(Arena, Jmine, xmine, ymine, x, y, jumlahpagar,cheat);
            PosisiBom(Arena, jumlahmine, Jmine, xmine, ymine);
            do{
                WINGAME = 0; cekX = false; cekY = false; cheat = false;
                PapanArena(Arena, Jmine, xmine, ymine, x, y, jumlahpagar,cheat);
                CetakPapan(Arena);
                menang(Arena, Jmine, WINGAME, win);
                replayGame(Arena, jumlahpagar, Jmine, xmine, ymine, x, y, cheat);
                if(win == true){
                    cout<<endl<<"ANDA MENANG"<<endl;
                    cout<<"Permainan Berakhir!"<<endl<<endl;
                    game = false; system("pause");
                } else{
                    cout<<endl<<"Tekan C untuk Cheat"<<endl;
                    cout<<"Tekan S untuk Save"<<endl;
                    cout<<"Tekan L untuk Load"<<endl;
                    cout<<"Tekan P untuk ScreenShot"<<endl;
                    cout<<"Tekan selain itu untuk input X dan Y"<<endl;
                    cout<<">>> "; submenu = getch();
                    cout<<endl<<endl;
                    if(submenu == 'c' || submenu == 'C'){
                        system("cls"); cheat=true;
                        PapanArena(Arena, Jmine, xmine, ymine, x, y, jumlahpagar, cheat);
                        CetakPapan(Arena); Sleep(1000);
                    } else if(submenu == 's' || submenu == 'S'){
                        save(x, y, jumlahpagar, Jmine, xmine, ymine);
                        system("pause");
                    } else if(submenu == 'l' || submenu == 'L'){
                        system("cls"); jumlahpagar=0; Jmine=0;
                        string tampungmine[100]; string tampungpagar[100];
                        char tampungxy;
                        int ctrMine=0; int ctrPagar=0;
                        load(koordinatMine, koordinatPagar);
                        for(int i=0; i<koordinatMine.size(); i++){
                            if(koordinatMine[i] != ' '){
                                tampungmine[ctrMine] += koordinatMine[i];
                            } else if(koordinatMine[i] == ' '){
                                ctrMine++;
                            }
                        }
                        for(int i=0; i<ctrMine; i++){
                            for(int j=0; j<tampungmine[i].size(); j++){
                                if(tampungmine[i][j] != ','){
                                    tampungxy = tampungmine[i][j];
                                } else if(tampungmine[i][j] == ','){
                                    xmine[i] = int(tampungxy) - 48;
                                }
                                ymine[i] = int(tampungxy) - 48;
                            }
                        }
                        for(int i=0; i<koordinatPagar.size(); i++){
                            if(koordinatPagar[i] != ' '){
                                tampungpagar[ctrPagar] += koordinatPagar[i];
                            } else if(koordinatPagar[i] == ' '){
                                ctrPagar++;
                            }
                        }
                        for(int i=0; i<ctrPagar; i++){
                            for(int j=0; j<tampungpagar[i].size(); j++){
                                if(tampungpagar[i][j] != ','){
                                    tampungxy = tampungpagar[i][j];
                                } else if(tampungpagar[i][j] == ','){
                                    x[i] = int(tampungxy) - 48;
                                }
                                y[i] = int(tampungxy) - 48;
                            }
                        }
                        jumlahpagar=ctrPagar; Jmine=ctrMine;
                        PapanArena(Arena, Jmine, xmine, ymine, x, y, jumlahpagar, cheat);
                        CetakPapan(Arena); system("pause");
                    } else if(submenu == 'p' || submenu == 'P'){
                        tulisfile(Arena); system("pause");
                    } else{
                        do{
                            cout<<" X : "; inputx = getch();
                            if(inputx >= 48 && inputx <= 57){
                                cekX = true;
                            } else{
                                cout<<endl;
                            }
                        } while(cekX == false); cout<<inputx-48<<endl;
                        do{
                            cout<<" Y : "; inputy = getch();
                            if(inputy >= 48 && inputy <= 57){
                                cekY = true;
                            } else{
                                cout<<endl;
                            }
                        } while(cekY == false); cout<<inputy-48<<endl;
                        bukanbom = true;
                        for(int i=0; i<Jmine; i++){
                            if(inputx-48 == xmine[i] && inputy-48 == ymine[i]){
                                bukanbom = false; i=Jmine;
                            }
                        }
                        if(bukanbom == true){
                            x[jumlahpagar] = inputx-48; y[jumlahpagar] = inputy-48;
                            jumlahpagar++;
                        } else{
                            cout<<endl<<"Anda Mengenai BOM"<<endl;
                            cout<<"Permainan Berakhir!"<<endl<<endl;
                            system("pause"); game = false;
                        }
                        system("cls");
                    }
                    system("cls");
                }
            } while(game == true);
            do{
                system("cls");
                cout<<"=== MENU REPLAY ==="<<endl;
                cout<<"1. Lihat Replay"<<endl;
                cout<<"0. Exit"<<endl;
                cout<<">>> "; menureplay = getch();
                if(menureplay == '1'){
                    system("cls"); int Replay=0; jumlahpagar++;
                    while(Replay != jumlahpagar){
                        PapanArena(Arena, Jmine, xmine, ymine, x, y, Replay, cheat);
                        CetakPapan(Arena);
                        cout<<endl<<"REPLAY GAME"<<endl;
                        Replay++; Sleep(1000); system("cls");
                    }
                }
            } while(menureplay != '0');
            jumlahpagar=0;
        }
        system("cls");
    } while(menu != '0');
}
