#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <limits>

using namespace std;
class Room;
vector<Room> room;
class Guest{
public:
    Guest(string a,string b,int c,int d,int e):name(a),id(b),LiveDay(c),charge(d),RoomNumber(e){

    }
private:
    string name;
    string id;
    int LiveDay;
    int charge;
    int RoomNumber;

};
vector<Guest> guest;
class Room{
public:
    Room(int a,int b,string c,bool d= true):RoomNumberList(a),price(b),RoomType(c),RoomStatus(d){}
    Room(){
        RoomStatus=true;
    }

	int getPrice() const{
		return price;
	}
    int getRoomNumberList() const{
		return RoomNumberList;
	}
	string getRoomType() const{
		return RoomType;
	}
	bool RoomStatus;
private:
    int RoomNumberList;
    int price;
    string RoomType;

};
void initial(){
    ifstream  infile("./RoomData.csv",ios::in);
    if(!infile.is_open()){
        cout<<"open file failed"<<endl;
        exit(1);
    }else{
        cout<<"open file success"<<endl;
        string line;
        int m_RoomNumberList,m_price;
        string m_RoomType;
        while(getline(infile,line)){
            stringstream ss(line);
            string token;
            int count=0;
            while(getline(ss,token,',')){
                if(count==0){
                    m_RoomNumberList=stoi(token);
                }else if(count==1){
                    m_RoomType=token;
                }else if(count==2){
                    m_price=stoi(token);
                }
                count++;
            }
            Room tmp(m_RoomNumberList,m_price,m_RoomType,true);
            //cout<<m_RoomNumberList<<" "<<m_RoomType<<" "<<m_price<<endl;
            room.push_back(tmp);
        }
    }
    infile.close();
}
void checkin(){
	cout<<"Spare room number \t"<<"Room type \t\t"<<"Room price($) "<<endl;
    for(int i =0;i<room.size();i++){
        if(room[i].RoomStatus){
            cout<<room[i].getRoomNumberList()<<"\t\t\t"
                <<room[i].getRoomType()<<"\t\t"
                <<room[i].getPrice()<<endl;
        }
    }
    while(1){
        int number;
        cout<<"Room number:";
        cin>>number;
        cin.ignore(1024,'\n');
        if(cin.fail()){
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"please input the right number"<<endl;
            continue;
        }
        for(int i=0;i<room.size();i++){
            if(room[i].getRoomNumberList()==number){
                if(!room[i].RoomStatus){
                    cout<<"Room is not available"<<endl;
                    Sleep(3000);
                    system("cls");
                    continue;
                }else{
                    cout<<"Room is available"<<endl;
                    Sleep(3000);
                    system("cls");
                    cout<<"Room number:"<<room[i].getRoomNumberList()<<endl;
                    cout<<"Room type:"<<room[i].getRoomType()<<endl;
                    cout<<"Room price($):"<<room[i].getPrice()<<endl;

                    string name,id;
                    int day,charge;
                    cout<<"Guest name:";
                    cin>>name;
                    cout<<"Guest ID:";
                    cin>>id;
                    while(1){
                        cout<<"Length of stay:";
                        cin>>day;
                        if(cin.fail()||day<=0){
                            cin.clear(); // 清除错误标志
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout<<"please input the right number"<<endl;
                            continue;
                        }else{break;}
                    }
                    cout<<"Guest charge($):"<<room[i].getPrice()*day<<endl;
                    Guest tmp(name,id,room[i].getRoomNumberList(),day,room[i].getPrice()*day);
                    guest.push_back(tmp);
                    return ;
                }
            }
        }
        cout<<"Room is not available"<<endl;
    }
}
void menu(){
    while (1) {
        cout << "Welcome to hotel management system" << endl;
        cout << "1.check in" << endl;
        cout << "2.check out" << endl;
        cout << "3.search a room" << endl;
        cout << "4.Room information inquiry" << endl;
        cout << "5.exit" << endl;
        cout << "please input your choice :" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                checkin();
                Sleep(3000);
                system("cls");
                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            case 6:

                break;

            case 7:
                return;

            default:
                cout << "please input the right choice" << endl;
                break;
        }
    }
}
int main(){
    initial();
    //cout<<room[0].getRoomType();
    checkin();
    return 0;
}
