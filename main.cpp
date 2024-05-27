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
    Guest(string a,string b,int c,int d,int e):name(a),id(b),RoomNumber(c),LiveDay(d),charge(e){

    }
    string getname(){
        return name;
    }
    string getid(){
        return id;
    }
    int getRoomNumber() const{
        return RoomNumber;
    }
    int getLiveDay() const{
        return LiveDay;
    }
    int getcharge() const{
        return charge;
    }
private:
    string name;
    string id;
    int RoomNumber;
    int LiveDay;
    int charge;


};
vector<Guest> guest;
class Room{
public:
    Room(int a,int b,string c,string d= "true"):RoomNumberList(a),price(b),RoomType(c),RoomStatus(d){}
    Room(){
        RoomStatus="true";
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
	string RoomStatus;
private:
    int RoomNumberList;
    int price;
    string RoomType;

};
void RoomInitial(){
    ifstream  infile("./RoomData.csv",ios::in);
    if(!infile.is_open()){
        cout<<"open file failed"<<endl;
        exit(1);
    }else{
        cout<<"open file success"<<endl;
        string line;
        int m_RoomNumberList,m_price;
        string m_RoomType;
        string m_RoomStatus;
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
                }else if(count==4){
                	m_RoomStatus=token;
				}
                count++;
            }
            Room tmp(m_RoomNumberList,m_price,m_RoomType,m_RoomStatus);
            //cout<<m_RoomNumberList<<" "<<m_RoomType<<" "<<m_price<<endl;
            room.push_back(tmp);
        }
        infile.close();
    }
}
void GuestInitial() {
    ifstream infile;
    infile.open("./GuestData.csv",ios::in);
    if (!infile.is_open()) {
        cout << "open file error" << endl;
        return;
    } else {
        cout<<"open file success"<<endl;
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string token;
            int count = 0;
            string m_name, m_id;
            int m_RoomNumber, m_day, m_charge;
            while (getline(ss, token, ',')) {
                if (count == 0) {
                    m_name = token;
                } else if (count == 1) {
                    m_id = token;
                } else if (count == 2) {
                    m_RoomNumber = stoi(token);
                } else if (count == 3) {
                    m_day = stoi(token);
                } else if (count == 4) {
                    m_charge = stoi(token);
                }
                count++;
            }
            Guest tmp(m_name, m_id, m_RoomNumber, m_day, m_charge);
            guest.push_back(tmp);
        }
        infile.close();
    }
}
void checkin(){
	cout<<"Spare room number \t"<<"Room type \t\t"<<"Room price($) "<<endl;
    for(int i =0;i<room.size();i++){
        if(room[i].RoomStatus=="true"){
            cout<<room[i].getRoomNumberList()<<"\t\t\t"
                <<room[i].getRoomType()<<"\t\t"
                <<room[i].getPrice()<<endl;
        }
    }
    while(1){
        int number;
        cout<<"Room number:";
        cin>>number;
        if(cin.fail()){
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"please input the right number"<<endl;
            continue;
        }
        for(int i=0;i<room.size();i++){
            if(room[i].getRoomNumberList()==number){
                if(room[i].RoomStatus=="false"){
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
void checkout(){
    while(1){
        int number;
        cout<<"Room number:";
        cin>>number;
        if(cin.fail()){
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"please input the right number"<<endl;
            continue;
        }
        for(int i=0;i<room.size();i++){
            if(room[i].getRoomNumberList()==number){
                if(room[i].RoomStatus=="true"){
                    cout<<"The room is idle"<<endl;
                    Sleep(3000);
                    system("cls");

                }else {
                    cout<<"Room number:"<<room[i].getRoomNumberList()<<endl;
                    cout<<"Room type:"<<room[i].getRoomType()<<endl;
                    for(int j=0;j<guest.size();j++){
                        if(guest[j].getRoomNumber()==number) {
                            cout<<"Please check your information"<<endl;
                            cout << "Guest name:" << guest[j].getname() << endl;
                            cout << "Guest ID:" << guest[j].getid() << endl;
                            cout << "Length of stay:" << guest[j].getLiveDay() << endl;
                            cout << "Guest charge($):" << guest[j].getcharge() << endl;
                            room[i].RoomStatus ="true" ;
                            guest.erase(guest.begin()+j);
                        }
                    }
                    Sleep(3000);
                    system("cls");
                    continue;
                }
            }
        }
    }
}
void RoomDataWriteIn(){
    ofstream outfile;
    outfile.open("./RoomData.csv",ios::out);
    if(!outfile.is_open()){
        cout<<"open file failed"<<endl;
        exit(1);
    }else{
        for(int i=0;i<room.size();i++){
            outfile<<room[i].getRoomNumberList()<<","<<room[i].getRoomType()<<","<<room[i].getPrice()<<","<<room[i].RoomStatus<<endl;
        }
        outfile.close();
    }

}
void GuestDataWriteIn(){
    ofstream outfile;
    outfile.open("./GuestData.csv",ios::app|ios::out);
    if(!outfile.is_open()){
        cout<<"open file failed"<<endl;
        exit(1);
    }else{
        for(int i=0;i<guest.size();i++){
            outfile<<guest[i].getname()<<","<<guest[i].getid()<<","<<guest[i].getRoomNumber()<<","<<guest[i].getLiveDay()<<","<<guest[i].getcharge()<<endl;
        }
        outfile.close();
    }
}

void menu(){
    while (1) {
        cout << "Welcome to hotel management system" << endl;
        cout << "1.check in" << endl;
        cout << "2.check out" << endl;
        cout << "3.search a room" << endl;
        cout << "4.Room information inquiry" << endl;
        cout << "5.History"<<endl;
        cout << "6.exit" << endl;
        cout << "please input your choice :" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                checkin();
                RoomDataWriteIn();
                Sleep(3000);
                system("cls");
                break;
            case 2:
                checkout();
                GuestDataWriteIn();
                Sleep(3000);
                system("cls");
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
    //RoomInitial();
    //cout<<room[0].getRoomType();
    //checkin();
    //GuestInitial();
    return 0;
}
